//======================================================================================
//! @file         KeyboardEvent.h
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

#ifndef CORE_KEYBOARDEVENT_H
#define CORE_KEYBOARDEVENT_H

#include "Core/BasicTypes.h"
#include "Core/KeyboardSensitive.h"
#include "Core/EventHandler.h"
#include "Core/Event.h"


//namespace Core
namespace Core
{

	//!@class	KeyboardEventHandler
	//!@brief	Informs IKeyboardSensitive inplementing objects of keyboard events
	class KeyboardEventHandler : public EventHandler<Core::IKeyboardSensitive>,
							   public Core::IKeyboardSensitive
	{
		public:

			KeyboardEventHandler ( Core::IKeyboardSensitive& keyboardSensitiveObject )
				: EventHandler<Core::IKeyboardSensitive>( keyboardSensitiveObject ) { }

			void OnKeyDown ( UInt keyCode ) 
				{ m_reciever.OnKeyDown(keyCode); }
		
			void OnChar ( Char charValue, UInt repeats, bool prevKeyState )
				{ m_reciever.OnChar(charValue, repeats, prevKeyState); }

			void OnKeyUp ( UInt keyCode )
				{ m_reciever.OnKeyUp(keyCode); }

	};
	//end class KeyboardEventHandler


	//!@class	KeyboardEvent
	//!@brief	Event class that informs IKeyboardSensitive objects of a keyboard events
	class KeyboardEvent : public Event<KeyboardEventHandler, Core::IKeyboardSensitive>, 
						public Core::IKeyboardSensitive
	{
		public:

			KeyboardEvent () : Event<KeyboardEventHandler, Core::IKeyboardSensitive>() {}

			void OnKeyDown ( UInt keyCode );
			void OnChar	   ( Char charValue, UInt repeats, bool prevKeyState );
			void OnKeyUp   ( UInt keyCode );
	};
	//end class KeyboardEvent

};
//end namespace Core


#endif
//#ifndef CORE_KEYBOARDEVENT_H