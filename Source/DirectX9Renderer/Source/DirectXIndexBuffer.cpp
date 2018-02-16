//======================================================================================
//! @file         DirectXIndexBuffer.cpp
//! @brief        Specialisation of IndexBuffer for DirectX
//!               
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
#include "Renderer/IndexBuffer.h"
#include "Renderer/RendererConstantToString.h"
#include "DirectX9Renderer/DirectX9Renderer.h"
#include "DirectX9Renderer/DirectXIndexBuffer.h"
#include "DirectX9Renderer/ErrorCodes.h"


using namespace DirectX9Renderer;



//=========================================================================
//! @function    DirectXIndexBuffer::DirectXIndexBuffer
//! @brief       Creates a DirectX index buffer
//!              
//! @param       renderer	 [in] Reference to the renderer to which this buffer belongs
//! @param       indexSize   [in] Size of a single index in the buffer, INDEX_16BIT or INDEX_32BIT
//! @param       indexCount  [in] Number of indices in the buffer
//! @param       usage		 [in] Usage flags for the buffer
//!             
//!	USAGE_STATIC		Index buffer won't be changed regularly
//!	USAGE_DYNAMIC		Index buffer will be changed regularly
//!	USAGE_WRITEONLY		Index buffer can only be written to
//!
//! @throw		If the creation of the index buffer fails, then
//!				a RendererError is thrown
//=========================================================================
DirectXIndexBuffer::DirectXIndexBuffer ( DirectXRenderer& renderer, Renderer::EIndexSize indexSize, 
										 size_t indexCount, Renderer::EUsage usage )
										   : IndexBuffer ( indexSize, indexCount, usage ), 
										     m_renderer(renderer),
											 m_requiresRestore(false),
											 m_pool(D3DPOOL_MANAGED)
{
	//Create the buffer
	Create();
}
//End DirectXIndexBuffer::DirectXIndexBuffer



//=========================================================================
//! @function    DirectXIndexBuffer::Bind
//! @brief       Bind an index buffer as the renderer's current index source
//!           
//! @return      true if successful
//!				 false if failed
//=========================================================================
bool DirectXIndexBuffer::Bind( )
{
	debug_assert ( !RequiresRestore(), "Buffer is lost!");

	HRESULT result = m_renderer.Device()->SetIndices( m_buffer );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ << ": Error! SetIndices failed!" << std::endl;
		return false;
	}

	return true;
}
//End DirectXIndexBuffer::Bind



//=========================================================================
//! @function    DirectXIndexBuffer::RequiresRestore
//! @brief       Indicates whether or not the contents of the buffer 
//!				 need to be restored
//!              
//!              If the buffer is in the managed pool, then this will always
//!				 return false
//=========================================================================
bool DirectXIndexBuffer::RequiresRestore( ) const
{
	if ( !m_buffer )
	{
		return true;
	}

	if ( m_pool == D3DPOOL_MANAGED )
	{
		return false;
	}
	else
	{
		return m_requiresRestore;
	}
}
//End DirectXIndexBuffer::RequiresRestore( )



//=========================================================================
//! @function    DirectXIndexBuffer::PrepareForRestore
//! @brief       Do any required preparation for a restore
//!              
//!				 In the case of a DirectX index buffer, this releases
//!				 the buffer, if the index buffer was not created in the managed pool
//!				 If forceRestore is true, then the buffer will be released, regardless
//!				 of whether it was created in the managed pool
//!
//! @param		 forceRestore [in] Prepare for restore, regardless of whether this
//!								   buffer was created in the managed pool
//=========================================================================
void DirectXIndexBuffer::PrepareForRestore( bool forceRestore )
{
	if ( (forceRestore) || (m_pool != D3DPOOL_MANAGED) )
	{
		m_requiresRestore = true;
		m_buffer.Release();
	}
}
//End DirectXIndexBuffer::PrepareForRestore



//=========================================================================
//! @function    DirectXIndexBuffer::Restore
//! @brief       Restore the DirectX index buffer
//!  
//!	@param		 forceRestore [in] Forces a restore, regardless of whether
//!								   the buffer has been lost or not
//!
//=========================================================================
void DirectXIndexBuffer::Restore( bool forceRestore )
{
	if ( forceRestore || m_requiresRestore )
	{
		if (!m_requiresRestore)
		{
			//Failsafe to make sure we don't leak memory
			PrepareForRestore(true);
		}

		Create();
		m_requiresRestore = false;
	}
}
//End DirectXIndexBuffer::Restore



//=========================================================================
//! @function    DirectXIndexBuffer::UnlockImplementation
//! @brief       Implementation of Unlock for DirectX index buffers
//!              
//=========================================================================
void DirectXIndexBuffer::UnlockImplementation()
{
	debug_assert( m_buffer, "Attempted to unlock null buffer" );

	m_buffer->Unlock();
}
//End DirectXIndexBuffer::UnlockImplementation



//=========================================================================
//! @function    DirectXIndexBuffer::LockImplementation
//! @brief       Lock part of the buffer
//!              
//! @param       lockBegin   [in] Offset from beginning of buffer to start of lock, in bytes
//! @param       lockSize    [in] Offset from the beginning of the lock to the end of the lock, in bytes
//! @param       lockOptions [in] Options used to lock the buffer @see ELock
//!              
//! @return      A lock into the buffer, if the lock operation succeeded
//!				 A null lock if the lock was not successful       
//=========================================================================
Renderer::ScopedBufferLock<Renderer::IndexBuffer> DirectXIndexBuffer::LockImplementation( size_t lockBegin, 
																	    size_t lockSize, 
																		Renderer::ELock lockOptions )
{
	debug_assert ( !RequiresRestore(), "Buffer is lost!");

	DWORD dxFlags = 0;
	void* lockPointer = 0;

	#ifdef DEBUG_BUILD
	
		std::clog << __FUNCTION__ ": Locking buffer from " << lockBegin 
				<< ", size " << lockSize
				<< ", options" << Renderer::RendererBufferLockOptionsToString ( lockOptions ) << std::endl;;

	#endif

	//Set up flags
	if ( dxFlags & static_cast<UInt>(Renderer::LOCK_DISCARD))
	{
		dxFlags |= D3DLOCK_DISCARD;
	}

	if ( dxFlags & static_cast<UInt>(Renderer::LOCK_NOOVERWRITE) )
	{
		dxFlags |= D3DLOCK_NOOVERWRITE;
	}

	if ( dxFlags & static_cast<UInt>(Renderer::LOCK_READONLY) )
	{
		dxFlags |= D3DLOCK_READONLY;
	}

	HRESULT result = m_buffer->Lock ( lockBegin, lockSize, &lockPointer, dxFlags );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ ": Lock failed! Error Code: "  << D3DErrorCodeToString(result) << std::endl;
		return Renderer::ScopedBufferLock<Renderer::IndexBuffer>();
	}
	else
	{
		return Renderer::ScopedBufferLock<Renderer::IndexBuffer>( *this, lockPointer );
	}
}
//End DirectXIndexBuffer::LockImplementation




//=========================================================================
//! @function    DirectXIndexBuffer::Create
//! @brief       Create the buffer
//=========================================================================
void DirectXIndexBuffer::Create()
{
	#ifdef DEBUG_BUILD
		std::clog << "\nCreating DirectXIndexBuffer:\n" 
				<< "\tIndex size = " << IndexSize() << "\n"
				<< "\tIndex count = " << IndexCount() << "\n"
				<< "\tUsage flags =" << Renderer::RendererBufferUsageToString(Usage()) << "\n" << std::endl;
	#endif


	//Convert the usage flags into something DirectX can use
	DWORD dxUsageFlags = 0;
	
	if ( (Usage() & Renderer::USAGE_DISCARDABLE ) && (!(Usage() && Renderer::USAGE_WRITEONLY)) )
	{
		//If the buffer is created with the discardable flag,
		//and not the write only flag, then locking with the discard flag
		//will incurr a severe performance penalty
		m_pool = D3DPOOL_DEFAULT;
	}

	if ( Usage() & Renderer::USAGE_DYNAMIC )
	{
		//Dynamic buffers cannot be created with D3DPOOL_MANAGED
		dxUsageFlags |= D3DUSAGE_DYNAMIC;
		m_pool = D3DPOOL_SYSTEMMEM;
	}

	if ( Usage() & Renderer::USAGE_WRITEONLY )
	{
		dxUsageFlags |= D3DUSAGE_WRITEONLY;
	}

	//Convert the index format
	D3DFORMAT dxIndexFormat = (IndexSize() == Renderer::INDEX_16BIT) ? D3DFMT_INDEX16 : D3DFMT_INDEX32;

	//Create the index buffer
	HRESULT result = m_renderer.Device()->CreateIndexBuffer 
												( IndexSize() * IndexCount(),	//Length
												  dxUsageFlags,			//Usage
												  dxIndexFormat,			//Index format
												  m_pool,					//Pool
												  &m_buffer,				//Pointer to index buffer pointer
												  0							//Shared handle, must be NULL
												  );

	if ( FAILED(result) )
	{
		std::ostringstream errorMessage;
		errorMessage << __FUNCTION__ << " CreateIndexBuffer failed! Error code " << D3DErrorCodeToString(result);
		std::cerr << errorMessage.str() << std::endl;

		throw Renderer::RendererError( errorMessage.str().c_str(), result, __FILE__, __FUNCTION__, __LINE__ );
	}

	#ifdef DEBUG_BUILD
		std::clog << __FUNCTION__ " Created index buffer successfully!" << std::endl;
	#endif

}
//End DirectXRenderer::Create