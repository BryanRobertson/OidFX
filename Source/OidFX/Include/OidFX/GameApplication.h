//======================================================================================
//! @file         GameApplication.h
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


#ifndef OIDFX_GAMEAPPLICATION_H
#define OIDFX_GAMEAPPLICATION_H


#include "Core/Singleton.h"
#include "Core/FramerateCounter.h"


//=========================================================================
//Forward declaration
//=========================================================================
namespace Core
{
	class InputSystem;
}

namespace Renderer 
{ 
	class DisplayModeList; class IRenderer; class RendererFactory; class FontManager; 
	class EffectManager;class RenderQueue; class StateManager; class AutogenTextureManager;
}

namespace OidFX
{
	class Scene; class Camera; class MeshManager; class BillboardManager;
}


//namespace OidFX
namespace OidFX
{

	//!@class	GameApplication
	//!@brief	Base class encapsulating the initialisation, update, and shutdown
	//!			of the game engine
	class GameApplication : public Core::Singleton<GameApplication>
	{
		public:


            //=========================================================================
            // Constructors
            //=========================================================================
			GameApplication( );


            //=========================================================================
            // Public methods
            //=========================================================================
			Int Run ( std::vector<std::string>& commandLine, const Char* windowTitle, 
					  const Char* logFileName );
			
			inline void Quit() throw();
			void InitialiseRenderer();

			void PrecacheResources();
			
            //=========================================================================
            // Public accessors
            //=========================================================================
			inline Renderer::IRenderer&				GetRenderer()			{ return *m_renderer;		}
			inline Renderer::FontManager&			GetFontManager()		{ return *m_fontManager;	}
			inline Renderer::EffectManager&			GetEffectManager()		{ return *m_effectManager;  }
			inline Renderer::RenderQueue&			GetRenderQueue()		{ return *m_renderQueue;	}
			inline Renderer::StateManager&			GetStateManager()		{ return *m_stateManager;	}
			inline MeshManager&						GetMeshManager()		{ return *m_meshManager;	}
			inline Scene&							GetScene()				{ return *m_scene;			}
			inline Camera&							GetCamera()				{ return *m_camera;			}
			inline const Core::FramerateCounter&	GetFramerateCounter()	{ return m_framerateCounter;	}
			inline Core::InputSystem&				GetInputSystem()		{ return *m_inputSystem;	}
			inline BillboardManager&				GetBillboardManager()	{ return *m_billboardManager;	}

		protected:

			//Protected methods

			//Initialisation
			void CreateRenderer();
			const Renderer::DisplayModeList& SupportedDisplayModes() const;
			
			void Initialise( const Char* logFileName );
			virtual void InitialiseConsole( const Char* logFileName );
			virtual void InitialiseEffectManager ();
			virtual void InitialiseRenderQueue ();
			virtual void InitialiseScriptingSystem();
			virtual void InitialiseMeshManager();
			virtual void InitialiseScene();
			virtual void InitialiseInputSystem();
			virtual void InitialiseBillboardManager();

			virtual void PostInitialise() {};
			virtual void CheckRendererMeetsMinimumSpec();

			//Update
			void Update( Float timeElapsed );
			virtual void UpdateScene( Float timeElapsed );

			//Rendering
			virtual void PreRender();
			virtual void Render();
			virtual void PostRender();

			//Shut down
			virtual void PreShutDown();
			void ShutDown();
			
            //=========================================================================
            // Protected data, but this should stuff really should be private.
			// 
			// Will fix this in a future release when I think about redesigning some of the components
            //=========================================================================
			boost::shared_ptr<Renderer::RendererFactory> m_rendererFactory;
			boost::shared_ptr<Core::Console>			 m_console;
			boost::shared_ptr<Renderer::IRenderer>		 m_renderer;
			boost::shared_ptr<Renderer::FontManager>	 m_fontManager;
			boost::shared_ptr<Renderer::EffectManager>	 m_effectManager;
			boost::shared_ptr<Renderer::AutogenTextureManager> m_autogenManager;
			boost::shared_ptr<Renderer::StateManager>	 m_stateManager;
			boost::shared_ptr<Renderer::RenderQueue>	 m_renderQueue;
			boost::shared_ptr<MeshManager>				 m_meshManager;
			boost::shared_ptr<Scene>					 m_scene;
			boost::shared_ptr<Camera>					 m_camera;
			boost::shared_ptr<Core::InputSystem>		 m_inputSystem;
			boost::shared_ptr<BillboardManager>			 m_billboardManager;

			Core::FramerateCounter						m_framerateCounter;
			
			bool m_quit;
			std::string m_windowTitle;

		private:
		
	};
	//end class GameApplication



    //=========================================================================
    //! @function    GameApplication::Quit
    //! @brief       Sets m_quit to true, which makes the game application quit
    //!              
    //=========================================================================
	void GameApplication::Quit()
	{
		m_quit = true;
	}
	//End GameApplication::Quit


};
//end namespace OidFX


#endif
//#ifndef OIDFX_GAMEAPPLICATION_H