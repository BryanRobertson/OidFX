//======================================================================================
//! @file         ConsoleCommandLine.cpp
//! @brief        Class representing the command line of the console
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

#include "Core/BasicTypes.h"
#include "Core/Console.h"
#include "Core/ConsoleBuffer.h"
#include "Core/ConsoleCommandLine.h"
#include "Core/ConsoleCursor.h"


using namespace Core;


static const UInt maxHistoryLines = 10;


//=========================================================================
//! @function    ConsoleCommandLine::ConsoleCommandLine
//! @brief       ConsoleCommandLine constructor
//!              
//! @return      
//! @throw       
//=========================================================================
ConsoleCommandLine::ConsoleCommandLine ( Console& console )
: m_currentHistoryLine(-1), m_console(console)
{
	m_cursor = boost::shared_ptr<ConsoleCursor>( new ConsoleCursor(*this) );
	m_history = boost::shared_ptr<ConsoleBuffer>( new ConsoleBuffer(maxHistoryLines, console.LineWidth()) );
}
//end ConsoleCommandLine::Constructor



//=========================================================================
//! @function    ConsoleCommandLine::History
//! @brief       Get a line from the command line history
//!
//! @param       index [in] Zero based index into the history, where zero 
//!							is the most recent line in the history
//!						
//!              
//! @return      The appropriate line from the history
//=========================================================================
const std::string& ConsoleCommandLine::History( UInt index ) const
{
	return m_history->History(index);
}
//end ConsoleCommandLine::History


//=========================================================================
//! @function    ConsoleCommandLine::SetFromNextHistoryEntry
//! @brief       Set the command line contents from the next oldest entry in the
//!              history. 
//!              
//!				 Repeated calls to this will get the next oldest entry in the list
//!				 If there are no more entries in the history, then nothing will happen
//!
//=========================================================================
void ConsoleCommandLine::SetFromNextHistoryEntry ( )
{
	++m_currentHistoryLine;

	if ( m_currentHistoryLine >= static_cast<Int>(m_history->Size()) )
	{
		--m_currentHistoryLine;
		return;
	}

	Set( History(static_cast<UInt>(m_currentHistoryLine)) );
}
//end ConsoleCommandLine::SetFromNextHistoryEntry



//=========================================================================
//! @function    ConsoleCommandLine::SetFromPrevHistoryEntry
//! @brief       Set the command line contents from the next newst entry in the
//!              history. 
//!              
//!				 Repeated calls to this will get the next nesest entry in the list
//!				 If there are no more entries in the history, then nothing will happen  
//! 
//=========================================================================
void ConsoleCommandLine::SetFromPrevHistoryEntry ( )
{
	--m_currentHistoryLine;

	if ( m_currentHistoryLine < 0 )
	{
		++m_currentHistoryLine;
		return;
	}

	Set( History(static_cast<UInt>(m_currentHistoryLine)) );
}
//end ConsoleCommandLine::SetFromPrevHistoryEntry


//=========================================================================
//! @function    ConsoleCommandLine::Execute
//! @brief       Execute the contents of the console command line
//!             
//! @return      
//! @throw       
//=========================================================================
bool ConsoleCommandLine::Execute( )
{
	//Copy the line to the command history 
	if ( m_commandLine.length() != 0 )
	{
		m_history->Write ( m_commandLine.c_str() );
		m_history->Write ( "\n" );
	}

	//Execute the contents of the commmand line
	bool result = m_console.ExecuteString ( m_commandLine );

	//Empty the command line buffer, and reset the current history index
	Set("");
	m_currentHistoryLine = -1;

	return result;
}
//end ConsoleCommandLine::Execute