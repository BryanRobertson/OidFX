//======================================================================================
//! @file         KeyboardEvent.cpp
//! @brief        Event that informs IKeyboardSensitive objects of keyboard events
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


#include "Core/KeyboardEvent.h"


using namespace Core;



//=========================================================================
//! @function    KeyboardEvent::OnChar
//! @brief       Call all event handlers, when a printable char is pressed
//!
//! @param       charValue [in] character value of the key that was pressed
//! @param       repeats		[in] number of times the message has been repeated
//! @param       prevKeyState	[in] previous state of the key. true for down, false for up   
//=========================================================================
void KeyboardEvent::OnChar ( Char charValue, UInt repeats, bool prevKeyState )
{
	//Iterate through the list, calling all OnChar handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnChar( charValue, repeats, prevKeyState );
		}
	}
}
//end KeyboardEvent::OnChar



//=========================================================================
//! @function    KeyboardEvent::OnKeyDown
//! @brief       Call all event handlers when a key is pressed down
//!              
   
//! @param       keyCode		[in] virtual key code of the key pressed
//=========================================================================
void KeyboardEvent::OnKeyDown ( UInt keyCode )
{
	//Iterate through the list, calling all OnKeyDown handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnKeyDown( keyCode );
		}
	}
}
//end KeyboardEvent::OnKeyDown



//=========================================================================
//! @function    Events::KeyboardEvent::OnKeyUp
//! @brief       Call all event handlers when a key is released
//!              
//! @param       keyCode [in] virtual key code of the key pressed
//!      
//=========================================================================
void KeyboardEvent::OnKeyUp ( UInt keyCode )
{
	//Iterate through the list, calling all OnKeyUp handlers
	HandlerStore::iterator begin = m_handlers.begin();
	HandlerStore::iterator current = begin;
	HandlerStore::iterator end = m_handlers.end();

	for ( current = begin; current != end; ++current )
	{
		if ( (*current).get() )
		{
			(*current)->OnKeyUp( keyCode );
		}
	}
}
//end KeyboardEvent::OnKeyUp