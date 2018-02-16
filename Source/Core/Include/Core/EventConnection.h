//======================================================================================
//! @file         EventConnection.h
//! @brief        EventConnection class. Represents a connection between
//!				  an Event and an EventHandler. 
//!
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 01 March 2005
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

#ifndef CORE_EVENTCONNECTION_H
#define CORE_EVENTCONNECTION_H


#include <iostream>
#include <boost/shared_ptr.hpp>
#include "Core/EventProxy.h"


//namespace Core
namespace Core
{

	class EventProxy;

	//!@class	EventConnection
	//!@brief	Represents a connection between an Event and an EventHandler. 
	//!
	//!			The class is reference counted, and destroys the connection
	//!			when the reference count reaches zero
	class EventConnection
	{
		public:

			//Public types
			inline EventConnection ( );
			inline EventConnection  ( boost::shared_ptr<EventProxy> func, UInt connectionID );
			inline EventConnection	 ( const EventConnection& eventConnection );
			inline ~EventConnection ( );

			inline void operator= ( EventConnection& eventConnection );
			inline bool operator==( EventConnection& eventConnection );
			inline bool operator!=( EventConnection& eventConnection );

			inline bool IsConnected() const;
			inline void Disconnect();		

			inline UInt ID() const			{ return m_connectionID;			   }

		private:

			UInt	m_connectionID;
			boost::shared_ptr<EventProxy>	m_eventProxy;	//!< EventProxy object to allow calls to the event class.
															//!< Any calls to methods of EventProxy must check to see if it is null!
															//!< as a call to Disconnect will set the pointer to null
	};
	//end class EventConnection


    //=========================================================================
    //! @function   EventConnection::EventConnection
    //! @brief      Construct an unconnected event connection
    //!              
    //=========================================================================
	EventConnection::EventConnection ( )
		: m_eventProxy(), m_connectionID(0)
	{
		
	}
	//end EventConnection::EventConnection


	//=========================================================================
    //! @function    EventConnection::EventConnection
    //! @brief       Construct a new event connection, connected to an event class
	//!				 through the EventProxy class passed in EventProxy
    //!              
    //!              
    //! @param       eventProxy		  [in] EventProxy class used to access the Event's methods
	//! @param		 connectionID [in] ID the connection uses to identify itself to the event class
    //=========================================================================
	EventConnection::EventConnection ( boost::shared_ptr<EventProxy> eventProxy, UInt connectionID )
		: m_eventProxy(eventProxy), m_connectionID(connectionID)
	{

	}
	//end EventConnection


    //=========================================================================
    //! @function    EventConnection::EventConnection
    //! @brief       Copy constructor
    //!              
    //!              
    //! @param       eventConnection    
    //=========================================================================
	EventConnection::EventConnection ( const EventConnection& eventConnection )
	:	m_connectionID(eventConnection.m_connectionID),  
		m_eventProxy(eventConnection.m_eventProxy)
	{
		if ( m_eventProxy )
		{
			m_eventProxy->IncrementReferenceCount();
		}
	}
	//end EventConnection::EventConnection



    //=========================================================================
    //! @function    EventConnection::~EventConnection
    //! @brief       Destructor
    //!                 
    //=========================================================================
	EventConnection::~EventConnection ( )
	{		
		#if 0
		std::clog << "EventConnection::~EventConnection: reference count =" << m_eventProxy->ReferenceCount() << std::endl;
		#endif

		if ( m_eventProxy )
		{
			if (m_eventProxy->DecrementReferenceCount() <= 0)
			{	
				#if 0
				std::clog << "Destroying event connection" << std::endl;
				#endif
				Disconnect();
			}
		}
	}
	//end EventConnection::~EventConnection



    //=========================================================================
    //! @function    Events::EventConnection::operator =
    //! @brief       Copy an existing EventConnection
    //!              
    //!              
    //! @param       eventConnection 
    //=========================================================================
	void EventConnection::operator = ( EventConnection& eventConnection )
	{	
		m_connectionID = eventConnection.m_connectionID;
		m_eventProxy = eventConnection.m_eventProxy;

		if ( m_eventProxy )
		{
			m_eventProxy->IncrementReferenceCount();
		}
	}
	//end EventConnection::operator=



    //=========================================================================
    //! @function    Events::EventConnection::IsConnected
    //! @brief       Indicates whether or not this event connection is connected
    //!				 to an event
    //!              
    //! @return      true if the event connection is connected to an event
    //=========================================================================
	bool EventConnection::IsConnected () const
	{
		if ( (m_eventProxy) && (m_eventProxy->IsConnected()) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//end EventConnection::IsConnected ()


    //=========================================================================
    //! @function    Events::EventConnection::Disconnect
    //! @brief       Disconnects the event connection from its event
    //!              After this call, any calls to methods of the event will fail
    //!               
    //=========================================================================
	void EventConnection::Disconnect ( )
	{
		if ( m_eventProxy )
		{
			//Disconnect the event connection, and clear the contents
			m_eventProxy->Disconnect();
			m_connectionID = 0;
			m_eventProxy.reset();
		}
		else
		{
			return;
		}
	}
	//end EventConnection::Disconnect

};
//end namespace Core

#endif
//#ifndef CORE_EVENTCONNECTION_H
