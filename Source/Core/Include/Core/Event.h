//======================================================================================
//! @file         Event.h
//! @brief		  Base template class representing an event, to which suitable classes can subscribe
//!               
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

#ifndef CORE_EVENTTEMPLATE_H
#define CORE_EVENTTEMPLATE_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "Core/Debug.h"
#include "Core/BasicTypes.h"
#include "Core/EventConnection.h"
#include "Core/EventProxy.h"


namespace Core
{

	//!@class	Event
	//!@brief	Template class for an event.
	//!
	//!			An event represents some action, where other classes have an interest in
	//!			knowning when the event occurs. An example might be a keypress, or a window resize
	//!			
	//!			Event handlers of the right type can be registered with the event, and then
	//!			be notified when the event is updated.
	//!
	//!			The design is based on the observer design pattern, where this class would be
	//!			the subject, and eventhandlers the observers
	template <class Handler, class Reciever>
	class Event : private boost::noncopyable
	{
		public:

			Event();
			virtual ~Event() { DisconnectAll(); }

			//=========================================================================
			// Event public types methods              
			//=========================================================================
			
			//!Proxy class to be passed to EventConnection, to allow it
			//!to access the methods of classes created by this template
			class ProxyType : public EventProxy
			{
				public:

					//ProxyType::Constructor
					ProxyType ( Event<Handler,Reciever>& event )
					: m_event(&event)
					{ 
					}
					//end Events::ProxyType<HandlerType,Reciever>
	
					//ProxyType::Destructor
					~ProxyType () 
					{ 
						Disconnect(); 
					}
					//end ProxyType::Destructor
			
					//ProxyType::SetConnection
					void SetConnection ( EventConnection& connection ) 
					{ 
						m_connection = connection; 
					}
					//end ProxyType::SetConnection

					//ProxyType::IsConnected
					bool IsConnected () const 
					{ 
						return m_event != 0;
					}
					//end ProxyType::IsConnected

					//ProxyType::Disconnect
					void Disconnect  ()
					{		
						if ( IsConnected() )
						{
							m_event->Disconnect( m_connection );
							m_event = 0;
						}
					}
					//end ProxyType::Disconnect

					//ProxyType::ReferenceCount
					inline UInt ReferenceCount() const
					{		
						if ( IsConnected() )
						{
							return m_event->ReferenceCount(m_connection);
						}

						std::cerr << "Called ReferenceCount() on a disconnected proxy object" << std::endl;
						return 0;
					}
					//end ProxyType::ReferenceCount

					//ProxyType::IncrementReferenceCount
					inline UInt IncrementReferenceCount()
					{
						if ( IsConnected() )
						{
							return m_event->IncrementReferenceCount(m_connection);
						}

						std::cerr << "Called IncrementReferenceCount() on a disconnected proxy object!" << std::endl;
						//debug_error ( "Called IncrementReferenceCount() on a disconnected proxy object!" );
						return 0;
					}
					//end ProxyType::IncrementReferenceCount

					//ProxyType::DecrementReferencCount
					inline UInt DecrementReferenceCount()
					{
						if ( IsConnected() )
						{
							return m_event->DecrementReferenceCount(m_connection);
						}

						std::cerr << "Called DecrementReferenceCount() on a disconnected proxy object!" << std::endl;
						//debug_error ( "Called IncrementReferenceCount() on a disconnected proxy object!" );
						return 0;
					}
					//end ProxyType::DecrementReferenceCount

					EventConnection Connection() const { return m_connection; }

				private:
					
					Event<Handler,Reciever>* m_event;
					EventConnection m_connection;
			};
			//end class ProxyType
			
			//=========================================================================
			// Event public methods              
			//=========================================================================

			//Public methods
			EventConnection Connect ( Reciever& reciever );
			void Disconnect	 ( const EventConnection& connection );
			void DisconnectAll ( );
			
			UInt ReferenceCount ( const EventConnection& connection ) const;
			UInt IncrementReferenceCount ( const EventConnection& connection );
			UInt DecrementReferenceCount ( const EventConnection& connection );

		protected:

			//Protected types
			typedef std::vector<boost::shared_ptr<ProxyType> > ProxyStore; 
			typedef std::vector<boost::shared_ptr<Handler> > HandlerStore;
			typedef std::vector<UInt> FreeStore;

			//Protected members
			HandlerStore m_handlers;
			ProxyStore	 m_proxies;
			FreeStore	 m_freeSlots;
	};
	//end class Event


	//=========================================================================
	// Event methods              
	//=========================================================================



	//=========================================================================
	//! @function    Event<HandlerType,Reciever>::Event
	//! @brief       Construct an event object
	//!              
	//!              
	//=========================================================================
	template <class HandlerType, class Reciever>
	Event<HandlerType,Reciever>::Event ( )
	{	

	}
	//end Event::Constructor



	//=========================================================================
	//! @function    Event<HandlerType, Reciever>::Connect
	//! @brief       Connect a reciever object to an event
	//!				 returns an existing connection if a connection between
	//!				 reciever and this event already exists
	//!
	//! @param       reciever [in] reciever object to be connected
	//!
	//=========================================================================
	template <class HandlerType, class Reciever>
	EventConnection Event<HandlerType, Reciever>::Connect ( Reciever& reciever )
	{

		//Guard against events being connected to themselves
		assert ( ((void*)&reciever != (void*)this) && "Attempted to connect an Event to itself!" );

		//First check the list to see if this reciever object is connected already
		UInt index = 0;
		HandlerStore::iterator begin = m_handlers.begin();
		HandlerStore::iterator current = begin;
		HandlerStore::iterator end = m_handlers.end();

		for ( current = begin; current != end; ++current, ++index )
		{
			//If current isn't a null pointer, and current is the event handler for
			//reciever, then we've found what we're looking for
			if ( (current->get()) && (*(*current) == reciever) )
					break;
		}

		if ( current != end )
		{
			assert ( current->get() );

			//We found a matching reciever then return a connection object
			//representing the connection between that reciever and this evevnt
			return m_proxies[index]->Connection();
		}
		else
		{

			UInt newIndex = 0;

			//Add a new reciever object and return a connection to it
			if (m_freeSlots.empty())
			{
				//Because indexes are zero based, and the size of the handlers is one based,
				//the new index will be equal to the current size of the m_handlers store
				//before we add the new item
				newIndex = m_handlers.size();

				m_handlers.push_back( boost::shared_ptr<HandlerType>(new HandlerType(reciever)) );
				m_proxies.push_back ( boost::shared_ptr<ProxyType>(new ProxyType(*this)) );
			}
			else
			{
				//Get the new index from the free store, and pop the index from the free store
				newIndex = m_freeSlots.back();
				m_freeSlots.pop_back();
				
				m_handlers[newIndex] = boost::shared_ptr<HandlerType>(new HandlerType(reciever));
				m_proxies[newIndex] = boost::shared_ptr<ProxyType>(new ProxyType(*this));
				
			}

			//Give the EventConnection its own local scope so that it doesn't
			//kill the connection when it is destructed, see note below
			{
				//Create a new event connection object representing the connection
				EventConnection connection ( m_proxies[newIndex], newIndex );
				//Give the proxy object a copy of the connection
				m_proxies[newIndex]->SetConnection ( connection );
			}

			// Now the reason we gave EventConnection its own local scope there
			// was because we're about to set the reference count for its handler to 1
			// If the EventConnection was destructed after this, then it'd destroy the
			// connection, deleting the handler object we're about to return from this function.
			//
			// Because this Event keeps a copy of the EventConnection in its proxy store
			// its reference count is actually 1 higher than it should be. 
			// If we left this as it is, then the EventConnection would never be destroyed
			// this means if the Reciever object for the event handler had been destroyed
			// then the Event would try to access the memory of a destroyed event
			// the next time the Event was triggered
			//
			// The solution is to set the reference count to 0 here, after the temporary
			// EventConnection we created has been destructed
			//
			// This ensures that the reference count of the EventConnection is always correct
			m_handlers[newIndex]->SetReferenceCount ( 0 );

			return m_proxies[newIndex]->Connection();

		}
		//end if ( current != end )
	}
	//end Event::Connect



	//=========================================================================
	//! @function    Event<HandlerType, Reciever>::Disconnect
	//! @brief       Disconnect a reciever object from an event
	//!
	//! @param       reciever [in] reciever object to be connected
	//!
	//=========================================================================
	template <class HandlerType, class Reciever>
	void Event<HandlerType, Reciever>::Disconnect ( const EventConnection& connection )
	{
		
		#if 0
		std::clog << __FUNCTION__ << ": Disconnecting connection with ID " << connection.ID() << std::endl;
		#endif
		
		//First check that the connection is connected
		if (!connection.IsConnected())
		{
			return;
		}

		assert((connection.ID() < m_handlers.size()) && (connection.ID() < m_proxies.size()));
		assert(m_handlers[connection.ID()]);
		assert(m_proxies[connection.ID()]);

		//Erase the handler and proxy object
		m_handlers[connection.ID()].reset();
		m_proxies[connection.ID()].reset();
		m_freeSlots.push_back(connection.ID());

	}
	//end Event<HandlerType, Reciever>::Disconnect



	//=========================================================================
	//! @function    Event<HandlerType, Reciever>::DisconnectAll
	//! @brief       Disconnect all handler objects, 
	//!
	//!				 Disconnects all the handlers by calling Disconnect
	//!				 on all the proxy objects, and releasing our pointers to them.
	//!			
	//!				 Note that the proxy objects won't be destroyed while
	//!				 EventConnection objects still have a pointer to them,
	//!				 they are just set to the disconnected state
	//!				 
	//=========================================================================
	template <class HandlerType, class Reciever>
	void Event<HandlerType, Reciever>::DisconnectAll ( )
	{
		ProxyStore::iterator begin = m_proxies.begin();
		ProxyStore::iterator current = begin;
		ProxyStore::iterator end = m_proxies.end();
	
		#if 0
		std::clog << __FUNCTION__ << " disconnecting " << m_proxies.size() << " objects" << std::endl;
		#endif

		for ( current = begin; current != end; ++current )
		{
			//If *current is not a null pointer,
			//then disconnect the proxy
			if ( (*current) )
			{
				//If we still have a pointer to a disconnected proxy then something is wrong
				assert ( (*current)->IsConnected() );
				//Disconnect the proxy
				(*current)->Disconnect();
			}
		}
	}
	//end Event<HandlerType, Reciever>::DisconnectAll



	//=========================================================================
	//! @function    Event<HandlerType, Reciever>::ReferenceCount
	//! @brief		 Return the reference count of the event handler
	//=========================================================================
	template <class HandlerType, class Reciever>
	UInt Event<HandlerType, Reciever>::ReferenceCount (const EventConnection& connection) const
	{
		assert( connection.ID() < m_handlers.size() );
		assert( m_handlers[connection.ID()] );

		return m_handlers[connection.ID()]->ReferenceCount();
	}
	//end Event<HandlerType, Reciever>::ReferenceCount


	//=========================================================================
	//! @function    Event<HandlerType, Reciever>::IncrementReferenceCount
	//! @brief		 Increment the reference count of the event handler
	//! @return		 The new reference count of the event handler
	//=========================================================================
	template <class HandlerType, class Reciever>
	UInt Event<HandlerType, Reciever>::IncrementReferenceCount ( const EventConnection& connection )
	{
		assert( connection.ID() < m_handlers.size() );
		assert( m_handlers[connection.ID()] );

		return m_handlers[connection.ID()]->IncrementReferenceCount();
	}
	//end Event<HandlerType, Reciever>::IncrementReferenceCount



	//=========================================================================
	//! @function    Event<HandlerType, Reciever>::DecrementReferenceCount
	//! @brief		 Decrement the reference count of the event handler
	//! @return		 The new reference count of the event handler
	//=========================================================================
	template <class HandlerType, class Reciever>
	UInt Event<HandlerType, Reciever>::DecrementReferenceCount ( const EventConnection& connection  )
	{
		assert( connection.ID() < m_handlers.size() );
		assert( m_handlers[connection.ID()] );

		return m_handlers[connection.ID()]->DecrementReferenceCount();
	}
	//end Event<HandlerType, Reciever>::DecrementReferenceCount


};
//end namespace Core

#endif
//#ifndef CORE_EVENTTEMPLATE_H