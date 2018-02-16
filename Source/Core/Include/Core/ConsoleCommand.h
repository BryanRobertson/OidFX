//======================================================================================
//! @file         ConsoleCommand.h
//! @brief        Base class for a command that can be executed from a Console command line
//!
//!				  Handles registration of the command with the console, and provides
//!				  an interface for the command to be called from the console
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

#ifndef CORE_CONSOLECOMMAND_H
#define CORECONSOLECOMMAND_H

#include <vector>
#include <string>
#include <boost/any.hpp>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{

	class Console;

	//!@class	ConsoleCommand
	//!@brief	 Base class for a command that can be executed from a Console command line
	//!
	//!			 Handles registration of the command with the console, and provides
	//!			 an interface for the command to be called from the console
	//!          class ConsoleCommand
	class ConsoleCommand
	{
		public:

			//Constructors/Destructor
			ConsoleCommand( const Char* name );
			virtual ~ConsoleCommand ();

			//Execute the command
			virtual bool Execute ( const std::vector<boost::any>& arguments ) = 0;

			//Accessors
			const std::string& Name() const { return m_name;	 }
			UInt NameHash() const			{ return m_nameHash; }

			//Unregister the command
			void Unregister();

		protected:

			//Protected methods
			void Register();
			

			//Protected data
			std::string m_name;		//!< Name of the command
			UInt		m_nameHash; //!< Unique hash generated from the name
	};
	//end class ConsoleCommand

};
//end namespace Core


#endif
//#ifndef CORE_CONSOLECOMMAND_H