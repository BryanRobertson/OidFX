//======================================================================================
//! @file         VertexBufferManager.h
//! @brief        Handle based resource manager class for vertex buffers. Provides a central point
//!				  for the creation, and access of vertex buffers. 
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

#ifndef RENDERER_VERTEXBUFFERMANAGER_H
#define RENDERER_VERTEXBUFFERMANAGER_H


#include <boost/noncopyable.hpp>
#include "Core/Restorable.h"
#include "Core/ResourceManager.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/RendererConstants.h"


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declaration
    //=========================================================================
	class IVertexBufferCreator;


	//!@class	VertexBufferManager
	//!@brief	Handle based resource manager class for vertex buffers. Provides a central point
	//!			for the creation, and access of vertex buffers. 
	class VertexBufferManager : public Core::ResourceManager<VertexBuffer>, 
								public Core::IRestorable, 
								public boost::noncopyable
	{
		public:

			inline VertexBufferManager ( IVertexBufferCreator& creator );

			//Create vertex buffer
			HandleType CreateVertexBuffer( size_t vertexSize, size_t vertexCount, EUsage usage );

			//IRestorable implementation
			bool RequiresRestore() const;
			void PrepareForRestore( bool forceRestore );
			void Restore( bool forceRestore );
			
		private:

			IVertexBufferCreator* m_creator;

	};
	//End class VertexBufferManager



    //=========================================================================
    //! @function    VertexBufferManager::VertexBufferManager
    //! @brief       Construct a vertex buffer manager
    //!              
    //! @param       creator [in] Reference to an object used to create the vertex buffers
    //!              
    //=========================================================================
	VertexBufferManager::VertexBufferManager ( IVertexBufferCreator& creator )
		: Core::ResourceManager<VertexBuffer> ( g_maxVertexBuffers ), m_creator(&creator)
	{

	}
	//End VertexBufferManager::VertexBufferManager

};
//end namespace Renderer


#endif
//#ifndef VERTEXBUFFERMANAGER_H

