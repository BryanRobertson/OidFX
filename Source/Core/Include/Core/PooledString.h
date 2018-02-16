//======================================================================================
//! @file         PooledString.h
//! @brief        Typedefs for strings that use a memory pool, rather than new/delete
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 19 August 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================

#ifndef CORE_POOLEDSTRING_H
#define CORE_POOLEDSTRING_H


#include <string>
#include <sstream>


//namespace Core
namespace Core
{

	typedef std::basic_string<Char, std::char_traits<Char>, FastPoolAllocator<Char>::Type >		 
			PooledString;

	typedef std::basic_stringstream< Char, std::char_traits<Char>,  FastPoolAllocator<Char>::Type > 
			PooledStringStream;

}
//end namespace Core

#endif
//#ifndef CORE_POOLEDSTRING_H

