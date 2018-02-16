//======================================================================================
//! @file         StateManager.cpp
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



#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/StateManager.h"
#include "Renderer/AutogenTextureManager.h"
#include "Renderer/RenderState.h"


using namespace Renderer;




//=========================================================================
//! @function    StateManager::StateManager
//! @brief       StateManager constructor
//!              
//! @param       renderer [in] Reference to the renderer which will have its states set
//!							   by the state manager
//!              
//=========================================================================
StateManager::StateManager ( IRenderer& renderer, AutogenTextureManager& autogenManager )
: m_renderer(renderer), m_renderState(0), m_autogenManager(autogenManager), m_passIndex(0), m_techniqueIndex(0)
{
	
}
//End StateManager::StateManager



//=========================================================================
//! @function    StateManager::ActivateRenderState
//! @brief       Activates a render state
//!              
//! @param       effect			[in] Effect to get the render state from
//! @param       techniqueIndex [in] Index of technique to get from the effect
//! @param       passIndex		[in] Index of pass from the technique, that holds the render state
//!              
//=========================================================================
void StateManager::ActivateRenderState ( HEffect& effect, UInt techniqueIndex, UInt passIndex )
{
	debug_assert ( !effect.IsNull(), "Tried to activate a null effect" );
	debug_assert ( techniqueIndex < effect->TechniqueCount(), "Technique index out of range!" );
	debug_assert ( passIndex < effect->Techniques(techniqueIndex).PassCount(), "Pass index out of range!" );

	if (   (m_renderState) 
		&& ( effect.Value() == m_effect.Value() ) 
		&& (techniqueIndex == m_techniqueIndex) 
		&& ( passIndex == m_passIndex ) )
	{
		return;
	}

	//Set the render state
	m_renderState = &(effect->Techniques( techniqueIndex).Passes(passIndex).GetRenderState());
	m_effect = effect;
	m_techniqueIndex = techniqueIndex;
	m_passIndex = passIndex;
	
	#ifdef DEBUG_BUILD

		static bool renderQueueDebug = false;

		if ( renderQueueDebug )
		{
			std::clog << "\nActivating Effect " << effect->Name()
					<< " Technique " << techniqueIndex << " Pass " << passIndex
					<< "\n" << (const RenderState&)*m_renderState << "\n" << std::endl;
		}

	#endif

	SyncRendererState ( *m_renderState );

}
//End StateManager::ActivateRenderState



//=========================================================================
//! @function    StateManager::ActivateRenderState
//! @brief       Deactivates effects and activates a renderer state
//!				 This method should only be used where necessary.
//!				 when drawing text for example
//!              
//! @param       state [in] State to set
//!              
//=========================================================================
void StateManager::ActivateRenderState ( const RenderState& state )
{
	//Disable all effects, so that they will be reset the next time an effect is activated
	m_renderState = 0;
	m_effect = Core::NullHandle();
	m_techniqueIndex = 0;
	m_passIndex = 0;

	//Syncronise the renderer state with the render state
	SyncRendererState( state );
}
//End StateManager::ActivateRenderState



//=========================================================================
//! @function    StateManager::ActivateVertexStreamBinding
//! @brief       Sets the active vertex stream binding
//!              
//!				 If the vertex buffers are identical to the currently set vertex data, then
//!				 nothing will happen
//!
//! @param       data [in] 
//!              
//=========================================================================
void StateManager::ActivateVertexStreamBinding ( VertexStreamBinding& binding )
{
	for ( UInt i=0; i < g_maxStreams; ++i )
	{
		if ( m_vertexBuffers[i].Value() != binding.GetStream(i).Value() )
		{
			m_vertexBuffers[i] = binding.GetStream(i);
			m_renderer.Bind ( m_vertexBuffers[i], i );
		}
	}
}
//End StateManager::ActivateVertexData



//=========================================================================
//! @function    StateManager::ActivateVertexDeclaration
//! @brief       Set the active vertex declaration
//!              
//!              
//! @param       data [in] 
//!              
//=========================================================================
void StateManager::ActivateVertexDeclaration ( HVertexDeclaration& decl )
{
	if ( m_declaration.Value() != decl.Value() )
	{
		m_declaration = decl;
		m_renderer.Bind ( m_declaration );
	}
}
//End StateManager::ActivateVertexDeclaration



//=========================================================================
//! @function    StateManager::ActivateIndexBuffer
//! @brief       Set the active index buffer.
//!              
//!				 If the index buffer handle is identical to the currently set buffer
//!				 then nothing will happen. Otherwise the renderer's index buffers will be changed
//!
//! @param       buffer [in]
//!              
//! @return      
//! @throw       
//=========================================================================
void StateManager::ActivateIndexBuffer ( HIndexBuffer& buffer )
{
	if ( m_indexBuffer.Value() != buffer.Value() )
	{
		m_indexBuffer = buffer;
		m_renderer.Bind ( m_indexBuffer );
	}
}
//End StateManager::ActivateIndexBuffer



//=========================================================================
//! @function    StateManager::SyncRendererState
//! @brief       Synchronises the renderer's state with that of a render state
//!              
//! @param		 state [in] State to sychronise the renderer with
//!              
//=========================================================================
void StateManager::SyncRendererState ( const RenderState& state )
{
	//Sync the renderer with our new render state
	m_renderer.SetMaterial ( state.GetMaterial() );
	m_renderer.SetMaterialColourSource ( STATE_AMBIENT_MATERIAL_SOURCE, state.GetMaterialSource(STATE_AMBIENT_MATERIAL_SOURCE) ); 
	m_renderer.SetMaterialColourSource ( STATE_DIFFUSE_MATERIAL_SOURCE, state.GetMaterialSource(STATE_DIFFUSE_MATERIAL_SOURCE) );
	m_renderer.SetMaterialColourSource ( STATE_SPECULAR_MATERIAL_SOURCE, state.GetMaterialSource(STATE_SPECULAR_MATERIAL_SOURCE) );
	m_renderer.SetMaterialColourSource ( STATE_EMISSIVE_MATERIAL_SOURCE, state.GetMaterialSource(STATE_EMISSIVE_MATERIAL_SOURCE) );

	m_renderer.SetRenderState ( STATE_BLENDING, state.Blending() );
	m_renderer.SetBlendOp   ( state.BlendOp() );
	m_renderer.SetBlendFunc ( state.SourceBlend(), state.DestBlend() );
	
	m_renderer.SetRenderState ( STATE_DEPTHTEST, state.DepthTest() );
	m_renderer.SetRenderState ( STATE_DEPTHWRITE, state.DepthWrite() );
	m_renderer.SetDepthFunc	  ( state.DepthFunc() );
	m_renderer.SetRenderState ( STATE_DEPTHBIASVALUE, state.DepthBias() );
	
	m_renderer.SetRenderState ( STATE_ALPHATEST, state.AlphaTest() );
	m_renderer.SetAlphaFunc	  ( state.AlphaFunc() );
	m_renderer.SetRenderState ( STATE_ALPHAREFERENCE, state.AlphaReference() );

	m_renderer.SetRenderState ( STATE_STENCIL, state.StencilTest() );
	m_renderer.SetRenderState ( STATE_STENCILREFERENCE, state.StencilRef() );
	m_renderer.SetRenderState ( STATE_STENCILMASK, state.StencilMask() );
	m_renderer.SetRenderState ( STATE_STENCILWRITEMASK, state.StencilWriteMask() );
	m_renderer.SetStencilFunc ( state.StencilFunc() );
	m_renderer.SetStencilOp	  ( STENCILOP_PASS, state.StencilPass() );
	m_renderer.SetStencilOp   ( STENCILOP_FAIL, state.StencilFail() );
	m_renderer.SetStencilOp   ( STENCILOP_ZFAIL, state.StencilZFail() );

	m_renderer.SetCullingMode ( state.CullMode() );

	m_renderer.SetRenderState ( STATE_LIGHTING, state.Lighting() );

	m_renderer.SetShadeMode ( state.ShadeMode() );

	if ( state.FogOverride() )
	{
		m_renderer.SetRenderState ( STATE_FOGBLENDING, true );

		m_renderer.SetFogMode	  ( FOGTYPE_VERTEX, state.FogMode() );
		m_renderer.SetColour	  ( STATE_FOGCOLOUR, state.FogColour() );
		m_renderer.SetRenderState ( STATE_FOGDENSITY, state.FogDensity() );
		m_renderer.SetRenderState ( STATE_FOGSTART, state.FogBegin() );
		m_renderer.SetRenderState ( STATE_FOGEND, state.FogEnd() );

	}
	else
	{
		//TODO: Set the renderer's fog state here

		m_renderer.SetRenderState ( STATE_FOGBLENDING, false );
		m_renderer.SetFogMode ( FOGTYPE_VERTEX, FOGMODE_NONE );
	}

	m_renderer.SetRenderState ( STATE_COLOURWRITE, state.ColourWrite() );
	m_renderer.SetRenderState ( STATE_NORMALISENORMALS, state.NormaliseNormals() );
	m_renderer.SetRenderState ( STATE_SPECULAR, state.SpecularHighlights() );

	for ( UInt index=0; index < state.TextureUnitCount() ; ++index )
	{
		//Make sure we don't set render states for texture units we don't have
		if ( index >=
		  	m_renderer.GetDeviceProperty(CAP_TEXTURE_MAX_SIMULTANEOUS) )
			break;

		SyncRendererTextureUnit( state.TextureUnits(index), index );
	}

	//If the render state doesn't have a render state for every 
	//texture stage, then disable the unused texture stages
	if ( (state.TextureUnitCount() < 
		 (m_renderer.GetDeviceProperty(CAP_TEXTURE_MAX_SIMULTANEOUS) - 1)) )
	{

		m_autogenManager.UnbindAutogenTexture (  static_cast<ETextureStageID>(state.TextureUnitCount()) );

		m_renderer.Bind( HTexture(), 
						 static_cast<ETextureStageID>(state.TextureUnitCount()) );

		m_renderer.SetTextureStageState ( static_cast<ETextureStageID>(state.TextureUnitCount()), 
											TEXSTAGE_COLOUROP, TEXOP_DISABLE ); 
											
	}
}
//End StateManager::SyncRendererState



//=========================================================================
//! @function    StateManager::SyncRendererTextureUnit
//! @brief       Sync the renderer state with the state of one of the 
//!				 current render state's texture units
//!              
//! @param       textureUnit [in]
//! @param       index		 [in]
//!              
//=========================================================================
void StateManager::SyncRendererTextureUnit ( const TextureUnit& textureUnit, UInt index )
{
	debug_assert ( index < TEXTURE_STAGE_COUNT, "Invalid texture stage!" );
	
	ETextureStageID stageID = static_cast<ETextureStageID>(index);

	//Set the texture for the texture stage
	if ( !textureUnit.AutoGenerated() )
	{
		m_autogenManager.UnbindAutogenTexture ( stageID );
		m_renderer.Bind ( textureUnit.TextureHandle(), stageID ); 
	}
	else
	{
		m_autogenManager.BindAutogenTexture ( stageID, textureUnit.NameHash() );
	}

	m_renderer.SetMatrix ( static_cast<EMatrixType>(MAT_TEXTURE0 + index), 
							textureUnit.GetTextureMatrix() );

	//Set up the texture filters
	m_renderer.SetTextureFilter ( stageID, TEXFILTER_MIN, textureUnit.MinFilter() );
	m_renderer.SetTextureFilter ( stageID, TEXFILTER_MAG, textureUnit.MagFilter() );
	m_renderer.SetTextureFilter ( stageID, TEXFILTER_MIP, textureUnit.MipFilter() );
	m_renderer.SetTextureParameter ( stageID, TEXPARAM_MAX_ANISOTROPY,
									 textureUnit.MaxAnisotropy() );

	//Set up the Colour Op
	TextureBlendOp op = textureUnit.ColourOp();
	m_renderer.SetTextureStageState ( stageID, TEXSTAGE_COLOUROP, op.operation );
	m_renderer.SetTextureStageState ( stageID, TEXSTAGE_COLOURARG0, op.arg1 );
	m_renderer.SetTextureStageState ( stageID, TEXSTAGE_COLOURARG1, op.arg2 );

	//Set up the Alpha op
	op = textureUnit.AlphaOp();
	m_renderer.SetTextureStageState ( stageID, TEXSTAGE_ALPHAOP, op.operation );
	m_renderer.SetTextureStageState ( stageID, TEXSTAGE_ALPHAARG0, op.arg1 );
	m_renderer.SetTextureStageState ( stageID, TEXSTAGE_ALPHAARG1, op.arg2 );

	//Set the per-stage constant colour
	m_renderer.SetTextureStageConstantColour ( stageID, textureUnit.ConstantColour() );

	//Set up the addressing mode
	m_renderer.SetTextureAddressingMode ( stageID, TEX_ADDRESS_U,
										  textureUnit.AddressingMode(TEX_ADDRESS_U) ); 
	m_renderer.SetTextureAddressingMode ( stageID, TEX_ADDRESS_V, 
										  textureUnit.AddressingMode(TEX_ADDRESS_V) );
	m_renderer.SetTextureAddressingMode ( stageID, TEX_ADDRESS_W,
										  textureUnit.AddressingMode(TEX_ADDRESS_W) );

	//Set up the texture coordinate set, or texture coordinate generation
	if ( textureUnit.CoordinateGenMode() == TEXGEN_NONE ) 
	{
		m_renderer.SetTextureStageState ( stageID, TEXSTAGE_TEXCOORDINDEX,
											textureUnit.CoordinateSet() );
	}
	else
	{
		m_renderer.SetTextureCoordGeneration ( stageID, textureUnit.CoordinateSet(),
												textureUnit.CoordinateGenMode() );
	}
}
//End StateManager::SyncRendererTextureUnit