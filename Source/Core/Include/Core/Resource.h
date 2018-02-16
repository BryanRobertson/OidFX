//======================================================================================
//! @file         Resource.h
//! @brief        Resource base class. Abstract base class representing a resource, such
//!               as a texture or sound. Under the control of a resource manager
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

#ifndef CORE_RESOURCE_H
#define CORE_RESOURCE_H

#include "Core/ResourceManager.h"


//namespace Core
namespace Core
{

	//! @class Resource
	//! @brief Resource template. 
	//!
	//!		   Template for an abstract base class representing a resource, such
	//!        as a texture or sound. Under the control of a resource manager       
	class Resource
	{
		public:

			Resource ( const Char* name );
			virtual ~Resource ( );

			virtual void Unload ( ) = 0;

			//Friends
			friend class ResourceManager;

			//Accessors
			const std::string& Name ( )	const	{ return m_name;			}
			UInt ID ( )	const					{ return NameHash();		}
			UInt NameHash ( ) const				{ return m_nameHash;		}
			UInt ReferenceCount ( ) const		{ return m_referenceCount;	}
			UInt SizeInBytes ( ) const			{ return m_sizeInBytes;		}

		protected:

			inline UInt IncrementReferenceCount ( )		{ return ++m_referenceCount;	}
			inline UInt DecrementReferenceCount ( )		{ return --m_referenceCount;	}

			void Name ( const Char* name );

		private:

			UInt		m_referenceCount;	//!< Count of the number of objects that have a handle to this resource
			std::string m_name;				//!< Name of the resource
			UInt		m_nameHash;			//!< Unsigned integer value generated from the filename that uniquely identifies it
											//!< for quick comparisons
			UInt		m_sizeInBytes;		//!< size of the stored resource in bytes
	};
	//end class Resource

};
//end namespace Core


#endif //#ifndef CORE_RESOURCE_H