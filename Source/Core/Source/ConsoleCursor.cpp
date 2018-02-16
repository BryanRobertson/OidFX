//======================================================================================
//! @file         ConsoleCursor.cpp
//! @brief        Class representing the cursor on the console command line
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

#include "Core/BasicTypes.h"
#include "Core/ConsoleCommandLine.h"
#include "Core/ConsoleCursor.h"


using namespace Core;



//=========================================================================
//! @function    ConsoleCursor::IsAtEnd
//! @brief       Return whether or not the cursor is at the end of the line
//!              
//! @return      true if the cursor is at the end of the line
//!				 false otherwise
//=========================================================================
bool ConsoleCursor::IsAtEnd() const
{
	return ( GetPosition() == m_commandLine.Length() );
}
//end ConsoleCursor::IsAtEnd



//=========================================================================
//! @function    ConsoleCursor::SetPosition
//! @brief       Set the cursor position to a special position on the line
//!				 such as the beginning or end.
//!
//! @param       pos [in] Position to set the cursor to
//!              
//! @return      The new position of the cursor
//=========================================================================
void ConsoleCursor::SetPosition( ConsoleCursor::ECursorPosition pos )
{
	if ( pos == ConsoleCursor::BEGIN )
	{
		SetPosition( 0 );
	}
	else if ( pos == ConsoleCursor::END )
	{
		SetPosition( static_cast<UInt>(m_commandLine.Length()) );
	}
}
//end ConsoleCursor::SetPosition(ECursorPosition)


//=========================================================================
//! @function    ConsoleCursor::SetPosition
//! @brief       Set the position of the cursor absolutely
//!              
//!              
//! @param       pos [in] New position to set the cursor to
//!              
//! @throw       OutOfRange if the new position would be greater than the 
//!				 end of the line
//=========================================================================
UInt ConsoleCursor::SetPosition ( UInt pos )
{
	if ( pos > m_commandLine.Length() )
	{
		throw OutOfRange ( "Cursor position out of range", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	return (m_position = pos);
}
//end ConsoleCursor::SetPosition



//=========================================================================
//! @function    ConsoleCursor::IncrementPosition
//! @brief       Increment the position of the cursor by a set amount
//!              
//! @param       increment [in] Amount to increment the cursor position 
//!              
//! @return      The new position of the cursor
//!
//! @throw       OutOfRange if the new position would be beyond the
//!				 end of the line
//=========================================================================
UInt ConsoleCursor::IncrementPosition ( UInt increment )
{
	if ( (GetPosition() + increment) > m_commandLine.Length() )
	{
		throw OutOfRange ( "Cursor position out of range", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	SetPosition ( GetPosition() + increment );

	return GetPosition();
}
//end ConsoleCursor::IncrementPosition


//=========================================================================
//! @function    ConsoleCursor::DecrementPosition
//! @brief       Decrement the position of the cursor by a set amount
//!              
//! @param       decrement [in] Amount to increment the cursor position 
//!              
//! @return      The new position of the cursor
//!
//! @throw       OutOfRange if the new position would be beyond the
//!				 end of the line
//=========================================================================
UInt ConsoleCursor::DecrementPosition ( UInt decrement )
{
	if ( GetPosition() == 0 )
	{
		throw OutOfRange ( "Cursor position out of range", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	SetPosition ( GetPosition() - decrement );

	return GetPosition();
}
//end ConsoleCursor::DecrementPosition