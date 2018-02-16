//======================================================================================
//! @file         IndexBufferManager.h
//! @brief        Handle based resource manager class for index buffers. Provides a central point
//!				  for the creation, and access of index buffers. 
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

#ifndef RENDERER_INDEXBUFFERMANAGER_H
#define RENDERER_INDEXBUFFERMANAGER_H


#include <boost/noncopyable.hpp>
#include "Core/Restorable.h"
#include "Core/ResourceManager.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/RendererConstants.h"


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declaration
    //=========================================================================
	class IIndexBufferCreator;



	//!@class	IndexBufferManager
	//!@brief	Handle based resource manager class for Index buffers. Provides a central point
	//!			for the creation, and access of Index buffers. 
	class IndexBufferManager : public Core::ResourceManager<IndexBuffer>, 
							   public Core::IRestorable,
							   public boost::noncopyable
	{
		public:

			inline IndexBufferManager ( IIndexBufferCreator& creator );

			//Create Index buffer
			HandleType CreateIndexBuffer( EIndexSize indexSize, size_t indexCount, EUsage usage );

			//IRestorable implementation
			bool RequiresRestore() const;
			void PrepareForRestore( bool forceRestore );
			void Restore( bool forceRestore );
			
		private:

			IIndexBufferCreator* m_creator;

	};
	//End class IndexBufferManager



    //=========================================================================
    //! @function    IndexBufferManager::IndexBufferManager
    //! @brief       Construct a Index buffer manager
    //!              
    //! @param       creator [in] Reference to an object used to create the index buffers
    //!              
    //=========================================================================
	IndexBufferManager::IndexBufferManager ( IIndexBufferCreator& creator  )
		: Core::ResourceManager<IndexBuffer> ( g_maxIndexBuffers ), m_creator(&creator)
	{

	}
	//End IndexBufferManager::IndexBufferManager


/*
    //=========================================================================
    //! @function    IndexBufferManager::SetCreator
    //! @brief       Set the object used to create Index buffers
    //!              
    //! @param       creator [in] A creator object, used to create new Index buffer objects
    //!              
    //=========================================================================
	void IndexBufferManager::SetCreator ( IIndexBufferCreator& creator )
	{
		m_creator = &creator;
	}
	//End IndexBufferManager::SetCreator
*/

};
//end namespace Renderer


#endif
//#ifndef INDEXBUFFERMANAGER_H
