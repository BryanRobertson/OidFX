//======================================================================================
//! @file         Util.h
//! @brief        Small utility functions. Anything that doesn't deserve its own header
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 01 July 2005
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


#ifndef CORE_COREUTIL_H
#define CORE_COREUTIL_H


#include <list>

//namespace Core
namespace Core
{

    //=========================================================================
    // Implementation
    //=========================================================================


    //=========================================================================
    //! @function    Core::Min<T>
    //! @brief       The windows headers define a macro "min", which breaks std::min
    //!				 This method provides a replacement            
	//!
    //! @param       first	[in] First object to compare 
    //! @param       second [in] Second object to compare
    //!              
    //! @return      The reference to whichever of first and second is the smallest
    //=========================================================================
	template <class T>
		const T& Min ( const T& first, const T& second ) 
	{
		if ( first < second )
		{
			return first;
		}
		else
		{
			return second;
		}
	}
	//End Core::Min


	//=========================================================================
    //! @function    Core::Max<T>
    //! @brief       The windows headers define a macro "max", which breaks std::max
    //!				 This method provides a replacement            
	//!
    //! @param       first	[in] First object to compare 
    //! @param       second [in] Second object to compare
    //!              
    //! @return      The reference to whichever of first and second is the smallest
    //=========================================================================
	template <class T>
		const T& Max ( const T& first, const T& second ) 
	{
		if ( first > second )
		{
			return first;
		}
		else
		{
			return second;
		}
	}
	//End Core::Max


	//=========================================================================
    //! @function    SpliceOntoEnd<ListType>
    //! @brief       Move a range of elements from one list onto the end of another
    //!              
	//!				 This is to be used in place of std::list::splice,
	//!				 since the original seems far too easy to make mistakes with
	//!
    //! @param       begin		  [in]	Iterator to the first item to be moved
	//! @param		 end		  [in]  Iterator one after the last item to be moved
    //! @param       source		  [in]  Source list
    //! @param       destination  [in]  Destination list
    //!              
    //=========================================================================
	template <class ListType>
		void SpliceOntoEnd ( ListType::iterator begin,
							 ListType::iterator end,
							 ListType& source,
							 ListType& destination )
	{

		destination.splice ( destination.end(),
							   source,
							   begin, 
							   end );

	}
	//End SpliceOntoEnd<ListType>



	//=========================================================================
    //! @function    SpliceOntoBeginning<ListType>
    //! @brief       Move a range of elements from one list to the beginning of another
	//!
	//!				 This is to be used in place of std::list::splice,
	//!				 since the original seems far too easy to make mistakes with
	//!  
    //! @param       begin		 [in]	Iterator to the first item to move
	//! @param		 end		 [in]	Iterator one after the last item to move
    //! @param       source		 [in]	Source list
    //! @param       destination [in]	Destination list
    //!              
    //=========================================================================
	template <class ListType>
		void SpliceOntoBeginning (  ListType::iterator begin,
									ListType::iterator end,
									ListType& source,
									ListType& destination )
	{

		destination.splice ( destination.begin(),
							   source,
							   begin, 
							   end );

	}
	//End SpliceOntoBeginning<ListType>



    //=========================================================================
    //! @function    SpliceOntoEnd<ListType>
    //! @brief       Move an element from one list onto the end of another
    //!              
	//!				 This is to be used in place of std::list::splice,
	//!				 since the original seems far too easy to make mistakes with
	//!
    //! @param       element	  [in]	Iterator to an item from source
    //! @param       source		  [in]  Source list
    //! @param       destination  [in]  Destination list
    //!              
    //=========================================================================
	template <class ListType>
		void SpliceOntoEnd ( ListType::iterator element,
							 ListType& source,
							 ListType& destination )
	{

		destination.splice ( destination.end(),
							   source,
							   element );

	}
	//End SpliceOntoEnd<ListType>



	//=========================================================================
    //! @function    SpliceOntoBeginning<T,AllocatorType>
    //! @brief       Move an element from one list to the beginning of another
	//!
	//!				 This is to be used in place of std::list::splice,
	//!				 since the original seems far too easy to make mistakes with
	//!  
    //! @param       element	 [in]	Iterator to an item in source
    //! @param       source		 [in]	Source list
    //! @param       destination [in]	Destination list
    //!              
    //=========================================================================
	template <class ListType>
		void SpliceOntoBeginning ( ListType::iterator element,
								   ListType& source,
								   ListType& destination )
	{

		destination.splice ( destination.end(),
								source,
								element );

	}
	//End SpliceOntoBeginning<ListType>

};
//end namespace Core


#endif
//#ifndef CORE_COREUTIL_H
