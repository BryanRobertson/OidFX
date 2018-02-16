//======================================================================================
//! @file         StandardIncludes.h
//! @brief        Includes from the standard library, and other important includes
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 15 September 2005
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


#ifndef CORE_STANDARDINCLUDES_H
#define CORE_STANDARDINCLUDES_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <set>
#include <map>

#ifdef CORE_HASHMAP_SUPPORTED
#	include <hash_map>
#endif 
//#ifdef CORE_HASHMAP_SUPPORTED

#ifdef CORE_HASHSET_SUPPORTED
#	include <hash_set>
#endif 
//#ifdef CORE_HASHSET_SUPPORTED


#endif
//#ifndef CORE_STANDARDINCLUDES_H
