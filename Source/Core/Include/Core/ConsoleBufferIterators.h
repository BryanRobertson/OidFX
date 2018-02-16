//======================================================================================
//! @file         ConsoleBufferIterators.h
//! @brief        STL style Iterators for the ConsoleBuffer class
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 22 May 2005
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

#ifndef CORE_CONSOLEBUFFERITERATORS_H
#define CORE_CONSOLEBUFFERITERATORS_H


#include <string>


//namespace Core
namespace Core
{

	//Forward declaration
	class ConsoleBuffer;


	//!@class	ConsoleBufferConstIterator
	//!@brief	
	class ConsoleBufferConstIterator
	{
		public:
			
			inline ConsoleBufferConstIterator();

			const std::string& operator*() const;
			const std::string* operator->() const;

			inline ConsoleBufferConstIterator& operator++();
			inline ConsoleBufferConstIterator operator++(int);

			inline bool operator == ( const ConsoleBufferConstIterator& rhs ) const throw();
			inline bool operator != ( const ConsoleBufferConstIterator& rhs ) const throw();

			//Friend classes
			friend class ConsoleBuffer;

		private:

			//Private constructor so that only ConsoleBuffer can
			//construct a ConsoleBufferConstIterator object that refers
			//to an object
			inline ConsoleBufferConstIterator( const ConsoleBuffer& buffer, UInt index );

			const ConsoleBuffer*  m_buffer;
			UInt				  m_index;

	};
	//end class ConsoleBufferConstIterator



	//=========================================================================
    //! @function    ConsoleBufferConstIterator::ConsoleBufferConstReverseIterator
    //! @brief       ConsoleBufferConstIterator constructor
    //!    
    //!                  
    //=========================================================================
	ConsoleBufferConstIterator::ConsoleBufferConstIterator ( )
	: m_buffer(0), m_index(0)
	{
	}
	//end ConsoleBufferConstIterator constructor



    //=========================================================================
    //! @function    ConsoleBufferConstIterator::ConsoleBufferConstIterator
    //! @brief       ConsoleBufferConstIterator constructor
    //!              
    //! @param       buffer [in] Pointer to the buffer that this iterator
	//!							 refers to
    //!                  
    //=========================================================================
	ConsoleBufferConstIterator::ConsoleBufferConstIterator ( const ConsoleBuffer& buffer, UInt index )
	: m_buffer(&buffer), m_index(index)
	{
	}
	//end ConsoleBufferConstIterator constructor



    //=========================================================================
    //! @function    ConsoleBufferConstIterator::operator ++
    //! @brief       Prefix iterator increment
    //!              
    //!              
    //! @return      *this
    //=========================================================================
	ConsoleBufferConstIterator& ConsoleBufferConstIterator::operator ++ ()
	{
		++m_index;

		return (*this);
	}
	//end ConsoleBufferConstIterator::operator ++



	//=========================================================================
    //! @function    ConsoleBufferConstIterator::operator ++
    //! @brief       Postfix iterator increment
    //!              
    //!              
    //! @return      Old value of *this
    //=========================================================================
	ConsoleBufferConstIterator ConsoleBufferConstIterator::operator ++ (int)
	{
		ConsoleBufferConstIterator temp = *(this);
		++(*this);

		return temp;
	}
	// ConsoleBufferConstIterator::operator ++


    //=========================================================================
    //! @function    ConsoleBufferConstIterator::operator ==
    //! @brief       Checks two ConsoleBufferConstIterators for equality
    //!              
    //! @param       rhs 
    //!              
    //! @return      true if the two iterators are equal, false otherwise
    //=========================================================================
	bool ConsoleBufferConstIterator::operator == ( const ConsoleBufferConstIterator& rhs ) const
	{
		if ( (m_buffer == rhs.m_buffer) &&
			 (m_index == rhs.m_index ) )
		{
			return true;
		}

		return false;
	}
	//End ConsoleBufferConstIterator::operator ==


	//=========================================================================
    //! @function    ConsoleBufferConstIterator::operator !=
    //! @brief       Checks two ConsoleBufferConstIterators for inequality
    //!              
    //! @param       rhs 
    //!              
    //! @return      true if the two iterators are not equal, false otherwise
    //=========================================================================
	bool ConsoleBufferConstIterator::operator != ( const ConsoleBufferConstIterator& rhs ) const
	{
		if ( (m_buffer == rhs.m_buffer) &&
			 (m_index == rhs.m_index ) )
		{
			return false;
		}

		return true;
	}
	//End ConsoleBufferConstIterator::operator !=



	//!@class	ConsoleBufferConstReverseIterator
	//!@brief	
	class ConsoleBufferConstReverseIterator
	{
		public:

			inline ConsoleBufferConstReverseIterator();

			const std::string& operator*() const;
			const std::string* operator->() const;

			inline ConsoleBufferConstReverseIterator& operator++();
			inline ConsoleBufferConstReverseIterator operator++(int);

			inline bool operator == ( const ConsoleBufferConstReverseIterator& it ) const throw();
			inline bool operator != ( const ConsoleBufferConstReverseIterator& it ) const throw();

			//Friend classes
			friend class ConsoleBuffer;

		private:

			inline ConsoleBufferConstReverseIterator( const ConsoleBuffer& buffer, UInt index);

			const ConsoleBuffer*  m_buffer;
			UInt				  m_index;
	};
	//end class ConsoleBufferConstReverseIterator



	//=========================================================================
    //! @function    ConsoleBufferConstReverseIterator::ConsoleBufferConstReverseIterator
    //! @brief       ConsoleBufferConstReverseIterator constructor
    //!    
    //!                  
    //=========================================================================
	ConsoleBufferConstReverseIterator::ConsoleBufferConstReverseIterator ( )
	: m_buffer(0), m_index(0)
	{
	}
	//end ConsoleBufferConstReverseIterator constructor



	//=========================================================================
    //! @function    ConsoleBufferConstReverseIterator::ConsoleBufferConstReverseIterator
    //! @brief       ConsoleBufferConstReverseIterator constructor
    //!              
    //! @param       buffer [in] Pointer to the buffer that this iterator
	//!							 refers to
    //!                  
    //=========================================================================
	ConsoleBufferConstReverseIterator::ConsoleBufferConstReverseIterator ( const ConsoleBuffer& buffer, UInt index )
	: m_buffer(&buffer), m_index(index)
	{
	}
	//end ConsoleBufferConstReverseIterator constructor



    //=========================================================================
    //! @function    ConsoleBufferConstReverseIterator::operator ++
    //! @brief       Prefix iterator increment
    //!              
    //!              
    //! @return      *this
    //=========================================================================
	ConsoleBufferConstReverseIterator& ConsoleBufferConstReverseIterator::operator ++ ()
	{
		++m_index;

		return (*this);
	}
	//end ConsoleBufferConstReverseIterator::operator ++



	//=========================================================================
    //! @function    ConsoleBufferConstReverseIterator::operator ++
    //! @brief       Postfix iterator increment
    //!              
    //!              
    //! @return      Old value of *this
    //=========================================================================
	ConsoleBufferConstReverseIterator ConsoleBufferConstReverseIterator::operator ++ (int)
	{
		ConsoleBufferConstReverseIterator temp = *(this);
		++(*this);

		return temp;
	}
	// ConsoleBufferConstReverseIterator::operator ++



	//=========================================================================
    //! @function    ConsoleBufferConstReverseIterator::operator ==
    //! @brief       Checks two ConsoleBufferConstReverseIterator for equality
    //!              
    //! @param       rhs 
    //!              
    //! @return      true if the two iterators are equal, false otherwise
    //=========================================================================
	bool ConsoleBufferConstReverseIterator::operator == ( const ConsoleBufferConstReverseIterator& rhs ) const
	{
		if ( (m_buffer == rhs.m_buffer) &&
			 (m_index == rhs.m_index ) )
		{
			return true;
		}

		return false;
	}
	//End ConsoleBufferConstIterator::operator ==


	//=========================================================================
    //! @function    ConsoleBufferConstReverseIterator::operator !=
    //! @brief       Checks two ConsoleBufferConstIterators for inequality
    //!              
    //! @param       rhs 
    //!              
    //! @return      true if the two iterators are not equal, false otherwise
    //=========================================================================
	bool ConsoleBufferConstReverseIterator::operator != ( const ConsoleBufferConstReverseIterator& rhs ) const
	{
		if ( (m_buffer == rhs.m_buffer) &&
			 (m_index == rhs.m_index ) )
		{
			return false;
		}

		return true;
	}
	//End ConsoleBufferConstIterator::operator !=

}
//end namespace Core


#endif
//#ifndef CORE_CONSOLEBUFFERITERATORS_H
