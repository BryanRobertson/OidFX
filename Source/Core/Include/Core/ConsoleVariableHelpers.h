//======================================================================================
//! @file         ConsoleVariableHelpers.h
//! @brief        Classes to encapsulate the ConsoleVariable class for specific types
//!				  such as Float, Int, String               
//!               
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


#include <string>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include "Core/BasicTypes.h"
#include "Core/Console.h"
#include "Core/ConsoleVariableManager.h"
#include "Core/ConsoleVariable.h"



#ifndef CORE_CONSOLEVARIABLEHELPERS_H
#define CORE_CONSOLEVARIABLEHELPERS_H



//namespace Core
namespace Core
{

	//! Console variable storing a Float
	class ConsoleFloat
	{
		public:

			ConsoleFloat ( const Char* name, Float value );

			operator Float()				 
			{ 
				assert(m_variable);
				return m_variable->GetFloat(); 
			}

			Float operator = ( Float value )
			{
				assert(m_variable);
				m_variable->SetFloat(value);

				return value;
			}
	
			/*
			bool  operator == ( Float value )
			{ 
				return (m_variable->GetFloat() == value);		  
			}
			*/

		private:

			boost::shared_ptr<ConsoleVariable> m_variable;
			
	};
	//end class ConsoleFloat


	//! Console variable storing a Int
	class ConsoleInt
	{
		public:
			
			ConsoleInt ( const Char* name, Int value );

			operator Int()				 
			{ 
				assert(m_variable);
				return m_variable->GetInt(); 
			}

			Int operator = ( Int value )
			{
				assert(m_variable);
				m_variable->SetInt(value);

				return value;
			}

			/*
			bool  operator == ( Int value )
			{ 
				return (m_variable->GetInt() == value);		  
			}
			*/

		private:

			boost::shared_ptr<ConsoleVariable> m_variable;
			
	};
	//end class ConsoleInt


	//! Console variable storing a UInt
	class ConsoleUInt
	{
		public:

			ConsoleUInt ( const Char* name, UInt value );

			operator UInt()				 
			{ 
				assert(m_variable);
				return m_variable->GetUInt(); 
			}

			UInt operator = ( UInt value )
			{
				assert(m_variable);
				m_variable->SetUInt(value);

				return value;
			}

			/*
			bool  operator == ( UInt value )
			{ 
				return (m_variable->GetUInt() == value);		  
			}
			*/

		private:

			boost::shared_ptr<ConsoleVariable> m_variable;
			
	};
	//end class ConsoleUInt


	//! Console variable storing a bool
	class ConsoleBool
	{
		public:

			ConsoleBool ( const Char* name, bool value );

			operator bool()				 
			{ 
				assert(m_variable);
				return m_variable->GetBool(); 
			}

			bool operator = ( bool value )
			{
				assert(m_variable);
				m_variable->SetBool(value);

				return value;
			}

			/*
			bool operator == ( bool value )
			{ 
				return (m_variable->GetBool() == value);		  
			}
			*/

		private:

			boost::shared_ptr<ConsoleVariable> m_variable;
			
	};
	//end class Consolebool


	//! Console variable storing a String
	class ConsoleString
	{
		public:

			ConsoleString ( const Char* name, const std::string& value );
			ConsoleString ( const Char* name, const Char* value );

			operator const std::string&()				 
			{ 
				assert(m_variable);
				return m_variable->GetString(); 
			}

			const std::string& operator = ( const std::string& value )
			{
				assert(m_variable);
				m_variable->SetString(value);

				return value;
			}

			/*
			bool operator == ( const std::string& value )
			{ 
				return (m_variable->GetString() == value);		  
			}
			*/

		private:

			boost::shared_ptr<ConsoleVariable> m_variable;
			
	};
	//end class ConsoleString

};
//end namespace Core


#endif
//#ifndef CORE_CONSOLEVARIABLEHELPERS_H
