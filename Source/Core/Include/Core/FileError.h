//======================================================================================
//! @file         FileError.h
//! @brief        Exceptions relating to files
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 28 February 2005
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

#ifndef CORE_FILEERROR_H
#define CORE_FILEERROR_H


#include "Core/StandardExceptions.h"
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{

	//! @brief	Indicates that a file was not found
	class FileNotFound : public RuntimeError
	{
		public:
		
			FileNotFound ( const Char* fileName, UInt errorCode = 0, const Char* file = "Unknown",
						   const Char* function = "Unknown", const UInt line = 0 ) throw()
									: RuntimeError ( fileName, errorCode, file, function, line )
			{
			}
	};
	//end FileNotFound

};
//end namespace Core


#endif
//#ifndef CORE_FILEERROR_H
