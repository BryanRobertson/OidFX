//======================================================================================
//! @file         TextureUnit.cpp
//! @brief        Class representing the state for a single texture unit
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 29 June 2005
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
#include "Renderer/RendererConstantToString.h"
#include "Renderer/RendererStateConstants.h"
#include "Renderer/TexturePrecacheList.h"
#include "Renderer/TextureUnit.h"



using namespace Renderer;


//=========================================================================
// TextureUnit methods
//=========================================================================



//=========================================================================
//! @function    TextureUnit::TextureUnit
//! @brief       
//!              
//=========================================================================
TextureUnit::TextureUnit (  )
: 
	m_type(TEXTURE_2D ), 
	m_nameHash(0),
	m_autoGenerated(false), 
	m_wavePosition(0.0f),
	m_minFilter(TEXFILTER_LINEAR), 
	m_magFilter(TEXFILTER_LINEAR), 
	m_mipFilter(TEXFILTER_LINEAR),
	m_maxAnisotropy(1), 
	m_coordinateSet(0), 
	m_addressingModeU(TEXADDRESS_WRAP),
	m_addressingModeV(TEXADDRESS_WRAP),
	m_addressingModeW(TEXADDRESS_WRAP),
	m_texCoordGenerationMode(TEXGEN_NONE), 
	m_rotate(0.0f), 
	m_rotateAnim(0.0f),
	m_scale(1.0f, 1.0f, 1.0f)
{ 

	m_colourOp.operation = TEXOP_MODULATE ;
	m_colourOp.arg1		 = TEXARG_DIFFUSE;
	m_colourOp.arg2		 = TEXARG_TEXTURE ;

	m_alphaOp.operation	 = TEXOP_MODULATE;
	m_alphaOp.arg1		 = TEXARG_DIFFUSE;
	m_alphaOp.arg2		 = TEXARG_TEXTURE; 

}
//End TextureUnit::TextureUnit



//=========================================================================
//! @function    TextureUnit::UpdateTextureAnimations
//! @brief       Updates the scroll, rotate, and scale members based on
//!				 their animation properties, and any wave transforms that may be set
//!              
//! @param       timeElapsedInSeconds [in] Time elapsed since last update in seconds
//!              
//=========================================================================
void TextureUnit::UpdateTextureAnimations ( Float timeElapsedInSeconds )
{
	//First, update from wave transforms
	m_wavePosition += timeElapsedInSeconds;

	for ( UInt index=0; index < WaveTransformCount(); ++index )
	{
		const WaveXForm& xform = GetWaveTransform( index );
		Float waveValue = 0.0f;

		switch ( xform.waveType )
		{
			case WAVE_SINE:
				waveValue = (Math::Sin((xform.phase + m_wavePosition) * xform.frequency * Math::TwoPi) * xform.amplitude) + xform.base;
				break;

			case WAVE_TRIANGLE:
				waveValue = (Math::TriangleWaveFunction((xform.phase + m_wavePosition) * xform.frequency) * xform.amplitude) 
							 + xform.base;
				break;

			case WAVE_SQUARE:
				waveValue = (Math::SquareWaveFunction((xform.phase + m_wavePosition) * xform.frequency) * xform.amplitude) 
							 + xform.base;
				break;

			case WAVE_SAWTOOTH:
				waveValue = (Math::SawToothFunction((xform.phase + m_wavePosition) * xform.frequency) * xform.amplitude) 
							 + xform.base;
				break;

			case WAVE_INVERSE_SAWTOOTH:
				waveValue = xform.base + (xform.amplitude *
											(Math::SawToothFunction((xform.phase + m_wavePosition) * xform.frequency) * xform.amplitude) );
				break;
		}

		//std::clog << "waveValue = " << waveValue << std::endl;

		switch ( xform.transformType )
		{
			case XFORM_SCROLL_X:
				m_scroll.X( waveValue );
				break;

			case XFORM_SCROLL_Y:
				m_scroll.Y( waveValue );
				break;

			case XFORM_ROTATE:
				m_rotate = waveValue;
				break;

			case XFORM_SCALE_X:
				m_scale.X( waveValue );
				break;

			case XFORM_SCALE_Y:
				m_scale.Y( waveValue );
				break;
		}

	}

	//Now update from the static animations
	m_scroll += m_scrollAnim * timeElapsedInSeconds;
	m_rotate += m_rotateAnim * timeElapsedInSeconds;
	m_scale  += m_scaleAnim * timeElapsedInSeconds;

	//Update the texture transform matrix
	m_textureTransform.Identity();
	m_textureTransform.Rotate ( Math::Vector3D(0.0f, 0.0f, 1.0f), Rotate() );
	m_textureTransform.Translate ( Scroll() );
	m_textureTransform.Scale ( Scale() );

}
//End TextureUnit::UpdateTextureAnimations



//=========================================================================
//! @function    TextureUnit::Precache
//! @brief       Adds the texture to a list of textures to be loaded
//!				 
//!				 If the texture is auto-generated, then it won't be added to the list
//!				 since auto-generated textures aren't loaded from disk
//!
//! @param       precacheList [out] List of textures to be loaded, to append the texture to
//!              
//=========================================================================
void TextureUnit::Precache ( TexturePrecacheList& precacheList )
{
	if ( !AutoGenerated() && (!m_name.empty()) && (m_textureHandle.IsNull()) )
	{
		precacheList.AddToPrecacheList ( m_textureHandle, m_type, m_name.c_str(), 0, 0, 0); 
	}
}
//End TextureUnit::Precache



//=========================================================================
//! @function    operator < ( const TextureUnit&, const TextureUnit& ) const
//! @brief       Compare two texture units (used for render state sorting)
//!              
//! @param       lhs 
//! @param       rhs 
//!              
//========================================================================
bool Renderer::operator < ( const TextureUnit& lhs, const TextureUnit & rhs )
{
	if ( lhs.TextureHandle().Value() < rhs.TextureHandle().Value() )
	{
		return true;
	}

	if ( lhs.MinFilter() < rhs.MinFilter() )
	{
		return true;
	}

	if ( lhs.MagFilter() < rhs.MagFilter() )
	{
		return true;
	}

	if ( lhs.MipFilter() < rhs.MipFilter() )
	{
		return true;
	}

	if ( lhs.ColourOp().operation < rhs.ColourOp().operation )
	{
		return true;
	}

	if ( lhs.AlphaOp().operation < rhs.AlphaOp().operation )
	{
		return true;
	}

	if ( (lhs.ColourOp().arg1 < rhs.ColourOp().arg1) ||
		 (lhs.ColourOp().arg2 < rhs.ColourOp().arg2) )
	{
		return true;
	}

	if ( (lhs.AlphaOp().arg1 < rhs.AlphaOp().arg1) ||
		 (lhs.AlphaOp().arg2 < rhs.AlphaOp().arg2) )
	{
		return true;
	}

	if ( lhs.AddressingMode(TEX_ADDRESS_U) < rhs.AddressingMode(TEX_ADDRESS_U) )
	{
		return true;
	}

	if ( lhs.AddressingMode(TEX_ADDRESS_V) < rhs.AddressingMode(TEX_ADDRESS_V) )
	{
		return true;
	}

	if ( lhs.AddressingMode(TEX_ADDRESS_W) < rhs.AddressingMode(TEX_ADDRESS_W) )
	{
		return true;
	}

	return false;
}
//End operator <



//=========================================================================
//! @function    operator << ( TextureUnit )
//! @brief		        
//!              
//! @param       out		 [in]
//! @param       textureUnit [in]
//!              
//! @return      out
//=========================================================================
std::ostream& Renderer::operator << ( std::ostream& out, const Renderer::TextureUnit& textureUnit )
{
	
	out << "{"
		<< "\n\tName: " << textureUnit.Name()
		<< "\n\tNameHash: " << textureUnit.NameHash()
		<< "\n\tAutoGenerated: " << textureUnit.AutoGenerated()
		<< "\n\tHTexture: "	 << textureUnit.TextureHandle().Value()
		<< "\n\tType: ";

	switch ( textureUnit.TextureType() )
	{
		case TEXTURE_1D:
			out << "TEXTURE_1D";
			break;

		case TEXTURE_2D:
			out << "TEXTURE_2D";
			break;

		case TEXTURE_CUBEMAP:
			out << "TEXTURE_CUBEMAP";
			break;
	}

	out << "\n\tMinFilter: " << TextureFilterToString(textureUnit.MinFilter())
		<< "\n\tMagFilter: " << TextureFilterToString(textureUnit.MagFilter())
		<< "\n\tMipFilter: " << TextureFilterToString(textureUnit.MipFilter())
		<< "\n\tMaxAnisotropy: " << textureUnit.MaxAnisotropy();


	out << "\n\t ColourOp:\n{" 
			"\n\t\tOperation: " << TextureOpToString(textureUnit.ColourOp().operation) 
		<<  "\n\t\tArgument1: " << TextureArgumentToString(textureUnit.ColourOp().arg1)
		<<  "\n\t\tArgument2: " << TextureArgumentToString(textureUnit.ColourOp().arg2)
		<< "\n}";

	out << "\n\t AlphaOp:\n{" 
			"\n\t\tOperation: " << TextureOpToString(textureUnit.AlphaOp().operation) 
		<<  "\n\t\tArgument1: " << TextureArgumentToString(textureUnit.AlphaOp().arg1)
		<<  "\n\t\tArgument2: " << TextureArgumentToString(textureUnit.AlphaOp().arg2)
		<< "\n\t}";
	

	out << "\n\tCoordinate Set: " << textureUnit.CoordinateSet()
		<< "\n\tAddressing Mode U: " << (std::string)TextureAddressingModeToString(textureUnit.AddressingMode(TEX_ADDRESS_U))
		<< "\n\tAddressing Mode V: " << (std::string)TextureAddressingModeToString(textureUnit.AddressingMode(TEX_ADDRESS_V))
		<< "\n\tAddressing Mode W: " << (std::string)TextureAddressingModeToString(textureUnit.AddressingMode(TEX_ADDRESS_W))
		<< "\n\tCoordinate Generation: ";

	switch (textureUnit.CoordinateGenMode())
	{
		case TEXGEN_NONE:
			out << "TEXGEN_NONE";
			break;
		case TEXGEN_EYESPACE_NORMAL:
			out << "TEXGEN_EYESPACE_NORMAL";
			break;
		case TEXGEN_EYESPACE_REFLECTION:
			out << "TEXGEN_EYESPACE_REFLECTION";
			break;
		case TEXGEN_SPHEREMAP:
			out << "TEXGEN_SPHEREMAP";
			break;
	}

	out << "\n\tScroll: " << textureUnit.Scroll()
		<< "\n\tScale: " << textureUnit.Scale()
		<< "\n\tRotate: " << textureUnit.Rotate()
		<< "\n\tScrollAnim: " << textureUnit.ScrollAnim()
		<< "\n\tScaleAnim: " << textureUnit.ScaleAnim()
		<< "\n\tRotateAnim: " << textureUnit.RotateAnim();
		
		
		for ( UInt i=0; i < textureUnit.WaveTransformCount(); ++i )
		{
			const TextureUnit::WaveXForm& xform = textureUnit.GetWaveTransform(i);
		
			out << "\n\tTransform\n\t{\n\t\tType:";

			switch ( xform.transformType )
			{
				case XFORM_SCROLL_X:
					out << "XFORM_SCROLL_X";
					break;

				case XFORM_SCROLL_Y:
					out << "XFORM_SCROLL_Y";
					break;

				case XFORM_ROTATE:
					out << "XFORM_ROTATE";
					break;

				case XFORM_SCALE_X:
					out << "XFORM_SCALE_X";
					break;

				case XFORM_SCALE_Y:
					out << "XFORM_SCALE_Y";
					break;
			}

			out << "\n\t\tWave Type:";
	
			switch ( xform.waveType )
			{
				case WAVE_SINE:
					out << "WAVE_SINE";
					break;

				case WAVE_TRIANGLE:
					out << "WAVE_TRIANGLE";
					break;

				case WAVE_SQUARE:
					out << "WAVE_SQUARE";
					break;

				case WAVE_SAWTOOTH:
					out << "WAVE_SAWTOOTH";
					break;

				case WAVE_INVERSE_SAWTOOTH:
					out << "WAVE_INVERSE_SAWTOOTH";
					break;
			}

			out << "\n\t\tAmplitude: " << xform.amplitude
				<< "\n\t\tPhase: " << xform.phase 
				<< "\n\t\tFrequency: " << xform.frequency
				<< "\n\t\tBase: " << xform.base;

		}

		out << "\n}" << std::endl;

		return out;
}
//End operator << (TextureUnit)
