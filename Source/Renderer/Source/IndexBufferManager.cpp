//======================================================================================
//! @file         IndexBufferManager.cpp
//! @brief        Handle based resource manager class for index buffers. Provides a central point
//!				  for the creation, and access of index buffers. 
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
#include "Renderer/IndexBufferManager.h"
#include "Renderer/IndexBufferCreator.h"



using namespace Renderer;



//=========================================================================
//! @function    IndexBufferManager::CreateIndexBuffer
//! @brief       Create a new Index buffer
//!              
//! @param       IndexSize  [in] Size of a single index in the buffer
//! @param       IndexCount [in] Number of vertices
//! @param       usage		 [in] Usage flags for the index buffer
//!              
//! @return      A handle to a new Index buffer object,
//!				 or a null handle, if the call was unsuccessful
//=========================================================================
IndexBufferManager::HandleType IndexBufferManager::CreateIndexBuffer( EIndexSize IndexSize, 
																		 size_t IndexCount, 
																		 EUsage usage )
{

	if ( !m_creator )
	{
		std::cerr << __FUNCTION__ ": Error! No creator has been set!" << std::endl;  
		return Core::NullHandle();
	}
	else
	{

		boost::shared_ptr<IndexBuffer> buffer(m_creator->CreateIndexBuffer
																( IndexSize, IndexCount, usage ));

		if ( buffer )
		{
			return AddNewResource(buffer);
		}
		else
		{
			std::cerr << __FUNCTION__ ": CreateIndexBuffer failed!" << std::endl;
			return Core::NullHandle();
		}
	}
}
//End IndexBufferManager::CreateIndexBuffer



//=========================================================================
//! @function    IndexBufferManager::RequiresRestore
//! @brief       Doesn't really make much sense in this context, just returns false
//=========================================================================
bool IndexBufferManager::RequiresRestore() const
{
	return false;
}
//End IndexBufferManager::RequiresRestore


//=========================================================================
//! @function    IndexBufferManager::PrepareForRestore
//! @brief       Prepares the index buffers to be restored
//!              Must be called before the renderer is restored
//!
//! @param		 forceRestore [in]	Forces all buffers to restore themselves
//=========================================================================
void IndexBufferManager::PrepareForRestore( bool forceRestore ) 
{
	IndexBufferManager::ResourceStore::iterator itr;

	for ( itr = Begin(); itr != End(); ++itr )
	{
		
		//If the object itr refers to is a valid Index buffer
		//then restore it
		if ( *itr )
		{
			(*itr)->PrepareForRestore(forceRestore);
		}
	}
}
//End IndexBufferManager::PrepareForRestore



//=========================================================================
//! @function    IndexBufferManager::Restore
//! @brief       Calls Restore on every buffer in the IndexBufferManager
//!              
//! @param		 forceRestore [in] Forces all buffers to restore themselves
//!
//=========================================================================
void IndexBufferManager::Restore( bool forceRestore )
{
	IndexBufferManager::ResourceStore::iterator itr;

	for ( itr = Begin(); itr != End(); ++itr )
	{
		
		//If the object itr refers to is a valid Index buffer
		//then restore it
		if ( *itr )
		{
			(*itr)->Restore(forceRestore);
		}
	}
}
//End IndexBufferManager::Restore
