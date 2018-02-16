//======================================================================================
//! @file         MilkshapeLoader.cpp
//! @brief        Structures, globals and classes related to loading milkshape files
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 16 August 2005
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


#include <iterator>
#include <boost/pool/pool_alloc.hpp>
#include "Core/Core.h"
#include "Renderer/EffectManager.h"
#include "OidFX/Mesh.h"
#include "OidFX/MilkshapeLoader.h"



using namespace Milkshape;



//=========================================================================
//! @function    MilkshapeLoader::Load
//! @brief       Load a milkshape file from an input stream
//!              
//!              
//! @param       file [in] istream to load the file from 
//! @param		 name [in] Name used to identify the mesh
//!              
//! @return      A pointer to a new OidFX::Mesh object
//! @throw       Core::RuntimeError if there is any problem
//=========================================================================
boost::shared_ptr<OidFX::Mesh> MilkshapeLoader::Load ( std::istream& file, const Char* name )
{
	//First read the header
	Milkshape::Header header;
	file.read ( reinterpret_cast<std::ifstream::char_type*>( &header ), sizeof(header) );

	const Char* headerValue = "MS3D000000";

	//Validate the header contents
	if ( memcmp(header.id, headerValue, sizeof(header.id) ) != 0 )
	{
		std::ostringstream errorMessage;
		errorMessage << "Error, invalid milkshape file: Header ID is invalid";

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	if ( header.version != 4 )
	{
		std::ostringstream errorMessage;
		errorMessage << "Error, " << header.version << " is an unsupported version of the milkshape format"
			            " this reader supports version 4 only.";

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	VertexStore vertices;
	ReadVertices ( vertices, file );

	TriangleStore triangles;
	ReadTriangles ( triangles, file );

	MeshGroupStore meshGroups;
	ReadMeshGroups ( meshGroups, file );

	MaterialStore materials;
	ReadMaterials ( materials, file );

	return ConvertToMeshData ( vertices, triangles, meshGroups, materials, name );

}
//End MilkshapeLoader::Load



//=========================================================================
//! @function    MilkshapeLoader::ReadVertices
//! @brief       Read vertices from the milkshape file into an array
//!              
//!              
//! @param       file [in] istream to load the vertices from 
//!              
//! @throw       Core::RuntimeError if there is any problem
//=========================================================================
void MilkshapeLoader::ReadVertices ( VertexStore& vertices, std::istream& file )
{

	//Read in the number of vertices
	Word vertexCount = 0;
	file.read ( reinterpret_cast<std::ifstream::char_type*>(&vertexCount), sizeof(vertexCount) );

	if ( vertexCount > Milkshape::maxVertices )
	{
		std::cerr << "Warning! Number of vertices (" << vertexCount << 
				  ") exceeds milkshapes maximum (" << maxVertices << ") File may be corrupt" << std::endl;
	}

	//Read in the vertices
	vertices.reserve ( vertexCount );

	Milkshape::Vertex tempVertex;

	for ( Word i=0; i < vertexCount; ++i )
	{
		file.read ( reinterpret_cast<std::ifstream::char_type*>(&tempVertex), sizeof(tempVertex) );
		vertices.push_back( tempVertex );
/*
		std::cout << (UInt)tempVertex.flags << "\t"
				  << tempVertex.vertex[0] << "\t"
				  << tempVertex.vertex[1] << "\t"
				  << tempVertex.vertex[2] << "\t" << std::endl;
*/
		debug_assert ( tempVertex.boneId == -1, "Error" );
	}
/*
	file.read ( reinterpret_cast<std::ifstream::char_type*>(&vertices[0]), 
				sizeof(Milkshape::Vertex) * vertexCount );
*/


}
//End MilkshapeLoader::ReadVertices



//=========================================================================
//! @function    MilkshapeLoader::ReadTriangles
//! @brief       Read triangles from the milkshape file into an array 
//!              
//!              
//! @param       file [in] istream to load the triangles from 
//!              
//! @throw       Core::RuntimeError if there is any problem
//=========================================================================
void MilkshapeLoader::ReadTriangles ( TriangleStore& triangles, std::istream& file )
{

	//Read in the number of triangles
	Word triangleCount = 0;
	file.read ( reinterpret_cast<std::ifstream::char_type*>(&triangleCount), sizeof(triangleCount) );

	if ( triangleCount > Milkshape::maxTriangles )
	{
		std::cerr << "Warning! Number of triangles (" << triangleCount << 
				  ") exceeds milkshapes maximum (" << maxTriangles << ") File may be corrupt" << std::endl;
	}

	//Read in the triangles
	triangles.reserve(triangleCount);

	Milkshape::Triangle tempTriangle;

	for ( UInt i=0; i < triangleCount; ++i )
	{
		file.read ( reinterpret_cast<std::ifstream::char_type*>(&tempTriangle), sizeof(tempTriangle) );
		triangles.push_back( tempTriangle );
	}

}
//End MilkshapeLoader::ReadTriangles



//=========================================================================
//! @function    MilkshapeLoader::ReadMeshGroups
//! @brief       Read mesh groups from the milkshape file into an array
//!              
//!              
//! @param       file [in] istream to load the mesh groups from 
//!              
//! @throw       Core::RuntimeError if there is any problem
//=========================================================================
void MilkshapeLoader::ReadMeshGroups ( MeshGroupStore& meshGroups, std::istream& file )
{

	//Read in the number of mesh groups
	Word meshGroupCount = 0;
	file.read ( reinterpret_cast<std::ifstream::char_type*>(&meshGroupCount), sizeof(meshGroupCount) );

	if ( meshGroupCount > Milkshape::maxGroups )
	{
		std::cerr << "Warning! Number of groups (" << meshGroupCount << 
				  ") exceeds milkshapes maximum (" << maxGroups << ") File may be corrupt" << std::endl;
	}

	//Read in the mesh groups
	meshGroups.reserve( meshGroupCount );

	for ( UInt i=0; i < meshGroupCount; ++i )
	{

		//Add a new meshgroup to the meshgroup array
		meshGroups.push_back( Milkshape::MeshGroup() );

		Milkshape::MeshGroup& currentGroup = meshGroups.back();

		//Read in the header
		file.read ( reinterpret_cast<std::ifstream::char_type*>(&currentGroup.header), sizeof(Milkshape::MeshGroupHeader) );

		//Reserve space for the triangle indices
		currentGroup.triangleIndices.resize ( currentGroup.header.numtriangles );

		//Read in the triangle indices
		file.read ( reinterpret_cast<std::ifstream::char_type*>(&currentGroup.triangleIndices[0]), 
					sizeof(Word) * currentGroup.header.numtriangles );

		//Read in the material index
		file.read ( reinterpret_cast<std::ifstream::char_type*>(&currentGroup.materialIndex),
					sizeof(currentGroup.materialIndex) );
		
	}

}
//End MilkshapeLoader::ReadMeshGroups



//=========================================================================
//! @function    MilkshapeLoader::ReadMaterials 
//! @brief       Read materials from the milkshape file into an array
//!              
//!				 Note that the actual material properties are ignored.
//!				 Only the name of the material is used, as a filename for an effect file
//!              
//! @param       file [in] istream to load the materials from 
//!              
//! @throw       Core::RuntimeError if there is any problem
//=========================================================================
void MilkshapeLoader::ReadMaterials ( MaterialStore& materials, std::istream& file )
{
	//Read in the number of materials
	Word materialCount = 0;
	file.read ( reinterpret_cast<std::ifstream::char_type*>(&materialCount), sizeof(materialCount) );

	if ( materialCount > Milkshape::maxMaterials )
	{
		std::cerr << "Warning! Number of materials (" << materialCount << 
				  ") exceeds milkshapes maximum (" << maxMaterials << ") File may be corrupt" << std::endl;
	}

	//Read in the mesh groups
	materials.reserve( materialCount );
	Milkshape::Material tempMaterial;

	for ( UInt i=0; i < materialCount; ++i )
	{
		file.read ( reinterpret_cast<std::ifstream::char_type*>(&tempMaterial), sizeof(tempMaterial) );
		materials.push_back( tempMaterial );
	}

}
//End MilkshapeLoader::ReadMaterials



//=========================================================================
//! @function    MilkshapeLoader::ConvertToMeshData 
//! @brief       Convert the data loaded from the milkshape file
//!				 into the form used by the OidFX engine
//!              
//!
//! @param		 vertices	[in] Array of vertices from the milkshape file
//! @param		 triangles	[in] Array of triangles from the milkshape file
//! @param		 meshGroups [in] Array of mesh groups from the milkshape file
//! @param		 material	[in] Array of materials from the milkshape file
//!
//! @throw       Core::RuntimeError if there is any problem
//=========================================================================
boost::shared_ptr<OidFX::Mesh> MilkshapeLoader::ConvertToMeshData ( const VertexStore& vertices,
																	const TriangleStore& triangles,
																	const MeshGroupStore& meshGroups,
																	const MaterialStore& materials,
																	const Char* name )
{
	//First create the array of vertices
	OidFX::Mesh::VertexStore outputVertices;
	outputVertices.reserve( vertices.size() );

	for ( MilkshapeLoader::VertexStore::const_iterator currentVertex = vertices.begin();
		  currentVertex != vertices.end();
		  ++currentVertex )
	{
		outputVertices.push_back(OidFX::Mesh::Vertex());

		OidFX::Mesh::Vertex& vertex = outputVertices.back();
		vertex.position.Set( currentVertex->vertex[0], 
							 currentVertex->vertex[1], 
							 currentVertex->vertex[2] );

		vertex.colour.Set ( 1.0f, 1.0f, 1.0f, 1.0f );

	}

	//Now create the array of triangles
	OidFX::Mesh::TriangleStore outputTriangles;
	outputTriangles.reserve ( triangles.size() );

	for ( MilkshapeLoader::TriangleStore::const_iterator currentTriangle = triangles.begin();
		  currentTriangle != triangles.end();
		  ++currentTriangle )
	{
		outputTriangles.push_back(OidFX::Mesh::Triangle(currentTriangle->vertexIndices[0],
														currentTriangle->vertexIndices[1],
														currentTriangle->vertexIndices[2],
														currentTriangle->smoothingGroup));
	}

	//Create an array of effects, using the material names from the 
	//milkshape file to load effect files
	OidFX::Mesh::EffectStore outputEffects;
	outputEffects.reserve ( materials.size() );

	const Char* effectBase = "Data/Art/Effects/";
	std::string materialName;

	for ( MilkshapeLoader::MaterialStore::const_iterator currentMaterial = materials.begin();
		  currentMaterial != materials.end();
		  ++currentMaterial )
	{
		materialName = effectBase;
		materialName += currentMaterial->name;

		Renderer::HEffect effect = m_effectManager.AcquireEffect ( materialName.c_str() );

		outputEffects.push_back(effect);
	}

	SetupTextureCoords ( triangles, outputVertices, outputTriangles );

	//Now we have all the information we need to set up the mesh groups
	std::vector<OidFX::MeshGroupDescriptor> outputMeshGroups;
	outputMeshGroups.reserve ( meshGroups.size() );

	for ( MilkshapeLoader::MeshGroupStore::const_iterator currentMeshGroup = meshGroups.begin();
		 currentMeshGroup != meshGroups.end();
		 ++currentMeshGroup )
	{

		debug_assert ( currentMeshGroup->materialIndex < static_cast<Int>(meshGroups.size()), "Invalid material!" );
		
		//Copy the Word triangle indices into an array of UInt indices
		std::vector<UInt> indices;
		std::copy ( currentMeshGroup->triangleIndices.begin(),
					currentMeshGroup->triangleIndices.end(),
					std::back_inserter(indices) );

		outputMeshGroups.push_back( OidFX::MeshGroupDescriptor ( currentMeshGroup->header.name, 
									 outputEffects[currentMeshGroup->materialIndex],
									  indices ) );

	}

	//Finally, create the mesh object

	boost::shared_ptr<OidFX::Mesh> mesh ( new OidFX::Mesh ( m_renderer, 
															name, 
															outputVertices, 
															outputTriangles,
															outputEffects,
															outputMeshGroups ) );

	return mesh;
}
//End MilkshapeLoader::ConvertToMeshData 



//=========================================================================
//! @function    MilkshapeLoader::SetupTextureCoords
//! @brief       Set up the texture coordinate data
//!
//!				 The vertex array doesn't have any texture coordinates set
//!				 due to the fact that the milkshape format stores the texture coordinated in the
//!				 triangles, not the vertices.
//!				 
//!				 Since our mesh format only allows one texture coordinate set per-vertex
//!				 we're going to go through every triangle, checking to see if its texture coords
//!				 match the texture coordinates already set for its vertices. If any of the vertices
//!				 have different texture coordinates, then we'll simply duplicate those vertices, and
//!				 set the triangle to have those new vertices
//!
//! @param		 milkshapeTriangleData [in] Triangle data from milkshape, including the texture coordinates
//! @param		 vertices			   [in] Output vertex data to have its texture coordinates set
//! @param		 triangles			   [in] Output triangle data to be altered, in the case that any vertices need 
//!											to be duplicated
//!
//! @throw       Core::RuntimeError if there is any problem
//=========================================================================
void MilkshapeLoader::SetupTextureCoords ( const MilkshapeLoader::TriangleStore& milkshapeTriangleData,
										  OidFX::Mesh::VertexStore& vertices,
										  OidFX::Mesh::TriangleStore& triangles )
{
	
	
	debug_assert ( milkshapeTriangleData.size() == triangles.size(), "Error in triangle data!" );

	//Create an array of boolean values, indicating whether or not the texture coordinate
	//for a member of the vertex array is set
	std::vector<bool> isTexCoordSet ( vertices.size(), false );

	for ( UInt tri = 0; tri < milkshapeTriangleData.size(); ++tri )
	{

		debug_assert ( milkshapeTriangleData[tri].vertexIndices[0] < vertices.size(), "Triangle vertex out of range!" ); 

		//Create references to some of the variables to make the code more readable
		OidFX::Mesh::Vertex& v0 = vertices[milkshapeTriangleData[tri].vertexIndices[0]];
		OidFX::Mesh::Vertex& v1 = vertices[milkshapeTriangleData[tri].vertexIndices[1]];
		OidFX::Mesh::Vertex& v2 = vertices[milkshapeTriangleData[tri].vertexIndices[2]];

		const Milkshape::Triangle& milkshapeTri = milkshapeTriangleData[tri];
		OidFX::Mesh::Triangle& currentTri = triangles[tri];

		//Vertex 0
		if ( isTexCoordSet[ milkshapeTri.vertexIndices[0] ] )
		{
			//Check to see if the texture coordinates match the coordinates
			//of the triangle's vertices. If not, duplicate the vertex
			if (	( v0.texCoord0.X() != milkshapeTri.s[0]) 
				 || ( v0.texCoord0.Y() != milkshapeTri.t[0]) )
			{
				vertices.push_back( OidFX::Mesh::Vertex(v0) );
				vertices.back().texCoord0.X( milkshapeTri.s[0] );
				vertices.back().texCoord0.Y( milkshapeTri.t[0] );

				currentTri.v0 = vertices.size() - 1;

				#ifdef DEBUG_BUILD
					std::clog << __FUNCTION__ " texture coordinate mismatch, duplicating vertex 0" << std::endl;
				#endif
			}

		}
		else
		{
			//Texture coordinate for this vertex hasn't been set yet, set it now
			v0.texCoord0.X( milkshapeTri.s[0] );
			v0.texCoord0.Y( milkshapeTri.t[0] );
		}

		//Vertex 1
		if ( isTexCoordSet[ milkshapeTri.vertexIndices[1] ] )
		{
			//Check to see if the texture coordinates match the coordinates
			//of the triangle's vertices. If not, duplicate the vertex
			if (	( v1.texCoord0.X() != milkshapeTri.s[1]) 
				 || ( v1.texCoord0.Y() != milkshapeTri.t[1]) )
			{
				vertices.push_back( OidFX::Mesh::Vertex(v1) );
				vertices.back().texCoord0.X( milkshapeTri.s[1] );
				vertices.back().texCoord0.Y( milkshapeTri.t[1] );

				currentTri.v1 = vertices.size() - 1;

				#ifdef DEBUG_BUILD
					std::clog << __FUNCTION__ " texture coordinate mismatch, duplicating vertex 1" << std::endl;
				#endif
			}

		}
		else
		{
			//Texture coordinate for this vertex hasn't been set yet, set it now
			v1.texCoord0.X( milkshapeTri.s[1] );
			v1.texCoord0.Y( milkshapeTri.t[1] );
		}


		//Vertex 2
		if ( isTexCoordSet[ milkshapeTri.vertexIndices[2] ] )
		{
			//Check to see if the texture coordinates match the coordinates
			//of the triangle's vertices. If not, duplicate the vertex
			if (	( v2.texCoord0.X() != milkshapeTri.s[2]) 
				 || ( v2.texCoord0.Y() != milkshapeTri.t[2]) )
			{
				vertices.push_back( OidFX::Mesh::Vertex(v2) );
				vertices.back().texCoord0.X( milkshapeTri.s[2] );
				vertices.back().texCoord0.Y( milkshapeTri.t[2] );

				currentTri.v2 = vertices.size() - 1;

				#ifdef DEBUG_BUILD
					std::clog << __FUNCTION__ " texture coordinate mismatch, duplicating vertex 2" << std::endl;
				#endif
			}

		}
		else
		{
			//Texture coordinate for this vertex hasn't been set yet, set it now
			v2.texCoord0.X( milkshapeTri.s[2] );
			v2.texCoord0.Y( milkshapeTri.t[2] );
		}


	}

}
//End MilkshapeLoader::SetupTextureCoords

