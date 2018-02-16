//======================================================================================
//! @file         TerrainNode.h
//! @brief        Scene graph node representing a whole terrain
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

#ifndef TERRAINNODE_H
#define TERRAINNODE_H


#include <vector>
#include "OidFX/SceneObject.h"
#include "Renderer/Effect.h"
#include "Renderer/IndexBuffer.h"


//=========================================================================
// Forward declaration
//=========================================================================
namespace OidFX		{ class Scene;		}
namespace Math		{ class Vector3D;	}
namespace Renderer	{ class EffectManager;	}


//namespace OidFX
namespace OidFX
{

	//!@class	TerrainNode
	//!@brief	Scene graph node representing a whole terrain
	class TerrainNode : public SceneObject
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			TerrainNode ( Scene& scene, 
						  UInt heightmapSize, 
						  UInt chunkSize, 
						  Float terrainSize,
						  Float terrainMaxY,
						  const Char* heightMapFileName, 
						  const Char* terrainEffectName,
						  const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
						  const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix
						  );


            //=========================================================================
            // Public types
            //=========================================================================
			struct LODInfo
			{
				UInt  startIndex;
				UInt  indexCount;
			};

			struct Triangle
			{
				UInt v0;
				UInt v1;
				UInt v2;
			};

			typedef Core::Vector<Triangle>::Type	TriangleStore;
            
            //=========================================================================
            // Public methods
            //=========================================================================
			void InitialiseTerrain();

			void Restore();

			//Fill visible object list
			void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );

			inline Float					HeightMapValueAt ( UInt row, UInt col ) const;
	
			inline const LODInfo& GetLODInfo ( UInt lod ) const throw();

			UInt  HeightmapSize () const		{ return m_heightmapSize;		}
			UInt  ChunkSize () const			{ return m_chunkSize;			}
			Float TerrainSize () const			{ return m_terrainSize;			}
			Float TerrainMaxY () const			{ return m_terrainMaxY;			}
			const TriangleStore& GetTriangles()	const { return m_triangles;		}


			virtual void CheckCollisions ( EntityNode* entity, 
										   ECollisionType collisionType,
										   const NodeCollisionFlags& collisionFlags,
										   CollisionManager& collisionManager );		

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			typedef std::vector<Float>				HeightStore;
			

            //=========================================================================
            // Private methods
            //=========================================================================
			void LoadHeightMap ( const Char* fileName );
			void PopulateTerrainChunks();
			void CreateChunkIndexBuffer ( );
			void PopulateChunkIndexBuffer ( );

			void FillIndexBufferLODLevel ( UInt lodLevel, 
										   UShort* buffer,
										   UInt chunkVertsX,
										   UInt chunkVertsZ,
										   UInt xSkip,
										   UInt ySkip,
										   UInt bufferPitch ) throw();

            //=========================================================================
            // Private data
            //=========================================================================
			HeightStore		m_heights;			//!< Heights of the terrain
			UInt			m_heightmapSize;	//!< Width/Height of the heightmap in pixels
			UInt			m_chunkSize;		//!< Width/Height of a single terrain chunk in pixels
			Float			m_terrainSize;		//!< Size of the terrain in the x and z dimensions
			Float			m_terrainMaxY;		//!< Maximum y value of the terrain
			
			Renderer::HIndexBuffer	m_indexBuffer;	//!< Shared index buffer for the terrain
			Renderer::HEffect		m_effect;		//!< Shared effect for the terrain

			std::vector<LODInfo>		m_lodStartIndices; //!< Offset into index buffer for each detail level

			TriangleStore	m_triangles;	//!< Triangle indices for the most detailed LOD

	};
	//End class TerrainNode



	//=========================================================================
	//! @function    TerrainNode::HeightMapValueAt
	//! @brief       Return the height map value at row,col
	//!              
	//! @param       row [in] Row index
	//! @param       col [in] Column index
	//!              
	//! @return      The height value at row,col
	//! @throw       
	//=========================================================================
	Float TerrainNode::HeightMapValueAt ( UInt row, UInt col ) const
	{
		debug_assert ( row < m_heightmapSize, "Invalid row index" );
		debug_assert ( col < m_heightmapSize, "Invalid column index" );
		debug_assert ( col + (row * m_heightmapSize) < m_heights.size(), "Invalid index!" );

		return m_heights [ col + (row * m_heightmapSize) ];
	}
	//End TerrainNode::HeightMapValueAt


    //=========================================================================
    //! @function    TerrainNode::GetLODInfo
    //! @brief       Get information about the LOD level specified, so that
    //!              it can be rendered
    //!              
    //! @param       lod [in] Level of detail to get information for 
    //!              
    //=========================================================================
	const TerrainNode::LODInfo& TerrainNode::GetLODInfo ( UInt lod ) const
	{

		debug_assert ( !m_lodStartIndices.empty(), "LOD levels are empty!" );

		static Core::ConsoleBool dbg_terrainlodenable ( "dbg_terrainlodenable", true );

		if ( !dbg_terrainlodenable )
		{
			lod = 0;
		}

		//Make sure that the LOD indices are in the correct range
		//
		//This isn't an assert, because it's not neccessarily an error to ask for an LOD
		//level that is out of range. It is not guaranteed that the terrain will have LOD generated
		//for every level of detail
		if ( lod >= m_lodStartIndices.size() )
		{
			lod = m_lodStartIndices.size() - 1;
		}

		return m_lodStartIndices[lod];
	}
	//End  TerrainNode::GetLODInfo

}
//end namespace OidFX


#endif
//#ifndef TERRAINNODE_H
