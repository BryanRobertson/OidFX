//======================================================================================
//! @file         Debug.cpp
//! @brief        Core library debug services
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 20 May 2005
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
#include <windows.h>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"

using namespace Core;



//=========================================================================
//! @function    DisplayUnimplementedMessage
//! @brief       Display a message to indicate that a piece of code
//!				 hasn't been implemented yet
//!              
//! @param		 function	[in] Function that the message refers to
//! @param       sourceFile [in] Source file in which the unimplemented function
//!								 resides
//! @param		 line		[in] Line of code that triggered this message
//!              
//=========================================================================
void Core::DisplayUnimplementedMessage ( const Char* function, const Char* sourceFile, UInt line )
{

	std::stringstream errorMessage;	
	errorMessage << "This function has not been implemented yet!\n\n"; 

	if ( function )
	{
		errorMessage << "Function: " << function << "\n\n";
	}

	if ( sourceFile )
	{
		errorMessage << "Source File:\n" << sourceFile << "\n\nLine:" << line << "\n\n";
	}

	std::cerr << errorMessage.str().c_str() << std::endl;
	MessageBox ( 0, errorMessage.str().c_str(), "Not implemented yet", MB_OK | MB_ICONSTOP );
}
//End DisplayUnimplementedMessage



//=========================================================================
//! @function    DisplayError
//! @brief       Display a message box with an error message
//!              
//! @param		 message	[in]
//!              
//=========================================================================
void Core::DisplayError ( const Char* message, const Char* title )
{
	if ( message && title )
	{
		MessageBox ( 0, message, title, MB_OK | MB_ICONERROR );
	}
}
//End Core::DisplayError



//=========================================================================
//! @function    DisplayAssertError
//! @brief       Display an assert message
//!              
//!              
//! @param       condition		[in] Condition that triggered the assert, copied
//!									 using the debug_assert macro
//! @param       outputMessage	[in] Message to be displayed along with the assert
//!              
//! @return      EA_IGNORE if the user chose ignore
//!				 EA_ABORT if the user chose abort
//!					
//! @throw       
//=========================================================================
Core::ERROR_RESULT Core::DisplayAssertError ( const Char* condition, const Char* outputMessage,
								  const Char* function, const Char* sourceFile, UInt line )
{
	std::stringstream str;
	
	str << "The following assertion failed!\n\n"; 

	if ( condition )
	{
		str << "Error:\n     \"" << condition << "\"\n\n";
	}

	if ( outputMessage )
	{
		str << "Error Message:\n      " << outputMessage << "\n\n";
	}

	if ( function )
	{
		str << "Function:\n      " << function << "\n\n";
	}

	if ( sourceFile )
	{
		str << "File:\n     " << sourceFile << "\n\nLine:\n     " << line << "\n\n";
	}

	std::cerr << "==============================================\n"
			  << "Assert failed!\n\n"
			  << str.str() << "\n"
			  << "==============================================\n" << std::endl;

	str << "Press Abort to exit, Retry to debug, Ignore to ignore this assert in future" << std::endl; 

	Int result = MessageBox( 0, str.str().c_str(), "Assert Failed!", MB_ABORTRETRYIGNORE | MB_ICONSTOP  ); 

	if ( result == IDABORT )
	{
		return _ERROR_ABORT;
	}
	else if ( result == IDRETRY )
	{
		return _ERROR_RETRY;
	}
	else
	{
		return _ERROR_IGNORE;
	}

}
//end DisplayAssertError