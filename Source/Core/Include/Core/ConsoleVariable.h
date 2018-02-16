//======================================================================================
//! @file         ConsoleVariable.h
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

#ifndef CORE_CONSOLEVARIABLE_H
#define CORE_CONSOLEVARIABLE_H

#include <iostream>
#include <boost/any.hpp>
#include <string>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{

	//!@class	ConsoleVariable
	//!@brief	Class representing a variable that can be changed from the console
	class ConsoleVariable
	{
		public:

			//Constructors/Destructor
			ConsoleVariable ( const Char* name, boost::any value );

			//Get type of the variable
			inline const type_info& Type() const;
			inline bool IsBool() const;
			inline bool IsInt() const;
			inline bool IsUInt() const;
			inline bool IsFloat() const;
			inline bool IsString() const;

			//Accessors
			inline const std::string& Name ( ) const;
			inline UInt NameHash ( ) const;

			inline Int	 GetInt() const;
			inline UInt	 GetUInt() const;
			inline bool	 GetBool() const;
			inline Float GetFloat() const;
			inline const std::string&  GetString() const;

			inline const boost::any& GetValue() const;

			//Mutators
			inline void	SetInt( Int value );
			inline void	SetUInt( UInt value );
			inline void	SetBool( bool value );
			inline void	SetFloat( Float value );
			inline void	SetString( const std::string& value );
			inline bool Set ( const boost::any& value );

			//
			friend inline std::ostream& operator << ( std::ostream& out, const ConsoleVariable& var );
			friend inline std::istream& operator >> ( std::istream& in, ConsoleVariable& var );

		private:

			//Private data
			UInt		m_nameHash;
			std::string m_name;
			boost::any  m_value;
	};
	//end class ConsoleVariable


    //=========================================================================
    //! @function    ConsoleVariable::Type
    //! @return      Return the type of the variable
    //=========================================================================
	const type_info& ConsoleVariable::Type() const
	{
		return m_value.type();
	}
	//end ConsoleVariable::Type


	//=========================================================================
    //! @function    ConsoleVariable::IsBool
    //! @return      Return true if the variable is of type bool, false otherwise
    //=========================================================================
	bool ConsoleVariable::IsBool() const
	{
		return (m_value.type() == typeid(bool));
	}
	//end ConsoleVariable::IsBool


	//=========================================================================
    //! @function    ConsoleVariable::IsInt
    //! @return      Return true if the variable is of type Int, false otherwise
    //=========================================================================
	bool ConsoleVariable::IsInt() const
	{
		return m_value.type() == typeid(Int);
	}
	//end ConsoleVariable::IsInt


	//=========================================================================
    //! @function    ConsoleVariable::IsUInt
    //! @return      Return true if the variable is of type UInt, false otherwise
    //=========================================================================
	bool ConsoleVariable::IsUInt() const
	{
		return m_value.type() == typeid(UInt);
	}
	//end ConsoleVariable::IsUInt


	//=========================================================================
    //! @function    ConsoleVariable::IsFloat
    //! @return      Return true if the variable is of type Float, false otherwise
    //=========================================================================
	bool ConsoleVariable::IsFloat() const
	{
		return m_value.type() == typeid(Float);
	}
	//end ConsoleVariable::IsFloat


	//=========================================================================
    //! @function    ConsoleVariable::IsString
    //! @return      Return true if the variable is of type std:string, false otherwise
    //=========================================================================
	bool ConsoleVariable::IsString() const
	{
		return (m_value.type() == typeid(std::string));
	}
	//end ConsoleVariable::IsString


	//=========================================================================
    //! @function    ConsoleVariable::Name
    //! @return      Return the name of the variable
    //=========================================================================
	const std::string& ConsoleVariable::Name() const
	{
		return m_name;
	}
	//end ConsoleVariable::Name


	//=========================================================================
    //! @function    ConsoleVariable::NameHash
    //! @return      Return the unique hash value generated from the variable's name
    //=========================================================================
	UInt ConsoleVariable::NameHash() const
	{
		return m_nameHash;
	}
	//end ConsoleVariable::NameHash


	//=========================================================================
    //! @function    ConsoleVariable::GetInt
    //! @return      Return the value of the variable as an integer
    //=========================================================================
	Int ConsoleVariable::GetInt() const
	{
		return boost::any_cast<Int>(m_value);
	}
	//End ConsoleVariable::GetInt()


	//=========================================================================
    //! @function    ConsoleVariable::GetUInt
    //! @return      Return the value of the variable as an unsigned integer
    //=========================================================================
	UInt ConsoleVariable::GetUInt() const
	{
		return boost::any_cast<UInt>(m_value);
	}
	//end ConsoleVariable::GetUInt


	//=========================================================================
    //! @function    ConsoleVariable::GetBool
    //! @return      Return the value of the variable as a bool
    //=========================================================================
	bool ConsoleVariable::GetBool() const
	{
		return boost::any_cast<bool>(m_value);
	}
	//end ConsoleVariable::GetBool


	//=========================================================================
    //! @function    ConsoleVariable::GetFloat
    //! @return      Return the value of the variable as a Float
    //=========================================================================
	Float ConsoleVariable::GetFloat() const
	{
		return boost::any_cast<Float>(m_value);
	}
	//end ConsoleVariable::GetFloat


	//=========================================================================
    //! @function    ConsoleVariable::GetString
    //! @return      Return the value of the variable as a string
    //=========================================================================
	const std::string& ConsoleVariable::GetString() const
	{
		return *boost::any_cast<std::string>(&m_value);
	}
	//end ConsoleVariable::GetString



    //=========================================================================
    //! @function    ConsoleVariable::GetValue
    //! @return      Return the value of the variable's internal variant type
    //=========================================================================
	const boost::any& ConsoleVariable::GetValue() const
	{
		return m_value;
	}
	//end ConsoleVariable::GetValue


	//=========================================================================
    //! @function    ConsoleVariable::SetInt
    //! @return      Set the value of the variable to an integer
    //=========================================================================
	void ConsoleVariable::SetInt( Int value )
	{
		m_value = value;
	}
	//end ConsoleVariable::SetInt


	//=========================================================================
    //! @function    ConsoleVariable::SetUInt
    //! @return      Return the value of the variable as an unsigned integer
    //=========================================================================
	void ConsoleVariable::SetUInt( UInt value )
	{
		m_value = value;
	}
	//end ConsoleVariable::SetUInt


	//=========================================================================
    //! @function    ConsoleVariable::SetBool
    //! @return      Return the value of the variable as a boolean value
    //=========================================================================
	void ConsoleVariable::SetBool( bool value )
	{
		m_value = value;
	}
	//end ConsoleVariable::SetBool


	//=========================================================================
    //! @function    ConsoleVariable::SetFloat
    //! @return      Return the value of the variable as a float
    //=========================================================================
	void ConsoleVariable::SetFloat( Float value )
	{
		m_value = value;
	}
	//end ConsoleVariable::SetFloat


	//=========================================================================
    //! @function    ConsoleVariable::SetString
    //! @return      Return the value of the variable as a string
    //=========================================================================
	void ConsoleVariable::SetString( const std::string& value )
	{
		std::string* valueAsString = boost::any_cast<std::string*>(m_value);
		*valueAsString = value;
	}
	//end ConsoleVariable::SetString


    //=========================================================================
    //! @function    ConsoleVariable::Set
    //! @brief       
    //!              
    //!              
    //! @param       value	[in] Value to set 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	bool ConsoleVariable::Set ( const boost::any& value )
	{
		if ( m_value.empty() )
		{
			m_value = value;
			return true;
		}

		//Boolean
		if ( (m_value.type() == typeid(bool)) )
		{
			if (value.type() == typeid(bool))
			{
				m_value = value;
				return true;
			}
			else
			{
				return false;
			}
		}

		//Float
		if (m_value.type() == typeid(Float))
		{
			if (value.type() == typeid(Float))
			{
				m_value = value;
				return true;
			}
			else if (value.type() == typeid(UInt))
			{
				m_value = static_cast<Float>( boost::any_cast<UInt>(value) );
				return true;
			}
			else if (value.type() == typeid(Int))
			{
				m_value = static_cast<Float>( boost::any_cast<Int>(value) );
				return true;
			}
			else
			{
				return false;
			}
		}

		if (m_value.type() == typeid(Int))
		{
			if (value.type() == typeid(Float))
			{
				m_value = static_cast<Int>( boost::any_cast<Float>(value) );
				return true;
			}
			else if (value.type() == typeid(UInt))
			{
				m_value = static_cast<Int>( boost::any_cast<UInt>(value) );
				return true;
			}
			else if (value.type() == typeid(Int))
			{
				m_value = value;
				return true;
			}
			else
			{
				return false;
			}
		}

		if (m_value.type() == typeid(UInt))
		{
			if (value.type() == typeid(Float))
			{
				Float newVal = boost::any_cast<Float>(value);

				//Don't allow assignment of a negative float to a UInt
				if ( newVal < 0.0f )
				{
					return false;
				}

				m_value = static_cast<UInt>( newVal );
				return true;
			}
			else if (value.type() == typeid(UInt))
			{
				m_value = value;
				return true;
			}
			else if (value.type() == typeid(Int))
			{
				Int newVal = boost::any_cast<Int>(value);

				//Don't allow assignment of a negative value to a UInt
				if ( newVal < 0 )
				{
					return false;
				}

				m_value = static_cast<UInt>(newVal);
				return true;
			}
			else
			{
				return false;
			}
		}

		if ( m_value.type() == typeid(std::string) )
		{
			if ( value.type() == typeid(std::string) )
			{
				m_value = value;
				return true;
			}
			else
			{
				return false;
			}
		}

		debug_error ( "Shouldn't get here!!" );
		return false;
	}
	//end ConsoleVariable::Set


	//=========================================================================
    //! @function    operator << ( ostream, ConsoleVariable )
    //! @return      Write the variable to an ostream
    //=========================================================================
	std::ostream& operator << ( std::ostream& out, const ConsoleVariable& var )
	{
		if ( var.IsBool() )
		{
			out << (var.GetBool() ? "true" : "false");
		}
		
		if ( var.IsInt() )
		{
			out << var.GetInt();
		}

		if ( var.IsUInt() )
		{
			out << var.GetUInt();
		}

		if ( var.IsFloat() )
		{
			out << var.GetFloat();
		}

		if ( var.IsString() )
		{
			out << var.GetString();
		}

		return out;
	}
	//end operator << ( ostream, ConsoleVariable )


	//=========================================================================
    //! @function    operator << ( ostream, ConsoleVariable )
    //! @return      Read the variable from an istream
    //=========================================================================
	std::istream& operator >> ( std::istream& in, ConsoleVariable& var )
	{
		if ( var.IsBool() )
		{
			bool temp;
			in >> temp;
			var.SetBool ( temp );
		}
		
		if ( var.IsInt() )
		{
			Int temp;
			in >> temp;
			var.SetInt ( temp );
		}

		if ( var.IsUInt() )
		{
			UInt temp;
			in >> temp;
			var.SetUInt ( temp );
		}

		if ( var.IsFloat() )
		{
			Float temp;
			in >> temp;
			var.SetFloat ( temp );
		}

		if ( var.IsString() )
		{
			std::string temp;
			in >> temp;
			var.SetString ( temp );
		}

		return in;
	}
	//end operator >> ( istream, ConsoleVariable )

};
//end namespace Core

#endif
//#ifndef CORE_CONSOLEVARIABLE_H