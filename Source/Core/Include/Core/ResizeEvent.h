//======================================================================================
//! @file         ResizeEvent.h
//! @brief        Event class and EventHandler class for informing IResizable implementing objects, of a resize
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

#ifndef CORE_RESIZEEVENT_H
#define CORE_RESIZEEVENT_H

#include "Core/BasicTypes.h"
#include "Core/Resizable.h"
#include "Core/EventHandler.h"
#include "Core/Event.h"


//namespace Core
namespace Core
{

	//!@class	ResizeEventHandler
	//!@brief	Informs IResizable inplementing objects of a resize event
	class ResizeEventHandler : public EventHandler<Core::IResizable>,
							   public Core::IResizable
	{
		public:

			ResizeEventHandler ( Core::IResizable& resizableObject )
				: EventHandler<Core::IResizable> ( resizableObject ) { }

			void Resize ( UInt width, UInt height ) { m_reciever.Resize( width, height ); }

	};
	//end class ResizeEventHandler


	//!@class	ResizeEvent
	//!@brief	Event class that informs IResizable objects of a resize event
	class ResizeEvent : public Event<ResizeEventHandler, Core::IResizable>, 
						public Core::IResizable
	{
		public:

			ResizeEvent () : Event<ResizeEventHandler, Core::IResizable>() {}

			void Resize ( UInt width, UInt height );
	};
	//end class ResizeEvent

};
//end namespace Core


#endif
//#ifndef CORE_RESIZEEVENT_H