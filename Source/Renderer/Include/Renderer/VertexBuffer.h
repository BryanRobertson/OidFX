//======================================================================================
//! @file         VertexBuffer.h
//! @brief        Abstract base class for a vertex buffer
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 05 June 2005
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

#ifndef RENDERER_VERTEXBUFFER_H
#define RENDERER_VERTEXBUFFER_H


#include <boost/noncopyable.hpp>
#include "Core/Resource.h"
#include "Core/Handle.h"
#include "Core/Restorable.h"
#include "Renderer/ScopedBufferLock.h"
#include "Renderer/RendererBuffer.h"


//namespace Renderer
namespace Renderer
{


	//!@class	VertexBuffer
	//!@brief	Abstract base class for a vertex buffer
	class VertexBuffer : public RendererBuffer<VertexBuffer>,
						 public Core::Resource,
						 public Core::IRestorable,
						 public boost::noncopyable
	{

		public:

			//Public methods
			inline VertexBuffer ( size_t vertexSize, size_t vertexCount, EUsage usage );

			inline size_t VertexSize() const throw();
			inline size_t VertexCount() const throw();

			inline virtual bool Bind( UInt streamNumber ) throw() = 0;

			//We have to put this in here or the
			inline ScopedBufferLock<VertexBuffer> LockAll ( ELock lockFlags );

		private:

			size_t	m_vertexSize;
			size_t	m_vertexCount;
	};
	//End VertexBuffer


	//Typedefs
	typedef Core::Handle<VertexBuffer>					HVertexBuffer;
	typedef Renderer::ScopedBufferLock<VertexBuffer>	ScopedVertexBufferLock;


    //=========================================================================
    //! @function    VertexBuffer::VertexBuffer
    //! @brief       Construct a vertex buffer
    //!              
    //! @param       vertexSize  [in] Size of vertex, in bytes
    //! @param       vertexCount [in] Number of vertices, in bytes
    //! @param       usage		 [in] Usage flags for the vertex buffer
    //!              
	//!	USAGE_STATIC		Vertex buffer won't be changed regularly
	//!	USAGE_DYNAMIC		Vertex buffer will be changed regularly
	//!	USAGE_WRITEONLY		Vertex buffer can only be written to
	//! USAGE_DONOTCLIP		Vertices should not be clipped
	//!
    //=========================================================================
	VertexBuffer::VertexBuffer ( size_t vertexSize, size_t vertexCount, EUsage usage )
		: Resource("."), RendererBuffer<VertexBuffer>(usage), m_vertexSize(vertexSize), m_vertexCount(vertexCount)
	{
	}
	//VertexBuffer::VertexBuffer


    //=========================================================================
    //! @function    VertexBuffer::VertexSize
    //! @brief       Size of a single vertex in the buffer
    //!              
    //! @return      The size of a single vertex in the buffer
    //=========================================================================
	size_t VertexBuffer::VertexSize() const
	{
		return m_vertexSize;
	}
	//End VertexBuffer::VertexSize


    //=========================================================================
    //! @function    VertexBuffer::VertexCount
    //! @brief       The number of vertices in the buffer
    //!              
    //! @return      The number of vertices in the buffer
    //=========================================================================
	size_t VertexBuffer::VertexCount() const
	{
		return m_vertexCount;
	}
	//End VertexBuffer::VertexCount


    //=========================================================================
    //! @function    VertexBuffer::LockAll
    //! @brief       Lock the whole buffer
    //!              
    //! @param       lockOptions [in] Options to lock the buffer with
    //!              
    //! @return      A lock object representing the lock, or a null lock if failed
    //=========================================================================
	ScopedBufferLock<VertexBuffer> VertexBuffer::LockAll ( ELock lockOptions )
	{
		return LockImplementation( 0, VertexSize()*VertexCount(), lockOptions );
	}
	//End VertexBuffer::Lock


};
//End namespace Renderer

#endif
//#ifndef VERTEXBUFFER_H
