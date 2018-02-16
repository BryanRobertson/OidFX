//======================================================================================
//! @file         EventProxy.h
//! @brief        Class that exists for the lifetime of a connection between an Event and EventConnection
//!               
//!				  Allows the EventConnection class to call the methods of the Event class without having
//!			      To know what template parameters the connection was instantiated with.
//!				  Disconnects the connection when the Event class is destroyed.	
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

#ifndef CORE_EVENTPROXY_H
#define CORE_EVENTPROXY_H


#include "Core/BasicTypes.h"


//namespace Core
namespace Core
{


	class EventConnection;

	//!@class	EventProxy
	//!@brief	Exists for the lifetime of the connection between an Event and an EventConnection
	//!			
	//!			Allows the EventConnection class to call the methods of the Event class without having
	//!			to know what template parameters the connection was instantiated with.
	//!			Disconnects the connection when the Event class is destroyed.
	class EventProxy
	{
		public:

			EventProxy ( ) { }

			virtual ~EventProxy(){  }

			virtual bool IsConnected ( ) const = 0;
			virtual void Disconnect ( ) = 0;

			virtual UInt ReferenceCount ( ) const = 0;	
			virtual UInt IncrementReferenceCount ( ) = 0;
			virtual UInt DecrementReferenceCount ( ) = 0;

	};
	//end class EventProxy


};
//end namespace Core

#endif
//#ifndef CORE_EVENTPROXY_H
