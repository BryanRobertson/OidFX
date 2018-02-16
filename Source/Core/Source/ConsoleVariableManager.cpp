//======================================================================================
//! @file         ConsoleVariableManager.cpp
//! @brief        Class that stores and provides access to console variables
//!               
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
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/ConsoleVariable.h"
#include "Core/ConsoleVariableManager.h"
#include "Core/Hash.h"


using namespace Core;


//=========================================================================
//! @function    ConsoleVariableManager::ConsoleVariableManager
//! @brief       ConsoleVariableManager constructor
//=========================================================================
ConsoleVariableManager::ConsoleVariableManager()
{
}
//end ConsoleVariableManager::ConsoleVariableManager



//=========================================================================
//! @function    ConsoleVariableManager::GetVariable
//! @brief       Get a pointer to a console variable, setting optional flags
//!				 on the variable, if it doesn't exist, and has to be created.
//!
//!
//!				 Currently this is identical to the other version of GetVariable.
//!				 If the console variable already exists, and has a value compatible
//!				 with variable, then the existing console variable is returned. 
//!				 If the variable already exists, but isn't a compatible type, (if the existing variable
//!				 is a string, and we're trying to add a float for example) then the existing variable
//!				 will be set to the value of variable.
//!
//!				 If no variable exists with a name matching that of variable, then a copy of
//!				 variable will be added as a new console variable
//!
//! @param		 variable [in] Variable to register
//! @param		 flags	  [in] Currently unused, set to zero. The purpose of this variable, is to allow
//!								future implementations to set variables as readonly, or to have other attributes
//=========================================================================
boost::shared_ptr<ConsoleVariable> ConsoleVariableManager::GetVariable( ConsoleVariable& variable, std::bitset<sizeof(Int)> flags )
{
	//Make sure there isn't a variable with that name registered already
	iterator existingVar = m_variables.find(variable.NameHash());

	if ( existingVar != m_variables.end() )
	{
		//Attempt to set the contents of variable to the contents of the existing variable.
		//If the types are incompatible, then this will fail, and the existing variable
		//will remain unchanged
		if ( variable.Set( existingVar->second->GetValue() ) == false )
		{
			std::cerr << __FUNCTION__ "Clobbering existing value of console variable " << variable.Name() << std::endl;
		}
		
		//Set the existing variable to variable.
		*(existingVar->second) = ConsoleVariable( variable );

		//std::cout << existingVar->second->Type().name() << std::endl;

		return existingVar->second;
	}
	else
	{
		return m_variables[variable.NameHash()] 
									= boost::shared_ptr<ConsoleVariable> (new ConsoleVariable(variable));
	}

}
//end ConsoleVariableManager::GetVariable


//=========================================================================
//! @function    ConsoleVariableManager::Find
//! @brief       Find a variable by name
//!
//!				 If the variable was found, then the returned iterator
//!				 references the variable. Otherwise, the iterator is equal to End()
//!              
//! @param       variableName [in] Name of variable to find
//!              
//! @return      An iterator to the variable if found
//!				 End() otherwise
//=========================================================================
ConsoleVariableManager::iterator ConsoleVariableManager::Find ( const Char* commandName )
{
	UInt nameHash = GenerateHashFromString (commandName);

	return m_variables.find(nameHash);
}
//end ConsoleVariableManager::Find