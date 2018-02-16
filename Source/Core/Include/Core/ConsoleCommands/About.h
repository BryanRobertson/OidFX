//======================================================================================
//! @file         About.h
//! @brief        About class. Class providing an "about" command for the console
//!				  When it is called, the about command prints a short description of the program 
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

#ifndef CORE_CONCMDABOUT_H
#define CORE_CONCMDABOUT_H

//namespace ConsoleCommands
namespace ConsoleCommands
{

	//!@class	About
	//!@brief	About command for the console. 
	//!			
	//!			When called, prints a short description of the program to the standard output
	class About : public Core::ConsoleCommand
	{
		public:

			About ( const Char* desc )
				: m_desc(desc), ConsoleCommand("about")
			{
			}

			bool Execute ( const std::vector<boost::any>& arguments )
			{
				std::cout << m_desc;
				return true;
			}

		private:
			
			std::string m_desc;

	};
	//end class About

};
//end namespace ConsoleCommands

#endif
//#ifndef CORE_CONCMDABOUT_H