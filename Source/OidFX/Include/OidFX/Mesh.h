//======================================================================================
//! @file         Mesh.h
//! @brief        Triangle mesh class
//!               
//!				  Class encapsulating a triangle mesh, and related methods. 
//!				  Does not handle loading of a mesh from disk. This is handled by the MeshLoader class
//!               
//! @author       Bryan Robertson
//! @date         Friday, 05 August 2005
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


#ifndef OIDFX_MESH_H
#define OIDFX_MESH_H


#include "Core/Resource.h"
#include "Math/Vector3D.h"
#include "Math/BoundingBox3D.h"
#include "Math/BoundingSphere3D.h"
#include "Renderer/Renderable.h"
#include "Renderer/Colour4f.h"
#include "Renderer/Effect.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/VertexStreamBinding.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace Renderer	{	class IRenderer;	}



//namespace OidFX
namespace OidFX
{


	//!@class	MeshGroupDescriptor
	//!
	//!@brief	Class describing a mesh group, used by the Mesh class constructor,
	//!			so that it can build a shared index buffer for all mesh groups
	class MeshGroupDescriptor
	{

		public:
		
            //=========================================================================
            // Constructor
            //=========================================================================
			MeshGroupDescriptor ( const Char* name, Renderer::HEffect& effect, std::vector<UInt>& triangleIndices )
				: m_name(name), m_effect(effect), m_triangleIndices(triangleIndices)
			{
			}

            //=========================================================================
            // Public methods
            //=========================================================================
			const std::string&	Name ( ) const						{ return m_name;					}
			Renderer::HEffect&	GetEffect ( )						{ return m_effect;					}
			const std::vector<UInt>&	Indices ( ) const			{ return m_triangleIndices;			}

			UInt IndexCount ( ) const				{ return m_triangleIndices.size();	}

		private:

			std::string		   m_name;
			Renderer::HEffect  m_effect;
			std::vector<UInt>  m_triangleIndices;

	};
	//End Class MeshGroupDescriptor



	//!@class	MeshGroup
	//!@brief	Class representing a named subset of a mesh, covered uniformly
	//!			by one effect
	class MeshGroup : public Renderer::IRenderable
	{

		public:

            //=========================================================================
            // Public types
            //=========================================================================
			typedef std::vector<UInt>			IndexStore;
			typedef IndexStore::const_iterator	ConstIndexIterator;


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			MeshGroup ( const Char* name, Renderer::HEffect& effect, UInt startOffset,
						const IndexStore& triangleIndices, UInt minVertexIndex, UInt maxVertexIndex )

				: 
				  m_name(name), m_effect(effect), m_startOffset(startOffset), 
				  m_triangleIndices(triangleIndices), m_minVertexIndex(minVertexIndex), m_maxVertexIndex(maxVertexIndex)
			{
			}


            //=========================================================================
            // Public methods
            //=========================================================================
			ConstIndexIterator	IndicesBegin() const	{ return m_triangleIndices.begin();	}
			ConstIndexIterator	IndicesEnd() const		{ return m_triangleIndices.end();	}
			UInt				IndexCount() const		{ return m_triangleIndices.size();	}


			// IRenderable implementation
			void Render( Renderer::IRenderer& renderer );
			void QueueForRendering ( Renderer::RenderQueue& queue, 
									 Renderer::HVertexDeclaration& vertexDeclaration,
									 Renderer::HIndexBuffer& indexBuffer,
									 Renderer::VertexStreamBinding& streamBinding,
									 const Math::Matrix4x4& worldMatrix,
									 UInt lodIndex );

			void QueueForRendering ( Renderer::RenderQueue& renderer ) {}


		private:

            //=========================================================================
            // Private data
            //=========================================================================
			std::string				m_name;
			UInt					m_startOffset;
			UInt					m_minVertexIndex;
			UInt					m_maxVertexIndex;
			IndexStore				m_triangleIndices;
			Renderer::HEffect		m_effect;


	};
	//End class MeshGroup



	//!@class	Mesh
	//!@brief	Mesh resource class. 
	//!
	//!			Class responsible for the storage of triangle mesh data, generating normals, and rendering of a mesh 
	//!
	class Mesh : public Core::Resource,
				 public Renderer::IRenderable
	{
		
		public:

			//=========================================================================
            // Public types required for the constructor
            //=========================================================================
			struct Vertex
			{
				Math::Vector3D		position;
				Math::Vector3D		normal;
				Renderer::Colour4f	colour;
				Math::Vector3D		texCoord0;
			};

			struct Triangle
			{

				Triangle ( UInt vertex0, UInt vertex1, UInt vertex2, UInt faceSmoothingGroup )
					: v0(vertex0), v1(vertex1), v2(vertex2), smoothingGroup(faceSmoothingGroup)
				{
				}

				UInt			v0;
				UInt			v1;
				UInt			v2;

				Math::Vector3D	faceNormal;
				UInt			smoothingGroup;
			};


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			Mesh ( Renderer::IRenderer& renderer,
				   const Char* name,
				   const std::vector<Vertex>& vertices,		
				   const std::vector<Triangle>& triangles,	
				   const std::vector<Renderer::HEffect>& effects,
				   std::vector<MeshGroupDescriptor>& groupDescriptor );


            //=========================================================================
            // More public types
            //=========================================================================

			//Storage for internal data
			typedef std::vector<Vertex>			VertexStore;
			typedef std::vector<Triangle>		TriangleStore;
			typedef std::vector<MeshGroup>		MeshGroupStore;
			typedef std::vector<Renderer::HEffect>		EffectStore;

			//Iterators for internal data storage
			typedef VertexStore::iterator			VertexIterator;
			typedef TriangleStore::iterator			TriangleIterator;
			typedef MeshGroupStore::iterator		MeshGroupIterator;
			typedef EffectStore::iterator			EffectIterator;

			typedef VertexStore::const_iterator		ConstVertexIterator;
			typedef TriangleStore::const_iterator	ConstTriangleIterator;
			typedef MeshGroupStore::const_iterator	ConstMeshGroupIterator;
			typedef EffectStore::const_iterator		ConstEffectIterator;


            //=========================================================================
            // Public methods
            //=========================================================================
			
			void Unload() {}

            // IRenderable implementation
			void Render( Renderer::IRenderer& renderer );
			void QueueForRendering ( Renderer::RenderQueue& queue, const Math::Matrix4x4& worldMatrix, UInt lodIndex );

			void QueueForRendering ( Renderer::RenderQueue& queue ) {}
      
            // Accessors
			inline const Math::AxisAlignedBoundingBox& GetObjectSpaceBoundingBox( ) const		{ return m_boundingBox;		}
            			
            //=========================================================================
            // Public iterator methods
            //=========================================================================
			inline ConstVertexIterator		VerticesBegin ( ) const			{ return m_vertices.begin();	}
			inline ConstVertexIterator		VerticesEnd ( ) const			{ return m_vertices.end();		}
			inline ConstTriangleIterator	TrianglesBegin ( ) const		{ return m_triangles.begin();	}
			inline ConstTriangleIterator	TrianglesEnd ( ) const			{ return m_triangles.end();		}
			inline ConstMeshGroupIterator	MeshGroupsBegin ( ) const		{ return m_groups.begin();		}
			inline ConstMeshGroupIterator	MeshGroupsEnd ( ) const			{ return m_groups.end();		}
			inline ConstEffectIterator		EffectsBegin ( ) const			{ return m_effects.begin();		}
			inline ConstEffectIterator		EffectsEnd ( ) const			{ return m_effects.end();		}

			inline UInt	VertexCount ( ) const		{ return m_vertices.size();		}
			inline UInt	TriangleCount ( ) const		{ return m_triangles.size();	}
			inline UInt	MeshGroupCount ( ) const	{ return m_groups.size();		}
			inline UInt	EffectCount ( ) const		{ return m_effects.size();		}
			
		private:

            //=========================================================================
            // Private types
            //=========================================================================
			
			//! Format for first stream of mesh data in the vertex buffer
			struct MeshStream0
			{
				Float	position [3];
				Float   normal   [3];
				UInt32	colour;
				Float	texcoord [2];
			};


            //=========================================================================
            // Private methods
            //=========================================================================
			void ValidateInputData ( const Char* name,
									 const std::vector<Vertex>& vertices,		
									 const std::vector<Triangle>& triangles,	
									 const std::vector<Renderer::HEffect>& effects,
									 const std::vector<MeshGroupDescriptor>& groupDescriptor );

			void BuildGroups ( std::vector<MeshGroupDescriptor>& groupDescriptor );
			void GenerateBoundingVolumes(); 
			void GenerateNormals();
			void CreateMeshVertexBuffer( Renderer::IRenderer& renderer );
			void CreateMeshIndexBuffer( Renderer::IRenderer& renderer );
			void FillVertexBuffer();
			void FillIndexBuffer();

			//Private iterator methods
			inline VertexIterator		VerticesBegin ( ) 	{ return m_vertices.begin();	}
			inline VertexIterator		VerticesEnd ( ) 	{ return m_vertices.end();		}
			inline TriangleIterator		TrianglesBegin ( ) 	{ return m_triangles.begin();	}
			inline TriangleIterator		TrianglesEnd ( ) 	{ return m_triangles.end();		}
			inline MeshGroupIterator	MeshGroupsBegin ( ) { return m_groups.begin();		}
			inline MeshGroupIterator	MeshGroupsEnd ( ) 	{ return m_groups.end();		}
			inline EffectIterator		EffectsBegin ( ) 	{ return m_effects.begin();		}
			inline EffectIterator		EffectsEnd ( ) 		{ return m_effects.end();		}


            //=========================================================================
            // Private data
            //=========================================================================

			//Vertices and triangles
			VertexStore						m_vertices;
			TriangleStore					m_triangles;

			//Bounding volume
			Math::AxisAlignedBoundingBox	m_boundingBox;
			
			//Mesh groups
			MeshGroupStore					m_groups;

			//Materials
			EffectStore						m_effects;
			
			//Rendering
			Renderer::VertexStreamBinding	m_vertexStreams;
			Renderer::HIndexBuffer			m_indexBuffer;
			Renderer::HVertexDeclaration	m_vertexDeclaration;

	};
	//End Class Mesh


    //=========================================================================
    // Typedefs
    //=========================================================================
	typedef	Core::Handle<Mesh>	HMesh;


}
//end namespace OidFX


#endif
//#ifndef OIDFX_MESH_H
