//======================================================================================
//! @file         Exec.h
//! @brief        Exec class. Class providing a "exec" command for the console
//!				  When it is called, the exec command executes the contents of an external file
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 13 March 2005
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

#ifndef CORE_CONCMDEXEC_H
#define CORE_CONCMDEXEC_H


#include <fstream>


//namespace ConsoleCommands
namespace ConsoleCommands
{

	//!@class	Exec
	//!@brief	Class providing a "exec" command for the console
	//!			When it is called, the exec command executes the contents of an external file
	class Exec : public Core::ConsoleCommand
	{
		public:

			Exec ()
				: ConsoleCommand("exec")
			{
			}

			bool Execute ( const std::vector<boost::any>& arguments )
			{				
				if ( (arguments.empty()) || 
					 (arguments[0].type() != typeid(std::string)) )
				{
					std::cout << "exec: Execute a file containing console commands" << std::endl
							  << "\tUsage: exec <filename>" << std::endl
							  << "\twhere filename is the name of the file to be executed." << std::endl
							  << "\tFilenames containing spaces should be enclosed in quotes" << std::endl;
					return false;
				}

				//boost::any_cast<std::string> actually returns std::string* if you
				//use the address of the any, instead of passing it by reference
				//
				//Wow, that sure is intuitive...
				const std::string* fileName = boost::any_cast<std::string>(&arguments[0]);

				std::cout << "Executing " << *fileName << std::endl << std::endl;

				std::ifstream file ( fileName->c_str() );

				if ( file.fail() )
				{
					std::cerr << "exec: Error, file " << fileName->c_str() << " not found!" << std::endl;
				}

				std::string line;
				UInt lineCount = 0;

				while ( !file.fail() && !file.eof() )
				{
					std::getline ( file, line );
					Core::Console::GetSingleton().ExecuteString ( line );
					++lineCount;
				}

				std::cout << std::endl << lineCount << " lines executed" << std::endl << std::endl;
				

				return true;
			}

		private:
	};
	//end class Quit

};
//end namespace ConsoleCommands

#endif
//#ifndef CORE_CONCMDEXEC_H