//======================================================================================
//! @file         Memory.h
//! @brief        Memory functions and classes
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 05 September 2005
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


#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H


#include <boost/pool/pool_alloc.hpp>


//namespace Core
namespace Core
{


	//! Simply renames boost::fast_pool_allocator for ease of use
	//! and perhaps to allow it to be swapped out in future, if necessary
	template <class ValueType>
	struct FastPoolAllocator
	{
		typedef boost::fast_pool_allocator<ValueType>	Type;
	};


	//! Simply renames boost::pool_allocator for ease of use
	//! and perhaps to allow it to be swapped out in future, if necessary
	template <class ValueType>
	struct PoolAllocator
	{
		typedef boost::pool_allocator<ValueType>	Type;
	};

	
}
//end namespace Core


#endif
//#ifndef CORE_MEMORY_H

