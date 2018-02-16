//======================================================================================
//! @file         StateManager.h
//! @brief        Class to manage the changing of render states in an efficient manner
//!               
//!               Sends only changed render states to the renderer
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 30 June 2005
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


#ifndef RENDERER_STATEMANAGER_H
#define RENDERER_STATEMANAGER_H


#include "Renderer/Effect.h"
#include "Renderer/RendererConstants.h"
#include "Renderer/RenderState.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexDeclaration.h"



//namespace Renderer
namespace Renderer
{


	//=========================================================================
	// Forward declarations
	//=========================================================================
	class IRenderer;
	class VertexData;
	class AutogenTextureManager;



	//!@class	StateManager
	//!@brief	Class to manage the changing of render states in an efficient manner
	//!
	//!			Sends only changed render states to the renderer
	class StateManager
	{
		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			StateManager ( IRenderer& renderer, AutogenTextureManager& manager );


            //=========================================================================
            // Public methods
            //=========================================================================
			void ActivateRenderState ( HEffect& effect, UInt techniqueIndex, UInt passIndex  );

			void ActivateRenderState ( const RenderState& state );

			void ActivateVertexDeclaration ( HVertexDeclaration& data );

			void ActivateVertexStreamBinding ( VertexStreamBinding& binding );

			void ActivateIndexBuffer ( HIndexBuffer& buffer );


		private:

            //=========================================================================
            // Private methods
            //=========================================================================
			void SyncRendererState   ( const RenderState& state );
			void SyncRendererTextureUnit ( const TextureUnit& textureUnit, UInt index );


            //=========================================================================
            // Private data
            //=========================================================================
			IRenderer&				m_renderer;
			AutogenTextureManager&  m_autogenManager;

			const RenderState*	m_renderState;
			HVertexBuffer		m_vertexBuffers[g_maxStreams];
			HIndexBuffer		m_indexBuffer;

			HVertexDeclaration	m_declaration;
            
			HEffect				m_effect;
			UInt				m_techniqueIndex;
			UInt				m_passIndex;

	};
	//End class StateManager



};
//end namespace Renderer


#endif
//#ifndef RENDERER_STATEMANAGER_H


