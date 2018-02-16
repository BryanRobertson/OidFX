//======================================================================================
//! @file         TerrainNode.cpp
//! @brief        Scene graph node representing a whole terrain
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
#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/Matrix4x4.h"
#include "Math/MatrixStack.h"
#include "Math/BoundingSphere3D.h"
#include "Math/IntersectionTests.h"
#include "Renderer/Renderer.h"
#include "Renderer/EffectManager.h"
#include "OidFX/Constants.h"
#include "OidFX/Scene.h"
#include "OidFX/GameApplication.h"
#include "OidFX/TerrainChunkNode.h"
#include "OidFX/TerrainNode.h"
#include "OidFX/QuadtreeNode.h"



using namespace OidFX;




//=========================================================================
//! @function    TerrainNode::TerrainNode
//! @brief       TerrainNode constructor
//!              
//! @param       scene				[in] Scene that this node belongs to
//! @param		 heightmapSize		[in] Width/height of the heightmap (heightmap is always square)
//! @param		 chunkSize			[in] Width/height of a single chunk of terrain (chunks are always square)
//! @param		 terrainSize		[in] Size of the terrain in world units
//! @param		 terrainMaxY		[in] Max Y (height) value of the terrain
//! @param		 heightmapFileName  [in] Filename used for the heightmap. In future this will be generated
//!										 randomly, but I've chosen this method for the moment, due to time constraints
//!										 time constraints
//! @param		 terrainEffectName	[in] Filename of the effect used to render the terrain
//!
//! @throw		 Core::RuntimeError if the terrain heightmap or normals could not be found
//=========================================================================
TerrainNode::TerrainNode ( Scene& scene,
						   UInt heightmapSize,
						   UInt chunkSize,
						   Float terrainSize,
						   Float terrainMaxY,
						   const Char* heightmapFileName,
						   const Char* terrainEffectName,
						   const Math::Matrix4x4& toWorld, 
						   const Math::Matrix4x4& fromWorld
						   )
: 
	 SceneObject(scene, NODETYPE_WORLD, Math::Matrix4x4(), Math::Matrix4x4() ), 
	 m_heightmapSize(heightmapSize), 
	 m_chunkSize(chunkSize),
	 m_terrainSize(terrainSize), 
	 m_terrainMaxY(terrainMaxY)
{

	//Set the bounding volume of the terrain
	m_boundingBox = Math::AxisAlignedBoundingBox ( Math::Vector3D(0.0f, 0.0f, 0.0f), 
												   Math::Vector3D(m_terrainSize, m_terrainMaxY * 2, m_terrainSize) );


	//Set the transformation matrices
	m_objectToWorld.Translate ( Math::Vector3D(-m_terrainSize/2, 0, -m_terrainSize/2) );
	m_objectFromWorld.Translate ( Math::Vector3D(m_terrainSize/2, 0, m_terrainSize/2) );

	//Load the heightmap
	LoadHeightMap ( heightmapFileName );

	//Load the terrain effect
	m_effect = m_scene.Application().GetEffectManager().AcquireEffect( terrainEffectName );

	//Create and populate the index buffer
	CreateChunkIndexBuffer();
	PopulateChunkIndexBuffer();
}
//End TerrainNode::TerrainNode



//=========================================================================
//! @function    TerrainNode::InitialiseTerrain
//! @brief       Updates the terrain bounding box, and creates all terrain chunks
//!
//=========================================================================
void TerrainNode::InitialiseTerrain ( )
{
	
	//Set the position of the bounding box
	UpdateBoundsPositionFromLocalTransform();

	//Populate the terrain chunks
	PopulateTerrainChunks();

}
//End TerrainNode::InitialiseTerrain



//=========================================================================
//! @function    TerrainNode::Restore
//! @brief       Restore any resources after the renderer device is lost
//=========================================================================
void TerrainNode::Restore ( )
{
	std::clog << __FUNCTION__ << ": Restoring terrain" << std::endl;

	PopulateChunkIndexBuffer();

	//Call the base class restore function to propagate the restore
	//call down to the children
	SceneNode::Restore();
}
//End TerrainNode::Restore



//=========================================================================
//! @function    TerrainNode::FillVisibleObjectList
//! @brief       Add the terrain to the visible object list if it is visible
//!              
//! @param       visibleObjectList [in] List of visible objects to add this object to
//! @param       camera			   [in] Camera to test visibility with
//!              
//=========================================================================
void TerrainNode::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera )
{
	if ( !Math::Intersects ( m_boundingBox, camera.ViewFrustum() ) )
	{
		return;
	}

	//Call the base class FillVisibleObjectList to add all children
	SceneObject::FillVisibleObjectList ( visibleObjectList, camera );
}
//End SceneObject::FillVisibleObjectList



//=========================================================================
//! @function    TerrainNode::LoadHeightMap
//! @brief       Populate the heights list from a RAW file
//!              
//!              In future I'll be generating a heightmap randomly
//!				 but due to time constraints, I've been forced to do it this way
//!				 for the moment.
//!              
//! @param       fileName [in]
//!              
//! @throw       Core::RuntimeError if the file could not be found
//=========================================================================
void TerrainNode::LoadHeightMap ( const Char* fileName )
{
	debug_assert ( fileName, "Error, null filename passed to LoadHeightMap!" );

	std::ifstream heightFile ( fileName, std::ios::binary );

	heightFile.seekg( 0, std::ios_base::end );
	UInt fileSize = heightFile.tellg();
    heightFile.seekg( 0, std::ios_base::beg );

	if ( !heightFile )
	{
		throw Core::RuntimeError ( "Couldn't find heightmap file!", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	//Read in the heightmap values
	UInt bytesToRead = fileSize;
	m_heights.reserve(bytesToRead);

	UInt fileHeightmapSize = Math::Sqrt(static_cast<Float>(fileSize));

	if ( fileHeightmapSize < m_heightmapSize )
	{
		m_heightmapSize = fileHeightmapSize;
	}

	while ( heightFile && bytesToRead )
	{
		UChar heightVal = 0;

		heightFile.read ( (std::istream::char_type*)(&heightVal), 1);
		m_heights.push_back ( (static_cast<Float>(heightVal) / 255.0) * m_terrainMaxY );
	
		--bytesToRead;
	}

	heightFile.close();
}
//End TerrainNode::LoadHeightMap


//=========================================================================
//! @function    TerrainNode::PopulateTerrainChunks
//! @brief       Create the terrain chunks
//!              
//!              
//! @return      
//! @throw       
//=========================================================================
void TerrainNode::PopulateTerrainChunks ( )
{
	//There is no corresponding chunkCols variable, because the
	//number of rows and columns are identical
	UInt chunkRows = m_heightmapSize / m_chunkSize;

	Math::Matrix4x4 chunkToWorld;
	Math::Matrix4x4 chunkFromWorld;
	Float chunkWorldSize = m_terrainSize / 
							( static_cast<Float>(m_heightmapSize) / 
							  static_cast<Float>(m_chunkSize) );

	Math::AxisAlignedBoundingBox leafBounds ( Math::Vector3D( 0.0f, 0.0f, 0.0f), 
											  Math::Vector3D( (chunkWorldSize), 
															   m_terrainMaxY , 
															  (chunkWorldSize)) );

	Math::AxisAlignedBoundingBox quadBoundingBox ( Math::Vector3D( 0.0f, 0.0f, 0.0f),
												   Math::Vector3D(	BoundingBox().ExtentX(), 
																	BoundingBox().ExtentY(), 
																	BoundingBox().ExtentZ()) );

	boost::shared_ptr<QuadtreeNode> quadtreeNode ( new QuadtreeNode( m_scene, quadBoundingBox ) );
	AddChild( quadtreeNode );
	quadtreeNode->BuildQuadtree( leafBounds );

	for ( UInt row = 0; row < chunkRows; ++row )
	{
		for ( UInt col = 0; col < chunkRows; ++col )
		{

			boost::shared_ptr<TerrainChunkNode> node
								( new TerrainChunkNode(m_scene,
														Math::Matrix4x4(),
													    Math::Matrix4x4(),
													   *this,
													    row,
													    col,
														m_indexBuffer,
														m_effect) );

			//Update the concatenated transform and bounding volume, so that the
			//node is sorted into the scene graph properly
			node->SetConcatTransform ( ConcatObjectToWorld() * node->ObjectToWorld(), 
									   ConcatObjectFromWorld () * node->ObjectFromWorld() );

			node->UpdateBoundsPositionFromConcatTransform();
			
			//Add the node to the quadtree
			quadtreeNode->AddSortedChild( node );

			std::clog << __FUNCTION__ ": Added terrain chunk " << row << "," << col << std::endl;
		}
	}
}
//End TerrainNode::PopulateTerrainChunks


//=========================================================================
//! @function    TerrainNode::CreateChunkIndexBuffer
//! @brief       Create an index buffer shared between the terrain chunks
//!              
//=========================================================================
void TerrainNode::CreateChunkIndexBuffer ( )
{

	UInt totalIndices = 0;
	UInt currentLODStartIndex = 0;
	UInt currentLOD = 0;
	UInt currentLODTriCount = ((m_chunkSize-1)/(currentLOD+1)) * 
							  ((m_chunkSize-1)/(currentLOD+1)) * 2.0f;

	//Get the number of indices for all detail levels
	while ( (currentLODTriCount > 2)
		&&  (currentLOD <= g_lodMax) )
	{	
		//Add to the total number of indices
		totalIndices += currentLODTriCount * 6;

		LODInfo info;
		info.startIndex = currentLODStartIndex;
		info.indexCount = currentLODTriCount * 6;

		m_lodStartIndices.push_back( info );

		//Add to the current LOD start index
		currentLODStartIndex += currentLODTriCount * 6;

		++currentLOD;
		currentLODTriCount = ((m_chunkSize-1)/(currentLOD+1)) * 
							  ((m_chunkSize-1)/(currentLOD+1)) * 2.0f;
	}

	m_indexBuffer = m_scene.Application().GetRenderer().CreateIndexBuffer( Renderer::INDEX_16BIT, totalIndices, Renderer::USAGE_STATICWRITEONLY );

	if ( !m_indexBuffer )
	{
		throw Core::RuntimeError ( "Couldn't create chunk index buffer!" , 0, __FILE__, __FUNCTION__, __LINE__ );
	}

}
//End TerrainNode::CreateChunkIndexBuffer



//=========================================================================
//! @function    TerrainNode::PopulateChunkIndexBuffer
//! @brief       Fill the index buffer
//=========================================================================
void TerrainNode::PopulateChunkIndexBuffer ( )
{
	Renderer::ScopedIndexBufferLock lock = m_indexBuffer->LockAll(Renderer::LOCK_NORMAL);

	if ( !lock )
	{
		std::cerr << __FUNCTION__ << "Error, couldn't lock chunk index buffer!" << std::endl;
	}

	UShort* indexPtr = reinterpret_cast<UShort*>(lock.GetLockPointer());
	
	//Number of vertices to skip for this LOD level. 1 = draw every vertex 
	UInt vertexSkip = 1;

	for ( UInt i=0; i < m_lodStartIndices.size(); ++i )
	{
		
		FillIndexBufferLODLevel ( i,
								  indexPtr + m_lodStartIndices[i].startIndex,
								  m_chunkSize,
								  m_chunkSize,
								  vertexSkip,
								  vertexSkip, 
								  m_chunkSize );

		vertexSkip *= 2;
	}

}
//End TerrainNode::PopulateChunkIndexBuffer


//=========================================================================
//! @function    TerrainNode::FillIndexBufferLODLevel
//! @brief       Fill the index buffer for a specific LOD level
//!              
//!              
//! @param       lodLevel		[in] LOD level of the chunk
//! @param       buffer			[in] Pointer to the location in the locked buffer
//!									 to start writing indices for this level of detail
//! @param       chunkVertsX	[in] Vertices in the x direction at the highest detail level
//! @param       chunkVertsZ	[in] Vertices in the z direction at the highest detail level
//! @param       xSkip			[in] Number of vertices to skip in the x direction for this LOD
//! @param       zSkip			[in] Number of vertices to skip in the y direction for this LOD
//! @param       bufferPitch	[in] Width of one row of vertices in the index buffer, in vertices
//!              
//=========================================================================
void TerrainNode::FillIndexBufferLODLevel ( UInt lodLevel, 
											UShort* buffer,
											UInt chunkVertsX,
											UInt chunkVertsZ,
											UInt xSkip,
											UInt zSkip,
											UInt bufferPitch )
{

	std::clog << __FUNCTION__ ": Filling in index data for LOD level " << lodLevel << std::endl;

	//Variables to hold the current row and column
	UInt row = 0;
	UInt col = 0;

	//Number of verts to step in the z direction
	UInt zStep = bufferPitch * zSkip;

	while ( ((row+1) * zSkip) < chunkVertsZ )
	{
		col = 0;

		while ( (col + xSkip) < chunkVertsX )
		{

			//Triangle 1
			*(buffer++) = (row * zStep) + col;
			*(buffer++) = ((row+1) * zStep) + col;
			*(buffer++) = (row * zStep) + (col + xSkip);

			//Triangle 2
			*(buffer++) = (row * zStep) + (col + xSkip);
			*(buffer++) = ((row+1) * zStep) + col;
			*(buffer++) = ((row+1) * zStep) + (col + xSkip);

			//Fill in the index data for the most detailed LOD level,
			//if this is LOD 0
			if ( lodLevel == 0 )
			{
				Triangle triangle;

				triangle.v0 = (row * zStep) + col;
				triangle.v1 = ((row+1) * zStep) + col;
				triangle.v2 = (row * zStep) + (col + xSkip);
				m_triangles.push_back(triangle);

				triangle.v0 = (row * zStep) + (col + xSkip);
				triangle.v1 = ((row+1) * zStep) + col;
				triangle.v2 = ((row+1) * zStep) + (col + xSkip);
				m_triangles.push_back(triangle);
			}

			col += xSkip;
		}

		++row;
	}

}
//End TerrainNode::FillIndexBufferLODLevel



//=========================================================================
//! @function    TerrainNode::CheckCollisions
//! @brief       Check collisions against an entity
//!              
//! @param       entity				[in]
//! @param       collisionType		[in] 
//! @param       collisionFlags		[in]
//! @param       collisionManager	[in]
//!              
//=========================================================================
void TerrainNode::CheckCollisions ( EntityNode* entity,
									ECollisionType collisionType,
									const NodeCollisionFlags& collisionFlags,
									CollisionManager& collisionManager )
{
	SceneNode::CheckCollisions( entity,
								collisionType,
								collisionFlags,
								collisionManager );
}
//End TerrainNode::CheckCollisions