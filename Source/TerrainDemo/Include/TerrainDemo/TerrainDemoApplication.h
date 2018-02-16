//======================================================================================
//! @file         TerrainDemoApplication.h
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

#ifndef TERRAINDEMO_TERRAINDEMOAPPLICATION_H
#define TERRAINDEMO_TERRAINDEMOAPPLICATION_H



#include "OidFX/GameApplication.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/Font.h"



//=========================================================================
// Forward declarations
//=========================================================================
namespace TerrainDemo	{	class Game;		}


//namespace TerrainDemo
namespace TerrainDemo
{


	//!@class	TerrainDemoApplication
	//!@brief	Class encapsulating the terrain demo application
	class TerrainDemoApplication : public OidFX::GameApplication, public Core::IKeyboardSensitive
	{
		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			TerrainDemoApplication();

            //=========================================================================
            // Public methods
            //=========================================================================
			void PostInitialise();
			void InitialiseScene();
			void UpdateScene(Float timeElapsed);

			void Render();
			void PostRender();

			void OnKeyDown ( UInt keyCode );										
			void OnKeyUp   ( UInt keyCode )										{ /*Not implemented*/ };
			void OnChar	   ( Char charValue, UInt repeats, bool prevKeyState )	{ /*Not implemented*/ };
			

		private:

			boost::shared_ptr<Game>	m_game;
			Renderer::HFont			m_font;

			Core::EventConnection   m_keyboardHandler;

	};
	//End TerrainDemoApplication


};
//end namespace TerrainDemo


#endif
//#ifndef TERRAINDEMO_TERRAINDEMOAPPLICATION_H
