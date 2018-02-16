//======================================================================================
//! @file         VertexBufferCreator.h
//! @brief        IVertexBufferCreator interface. Interface for objects that
//!				  instantiate a specific sub-class derived from VertexBuffer
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

#ifndef RENDERER_VERTEXBUFFERCREATOR_H
#define RENDERER_VERTEXBUFFERCREATOR_H


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declarations
    //=========================================================================
	class VertexBuffer;


	//!@class	IVertexBufferCreator
	//!@brief	IVertexBufferCreator interface.
	//!			Interface that instantiates a specific sub-class derived from VertexBuffer
	//!			
	//!			This interface allows the VertexBufferManager to operate, without having
	//!			to know anything about subclasses of VertexBuffer
	class IVertexBufferCreator
	{
		public:

			virtual ~IVertexBufferCreator(){}

			//! Create a vertex buffer
			virtual boost::shared_ptr<VertexBuffer>	CreateVertexBuffer( size_t vertexSize, size_t vertexCount, EUsage usage ) = 0;

	};
	//End IVertexBufferCreator


};
//end namespace Renderer

#endif
//#ifndef VERTEXBUFFERCREATOR_H
