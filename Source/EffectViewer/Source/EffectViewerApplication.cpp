//======================================================================================
//! @file         EffectViewerApplication.cpp
//! @brief        Class encapsulating the effect viewer application
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
#include "Math/Matrix4x4.h"
#include "Math/Vector3D.h"
#include "Renderer/Renderer.h"
#include "Renderer/FontManager.h"
#include "Renderer/TexturePrecacheList.h"
#include "OidFX/GameApplication.h"
#include "EffectViewer/EffectViewerApplication.h"
#include <algorithm>



namespace EffectViewer
{



//=========================================================================
//! @function    EffectViewerApplication::EffectViewerApplication
//! @brief       Effect viewer application constructor
//!
//=========================================================================
EffectViewerApplication::EffectViewerApplication ()
	: GameApplication()
{
}
//End EffectViewerApplication::EffectViewerApplication



//=========================================================================
//! @function    EffectViewerApplication::PostInitialise
//! @brief       Any calls to be made after initialisation
//!              
//!              
//=========================================================================
void EffectViewerApplication::PostInitialise()
{
	GetRenderer().SetClearColour( Renderer::Colour4f( static_cast<UInt>(27), 20, 100, 255 ) );
}
//End EffectViewerApplication::PostInitialise 



//=========================================================================
//! @function    EffectViewerApplication::InitialiseScene
//! @brief       Initialise the terrain demo scene
//=========================================================================
void EffectViewerApplication::InitialiseScene()
{
	using namespace Renderer;

	Core::ConsoleString init_font ( "init_font", "Verdana" );
	Core::ConsoleBool   init_fontbold ( "init_fontbold", true );

	UInt fontSize = 11;

	if ( GetRenderer().ScreenWidth() >= 1000 )
	{
		fontSize = 14;
	}

	UInt fontWeight = init_fontbold ? Renderer::FONTWEIGHT_BOLD : Renderer::FONTQUALITY_DEFAULT;

	m_font = GetFontManager().CreateFontObject ( ((std::string)init_font).c_str(), 
												  fontSize, 
												  fontWeight, 0, false, Renderer::FONTQUALITY_DEFAULT );


	m_effectDisplayer = boost::shared_ptr<EffectDisplayer>( new EffectDisplayer(GetRenderer(), GetEffectManager(), "Data/Art/Effects/Test.ofx") );
	Renderer::TexturePrecacheList precacheList;

	GetRenderer().Enter2DMode();

	//Precache all required textures
	GetEffectManager().Precache( precacheList );
	precacheList.PrecacheAll( GetRenderer() );

}
//End EffectViewerApplication::InitialiseScene


//=========================================================================
//! @function    EffectViewerApplication::UpdateScene
//! @brief       Update the scene
//!              
//! @param       timeElapsed [in] Time elapsed since last update
//!              
//=========================================================================
void EffectViewerApplication::UpdateScene( Float timeElapsed )
{
	
}
//End EffectViewerApplication::UpdateScene



//=========================================================================
//! @function    EffectViewerApplication::Render
//! @brief       Render the scene
//!              
//=========================================================================
void EffectViewerApplication::Render()
{
	m_effectDisplayer->QueueForRendering(GetRenderQueue());
}
//End EffectViewerApplication::Render


}
//end namespace EffectViewer