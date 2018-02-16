//======================================================================================
//! @file         RenderQueue.h
//! @brief        Class that queues up IRenderable objects for rendering
//!				  Renderable objects are ordered in the queue, so that state changes are minimised               
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


#ifndef RENDERER_RENDERQUEUE_H
#define RENDERER_RENDERQUEUE_H

#include <list>
#include <boost/pool/pool_alloc.hpp>
#include "Renderer/RenderQueueEntry.h"
#include "Renderer/Effect.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexDeclaration.h"

//=========================================================================
// Forward declaration
//=========================================================================
namespace Math		{  class Matrix4x4; }
namespace Renderer	{  class IRenderer; class IRenderable; class StateManager; class VertexStreamBinding; }



//namespace Renderer
namespace Renderer
{

	
	//!@class	RenderQueue
	//!@brief	Class that queues up IRenderable objects for rendering
	//!			Renderable objects are ordered in such a way to minimise state changes
	class RenderQueue
	{
		public:

			
            //=========================================================================
            // Constructors
            //=========================================================================
			RenderQueue ( StateManager& stateManager, IRenderer& renderer );


            //=========================================================================
            // Public types
            //=========================================================================
			typedef std::list<RenderQueueEntry, boost::fast_pool_allocator<RenderQueueEntry> >	RenderQueueStore; 

            //=========================================================================
            // Public methods
            //=========================================================================
			
			//Must be called at the start of the frame to clear out the queue
			inline void Clear();

			//Add an object to the queue
			inline void QueueForRendering ( IRenderable& renderable, HEffect& effect, UInt techniqueIndex, UInt passIndex,
				                            HVertexDeclaration& decl, VertexStreamBinding& binding, HIndexBuffer& indexBuffer,
											const Math::Matrix4x4& worldMatrix );

			//Sort the queue by render state
			inline void Sort();

			//Render all items in the queue
			void Render();


		private:


			//=========================================================================
            // Private types
            //=========================================================================
			typedef RenderQueueStore::iterator iterator;


            //=========================================================================
            // Private data
            //=========================================================================
			RenderQueueStore		m_queue;
			StateManager&			m_stateManager;
			IRenderer&				m_renderer;

	};		
	//End class RenderQueue


	
	//=========================================================================
	//! @function    RenderQueue::Clear
	//! @brief       Empties the render queue
	//!              
	//=========================================================================
	void RenderQueue::Clear()
	{
		m_queue.clear();
	}
	//End RenderQueue::Clear



	//=========================================================================
	//! @function    RenderQueue::QueueForRendering
	//! @brief       Queue an object to be rendered
	//!
	//!				 Adds a rendering pass of an object to the render queue for later rendering
	//!
	//!
	//! @param		 renderable		[in]	Renderable object to be rendered
	//! @param		 effect			[in]	Effect to render the object with
	//! @param		 techniqueIndex [in]	Index into the effect's techniques
	//! @param		 passIndex		[in]	Index into the technique's passes
	//! @param		 vertexData		[in]	Vertex data of the renderable object
	//! @param		 indexBuffer	[in]	Index buffer of the renderable object
	//! @param		 worldMatrix	[in]	World matrix of the object to be rendered
	//!
	//=========================================================================
	void RenderQueue::QueueForRendering ( IRenderable& renderable, HEffect& effect, UInt techniqueIndex,
										  UInt passIndex,  HVertexDeclaration& decl, VertexStreamBinding& binding,
										  HIndexBuffer& indexBuffer, const Math::Matrix4x4& worldMatrix )
	{
		m_queue.push_back ( RenderQueueEntry(renderable, effect, techniqueIndex, passIndex,
			                decl, binding, indexBuffer, worldMatrix ));
	}
	//End RenderQueue::QueueForRendering



    //=========================================================================
    //! @function    RenderQueue::Sort
    //! @brief       Sorts the queue by render state
    //!              
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	void RenderQueue::Sort()
	{
		#ifdef DEBUG_BUILD
		static Core::ConsoleBool dbg_sortrenderqueue ( "dbg_sortrenderqueue", true );

		if ( !dbg_sortrenderqueue )
		{
			return;
		}

		#endif

		m_queue.sort();

	}
	//End RenderQueue::SortQueue


};
//end namespace Renderer



#endif
//#ifndef RENDERER_RENDERQUEUE_H