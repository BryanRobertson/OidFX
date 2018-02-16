//======================================================================================
//! @file         ConCvarList.h
//! @brief        ConCvarList class. Class providing a "cvarlist" command for the console
//!				  When it is called, it prints a list of all variables registered with the console
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

#ifndef CORE_CONCVARIST_H
#define CORE_CONCVARIST_H

//namespace ConsoleCommands
namespace ConsoleCommands
{

	//!@class	CvarList
	//!@brief	cmdlist command for the console. Prints a list of all commands
	class CvarList : public Core::ConsoleCommand
	{
		public:

			CvarList ()
				: ConsoleCommand("cvarlist")
			{
			}

			bool Execute ( const std::vector<boost::any>& arguments )
			{
				using Core::Console;

				std::cout << std::endl 
						  << "List of all variables registered:" << std::endl
						  << "=================================" << std::endl;						 

				UInt variableCount = 0;

				Core::ConsoleVariableManager::const_iterator current = Console::GetSingleton().Variables().Begin();
				Core::ConsoleVariableManager::const_iterator end = Console::GetSingleton().Variables().End();

				for ( ; current != end; ++current )
				{
					++variableCount;
					std::cout << current->second->Name() << "   \t\t" << *current->second << std::endl;
				}

				std::cout << std::endl;

				return true;
			}
	};
	//end class CvarList

};
//end namespace ConsoleCommands

#endif
//#ifndef CORE_CONCVARIST_H