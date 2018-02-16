//======================================================================================
//! @file         TerrainDemoApplication.cpp
//! @brief        Class encapsulating the terrain demo application
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 09 June 2005
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
#include "Core/InputSystem.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3D.h"
#include "Renderer/Renderer.h"
#include "Renderer/FontManager.h"
#include "Renderer/TexturePrecacheList.h"
#include "Renderer/EffectManager.h"
#include "OidFX/GameApplication.h"
#include "OidFX/Scene.h"
#include "OidFX/Camera.h"
#include "OidFX/FirstPersonCamera.h"
#include "OidFX/ThirdPersonCamera.h"
#include "OidFX/SkyDomeNode.h"
#include "OidFX/TerrainNode.h"
#include "OidFX/TerrainChunkNode.h"
#include "OidFX/EntityNode.h"
#include "OidFX/Chopper.h"
#include "OidFX/Version.h"
#include "TerrainDemo/Game.h"
#include "TerrainDemo/TerrainDemoApplication.h"
#include <algorithm>



namespace TerrainDemo
{



//=========================================================================
//! @function    TerrainDemoApplication::TerrainDemoApplication
//! @brief       Terrain demo application constructor
//!
//=========================================================================
TerrainDemoApplication::TerrainDemoApplication ()
	: GameApplication()
{
}
//End TerrainDemoApplication::TerrainDemoApplication



//=========================================================================
//! @function    TerrainDemoApplication::PostInitialise
//! @brief       Any calls to be made after initialisation
//!              
//!              
//=========================================================================
void TerrainDemoApplication::PostInitialise()
{
	GetRenderer().SetClearColour( Renderer::Colour4f( 0.26274509803921568627450980392157f, 
													  0.55686274509803921568627450980392f, 
													  0.93333333333333333333333333333333f ) );

	m_keyboardHandler = GetInputSystem().RegisterKeyboardHandler(*this);
}
//End TerrainDemoApplication::PostInitialise 



//=========================================================================
//! @function    TerrainDemoApplication::InitialiseScene
//! @brief       Initialise the terrain demo scene
//=========================================================================
void TerrainDemoApplication::InitialiseScene()
{
	using namespace Renderer;

	m_scene = boost::shared_ptr<OidFX::Scene> ( new OidFX::Scene(*this) );

	std::clog << __FUNCTION__ ": Creating terrain" << std::endl;
	boost::shared_ptr<OidFX::TerrainNode> terrain ( new OidFX::TerrainNode( GetScene(),
																			257,
																			33,
																			80000.0f,
																			8000.0f,
																			"Data/Heightmaps/heights.RAW",
																			"Data/Art/Effects/Terrain.ofx" ) );

	std::clog << __FUNCTION__ ": Adding terrain to scene graph" << std::endl;
	GetScene().Root()->AddChild( terrain );

	std::clog << __FUNCTION__ ": Initialising terrain" << std::endl;
	terrain->InitialiseTerrain();


	std::clog << __FUNCTION__ ": Creating sky dome" << std::endl;
	boost::shared_ptr<OidFX::SkyDomeNode> skyDome ( new OidFX::SkyDomeNode( GetScene(),
																			700.0f,
																			2000.0f,
																			20,
																			"Data/Art/Effects/Sky.ofx",
																			GetEffectManager() ) );

	std::clog << __FUNCTION__ ": Adding sky dome to scene graph" << std::endl;
	GetScene().Root()->AddChild( skyDome );

	std::clog << __FUNCTION__ ": Initialising camera" << std::endl;

	//Initialise the camera
	m_camera = boost::shared_ptr<OidFX::Camera> ( new OidFX::Camera( *m_scene, m_renderer->GetHandedness()) );

	Float aspectRatio = static_cast<Float>(GetRenderer().ScreenWidth())
						/static_cast<Float>(GetRenderer().ScreenHeight());

	GetCamera().SetProjection ( 90.0f, aspectRatio, 
								20.0f, 40000.0f );

	//Initialise the font
	Core::ConsoleString init_font ( "init_font", "Verdana" );
	Core::ConsoleBool   init_fontbold ( "init_fontbold", true );

	//Calculate a good font size for the screen size. This seems to work well
	UInt fontSize = GetRenderer().ScreenHeight() / 40;

	UInt fontWeight = init_fontbold ? Renderer::FONTWEIGHT_BOLD : Renderer::FONTWEIGHT_DEFAULT;

	m_font = GetFontManager().CreateFontObject ( ((std::string)init_font).c_str(), 
												  fontSize, 
												  fontWeight, 0, false, Renderer::FONTQUALITY_DEFAULT );

	//Precache all required textures
	PrecacheResources();


	//Initialise the game
	m_game = boost::shared_ptr<Game>( new Game(*this, GetScene()) );

}
//End TerrainDemoApplication::InitialiseScene


//=========================================================================
//! @function    TerrainDemoApplication::UpdateScene
//! @brief       Update the scene
//!              
//! @param       timeElapsed [in] Time elapsed since last update
//!              
//=========================================================================
void TerrainDemoApplication::UpdateScene( Float timeElapsed )
{
	GameApplication::UpdateScene(timeElapsed);

	m_game->Update( timeElapsed );
}
//End TerrainDemoApplication::UpdateScene



//=========================================================================
//! @function    TerrainDemoApplication::Render
//! @brief       Render the scene
//!              
//=========================================================================
void TerrainDemoApplication::Render()
{
	
}
//End TerrainDemoApplication::Render


//=========================================================================
//! @function    TerrainDemoApplication::PostRender
//! @brief      
//!              
//=========================================================================
void TerrainDemoApplication::PostRender ( )
{

	//Console variables that determine the information that will be displayed
	static Core::ConsoleBool con_showfps ( "con_showfps", false );
	static Core::ConsoleBool dbg_debuginfo ( "dbg_debuginfo", false );

	//Render all text
	GetRenderer().Enter2DMode();

		m_font->SetupRenderState( GetStateManager() );
		m_game->DisplayText( m_font );

		if ( con_showfps )
		{	
			static Core::PooledStringStream framerateString;
			framerateString.str("");
			framerateString << GetFramerateCounter().FrameRate() << " fps" << std::endl;
			
			m_font->WriteText ( framerateString.str().c_str(), 50.0, 50.0 );
		}

		if ( dbg_debuginfo )
		{
			static Core::PooledStringStream debugInfo;
			debugInfo.str("");
			debugInfo << GetCamera().GetPosition();

			m_font->WriteText ( debugInfo.str().c_str(), 50.0, GetRenderer().ScreenHeight() - 100.0f );

			//Display the number of chunks rendered
			debugInfo.str("");
			debugInfo << OidFX::TerrainChunkNode::NodesRenderedThisFrame() << " terrain chunks rendered" << std::endl;
			m_font->WriteText ( debugInfo.str().c_str(), 50.0f, GetRenderer().ScreenHeight() - 50.0f );
		}

	GetRenderer().Exit2DMode();
}
//End TerrainDemoApplication::PostRender



//=========================================================================
//! @function    TerrainDemoApplication::OnKeyDown
//! @brief       Keyboard handler for TerrainDemoApplication
//!              
//! @param       keyCode [in]
//!              
//=========================================================================
void TerrainDemoApplication::OnKeyDown ( UInt keyCode )
{
	if ( keyCode == Core::KEY_ESCAPE )
	{
		std::clog << __FUNCTION__ << ": Escape key pressed, quitting!" << std::endl;
		Quit();
	}
}
//End TerrainDemoApplication::OnKeyDown

}
//end namespace TerrainDemo