//======================================================================================
//! @file         Resource.cpp
//! @brief        Resource base class. Base class representing a resource, such
//!               as a texture or sound. Under the control of a resource manager
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 17 January 2005
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


#include <string>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/Hash.h"
#include "Core/Resource.h"
#include "Core/ResourceManager.h"



using namespace Core;



//=========================================================================
//! @function    Resource::Resource<Manager>::Constructor
//! @brief       
//!              
//=========================================================================
Resource::Resource( const Char* name )
: m_referenceCount ( 1 ), m_nameHash ( 0 ), m_sizeInBytes ( 0 )
{
	Name ( name );
}
//end Resource::Resource<Manager>::Constructor



//=========================================================================
//! @function    Resource::Resource<Manager>::Destructor
//! @brief       
//!              
//=========================================================================
Resource::~Resource( )
{
	//Unload();
}
//end Resource::Resource<Manager>::Destructor



//=========================================================================
//! @function    Resources::Resource::Name ( const Char* )
//! @brief       Set the name of the resource, and update the name hash
//!              
//! @param       name [in]	New name of the resource 
//!              
//=========================================================================
void Resource::Name ( const Char* name )
{
	assert ( name );

	m_name = name;
	m_nameHash = GenerateHashFromString ( m_name.c_str() );
}
//end Resource::Name
