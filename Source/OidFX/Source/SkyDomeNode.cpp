//======================================================================================
//! @file         SkyDomeNode.cpp
//! @brief        Scene graph node representing a sky dome
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 23 July 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================


#include "Core/Core.h"
#include "Math/Matrix4x4.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderQueue.h"
#include "Renderer/EffectManager.h"
#include "OidFX/GameApplication.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/Scene.h"
#include "OidFX/Camera.h"
#include "OidFX/SkyDomeNode.h"


using namespace OidFX;




//=========================================================================
//! @function    SkyDomeNode::SkyDomeNode
//! @brief       SkyDomeNode constructor
//!              
//! @param		 scene				[in] Scene that this node belongs to
//! @param       planetRadius		[in] Radius of the planet
//! @param       atmosphereRadius	[in] Radius of the atmosphere
//! @param       divisions			[in] Number of divisions for the sky plane
//! @param       effectFileName		[in] Filename of the effect to use
//! @param       effectManager		[in] Effect manager to get the effect from
//!              
//! @return      
//! @throw       
//=========================================================================
SkyDomeNode::SkyDomeNode ( Scene& scene, Float planetRadius, Float atmosphereRadius, UInt divisions,
							const Char* effectFileName, Renderer::EffectManager& effectManager )
:   SceneNode(scene, NODETYPE_SKY, Math::Matrix4x4::IdentityMatrix , Math::Matrix4x4::IdentityMatrix ),
	m_planetRadius(planetRadius), 
	m_atmosphereRadius(atmosphereRadius), 
	m_divisions(divisions)
{
	if ( m_divisions < 1 )
	{
		m_divisions = 1;
	}	

	if ( m_divisions > 255 )
	{
		m_divisions = 255;
	}

	CreateSkyVertexBuffer();
	FillSkyVertexBuffer();
	CreateSkyIndexBuffer();
	FillSkyIndexBuffer();

	m_effect = effectManager.AcquireEffect(effectFileName);
}
//End SkyDomeNode::SkyDomeNode



//=========================================================================
//! @function    SkyDomeNode::Restore
//! @brief       Restore all buffers after a renderer restore
//=========================================================================
void SkyDomeNode::Restore ()
{

	FillSkyVertexBuffer();
	FillSkyIndexBuffer();

}
//End SkyDomeNode::Restore



//=========================================================================
//! @function    SkyDomeNode::QueueForRendering
//! @brief       Add the sky dome node to the render queue
//!              
//! @param       queue [in] Render queue to add the node to
//!              
//=========================================================================
void SkyDomeNode::QueueForRendering ( Renderer::RenderQueue& queue )
{
	debug_assert ( !m_effect.IsNull(), "Sky effect is null!" );
	debug_assert ( m_effect->TechniqueCount() != 0, "Effect has no techniques!" );

	for ( UInt passIndex = 0; passIndex < m_effect->Techniques(0).PassCount(); ++passIndex )
	{
		queue.QueueForRendering ( *this, m_effect, 0, passIndex, 
									m_vertexDeclaration, m_vertexStreamBinding, m_indexBuffer, m_objectToWorld );
	}
}
//End SkyDomeNode::QueueForRendering


//=========================================================================
//! @function    SkyDomeNode::Render
//! @brief       Render the sky dome
//!              
//!              
//! @param       renderer [in] Renderer to use to render the sky dome
//!              
//=========================================================================
void SkyDomeNode::Render ( Renderer::IRenderer& renderer )
{
	
	const UInt verticesPerRow = m_divisions + 1;
	const UInt indicesPerStrip = verticesPerRow * 2;
	const UInt numberOfStrips = verticesPerRow - 1;
	const UInt totalDegenerateIndices = (2 * numberOfStrips) - 2;

	renderer.DrawIndexedPrimitive ( Renderer::PRIM_TRIANGLESTRIP, 
									0,
									m_vertexStreamBinding.GetStream(0)->VertexCount(),
									0,
									indicesPerStrip * numberOfStrips
									+ totalDegenerateIndices );
}
//End SkyDomeNode::Render



//=========================================================================
//! @function    SkyDomeNode::FillVisibleObjectList
//! @brief       Add the skydome to the visible object list
//!
//!				 The sky dome is always visible, so it will always be
//!				 added to the visible object list
//!
//!				 In addition to adding the dome to the visible object list,
//!				 the position of the sky dome is updated, using the position of the camera
//!              
//! @param       visibleObjectList 
//! @param       camera 
//!              
//! @return      
//! @throw       
//=========================================================================
void SkyDomeNode::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera )
{
	//Skydome is always visible
	visibleObjectList.AddObject ( *this );

	//Update the skydome position from the camera position
	m_objectToWorld.Identity();
	m_objectToWorld.Translate ( camera.GetPosition() );
	m_objectToWorld.Translate ( Math::Vector3D ( 0.0f, 500.0f, 0.0f ) );

	//We won't bother updating the object from world matrix
}
//End SkyDomeNode::FillVisibleObjectList



//=========================================================================
//! @function    SkyDomeNode::CreateSkyVertexBuffer
//! @brief       Create the vertex buffer for the sky dome
//=========================================================================
void SkyDomeNode::CreateSkyVertexBuffer()
{
	const UInt numVertices = (m_divisions + 1) * (m_divisions + 1);

	
	Renderer::VertexDeclarationDescriptor descriptor;

	descriptor.AddElement ( 0, 0, Renderer::DECLTYPE_FLOAT3, Renderer::DECLUSAGE_POSITION, 0 ); 
	descriptor.AddElement ( 0, 12, Renderer::DECLTYPE_COLOUR, Renderer::DECLUSAGE_DIFFUSE, 0 );
	descriptor.AddElement ( 0, 16, Renderer::DECLTYPE_FLOAT2, Renderer::DECLUSAGE_TEXCOORD, 0 ); 

	m_vertexDeclaration = m_scene.Application().GetRenderer().AcquireVertexDeclaration( descriptor );

	Renderer::HVertexBuffer chunkBuffer = 
				m_scene.Application().GetRenderer().CreateVertexBuffer
							( sizeof(SkyVertex), 
							  numVertices, 
							  Renderer::USAGE_STATICWRITEONLY );

	if ( !chunkBuffer )
	{
		throw Core::RuntimeError ( "Couldn't create sky dome vertex buffer!", 
									0, __FILE__, __FUNCTION__, __LINE__ );
	}
	else
	{
		m_vertexStreamBinding.SetStream ( chunkBuffer, 0 );
	}

}
//End SkyDomeNode::CreateSkyVertexBuffer



//=========================================================================
//! @function    SkyDomeNode::CreateSkyIndexBuffer
//! @brief       Create the index buffer for the sky dome
//=========================================================================
void SkyDomeNode::CreateSkyIndexBuffer ()
{
	
	//Create the indexbuffer
	const UInt verticesPerRow = m_divisions + 1;
	const UInt indicesPerStrip = verticesPerRow * 2;
	const UInt numberOfStrips = verticesPerRow - 1;

	//Subtract two because the last strip doesn't have any degenerate triangles
	const UInt totalDegenerateIndices = (2 * numberOfStrips) - 2;
	
	m_indexBuffer = m_scene.Application().GetRenderer().CreateIndexBuffer ( Renderer::INDEX_16BIT, 
																			(indicesPerStrip * numberOfStrips)
																			+ totalDegenerateIndices,
																			Renderer::USAGE_STATICWRITEONLY );

	if ( !m_indexBuffer )
	{
		throw Core::RuntimeError ( "Couldn't create sky dome index buffer!" , 0, __FILE__, __FUNCTION__, __LINE__ );
	}

}
//End SkyDomeNode::CreateSkyIndexBuffer


//=========================================================================
//! @function    SkyDomeNode::FillSkyVertexBuffer
//! @brief       Fill the sky dome vertex buffer
//=========================================================================
void SkyDomeNode::FillSkyVertexBuffer()
{
	using namespace Renderer;

	ScopedVertexBufferLock vLock = m_vertexStreamBinding.GetStream(0)->LockAll(LOCK_NORMAL);

	if ( !vLock )
	{
		throw Core::RuntimeError ( "Couldn't lock sky vertex buffer!", 0, __FILE__,
									__FUNCTION__, __LINE__ );
	}

	Float planeSize = 2.0f * Math::Sqrt(((m_atmosphereRadius * m_atmosphereRadius)
											-(m_planetRadius * m_planetRadius)));

	Float planeDelta = planeSize / static_cast<Float>(m_divisions);

	Float texCoordDelta = 2.0f / static_cast<Float>(m_divisions);


	//Variables used during the dome generation
	Float xDist = 0.0f;
	Float zDist = 0.0f;
	Float xHeight = 0.0f;
	Float zHeight = 0.0f;
	Float height = 0.0f;

	SkyVertex* vertex = reinterpret_cast<SkyVertex*>(vLock.GetLockPointer());

	for ( UInt row=0; row <= m_divisions; ++row )
	{
		for ( UInt col=0; col <= m_divisions; ++col )
		{
			xDist = ( -0.5f * planeSize ) + static_cast<Float>(col) * planeDelta;
			zDist = ( -0.5f * planeSize ) + static_cast<Float>(row) * planeDelta;

			xHeight = (xDist * xDist) / m_atmosphereRadius;
			zHeight = (zDist * zDist) / m_atmosphereRadius;

			height = xHeight + zHeight;

			vertex->position[0] = xDist;
			vertex->position[1] = 1.0f - height;
			vertex->position[2] = zDist;

			vertex->texCoord0[0] = static_cast<Float>(col) * texCoordDelta * 0.5f;
			vertex->texCoord0[1] = 1.0f - static_cast<Float>(row) * texCoordDelta * 0.5f;

			vertex->colour = Colour4f ( 1.0f, 1.0f, 1.0f, 1.0f);

			++vertex;
		}
	}

}
//End SkyDomeNode::FillSkyVertexBuffer


//=========================================================================
//! @function    SkyDomeNode::FillSkyIndexBuffer
//! @brief       Fill the sky dome index buffer
//!              
//!              
//=========================================================================
void SkyDomeNode::FillSkyIndexBuffer ()
{
	using namespace Renderer;

	//Fill the index buffer
	ScopedIndexBufferLock iLock = m_indexBuffer->LockAll(LOCK_NORMAL);
	
	UShort* indexPtr = reinterpret_cast<UShort*>(iLock.GetLockPointer());
	UInt rowCount = m_divisions;
	UInt colCount = rowCount;

	UInt currentIndex = 0;
	UInt startVertex = 0;

	for ( UInt row = 0; row < rowCount; ++row )
	{
		currentIndex = startVertex;

		//Create a triangle strip for the row
		for ( UInt col = 0; col < colCount; ++col )
		{
			*(indexPtr++) = currentIndex;
			*(indexPtr++) = currentIndex + m_divisions + 1;

			++currentIndex;
		}

		startVertex += m_divisions + 1;

		//Create a degenerate triangle to link this triangle
		//to the previous row (unless this is the last row)
		if ( (row + 1) < rowCount )
		{
			*(indexPtr++) = (currentIndex - 1) + m_divisions + 1;
			*(indexPtr++) = startVertex;
		}
		
	}

}
//End SkyDomeNode::FillSkyIndexBuffer