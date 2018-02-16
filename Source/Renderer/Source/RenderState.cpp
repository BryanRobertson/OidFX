//======================================================================================
//! @file         RenderState.cpp
//! @brief        RenderState and TextureUnit classes
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 24 June 2005
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
#include "Math/Math.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/Matrix4x4.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderState.h"
#include "Renderer/RendererConstantToString.h"
#include "Renderer/TexturePrecacheList.h"


using namespace Renderer;



//=========================================================================
// RenderState methods
//=========================================================================



//=========================================================================
//! @function    RenderState::RenderState
//! @brief       Construct a render state
//!           
//!              Constructs a render state for the default render state.
//!
//! @return      
//! @throw       
//=========================================================================
RenderState::RenderState ()
: 	m_depthTest( false ),
	m_depthFunc( CMP_LEQUAL ),
	m_depthBias( 0.0f ),
	m_depthWrite( true ),
	m_alphaTest( false ),
	m_alphaFunc( CMP_GEQUAL ),
	m_alphaRef(0.5f),
	m_blendEnable( false ),
	m_blendOp    ( BLEND_ADD ),
	m_stencilTest(false),
	m_stencilFunc(CMP_GEQUAL),
	m_stencilPass(STENCILOP_KEEP),
	m_stencilFail(STENCILOP_ZERO),
	m_stencilZFail(STENCILOP_ZERO),
	m_stencilRef(100),
	m_stencilMask(0xFFFFFFFF),
	m_stencilWriteMask(0xFFFFFFFF),
	m_culling( CULL_NONE ),
	m_lighting( false ),
	m_shadingMode ( SHADE_GOURAUD ),
	m_colourWrite ( true ),
	m_maxLights ( 8 ),
	m_ambientMaterialSource  ( MATERIALSOURCE_MATERIALCOLOUR ),
	m_diffuseMaterialSource  ( MATERIALSOURCE_MATERIALCOLOUR ),
	m_specularMaterialSource ( MATERIALSOURCE_MATERIALCOLOUR ),
	m_emissiveMaterialSource ( MATERIALSOURCE_MATERIALCOLOUR ),
	m_normaliseNormals ( false ),
	m_specular( true )

{
	m_sceneBlend.srcBlend = BLEND_SRCALPHA;
	m_sceneBlend.destBlend = BLEND_INVSRCALPHA ;
	
	m_fog.override = false;
	m_fog.density = 0.5f;
	m_fog.begin = 10.0f;
	m_fog.end = 1000.0f;
	m_fog.mode = FOGMODE_LINEAR; 
}
//End RenderState::RenderState



//=========================================================================
//! @function    RenderState::Precache
//! @brief       Adds any required textures to a list of textures to be loaded
//!
//!
//! @param       precacheList [out] List of textures to be loaded, to append to
//!              
//=========================================================================
void RenderState::Precache ( TexturePrecacheList& precacheList )
{
	TextureUnitIterator current = TextureUnitsBegin();
	TextureUnitIterator end = TextureUnitsEnd();

	for ( ; current != end; ++current )
	{
		current->Precache(precacheList);
	}
}
//End RenderState::Precache



//=========================================================================
//! @function    RenderState::UpdateTextureAnimations
//! @brief       Update the texture animations of the texture units
//!              
//! @param       timeElapsedInSeconds [in]
//!              
//=========================================================================
void RenderState::UpdateTextureAnimations ( Float timeElapsedInSeconds )
{
	TextureUnitIterator current = TextureUnitsBegin();
	TextureUnitIterator end = TextureUnitsEnd();

	for ( ; current != end; ++current )
	{
		current->UpdateTextureAnimations( timeElapsedInSeconds );
	}

}
//End RenderState::UpdateTextureAnimations



//=========================================================================
//! @function    operator << ( RenderState )
//! @brief       
//!              
//! @param       out		 [in]
//! @param       renderState [in]
//!              
//! @return      out
//=========================================================================
std::ostream& Renderer::operator << ( std::ostream& out, const Renderer::RenderState& renderState )
{

	out << "\n{"
		   "\n\tAmbient Colour: " << renderState.AmbientColour()
		<< "\n\tDiffuse Colour: " << renderState.DiffuseColour()
		<< "\n\tSpecular Colour: " << renderState.SpecularColour()
		<< "\n\tEmissive Colour: " << renderState.EmissiveColour()
		<< "\n\tShininess: " << renderState.Shininess();

	out << "\n\tSceneBlend: " << BlendModeToString(renderState.SourceBlend()) << " " 
							  << BlendModeToString(renderState.DestBlend());
	out << "\n\tDepth Test: " << renderState.DepthTest()
		<< "\n\tDepth Write: " << renderState.DepthWrite()
		<< "\n\tDepth Func: " << CmpFuncToString(renderState.DepthFunc())
		<< "\n\tDepth Bias: " << renderState.DepthBias()
		<< "\n\tAlpha Test: " << renderState.AlphaTest()
		<< "\n\tAlpha Func: " << renderState.AlphaFunc()
		<< "\n\tAlpha Reference:	" << renderState.AlphaReference()
		<< "\n\tCull Mode: ";

	switch ( renderState.CullMode() )
	{
		case CULL_NONE:
			out << "CULL_NONE";
			break;

		case CULL_CLOCKWISE:
			out << "CULL_CLOCKWISE";
			break;

		case CULL_COUNTERCLOCKWISE:
			out << "CULL_COUNTERCLOCKWISE";
			break;
	}

	out << "\n\tLighting: " << renderState.Lighting();
	out << "\n\tShade Mode: ";

	switch ( renderState.ShadeMode() )
	{
		case SHADE_FLAT:
			out << "SHADE_FLAT";		
			break;
		
		case SHADE_GOURAUD:
			out << "SHADE_GOURAUD";
			break;
	}


	out << "\n\tFog: \n\t{"
		<< "\n\t\tFog Override:" << renderState.FogOverride()
		<< "\n\t\tFog Mode: " << FogModeToString(renderState.FogMode())
		<< "\n\t\tFog Colour: " << renderState.FogColour()
		<< "\n\t\tFog Begin: " << renderState.FogBegin()
		<< "\n\t\tFog End: " << renderState.FogEnd()
		<< "\n\t\tFog Density: "  << renderState.FogDensity()
		<< "\n\t}"

		<< "\n\tColour Write: " << renderState.ColourWrite()
		<< "\n\tMax Lights: " << renderState.MaxLights() << "\n";
	
	for ( UInt i=0; i < renderState.TextureUnitCount(); ++i )
	{
		const TextureUnit& textureUnit = renderState.TextureUnits(i);
		out << "Texture Unit " << i << ": ";

		//We have to do this for some reason, because the compiler gets confused otherwise
		out << textureUnit;
	}

	return out;
}
//End operator << (RenderState)