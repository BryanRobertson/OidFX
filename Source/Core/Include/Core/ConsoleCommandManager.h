//======================================================================================
//! @file         ConsoleCommandManager.h
//! @brief        Class to deal with registration, storage, and unregistering of
//!				  ConsoleCommand objects
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

#ifndef CORE_CONSOLECOMMANDMANAGER_H
#define CORE_CONSOLECOMMANDMANAGER_H

#include <map>
#include <bitset>
#include <boost/shared_ptr.hpp>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/StandardExceptions.h"



//namespace Core
namespace Core
{


	//!@class	ConsoleRegistrationError
	//!@brief	Exception thrown when a call to Register or Unregister fails
	class ConsoleRegistrationError : public RuntimeError
	{
		public:
			
			ConsoleRegistrationError ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: RuntimeError ( what, errorCode, file, function, line )
			{
			}
	};
	//end ConsoleRegistrationError



	//!@class	ConsoleCommandManager
	//!@brief	Class to deal with registration, storage and unregistering of
	//!			ConsoleCommand objects
	class ConsoleCommandManager
	{
		public:

			ConsoleCommandManager ();

			//Public types
			typedef std::map<UInt,ConsoleCommand*> ConCmdStore;
			typedef ConCmdStore::const_iterator const_iterator;
			typedef ConCmdStore::iterator		iterator;
			
			//Register/Unregister console commands
			void Register   ( ConsoleCommand& command );
			void Unregister ( ConsoleCommand& command );

			//Iterator access to the commands
			inline iterator Begin();
			inline iterator End();

			//Const iterator access to the commands
			inline const_iterator Begin() const;
			inline const_iterator End() const;

			iterator Find( const Char* commandName );

		private:

			ConCmdStore m_commands;

	};
	//end class ConsoleCommandManager


	//=========================================================================
    //! @function    ConsoleCommandManager::Begin
    //! @brief       Return an iterator to the beginning of the Command sequence
    //!             
    //! @return      Return an iterator to the beginning of the Command sequence
    //=========================================================================
	ConsoleCommandManager::iterator ConsoleCommandManager::Begin()
	{ 
		return m_commands.begin(); 
	}
	//end ConsoleCommandManager::Begin


	//=========================================================================
    //! @function    ConsoleCommandManager::End
    //! @brief       Return an iterator one past the end of the Command sequence
    //!             
    //! @return      Return an iterator one past the end of the Command sequence
    //=========================================================================
	ConsoleCommandManager::iterator ConsoleCommandManager::End()
	{ 
		return m_commands.end();   
	}
	//end ConsoleCommandManager::End


    //=========================================================================
    //! @function    ConsoleCommandManager::Begin
    //! @brief       Return a const_iterator to the beginning of the Command sequence
    //!             
    //! @return      Return a const_iterator to the beginning of the Command sequence
    //=========================================================================
	ConsoleCommandManager::const_iterator ConsoleCommandManager::Begin() const
	{
		return m_commands.begin(); 
	}
	//end ConsoleCommandManager::Begin


	//=========================================================================
    //! @function    ConsoleCommandManager::End
    //! @brief       Return a const_iterator one past the end of the Command sequence
    //!             
    //! @return      Return a const_iterator one past the end of the Command sequence
    //=========================================================================
	ConsoleCommandManager::const_iterator ConsoleCommandManager::End() const
	{
		return m_commands.end();   
	}
	//end ConsoleCommandManager::End



};
//end namespace Core


#endif
//#ifndef CONSOLECOMMANDMANAGER_H