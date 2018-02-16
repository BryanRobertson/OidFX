//======================================================================================
//! @file         ConsoleCommandLineParser.h
//! @brief        Class responsible for interpreting a command line string
//!               
//!               The ConsoleCommandLineParser takes in a command line string
//!				  and converts it into a command name string, with arguments.
//!				  The parser is capable of interpreting boolean, integer, unsigned integer
//!				  floating point arguments, and string literals, enclosed in quotes ("") 
//!				  
//!               
//! @author       Bryan Robertson
//! @date         Friday, 11 March 2005
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

#ifndef CORE_CONSOLECOMMANDLINEPARSER_H
#define CORE_CONSOLECOMMANDLINEPARSER_H


#include <vector>
#include <boost/any.hpp>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{

	//! @brief        Class responsible for interpreting a command line string
	//!               
	//!               The ConsoleCommandLineParser takes in a command line string
	//!				  and converts it into a command name string, with arguments.
	//!				  The parser is capable of interpreting boolean, integer, unsigned integer
	//!				  floating point arguments, and string literals, enclosed in quotes ("") 
	class ConsoleCommandLineParser
	{
		public:
			ConsoleCommandLineParser ( const Char* input );

			//Indicates whether or not parsing succeeded
			bool Succeeded() { return m_succeeded; }

			//Accessors
			const std::string&			   CommandName() const	{ return m_commandName; }
			const std::vector<boost::any>& Arguments() const	{ return m_arguments;	}

		private:

			bool m_succeeded;
			std::string m_commandName;
			std::vector<boost::any> m_arguments;
	};

};
//end namespace Core


#endif
//#ifndef CONSOLECOMMANDLINEPARSER_H