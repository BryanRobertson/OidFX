//======================================================================================
//! @file         SkyDomeNode.h
//! @brief        Scene graph node responsible for the creation, and rendering
//!				  of a sky box
//!
//!				  Note that I'm not happy with the implementation of the scene graph, and this
//!			      is all going to be scrapped later. The only reason I'm not scrapping it now,
//!			      is due to the time constraints I'm under. I just need to get something that works
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 23 July 2005
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

#ifndef OIDFX_SKYDOME_H
#define OIDFX_SKYDOME_H


#include <boost/shared_ptr.hpp>
#include "Renderer/VertexData.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Effect.h"
#include "OidFX/SceneNode.h"



//namespace OidFX
namespace OidFX
{


	//!@class	SkyDomeNode
	//!@brief	Scene graph node responsible for the creation, and rendering
	//!			of a sky box
	class SkyDomeNode : public SceneNode
	{
		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			SkyDomeNode( Scene& scene, Float planetRadius, Float atmosphereRadius, UInt divisions,
						 const Char* effectFileName, Renderer::EffectManager& effectManager );

            //=========================================================================
            // Public methods
            //=========================================================================
			void Restore();

			void QueueForRendering ( Renderer::RenderQueue& queue );
			void Render ( Renderer::IRenderer& renderer );

			//
			void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );


		private:

            //=========================================================================
            // Private types
            //=========================================================================
			struct SkyVertex	
			{
				Float	position[3];
				UInt32	colour;
				Float	texCoord0[2];
			};

            //=========================================================================
            // Private methods
            //=========================================================================
			void CreateSkyVertexBuffer();
			void FillSkyVertexBuffer();
			void CreateSkyIndexBuffer();
			void FillSkyIndexBuffer();

            //=========================================================================
            // Private data
            //=========================================================================
			Renderer::HVertexDeclaration			m_vertexDeclaration;
			Renderer::VertexStreamBinding			m_vertexStreamBinding;
			Renderer::HIndexBuffer					m_indexBuffer;
			Renderer::HEffect						m_effect;

			Float									m_planetRadius;
			Float									m_atmosphereRadius; 
			UInt									m_divisions;

	};
	//End class SkyDomeNode


}
//end namespace OidFX



#endif
//#ifndef OIDFX_SKYDOME_H

