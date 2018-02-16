//======================================================================================
//! @file         ConsoleCommandManager.cpp
//! @brief        Class to deal with registration, storage, and unregistering of
//!				  ConsoleCommand objects
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


#include <iostream>
#include <sstream>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/ConsoleCommand.h"
#include "Core/ConsoleCommandManager.h"
#include "Core/Hash.h"


using namespace Core;



//=========================================================================
//! @function    ConsoleCommandManager::ConsoleCommandManager
//! @brief       ConsoleCommandManager Constructor
//!              
//=========================================================================
ConsoleCommandManager::ConsoleCommandManager()
{
}
//end ConsoleCommandManager::ConsoleCommandManager



//=========================================================================
//! @function    ConsoleCommandManager::Register
//! @brief       Register a command with the console
//!
//!				 If a command is already registered with the same name
//!				 then the call will fail, and a ConsoleRegistrationError will be thrown
//!
//! @param		 command [in] Command to register with the console
//!
//! @throw		 ConsoleRegistrationError
//=========================================================================
void ConsoleCommandManager::Register( ConsoleCommand& command )
{
	//Make sure there isn't a command with that name registered already
	iterator existingCommand = m_commands.find(command.NameHash());

	if ( existingCommand != m_commands.end() )
	{
		std::stringstream str;
		str << "Error, couldn't register command " << command.Name() 
			<< ". Command already exists!" << std::endl;
		
		throw ConsoleRegistrationError( str.str().c_str(), command.NameHash(), __FILE__, __FUNCTION__, __LINE__);
	}

	m_commands[command.NameHash()] = &command;

}
//end ConsoleCommandManager::Register



//=========================================================================
//! @function    ConsoleCommandManager::UnregisterCommand
//! @brief       Remove a console command from the console
//!				 If no such command exists, then the call will fail and a
//!				 ConsoleRegistrationError will be thrown
//!
//! @param		 command [in] Command to be removed
//!
//! @throw		 ConsoleRegistrationError
//=========================================================================
void ConsoleCommandManager::Unregister( ConsoleCommand& command )
{
	//Find the command to remove
	iterator existingCommand = m_commands.find(command.NameHash());

	if ( existingCommand == m_commands.end() )
	{
		std::stringstream str;
		str << "Error: " << command.Name() << " no such command registered!" << std::endl;
		throw ConsoleRegistrationError( str.str().c_str(), command.NameHash(), __FILE__, __FUNCTION__, __LINE__);
	}

	m_commands.erase(existingCommand);
}
//end ConsoleCommandManager::UnregisterCommand



//=========================================================================
//! @function    ConsoleCommandManager::Find
//! @brief       Find a command by name
//!
//!				 If the command was found, then the returned iterator
//!				 references the command. Otherwise, the iterator is equal to End()
//!              
//! @param       commandName [in] Name of command to find
//!              
//! @return      An iterator to the command if found
//!				 End() otherwise
//=========================================================================
ConsoleCommandManager::iterator ConsoleCommandManager::Find ( const Char* commandName )
{
	UInt nameHash = GenerateHashFromString (commandName);

	return m_commands.find(nameHash);
}
//end ConsoleCommandManager::Find