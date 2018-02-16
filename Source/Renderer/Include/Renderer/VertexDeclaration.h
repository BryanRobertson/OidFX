//======================================================================================
//! @file         VertexDeclaration.h
//! @brief        Base class for objects describing the formats for a set of vertex buffers
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


#ifndef RENDERER_VERTEXDECLARATION_H
#define RENDERER_VERTEXDECLARATION_H



#include "Core/Handle.h"
#include "Renderer/VertexElement.h"
#include "Renderer/VertexDeclarationDescriptor.h"



//namespace Renderer
namespace Renderer
{


	//!@class	VertexDeclaration
	//!@brief	Base class for objects describing the format for a set of vertex buffers
	class VertexDeclaration
	{
		public:

			inline VertexDeclaration( const VertexDeclarationDescriptor& descriptor );
			virtual ~VertexDeclaration() {}

			//Friends
			friend class Core::ResourceManager;

			//! Bind the vertex declaration as a renderer's current declaration
			//! Called automatically by the renderer's bind method 
			virtual bool Bind() = 0;

			// Get the descriptor
			inline const VertexDeclarationDescriptor& Descriptor() const;

			// Methods to make the declaration compatible with the resource manager class.
			// TODO: Revisit the ResourceManager, and make it more generic, to remove the need
			// for this
			UInt ID ( )							{ return m_desc.Checksum(); }	
			UInt ReferenceCount ( ) const		{ return m_referenceCount;	}
			std::string Name ( ) const			{ return "VertexDeclaration"; }

		protected:

            //=========================================================================
            // Private methods
            //=========================================================================
			inline UInt IncrementReferenceCount ( )		{ return ++m_referenceCount;	}
			inline UInt DecrementReferenceCount ( )		{ return --m_referenceCount;	}
		

            //=========================================================================
            // Private data
            //=========================================================================
			VertexDeclarationDescriptor m_desc;
			UInt						m_referenceCount;

	};
	//end class VertexDeclaration



    //=========================================================================
    // Typedefs
    //=========================================================================
	typedef Core::Handle<VertexDeclaration>	HVertexDeclaration;



    //=========================================================================
    //! @function    VertexDeclaration::VertexDeclaration
    //! @brief       VertexDeclaration constructor
    //!              
	//! @param		 descriptor [in]	Object describing the vertex declaration format
    //=========================================================================
	VertexDeclaration::VertexDeclaration( const VertexDeclarationDescriptor& descriptor )
		: m_desc(descriptor), m_referenceCount(1)
	{
	}
	//End VertexDeclaration::VertexDeclaration


    //=========================================================================
    //! @function    VertexDeclaration::VertexDeclarationDescriptor
    //! @brief       Return a reference to the vertex declaration descriptor
	//!
	//!				 The descriptor describes the format used in the vertex declaration
    //!              
    //! @return      A reference to the vertex declaration descriptor
    //=========================================================================
	const VertexDeclarationDescriptor& VertexDeclaration::Descriptor() const
	{
		return m_desc;
	}
	//End VertexDeclaration::VertexDeclarationDescriptor 



}
//end namespace Renderer


#endif
//#ifndef VERTEXDECLARATION_H