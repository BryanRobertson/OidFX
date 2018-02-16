//======================================================================================
//! @file         ConsoleVariable.cpp
//! @brief        Class representing a variable that can be changed from the console
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 10 March 2005
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
#include <fstream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include "Core/BasicTypes.h"
#include "Core/Hash.h"
#include "Core/ToLower.h"
#include "Core/Console.h"
#include "Core/ConsoleVariable.h"


using namespace Core;



//=========================================================================
//! @function    ConsoleVariable::ConsoleVariable
//! @brief       Convert the name to lower cases and generates a hash for it
//!              
//!              
//! @param       console [in]	Pointer to the console
//! @param       name	 [in]	Name for the variable
//! @param       value	 [in]	Value to assign to the variable
//!              
//=========================================================================
ConsoleVariable::ConsoleVariable ( const Char* name, boost::any value )
: m_name(name)
{
	//Convert the variable to lower case
	std::for_each(m_name.begin(), m_name.end(), ToLowerFunc() );

	//Generate a hash from the string
	m_nameHash = GenerateHashFromString ( m_name.c_str() );

	//Set the value of the variable
	Set (value);
}
//end ConsoleVariable::Constructor