//======================================================================================
//! @file         MeshLoader.h
//! @brief        Class that loads a mesh from a file
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 10 August 2005
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

#ifndef OIDFX_MESHLOADER_H
#define OIDFX_MESHLOADER_H



//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer	{ class IRenderer;	class EffectManager;	}
namespace OidFX		{ class Mesh;								}



//namespace OidFX
namespace OidFX
{



	//!@class	MeshLoader
	//!@brief	Class that loads a mesh from a file
	class MeshLoader
	{

		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			inline MeshLoader ( Renderer::IRenderer& renderer, Renderer::EffectManager& effectManager );


            //=========================================================================
            // Public methods
            //=========================================================================
			boost::shared_ptr<Mesh> Load ( const Char* fileName );


		private:

            //=========================================================================
            // Private data
            //=========================================================================
			Renderer::IRenderer&		m_renderer;
			Renderer::EffectManager&	m_effectManager;


	};
	//End class MeshLoader



    //=========================================================================
    //! @function    MeshLoader::MeshLoader
    //! @brief       MeshLoader constructor
    //!              
    //! @param       renderer		[in] Renderer used to request vertex\index buffer resources
    //! @param       effectManager	[in] Effect manager used to request effects
    //!              
    //=========================================================================
	MeshLoader::MeshLoader ( Renderer::IRenderer& renderer, Renderer::EffectManager& effectManager )
		: m_renderer(renderer), m_effectManager(effectManager)
	{

	}
	//End MeshLoader::MeshLoader




}
//end namespace OidFX


#endif
//#ifndef OIDFX_MESHLOADER_H

