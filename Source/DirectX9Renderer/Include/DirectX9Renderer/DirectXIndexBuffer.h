//======================================================================================
//! @file         DirectXIndexBuffer.h
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


#ifndef DIRECTX9RENDERER_DIRECTXINDEXBUFFER_H
#define DIRECTX9RENDERER_DIRECTXINDEXBUFFER_H


#include <atlbase.h>


//namespace DirectX9Renderer
namespace DirectX9Renderer
{

	//!@class	DirectXIndexBuffer
	//!@brief	Specialisation of IndexBuffer for DirectX
	class DirectXIndexBuffer : public Renderer::IndexBuffer
	{
		public:

			DirectXIndexBuffer ( DirectXRenderer& renderer, 
								 Renderer::EIndexSize indexSize, 
								 size_t indexCount, 
								 Renderer::EUsage usage );

			//Bind an index buffer as the renderer's current index source
			bool Bind( );

			//Resource implementations
			void Unload() {}

			//IRestorable implementation
			bool RequiresRestore() const;
			void PrepareForRestore( bool forceRestore );
			void Restore( bool forceRestore );

		private:

			//Create the buffer
			void Create();

			//Implementation of unlock and lock methods
			void UnlockImplementation();
			Renderer::ScopedBufferLock<Renderer::IndexBuffer> LockImplementation( size_t lockBegin, 
																				  size_t lockSize, 
																				  Renderer::ELock lockOptions ) throw();
			
			//Private data
			DirectXRenderer&				m_renderer;
			CComPtr<IDirect3DIndexBuffer9>  m_buffer;
			bool							m_requiresRestore;
			D3DPOOL							m_pool;
	};

};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_DIRECTXINDEXBUFFER_H
