//======================================================================================
//! @file         Singleton.h
//! @brief        Base class for an object using the singleton design pattern
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 21 May 2005
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

#ifndef CORE_SINGLETON_H
#define CORE_SINGLETON_H


#include <boost/shared_ptr.hpp>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"

//namespace Core
namespace Core
{

	//!@class	Singleton
	//!@brief	Base class for an object using the singleton design pattern
	template <class T>
	class Singleton
	{
		public:

			Singleton ( T* instance )
			{
				//NOTE: Singleton may not call any methods of instance here,
				//as instance is not fully constructed at this point
				ms_singleton = instance;
			}

			virtual ~Singleton ()
			{
				debug_assert ( ms_singleton, "Singleton is null!" );
				ms_singleton = 0;
			}

			static T& GetSingleton()
			{
				debug_assert ( ms_singleton, "Singleton is null!" );
				return *ms_singleton;
			}

		protected:

		private:

			//Private data
			static T* ms_singleton;

	};
	//end class Singleton

	//Static initialization
	template <class T> 
		T* Singleton<T>::ms_singleton = 0;


};
//end namespace Core


#endif
//#ifndef CORE_SINGLETON_H
