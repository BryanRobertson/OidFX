//======================================================================================
//! @file         DirectXIndexBufferCreator.h
//! @brief        Implementation of the IIndexBufferCreator interface that creates
//!               DirectXIndexBuffer objects
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

#ifndef DIRECTX9RENDERER_DIRECTXINDEXBUFFERCREATOR_H
#define DIRECTX9RENDERER_DIRECTXINDEXBUFFERCREATOR_H


#include <boost/shared_ptr.hpp>
#include "Renderer/IndexBufferCreator.h"
#include "DirectX9Renderer/DirectXIndexBuffer.h"


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


    //=========================================================================
    // Forward declarations
    //=========================================================================
	class DirectXRenderer;



	//!@class	DirectXIndexBufferCreator
	//!@brief	Implementation of the IIndexBufferCreator interface that creates
	//!         DirectXIndexBuffer objects
	class DirectXIndexBufferCreator : public Renderer::IIndexBufferCreator
	{
		public:

			inline DirectXIndexBufferCreator ( DirectXRenderer& renderer );

			boost::shared_ptr<Renderer::IndexBuffer> CreateIndexBuffer(  Renderer::EIndexSize indexSize, 
																		 size_t indexCount, 
																		 Renderer::EUsage usage );

		private:

			DirectXRenderer& m_renderer;

	};
	//End DirectXIndexBufferCreator



    //=========================================================================
    //! @function    DirectXIndexBufferCreator::DirectXIndexBufferCreator
    //! @brief       Initialise the DirectXIndexBufferCreator
    //!              
    //! @param       renderer [in] Renderer object that the creator belongs to
    //!              
    //=========================================================================
	DirectXIndexBufferCreator::DirectXIndexBufferCreator ( DirectXRenderer& renderer )
		: m_renderer(renderer)
	{

	}
	//End DirectXIndexBufferCreator::DirectXIndexBufferCreator



    //=========================================================================
    //! @function    DirectXIndexBufferCreator::CreateIndexBuffer
    //! @brief       Create a new DirectXIndexBuffer object
    //!              
    //!              
    //! @return      A new DirectXIndexBuffer object, or 
	//!				 a null pointer if the create operation failed
    //=========================================================================
	boost::shared_ptr<Renderer::IndexBuffer> 
		DirectXIndexBufferCreator::CreateIndexBuffer (  Renderer::EIndexSize indexSize, 
														size_t indexCount,
														Renderer::EUsage usage )
	{
		try
		{
			boost::shared_ptr<Renderer::IndexBuffer> buffer( new DirectXIndexBuffer(m_renderer,  indexSize, indexCount, usage) );

			return buffer;
		}
		catch (Renderer::RendererError& err)
		{
			std::cerr << __FUNCTION__ << " Failed to create Index buffer: " << err.What() << std::endl;

			return boost::shared_ptr<Renderer::IndexBuffer>();
		}
	}
	//End DirectXIndexBufferCreator::Create


};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_DIRECTXINDEXBUFFERCREATOR_H
