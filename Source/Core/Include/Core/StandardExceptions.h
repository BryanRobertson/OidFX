//======================================================================================
//! @file         StandardExceptions.h
//! @brief        Replacement for stdexcept, deriving from Exception, rather than exception
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 24 January 2005
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
#ifndef CORE_STANDARDEXCEPTIONS_H
#define CORE_STANDARDEXCEPTIONS_H

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/Exception.h"


namespace Core
{

	//! @brief	Base class for all exceptions reporting errors presumably detectable 
	//!		    before the program executes, such as violations of logical preconditions.
	class LogicError : public Exception
	{
		public:
		
			LogicError ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: Exception ( what, errorCode, file, function, line )
			{
			}
	};
	//end LogicError



	//! @brief	The class serves as the base class for all exceptions thrown to report a domain error
	class DomainError : public LogicError
	{
		public:

			DomainError ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: LogicError ( what, errorCode, file, function, line )
			{
			}
	};
	//end DomainError



	//! @brief	The class serves as the base class for all 
	//!			exceptions thrown to report an invalid argument.
	class InvalidArgument : public LogicError
	{
		public:

			InvalidArgument ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: LogicError ( what, errorCode, file, function, line )
			{
			}
	};
	//end InvalidArgument



	//!@ brief The class serves as the base class for all exceptions thrown to report 
	//!			an attempt to generate an object too long to be specified.
	class LengthError : public LogicError
	{
		public:
		
			LengthError	 ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: LogicError ( what, errorCode, file, function, line )
			{
			}	
	};
	//end LengthError



	//!@brief	The class serves as the base class for all exceptions thrown 
	//!			to report an argument that is out of its valid range.
	class OutOfRange : public LogicError
	{
		public:

			OutOfRange ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: LogicError ( what, errorCode, file, function, line )
			{
			}

	};
	//end OutOfRange



	//!@brief	Base class for all exceptions only detectable at runtime
	class RuntimeError : public Exception
	{
		public:

			RuntimeError ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
				: Exception ( what, errorCode, file, function, line )
			{
			}

	};
	//end RuntimeError



	//!@brief	The class serves as the base class for all exceptions thrown to report an arithmetic overflow.
	class OverflowError : public RuntimeError
	{
		public:

			OverflowError ( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: RuntimeError ( what, errorCode, file, function, line )
			{
			}

	};
	//end OverflowError



	//!@brief	The class serves as the base class for all exceptions thrown to report a range error.
	class RangeError : public RuntimeError
	{
		public:

			RangeError	( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: RuntimeError ( what, errorCode, file, function, line )
			{
			}
	};
	//end RangeError



	//!@brief	The class serves as the base class for all exceptions thrown to report an arithmetic underflow.
	class UnderflowError : public RuntimeError
	{
		public:

			UnderflowError	( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
									const Char* function = "Unknown", const UInt line = 0 ) throw()
									: RuntimeError ( what, errorCode, file, function, line )
			{
			}

	};
	//end UnderflowError


};
//end namespace Core

#endif
//#ifndef CORE_STANDARDEXCEPTIONS_H
