//======================================================================================
//! @file         VertexStreamBinding.h
//! @brief        Class representing a set of vertex buffers bound to stream indices
//!              
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 12 June 2005
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

#ifndef RENDERER_VERTEXSTREAMBINDING_H
#define RENDERER_VERTEXSTREAMBINDING_H


#include "Renderer/VertexBuffer.h"
#include "Renderer/RendererConstants.h"



//namespace Renderer
namespace Renderer
{

    //=========================================================================
    // Forward declaration
    //=========================================================================
	class IRenderer;



	//!@class	VertexStreamBinding
	//!@brief	Class representing a set of vertex buffers bound to stream indices
	class VertexStreamBinding
	{

		public:

			//Set one of the streams
			inline void SetStream ( HVertexBuffer& buffer, UInt streamIndex ) throw();
			inline HVertexBuffer GetStream ( UInt streamIndex ) const throw();

			void Bind ( IRenderer& renderer );

			bool operator < ( const VertexStreamBinding& rhs ) const;

		private:

			HVertexBuffer m_bindings[Renderer::g_maxStreams];

	};
	//end class VertexStreamBinding



    //=========================================================================
    //! @function    VertexStreamBinding::SetStream
    //! @brief       Set one of the vertex stream binding's internal streams
	//!				 streamIndex must be less than g_maxStreams @see RendererConstants.h
    //!              
    //! @param       buffer		 [in] Handle to the buffer to set to the stream
    //! @param       streamIndex [in] Stream index
    //=========================================================================
	void VertexStreamBinding::SetStream ( HVertexBuffer& buffer, UInt streamIndex )
	{
		debug_assert ( streamIndex < Renderer::g_maxStreams, "Stream index out of bounds!" );

		m_bindings[streamIndex] = buffer;
	}
	//End VertexStreamBinding::SetStream


    //=========================================================================
    //! @function    VertexStreamBinding::GetStream
    //! @brief       Get the stream bound to a stream index 
	//!				 streamIndex must be less than g_maxStreams @see RendererConstants.h
    //!              
    //! @param       streamIndex [in] Stream index
    //!              
    //! @return      A handle to the vertex buffer, this will be a null handle
	//!				 if no buffer has been bound at this index       
    //=========================================================================
	HVertexBuffer VertexStreamBinding::GetStream ( UInt streamIndex ) const
	{
		debug_assert ( streamIndex < Renderer::g_maxStreams, "Stream index out of bounds!" );

		return m_bindings[streamIndex];
	}
	//End VertexStreamBinding::GetStream


};
//end namespace Renderer



#endif
//#ifndef VERTEXSTREAMBINDING_H