//======================================================================================
//! @file         Technique.cpp
//! @brief        Class representing a single technique in an effect
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
#include "Renderer/Technique.h"
#include "Renderer/Pass.h"
#include "Renderer/TexturePrecacheList.h"


using namespace Renderer;



//=========================================================================
//! @function    Technique::Technique
//! @brief       Technique constructor
//!					
//! @param       lodLevel		[in] LOD level of the technique.
//!									 where 0 is the highest detail level
//!
//! @param       receiveShadows [in] Indicates whether or not objects rendered
//!									 with the effect receive shadows
//!
//! @param       castShadows	[in] Indicates whether or not objects rendered
//!									 with the effect cast shadows
//!              
//=========================================================================
Technique::Technique ( UInt lodLevel, bool receiveShadows, bool castShadows )
: m_lodLevel(lodLevel), m_receiveShadows(receiveShadows), m_castShadows(castShadows), m_sortValue(SORT_NORMAL)
{

}
//End Technique::Technique



//=========================================================================
//! @function    Technique::Precache
//! @brief       Tells all passes to list any textures they require to be precached
//!              
//! @param       precacheList [out] List of textures to append to
//!              
//=========================================================================
void Technique::Precache ( TexturePrecacheList& precacheList )
{
	PassStore::iterator itr = PassesBegin();
	PassStore::iterator end = PassesEnd();

	for ( ; itr != end; ++itr )
	{
		itr->Precache(precacheList);
	}

}
//End Technique::Precache



//=========================================================================
//! @function    Technique::Update
//! @brief       Updates the passes 
//!              
//=========================================================================
void Technique::Update ( Float timeElapsedInSeconds )
{

	PassStore::iterator itr = PassesBegin();
	PassStore::iterator end = PassesEnd();

	for ( ; itr != end; ++itr )
	{
		itr->Update(timeElapsedInSeconds);
	}

}
//End Technique::Update