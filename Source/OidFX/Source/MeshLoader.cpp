//======================================================================================
//! @file         MeshLoader.cpp
//! @brief        Class that loads a mesh from a file
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 15 August 2005
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
#include "OidFX/MeshLoader.h"
#include "OidFX/MilkshapeLoader.h"



using namespace OidFX;



//=========================================================================
//! @function    MeshLoader::Load
//! @brief       Load a mesh from a milkshape file
//!              
//!				 Note that the material properties in milkshape are completely
//!				 ignored. Instead, the name of the material is used to find
//!				 an effect file,
//!              
//! @param       fileName [in] Filename of mesh to load
//!              
//! @return      A pointer to a new Mesh object
//! @throw		 Core::RuntimeError if the mesh load fails
//=========================================================================
boost::shared_ptr<Mesh> MeshLoader::Load ( const Char* fileName )
{
	debug_assert ( fileName, "Filname is null!" );

	std::ifstream meshFile ( fileName, std::ios::binary );

	if ( !meshFile )
	{
		std::ostringstream errorMessage;
		errorMessage << "Error, couldn't open mesh file " << fileName;

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	std::clog << __FUNCTION__ << ": Mesh " << fileName << " opened for reading!" << std::endl;

	Milkshape::MilkshapeLoader loader ( m_renderer, m_effectManager );
	
	return loader.Load ( meshFile, fileName );

}
//End MeshLoader::Load