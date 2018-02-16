//======================================================================================
//! @file         ToLower.h
//! @brief        Utilities for converting standard C++ strings to lower case
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 01 February 2005
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

#ifndef CORE_UTIL_TOLOWER
#define CORE_UTIL_TOLOWER

#include <algorithm>
#include <string>
#include <cstdlib>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"

//namespace Core
namespace Core
{
	
	//!@class	ToLowerFunc
	//!@brief	Function object compatible with std::for_each
	//!			user to convert a container holding chars to lower case
	class ToLowerFunc
	{
		public:
			
			void operator()( Char& elem )
			{
				elem = tolower(elem);		
			}
	};
	//end class ToLowerFunc

};
//end namespace Core


#endif
//#ifndef CORE_UTIL_TOLOWER