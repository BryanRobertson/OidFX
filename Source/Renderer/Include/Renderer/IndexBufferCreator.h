//======================================================================================
//! @file         IndexBufferCreator.h
//! @brief        IIndexBufferCreator interface. Interface for objects that
//!				  instantiate a specific sub-class derived from IndexBuffer
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


#ifndef RENDERER_INDEXBUFFERCREATOR_H
#define RENDERER_INDEXBUFFERCREATOR_H


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declarations
    //=========================================================================
	class IndexBuffer;
	enum  EIndexSize;


	//!@class	IIndexBufferCreator
	//!@brief	IIndexBufferCreator interface.
	//!			Interface that instantiates a specific sub-class derived from IndexBuffer
	//!			
	//!			This interface allows the IndexBufferManager to operate, without having
	//!			to know anything about subclasses of IndexBuffer
	class IIndexBufferCreator
	{
		public:

			virtual ~IIndexBufferCreator(){}

			//! Create a Index buffer
			virtual boost::shared_ptr<IndexBuffer>	CreateIndexBuffer( EIndexSize indexSize, 
																		size_t indexCount, 
																		EUsage usage  ) = 0;

	};
	//End IIndexBufferCreator


};
//end namespace Renderer


#endif
//#ifndef INDEXBUFFERCREATOR_H
