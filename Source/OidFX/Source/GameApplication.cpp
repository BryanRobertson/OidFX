//======================================================================================
//! @file         GameApplication.cpp
//! @brief        Base class encapsulating the initialisation, update, and shutdown
//!				  of the game engine
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 30 May 2005
//! @copyright    Bryan Robertson 2005
//
//				  This file is part of OidFX Engine.
//
//  			  OidFX Engine is free software; you can redistribute it and/or modify
//  			  it under the terms of the GNU General Public License as published by
//  			  the Free Software Foundation; either version 2 of the License, or
//  			  (at your option) any later version.
//
//  			  OidFX Engine is distributed in the hope that it will be useful,
//  			  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  			  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  			  GNU General Public License for more details.
//
//  			  You should have received a copy of the GNU General Public License
//  			  along with OidFX Engine; if not, write to the Free Software
//  			  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================


#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/FontManager.h"
#include "Renderer/DisplayModeList.h"
#include "Renderer/RendererFactory.h"
#include "Renderer/RendererWindow.h"
#include "Renderer/EffectManager.h"
#include "Renderer/RenderQueue.h"
#include "Renderer/AutogenTextureManager.h"
#include "Renderer/StateManager.h"
#include "Renderer/TexturePrecacheList.h"
#include "SettingsDialogue/Dialogue.h"
#include "DirectX9Renderer/DirectXRendererCreator.h"
#include "DirectX9Input/DirectXInputSystem.h"
#include "OidFX/GameApplication.h"
#include "OidFX/Scene.h"
#include "OidFX/Camera.h"
#include "OidFX/FirstPersonCamera.h"
#include "OidFX/ThirdPersonCamera.h"
#include "OidFX/MeshManager.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/BillboardManager.h"



using namespace OidFX;



//!@class	GameAppStartFunc
//!@brief	Implementation of SettingsDialogue::IStartFunc
//!
//!			This is passed to the settings dialogue, to
//!			initialise the renderer when the "Start" button 
//!			on the dialogue is pressed
class GameAppStartFunc : public SettingsDialogue::IStartFunc
{

	public:
		GameAppStartFunc( GameApplication& app )
			:IStartFunc(), m_app(app)
		{}

		void operator()()
		{
			m_app.InitialiseRenderer();
		}

	private:

		GameApplication& m_app;
};
//End class GameAppStartFunc



//!@class	GameAppExitFunc
//!@brief	Implementation of SettingsDialogue::IExitFunc
//!
//!			This is passed to the settings dialogue, to
//!			shut down the application when the Exit button
//!			is clicked
class GameAppExitFunc : public SettingsDialogue::IExitFunc
{

	public:

		GameAppExitFunc( GameApplication& app )
			:IExitFunc(), m_app(app)
		{
		}

		void operator()()
		{
			m_app.Quit();
		}

	private:

		GameApplication& m_app;
};
//End class GameAppStartFunc



//=========================================================================
//! @function    GameApplication::GameApplication
//! @brief       Game application constructor
//!
//=========================================================================
GameApplication::GameApplication( )
: Core::Singleton<GameApplication>(this), m_quit(false), m_framerateCounter()
{
	//Set up the renderer factory
	m_rendererFactory = boost::shared_ptr<Renderer::RendererFactory>( new Renderer::RendererFactory() );
	boost::shared_ptr<Renderer::RendererCreator> dxCreator(new DirectX9Renderer::DirectXRendererCreator());
	m_rendererFactory->RegisterCreator ( dxCreator );
}
//End GameApplication::GameApplication



//=========================================================================
//! @function    GameApplication::Run
//! @brief       Main method for the game application
//!              
//! @param       commandLine [in] Command line string passed to the application
//! @param		 logFileName [in] Filename of log file to use
//!              
//! @return      0 if all went well
//!				 A non zero error code, if there was an error.
//!				 The code that calls this method, should return
//!				 this code from the main function
//=========================================================================
Int GameApplication::Run ( std::vector<std::string>& commandLine, const Char* windowTitle,
						  const Char* logFileName )
{
	try
	{
		m_windowTitle = windowTitle;
		Initialise( logFileName );

		if ( m_quit )
		{	
			//If m_quit is true at this point, it means that the user pressed Exit in the 
			//settings dialogue
			PreShutDown();
			ShutDown();
			return 0;
		}

		InitialiseInputSystem();
		InitialiseBillboardManager();
		InitialiseScriptingSystem();
		InitialiseMeshManager();
		InitialiseScene();
		PostInitialise();

		//Initialise the timer
		Core::Timer timer;
		Core::TimerValue timeElapsed = timer.Update();

		//Cap the maximum time elapsed so that the
		//game doesn't mess up
		if ( timeElapsed > 2.0f )
		{
			timeElapsed = 2.0f;
		}

		Core::ConsoleBool con_showfps ( "con_showfps", false );

		OidFX::VisibleObjectList visibleObjectList;

		while (!m_quit)
		{
			//Check that the renderer hasn't been lost
			if ( (m_renderer->RequiresRestore()) && (m_quit == false) )
			{
				m_renderer->Restore(true);
				m_scene->Restore();
			}
			
			//Process any window messages sent to the renderer window
			//Window::ProcessMessage will throw Renderer::RendererWindow:QuitMessage
			//if the quit message was recieved
			m_renderer->Window().ProcessMessageQueue();

			//Update any effect animations
			m_effectManager->UpdateEffects( timeElapsed );

			//Clear out the billboard manager
			m_billboardManager->ClearBillboardList( );

			//Update game logic
			Update ( timeElapsed );

			//Update the billboard manager
			m_billboardManager->Update ( timeElapsed );

			//Clear out the render queue
			m_renderQueue->Clear();

			//Fill the list of visible objects
			visibleObjectList.Clear();
			m_scene->FillVisibleObjectList(visibleObjectList, GetCamera());

			//Queue all visible objects for rendering
			visibleObjectList.QueueAllForRendering ( *m_renderQueue );

			//Sort the render queue
			m_renderQueue->Sort();

			//Start a new frame and clear the screen
			m_renderer->BeginFrame();
			m_renderer->Clear( Renderer::COLOUR_BUFFER | Renderer::DEPTH_BUFFER );

				PreRender();
				Render();

				//Render the contents of the render queue
				m_renderQueue->Render();

				//Render all billboards
				m_billboardManager->Render( GetRenderer(), GetCamera() );

				PostRender();


			//End the frame
			m_renderer->EndFrame();

			//Update the timer
			timeElapsed = timer.Update();
			
			//Update the framerate counter
			if ( con_showfps )
			{
				m_framerateCounter.Update(timeElapsed);
			}

			//Cap the time elapsed between frames
			if ( timeElapsed > 2.0f )
			{
				timeElapsed = 2.0f;
			}
		}

		PreShutDown();
		ShutDown();

	}
	catch ( Renderer::RendererWindow::QuitMessage& exp )
	{
		std::clog << "Quit message recieved. Shutting down" << std::endl;
		PreShutDown();
		ShutDown();
	}
	catch ( std::exception& exp )
	{
		std::stringstream errorMessage;
		errorMessage << "Exeption caught: " << typeid(exp).name() << std::endl
					 << "\t" << exp.what() << std::endl;
		
		Core::DisplayError ( errorMessage.str().c_str(), "Exception caught" );
		
		#ifdef DEBUG_BUILD
			throw;
		#endif
		
		return 1;
	}
	catch ( Core::Exception& exp )
	{
		std::stringstream str;
		str << "Exception caught: " << typeid(exp).name() << "\n"
			<< "\t" <<  exp.What() << "\n\n";
		
		if ( exp.ErrorCode() )
		{
			str << "\tError code: " << exp.ErrorCode() << "\n";
		}

		str	 << "\t" << exp.File() << "\n"
			 << "\t" << exp.Function() << "\n"
			 << "\t" << "Line: " << exp.Line() << "\n" << std::endl;

		std::cerr << str.str() << std::endl;

		Core::DisplayError ( str.str().c_str(), "Exception caught" );
		
		#ifdef DEBUG_BUILD
			throw;
		#endif
		
		 return (exp.ErrorCode()) ? exp.ErrorCode() : 1;
	}

	return 0;
}
//End GameApplication::Run



//=========================================================================
//! @function    GameApplication::CreateRenderer
//! @brief       Creates the renderer, but does not initialise it
//!              
//!				 This allows the renderer to be queried for supported 
//!				 display modes
//!
//! @throw
//=========================================================================
void GameApplication::CreateRenderer()
{
	//Get the "init_renderer" console variable, to allow config.cfg to 
	//specify the renderer to use.
	//
	//If config.cfg hasn't specified a value, then the default value specified here is used
	Core::ConsoleString init_renderer ( "init_renderer", "DirectX9" );

	m_renderer = m_rendererFactory->Create( static_cast<const std::string&>(init_renderer).c_str() );
	m_fontManager = boost::shared_ptr<Renderer::FontManager>( new Renderer::FontManager(*m_renderer) );
}
//End GameApplication::CreateRenderer



//=========================================================================
//! @function    GameApplication::SupportedDisplayModes
//! @brief       Get a list of supported display modes from the renderer
//!              
//!              
//! @return      A pointer to a DisplayModeList object, containing the list
//!				 of supported display modes
//! @throw       
//=========================================================================
const Renderer::DisplayModeList& GameApplication::SupportedDisplayModes() const
{
	return m_renderer->GetDisplayModeList();
}
//End GameApplication::SupportedDisplayModes



//=========================================================================
//! @function    GameApplication::Initialise
//! @brief       Do all initialisation of the application
//!           
//! @param		 logFileName [in] Filename of log file to use
//!              
//! @throw       
//=========================================================================
void GameApplication::Initialise( const Char* logFileName )
{
	InitialiseConsole( logFileName );
	CreateRenderer();
	InitialiseEffectManager();
	InitialiseRenderQueue();

	//Get the variable that specifies whether or not the 
	//configuration dialogue should be shown
	Core::ConsoleBool init_showconfigdialog("init_showconfigdialog", true);

	if ( init_showconfigdialog )
	{
		//Show a configuration dialogue to allow the user to select an
		//appropriate display mode
		GameAppStartFunc startFunc(*this);
		GameAppExitFunc  exitFunc(*this);

		SettingsDialogue::Dialogue dialogue( SupportedDisplayModes(), startFunc, exitFunc );
		dialogue.ShowDialogue();
	}
	else
	{
		//Set the initial display mode to valid settings 
		//if they're invalid
		Core::ConsoleUInt init_mode("init_mode", 0 );
		Core::ConsoleUInt init_bpp ("init_bpp", 32 );
		Core::ConsoleBool init_fullscreen ( "init_fullscreen", true );

		//Validate the colour depth first, as the other settings rely on it
		if ( SupportedDisplayModes().ModeCount(32) == 0 )
		{
			if ( SupportedDisplayModes().ModeCount(16) == 0 )
			{
				throw Core::RuntimeError ( "Error! Could not find any hardware accellerated display modes!\n"
											"Unfortunately your graphics card does not meet the requirements for this demo.",
											 0, __FILE__, __FUNCTION__, __LINE__ );
			}
			else
			{
				init_bpp = 16;
			}
		}

		//Validate the display mode index
		if ( init_mode > SupportedDisplayModes().ModeCount(init_bpp) )
		{
			init_mode = 0;
		}

		//Validate the fullscreen setting
		if ( (init_fullscreen == false) && (SupportedDisplayModes().ModeCount(init_bpp) > 0)
			&& (!SupportedDisplayModes().GetMode(init_mode, init_bpp).SupportsWindowed()) )
		{
			init_fullscreen = false;
		}

		InitialiseRenderer();
	}

	
}
//End GameApplication::Initialise



//=========================================================================
//! @function    GameApplication::InitialiseConsole
//! @brief       Initialise the in-game console. 
//!              
//!				 "Console" in this instance, refers to the underlying console
//!				 system, which is seperate from the console user interface 
//!				 seen at runtime
//!
//! @param		 logFileName [in] Filename of log file to use
//!              
//=========================================================================
void GameApplication::InitialiseConsole ( const Char* logFileName )
{
	m_console = boost::shared_ptr<Core::Console>(new Core::Console(500, 75, logFileName) );
	
	//Exec config.cfg
	m_console->ExecuteString( "exec \"./data/config.cfg\"");
}
//End GameApplication::InitialiseConsole



//=========================================================================
//! @function    GameApplication::InitialiseEffectManager
//! @brief       Initialise the effect manager
//!              
//=========================================================================
void GameApplication::InitialiseEffectManager ()
{
	m_effectManager = boost::shared_ptr<Renderer::EffectManager>(new Renderer::EffectManager(GetRenderer()));
}
//End GameApplication::InitialiseEffectManager



//=========================================================================
//! @function    GameApplication::InitialiseRenderQueue
//! @brief       Initialise the render queue
//!              
//=========================================================================
void GameApplication::InitialiseRenderQueue ()
{
	m_autogenManager = boost::shared_ptr<Renderer::AutogenTextureManager> ( new Renderer::AutogenTextureManager(*m_renderer) );
	m_stateManager = boost::shared_ptr<Renderer::StateManager> ( new Renderer::StateManager(*m_renderer, *m_autogenManager) );
	m_renderQueue = boost::shared_ptr<Renderer::RenderQueue>( new Renderer::RenderQueue (*m_stateManager, *m_renderer) );
}
//End GameApplication::InitialiseRenderQueue



//=========================================================================
//! @function    GameApplication::InitialiseScriptingSystem
//! @brief       Initialise the scripting system
//!              
//!              
//=========================================================================
void GameApplication::InitialiseScriptingSystem ()
{
	//not_implemented_yet;
}
//End GameApplication::InitialiseScriptingSystem



//=========================================================================
//! @function    GameApplication::InitialiseRenderer
//! @brief       Initialise the renderer.
//!
//!				 The display mode will be set automatically by 
//!				 the settings dialogue. Communication between the renderer
//!				 and the settings dialogue takes place through console variables
//!
//!				 The renderer object is instantiated using the renderer factory
//!				 the renderer to be instantiated is set by the console variable
//!				 "renderer", which should be set in config.cfg
//!                
//! @throw       
//=========================================================================
void GameApplication::InitialiseRenderer()
{
	try
	{
		//Check the renderer to see that it supports our minimum specifications
		CheckRendererMeetsMinimumSpec();
	}
	catch ( Core::RuntimeError exp )
	{
		std::ostringstream errorMessage;

		errorMessage << "Sorry, but your computer does not meet the minimum specifications for this demo.\n"
						"This demo has been designed with hardware accellerated graphics cards in mind.\n\n"
						"The minimum graphics card required is an Nvidia Geforce, or competing card with\n"
						"similar specifications\n\n\n"
						<< "Reason: " << exp.What() << std::endl;

		Core::DisplayError ( errorMessage.str().c_str(), "Graphics card not supported" );
		throw;
	}

	m_renderer->Initialise();
	
	//Set the window title
	m_renderer->Window().SetTitle( m_windowTitle.c_str() );

	//Set the default clear colour
	m_renderer->SetClearColour ( Renderer::Colour4f( 0.0f, 0.6f, 0.8f) );
}
//End GameApplication::InitialiseRenderer



//=========================================================================
//! @function    GameApplication::PrecacheResources
//! @brief       Loads any unloaded textures into memory
//=========================================================================
void GameApplication::PrecacheResources()
{

	std::clog << __FUNCTION__ ": Building texture precache list" << std::endl;
	Renderer::TexturePrecacheList precacheList;

	GetEffectManager().Precache( precacheList );
	std::clog << __FUNCTION__ ": Loading textures from precache list" << std::endl;

	precacheList.PrecacheAll( GetRenderer() );
	std::clog << __FUNCTION__ ": All textures from precache list loaded!" << std::endl;

}
//End GameApplication::PrecacheResources



//=========================================================================
//! @function    GameApplication::InitialiseScene
//! @brief       Does any default intialisation of the scene.
//!              
//!              Subclasses of GameApplication may choose to override this
//!				 method, but they should call the default implementation
//!				 at some point, otherwise things will break
//!				 The default implementation should be called before any
//!				 code that accesses the scene, otherwise crashes may occurr.
//!
//!
//! @throw       
//=========================================================================
void GameApplication::InitialiseScene()
{
	m_scene = boost::shared_ptr<Scene> ( new Scene(*this) );
	m_camera = boost::shared_ptr<Camera> ( new FirstPersonCamera( *m_scene, m_renderer->GetHandedness()) );

	//Initialise the camera

	GetCamera().SetProjection ( 90.0f, 
								static_cast<Float>(GetRenderer().ScreenWidth()) / static_cast<Float>(GetRenderer().ScreenHeight()), 
								0.1f, 
								1000.0f );
}
//End GameApplication::InitialiseScene



//=========================================================================
//! @function    GameApplication::InitialiseMeshManager
//! @brief       Initialise the mesh manager
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void GameApplication::InitialiseMeshManager ( )
{
	m_meshManager = boost::shared_ptr<MeshManager>( new MeshManager ( *m_renderer, *m_effectManager ) );
}
//End GameApplication::InitialiseMeshManager




//=========================================================================
//! @function    GameApplication::InitialiseInputSystem
//! @brief       Create and initalise the input system
//!              
//! @throw       
//=========================================================================
void GameApplication::InitialiseInputSystem()
{
	m_inputSystem = boost::shared_ptr<Core::InputSystem>( 
		new DirectX9Input::DirectXInputSystem( GetRenderer().Window().WindowHandle()) );
}
//End GameApplication::InitialiseInputSystem



//=========================================================================
//! @function    GameApplication::InitialiseBillboardManager
//! @brief       Create and initialise the billboard manager
//!              
//=========================================================================
void GameApplication::InitialiseBillboardManager ( )
{
	m_billboardManager = boost::shared_ptr<BillboardManager>
								( new BillboardManager(GetRenderer(), GetStateManager()) );
}
//End GameApplication::InitialiseBillboardManager



//=========================================================================
//! @function    GameApplication::CheckRendererMeetsMinimumSpec
//! @brief       Check that the renderer meets the minimum specification for OidFX
//!              
//! @throw       RuntimeError if the specifications are not met
//=========================================================================
void GameApplication::CheckRendererMeetsMinimumSpec()
{

	if ( GetRenderer().GetDeviceProperty(Renderer::CAP_MAX_STREAMS) < 16 )
	{
		throw Core::RuntimeError( "Your graphics card does not support enough hardware streams.\n"
								  "The minimum number of supported streams supported is 16.", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

}
//End GameApplication::CheckRendererMeetsMinimumSpec



//=========================================================================
//! @function    GameApplication::Update
//! @brief       Update the game world
//!              
//! @param		 timeElapsed [in] Time elapsed since last update
//!              
//! @throw       
//=========================================================================
void GameApplication::Update(Float timeElapsed)
{

	//Update the input system
	m_inputSystem->Update();

	//Update the scene
	UpdateScene(timeElapsed);

	//Update the camera
	GetCamera().Update(timeElapsed);

	//Update the camera
	m_renderer->SetMatrix ( Renderer::MAT_VIEW, m_camera->ViewMatrix()		);
	m_renderer->SetMatrix ( Renderer::MAT_PROJECTION, m_camera->ProjectionMatrix() );
}
//End GameApplication::Update



//=========================================================================
//! @function    GameApplication::UpdateScene
//! @brief       Update the sceney
//!  
//! @param		 timeElapsed [in] Time elapsed since last update
//!              
//! @return      
//! @throw       
//=========================================================================
void GameApplication::UpdateScene(Float timeElapsed)
{
	m_scene->Update(timeElapsed);
}
//End GameApplication::UpdateScene



//=========================================================================
//! @function    GameApplication::PreRender
//! @brief       Called just before a render takes place, to
//!				 allow derived classes to provide their own special functionality
//!              
//!              
//! @throw       
//=========================================================================
void GameApplication::PreRender()
{
}
//End GameApplication::PreRender



//=========================================================================
//! @function    GameApplication::Render
//! @brief       Render the scene
//!              
//!				 Any derived classes that override this, should call
//!				 the default implementation at some point, or things will break
//!              
//! @throw       
//=========================================================================
void GameApplication::Render()
{
}
//End GameApplication::Render



//=========================================================================
//! @function    GameApplication::PostRender
//! @brief       Called just after a render takes place, to
//!				 allow derived classes to provide their own special functionality
//!              
//!                 
//! @throw       
//=========================================================================
void GameApplication::PostRender()
{
}
//End GameApplication::PostRender



//=========================================================================
//! @function    GameApplication::PreShutDown
//! @brief       Override this method for any code that needs to be run
//!				 just before shutdown
//!
//!				 The default implementation of this doesn't actually do anything
//!
//! @return      
//! @throw       
//=========================================================================
void GameApplication::PreShutDown()
{
	
}
//End GameApplication::PreShutDown



//=========================================================================
//! @function    GameApplication::ShutDown
//! @brief       Shut down the application, and all subsystems
//!               
//! @throw       
//=========================================================================
void GameApplication::ShutDown()
{
	
}
//End GameApplication::ShutDown

