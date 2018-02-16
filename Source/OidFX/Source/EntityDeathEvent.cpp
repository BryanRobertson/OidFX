//======================================================================================
//! @file         EntityDeathEvent.cpp
//! @brief        Event handling for entity death
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 13 October 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================

#include "Core/Core.h"
#include "OidFX/EntityNode.h"
#include "OidFX/EntityDeathEvent.h"


using namespace OidFX;



//=========================================================================
//! @function    EntityDeathEvent::OnEntityDeath
//! @brief       Calls all event handlers for the death of this entity
//!              
//! @param       entity 
//!              
//=========================================================================
void EntityDeathEvent::OnEntityDeath ( EntityNode* entity )
{

	//Iterate through the list, calling all OnChar handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnEntityDeath( entity );
		}
	}

}
//End EntityDeathEvent::OnEntityDeath
