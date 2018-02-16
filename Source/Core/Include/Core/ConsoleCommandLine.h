//======================================================================================
//! @file         ConsoleCommandLine.h
//! @brief        Class representing the command line of the console
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

#ifndef CORE_CONSOLECOMMANDLINE_H
#define CORE_CONSOLECOMMANDLINE_H

#include <boost/shared_ptr.hpp>
#include <string>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/Console.h"
#include "Core/ConsoleCursor.h"

//namespace Core
namespace Core
{

	//Forward declarations
	class ConsoleCursor;

	//!@class	ConsoleCommandLine
	//!@brief	Class representing the command line of the console
	class ConsoleCommandLine
	{
		public:

			ConsoleCommandLine( Console& console );

			//Accessors
			inline const std::string& Get() const throw();
			inline const ConsoleCursor& Cursor() const throw();
			inline size_t Length() const throw();
			const std::string& History(UInt index) const throw();

			//Mutators
			inline void AddChar ( Char character );
			inline void Clear ( ) throw();
			inline void Set ( const std::string& str );

			bool Execute ( );
			void SetFromNextHistoryEntry ( ) throw();
			void SetFromPrevHistoryEntry ( ) throw();

		private:

			Console&					 m_console;
			boost::shared_ptr<ConsoleCursor> m_cursor;
			boost::shared_ptr<ConsoleBuffer> m_history;
			std::string						 m_commandLine;
			Int								 m_currentHistoryLine;
			
	};
	//end class ConsoleCommandLine


    //=========================================================================
    //! @function    ConsoleCommandLine::Get
    //! @brief       Get the contents of the command line string
	//!
    //! @return      The contents of the command line string
    //=========================================================================
	const std::string& ConsoleCommandLine::Get() const 
	{
		return m_commandLine;
	}
	//end ConsoleCommandLine::Get



    //=========================================================================
    //! @function    ConsoleCommandLine::Cursor
    //! @brief       Return the command line's cursor
	//!
    //! @return      The command line's cursor object
    //=========================================================================
	const ConsoleCursor& ConsoleCommandLine::Cursor() const
	{
		return *m_cursor;
	}
	//end ConsoleCommandLine::Cursor



    //=========================================================================
    //! @function    ConsoleCommandLine::Length
    //! @brief       Return the length of the command line
    //!              
    //! @return      Return the length of the command line
    //=========================================================================
	size_t ConsoleCommandLine::Length ( ) const
	{
		return m_commandLine.length();
	}
	//end ConsoleCommmandLine::Length




    //=========================================================================
    //! @function    ConsoleCommandLine::AddChar
    //! @brief       Add a character to the command line's buffer
	//!
    //! @param       character [in] Character to add
    //!             
	//!				 If backspace is added, then the previous character in the
	//!				 buffer will be deleted.
	//!				 If a newline is added, then the command line will be executed
	//!
    //=========================================================================
	void ConsoleCommandLine::AddChar ( Char character )
	{
		//Make sure we can't exceed the length of the command line
		if (Length() >= (m_console.LineWidth()-1))
		{
			return;
		}

		switch ( character )
		{
			//Backspace
			case '\b':

				//Check to see if there are any characters left to delete
				if ( m_cursor->GetPosition() != 0 )
				{
					//There are, delete them
					m_cursor->DecrementPosition(1);
					m_commandLine.erase ( Cursor().GetPosition(), 1 );
				}
				else
				{
					//There aren't, throw an exception
					throw OutOfRange ( "No more characters left to delete!", 0, __FILE__, __FUNCTION__, __LINE__ );
				}
			return;

			//Line break, execute the command
			case '\r':
			case '\n':
				Execute();
			return;

			//Any other character we just write to the command line buffer
			default:
				m_commandLine.insert ( Cursor().GetPosition(), &character, 1 );
				m_cursor->IncrementPosition(1);
			
			return;
		}
	}
	//end ConsoleCommandLine::AddChar



    //=========================================================================
    //! @function    ConsoleCommandLine::Set
    //! @brief       Set the contents of the command line
	//!
    //! @param       str [in] String to set the command line to
    //!             
    //=========================================================================
	void ConsoleCommandLine::Set ( const std::string& str )
	{
		m_commandLine = str;
		m_cursor->SetPosition(ConsoleCursor::END);
	}
	//end ConsoleCommandLine::Set
 

    //=========================================================================
    //! @function    ConsoleCommandLine::Clear
    //! @brief       Clear the command line
    //!              
    //=========================================================================
	void ConsoleCommandLine::Clear ( )
	{
		Set ("");
	}
	//end ConsoleCommandLine::Clear



};
//end namespace Core


#endif
//#ifndef CORE_CONSOLECOMMANDLINE_H