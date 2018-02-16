//======================================================================================
//! @file         ManagedPool.h
//! @brief        Template for a container that stores data in a fixed-size pool of
//!               array slots, and allows automatic and efficient reuse of freed slots
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 24 May 2005
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

#ifndef CORE_MANAGEDPOOL_H
#define CORE_MANAGEDPOOL_H

#include <vector>
#include <deque>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{


	//!@class	OutOfFreePoolSlots
	//!@brief	OutOfFreePoolSlots exception. Thrown when attempting to add an item
	//!			to a ManagedPool, when there are no free slots left
	template <class DataType>
	class OutOfFreePoolSlots : public RuntimeError
	{
		public:

		OutOfFreePoolSlots ( const Char* file = "Unknown", const Char* function = "Unknown", const UInt line = 0 ) throw()
		: RuntimeError ( "Error, insufficient free slots to add new item to ManagedPool!", 0, file, function, line )
		{
		}
	};
	//End OutOfFreeSlots


	//!@class	ManagedPool
	//!@brief	 Template for a randomly-accessable container that stores data in a fixed-size pool of
	//!          array slots, that allows automatic and efficient reuse of freed slots
	template <class DataType>
		class ManagedPool
	{
		public:

			//Public types
			typedef std::vector<DataType> DataStore;
			typedef std::deque<UInt> FreeSlotStore;
			typedef DataStore::iterator		  iterator;
			typedef DataStore::const_iterator const_iterator;

			//Public methods

			//Constructor
			ManagedPool( UInt maxSlots );

			//Accessors
			inline DataType& operator[]( UInt index ) const;

			inline iterator	Begin();
			inline iterator End();
			inline const_iterator Begin() const;
			inline const_iterator End() const;

			inline UInt FreeSlotCount() const throw();
			inline UInt UsedSlotCount() const throw();

			//Mutators
			void AddItem	( DataType& item, UInt& index );
			void RemoveItem ( UInt index ); 

		private:

			DataStore		m_dataStore;
			FreeSlotStore	m_freeSlots;
			UInt			m_numberOfFreeSlots;
			UInt			m_maxSlots;

	};
	//end class ManagedPool



	//=========================================================================
	//! @function    ManagedPool<T>::ManagedPool
	//! @brief       ManagedPool<T>::Constructor
	//!              
	//! @param       maxSlots [in] Maximum number of data slots in the pool
	//=========================================================================
	template <class DataType>
		ManagedPool<DataType>::ManagedPool( UInt maxSlots )
	: m_numberOfFreeSlots(maxSlots), m_maxSlots(maxSlots)
	{
		debug_assert(maxSlots != 0, "0 is not a valid value for maxSlots!" );

		m_dataStore.reserve( maxSlots );
	}
	//End ManagedPool<DataType>::ManagedPool



    //=========================================================================
    //! @function    ManagedPool<DataType>::operator []
    //! @brief       Access a member of the pool
    //!                  
    //! @param       index [in] 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	template <class DataType>
		DataType& ManagedPool<DataType>::operator []( UInt index ) const
	{
		debug_assert ( index < m_dataStore.size(), "Index out of range!" );

	
		//We have to cast to DataType& here because
		//the visual studio compiler refuses to recognise that
		//std::vector::operator[] has non-const version.
		//
		//Oh Visual Studio compiler, what hilarious antics will you get up to next?
		return const_cast<DataType&>(m_dataStore[index]);
	}
	//end ManagedPool<DataType>::operator []



    //=========================================================================
    //! @function    ManagedPool<DataType>::Begin
    //! @brief       Return an iterator to the beginning of the sequence
    //!              
    //! @return      An iterator to the beginning of the sequence
    //=========================================================================
	template <class DataType>
		ManagedPool<DataType>::iterator ManagedPool<DataType>::Begin()
	{
		return m_dataStore.begin();
	}
	//End ManagedPool<DataType>::Begin



    //=========================================================================
    //! @function    ManagedPool<DataType>::End
    //! @brief       Return an iterator one past the end of the sequence
    //!              
    //! @return      An iterator one past the end of the sequence
    //=========================================================================
	template <class DataType>
		ManagedPool<DataType>::iterator ManagedPool<DataType>::End()
	{
		return m_dataStore.end();
	}
	//End ManagedPool<DataType>::End()



    //=========================================================================
    //! @function    ManagedPool<DataType>::Begin
    //! @brief       Return a const_iterator to the beginning of the sequence
    //!              
    //! @return      A const_iterator to the beginning of the sequence
    //=========================================================================
	template <class DataType>
		ManagedPool<DataType>::const_iterator ManagedPool<DataType>::Begin() const
	{
		return m_dataStore.begin();
	}
	//End ManagedPool<DataType>::Begin



    //=========================================================================
    //! @function    ManagedPool<DataType>::End
    //! @brief       Return a const_iterator, one past the end of the sequence
    //!              
    //! @return      A const_iterator, one past the end of the sequence
    //=========================================================================
	template <class DataType>
		ManagedPool<DataType>::const_iterator ManagedPool<DataType>::End() const
	{
		return m_dataStore.end();
	}
	//End ManagedPool<DataType>::End



    //=========================================================================
    //! @function    ManagedPool<DataType>::FreeSlotCount
    //! @brief       Return the number of free slots
    //!              
    //!              
    //! @return      The number of free slots
    //=========================================================================
	template <class DataType>
		UInt ManagedPool<DataType>::FreeSlotCount() const
	{
		return m_numberOfFreeSlots
	}
	//End ManagedPool<DataType>::FreeSlotCount



    //=========================================================================
    //! @function    ManagedPool<DataType>::UsedSlotCount
    //! @brief       Return the number of used slots
    //!              
    //! @return      The number of used slots
    //=========================================================================
	template <class DataType>
		UInt ManagedPool<DataType>::UsedSlotCount() const
	{
		return m_maxSlots - m_numberOfFreeSlots;
	}
	//End ManagedPool<DataType>::UsedSlotCount



    //=========================================================================
    //! @function    ManagedPool<DataType>::AddItem
    //! @brief       Add an item to the data pool
    //!              
    //! @param       item	[in] Reference to the item to be added to the pool
    //! @param       index	[out] Index at which the new item was added
    //!              
    //! @throw       OutOfFreeSlots<DataType> if there were no free slots to add a new item
    //=========================================================================
	template <class DataType>
		void ManagedPool<DataType>::AddItem( DataType& item, UInt& index )
	{
		//Check that we actually have some free space
		if ( (m_dataStore.size() >= m_maxSlots) && (m_freeSlots.empty()) )
		{
			throw Core::OutOfFreePoolSlots<DataType>(__FILE__, __FUNCTION__, __LINE__);
		}

		//Add the resource to the resource store
		if ( m_freeSlots.empty() )
		{
			//We've already checked to see if the resource store is full,
			//so if the freeslots list is empty at this point, it means no slots
			//have ever been freed, and we've not hit the size limit yet, so just add a new resource
			index = m_dataStore.size();
			m_dataStore.push_back ( item );
		}
		else
		{
			//Just use the last item in the free slot list
			index = m_freeSlots.back();
			m_dataStore[index] = item;

			//Remove the free slot from the free slot list
			m_freeSlots.pop_back();
		}

	}
	//End ManagedPool<DataType>::AddItem



    //=========================================================================
    //! @function    ManagedPool<DataType>::RemoveItem
    //! @brief       Remove the item at index from the pool
	//!
	//!				 Note, the actual item at index will not be destroyed immediately
	//!				 The slot at index will be added to the free slot list
	//!				 and will be reused.
    //!              
    //! @param       index [in] Index to remove
    //!              
    //=========================================================================
	template <class DataType>
		void ManagedPool<DataType>::RemoveItem ( UInt index )
	{
		debug_assert(index < m_dataStore.size(), "Attempted to remove item with invalid index from pool!" );

		m_freeSlots.push_back(index);
	}
	//End ManagedPool<DataType>::RemoveItem


};
//end namespace Core



#endif //#ifndef CORE_MANAGEDPOOL_H