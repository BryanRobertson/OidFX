//======================================================================================
//! @file         VisibleObjectList.cpp
//! @brief        Class containing a list of visible objects to be rendered
//!				  When the scene is rendered, all visible objects add themselves               
//!				  to a VisibleObjectList, in order to be queued for rendering
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 14 July 2005
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
#include "Renderer/RenderQueue.h"
#include "OidFX/SceneObject.h"
#include "OidFX/VisibleObjectList.h"



using namespace OidFX;



//=========================================================================
//! @function    VisibleObjectList::VisibleObjectList
//! @brief       
//=========================================================================
VisibleObjectList::VisibleObjectList ( )
{
}
//End VisibleObjectList::VisibleObjectList



//=========================================================================
//! @function    VisibleObjectList::QueueAllForRendering
//! @brief       Add all objects in the visible object list to a render queue
//!              
//! @param       queue [in] Render queue to add the objects to
//!              
//=========================================================================
void VisibleObjectList::QueueAllForRendering ( Renderer::RenderQueue& renderQueue )
{
	iterator current = m_list.begin();
	iterator end = m_list.end();

	for (  ; current != end ; ++current )
	{
		(*current)->QueueForRendering( renderQueue );
	}
}
//End VisibleObjectList::QueueAllForRendering