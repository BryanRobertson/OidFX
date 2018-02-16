//======================================================================================
//! @file         Console.cpp
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

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/ConsoleOutputListener.h"
#include "Core/ConsoleVariable.h"
#include "Core/ConsoleCommand.h"
#include "Core/ConsoleVariableManager.h"
#include "Core/ConsoleCommandManager.h"
#include "Core/ConsoleCommandLineParser.h"
#include "Core/ConsoleBuffer.h"
#include "Core/ConsoleCommandLine.h"
#include "Core/Console.h"
#include "Core/ConsoleCommands/About.h"
#include "Core/ConsoleCommands/CmdList.h"
#include "Core/ConsoleCommands/CvarList.h"
#include "Core/ConsoleCommands/Exec.h"

#ifdef WIN32
#include <windows.h> //OutputDebugString
#include <Shlobj.h>
#endif


using namespace Core;


//=========================================================================
//! @function    Console::Console
//! @brief       Console constructor
//!              
//!              
//! @param       maxLines [in]	Maximum number of history lines stored
//! @param		 lineWidth[in]	Maximum length of a line, in characters
//! @param		 logFileName[in] Filename for the log file
//=========================================================================
Console::Console ( UInt maxLines, UInt lineWidth, const Char* logFileName )

: 
  Singleton<Console>(this), //This is OK, because the singleton constructor only stores the pointer to this
  m_variables(new ConsoleVariableManager),
  m_commands(new ConsoleCommandManager),
  m_buffer(new ConsoleBuffer(maxLines, lineWidth)),
  m_lineWidth(lineWidth)
{

	m_commandLine = boost::shared_ptr<ConsoleCommandLine>(new ConsoleCommandLine(*this));
	
	//Init event handling
	m_outputEvent = boost::shared_ptr<ConsoleOutputEvent> ( new ConsoleOutputEvent() );

	//Set up the output streams
	m_conOutBuf = boost::shared_ptr<OConsoleBuf>(new OConsoleBuf(STRM_CONOUT, *this ));
	m_conErrBuf = boost::shared_ptr<OConsoleBuf>(new OConsoleBuf(STRM_CONERR, *this ));
	m_conLogBuf = boost::shared_ptr<OConsoleBuf>(new OConsoleBuf(STRM_CONLOG, *this ));

	m_conOut = boost::shared_ptr<std::ostream>(new std::ostream(m_conOutBuf.get()));
	m_conErr = boost::shared_ptr<std::ostream>(new std::ostream(m_conErrBuf.get()));
	m_conLog = boost::shared_ptr<std::ostream>(new std::ostream(m_conLogBuf.get()));

	//Set up the built-in console commands cmdlist, cvarlist, and exec
	m_cmdlistcommand = boost::shared_ptr<ConsoleCommand>( new ConsoleCommands::CmdList() );
	m_cvarlistcommand = boost::shared_ptr<ConsoleCommand>( new ConsoleCommands::CvarList());
	m_execcommand = boost::shared_ptr<ConsoleCommand>( new ConsoleCommands::Exec());

	//Redirect I/O to the console
	RedirectStandardIOToConsole();

	//Set up the log file
	if ( (logFileName != 0) && (logFileName != "") )
	{
		std::ostringstream filePath;

		#ifdef WIN32

			//On windows we store the log file on the desktop
			//
			//This makes it easy to find and delete. Also, there shouldn't be any access rights
			//issues
			TCHAR logFilePath[MAX_PATH];
			if ( SHGetSpecialFolderPath(0, logFilePath, CSIDL_DESKTOP, true ) )
			{
				filePath << logFilePath << "\\" << logFileName;
			}
			else
			{
				filePath << ".\\" << logFileName;
			}

		#else

			filePath << "./" << logFileName;

		#endif

		m_logFile.open ( filePath.str().c_str() );

		if ( m_logFile )
		{
			std::clog << "Log file " << filePath.str().c_str() << " created successfully" << std::endl;
		}
		else
		{
			std::cerr << "Error: Failed to create log file " << filePath.str().c_str() << "!" << std::endl;
		}

	}

	std::clog << "Console initialised" << std::endl;

}
//end Console::Console



//=========================================================================
//! @function    Console::~Console
//! @brief       Console destructor
//!              
//!              
//=========================================================================
Console::~Console ( )
{
	RestoreStandardIO();
	m_logFile.close();
}
//end Console::~Console



//=========================================================================
//! @function    Console::RedirectStandardIOToConsole
//! @brief       Redirect the standard C++ streams, cout and cerr
//!				 to write to the console
//!              
//=========================================================================
void Console::RedirectStandardIOToConsole ()
{
	m_oldCout = std::cout.rdbuf( m_conOut->rdbuf() );
	m_oldCerr = std::cerr.rdbuf( m_conErr->rdbuf() );
	m_oldClog = std::clog.rdbuf( m_conLog->rdbuf() );
}
//end Console::RedirectStandardIOToConsole



//=========================================================================
//! @function    Console::RestoreStandardIO
//! @brief       Restore the states of the standard iostreams to their
//!              original values
//=========================================================================
void Console::RestoreStandardIO ()
{
	std::cout.rdbuf( m_oldCout );
	std::cerr.rdbuf( m_oldCerr );
	std::clog.rdbuf( m_oldClog );
}
//end Console::RestoreStandardIO



//=========================================================================
//! @function    Console::Write
//! @brief       Write text to one of the console's stream
//!              
//! @param		 text	  [in]	Text to write to the console
//! @param		 streamID [in]	Stream to write to to
//=========================================================================
void Console::Write ( const Char* text, StreamID streamID )
{
	//Note that the case statements falling through to the next
	//case statement is intentional.
	switch ( streamID )
	{
		case STRM_CONLOG:
		case STRM_CONERR:
			m_logFile << text;
			m_logFile.flush();

		case STRM_CONOUT:
		
			#ifdef WIN32
				OutputDebugString ( text );
			#endif

				m_buffer->Write( text );
				m_outputEvent->OnConsoleTextOutput ( text );

			return;
	}
}
//end Console::Write



//=========================================================================
//! @function    Console::AddOutputListener
//! @brief       Add an output listener
//!
//!				 An output listener is an object that will be automatically
//!				 updated every time text is written to the console              
//!
//! @param       listener [in] Listener object 
//!              
//! @return      A connection object between the event and the event handler
//=========================================================================
EventConnection Console::AddOutputListener ( IConsoleOutputListener& listener )
{
	return m_outputEvent->Connect ( listener );
}
//End Console::AddOutputListener



//=========================================================================
//! @function    Console::ExecuteString
//! @brief       Execute a string, as if it were typed in on the command line
//!              
//! @param       commandString [in] The string to execute
//!              
//=========================================================================
bool Console::ExecuteString ( const std::string& commandString )
{
	if ( commandString.empty() )
	{
		return false;
	}

	ConsoleCommandLineParser commandLineParser ( commandString.c_str() );

	if (!commandLineParser.Succeeded())
	{
		Err() << "Bad command - command line parse error" << std::endl;
		return false;
	}

	//If the line was a comment, then ignore it
	if ( commandLineParser.CommandName().empty() )
	{
		return true;
	}
	
	//First search through the commands for a matching entry
	ConsoleCommandManager::iterator commandSearchResult;
	commandSearchResult = Commands().Find ( commandLineParser.CommandName().c_str() );

	if ( commandSearchResult != Commands().End ( ) )
	{
		//We found a matching command, execute it
		return commandSearchResult->second->Execute ( commandLineParser.Arguments() );
	}

	//If no match is found, then search through the variables for a matching entry
	ConsoleVariableManager::iterator variableSearchResult;
	variableSearchResult = Variables().Find ( commandLineParser.CommandName().c_str() );

	if ( variableSearchResult == Variables().End() )
	{
		if ( commandLineParser.Arguments().size() == 1 )
		{
			//There's no existing variable with that name, so create one
			Variables().GetVariable ( ConsoleVariable(commandLineParser.CommandName().c_str(), 
														commandLineParser.Arguments()[0]));
			return true;
		}
		else
		{
			std::cerr << "Bad command" << std::endl;
			return false;
		}
	}

	if ( commandLineParser.Arguments().size ( ) == 1 )
	{
		//there is only one argument, assume assignment statement is meant
		if ( variableSearchResult->second->Set( commandLineParser.Arguments()[0] ) )
		{
			Out() << "Set " << variableSearchResult->second->Name() << " to " << *variableSearchResult->second << std::endl;	
		}
		else
		{
			Out() << "Not a valid value for " << variableSearchResult->second->Name() << std::endl;	
		}
	}
	else if ( commandLineParser.Arguments().size() == 0 )
	{
		//If there are no arguments display the value of the variable
		Out() << variableSearchResult->second->Name ( ) 
			<< " = " << *variableSearchResult->second << std::endl;		
	}

	return false;

}
//end Console::ExecuteString



