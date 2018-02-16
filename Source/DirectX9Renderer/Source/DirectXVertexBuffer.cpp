//=====================================================================================
//! @file         DirectXVertexBuffer.cpp
//! @brief        Specialisation of VertexBuffer for DirectX
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
#include "Renderer/VertexBuffer.h"
#include "Renderer/RendererConstantToString.h"
#include "DirectX9Renderer/DirectX9Renderer.h"
#include "DirectX9Renderer/DirectXVertexBuffer.h"
#include "DirectX9Renderer/ErrorCodes.h"


using namespace DirectX9Renderer;


//=========================================================================
//! @function    DirectXVertexBuffer::DirectXVertexBuffer
//! @brief       Creates a DirectX vertex buffer
//!              
//! @param       renderer	 [in] Reference to the renderer to which this buffer belongs
//! @param       vertexSize  [in] Size of a single vertex in the buffer
//! @param       vertexCount [in] Number of vertices in the buffer
//! @param       usage		 [in] Usage options for the buffer
//!             
//! @throw		If the creation of the vertex buffer fails, then
//!				a RendererError is thrown
//=========================================================================
DirectXVertexBuffer::DirectXVertexBuffer ( DirectXRenderer& renderer, size_t vertexSize, 
										  size_t vertexCount, Renderer::EUsage usage )
										   : VertexBuffer ( vertexSize, vertexCount, usage ), 
										   m_renderer(renderer),
										   m_pool(D3DPOOL_MANAGED),
										   m_requiresRestore(false)
{
	Create();
}
//End DirectXVertexBuffer::DirectXVertexBuffer



//=========================================================================
//! @function    DirectXVertexBuffer::Bind
//! @brief       Bind a vertex buffer to a renderer stream index
//!				 Called internally by DirectXRenderer::Bind, so that
//!				 the DirectX vertex buffer class can call the appropriate
//!				 methods of the Direct3D device
//!              
//! @param       streamNumber [in]	Stream number to be bound to
//!              
//! @return      true if successful
//!				 false if failed
//=========================================================================
bool DirectXVertexBuffer::Bind( UInt streamNumber )
{

	debug_assert ( !RequiresRestore(), "Buffer is lost!");

	if ( streamNumber >= m_renderer.GetDeviceProperty(Renderer::CAP_MAX_STREAMS) )
	{
		std::cerr << __FUNCTION__ << ": Error, streamIndex " << streamNumber 
				  << " is out of range. This device supports a maximum of " 
				  << m_renderer.GetDeviceProperty(Renderer::CAP_MAX_STREAMS) << " streams" << std::endl;
	}	

	HRESULT result = m_renderer.Device()->SetStreamSource ( streamNumber, m_buffer, 0, VertexSize() );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ << ": Error! SetStreamSource failed!" << std::endl;
		return false;
	}

	return true;
}
//End DirectXVertexBuffer::Bind




//=========================================================================
//! @function    DirectXVertexBuffer::RequiresRestore
//! @brief       Indicates whether or not the contents of the buffer 
//!				 need to be restored
//!              
//!              If the buffer is in the managed pool, then this will always
//!				 return false
//=========================================================================
bool DirectXVertexBuffer::RequiresRestore( ) const
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
//End DirectXVertexBuffer::RequiresRestore( )



//=========================================================================
//! @function    DirectXVertexBuffer::PrepareForRestore
//! @brief       Do any required preparation for a restore
//!              
//!				 In the case of a DirectX index buffer, this releases
//!				 the buffer, if the index buffer was not created in the managed pool
//!
//! @param		 forceRestore [in] Force a restore, regardless of whether or not it is required
//=========================================================================
void DirectXVertexBuffer::PrepareForRestore( bool forceRestore )
{
	if ( (forceRestore) || (m_pool != D3DPOOL_MANAGED) )
	{
		m_requiresRestore = true;
		m_buffer.Release();
	}
}
//End DirectXVertexBuffer::PrepareForRestore



//=========================================================================
//! @function    DirectXVertexBuffer::Restore
//! @brief       Restore the DirectX index buffer
//!              
//! @param		 forceRestore [in] Forces a restore even if it is not required
//!
//=========================================================================
void DirectXVertexBuffer::Restore( bool forceRestore )
{
	if ( (forceRestore) || (m_requiresRestore) )
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
//End DirectXVertexBuffer::Restore



//=========================================================================
//! @function    DirectXVertexBuffer::UnlockImplementation
//! @brief       Implementation of Unlock for DirectX vertex buffers
//!              
//=========================================================================
void DirectXVertexBuffer::UnlockImplementation()
{
	debug_assert( m_buffer, "Attempted to unlock null buffer" );
	debug_assert ( !RequiresRestore(), "Buffer is lost!");

	m_buffer->Unlock();
}
//End DirectXVertexBuffer::UnlockImplementation



//=========================================================================
//! @function    DirectXVertexBuffer::LockImplementation
//! @brief       Lock part of the buffer
//!              
//! @param       lockBegin [in] Offset from beginning of buffer to start of lock, in bytes
//! @param       lockSize  [in] Offset from the beginning of the lock to the end of the lock, in bytes
//! @param       flags	   [in] Lock flags
//!              
//! @return      A lock into the buffer, if the lock operation succeeded
//!				 A null lock if the lock was not successful       
//=========================================================================
Renderer::ScopedBufferLock<Renderer::VertexBuffer> DirectXVertexBuffer::LockImplementation( size_t lockBegin, 
																	    size_t lockSize, 
																		Renderer::ELock lockOptions )
{
	debug_assert ( !RequiresRestore(), "Buffer is lost!");

	DWORD dxFlags = 0;
	void* lockPointer = 0;

	#if 0
	
		std::clog << __FUNCTION__ ": Locking buffer from " << lockBegin 
				<< ", size " << lockSize
				<< ", flags" << Renderer::RendererBufferLockOptionsToString ( lockOptions ) << std::endl;;

	#endif

	//Set up flags
	if ( lockOptions == Renderer::LOCK_DISCARD )
	{
		if ( !(Usage() & Renderer::USAGE_DYNAMIC) )
		{
			std::cerr << "Error, tried to lock a static vertex buffer with LOCK_DISCARD, this is not allowed!" << std::endl;
		}
		
		dxFlags |= D3DLOCK_DISCARD;
	}

	if ( lockOptions == Renderer::LOCK_NOOVERWRITE )
	{
		if ( !(Usage() & Renderer::USAGE_DYNAMIC) )
		{
			std::cerr << "Error, tried to lock a static vertex buffer with LOCK_NOOVERWRITE, this is not allowed!" << std::endl;
		}

		dxFlags |= D3DLOCK_NOOVERWRITE;
	}

	if ( lockOptions == Renderer::LOCK_READONLY )
	{
		dxFlags |= D3DLOCK_READONLY;
	}

	HRESULT result = m_buffer->Lock ( lockBegin, lockSize, &lockPointer, dxFlags );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ ": Lock failed! Error Code: "  << D3DErrorCodeToString(result) << std::endl;
		return Renderer::ScopedBufferLock<Renderer::VertexBuffer>();
	}
	else
	{
		return Renderer::ScopedBufferLock<Renderer::VertexBuffer>( *this, lockPointer );
	}
}
//End DirectXVertexBuffer::LockImplementation



//=========================================================================
//! @function    DirectXVertexBuffer::Create
//! @brief       Create the  buffer
//=========================================================================
void DirectXVertexBuffer::Create()
{

	#ifdef DEBUG_BUILD
		std::clog << "\nCreating DirectXVertexBuffer:\n" 	
				  << "\tVertex size = " << VertexSize() << "\n"
				  << "\tVertex count = " << VertexCount() << "\n"
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

	//Create the vertex buffer
	HRESULT result = m_renderer.Device()->CreateVertexBuffer 
												( VertexSize() * VertexCount(), //Length
												  dxUsageFlags,					//Usage
												  0,							//FVF. We won't be using FVF codes
												  m_pool,						//Pool
												  &m_buffer,					//Pointer to vertex buffer pointer
												  0								//Shared handle, must be NULL
												  );

	if ( FAILED(result) )
	{
		std::ostringstream errorMessage;
		errorMessage << __FUNCTION__ << " CreateVertexBuffer failed! Error code " << D3DErrorCodeToString(result);
		std::cerr << errorMessage.str() << std::endl;

		throw Renderer::RendererError( errorMessage.str().c_str(), result, __FILE__, __FUNCTION__, __LINE__ );
	}

	#ifdef DEBUG_BUILD
		std::clog << __FUNCTION__ " Created vertex buffer successfully!" << std::endl;
	#endif

}
//End DirectXVertexBuffer::Create