//======================================================================================
//! @file         ConsoleOutputListener.h
//! @brief        IConsoleOutputListener interface, and related event classes,
//!				  ConsoleOutputEvent, and ConsoleOutputEventHandler. 
//!
//!				  The IConsoleOutputListener Interface allows objects to
//!               be notified when text is written to the console output buffer
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 31 May 2005
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

#ifndef CORE_CONSOLEOUTPUTLISTENER_H
#define CORE_CONSOLEOUTPUTLISTENER_H


#include "Core/Event.h"
#include "Core/EventHandler.h"


//namespace Core
namespace Core
{

	//!@class	IConsoleOutputListener
	//!@brief	IConsoleOutputListener interface. Interface that allows objects to
	//!         be notified when text is written to the console output buffer
	class IConsoleOutputListener
	{
		public:

			virtual void OnConsoleTextOutput ( const Char* text ) = 0;
	
	};
	//end class IConsoleOutputListener


	//!@class	ConsoleOutputEventHandler
	//!@brief	Class which binds a ConsoleOutputEvent to an object implementing IConsoleOutputListener
	//!			The IConsoleOutputListener handles the event, the event handler merely provides an
	//			adapter between the event and the listener object
	class ConsoleOutputEventHandler : public EventHandler<IConsoleOutputListener>,
									  public IConsoleOutputListener
	{
		public:

			ConsoleOutputEventHandler ( IConsoleOutputListener& listener )
				: EventHandler<IConsoleOutputListener>(listener)
			{
			}

			void OnConsoleTextOutput ( const Char* text ) throw()
			{
				GetReciever().OnConsoleTextOutput( text );
			}
	};
	//End ConsoleOutputEventHandler


	//!@class	ConsoleOutputEvent
	//!@brief	Event class, triggered when text is added to a console
	class ConsoleOutputEvent : public Event<ConsoleOutputEventHandler, IConsoleOutputListener>,
							   public IConsoleOutputListener
	{
		public:

			void OnConsoleTextOutput ( const Char* text )
			{
				//Iterate through the list, calling all OnConsoleTextOutput handlers
				HandlerStore::iterator current = m_handlers.begin();
				HandlerStore::iterator end = m_handlers.end();

				for ( ; current != end; ++current )
				{
					//If current isn't an empty slot, then
					//update it
					if (current->get())
					{
						(*current)->OnConsoleTextOutput ( text );
					}
				}
			}
	
	};
	//End class ConsoleOutputEvent

}
//end namespace Core


#endif
//#ifndef CORE_CONSOLEOUTPUTLISTENER_H
