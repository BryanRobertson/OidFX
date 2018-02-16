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

#ifndef CORE_COMMANDLINE_H
#define CORE_COMMANDLINE_H

#include <string>
#include <vector>

//namespace Core
namespace Core
{

	void TokeniseCommandLine ( std::string commandString, std::vector<std::string>& commandLine );

};
//end namespace Core

#endif
//#ifndef CORE_COMMANDLINE_H
