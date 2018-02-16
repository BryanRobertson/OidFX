//======================================================================================
//! @file         MouseEvent.h
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


#ifndef CORE_MOUSEEVENT_H
#define CORE_MOUSEEVENT_H

#include "Core/BasicTypes.h"
#include "Core/MouseSensitive.h"
#include "Core/EventHandler.h"
#include "Core/Event.h"



//namespace Core
namespace Core
{

	//!@class	MouseEventHandler
	//!@brief	Informs IMouseSensitive inplementing objects of Mouse events
	class MouseEventHandler : public EventHandler<Core::IMouseSensitive>,
							   public Core::IMouseSensitive
	{
		public:

			MouseEventHandler ( Core::IMouseSensitive& MouseSensitiveObject )
				: EventHandler<Core::IMouseSensitive>( MouseSensitiveObject ) { }

			void OnMouseMove		( Int movementX, Int movementY )
				{ m_reciever.OnMouseMove(movementX, movementY); }
			
			void OnMouseButtonDown  ( UInt buttonIndex )
				{ m_reciever.OnMouseButtonDown(buttonIndex); }

			void OnMouseButtonUp	( UInt buttonIndex )
				{ m_reciever.OnMouseButtonUp(buttonIndex); }

			void OnMouseScroll		( Int scroll )
				{ m_reciever.OnMouseScroll(scroll); }

	};
	//end class MouseEventHandler


	//!@class	MouseEvent
	//!@brief	Event class that informs IMouseSensitive objects of a Mouse events
	class MouseEvent : public Event<MouseEventHandler, Core::IMouseSensitive>, 
						public Core::IMouseSensitive
	{
		public:

			MouseEvent () : Event<MouseEventHandler, Core::IMouseSensitive>() {}

			void OnMouseMove		( Int movementX, Int movementY );
			void OnMouseButtonDown  ( UInt buttonIndex ); 
			void OnMouseButtonUp	( UInt buttonIndex );
			void OnMouseScroll		( Int scroll );
	};
	//end class MouseEvent

};
//end namespace Core


#endif
//#ifndef CORE_MOUSEEVENT_H
