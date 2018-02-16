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


#ifndef OIDFX_TERRAINCHUNKNODE_H
#define OIDFX_TERRAINCHUNKNODE_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "Math/Triangle.h"
#include "Renderer/VertexData.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"
#include "OidFX/SceneObject.h"
#include "OidFX/TerrainNode.h"
#include "OidFX/CollisionManager.h"


//=========================================================================
// Forward declaration
//=========================================================================
namespace Math		{ class Vector3D; class Triangle; }
namespace Renderer	{ class VertexData; }
namespace OidFX		{ class Scene;		}


//namespace OidFX
namespace OidFX
{

	//!@class	TerrainChunkNode
	//!@brief	Scene graph node representing a single chunk of terrain
	class TerrainChunkNode : public SceneObject
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			TerrainChunkNode (	Scene& scene, 
								const Math::Matrix4x4& toWorld,
								const Math::Matrix4x4& fromWorld,
								TerrainNode& terrainNode,
								UInt chunkRow,
								UInt chunkColumn,
								Renderer::HIndexBuffer indexBuffer,
								Renderer::HEffect effect );


            //=========================================================================
            // Public methods
            //=========================================================================
			void Update( Math::MatrixStack& toWorldStack, 
						 Math::MatrixStack& fromWorldStack, 
						 Float timeElapsedInSeconds );			
										

			//Restore
			virtual void Restore( );

			//Fill visible object list
			void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );


			//Collisions
			bool CanCollideWith ( EntityNode* entity );
			bool CollidesWith   ( EntityNode* entity,
								  ECollisionType collisionType,
								  Math::Vector3D& normal,
								  Float& depth );


			virtual void QueryScene ( const Math::ParametricLine3D& ray, 
									  SceneQueryResult& result );
	

			//=========================================================================
            // IRenderable implementation
            //=========================================================================
			void QueueForRendering ( Renderer::RenderQueue& queue );
			void Render ( Renderer::IRenderer& renderer );


            //=========================================================================
            // Static methods
            //=========================================================================
			static UInt	NodesRenderedThisFrame () 			{ return ms_nodesRendered;	}

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			struct TerrainMeshVertex
			{
				Math::Vector3D		position;
				Math::Vector3D		normal;
				Renderer::Colour4f	colour;
				Math::Vector3D		texCoord0;
				Math::Vector3D		texCoord1;
			};

			struct CollisionMesh
			{
				typedef Core::Vector<TerrainMeshVertex>::Type	VertexStore;
				typedef Core::Vector<Math::Triangle>::Type 		TriangleStore;
				
				VertexStore   vertices;
				TriangleStore triangles;
			};

			//Vertex type used in the index buffer
			struct TerrainVertex
			{
				Float	position[3];
				Float	normal[3];
				UInt32	colour;
				Float	texCoord0[2];	//! TexCoord 0 has the texture coordinates running from 0-1 over a single chunk
				Float	texCoord1[2];	//! TexCoord 1 has the texture coordinates running from 0-1 over the entire terrain
			};

	
            //=========================================================================
            // Private methods
            //=========================================================================
			void BuildCollisionMesh ( );
			void BuildVertexList  ( );
			void SmoothTerrainHeights ( );
			void CalculateNormals ( );
			void CalculateBoundingBox ( );

			void CreateChunkVertexBuffer();
			void FillChunkVertexBuffer();
			void InitialiseAutogenAlphaTextures();


            //=========================================================================
            // Private data
            //=========================================================================
			TerrainNode&							m_terrainNode;
			UInt									m_chunkRow;
			UInt									m_chunkColumn;
			Renderer::HVertexDeclaration			m_vertexDeclaration;
			Renderer::VertexStreamBinding			m_vertexStreamBinding;
			Renderer::HIndexBuffer					m_indexBuffer;
			Renderer::HEffect						m_effect;

			CollisionMesh							m_collisionMesh;

			static UInt								ms_nodesRendered;
			
			//Autogen alpha textures
			std::vector<Renderer::HTexture>			m_alphaLayers;


	};
	//End class TerrainChunkNode


};
//end namespace OidFX


#endif
//#ifndef OIDFX_TERRAINCHUNKNODE_H

