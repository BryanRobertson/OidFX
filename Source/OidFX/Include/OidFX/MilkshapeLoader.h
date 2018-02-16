//======================================================================================
//! @file         MilkshapeLoader.h
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


#ifndef OIDFX_MILKSHAPELOADER_H
#define OIDFX_MILKSHAPELOADER_H



//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer	{ class EffectManager; class IRenderer;	}
namespace OidFX		{ class Mesh;	}


namespace Milkshape
{

	//=========================================================================
	// Constants
	//=========================================================================

	//Milkshape constants
	const UInt maxVertices     = 65534;
	const UInt maxTriangles    = 65534;
	const UInt maxGroups       = 255;
	const UInt maxMaterials    = 128;
	const UInt maxJoints       = 128;
	const UInt maxKeyFrames    = 216;   


	//=========================================================================
	// Structures used to store data from a milkshape file
	//=========================================================================
	#include "Core/PushPack1.h" //Change the packing to 1

	//Header
	struct Header
	{
		Char    id[10];        // always "MS3D000000"
		Int     version;       // 4
	};
	//End Header

	//Vertex
	struct Vertex
	{
		UChar    flags;              // SELECTED | SELECTED2 | HIDDEN
		Float   vertex[3];          //
		Char    boneId;             // -1 = no bone
		UChar    referenceCount;
	};
	//End Vertex

	//Triangle
	struct Triangle
	{
		Word    flags;                                      // SELECTED | SELECTED2 | HIDDEN
		Word    vertexIndices[3];                           //
		Float   vertexNormals[3][3];                        //
		Float   s[3];                                       //
		Float   t[3];                                       //
		UChar    smoothingGroup;                             // 1 - 32
		UChar    groupIndex;                                 //
	};
	//End Triangle

	//MeshGroupHeader
	struct MeshGroupHeader
	{
		UChar            flags;                              // SELECTED | HIDDEN
		Char            name[32];                           //
		Word            numtriangles;                       
	};
	//End MeshGroupHeader

	//MeshGroup
	struct MeshGroup
	{
		MeshGroupHeader		header;
		std::vector<Word>	triangleIndices;
		Char				materialIndex;					// -1 = no material
	};
	//End MeshGroup

	//Material
	struct Material
	{
		Char            name[32];                           //
		Float           ambient[4];                         //
		Float           diffuse[4];                         //
		Float           specular[4];                        //
		Float           emissive[4];                        //
		Float           shininess;                          // 0.0f - 128.0f
		Float           transparency;                       // 0.0f - 1.0f
		Char            mode;                               // 0, 1, 2 is unused now
		Char            texture[128];                       // texture.bmp
		Char            alphamap[128];                      // alpha.bmp
	};
	//End Material

	#include "Core/PopPack.h"	//Restore the packing


    //=========================================================================
    // Milkshape Loader 
    //=========================================================================
	
	//!@class	MilkshapeLoader
	//!@brief	Class used to load milkshape files from disk
	class MilkshapeLoader
	{

		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			inline MilkshapeLoader ( Renderer::IRenderer& renderer, Renderer::EffectManager& effectManager );


            //=========================================================================
            // Public methods
            //=========================================================================
			boost::shared_ptr<OidFX::Mesh> Load ( std::istream& file, const Char* name );


		private:


            //=========================================================================
            // Private types
            //=========================================================================
			typedef	std::vector<Vertex>		VertexStore;
			typedef std::vector<Triangle>	TriangleStore;
			typedef std::vector<MeshGroup>	MeshGroupStore;
			typedef std::vector<Material>	MaterialStore;


            //=========================================================================
            // Private methods
            //=========================================================================
			void ReadVertices ( VertexStore& vertices, std::istream& file );
			void ReadTriangles ( TriangleStore& triangles, std::istream& file );
			void ReadMeshGroups ( MeshGroupStore& meshGroups, std::istream& file );
			void ReadMaterials ( MaterialStore& materials, std::istream& file );

			boost::shared_ptr<OidFX::Mesh> ConvertToMeshData ( const VertexStore& vertices, 
															   const TriangleStore& triangles, 
															   const MeshGroupStore& meshGroups,
															   const MaterialStore& material,
															   const Char* name );

			void SetupTextureCoords ( const TriangleStore& milkshapeTriangleData,
									  OidFX::Mesh::VertexStore& vertices,
									  OidFX::Mesh::TriangleStore& triangles );


            //=========================================================================
            // Private data
            //=========================================================================
			Renderer::IRenderer&		m_renderer;
			Renderer::EffectManager&	m_effectManager;


	};
	//End class MilkshapeLoader



	//=========================================================================
    //! @function    MilkshapeLoader::MilkshapeLoader
    //! @brief       MilkshapeLoader constructor
    //!              
    //! @param       renderer		[in] Renderer used to request vertex\index buffer resources
    //! @param       effectManager	[in] Effect manager used to request effects
    //!              
    //=========================================================================
	MilkshapeLoader::MilkshapeLoader ( Renderer::IRenderer& renderer, Renderer::EffectManager& effectManager )
		: m_renderer(renderer), m_effectManager(effectManager)
	{

	}
	//End MilkshapeLoader::MilkshapeLoader




}


#endif
//#ifndef OIDFX_MILKSHAPELOADER_H