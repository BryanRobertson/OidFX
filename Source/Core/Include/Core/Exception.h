//======================================================================================
//! @file         Exception.h
//! @brief        Replacement for std::exception, providing more information,
//!				  such as file, line, and error code of the error
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 14 January 2005
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

#ifndef CORE_EXCEPTION_H
#define CORE_EXCEPTION_H


#include <string>
#include <iostream>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{

	//! @class	Exception
	class Exception
	{
		public:

			inline Exception ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
								const Char* function = "Unknown", const UInt line = 0) throw ( );

			inline Exception ( const Exception& right );

			virtual ~Exception () {}

			virtual inline Exception& operator= ( const Exception& right );

			virtual const Char* What ( ) const throw ( )			{ return m_what.c_str();		}
			virtual const Char* File ( ) const throw ( )			{ return m_file.c_str();		}
			virtual const Char* Function ( ) const throw ( )		{ return m_function.c_str();	}
			virtual UInt  Line ( ) const throw ( )					{ return m_line;				}
			virtual UInt  ErrorCode ( ) const throw ( )				{ return m_errorCode;			}

		protected:

			std::string m_what;
			std::string m_file;
			std::string m_function;
			UInt		m_line;
			UInt		m_errorCode;
			
	};
	//end class Exception



	Exception::Exception ( const Char* what, UInt errorCode, const Char* file,
							const Char* function, const UInt line )
		: m_what(what), m_errorCode(errorCode), m_file(file),
			m_function(function), m_line(line)
	{
		if ( what==0 )
			m_what = "Unknown";

		if ( file == 0 )
			m_file = "Unknown";

		if ( function == 0 )
			m_function = "Unknown";

	}


	Exception::Exception ( const Exception& right )
	{
		m_what = right.m_what;
		m_errorCode = right.m_errorCode;
		m_file = right.m_file;
		m_function = right.m_function;
		m_line = right.m_line;
	}


	Exception& Exception::operator= ( const Exception& right )
	{
		m_what = right.m_what;
		m_errorCode = right.m_errorCode;
		m_file = right.m_file;
		m_function = right.m_function;
		m_line = right.m_line;

		return *this;
	}

};
//end namespace Core

#endif //#ifndef CORE_EXCEPTION_H