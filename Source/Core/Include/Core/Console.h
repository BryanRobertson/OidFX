//======================================================================================
//! @file         Console.h
//! @brief        Class to implement a command line console. 
//!
//!				  Stores application output
//!				  Accepts input from a command line
//!				  Stores a list of ConsoleVariable objects, variables which can be
//!				  viewed, and changed from the command line at run time
//!				  Stores ConsoleCommand objects, function objects which can be run from the
//!               command line, or called from code
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

#ifndef CORE_CONSOLE_H
#define CORE_CONSOLE_H

#include <fstream>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <string>
#include "Core/Debug.h"
#include "Core/Singleton.h"


//namespace Core
namespace Core
{


    //=========================================================================
    //Forward declaration
    //=========================================================================
	class ConsoleBuffer;
	class ConsoleCommand;
	class ConsoleCommandManager;
	class ConsoleVariable;
	class ConsoleVariableManager;
	class ConsoleCommandLine;
	class OConsoleBuf;
	class ConsoleOutputEvent;
	class EventConnection;
	class IConsoleOutputListener;


	//Public types
	enum StreamID
	{
		STRM_CONOUT, STRM_CONERR, STRM_CONLOG
	};


	//!@class	Console
	//! @brief  Class to implement a command line console. 
	//!
	//!			Stores application output
	//!			Accepts input from a command line
	//!			Stores a list of ConsoleVariable objects, variables which can be
	//!			viewed, and changed from the command line at run time
	//!			Stores ConsoleCommand objects, function objects which can be run from the
	//!         command line, or called from code
	class Console : public Singleton<Console>
	{
		public:

			Console ( UInt maxLines, UInt lineWidth, const Char* logFileName );
			virtual ~Console ( );

			//Redirection of the standard C++ streams std::cout, std::clog and std::cerr
			//to the console
			void RedirectStandardIOToConsole ();
			void RestoreStandardIO ();

			//Write text to one of the streams
			void Write ( const Char* text, StreamID streamID = STRM_CONOUT );

			//Execute a string
			bool ExecuteString ( const std::string& commandString );

			//Buffer access
			inline const ConsoleBuffer& Buffer() const throw();
			inline ConsoleCommandLine& CommandLine() const throw();

			//Variable and Command access
			inline ConsoleCommandManager&  Commands() const throw();
			inline ConsoleVariableManager& Variables() const throw();

			inline size_t LineWidth() const;

			//IOStreams
			inline std::ostream& Out();
			inline std::ostream& Err();
			inline std::ostream& Log();

			//Event handlers
			EventConnection AddOutputListener ( IConsoleOutputListener& listener ) throw();

		private:

			//Private types
			//! @class	OConsoleBuf
			//! @brief	Streambuf class that writes to a Console object
			class OConsoleBuf : public std::stringbuf
			{
				public:

					inline OConsoleBuf ( StreamID streamID, Console& console );
					inline int sync();

				private:

					Console&  m_console;
					StreamID  m_streamID;
			}; 
			//end class OConsoleBuf

			//Private members
			boost::shared_ptr<ConsoleVariableManager>   m_variables;
			boost::shared_ptr<ConsoleCommandManager>	m_commands;
			boost::shared_ptr<ConsoleBuffer>			m_buffer;
			boost::shared_ptr<ConsoleCommandLine>		m_commandLine;
			UInt										m_lineWidth;

			//Commands
			boost::shared_ptr<ConsoleCommand> m_cmdlistcommand;
			boost::shared_ptr<ConsoleCommand> m_cvarlistcommand;
			boost::shared_ptr<ConsoleCommand> m_execcommand;
			
			//Output streams
			boost::shared_ptr<std::ostream> m_conOut;
			boost::shared_ptr<std::ostream> m_conErr;
			boost::shared_ptr<std::ostream> m_conLog;

			//Buffers for output streams
			boost::shared_ptr<OConsoleBuf> m_conOutBuf;
			boost::shared_ptr<OConsoleBuf> m_conErrBuf;
			boost::shared_ptr<OConsoleBuf> m_conLogBuf;
			
			//Log file
			std::ofstream m_logFile;

			//Event handlers
			boost::shared_ptr<ConsoleOutputEvent> m_outputEvent;

			//Stores the old versions of the standard streams' buffers
			//so they can be restored
			std::streambuf* m_oldCout;
			std::streambuf* m_oldCerr;
			std::streambuf* m_oldClog;
	};
	//end class Console


    //=========================================================================
    //! @function    Console::Buffer
    //! @brief       Return a reference to the console's text buffer
    //!              
    //! @return      A const reference to the console's text buffer
    //! @throw       
    //=========================================================================
	const ConsoleBuffer& Console::Buffer() const
	{
		return *m_buffer;
	}
	//End Console::Buffer


    //=========================================================================
    //! @function    Console::CommandLine
    //! @brief       Return a reference to the console's command line
    //!              
    //!              
    //! @return      A reference to the console's command line
    //=========================================================================
	ConsoleCommandLine& Console::CommandLine() const
	{
		return *m_commandLine;
	}
	//End Console::CommandLine


    //=========================================================================
    //! @function    Console::Commands
    //! @brief       Return a reference to the console's commands
    //!               
    //!              
    //! @return      A reference to the console's commands
    //=========================================================================
	ConsoleCommandManager& Console::Commands() const
	{
		return *m_commands;
	}
	//End Console::Commands


    //=========================================================================
    //! @function    Console::Variables
    //! @brief       Return a reference to the console's variables
    //!              
    //!              
    //! @return      A reference to the console's variables
    //=========================================================================
	ConsoleVariableManager& Console::Variables() const
	{
		return *m_variables;
	}
	//End Console::Variables


    //=========================================================================
    //! @function    Console::LineWidth
    //! @brief       Return the line width of the console
    //!              
    //! @return      The line width of the console
    //=========================================================================
	size_t Console::LineWidth() const
	{
		return m_lineWidth;
	}
	//End Console::LineWidth


	//=========================================================================
    //! @function    Console::Out
    //! @return      Return the console's output stream
    //=========================================================================
	std::ostream& Console::Out ( )
	{
		return *m_conOut;
	}
	//end Console::Out


    //=========================================================================
    //! @function    Console::Err
    //! @return      Return the console's error stream
    //=========================================================================
	std::ostream& Console::Err ( )
	{
		return *m_conErr;
	}
	//end Console::Err


    //=========================================================================
    //! @function    Console::Log
    //! @return      Return the console's log stream
    //=========================================================================
	std::ostream& Console::Log ( )
	{
		return m_logFile;
	}
	//end Console::Log


	 //=========================================================================
    //! @function    OConsoleBuf::OConsoleBuf
    //! @brief       OConsoleBuf constructor
    //!              
    //! @param       streamID	[in] Console stream that this buffer will write to
    //! @param       console	[in] Console that this buffer will write to
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	Console::OConsoleBuf::OConsoleBuf ( StreamID streamID, Console& console )
		: m_streamID(streamID), m_console(console)
	{
	}
	//end OConsoleBuf::OConsoleBuf


    //=========================================================================
    //! @function    OConsoleBuf::sync
    //! @brief       Sync the buffer with the console
    //!              
    //=========================================================================
	int Console::OConsoleBuf::sync ()
	{
		//Write the contents of the buffer out to the console
		m_console.Write( str().c_str(), m_streamID );
	
		//Clear the internal buffer so our output doesn't accumulate in the buffer
		str ("");

		//Call base class sync
		return std::stringbuf::sync( );
	}
	//end OConsoleBuf::sync


};
//end namespace Core

#endif
//#ifndef CORE_CONSOLE_H

