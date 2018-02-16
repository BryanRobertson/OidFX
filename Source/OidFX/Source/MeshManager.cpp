//======================================================================================
//! @file         MeshManager.cpp
//! @brief        Resource manager class for Meshes
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 04 August 2005
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
#include "Renderer/EffectManager.h"
#include "OidFX/Mesh.h"
#include "OidFX/MeshManager.h"
#include "OidFX/MeshLoader.h"


using namespace OidFX;



//=========================================================================
//! @function    MeshManager::MeshManager
//! @brief       MeshManager constructor
//!              
//!              
//=========================================================================
MeshManager::MeshManager ( Renderer::IRenderer& renderer, Renderer::EffectManager& effectManager )
: Core::ResourceManager<Mesh>( g_maxMeshes ), m_renderer(renderer), m_effectManager(effectManager)
{

}
//End MeshManager::MeshManager



//=========================================================================
//! @function    MeshManager::AcquireMesh
//! @brief       Get a handle to a Mesh resource
//!              
//!              If the Mesh is not loaded, then it will be loaded from disk
//!				 and a handle to the new Mesh returned.
//!
//!				 Otherwise, a handle to the existing Mesh will be returned
//!              
//! @param       fileName [in]
//!              
//! @return      A handle to the Mesh
//!
//! @throw       Core::RuntimeError, if the mesh could not be loaded for any reason
//=========================================================================
HMesh MeshManager::AcquireMesh ( const Char* fileName )
{
	HandleType handle = AcquireExistingResource ( fileName );

	if ( handle == Core::NullHandle() )
	{
		
		MeshLoader loader ( m_renderer, m_effectManager );
		boost::shared_ptr<Mesh> mesh = loader.Load( fileName );

		return AddNewResource( mesh );
	}
	else
	{
		return handle;
	}

}
//End MeshManager::AcquireMesh 