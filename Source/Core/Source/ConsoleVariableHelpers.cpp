//======================================================================================
//! @file         ConsoleVariableHelpers.h
//! @brief        Classes to encapsulate the ConsoleVariable class for specific types
//!				  such as Float, Int, String               
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
#include "Core/ConsoleVariableHelpers.h"


using namespace Core;



//=========================================================================
//! @function    ConsoleFloat::ConsoleFloat
//! @brief       Initialize a float console variable
//!               
//! @param       name  [in] Name to give the variable
//! @param       value [in] Value to give the variable
//!              
//! @see		 ConsoleVariable::ConsoleVariable
//! @return      
//! @throw       
//=========================================================================
ConsoleFloat::ConsoleFloat ( const Char* name, Float value )
{
	m_variable = Console::GetSingleton().Variables().GetVariable(ConsoleVariable(name, value));
}
//end ConsoleFloat::ConsoleFloat



//=========================================================================
//! @function    ConsoleInt::ConsoleInt
//! @brief       Initialize a Int console variable
//!               
//! @param       name  [in] Name to give the variable
//! @param       value [in] Value to give the variable
//!              
//! @see		 ConsoleVariable::ConsoleVariable
//! @return      
//! @throw       
//=========================================================================
ConsoleInt::ConsoleInt ( const Char* name, Int value )
{
	m_variable = Console::GetSingleton().Variables().GetVariable(ConsoleVariable(name, value));
}
//end ConsoleInt::ConsoleInt



//=========================================================================
//! @function    ConsoleUInt::ConsoleUInt
//! @brief       Initialize a UInt console variable
//!               
//! @param       name  [in] Name to give the variable
//! @param       value [in] Value to give the variable
//!              
//! @see		 ConsoleVariable::ConsoleVariable
//! @return      
//! @throw       
//=========================================================================
ConsoleUInt::ConsoleUInt ( const Char* name, UInt value )
{
	m_variable = Console::GetSingleton().Variables().GetVariable(ConsoleVariable(name, value));
}
//end ConsoleUInt::ConsoleUInt



//=========================================================================
//! @function    ConsoleBool::ConsoleBool
//! @brief       Initialize a Bool console variable
//!               
//! @param       name  [in] Name to give the variable
//! @param       value [in] Value to give the variable
//!              
//! @see		 ConsoleVariable::ConsoleVariable
//! @return      
//! @throw       
//=========================================================================
ConsoleBool::ConsoleBool ( const Char* name, bool value )
{
	m_variable = Console::GetSingleton().Variables().GetVariable(ConsoleVariable(name, value));
}
//end ConsoleBool::ConsoleBool



//=========================================================================
//! @function    ConsoleString::ConsoleString
//! @brief       Initialize a String console variable
//!               
//! @param       name  [in] Name to give the variable
//! @param       value [in] Value to give the variable
//!              
//! @see		 ConsoleVariable::ConsoleVariable
//! @return      
//! @throw       
//=========================================================================
ConsoleString::ConsoleString ( const Char* name, const std::string& value )
{
	m_variable = Console::GetSingleton().Variables().GetVariable( ConsoleVariable (name, std::string(value)) );
}
//end ConsoleString::ConsoleString



//=========================================================================
//! @function    ConsoleString::ConsoleString
//! @brief       Initialize a String console variable
//!               
//! @param       name  [in] Name to give the variable
//! @param       value [in] Value to give the variable
//!              
//! @see		 ConsoleVariable::ConsoleVariable
//! @return      
//! @throw       
//=========================================================================
ConsoleString::ConsoleString ( const Char* name, const Char* value )
{
	debug_assert ( value, "Attempted to initialize ConsoleString with null character pointer!" );
	m_variable = Console::GetSingleton().Variables().GetVariable( ConsoleVariable (name, std::string(value)) );
}
//end ConsoleString::ConsoleString