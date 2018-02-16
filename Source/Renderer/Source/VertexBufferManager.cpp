//======================================================================================
//! @file         VertexBufferManager.cpp
//! @brief        Handle based resource manager class for vertex buffers. Provides a central point
//!				  for the creation, and access of vertex buffers. 
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 06 June 2005
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



#include "Core/Core.h"
#include "Renderer/VertexBufferManager.h"
#include "Renderer/VertexBufferCreator.h"



using namespace Renderer;



//=========================================================================
//! @function    VertexBufferManager::CreateVertexBuffer
//! @brief       Create a new vertex buffer
//!              
//! @param       vertexSize  [in] Size of a single vertex in the buffer
//! @param       vertexCount [in] Number of vertices
//! @param       usage		 [in] Usage flags for the vertex buffer
//!              
//! @return      A handle to a new vertex buffer object,
//!				 or a null handle, if the call was unsuccessful
//=========================================================================
VertexBufferManager::HandleType VertexBufferManager::CreateVertexBuffer( size_t vertexSize, 
																		 size_t vertexCount, 
																		 EUsage usage )
{
	if ( !m_creator )
	{
		std::cerr << __FUNCTION__ ": Error! No creator has been set!" << std::endl;  
		return Core::NullHandle();
	}
	else
	{

		boost::shared_ptr<VertexBuffer> buffer(m_creator->CreateVertexBuffer
																( vertexSize, vertexCount, usage ));

		if ( buffer )
		{
			return AddNewResource(buffer);
		}
		else
		{
			std::cerr << __FUNCTION__ ": CreateVertexBuffer failed!" << std::endl;
			return Core::NullHandle();
		}
	}
}
//End VertexBufferManager::CreateVertexBuffer



//=========================================================================
//! @function    VertexBufferManager::RequiresRestore
//! @brief       Doesn't really make much sense in this context, just returns false
//=========================================================================
bool VertexBufferManager::RequiresRestore() const
{
	return false;
}
//End VertexBufferManager::RequiresRestore



//=========================================================================
//! @function    VertexBufferManager::PrepareForRestore
//! @brief       Prepares the vertex buffers to be restored
//!              Must be called before the renderer is restored
//!
//! @param		 forceRestore [in] Forces a restore on all buffers
//!								   regardless of whether they need to be 
//!								   restored or not
//=========================================================================
void VertexBufferManager::PrepareForRestore( bool forceRestore ) 
{
	VertexBufferManager::ResourceStore::iterator itr;

	for ( itr = Begin(); itr != End(); ++itr )
	{
		//If the object itr refers to is a valid vertex buffer
		//then restore it
		if ( *itr )
		{
			(*itr)->PrepareForRestore(forceRestore);
		}
	}
}
//End VertexBufferManager::PrepareForRestore 



//=========================================================================
//! @function    VertexBufferManager::Restore
//! @brief       Calls Restore on every buffer in the VertexBufferManager
//!              
//! @param		 forceRestore [in] Forces a restore whether it is needed or not
//!
//=========================================================================
void VertexBufferManager::Restore( bool forceRestore )
{
	VertexBufferManager::ResourceStore::iterator itr;

	for ( itr = Begin(); itr != End(); ++itr )
	{
		//If the object itr refers to is a valid vertex buffer
		//then restore it
		if ( *itr )
		{
			(*itr)->Restore( forceRestore );
		}
	}
}
//End VertexBufferManager::Restore
