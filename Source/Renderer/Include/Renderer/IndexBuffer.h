//======================================================================================
//! @file         IndexBuffer.h
//! @brief        Abstract base class for an index buffer
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


#ifndef RENDERER_INDEXBUFFER_H
#define RENDERER_INDEXBUFFER_H


#include <boost/noncopyable.hpp>
#include "Core/Resource.h"
#include "Core/Handle.h"
#include "Core/Restorable.h"
#include "Renderer/ScopedBufferLock.h"
#include "Renderer/RendererBuffer.h"


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Related types
    //=========================================================================
	enum EIndexSize { INDEX_16BIT = 16, INDEX_32BIT = 32 };


	//!@class	IndexBuffer
	//!@brief	Abstract base class for an index buffer
	class IndexBuffer:   public RendererBuffer<IndexBuffer>,
						 public Core::Resource,
						 public Core::IRestorable,
						 public boost::noncopyable
	{
		public:

			//Public methods
			inline IndexBuffer ( EIndexSize indexSize, size_t indexCount, EUsage usage  );

			inline virtual bool Bind () throw() = 0;

			inline EIndexSize IndexSize() const throw();
			inline size_t	  IndexCount() const throw();

			inline ScopedBufferLock<IndexBuffer> LockAll ( ELock lockOptions );

		private:

			EIndexSize m_indexSize;
			size_t	   m_indexCount;
	};
	//End class IndexBuffer


	//Typedefs
	typedef Core::Handle<IndexBuffer> HIndexBuffer;
	typedef Renderer::ScopedBufferLock<IndexBuffer>	ScopedIndexBufferLock;



    //=========================================================================
    //! @function    IndexBuffer::IndexBuffer
    //! @brief       Construct an index buffer
    //!              
    //! @param       indexSize	  [in] Size of a single index in the buffer	 
    //! @param       indexCount	  [in] Number of indices	
    //! @param       usageOptions [in] Usage options for the buffer
	//!              
    //=========================================================================
	IndexBuffer::IndexBuffer ( EIndexSize indexSize, size_t indexCount, EUsage usage )
		: Resource("."), RendererBuffer<IndexBuffer>(usage), m_indexSize(indexSize), m_indexCount(indexCount)
	{
	}
	//End IndexBuffer::IndexBuffer



    //=========================================================================
    //! @function    IndexBuffer::IndexSize
    //! @brief       Size of a single index in the index buffer
    //!              
    //! @return      Size of a single index in the index buffer
    //=========================================================================
	EIndexSize IndexBuffer::IndexSize() const
	{
		return m_indexSize;
	}
	//End IndexBuffer::IndexSize



    //=========================================================================
    //! @function    IndexBuffer::IndexCount
    //! @brief       Number of indices in the buffer
    //!              
    //! @return      Number of indeices in the buffer
    //=========================================================================
	size_t IndexBuffer::IndexCount() const
	{
		return m_indexCount;
	}
	//End IndexBuffer::IndexCount



	//=========================================================================
    //! @function    IndexBuffer::LockAll
    //! @brief       Lock the whole buffer
    //!              
    //! @param       lockOptions [in] Options to lock the buffer with
    //!              
    //! @return      A lock object representing the lock, or a null lock if failed
    //=========================================================================
	ScopedBufferLock<IndexBuffer> IndexBuffer::LockAll ( ELock lockOptions )
	{
		return LockImplementation( 0, IndexSize()*IndexCount(), lockOptions );
	}
	//End VertexBuffer::Lock


};
//end namespace Renderer


#endif
//#ifndef INDEXBUFFER_H
