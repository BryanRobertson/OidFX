//======================================================================================
//! @file         DirectXVertexBuffer.h
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


#ifndef DIRECTX9RENDERER_DIRECTXVERTEXBUFFER_H
#define DIRECTX9RENDERER_DIRECTXVERTEXBUFFER_H


#include <atlbase.h>


//namespace DirectX9Renderer
namespace DirectX9Renderer
{

	//!@class	DirectXVertexBuffer
	//!@brief	Specialisation of VertexBuffer for DirectX
	class DirectXVertexBuffer : public Renderer::VertexBuffer
	{
		public:

			DirectXVertexBuffer ( DirectXRenderer& renderer, size_t vertexSize, size_t vertexCount, Renderer::EUsage usage );

			//Bind a vertex buffer to one of the renderers streams
			bool Bind( UInt streamNumber );

			//Resource implementations
			void Unload() {}

			//IRestorable implementation
			bool RequiresRestore() const;
			void PrepareForRestore( bool forceRestore );
			void Restore( bool forceRestore );

		private:

			//Create the vertex buffer
			void Create();

			//Implementation of unlock and lock methods
			void UnlockImplementation();
			Renderer::ScopedBufferLock<Renderer::VertexBuffer> LockImplementation( size_t lockBegin, size_t lockSize, Renderer::ELock lockOptions ) throw();
			
			//Private data
			DirectXRenderer&				m_renderer;
			CComPtr<IDirect3DVertexBuffer9> m_buffer;
			bool							m_requiresRestore;
			D3DPOOL							m_pool;
	};

};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_DIRECTXVERTEXBUFFER_H
