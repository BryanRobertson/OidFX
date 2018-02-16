//======================================================================================
//! @file         RenderQueueEntry.h
//! @brief        Entry in the render queue. Allows renderable object to be sorted by state
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 29 June 2005
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


#ifndef RENDERER_RENDERQUEUE_ENTRY_H
#define RENDERER_RENDERQUEUE_ENTRY_H


#include "Renderer/Renderable.h"
#include "Renderer/Effect.h"
#include "Renderer/RenderState.h"
#include "Renderer/Technique.h"
#include "Renderer/Pass.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexData.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/VertexStreamBinding.h"
#include "Renderer/RendererConstants.h"


//=========================================================================
// Forward declaration
//=========================================================================
namespace Math		{	class Matrix4x4;	}
namespace Renderer	{	class VertexData;	}



//namespace Renderer
namespace Renderer
{


	//!@class	RenderQueueEntry
	//!@brief	Class representing an entry in the render queue 
	class RenderQueueEntry
	{
		public:


            //=========================================================================
            // Constructor
            //=========================================================================
			RenderQueueEntry( IRenderable& renderable, HEffect& effect, UInt techniqueIndex, UInt passIndex,
				              HVertexDeclaration& decl, VertexStreamBinding& binding, HIndexBuffer& indexBuffer,
							  const Math::Matrix4x4& worldMatrix );


            //=========================================================================
            // Public methods
            //=========================================================================
			inline HVertexDeclaration	GetVertexDeclaration  () throw(); 
			inline HVertexBuffer		GetStream( UInt index ) throw();
			inline HIndexBuffer			GetIndexBuffer () throw();

			inline VertexStreamBinding& GetStreamBinding() throw() { return m_binding;	}

			inline IRenderable&	 GetRenderable () throw()	{ return m_renderable;		}

			HEffect& GetEffect ( ) throw()					{ return m_effect;			}
			UInt     TechniqueIndex ( ) const throw()		{ return m_techniqueIndex;	}
			UInt     PassIndex ( ) const throw()			{ return m_passIndex;		}
			
			const Math::Matrix4x4& GetWorldMatrix() const throw()	{ return m_worldMatrix;	}
			
			


            //=========================================================================
            // Operator overloads
            //=========================================================================
			
			//Operator <, used for sorting
			bool operator < ( const RenderQueueEntry& rhs ) const;

		private:


            //=========================================================================
            // Private data
            //=========================================================================
			IRenderable&	m_renderable;
			HEffect			m_effect;
			UInt			m_techniqueIndex;
			UInt			m_passIndex;

			HVertexDeclaration			  m_vertexDeclaration;
			VertexStreamBinding&		  m_binding;
			HIndexBuffer				  m_indexBuffer;

			const Math::Matrix4x4&		  m_worldMatrix;
			
	};
	//End class RenderQueueEntry



    //=========================================================================
    //! @function    RenderQueueEntry::GetVertexDeclaration
    //! @brief       Return a pointer to the vertex declaration
    //!              
    //! @return      A handle to the vertex declaration
    //=========================================================================
	HVertexDeclaration RenderQueueEntry::GetVertexDeclaration ( )
	{
		return m_vertexDeclaration;
	}
	//End RenderQueueEntry::GetVertexData


    //=========================================================================
    //! @function    RenderQueueEntry::GetIndexBuffer
    //! @brief       Return a handle to the index buffer
    //!              
    //!              
    //! @return      A handle to the index buffer
    //=========================================================================
	HIndexBuffer RenderQueueEntry::GetIndexBuffer () 
	{
		return m_indexBuffer;
	}
	//End RenderQueueEntry::GetIndexBuffer


    //=========================================================================
    //! @function    RenderQueueEntry::GetStream
    //! @brief       Return one of the vertex streams
    //!              
    //! @return      A handle to one of the vertex buffers
    //=========================================================================
	HVertexBuffer RenderQueueEntry::GetStream ( UInt index )
	{
		return m_binding.GetStream(index);
	}
	//End RenderQueueEntry::GetStream


}
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERQUEUE_ENTRY_H