//======================================================================================
//! @file         EventHandler.h
//! @brief        Base class for classes which handle specific events
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 27 February 2005
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

#ifndef CORE_EVENT_H
#define CORE_EVENT_H


//namespace Core
namespace Core
{
	
	//!@class	EventHandler
	//!@brief	Base class for classes which handle specific events
	//!
	//!			Other classes can use these derived classes to register
	//!			interest in specific events.
	//!
	//!			The EventHandler template is used internally by Events, to hold
	//!			reciever objects, which recieve the notification when the event is triggered. 
	template <class Reciever>
	class EventHandler
	{
		public:
			EventHandler( Reciever& reciever ) throw() : m_reciever(reciever), m_referenceCount(1) {}
			virtual ~EventHandler() throw() {}

			bool operator == ( Reciever& reciever ) throw() { return &m_reciever == &reciever; }
			bool operator != ( Reciever& reciever ) throw() { return &m_reciever != &reciever; }

			UInt ReferenceCount () const throw()		{ return m_referenceCount;   }
			UInt IncrementReferenceCount ()	throw()		{ return ++m_referenceCount; }
			UInt DecrementReferenceCount ()	throw()		{ return --m_referenceCount; }
			UInt SetReferenceCount (UInt newCount) throw() { return (m_referenceCount = newCount); }

		protected:

			//Protected methods
			Reciever& GetReciever() const throw() { return m_reciever; }

			//Protected data
			Reciever& m_reciever;
			UInt	  m_referenceCount;
	};
	//end class EventHandler


};
//end namespace Core


#endif
//#ifndef CORE_EVENT_H