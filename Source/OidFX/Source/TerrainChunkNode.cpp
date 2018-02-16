//======================================================================================
//! @file         TerrainChunkNode.h
//! @brief        Scene graph node representing a single chunk of terrain
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 16 July 2005
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
#include "Math/IntersectionTests.h"
#include "Math/ParametricLine3D.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderQueue.h"
#include "OidFX/GameApplication.h"
#include "OidFX/Scene.h"
#include "OidFX/TerrainNode.h"
#include "OidFX/TerrainChunkNode.h"
#include "OidFX/EntityNode.h"



using namespace OidFX;




//=========================================================================
// Static initialisation
//=========================================================================
UInt TerrainChunkNode::ms_nodesRendered = 0;


//=========================================================================
//! @function    TerrainChunkNode::TerrainChunkNode
//! @brief       TerrainChunkNode constructor
//!              
//! @param       scene			[in] Reference to the scene
//! @param       terrainNode	[in] Terrain node that owns this chunk	
//! @param       chunkRow		[in] Row position of this chunk in the terrain node's chunk list
//! @param       chunkColumn	[in] Column position of this chunk in the terrain node's chunk list	
//! @param       indexBuffer	[in] Handle to the shared index buffer used to draw all terrain chunks	
//! @param       effect			[in] Handle to the shared effect used to draw all terrain chunks	
//!              
//! @return      
//! @throw       
//=========================================================================
TerrainChunkNode::TerrainChunkNode ( Scene& scene, 
									 const Math::Matrix4x4& toWorld,
									 const Math::Matrix4x4& fromWorld,
									 TerrainNode& terrainNode, 
									 UInt chunkRow, 
									 UInt chunkColumn,
									 Renderer::HIndexBuffer indexBuffer,
									 Renderer::HEffect effect )
	:	
		SceneObject(scene, NODETYPE_WORLD, toWorld, fromWorld ), 
		m_terrainNode(terrainNode), 
		m_chunkRow(chunkRow),
		m_chunkColumn(chunkColumn),
		m_indexBuffer(indexBuffer),
		m_effect(effect)
{

	std::clog << __FUNCTION__ ": Creating Terrain chunk " << chunkRow << "," << chunkColumn << std::endl;

	BuildVertexList();
	//SmoothTerrainHeights();
	CalculateNormals();
	CalculateBoundingBox();
	BuildCollisionMesh();

	m_collisionVolume = m_scene.GetCollisionManager().CreateTreeCollision( m_collisionMesh.triangles );

	CreateChunkVertexBuffer();
	FillChunkVertexBuffer();

}
//End TerrainChunkNode::TerrainChunkNode



//=========================================================================
//! @function    TerrainChunkNode::Update
//! @brief       Updates the terrain chunk and all children
//!            
//!				 Essentially identical to the base class Update method,
//!				 except that it clears the count of nodes rendered.
//!				 (we keep a count of the number of nodes rendered this frame for
//!				 debugging purposes)
//!              
//! @param       toWorldStack		  [in] Matrix stack for the toWorld transform
//! @param		 fromWorldStack		  [in] Matrix stack for the fromWorld transform
//! @param       timeElapsedInSeconds [in] Time elapsed since last update
//!              
//=========================================================================
void TerrainChunkNode::Update ( Math::MatrixStack& toWorldStack, 
							   Math::MatrixStack& fromWorldStack, 
							   Float timeElapsedInSeconds )
{

	ms_nodesRendered = 0; 
	
	//Terrain does not have child nodes
	//SceneObject::Update(toWorldStack, fromWorldStack, timeElapsedInSeconds);

}
//End TerrainChunkNode::Update



//=========================================================================
//! @function    TerrainChunkNode::Restore
//! @brief       Restore any lost resources, after a renderer restore
//!              
//=========================================================================
void TerrainChunkNode::Restore ()
{
	std::clog << __FUNCTION__ << ": Restoring terrain chunk " 
			 << m_chunkRow << ", " << m_chunkColumn << std::endl;

	FillChunkVertexBuffer();
	
	//Call the base class restore to propagate the restore down to childrern
	SceneNode::Restore();
}
//End TerrainChunkNode::Restore



//=========================================================================
//! @function    TerrainChunkNode::QueueForRendering
//! @brief       Add the terrain chunk to the render queue
//!              
//! @param       queue [in]	Render queue to add the chunk to
//!              
//=========================================================================
void TerrainChunkNode::QueueForRendering ( Renderer::RenderQueue& queue )
{
	debug_assert ( !m_effect.IsNull(), "Terrain effect is null!" );
	debug_assert ( m_effect->TechniqueCount() != 0, "Effect has no techniques!" );

	++ms_nodesRendered;

	UInt techniqueIndex = m_effect->GetBestTechniqueForLOD(m_lodLevel);

	for ( UInt passIndex = 0; passIndex < m_effect->Techniques(techniqueIndex).PassCount(); ++passIndex )
	{
		queue.QueueForRendering ( *this, m_effect, techniqueIndex, passIndex, m_vertexDeclaration, 
									m_vertexStreamBinding, m_indexBuffer, m_concatObjectToWorld );
	}
}
//End TerrainChunkNode::QueueForRendering



//=========================================================================
//! @function    TerrainChunkNode::Render
//! @brief       Render the terrain chunk
//!              
//! @param       renderer [in] Renderer to draw the terrain chunk with
//!              
//=========================================================================
void TerrainChunkNode::Render ( Renderer::IRenderer& renderer )
{
	const UInt chunkSize = m_terrainNode.ChunkSize();

	renderer.DrawIndexedPrimitive ( Renderer::PRIM_TRIANGLELIST, 
									0,
									chunkSize * chunkSize,
									m_terrainNode.GetLODInfo(m_lodLevel).startIndex,
									m_terrainNode.GetLODInfo(m_lodLevel).indexCount );
}
//End TerrainChunkNode::Render



//=========================================================================
//! @function    TerrainChunkNode::BuildVertexList
//! @brief       Build the list of vertices for the terrain
//!              
//=========================================================================
void TerrainChunkNode::BuildVertexList  ( )
{
	
	//Width/Height of the terrain in the world
	const Float terrainSize = m_terrainNode.TerrainSize();

	//Width/Height of a single chunk, in vertices
	const UInt chunkSize = m_terrainNode.ChunkSize();

	//Width/Height of the heightmap, in vertices
	const UInt heightmapSize = m_terrainNode.HeightmapSize();

	//Amount to increment the position and tex coords, while iterating through the loop
	const Float positionIncrement = terrainSize / static_cast<Float>(heightmapSize - 1);
	const Float texCoord0Increment = 1.0f / static_cast<Float>( chunkSize );

	//The second set of texture coordinates interpolates from 0 to 1 over the entire 
	//terrain, rather than over a single chunk
	const Float texCoord1Increment = 1.0f / static_cast<Float>( heightmapSize - 1);
	const Float texCoord1StartU	   = texCoord1Increment * (chunkSize - 1)
									* static_cast<Float>(m_chunkColumn);
	const Float texCoord1StartV	   = texCoord1Increment * (chunkSize - 1)
									* static_cast<Float>(m_chunkRow);

	//Starting x and y position for the vertices of this terrain chunk
	const Float positionStartX = positionIncrement * (chunkSize - 1) 
								* static_cast<Float>(m_chunkColumn);

	const Float positionStartZ = positionIncrement * (chunkSize - 1) 
								* static_cast<Float>(m_chunkRow);

	//Variables which change as we iterate through the terrain
	Float positionX = positionStartX;
	Float positionZ = positionStartZ;
	Float texCoord0U = 0.0f;
	Float texCoord0V = 0.0f;
	Float texCoord1U = texCoord1StartU;
	Float texCoord1V = texCoord1StartV;
	
	//Now build the list of vertices
	for ( UInt row = 0; row < chunkSize; ++row )
	{
		positionX = positionStartX;
	

		for ( UInt col = 0; col < chunkSize; ++col )
		{
			TerrainMeshVertex vertex;
			
			vertex.position.Set( positionX, 
								 m_terrainNode.HeightMapValueAt(row + ((chunkSize-1) * m_chunkRow), 
															    col + ((chunkSize-1) * m_chunkColumn)), 
								 positionZ );

			vertex.colour.Set (1.0f, 1.0f, 1.0f, 1.0f);
			vertex.texCoord0.Set ( texCoord0U, texCoord0V, 0.0f );
			vertex.texCoord1.Set ( texCoord1U, texCoord1V, 0.0f );

			m_collisionMesh.vertices.push_back(vertex);

			texCoord0U += texCoord0Increment;
			texCoord1U += texCoord1Increment;
			positionX += positionIncrement;
		}

		texCoord0U = 0.0f;
		texCoord0V += texCoord0Increment;

		texCoord1U = texCoord1StartU;
		texCoord1V += texCoord1Increment;
		
		positionZ += positionIncrement;
	}
}
//End  TerrainChunkNode::BuildVertexList



//=========================================================================
//! @function    TerrainChunkNode::SmoothTerrainHeights
//! @brief       Smooth the terrain out by averaging heights with neighbouring
//!              vertices
//=========================================================================
void TerrainChunkNode::SmoothTerrainHeights ( )
{

	
}
//End TerrainChunkNode::SmoothTerrainHeights



//=========================================================================
//! @function    TerrainChunkNode::CalculateNormals
//! @brief       Calculate normals for the terrain
//!
//!				 For details on the implementation, see the article 
//!				 "Fast Heightfield Normal Calculation" in Game Programming Gems 3
//!              
//=========================================================================
void TerrainChunkNode::CalculateNormals ( )
{
	const UInt chunkSize = m_terrainNode.ChunkSize();

	Math::Vector3D normal;

	for ( UInt row = 0; row < chunkSize; ++row )
	{
		for ( UInt col = 0; col < chunkSize; ++col )
		{
			Float h1 = 0.0f;
			Float h2 = 0.0f;
			Float h3 = 0.0f;
			Float h4 = 0.0f;

			//Get the surrounding height values, if they exist
			if ( (col + 1) < chunkSize )
			{
				h1 = m_terrainNode.HeightMapValueAt(row + ((chunkSize-1) * m_chunkRow), 
													(col+1) + ((chunkSize-1) * m_chunkColumn));
			}

			if ( (row + 1) < chunkSize )
			{
				h2 = m_terrainNode.HeightMapValueAt((row+1) + ((chunkSize-1) * m_chunkRow), 
													(col) + ((chunkSize-1) * m_chunkColumn));
			}

			if ( col > 0 )
			{
				h3 = m_terrainNode.HeightMapValueAt((row) + ((chunkSize-1) * m_chunkRow), 
													(col-1) + ((chunkSize-1) * m_chunkColumn));
			}

			if ( row > 0 )
			{
				h4 = m_terrainNode.HeightMapValueAt((row-1) + ((chunkSize-1) * m_chunkRow), 
													(col) + ((chunkSize-1) * m_chunkColumn));
			}

			m_collisionMesh.vertices[(row * chunkSize) + col].normal.Set((h3-h1), (h4-h2), 2.0f);
			m_collisionMesh.vertices[(row * chunkSize) + col].normal.Normalise();
		}
	}

}
//End TerrainChunkNode::CalculateNormals



//=========================================================================
//! @function    TerrainChunkNode:CalculateBoundingBox
//! @brief       Calculate the bounding box from the terrain's vertices
//=========================================================================
void TerrainChunkNode::CalculateBoundingBox ( )
{
	debug_assert ( !m_collisionMesh.vertices.empty(), "No vertices!" );

	CollisionMesh::VertexStore::const_iterator itr = m_collisionMesh.vertices.begin();
	CollisionMesh::VertexStore::const_iterator end = m_collisionMesh.vertices.end();

	Math::Vector3D max = itr->position;
	Math::Vector3D min = itr->position;

	for ( ++itr; itr != end; ++itr )
	{
		
		if ( itr->position.X() > max.X() )
			max.X( itr->position.X() );

		if ( itr->position.X() < min.X() )
			min.X( itr->position.X() );

		if ( itr->position.Y() > max.Y() )
			max.Y( itr->position.Y() );

		if ( itr->position.Y() < min.Y() )
			min.Y( itr->position.Y() );

		if ( itr->position.Z() > max.Z() )
			max.Z( itr->position.Z() );

		if ( itr->position.Z() < min.Z() )
			min.Z( itr->position.Z() );

	}

	m_boundingBox = Math::AxisAlignedBoundingBox ( min, max );

}
//End TerrainChunkNode::CalculateBoundingBox



//=========================================================================
//! @function    TerrainChunkNode::BuildCollisionMesh
//! @brief       Build the collision mesh, from a low LOD version
//!				 of the terrain
//!              
//=========================================================================
void TerrainChunkNode::BuildCollisionMesh ( )
{

	for ( UInt i=0; i < m_terrainNode.GetTriangles().size(); i+=2 )
	{

		m_collisionMesh.triangles.push_back( Math::Triangle(  m_collisionMesh.vertices[m_terrainNode.GetTriangles()[i].v0].position,
															  m_collisionMesh.vertices[m_terrainNode.GetTriangles()[i].v1].position,
															  m_collisionMesh.vertices[m_terrainNode.GetTriangles()[i].v2].position ));

		m_collisionMesh.triangles.push_back( Math::Triangle(   m_collisionMesh.vertices[m_terrainNode.GetTriangles()[i+1].v0].position,
															   m_collisionMesh.vertices[m_terrainNode.GetTriangles()[i+1].v1].position,
															   m_collisionMesh.vertices[m_terrainNode.GetTriangles()[i+1].v2].position) );
	}

}
//End TerrainChunkNode::BuildCollisionMesh



//=========================================================================
//! @function    TerrainChunkNode::CreateChunkVertexBuffer
//! @brief       Create the vertex buffer to hold the 
//!         
//! @param       renderer 
//!              
//=========================================================================
void TerrainChunkNode::CreateChunkVertexBuffer ( )
{
	
	Renderer::VertexDeclarationDescriptor descriptor;

	descriptor.AddElement ( 0, 0, Renderer::DECLTYPE_FLOAT3, Renderer::DECLUSAGE_POSITION, 0 ); 
	descriptor.AddElement ( 0, 12, Renderer::DECLTYPE_FLOAT3, Renderer::DECLUSAGE_NORMAL, 0 ); 
	descriptor.AddElement ( 0, 24, Renderer::DECLTYPE_COLOUR, Renderer::DECLUSAGE_DIFFUSE, 0 );
	descriptor.AddElement ( 0, 28, Renderer::DECLTYPE_FLOAT2, Renderer::DECLUSAGE_TEXCOORD, 0 ); 
	descriptor.AddElement ( 0, 36, Renderer::DECLTYPE_FLOAT2, Renderer::DECLUSAGE_TEXCOORD, 1 );

	m_vertexDeclaration = m_scene.Application().GetRenderer().AcquireVertexDeclaration( descriptor );

	Renderer::HVertexBuffer chunkBuffer = 
				m_scene.Application().GetRenderer().CreateVertexBuffer
							( sizeof(TerrainVertex), 
							  m_terrainNode.ChunkSize() *  m_terrainNode.ChunkSize(), 
							  Renderer::USAGE_STATICWRITEONLY );

	if ( !chunkBuffer )
	{
		throw Core::RuntimeError ( "Couldn't create terrain chunk vertex buffer!", 
									0, __FILE__, __FUNCTION__, __LINE__ );
	}
	else
	{
		m_vertexStreamBinding.SetStream ( chunkBuffer, 0 );
	}

}	
//End TerrainChunkNode::CreateChunkVertexBuffer


//=========================================================================
//! @function    TerrainChunkNode::FillVisibleObjectList
//! @brief       This isn't really all that different from the SceneObject
//!              version, it's just here to keep track of terrain rendering
//!              for debug purposes
//!              
//! @param       visibleObjectList 
//! @param       camera 
//!              
//! @return      
//! @throw       
//=========================================================================
void TerrainChunkNode::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera )
{

	SceneObject::FillVisibleObjectList ( visibleObjectList, camera );

}
//End TerrainChunkNode::FillVisibleObjectList


//=========================================================================
//! @function    TerrainChunkNode::FillChunkVertexBuffer
//! @brief       Fill the chunk vertex buffer with vertices from the 
//!				 terrain              
//!
//=========================================================================
void TerrainChunkNode::FillChunkVertexBuffer ( )
{
	Renderer::ScopedVertexBufferLock lock = m_vertexStreamBinding.GetStream(0)->LockAll( Renderer::LOCK_NORMAL );

	if ( !lock )
	{
		std::cerr << __FUNCTION__ << ": Error, couldn't lock vertex buffer!" << std::endl;
		return;
	}

	TerrainVertex* vertexPtr = reinterpret_cast<TerrainVertex*>(lock.GetLockPointer());

	//Copy the vertex data from the collision mesh vertex store into the vertex buffer
	CollisionMesh::VertexStore::const_iterator itr = m_collisionMesh.vertices.begin();
	CollisionMesh::VertexStore::const_iterator end = m_collisionMesh.vertices.end();

	for ( ; itr != end; ++itr )
	{
		vertexPtr->position[0] = itr->position.X();
		vertexPtr->position[1] = itr->position.Y();
		vertexPtr->position[2] = itr->position.Z();

		vertexPtr->normal[0] = itr->normal.X();
		vertexPtr->normal[1] = itr->normal.Y();
		vertexPtr->normal[2] = itr->normal.Z();

		vertexPtr->colour = itr->colour;

		vertexPtr->texCoord0[0] = itr->texCoord0.X();
		vertexPtr->texCoord0[1] = itr->texCoord0.Y();

		vertexPtr->texCoord1[0] = itr->texCoord1.X();
		vertexPtr->texCoord1[1] = itr->texCoord1.Y();

		++vertexPtr;
	}

}
//End TerrainChunkNode::FillChunkVertexBuffer



//=========================================================================
//! @function    TerrainChunkNode::InitialiseAutogenAlphaTextures
//! @brief       Initialise the autogenerated alpha textures
//!              
//!				 The autogen textures are used as alpha for the texture layers
//!				 for the terrain texture splatting
//=========================================================================
void TerrainChunkNode::InitialiseAutogenAlphaTextures()
{
	
}
//End TerrainChunkNode::InitialiseAutogenAlphaTextures



//=========================================================================
//! @function    TerrainChunkNode::CanCollideWith
//! @brief       Indicates whether or not an entity can collide with the terrain
//!              
//! @param       entity [in]
//!              
//! @return      Always returns true, any collidable object should be
//!				 able to collide with the terrain
//=========================================================================
bool TerrainChunkNode::CanCollideWith ( EntityNode* entity )
{
	return true;
}
//End TerrainChunkNode::CanCollideWith



//=========================================================================
//! @function    TerrainChunkNode::CollidesWith
//! @brief       Indicates whether an entity collides with the terrain
//!              
//! @param       entity			[in]	Entity to check collision with
//! @param       collisionType	[in]	Type of collision test to perform
//!										
//! @param       normal			[out]   Normal of the surface collided with
//! @param       depth			[out]	Depth of penetration into the plane of the surface
//!              
//! @return      true if collided, false if no collision
//=========================================================================
bool TerrainChunkNode::CollidesWith ( EntityNode* entity,
									  ECollisionType collisionType,
									  Math::Vector3D& normal,
									  Float& depth )
{



	//First check to see if the bounding boxes of the objects overlap
	if ( !Math::Intersects( m_boundingBox, entity->BoundingBox() ) )
	{
		return false;
	}
	else
	{

		CollisionManager::CollisionInfo contacts;
		CollisionManager::CollisionInfo normals;
		CollisionManager::PenetrationInfo penetration;

		//REMOVE ME!!! Debug check!!!
		entity->GetMesh().SafeDereference();

		if ( m_scene.GetCollisionManager().Collide( GetCollisionVolume(),
													ConcatObjectToWorld(),
													entity->GetCollisionVolume(),
													entity->ConcatObjectToWorld(),
													1,
													contacts,
													normals,
													penetration ) )
		{
			normal = normals[0];
			depth = penetration[0];

			//REMOVE ME!!! Debug check!!!
			entity->GetMesh().SafeDereference();

			return true;
		}	
	}

	return false;
	
}
//End TerrainChunkNode::CollidesWith



//=========================================================================
//! @function    TerrainChunkNode::QueryScene
//! @brief       Checks the terrain triangles for an intersection, and
//!				 returns any triangles intersected by the ray
//!              
//! @param       ray	[in]  Ray to check intesection with
//! @param       result [out] Array of triangles which intersect with the ray
//!              
//=========================================================================
void TerrainChunkNode::QueryScene ( const Math::ParametricLine3D& ray, SceneQueryResult& result )
{

	Float t = 0.0f;

	//If the ray intersects the terrain node bounding box, then check the terrain triangles
	if ( Math::Intersects(ray, m_boundingBox, t) != Math::NoIntersect )
	{

		t = m_scene.GetCollisionManager().Collide(GetCollisionVolume(), ray);
		
		if ( Math::InRange(t, 0.0f, 1.0f) )
		{
			result.push_back( t );
		}

		//Check any child nodes
		SceneNode::QueryScene( ray, result );
	}

}
//End TerrainChunkNode::QueryScene