//======================================================================================
//! @file         VertexDeclarationManager.cpp
//! @brief        Resource manager for vertex declaration resources
//!               
//!				  VertexDeclaration objects describe a format for vertex data
//!               contained in an arbitrary number of vertex "streams"
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 28 July 2005
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


#include "Core/Core.h"
#include "Renderer/RendererConstants.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/VertexDeclarationDescriptor.h"
#include "Renderer/VertexDeclarationCreator.h"
#include "Renderer/VertexDeclarationManager.h"


using namespace Renderer;



//=========================================================================
//! @function    VertexDeclarationManager::VertexDeclarationManager
//! @brief       VertexDeclarationManager creator
//!              
//! @param       creator  [in]		
//!              
//!
//=========================================================================
VertexDeclarationManager::VertexDeclarationManager ( IVertexDeclarationCreator& creator )
: Core::ResourceManager<VertexDeclaration>( g_maxVertexDeclarations ), m_creator(&creator)
{

}
//End VertexDeclarationManager::VertexDeclarationManager



//=========================================================================
//! @function    VertexDeclarationManager::AcquireVertexDeclaration
//! @brief       Get a handle to a vertex declaration
//!
//!				 If a vertex declaration with the same format as descriptor 
//!				 exists, then a handle to the existing declaration will be returned
//!				 Otherwise, a new vertex declaration will be created, and the handle
//!				 to the new object returned
//!
//! @param       descriptor [in]	Descriptor, describing the format of the vertex declaration
//!                            
//! @return      A handle to the vertex declaration
//! @throw       Core::RuntimeError
//=========================================================================
VertexDeclarationManager::HandleType VertexDeclarationManager::AcquireVertexDeclaration 
																( VertexDeclarationDescriptor& descriptor )
{
	debug_assert ( m_creator, "No creator object set!" );

	HandleType handle ( AcquireExistingResource(descriptor.Checksum()) );

	if ( handle == Core::NullHandle() )
	{
		
		boost::shared_ptr<VertexDeclaration> decl = m_creator->CreateVertexDeclaration( descriptor );

		return AddNewResource ( decl );
	
	}
	else
	{
		return handle;
	}

}
//End VertexDeclarationManager::AcquireVertexDeclaration
