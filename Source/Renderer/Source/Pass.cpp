//======================================================================================
//! @file         Pass.cpp
//! @brief        Pass class
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 24 June 2005
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
#include "Renderer/Pass.h"
#include "Renderer/RenderState.h"
#include "Renderer/TexturePrecacheList.h"


using namespace Renderer;



//=========================================================================
//! @function    Pass::Pass
//! @brief       Pass constructor 
//!              
//! @param       renderState [in] Render state for the pass
//!              
//=========================================================================
Pass::Pass ( const RenderState& renderState )
: m_renderState(renderState)
{

}
//End Pass::Pass



//=========================================================================
//! @function    Pass::Precache
//! @brief       Adds all textures that need to be precached to a list
//!
//! @param		 precacheList [out] List of textures to append to
//=========================================================================
void Pass::Precache ( TexturePrecacheList& precacheList )
{
	m_renderState.Precache(precacheList);
}
//End Pass::Precache


//=========================================================================
//! @function    Pass::Update
//! @brief       Update the render state of the pass
//!				 This includes updating any texture animations
//!              
//=========================================================================
void Pass::Update ( Float timeElapsedInSeconds )
{
	m_renderState.UpdateTextureAnimations( timeElapsedInSeconds );
}
//End Pass::Update