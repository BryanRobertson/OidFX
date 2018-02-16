//======================================================================================
//! @file         DirectXVertexBufferCreator.h
//! @brief        Implementation of the IVertexBufferCreator interface that creates
//!               DirectXVertexBuffer objects
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

#ifndef DIRECTX9RENDERER_DIRECTXVERTEXBUFFERCREATOR_H
#define DIRECTX9RENDERER_DIRECTXVERTEXBUFFERCREATOR_H


#include <boost/shared_ptr.hpp>
#include "Renderer/VertexBufferCreator.h"
#include "DirectX9Renderer/DirectXVertexBuffer.h"


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


    //=========================================================================
    // Forward declarations
    //=========================================================================
	class DirectXRenderer;



	//!@class	DirectXVertexBufferCreator
	//!@brief	Implementation of the IVertexBufferCreator interface that creates
	//!         DirectXVertexBuffer objects
	class DirectXVertexBufferCreator : public Renderer::IVertexBufferCreator
	{
		public:

			inline DirectXVertexBufferCreator ( DirectXRenderer& renderer );

			boost::shared_ptr<Renderer::VertexBuffer> CreateVertexBuffer( size_t vertexSize, 
																		  size_t vertexCount, 
																		  Renderer::EUsage usage );

		private:

			DirectXRenderer& m_renderer;

	};
	//End DirectXVertexBufferCreator



    //=========================================================================
    //! @function    DirectXVertexBufferCreator::DirectXVertexBufferCreator
    //! @brief       Initialise the DirectXVertexBufferCreator
    //!              
    //! @param       renderer [in] Renderer object that the creator belongs to
    //!              
    //=========================================================================
	DirectXVertexBufferCreator::DirectXVertexBufferCreator ( DirectXRenderer& renderer )
		: m_renderer(renderer)
	{

	}
	//End DirectXVertexBufferCreator::DirectXVertexBufferCreator



    //=========================================================================
    //! @function    DirectXVertexBufferCreator::CreateVertexBuffer
    //! @brief       Create a new DirectXVertexBuffer object
    //!              
    //!              
    //! @return      A new DirectXVertexBuffer object, or 
	//!				 a null pointer if the create operation failed
    //=========================================================================
	boost::shared_ptr<Renderer::VertexBuffer> 
		DirectXVertexBufferCreator::CreateVertexBuffer ( size_t vertexSize, 
														 size_t vertexCount, 
														 Renderer::EUsage usage )
	{
		try
		{
			boost::shared_ptr<Renderer::VertexBuffer> buffer( new DirectXVertexBuffer(m_renderer, vertexSize, vertexCount, usage) );

			return buffer;
		}
		catch (Renderer::RendererError& err)
		{
			std::cerr << __FUNCTION__ << " Failed to create vertex buffer: " << err.What() << std::endl;

			return boost::shared_ptr<Renderer::VertexBuffer>();
		}
	}
	//End DirectXVertexBufferCreator::Create


};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_DIRECTXVERTEXBUFFERCREATOR_H
