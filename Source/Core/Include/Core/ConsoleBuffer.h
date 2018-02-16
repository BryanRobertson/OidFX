//======================================================================================
//! @file         ConsoleBuffer.h
//! @brief        Class representing the output buffer of a command line console
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 21 May 2005
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

#ifndef CORE_CONSOLEBUFFER_H
#define CORE_CONSOLEBUFFER_H

#include <vector>
#include <string>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/ConsoleBufferIterators.h"


//namespace Core
namespace Core
{

	//!@class	ConsoleBuffer
	//!@brief	Class representing the output buffer of a command line console
	//!
	//!			The actual buffer is stored as a fixed size, circular queue of strings
	//!			When the queue is full, it reuses the slot containing the oldest element
	class ConsoleBuffer
	{
		public:

			ConsoleBuffer ( UInt maxLines, UInt lineWidth );
			~ConsoleBuffer ( );
			
			//Public types
			typedef std::vector<std::string> Buffer;
			typedef ConsoleBufferConstIterator const_iterator;
			typedef ConsoleBufferConstReverseIterator const_reverse_iterator;
			
			//Public methods
			void Write ( const Char* text );
			
			inline const std::string& Lines  ( UInt index ) const;
			inline const std::string& History( UInt index ) const;
			inline std::size_t Count() const;
			inline std::size_t Size() const;

			//Iterator access
			inline const_iterator Begin() const;
			inline const_iterator End() const;
			inline const_reverse_iterator RBegin() const;
			inline const_reverse_iterator REnd() const;
			
		private:

			//Private methods
			void NewLine ();

			//Private members
			Buffer m_buffer;		//!< Text buffer, stored as an array of strings, but representing a circular queue
			UInt m_front;			//!< Index of the oldest entry in the buffer
			UInt m_back;			//!< Index of the most recent entry in the buffer
			UInt m_itemCount;		//!< Count of the number of items
			UInt m_lineWidth;		//!< Maximum length of a line
	};
	//end class ConsoleBuffer



    //=========================================================================
    //! @function    ConsoleBuffer::Lines
    //! @brief       Return a line from the buffer
    //!              
    //!              Lines(0) is defined as the oldest line in the buffer
	//!
	//!				 Lines(1) is defined as the second oldest line in the buffer
    //!              
	//!				 If index is greater than or equal to Size() then the result is undefined
	//!				 but is guaranteed not to crash the program
	//!
    //! @param       index [in] Zero based index into the buffer's lines
    //!              
    //! @return      The buffer line at m_buffer[index]
    //=========================================================================
	const std::string& ConsoleBuffer::Lines ( UInt index ) const
	{
		debug_assert ( index < Size(), "History index out of range" );
		return m_buffer[ (m_front + index) % m_buffer.size() ];
	}
	//end ConsoleBuffer::Lines



    //=========================================================================
    //! @function    ConsoleBuffer::History
    //! @brief       Return a previous line from the buffer
    //!              
    //!              History(0) is defined as the most recently added line in
	//!				 the buffer
	//!
	//!				 History(1) is the next most recent line in the buffer
	//!
	//!				 If index is greater than or equal to Size(), then the results are undefined. 
	//!				 (but can be guaranteed not to crash the program)
    //!              
    //! @param       index [in] Zero based index into the buffer's history
    //!              
    //! @return		 The line in the console's history at index
    //=========================================================================
	const std::string& ConsoleBuffer::History( UInt index ) const
	{
		debug_assert ( index < Size(), "History index out of range" );

		//Compute the actual index
		//
		//Note that we cast everything to Int: 
		//Otherwise we don't get the correct answer for actualIndex!
		//Don't change this, it works now! :)
		Int actualIndex = (static_cast<Int>(m_back) - static_cast<Int>(index)) 
										% static_cast<Int>(m_buffer.size());

		if ( actualIndex < 0 )
		{
			actualIndex = static_cast<Int>(m_buffer.size() + actualIndex);
		}

		return m_buffer[ actualIndex ];
	}
	//end ConsoleBuffer::History


    //=========================================================================
    //! @function    ConsoleBuffer::Count
    //! @brief       Return the number of items in the buffer 
    //!              
	//!				 The value returned is guaranteed never to be bigger than
	//!				 the value of maxItems passed to the constructor
	//!
    //! @return      The number of items in the buffer
    //! @throw       
    //=========================================================================
	std::size_t ConsoleBuffer::Count( ) const
	{
		return m_itemCount;
	}
	//end ConsoleBuffer::Count



    //=========================================================================
    //! @function    ConsoleBuffer::Size
    //! @brief       Return the size of the allocated buffer
	//!
	//!				 Because the buffer is a circular queue, this will return
	//!				 the value of maxLines passed to the constructor
	//!
    //! @return      The size of the buffer       
    //=========================================================================
	std::size_t ConsoleBuffer::Size( ) const
	{
		return m_buffer.size();
	}
	//end ConsoleBuffer::Size



    //=========================================================================
    //! @function    ConsoleBuffer::Begin
    //! @brief       Return a const_iterator to the beginning of the buffer   
    //!              
    //! @return      A const_iterator to the beginning of the buffer 
    //=========================================================================
	ConsoleBuffer::const_iterator ConsoleBuffer::Begin() const
	{
		return const_iterator(*this, 0);
	}
	//End ConsoleBuffer::Begin



    //=========================================================================
    //! @function    ConsoleBuffer::End
    //! @brief       Return a const_iterator one past the end of the buffer   
    //!              
    //! @return      A const_iterator one past the end of the buffer
    //=========================================================================
	ConsoleBuffer::const_iterator ConsoleBuffer::End() const
	{
		return const_iterator(*this, static_cast<UInt>(Count()));
	}
	//End ConsoleBuffer::End



    //=========================================================================
    //! @function    ConsoleBuffer::RBegin
    //! @brief       Return a const iterator to the beginning of the reversed buffer
    //!              
    //! @return      A const iterator to the beginning of the reversed buffer
    //=========================================================================
	ConsoleBuffer::const_reverse_iterator ConsoleBuffer::RBegin() const
	{
		return const_reverse_iterator(*this, 0);
	}
	//End ConsoleBuffer::RBegin



    //=========================================================================
    //! @function    ConsoleBuffer::REnd
    //! @brief       Return a const iterator one past the end of the reversed buffer
    //!              
    //! @return      A const iterator one past the end of the reversed buffer
    //=========================================================================
	ConsoleBuffer::const_reverse_iterator ConsoleBuffer::REnd() const
	{
		return const_reverse_iterator(*this, static_cast<UInt>(Count()));
	}
	//End ConsoleBuffer::REnd


};
//end namespace Core


#endif
//#ifndef CORE_CONSOLEBUFFER_H
