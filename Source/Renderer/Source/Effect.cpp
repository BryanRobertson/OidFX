//======================================================================================
//! @file         Effect.cpp
//! @brief        Effect class
//!               
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
#include "Renderer/Effect.h"
#include "Renderer/Technique.h"
#include "Renderer/TexturePrecacheList.h"


using namespace Renderer;



//=========================================================================
//! @function    Effect::Effect
//! @brief       Effect constructor
//!              
//! @param       fileName [in]
//!              
//! @return      
//! @throw       
//=========================================================================
Effect::Effect ( const Char* fileName )
: Core::Resource(fileName)
{
}
//End Effect::Effect



//=========================================================================
//! @function    Effect::Precache
//! @brief       Add a list of all textures that need to be loaded by the effect
//!				 
//!				 When the effect is loaded, the textures are not loaded by default
//!				 This allows the application more control over when resources are loaded,
//!				 control that may be required if the application is to have a loading screen, for example
//!              
//! @param       precacheList [out] List to append textures to
//!              
//=========================================================================
void Effect::Precache ( TexturePrecacheList& precacheList )
{
	TechniqueStore::iterator itr = TechniquesBegin();
	TechniqueStore::iterator end = TechniquesEnd();

	for ( ; itr != end; ++itr )
	{
		itr->Precache(precacheList);
	}	
}
//End Effect::Precache



//=========================================================================
//! @function    Effect::Update
//! @brief       Update all techniques
//!              
//=========================================================================
void Effect::Update ( Float timeElapsedInSeconds )
{
	TechniqueStore::iterator itr = TechniquesBegin();
	TechniqueStore::iterator end = TechniquesEnd();

	for ( ; itr != end; ++itr )
	{
		itr->Update(timeElapsedInSeconds);
	}
}
//End Effect::Update