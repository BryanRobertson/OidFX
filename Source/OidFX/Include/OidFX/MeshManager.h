//======================================================================================
//! @file         MeshManager.h
//! @brief        Resource manager for triangle mesh resources
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

#ifndef OIDFX_MESHMANAGER_H
#define OIDFX_MESHMANAGER_H


#include "OidFX/Mesh.h"


//=========================================================================
// Forward declaration
//=========================================================================
namespace Renderer		{ class IRenderer; class EffectManager;	}



//namespace OidFX
namespace OidFX
{


    //=========================================================================
    // Constants
    //=========================================================================
	const UInt	g_maxMeshes = 20;



	//!@class	MeshManager
	//!@brief	Resource manager for triangle mesh resources
	//!
	class MeshManager : public Core::ResourceManager<Mesh>,
						public boost::noncopyable
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			MeshManager ( Renderer::IRenderer& renderer, Renderer::EffectManager& effectManager );

            //=========================================================================
            // Public methods
            //=========================================================================
			HMesh AcquireMesh ( const Char* fileName );


		private:

			Renderer::IRenderer&	 m_renderer;
			Renderer::EffectManager& m_effectManager;

	};
	//End class MeshManager

}
//end namespace OidFX


#endif
//#ifndef OIDFX_MESHMANAGER_H
