//======================================================================================
//! @file         ResizeEvent.cpp
//! @brief        Event class and EventHandler class for informing IResizable implementing objects, of a resize
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 03 March 2005
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


#include "Core/ResizeEvent.h"


using namespace Core;


//=========================================================================
//! @function    ResizeEvent::Resize
//! @brief       Call the Resize methods of all handlers bound to this event
//!              
//! @param       width	[in] New width of the object that triggered the resize event 
//! @param       height [in] New height of the object that triggered the resize event
//!              
//=========================================================================
void ResizeEvent::Resize ( UInt width, UInt height )
{
	//Iterate through the list, calling all resize handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if (current->get())
		{
			(*current)->Resize(width, height );
		}
	}
}
//end ResizeEvent::Resize