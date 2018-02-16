//======================================================================================
//! @file         RenderQueue.cpp
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

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderQueue.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Effect.h"
#include "Renderer/StateManager.h"
#include <algorithm>


using namespace Renderer;



//=========================================================================
//! @function    RenderQueue::RenderQueue
//! @brief       RenderQueue constructor
//!              
//! @param		 stateManager [in] 
//!	@param		 renderer	  [in] Reference to the renderer
//!
//=========================================================================
RenderQueue::RenderQueue ( StateManager& stateManager, IRenderer& renderer )
: m_stateManager(stateManager), m_renderer(renderer)
{
}
//End RenderQueue::RenderQueue



//=========================================================================
//! @function    RenderQueue::Render
//! @brief       Render all objects in the queue
//!              
//=========================================================================
void RenderQueue::Render ()
{
	iterator current = m_queue.begin();
	iterator end = m_queue.end();

	#if 0
	std::clog << "\nBegin frame: " << std::endl;
	#endif

	for ( ; current != end; ++current )
	{
		m_stateManager.ActivateIndexBuffer ( current->GetIndexBuffer() );
		m_stateManager.ActivateVertexStreamBinding ( current->GetStreamBinding() );
		m_stateManager.ActivateVertexDeclaration ( current->GetVertexDeclaration() );
		m_stateManager.ActivateRenderState ( current->GetEffect(), current->TechniqueIndex(), current->PassIndex() );

		static Math::Matrix4x4 world;
		m_renderer.GetMatrix ( Renderer::MAT_WORLD, world );

		if ( !(world == current->GetWorldMatrix()) )
		{
			m_renderer.SetMatrix ( Renderer::MAT_WORLD, current->GetWorldMatrix() );
		}

		current->GetRenderable().Render ( m_renderer );
	}

	#if 0
	std::clog << "End frame:\n" << std::endl;
	#endif

}
//End RenderQueue::Render