//======================================================================================
//! @file         ConsoleBuffer.cpp
//! @brief        Class representing the output buffer of a command line console
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
#include "Core/Debug.h"
#include "Core/ConsoleBuffer.h"


using namespace Core;


//=========================================================================
//! @function    ConsoleBuffer::ConsoleBuffer
//! @brief       ConsoleBuffer constructor
//!              
//! @param       maxLines [in] Return the maximum number of lines the buffer can hold 
//! @param		 lineWidth[in] Return the maximum width of a line
//!              
//=========================================================================
ConsoleBuffer::ConsoleBuffer ( UInt maxLines, UInt lineWidth )
: m_front(0), m_back(-1), m_itemCount(0), m_lineWidth(lineWidth)
{
	for ( UInt index=0; index < maxLines; ++index )
	{
		m_buffer.push_back ( std::string() );
		m_buffer[index].reserve ( m_lineWidth );
	}

	//Set up the console to write to the first line in the buffer
	NewLine();
}
//end ConsoleBuffer constructor



//=========================================================================
//! @function    ConsoleBuffer::~ConsoleBuffer
//! @brief       ConsoleBuffer destructor
//!              
//=========================================================================
ConsoleBuffer::~ConsoleBuffer ( )
{

}
//end ConsoleBuffer destructor



//=========================================================================
//! @function    ConsoleBuffer::Write
//! @brief       Write text to the buffer, adding new lines if necessary
//!              
//! @param       text [in] Text to write to the buffer 
//!              
//=========================================================================
void ConsoleBuffer::Write ( const Char* text )
{
	debug_assert ( text != 0, "Null char pointer sent to ConsoleBuffer::Write" );

	if ( (text == 0) || ( strlen(text) == 0) )
	{
		return;
	}

	//Current character we are writing to
	const Char* currentChar = text;

	while ( *currentChar != '\0' )
	{
		switch ( *currentChar )
		{
			//If the current character is a line break, then
			//start a new line
			case '\n':
				NewLine();
			break;
			
			//Start a new line if we encounter an \r\n style line break
			case '\r':
				if ( *(currentChar+1) == '\n' )
				{
					NewLine();
					++currentChar;
				}
			break;


			//If the current character is any other character then add it to the current line
			default:

				//If we reached the maximum line length, then start a new line 
				if (m_buffer[m_back].length() >= m_lineWidth )
				{
					NewLine();
				}
				
				//Insert the new character
				m_buffer[m_back].push_back( *currentChar );
				
			break;
		}

		++currentChar;
	}

}
//end ConsoleBuffer::Write



//=========================================================================
//! @function    ConsoleBuffer::NewLine
//!
//!		         Update the console buffer internals so that future calls to Write() will write to a new line.
//!				 After this call has completed m_back will contain the index of the new back of the buffer, 
//!				 and m_front will contain the index of the new front of the buffer
//!              
//==========================================================================
void ConsoleBuffer::NewLine ( )
{
	//If the buffer is full, then m_itemCount will be equal to m_buffer.size
	if ( m_itemCount == m_buffer.size() )
	{
		//The buffer is full, so we have to pop an item
		//from the front, before we can push one to the front

		//Update the back index and clear the entry
		m_back = (m_back+1) % m_buffer.size();
		m_buffer[m_back] = "";

		//We're popping an item from the front, so increment the front
		//index by one
		m_front = (m_front+1) % m_buffer.size();
		//Don't increment the item count, we're at the maximum number of items

	}
	else
	{
		//The buffer isn't full, so we can just push an item to the back
		//of the buffer

		//Update the back index
		m_back = (m_back+1) % m_buffer.size();

		//Increment the item count
		++m_itemCount;
	}
}
//end ConsoleBuffer::NewLine