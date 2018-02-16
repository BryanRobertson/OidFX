//======================================================================================
//! @file         ConsoleCommand.cpp
//! @brief        Base class for a command that can be executed from a Console command line
//!
//!				  Handles registration of the command with the console, and provides
//!				  an interface for the command to be called from the console
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

#include <iostream>
#include "Core/BasicTypes.h"
#include "Core/Hash.h"
#include "Core/ToLower.h"
#include "Core/Console.h"
#include "Core/ConsoleCommand.h"
#include "Core/ConsoleCommandManager.h"


using namespace Core;



//=========================================================================
//! @function    ConsoleCommand::ConsoleCommand
//! @brief       ConsoleCommand constructor: Automatically registers
//!				 the variable with the console
//!
//! @param		 name		[in] Name of console command. Valid names consist
//!								 of any letter, followed by a series of numbers, letters or the 
//!								 underscore '_' character. Case does not matter, as all command names
//!								 are converted to lower case before registration
//!
//! @throw		 ConsoleRegistrationError
//=========================================================================
ConsoleCommand::ConsoleCommand ( const Char* name )
: m_name (name)
{
	//Convert the name to lower case
	std::for_each( m_name.begin(), m_name.end(), ToLowerFunc() );

	m_nameHash = GenerateHashFromString ( name );
	Register();
}
//End ConsoleCommand::ConsoleCommand



//=========================================================================
//! @function    ConsoleCommand::~ConsoleCommand
//! @brief       ConsoleCommand destructor: Automatically unregisters
//!				 the variable from the console
//!				 Throws a ConsoleRegistrationError if the command wasn't registered
//!
//! @throw		 ConsoleRegistrationError
//=========================================================================
ConsoleCommand::~ConsoleCommand ( )
{
	Unregister();
}
//End ConsoleCommand::~ConsoleCommand



//=========================================================================
//! @function    ConsoleCommand::Register
//! @brief       Register the command with the console
//!
//! @throw		 ConsoleRegistrationError
//=========================================================================
void ConsoleCommand::Register ( )
{
	Console::GetSingleton().Commands().Register(*this);
}
//end ConsoleCommand::Register



//=========================================================================
//! @function    ConsoleCommand::Unregister
//! @brief       Unregister the command from the console
//!
//! @throw		 ConsoleRegistrationError
//=========================================================================
void ConsoleCommand::Unregister ( )
{
	Console::GetSingleton().Commands().Unregister(*this);	
}
//end ConsoleCommand::Unregister