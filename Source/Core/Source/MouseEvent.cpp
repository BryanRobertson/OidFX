//======================================================================================
//! @file         MouseEvent.cpp
//! @brief        Event that informs IMouseSensitive objects of mouse events
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 19 July 2005
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


#include "Core/MouseEvent.h"


using namespace Core;



//=========================================================================
//! @function    MouseEvent::OnMouseMove
//! @brief       Propagate a mousemove event to all event handlers
//!              
//! @param       movementX 
//! @param       movementY 
//!              
//=========================================================================
void MouseEvent::OnMouseMove ( Int movementX, Int movementY )
{
	//Iterate through the list, calling all OnMouseMove handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnMouseMove ( movementX, movementY );
		}
	}

}
//End MouseEvent::OnMouseMove



//=========================================================================
//! @function    MouseEvent::OnMouseButtonUp
//! @brief       Propagate mouse button up event to all event handlers
//!              
//! @param       buttonIndex [in] 
//!              
//=========================================================================
void MouseEvent::OnMouseButtonUp ( UInt buttonIndex )
{
	
	//Iterate through the list, calling all OnMouseButtonUp handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnMouseButtonUp( buttonIndex );
		}
	}

}
//End MouseEvent::OnMouseButtonUp



//=========================================================================
//! @function    MouseEvent::OnMouseButtonDown
//! @brief       Propagate mouse button down event to all event handlers
//!              
//! @param       buttonIndex [in] 
//!              
//=========================================================================
void MouseEvent::OnMouseButtonDown ( UInt buttonIndex )
{
	
	//Iterate through the list, calling all OnMouseButtonUp handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnMouseButtonDown( buttonIndex );
		}
	}

}
//End MouseEvent::OnMouseButtonDown



//=========================================================================
//! @function    MouseEvent::OnMouseScroll
//! @brief       Propagate a mouse scroll event down to all event handlers
//!              
//!              
//! @param       scroll [in]
//!              
//=========================================================================
void MouseEvent::OnMouseScroll ( Int scroll )
{
	//Iterate through the list, calling all OnMouseScroll handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnMouseScroll( scroll );
		}
	}
}
//End MouseEvent::OnMouseScroll