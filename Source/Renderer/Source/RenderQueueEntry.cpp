//======================================================================================
//! @file         RenderQueueEntry.cpp
//! @brief        Entry in the render queue. Allows objects to be sorted by render state
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


#include "Core/Core.h"
#include "Renderer/RenderQueueEntry.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/TextureUnit.h"
#include "Renderer/VertexStreamBinding.h"



using namespace Renderer;




//=========================================================================
//! @function    RenderQueueEntry::RenderQueueEntry
//! @brief       RenderQueueEntry constructor
//!              
//! @param       renderable		[in] Renderable object to be added to the queue 
//! @param       effect			[in] Effect that the object will be rendered with
//! @param       techniqueIndex [in] Technique that the object will be rendered with	
//! @param       passIndex		[in] Index of the render pass
//! @param       decl			[in] Vertex declaration
//! @param		 binding		[in] Vertex stream binding
//! @param       indexBuffer	[in] Index buffer used to render the object	
//!              
//=========================================================================
RenderQueueEntry::RenderQueueEntry ( IRenderable& renderable, HEffect& effect, UInt techniqueIndex, UInt passIndex,
									HVertexDeclaration& decl, VertexStreamBinding& binding, HIndexBuffer& indexBuffer,
									const Math::Matrix4x4& worldMatrix )
:	m_renderable(renderable), 
	m_effect(effect), 
	m_techniqueIndex(techniqueIndex),
	m_passIndex(passIndex),
	m_binding(binding),
	m_vertexDeclaration(decl),
	m_indexBuffer(indexBuffer),
	m_worldMatrix(worldMatrix)
{

	//Check the technique index is in range
	debug_assert ( techniqueIndex < effect->TechniqueCount(), "Technique index out of range" );

	//Check the pass index is in range
	debug_assert ( passIndex < effect->Techniques(techniqueIndex).PassCount(), "Pass index out of range!" );

}
//End RenderQueueEntry::RenderQueueEntry




//=========================================================================
//! @function    RenderQueueEntry::operator <
//! @brief       Compare two render queue entries (for render state sorting purposes)
//!
//=========================================================================
bool RenderQueueEntry::operator < ( const RenderQueueEntry& rhs ) const
{

	//First sort by the technique's sort value
	if ( static_cast<UInt>(m_effect->Techniques(TechniqueIndex()).SortValue())
			< static_cast<UInt>(rhs.m_effect->Techniques(rhs.TechniqueIndex()).SortValue()) )
	{
		return true;
	}

	if ( static_cast<UInt>(m_effect->Techniques(TechniqueIndex()).SortValue())
			> static_cast<UInt>(rhs.m_effect->Techniques(rhs.TechniqueIndex()).SortValue()) )
	{
		return false;
	}

	//Then sort by effect
	if ( m_effect.Value() < rhs.m_effect.Value() )
	{
		return true;
	}

	if ( m_effect.Value() > rhs.m_effect.Value() )
	{	
		return false;
	}	

	//Then sort by technique
	if ( TechniqueIndex() < rhs.TechniqueIndex() )
	{
		return true;
	}

	if ( TechniqueIndex() > rhs.TechniqueIndex() )
	{
		return false;
	}

	//Then sort by pass
	if ( PassIndex() < rhs.PassIndex() )
	{	
		return true;
	}

	if ( PassIndex() > rhs.PassIndex() )
	{
		return false;
	}

	//Then sort by vertex format
	if ( m_vertexDeclaration.Value() < rhs.m_vertexDeclaration.Value() )
	{
		return true;
	}

	if ( m_vertexDeclaration.Value() > rhs.m_vertexDeclaration.Value() )
	{
		return false;
	}

	//Then sort by which buffers are set
	if ( m_binding < rhs.m_binding )
	{
		return true;
	}

	//Then sort by index buffer
	if ( m_indexBuffer.Value() < rhs.m_indexBuffer.Value() )
	{
		return true;
	}

	return false;
	
}
//End RenderQueueEntry::operator < 