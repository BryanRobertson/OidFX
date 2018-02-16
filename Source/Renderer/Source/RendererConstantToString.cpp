//======================================================================================
//! @file         RendererConstantToString.cpp
//! @brief        Contains functions for converting between Renderer constants and
//!				  strings
//!
//! @author       Bryan Robertson
//! @date         Monday, 06 June 2005
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
#include "Renderer/RendererBuffer.h"
#include "Renderer/RendererTypes.h"
#include "Renderer/RendererStateConstants.h"
#include "Renderer/RendererConstantToString.h"


//namespace Renderer
namespace Renderer
{

    //=========================================================================
    //! @function    RendererBufferUsageToString
    //! @brief       Convert renderer buffer usage options to a string
	//!				 for debugging purposes
    //!              
    //! @param       usage [in] Usage options to print
    //!              
    //! @return      A string representing the usage options
    //=========================================================================
	std::string RendererBufferUsageToString ( EUsage usage )
	{
		std::ostringstream outputString;
		outputString << std::endl;

		UInt usageFlags = static_cast<UInt>(usage);

		if ( usageFlags & USAGE_STATIC )
		{
			outputString << " USAGE_STATIC";
		}

		if ( usageFlags & USAGE_WRITEONLY )
		{
			outputString << " USAGE_WRITEONLY";
		}

		if ( usageFlags & USAGE_DYNAMIC )
		{
			outputString << " USAGE_DYNAMIC";
		}

		if ( usageFlags & USAGE_DISCARDABLE )
		{
			outputString << "USAGE_DISCARDABLE";
		}

		return outputString.str();
	}
	//End RendererBufferUsageToString



    //=========================================================================
    //! @function    RendererBufferLockOptionsToString
    //! @brief       Convert renderer buffer lock flags to a string
	//!				 for debugging purposes
    //!              
    //! @param       lockOptions [in] Lock options to print
    //!              
    //! @return      A string representing the lock flags
    //=========================================================================
	std::string RendererBufferLockOptionsToString ( ELock lockOptions )
	{
		std::ostringstream outputString;

		UInt lockFlags = static_cast<UInt>(lockOptions);

		if ( lockFlags & LOCK_DISCARD )
		{
			outputString << " LOCK_DISCARD";
		}

		if ( lockFlags & LOCK_NOOVERWRITE )
		{
			outputString << " LOCK_NOOVERWRITE";
		}

		if ( lockFlags & LOCK_READONLY )
		{
			outputString << " LOCK_READONLY";
		}

		return outputString.str();
	}
	//End RendererBufferLockFlagsToString



    //=========================================================================
    //! @function    PrimTypeToString
    //! @brief       Convert a primitive type to a string
    //!              
    //! @param       type [in] Primitive type to convert to string
    //!              
    //! @return      A string representing the primitive type
    //=========================================================================
	std::string PrimTypeToString ( Renderer::EPrimType type )
	{
		switch ( type )
		{
			case PRIM_POINTLIST:
				return "PRIM_POINTLIST";

			case PRIM_LINELIST:
				return "PRIM_LINELIST";
				
			case PRIM_LINESTRIP:
				return "PRIM_LINESTRIP";

			case PRIM_TRIANGLELIST:
				return "PRIM_TRIANGLELIST";

			case PRIM_TRIANGLESTRIP:
				return "PRIM_TRIANGLESTRIP";

			case PRIM_TRIANGLEFAN:
				return "PRIM_TRIANGLEFAN";

			default:
				debug_assert ( false, "Invalid primitive type!" );
				return "Invalid primitive type";
		}
	}
	//End PrimTypeToString



    //=========================================================================
    //! @function    BoolStateIDToString
    //! @brief       Convert a boolean state ID to a string
    //!              
    //! @param       stateID 
    //!              
    //=========================================================================
	std::string BoolStateIDToString ( EBoolStateID stateID )
	{
		switch ( stateID )
		{
			case STATE_COLOURWRITE:
				return "STATE_COLOURWRITE";			
	
			case STATE_DEPTHTEST:
				return "STATE_DEPTHTEST";			
	
			case STATE_DEPTHWRITE:
				return "STATE_DEPTHWRITE";			
	
			case STATE_ALPHATEST:
				return "STATE_ALPHATEST";			
	
			case STATE_BLENDING:
				return "STATE_BLENDING"	;			
	
			case STATE_FOGBLENDING:
				return "STATE_FOGBLENDING";			
	
			case STATE_SPECULAR:
				return "STATE_SPECULAR";			
	
			case STATE_STENCIL:
				return "STATE_STENCIL";				
	
			case STATE_RANGEFOG:
				return "STATE_RANGEFOG";				
	
			case STATE_CLIPPING:
				return "STATE_CLIPPING";			
	
			case STATE_LIGHTING:
				return "STATE_LIGHTING";			
	
			case STATE_VERTEXCOLOURS:
				return "STATE_VERTEXCOLOURS";		
	
			case STATE_NORMALISENORMALS:
				return "STATE_NORMALISENORMALS";		
	
			case STATE_POINTSPRITE:
				return "STATE_POINTSPRITE";	
	
			case STATE_POINTSCALE:
				return "STATE_POINTSCALE";			
	
			case STATE_SCISSORTEST:
				return "STATE_SCISSORTEST";			
	
			case STATE_TWOSIDEDSTENCIL:
				return "STATE_TWOSIDEDSTENCIL";		
	
			case STATE_SEPERATE_ALPHABLEND:
				return "STATE_SEPERATE_ALPHABLEND";	
	
			case STATE_INDEXED_VERTEX_BLEND:
				return "STATE_INDEXED_VERTEX_BLEND";	
	
			default:
				return "Invalid state ID";
		}
	}
	//End BoolStateIDToString 



    //=========================================================================
    //! @function    UIntStateIDToString
    //! @brief       Convert a UInt state ID to a string
    //!              
    //! @param       stateID 
    //!              
    //! @return      
    //=========================================================================
	std::string UIntStateIDToString ( EUIntStateID stateID )
	{
		switch ( stateID )
		{
			case STATE_STENCILREFERENCE:
				return "STATE_STENCILREFERENCE";

			case STATE_STENCILMASK:
				return "STATE_STENCILMASK";

			case STATE_STENCILWRITEMASK:
				return "STATE_STENCILWRITEMASK";

			default:
				return "Invalid state ID";
		}
	}
	//End UIntStateIDToString


    //=========================================================================
    //! @function    FloatStateIDToString
    //! @brief       Convert a float state ID to a string
    //!              
    //! @param       stateID 
    //!              
    //! @return      
    //=========================================================================
	std::string FloatStateIDToString ( EFloatStateID stateID )
	{
		switch ( stateID )
		{
			case STATE_ALPHAREFERENCE:
				return "STATE_ALPHAREFERENCE";
			
			case STATE_FOGSTART:
				return "STATE_FOGSTART";
					
			case STATE_FOGEND:
				return "STATE_FOGEND";
					
			case STATE_FOGDENSITY:
				return "STATE_FOGDENSITY";
				
			case STATE_DEPTHBIASVALUE:
				return "STATE_DEPTHBIASVALUE";
			
			case STATE_SLOPESCALEDEPTHBIASVALUE:
				return "STATE_SLOPESCALEDEPTHBIASVALUE";
	
			case STATE_POINTSIZE:
				return "STATE_POINTSIZE";
				
			case STATE_POINTSIZEMIN:
				return "STATE_POINTSIZEMIN";
				
			case STATE_POINTSIZEMAX:
				return "STATE_POINTSIZEMAX";
				
			case STATE_POINTSCALE_A:
				return "STATE_POINTSCALE_A";
				
			case STATE_POINTSCALE_B:
				return "STATE_POINTSCALE_B";
				
			case STATE_POINTSCALE_C:
				return "STATE_POINTSCALE_C";
		
			default:
				return "Invalid state ID";
		}
	}
	//End FloatStateIDToString



    //=========================================================================
    //! @function    TextureStageStateIDToString
    //! @brief       Convert a texture stage state ID to a string
    //!              
    //! @param       stateID 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	std::string TextureStageStateIDToString ( ETextureStageStateID stateID )
	{
		switch ( stateID )
		{
			case TEXSTAGE_COLOUROP:
				return "TEXSTAGE_COLOUROP";

			case TEXSTAGE_COLOURARG1:
				return "TEXSTAGE_COLOURARG1";

			case TEXSTAGE_COLOURARG2:
				return "TEXSTAGE_COLOURARG2";

			case TEXSTAGE_ALPHAOP:
				return "TEXSTAGE_ALPHAOP";

			case TEXSTAGE_ALPHAARG1:
				return "TEXSTAGE_ALPHAARG1";

			case TEXSTAGE_ALPHAARG2:
				return "TEXSTAGE_ALPHAARG2";

			case TEXSTAGE_TEXCOORDINDEX:
				return "TEXSTAGE_TEXCOORDINDEX";

			case TEXSTAGE_COLOURARG0:
				return "TEXSTAGE_COLOURARG0";

			case TEXSTAGE_ALPHAARG0:
				return "TEXSTAGE_ALPHAARG0";

			case TEXSTAGE_RESULTARG:
				return "TEXSTAGE_RESULTARG";

			default:
				return "Invalid state ID";
		}
	}
	//End TextureStageStateIDToString


    //=========================================================================
    //! @function    TextureOpToString
    //! @brief       Convert a texture op to a string
    //!              
    //! @param       op 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	std::string TextureOpToString ( ETextureOp op )
	{
		switch ( op )
		{
			case TEXOP_DISABLE:
				return "TEXOP_DISABLE";

			case TEXOP_SELECTARG1:
				return "TEXOP_SELECTARG1";

			case TEXOP_SELECTARG2:
				return "TEXOP_SELECTARG2";

			case TEXOP_MODULATE:
				return "TEXOP_MODULATE";

			case TEXOP_MODULATE2X:
				return "TEXOP_MODULATE2X";

			case TEXOP_MODULATE4X:
				return "TEXOP_MODULATE4X";

			case TEXOP_ADD:
				return "TEXOP_ADD";

			case TEXOP_ADDSIGNED:
				return "TEXOP_ADDSIGNED";

			case TEXOP_SUBTRACT:
				return "TEXOP_SUBTRACT";

			case TEXOP_ADDSMOOTH:
				return "TEXOP_ADDSMOOTH";

			case TEXOP_BLENDDIFFUSEALPHA:
				return "TEXOP_BLENDDIFFUSEALPHA";

			case TEXOP_BLENDTEXTUREALPHA:
				return "TEXOP_BLENDTEXTUREALPHA";

			case TEXOP_BLENDFACTORALPHA:
				return "TEXOP_BLENDFACTORALPHA";

			case TEXOP_BLENDTEXTUREALPHAPM:
				return "TEXOP_BLENDTEXTUREALPHAPM";

			case TEXOP_BLENDCURRENTALPHA:
				return "TEXOP_BLENDCURRENTALPHA";

			case TEXOP_PREMODULATE:
				return "TEXOP_PREMODULATE";

			case TEXOP_MODULATEALPHA_ADDCOLOUR:
				return "TEXOP_MODULATEALPHA_ADDCOLOUR";

			case TEXOP_MODULATECOLOUR_ADDALPHA:
				return "TEXOP_MODULATECOLOUR_ADDALPHA";

			case TEXOP_DOTPRODUCT3:
				return "TEXOP_DOTPRODUCT3";

			case TEXOP_MULTIPLYADD:
				return "TEXOP_MULTIPLYADD";

			case TEXOP_LERP:
				return "TEXOP_LERP";

			default:
				return "Invalid TexOp";
		}
	}
	//End TextureOpToString


    //=========================================================================
    //! @function    BlendOpToString
    //! @brief       Convert a blend op to a string
    //!              
    //! @param       op [in] op to covert
    //!              
    //! @return      String representing op
    //=========================================================================
	std::string BlendOpToString ( EBlendOp op )
	{
		switch ( op )
		{
			case BLEND_ADD:
				return "BLEND_ADD";

			case BLEND_SUBTRACT:
				return "BLEND_SUBTRACT";
				
			case BLEND_REVERSE_SUBTRACT:
				return "BLEND_REVERSE_SUBTRACT";
				
			case BLEND_MIN:
				return "BLEND_MIN";
				
			case BLEND_MAX:
				return "BLEND_MAX";
				
			default:
				return "Invalid blend op!";
		}
	}
	//End BlendOpToString



	//=========================================================================
    //! @function    BlendModeToString
    //! @brief       Convert a blend mode to a string
    //!              
    //! @param       mode [in] mode to covert
    //!              
    //! @return      String representing mode
    //=========================================================================
	std::string BlendModeToString ( EBlendMode mode )
	{
		switch ( mode )
		{
			case BLEND_ONE:
				return "BLEND_ONE";

			case BLEND_ZERO:
				return "BLEND_ZERO";
			
			case BLEND_SRCCOLOUR:
				return "BLEND_SRCCOLOUR";
	
			case BLEND_INVSRCCOLOUR:
				return "BLEND_INVSRCCOLOUR";
	
			case BLEND_SRCALPHA:
				return "BLEND_SRCALPHA";
		
			case BLEND_INVSRCALPHA:
				return "BLEND_INVSRCALPHA";
	
			case BLEND_SRCALPHASAT:
				return "BLEND_SRCALPHASAT";
	
			case BLEND_DESTALPHA:
				return "BLEND_DESTALPHA";
	
			case BLEND_INVDESTALPHA:
				return "BLEND_INVDESTALPHA";
	
			case BLEND_DESTCOLOUR:
				return "BLEND_DESTCOLOUR";
	
			case BLEND_INVDESTCOLOUR:
				return "BLEND_INVDESTCOLOUR";

			case BLEND_BLENDFACTOR:
				return "BLEND_BLENDFACTOR";
	
			case BLEND_INVBLENDFACTOR:
				return "BLEND_INVBLENDFACTOR";

			case BLEND_BOTHINVSRCALPHA:
				return "BLEND_BOTHINVSRCALPHA";

			default:
				return "Invalid blend mode!";
		}
	}
	//End BlendModeToString



    //=========================================================================
    //! @function    CmpFuncToString
    //! @brief		 Convert a comparison function to a string       
    //!              
    //! @param       func [in]
    //!              
    //! @return      A string representing func
    //! @throw       
    //=========================================================================
	std::string CmpFuncToString ( ECmpFunc func )
	{

		switch ( func )
		{
			case Renderer::CMP_NEVER:
				return "CMP_NEVER";
	
			case Renderer::CMP_LESS:
				return "CMP_LESS";
	
			case Renderer::CMP_LEQUAL:
				return "CMP_LEQUAL";
	
			case Renderer::CMP_GREATER:
				return "CMP_GREATER";

			case Renderer::CMP_GEQUAL:
				return "CMP_GEQUAL";
	
			case Renderer::CMP_ALWAYS:
				return "CMP_ALWAYS";

			case Renderer::CMP_EQUAL:
				return "CMP_EQUAL";

			case Renderer::CMP_NOTEQUAL:
				return "CMP_NOTEQUAL";

			default:
				return "Invalid comparison function";
		}
	}
	//End CmpFuncToString



    //=========================================================================
    //! @function    StencilOpToString
    //! @brief       Convert a stencil operation to a string
    //!              
    //! @param       op [in] Operation to convert
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	std::string StencilOpToString ( Renderer::EStencilOp op )
	{
		switch ( op )
		{
			case STENCILOP_KEEP:
				return "STENCILOP_KEEP";
		
			case STENCILOP_ZERO:
				return "STENCILOP_ZERO";
		
			case STENCILOP_REPLACE:
				return "STENCILOP_REPLACE";
	
			case STENCILOP_INCRSAT:
				return "STENCILOP_INCRSAT";
	
			case STENCILOP_DECRSAT:
				return "STENCILOP_DECRSAT";
	
			case STENCILOP_INVERT:
				return "STENCILOP_INVERT";
		
			case STENCILOP_INCR:
				return "STENCILOP_INCR";
		
			case STENCILOP_DECR:
				return "STENCILOP_DECR";

			default:
				return "Invalid stencil op";
		}
	}
	//End StencilOpToString 



    //=========================================================================
    //! @function    FogModeToString
    //! @brief       Convert a fog mode to a string
    //!              
    //! @param       mode [in]
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	std::string FogModeToString ( Renderer::EFogMode mode )
	{
		switch ( mode )
		{
			case FOGMODE_NONE:
				return "FOGMODE_NONE";
	
			case FOGMODE_EXP:
				return "FOGMODE_EXP";
	
			case FOGMODE_EXP2:
				return "FOGMODE_EXP2";
	
			case FOGMODE_LINEAR:
				return "FOGMODE_LINEAR";
	
			default:
				return "Invalid fog type!";
		}
	}
	//End FogModeToString


    //=========================================================================
    //! @function    TextureAddressingModeToString
    //! @brief       Convert a texture addressing mode to a string
    //!              
    //! @param       mode [in] Mode to convert
    //!              
    //! @return      String representing mode
    //=========================================================================
	std::string TextureAddressingModeToString ( ETextureAddressingMode mode )
	{
		switch ( mode )
		{
			case TEXADDRESS_WRAP:
				return "TEXADDRESS_WRAP";
 
			case TEXADDRESS_CLAMP:
				return "TEXADDRESS_CLAMP";
 
			case TEXADDRESS_BORDER:
				return "TEXADDRESS_BORDER";

			case TEXADDRESS_MIRROR:
				return "TEXADDRESS_MIRROR";
 
			case TEXADDRESS_MIRRORONCE:
				return "TEXADDRESS_MIRRORONCE";

			default:
				return "Invalid texture addressing mode";
		}
	}
	//End TextureAddressingModeToString



    //=========================================================================
    //! @function    TextureFilterToString
    //! @brief       Convert a texture filter to a string
    //!              
    //! @param       filter [in] Filter to convert
    //!              
    //! @return      String representing the filter mode
    //=========================================================================
	std::string TextureFilterToString ( ETextureFilter filter )
	{
		switch ( filter )
		{
			case TEXFILTER_POINT:
				return "TEXFILTER_POINT";

			case TEXFILTER_LINEAR:
				return "TEXFILTER_LINEAR";

			case TEXFILTER_ANISOTROPIC:
				return "TEXFILTER_ANISOTROPIC";

			default:
				debug_assert ( false, "Invalid filter");
		}
	}
	//End TextureFilterToString




    //=========================================================================
    //! @function    TextureArgumentToString
    //! @brief       Convert a texture argument to a string
    //!              
    //! @param       arg 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	std::string TextureArgumentToString ( ETextureArgument arg )
	{

		switch ( arg )
		{
			case TEXARG_CONSTANT:
				return "TEXARG_CONSTANT";
	
			case TEXARG_CURRENT:
				return "TEXARG_CURRENT";
								
			case TEXARG_DIFFUSE:
				return "TEXARG_DIFFUSE";
		
			case TEXARG_SPECULAR:
				return "TEXARG_SPECULAR";
	
			case TEXARG_TEMP:
				return "TEXARG_TEMP";
		
			case TEXARG_TEXTURE:
				return "TEXARG_TEXTURE";
		
			case TEXARG_TEXTUREFACTOR:
				return "TEXARG_TEXTUREFACTOR";
				
			default:
				debug_assert ( false, "Invalid texture argument");
		}
	}
	//End TextureArgumentToString

};
//End namespace Renderer


