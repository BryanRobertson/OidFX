//======================================================================================
//! @file         CommandLine.h
//! @brief        Misc functions for processing command lines, etc
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 07 October 2004
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

#include <string>
#include <vector>
#include "Core/CommandLine.h"


namespace Core
{

//=========================================================================
//! @function    TokeniseCommandLine
//! @brief       Turn a command line string, into an array of command line tokens
//!              
//! @param       commandString [in] - Command line as a string
//! @param       commandLine   [out] - Array of strings holding tokens extracted
//!									   from the command line
//=========================================================================
void TokeniseCommandLine ( std::string commandString, std::vector<std::string>& commandLine )
{
	if ( commandString.empty ( ) )
	{
		return;
	}

	//First write the full command line string as the first entry of
	//the command line array
	commandLine.push_back(commandString);

	//Now tokenise the command line
	typedef std::string::iterator StringPos;

	//Beginning/End of current token
	//Prev points to the position one before the beginning of the
	//current token
	//Curr points to the position one after the end of the current
	//token
	std::string::iterator prev; 
	std::string::iterator curr;	

	//Set both pointers to position before beginning of stream
	prev = curr = commandString.begin() - 1;


	//Tokenise the string, stepping through it one character at a time
	for ( std::string::iterator itor = commandString.begin(); 
		  itor < commandString.end();
		  ++itor )
	{
		
		//Check if the current character is a space or if we have reached
		//the end of the string
		if ( (*itor == ' ') || (*itor == '\0') )
		{

			//Update the beginning and end pointers of current token
			prev = curr;
			curr = itor;

			//If the difference between the prev and curr pointers
			//is greater than one character, then the previous character was
			//not a space, and we have found the start of a new token
			if ( std::distance ( prev, curr ) > 1 )
			{
				//Add the new token to the array
				commandLine.push_back( std::string ( prev+1, curr ) );
			}

		}
	}

}//End TokeniseCommandLine


}
//end namespace Core
