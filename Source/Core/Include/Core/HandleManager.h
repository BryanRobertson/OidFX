//======================================================================================
//! @file         HandleManager.h
//! @brief        HandleManager class. Class responsible for storage and valdation
//!				  of data relating to resource handles
//!
//! @author       Bryan Robertson
//! @date         Tuesday, 01 February 2005
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


#ifndef CORE_HANDLEMANAGERCLASS_H
#define CORE_HANDLEMANAGERCLASS_H

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/Handle.h"
#include <vector>



//namespace Core
namespace Core
{

	//!@class	HandleManager
	//!@brief	Class responsible for storage and valdation of data relating to resource handles
	//!			for the ResourceManager class
	template <class T>
	class HandleManager
	{
		public:

			//Check handle for validity
			inline bool IsHandleValid ( const Handle<T>& handle ) const;

			//Change handles
			inline void GenerateHandleForIndex	( UInt index );
			inline void ClearHandle ( UInt index );

			//Get handle
			inline Handle<T> GetHandle ( UInt index ) const;

			//Get a new magic number
			inline UInt GetNewMagicNumber ( UInt index ) const;

		private:

			//Private types
			typedef std::vector<UInt> MagicNumberStore;
			
			//Private data
			MagicNumberStore m_magicNumbers;

	};
	//end class HandleManager



	//=========================================================================
	//! @function    HandleManager<T>::IsHandleValid
	//! @brief       Returns true if the handle is valid, that is, it refers
	//!				 to a valid resource, and its index value matches the
	//!				 corresponding magic number valud in the magic number store
	//!              
	//! @param       handle 
	//!              
	//! @return      
	//! @throw       
	//=========================================================================
	template <class T>
		bool HandleManager<T>::IsHandleValid ( const Handle<T>& handle ) const
	{
		//First check that the handle isn't null
		if ( handle.IsNull() )
			return false;

		//Then check that the index value isn't bigger than the magic numbers array
		if ( handle.Index() >= m_magicNumbers.size() )
			return false;
		
		//Then check that the corresponding magic number value
		if ( handle.MagicNumber() != m_magicNumbers[handle.Index()] )
			return false;

		return true;
	}
	//end HandleManager<T>::IsHandleValid
	


	//=========================================================================
	//! @function    HandleManager<T>::GenerateHandleForIndex
	//! @brief       Generate a magic number for an existing index in the
	//!				 magic number store. 
	//!				
	//!				 If the index passed is outside the bounds of the handle manager
	//!				 then a new handle will be added
	//!				 
	//! @param       index 
	//=========================================================================
	template <class T>
		void HandleManager<T>::GenerateHandleForIndex ( UInt index )
	{
		if ( (index > 0) && (index < m_magicNumbers.size()) )
		{
			//Make sure that an item at index doesn't already exist
			debug_assert ((m_magicNumbers[index] == 0), "Trying to overwrite magic number!" );		
		}

		while ( index >= m_magicNumbers.size() )
		{
			m_magicNumbers.push_back(0);
		}

		m_magicNumbers[index] = GetNewMagicNumber(index);
	}
	//end HandleManager<T>::SetHandle


	//=========================================================================
	//! @function    HandleManager<T>::ClearHandle
	//! @brief		 Clear the magic number value at index. Index must be less
	//!				 than the size of the magic number array
	//!              
	//! @param       index 
	//!              
	//=========================================================================
	template <class T>
		void HandleManager<T>::ClearHandle ( UInt index )
	{
		//Make sure we the item at index has actually been allocated
		debug_assert ( index < m_magicNumbers.size(), "Item at index hasn't been allocated!" );

		m_magicNumbers[index] = 0;
	}
	//end HandleManager<T>::ClearHandle



	//=========================================================================
	//! @function    HandleManager<T>::GetHandle
	//! @brief		 Construct a handle value for the index provided
	//!				 The index must be less than the size of the magic numbers array
	//!
	//!				 This method is the ONLY way to construct a non-null handle object
	//!				 (not counting copying an existing one of course)
	//!
	//! @param       index 
	//!              
	//=========================================================================
	template <class T>
		Handle<T> HandleManager<T>::GetHandle ( UInt index ) const
	{
		//Make sure we the item at index has actually been allocated
		debug_assert ( index < m_magicNumbers.size(), "Item at index hasn't been allocated!" );

		return Handle<T> ( index, m_magicNumbers[index] );
	}
	//end  HandleManager<T>::GetHandle


	//=========================================================================
	//! @function    HandleManager<T>::GetNewMagicNumber
	//! @brief		 Return a new magic number for the index provided
	//! @param       index 
	//!              
	//=========================================================================
	template <class T>
		UInt HandleManager<T>::GetNewMagicNumber ( UInt index ) const
	{
		static UInt newMagicNumber = 0;

		//Note that this makes the first magic number value 1,
		//this is because Handle uses a zero magic number value for the
		//null handle
		return ++newMagicNumber;
	}
	//end  HandleManager<T>::GetNewMagicNumber

};
//end namespace Core


#endif
//#ifndef CORE_HANDLEMANAGERCLASS_H