//======================================================================================
//! @file         ConsoleBufferIterators.cpp
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

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/ConsoleBuffer.h"
#include "Core/ConsoleBufferIterators.h"


using namespace Core;


//=========================================================================
//! @function    ConsoleBufferConstIterator::operator *
//! @brief       Dereference the iterator
//!
//! @return		 Return the string that the iterator points to      
//=========================================================================
const std::string& ConsoleBufferConstIterator::operator * () const
{
	debug_assert ( m_buffer, "Attempted to dereference null iterator!" );
	debug_assert ( m_index < m_buffer->Size(), "Attempted to dereference invalid iterator!" );

	return m_buffer->Lines(m_index);
}
//end ConsoleBufferConstIterator::operator *


//=========================================================================
//! @function    ConsoleBufferConstIterator::operator ->
//! @brief       
//!               
//=========================================================================
const std::string* ConsoleBufferConstIterator::operator -> () const
{
	debug_assert ( m_buffer, "Attempted to dereference null iterator!" );
	debug_assert ( m_index < m_buffer->Size(), "Attempted to dereference invalid iterator!" );

	return &m_buffer->Lines(m_index);
}
//end ConsoleBufferConstIterator::operator ->


//=========================================================================
//! @function    ConsoleBufferConstIterator::operator *
//! @brief       Dereference the iterator
//!
//! @return		 Return the string that the iterator points to      
//=========================================================================
const std::string& ConsoleBufferConstReverseIterator::operator * () const
{
	debug_assert ( m_buffer, "Attempted to dereference null iterator!" );
	debug_assert ( m_index < m_buffer->Size(), "Attempted to dereference invalid iterator!" ); 

	return m_buffer->History(m_index);
}
//end ConsoleBufferConstReverseIterator::operator *


//=========================================================================
//! @function    ConsoleBufferConstIterator::operator ->
//! @brief       
//!               
//=========================================================================
const std::string* ConsoleBufferConstReverseIterator::operator -> () const
{
	debug_assert ( m_buffer, "Attempted to dereference null iterator!" );
	debug_assert ( m_index < m_buffer->Size(), "Attempted to dereference invalid iterator!" ); 

	return &m_buffer->History(m_index);
}
//end ConsoleBufferConstReverseIterator::operator ->