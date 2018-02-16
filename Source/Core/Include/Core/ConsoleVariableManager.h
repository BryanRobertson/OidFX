//======================================================================================
//! @file         ConsoleVariableManager.h
//! @brief        Class that stores and provides access to console variables
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

#ifndef CORE_CONSOLEVARIABLEMANAGER_H
#define CORE_CONSOLEVARIABLEMANAGER_H

#include <map>
#include <bitset>
#include <boost/shared_ptr.hpp>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{

	//!@class	ConsoleVariableManager
	//!@brief	Class that stores and provides access to console variables
	class ConsoleVariableManager
	{
		public:

			ConsoleVariableManager ();

			//Public types
			typedef std::map<UInt,boost::shared_ptr<ConsoleVariable> > ConVarStore;
			typedef ConVarStore::const_iterator const_iterator;
			typedef ConVarStore::iterator		iterator;
			
			enum FlagIndices
			{
				READONLY = 0	
			};

			//Get a pointer to a console variable
			boost::shared_ptr<ConsoleVariable> GetVariable ( ConsoleVariable& defaultValue, std::bitset<sizeof(Int)> flags = std::bitset<sizeof(Int)>(0) );

			//Iterator access to the variables
			inline iterator Begin();  
			inline iterator End(); 

			//Const iterator access to the variables
			inline const_iterator Begin() const;
			inline const_iterator End() const;

			iterator Find( const Char* variableName );

		private:
			
			ConVarStore m_variables;

	};
	//end class ConsoleVariableManager


    //=========================================================================
    //! @function    ConsoleVariableManager::Begin
    //! @brief       Return an iterator to the beginning of the variable sequence
    //!             
    //! @return      Return an iterator to the beginning of the variable sequence
    //=========================================================================
	ConsoleVariableManager::iterator ConsoleVariableManager::Begin()
	{ 
		return m_variables.begin(); 
	}
	//end ConsoleVariableManager::Begin


	//=========================================================================
    //! @function    ConsoleVariableManager::End
    //! @brief       Return an iterator one past the end of the variable sequence
    //!             
    //! @return      Return an iterator one past the end of the variable sequence
    //=========================================================================
	ConsoleVariableManager::iterator ConsoleVariableManager::End()
	{ 
		return m_variables.end();   
	}
	//end ConsoleVariableManager::End


    //=========================================================================
    //! @function    ConsoleVariableManager::Begin
    //! @brief       Return a const_iterator to the beginning of the variable sequence
    //!             
    //! @return      Return a const_iterator to the beginning of the variable sequence
    //=========================================================================
	ConsoleVariableManager::const_iterator ConsoleVariableManager::Begin() const
	{
		return m_variables.begin(); 
	}
	//end ConsoleVariableManager::Begin


	//=========================================================================
    //! @function    ConsoleVariableManager::End
    //! @brief       Return a const_iterator one past the end of the variable sequence
    //!             
    //! @return      Return a const_iterator one past the end of the variable sequence
    //=========================================================================
	ConsoleVariableManager::const_iterator ConsoleVariableManager::End() const
	{
		return m_variables.end();   
	}
	//end ConsoleVariableManager::End


};
//end namespace Core


#endif
//#ifndef CORE_CONSOLEVARIABLEMANAGER_H