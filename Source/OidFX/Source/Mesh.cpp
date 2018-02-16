//======================================================================================
//! @file         Mesh.cpp
//! @brief        Triangle mesh class
//!               
//!				  Class encapsulating a triangle mesh, and related methods. 
//!				  Does not handle loading of a mesh from disk. This is handled by the MeshLoader class
//!               
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


#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderQueue.h"
#include "OidFX/Mesh.h"



using namespace OidFX;



//=========================================================================
//! @function    Mesh::Mesh 
//! @brief       Mesh constructor
//!
//!
//! @param       name		[in]	Name used to identify the mesh
//! @param		 vertices	[in]	Array of vertices
//! @param		 triangles	[in]	Array of triangles
//! @param		 effects	[in]	Array of effects used by the mesh
//! @param		 groupDescriptor [in]	Array of structures describing the
//!										assignment of triangles to groups
//!   
//=========================================================================
Mesh::Mesh ( Renderer::IRenderer& renderer,
			 const Char* name, 
			 const std::vector<Mesh::Vertex>& vertices, 
			 const std::vector<Mesh::Triangle>& triangles,
			 const std::vector<Renderer::HEffect>& effects,
			 std::vector<MeshGroupDescriptor>& groupDescriptor )
 :
   Resource(name)
{

	//Make sure we have all required input data
	ValidateInputData ( name, vertices, triangles, effects, groupDescriptor );

	//Copy the arrays into our internal arrays
	std::copy ( vertices.begin(), vertices.end(), std::back_inserter(m_vertices) );
	std::copy ( triangles.begin(), triangles.end(), std::back_inserter(m_triangles) );
	std::copy ( effects.begin(), effects.end(), std::back_inserter(m_effects) );

	GenerateBoundingVolumes();
	BuildGroups ( groupDescriptor );
	GenerateNormals();

	CreateMeshVertexBuffer( renderer );
	FillVertexBuffer();

	CreateMeshIndexBuffer( renderer );
	FillIndexBuffer();

}
//End Mesh::Mesh 



//=========================================================================
//! @function    Mesh::ValidateInputData
//! @brief       Make sure that we have all required input data to 
//!              build the mesh. Throws Core::RuntimeError if any of the data is missing
//!              
//!              
//! @param       name 
//! @param       vertices 
//! @param       triangles 
//! @param       effects 
//! @param       groupDescriptor 
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void Mesh::ValidateInputData ( const Char* name, 
							   const std::vector<Vertex>& vertices, 
							   const std::vector<Triangle>& triangles,
							  const std::vector<Renderer::HEffect>& effects, 
							  const std::vector<MeshGroupDescriptor>& groupDescriptor )
{

	if ( vertices.size() == 0 )
	{
		throw Core::RuntimeError ( "Mesh has no vertices!", 0, __FILE__, __FUNCTION__, __LINE__  );
	}

	if ( triangles.size() == 0 )
	{
		throw Core::RuntimeError ( "Mesh has no triangles!", 0, __FILE__, __FUNCTION__, __LINE__  );
	}

	if ( effects.size() == 0 )
	{
		throw Core::RuntimeError ( "Mesh has no effects!" );
	}

	if ( groupDescriptor.size() == 0 )
	{ 
		throw Core::RuntimeError ( "Mesh has no groups!" );
	}

}
//End Mesh::ValidateInputData



//=========================================================================
//! @function    Mesh::GenerateBoundingVolumes
//! @brief       Generate the object space bounding box and bounding sphere for the mesh
//!              
//=========================================================================
void Mesh::GenerateBoundingVolumes ( )
{
	if ( VertexCount() == 0 )
		return;

	//Initialise the maximum and minimum vertices for the bounding box
	Math::Vector3D max;
	Math::Vector3D min = VerticesBegin()->position;

	//Iterators to iterate through the vertices
	ConstVertexIterator itr = VerticesBegin();
	ConstVertexIterator end = VerticesEnd();

	for ( ; itr != end; ++itr )
	{
		if ( itr->position.X() > max.X() )
		{
			max.X( itr->position.X() );
		}

		if ( itr->position.Y() > max.Y() )
		{
			max.Y( itr->position.Y() );
		}

		if ( itr->position.Z() > max.Z() )
		{
			max.Z( itr->position.Z() );
		}

		if ( itr->position.X() < min.X() )
		{
			min.X( itr->position.X() );
		}

		if ( itr->position.Y() < min.Y() )
		{
			min.Y( itr->position.Y() );
		}

		if ( itr->position.Z() < min.Z() )
		{
			min.Z( itr->position.Z() );
		}
	}

	m_boundingBox = Math::AxisAlignedBoundingBox ( min, max );
}
//End Mesh::GenerateBoundingBox


//=========================================================================
//! @function    Mesh::BuildGroups
//! @brief       Build the list of mesh groups
//!              
//! @param		 groupDescriptor [in] Array of descriptors for the mesh groups
//!
//=========================================================================
void Mesh::BuildGroups ( std::vector<MeshGroupDescriptor>& groupDescriptor )
{

	UInt currentStartOffset = 0;

	//iterators
	std::vector<MeshGroupDescriptor>::iterator itr = groupDescriptor.begin();
	std::vector<MeshGroupDescriptor>::iterator end = groupDescriptor.end();

	for ( ; itr != end; ++itr )
	{
		m_groups.push_back ( MeshGroup(itr->Name().c_str(), 
									   itr->GetEffect(), 
									   currentStartOffset, 
									   itr->Indices(), 
									   0,
									   m_vertices.size() ) );

		currentStartOffset += (itr->IndexCount() * 3);
	}

}
//End Mesh::BuildGroups



//=========================================================================
//! @function    Mesh::GenerateNormals
//! @brief       Generate face and vertex normals for the mesh
//!              
//=========================================================================
void Mesh::GenerateNormals ( )
{
	TriangleIterator triangle = TrianglesBegin();
	TriangleIterator trianglesEnd = TrianglesEnd();


	//First generate face normals 
	for ( ; triangle != trianglesEnd; ++triangle )
	{
		//Make sure that the vertex indices of the triangle are valid
		debug_assert ( triangle->v0 <= VertexCount(), "v0 has an invalid vertex index!" );
		debug_assert ( triangle->v1 <= VertexCount(), "v1 has an invalid vertex index!" );
		debug_assert ( triangle->v2 <= VertexCount(), "v2 has an invalid vertex index!" );

		//Calculate the face normal
		Math::Vector3D v0v1 = m_vertices[triangle->v1].position - m_vertices[triangle->v0].position;
		Math::Vector3D v0v2 = m_vertices[triangle->v2].position - m_vertices[triangle->v0].position;

		Math::Vector3D::CrossProduct ( v0v1, v0v2, triangle->faceNormal );
		triangle->faceNormal.Normalise();
	}

	VertexIterator vertex = VerticesBegin();
	VertexIterator vertexEnd = VerticesEnd();
	UInt		   vertexUsageCount = 0;
	UInt		   vertexIndex = 0;

	//Then generate vertex normals
	for ( ; vertex != vertexEnd; ++vertex, ++vertexIndex )
	{
		vertexUsageCount = 0;

		//Go through each triangle, checking to see
		//if it uses this vertex
		for ( triangle = TrianglesBegin(); triangle != trianglesEnd; ++triangle )
		{
			if (	( triangle->v0 == vertexIndex )
				||  ( triangle->v1 == vertexIndex )
				||  ( triangle->v2 == vertexIndex ) )
			{
				++vertexUsageCount;
				vertex->normal += triangle->faceNormal;
			}
		}

		vertex->normal /= vertexUsageCount;
		vertex->normal.Normalise();
	}

}
//End Mesh::GenerateNormals



//=========================================================================
//! @function    Mesh::CreateMeshVertexBuffer
//! @brief       Create the vertex buffer for the vertex data
//!              
//! @param		 renderer [in] Renderer to get the vertex buffer from
//!
//! @throw		 Core::RuntimeError
//=========================================================================
void Mesh::CreateMeshVertexBuffer ( Renderer::IRenderer& renderer )
{
	//Create the vertex buffer
	Renderer::HVertexBuffer stream0 
				= renderer.CreateVertexBuffer ( sizeof(MeshStream0), m_vertices.size(), Renderer::USAGE_STATICWRITEONLY  );

	m_vertexStreams.SetStream ( stream0, 0 );


	//Create the vertex declaration
	Renderer::VertexDeclarationDescriptor descriptor;
	descriptor.AddElement ( 0, 0, Renderer::DECLTYPE_FLOAT3, Renderer::DECLUSAGE_POSITION, 0 ); 
	descriptor.AddElement ( 0, 12, Renderer::DECLTYPE_FLOAT3, Renderer::DECLUSAGE_NORMAL, 0 ); 
	descriptor.AddElement ( 0, 24, Renderer::DECLTYPE_COLOUR, Renderer::DECLUSAGE_DIFFUSE, 0 );
	descriptor.AddElement ( 0, 28, Renderer::DECLTYPE_FLOAT2, Renderer::DECLUSAGE_TEXCOORD, 0 ); 

	m_vertexDeclaration = renderer.AcquireVertexDeclaration ( descriptor );

}
//End Mesh::CreateMesh



//=========================================================================
//! @function    Mesh::FillVertexBuffer
//! @brief       Fill the mesh's vertex buffer
//!              
//! @throw		 Core::RuntimeError              
//=========================================================================
void Mesh::FillVertexBuffer ( )
{
	Renderer::HVertexBuffer stream0 = m_vertexStreams.GetStream ( 0 );

	debug_assert ( stream0, "Null vertex buffer handle!" );

	//Lock the vertex buffer
	Renderer::ScopedVertexBufferLock lock = stream0->LockAll ( Renderer::LOCK_NORMAL );

	if ( !lock )
	{
		throw Core::RuntimeError ( "Error, couldn't lock vertex buffer!", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	MeshStream0* vertex = reinterpret_cast<MeshStream0*>( lock.GetLockPointer() );

	//Copy all of the vertices into the vertex buffer
	for ( ConstVertexIterator itr = VerticesBegin(); itr != VerticesEnd(); ++itr )
	{
		vertex->position[0] = itr->position.X();
		vertex->position[1] = itr->position.Y();
		vertex->position[2] = itr->position.Z();

		vertex->normal[0] = itr->normal.X();
		vertex->normal[1] = itr->normal.Y();
		vertex->normal[2] = itr->normal.Z();

		vertex->colour = itr->colour;

		debug_assert ( vertex->colour = 0xFFFFFFFF, "Bullshit is happening here" );

		vertex->texcoord[0] = itr->texCoord0.X();
		vertex->texcoord[1] = itr->texCoord0.Y();

		++vertex;
	}
}
//End Mesh::FillIndexBuffer



//=========================================================================
//! @function    Mesh::CreateMeshIndexBuffer
//! @brief       Create the index buffer to store the indices
//!              
//! @param       renderer [in] 
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void Mesh::CreateMeshIndexBuffer ( Renderer::IRenderer& renderer )
{
	//Get the number of indices by adding the number of indices from each mesh group
	UInt indexCount = 0;

	for ( ConstMeshGroupIterator itr = MeshGroupsBegin(); itr != MeshGroupsEnd(); ++itr )
	{
		indexCount += itr->IndexCount();
	}

	//Multiply by three, since each triangle has three vertices
	indexCount *= 3;

	//Now create the vertex buffer
	m_indexBuffer = renderer.CreateIndexBuffer ( Renderer::INDEX_16BIT, indexCount, 
												 Renderer::USAGE_STATICWRITEONLY );

	if ( !m_indexBuffer )
	{
		throw Core::RuntimeError ( "Couldn't create index buffer!", 0, __FILE__, __FUNCTION__, __LINE__ );
	}
}
//End Mesh::CreateMeshIndexBuffer


//=========================================================================
//! @function    Mesh::FillIndexBuffer
//! @brief       Fill the mesh index buffer with indices from the mesh groups
//!              
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void Mesh::FillIndexBuffer ( )
{
	
	//First lock the buffer
	Renderer::ScopedIndexBufferLock lock = m_indexBuffer->LockAll( Renderer::LOCK_NORMAL );

	if ( !lock )
	{
		throw Core::RuntimeError ( "Error, couldn't lock index buffer!", 0,
									__FILE__, __FUNCTION__, __LINE__ );
	}

	UInt16*	currentIndex = reinterpret_cast<UInt16*>( lock.GetLockPointer() );

	//Iterate through each mesh group, copying the vertex indices into the index buffer
	for ( ConstMeshGroupIterator group = MeshGroupsBegin(); group != MeshGroupsEnd(); ++group )
	{
		
		for ( MeshGroup::ConstIndexIterator index = group->IndicesBegin();
			 index != group->IndicesEnd();
			 ++index )
		{
		
			*currentIndex = m_triangles[*index].v0;
			++currentIndex;

			*currentIndex = m_triangles[*index].v1;
			++currentIndex;

			*currentIndex = m_triangles[*index].v2;
			++currentIndex;

		}
	}


}
//End Mesh::FillIndexBuffer


//=========================================================================
//! @function    Mesh::QueueForRendering
//! @brief       Queue all mesh groups for rendering
//!              
//! @param		 queue		 [in] Queue to add the mesh to
//! @param		 worldMatrix [in] worldMatrix, world matrix to transform the mesh by on rendering
//! @param		 lodIndex	 [in] lodIndex, LOD index at which to render the mesh
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void Mesh::QueueForRendering ( Renderer::RenderQueue& queue, const Math::Matrix4x4& worldMatrix, UInt lodIndex )
{
	MeshGroupIterator itr = MeshGroupsBegin();
	MeshGroupIterator end = MeshGroupsEnd();

	for ( ; itr != end; ++itr )
	{
		itr->QueueForRendering ( queue, 
								 m_vertexDeclaration,
								 m_indexBuffer,
								 m_vertexStreams,
								 worldMatrix,
								 lodIndex );
	}
}
//End Mesh::QueueForRendering



//=========================================================================
//! @function    Mesh::Render
//! @brief       Doesn't really do anything. Rendering is handled by the MeshGroup
//!              class. This is only here because this class implements the IRenderable 
//!              interface
//!              
//! @param       renderer 
//!              
//! @return      
//! @throw       
//=========================================================================
void Mesh::Render ( Renderer::IRenderer& renderer )
{

}
//End Mesh::Render



//=========================================================================
//! @function    MeshGroup::QueueForRendering
//! @brief       Add a mesh group to the render queue
//!              
//!              
//! @param       queue 
//! @param       vertexDeclaration 
//! @param       indexBuffer 
//! @param       streamBinding 
//!              
//! @return      
//! @throw       
//=========================================================================
void MeshGroup::QueueForRendering ( Renderer::RenderQueue& queue, 
									Renderer::HVertexDeclaration& vertexDeclaration,
									Renderer::HIndexBuffer& indexBuffer,
									Renderer::VertexStreamBinding& streamBinding,
									const Math::Matrix4x4& worldMatrix,
									UInt lodIndex )
{
	if ( !m_effect )
	{
		std::cerr << __FUNCTION__ << " Mesh has no effect!" << std::endl;
		return;
	}

	for ( UInt passIndex = 0; passIndex < m_effect->Techniques(0).PassCount(); ++passIndex )
	{
		queue.QueueForRendering ( *this, 
								  m_effect, 
								  m_effect->GetBestTechniqueForLOD(lodIndex), 
								  passIndex,
								  vertexDeclaration,
								  streamBinding,
								  indexBuffer,
								  worldMatrix );
	}

}
//End MeshGroup::QueueForRendering


//=========================================================================
//! @function    MeshGroup::Render
//! @brief       Render a mesh group
//!              
//! @param       renderer [in] 
//!              
//=========================================================================
void MeshGroup::Render ( Renderer::IRenderer& renderer )
{
	
	renderer.DrawIndexedPrimitive ( Renderer::PRIM_TRIANGLELIST,
									0,
									m_maxVertexIndex,
									m_startOffset,
									m_triangleIndices.size() * 3 );

}
//End MeshGroup::Render

