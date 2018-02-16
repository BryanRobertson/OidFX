//======================================================================================
//! @file         ConversionFunctions.h
//! @brief        Functions used to convert renderer constants into their Direct3D equivilents
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 15 June 2005
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

#ifndef DIRECTX9RENDERER_CONVERSIONFUNCTIONS_H
#define DIRECTX9RENDERER_CONVERSIONFUNCTIONS_H


#include "Imaging/PixelFormat.h"


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


	//Conversion methods
	inline D3DPRIMITIVETYPE ConvertPrimTypeToD3D ( Renderer::EPrimType type ) throw();
	inline void SetD3DMatrixFromMatrix4x4 ( const Math::Matrix4x4& matrix, D3DXMATRIX& d3dMatrix ) throw();
	inline void SetD3DTextureMatrixFromMatrix4x4 ( const Math::Matrix4x4& matrix, D3DXMATRIX& d3dMatrix, Renderer::ETextureType type ) throw();
	inline D3DTEXTURESTAGESTATETYPE ConvertTextureStageStateTypeToD3D ( Renderer::ETextureStageStateID stateID ) throw();
	inline D3DTEXTUREOP ConvertTextureOpToD3D ( Renderer::ETextureOp texOp ) throw();
	inline DWORD ConvertTextureArgumentToD3D ( Renderer::ETextureArgument arg ) throw();
	inline D3DBLENDOP ConvertBlendOpToD3D ( Renderer::EBlendOp op ) throw();
	inline D3DBLEND ConvertBlendModeToD3D ( Renderer::EBlendMode factor ) throw();
	inline D3DCMPFUNC ConvertCmpFuncToD3D ( Renderer::ECmpFunc func ) throw();
	inline D3DSTENCILOP ConvertStencilOpToD3D ( Renderer::EStencilOp op ) throw();
	inline D3DFOGMODE ConvertFogModeToD3D ( Renderer::EFogMode mode ) throw();
	inline D3DTEXTUREADDRESS ConvertTextureAddressingModeToD3D( Renderer::ETextureAddressingMode mode) throw();
	inline bool ConvertPixelFormatToD3D ( Imaging::PixelFormat format, D3DFORMAT& dxFormat ) throw();
	inline bool ConvertD3DFormatToPixelFormat ( D3DFORMAT dxFormat, Imaging::PixelFormat& format ) throw();		

	
    //=========================================================================
    //! @function    ConvertPrimTypeToD3D
    //! @brief       Convert a member of the EPrimType enumerated type,
	//!				 to a member of the D3DPRIMITIVETYPE type
    //!              
    //! @param       type [in] EPrimType to convert
    //!              
    //! @return      The equivilent member of D3DPRIMITIVETYPE
    //=========================================================================
	inline D3DPRIMITIVETYPE ConvertPrimTypeToD3D ( Renderer::EPrimType type )
	{
		
		switch ( type )
		{
			case Renderer::PRIM_POINTLIST:
				return D3DPT_POINTLIST;

			case Renderer::PRIM_LINELIST:
				return D3DPT_LINELIST;
				
			case Renderer::PRIM_LINESTRIP:
				return D3DPT_LINESTRIP;

			case Renderer::PRIM_TRIANGLELIST:
				return D3DPT_TRIANGLELIST;

			case Renderer::PRIM_TRIANGLESTRIP:
				return D3DPT_TRIANGLESTRIP;

			case Renderer::PRIM_TRIANGLEFAN:
				return D3DPT_TRIANGLEFAN;

			default:
				debug_assert ( false, "Invalid primitive type!" );
				return D3DPT_POINTLIST;
		}
	}
	//End ConvertPrimTypeToD3D



    //=========================================================================
    //! @function    SetD3DMatrixFromMatrix4x4
    //! @brief       Set a Direct3D matrix structure from a Matrix4x4
    //!              
    //! @param       matrix		[in] Matrix to copy
    //! @param       d3dMatrix	[out] D3DMATRIX structure to recieve the contents of matrix
    //!              
    //=========================================================================
	void SetD3DMatrixFromMatrix4x4 ( const Math::Matrix4x4& matrix, D3DXMATRIX& d3dMatrix )
	{
		d3dMatrix(0,0) = matrix(0,0);
		d3dMatrix(0,1) = matrix(0,1);
		d3dMatrix(0,2) = matrix(0,2);
		d3dMatrix(0,3) = matrix(0,3);
		d3dMatrix(1,0) = matrix(1,0);
		d3dMatrix(1,1) = matrix(1,1);
		d3dMatrix(1,2) = matrix(1,2);
		d3dMatrix(1,3) = matrix(1,3);
		d3dMatrix(2,0) = matrix(2,0);
		d3dMatrix(2,1) = matrix(2,1);
		d3dMatrix(2,2) = matrix(2,2);
		d3dMatrix(2,3) = matrix(2,3);
		d3dMatrix(3,0) = matrix(3,0);
		d3dMatrix(3,1) = matrix(3,1);
		d3dMatrix(3,2) = matrix(3,2);
		d3dMatrix(3,3) = matrix(3,3);
	}
	//End SetD3DMatrixFromMatrix4x4



    //=========================================================================
    //! @function    SetD3DTextureMatrixFromMatrix4x4
    //! @brief       Set a Direct3D Texture matrix from a Matrix4x4
	//!
	//!				 In Direct3D, 2D texture coordinates require the translation
	//!				 components to be in the third row. This function sets the matrix
	//!				 appropriately, depending on the texture type (2D or 3D coordinates)
    //!				 1D coordinates are not supported at the momente 
	//!
    //! @param       matrix		[in]
    //! @param       d3dMatrix	[in]
    //! @param       type		[in]
    //!              
    //=========================================================================
	void SetD3DTextureMatrixFromMatrix4x4 ( const Math::Matrix4x4& matrix, D3DXMATRIX& d3dMatrix, Renderer::ETextureType type )
	{
		if ( type == Renderer::TEXTURE_CUBEMAP )
		{
			SetD3DMatrixFromMatrix4x4 ( matrix, d3dMatrix );
		}
		else
		{
			d3dMatrix(0,0) = matrix(0,0);
			d3dMatrix(0,1) = matrix(0,1);
			d3dMatrix(0,2) = matrix(0,2);
			d3dMatrix(0,3) = matrix(0,3);
			d3dMatrix(1,0) = matrix(1,0);
			d3dMatrix(1,1) = matrix(1,1);
			d3dMatrix(1,2) = matrix(1,2);
			d3dMatrix(1,3) = matrix(1,3);
			d3dMatrix(2,0) = matrix(3,0);
			d3dMatrix(2,1) = matrix(3,1);
			d3dMatrix(2,2) = matrix(3,2);
			d3dMatrix(2,3) = matrix(3,3);
			d3dMatrix(3,0) = matrix(3,0);
			d3dMatrix(3,1) = matrix(3,1);
			d3dMatrix(3,2) = matrix(3,2);
			d3dMatrix(3,3) = matrix(3,3);

		}
	}
	//End SetD3DTextureMatrixFromMatrix4x4



    //=========================================================================
    //! @function    ConvertTextureStageStateTypeToD3D
    //! @brief       Convert a texture stage state ID to the Direct3D equivilent
    //!              
    //! @param       stateID 
    //!              
    //! @return      The equivilent texture stage state ID in the D3DTEXTURESTAGESTATETYPE enumeration
    //=========================================================================
	D3DTEXTURESTAGESTATETYPE ConvertTextureStageStateTypeToD3D ( Renderer::ETextureStageStateID stateID )
	{
		switch ( stateID )
		{
			case Renderer::TEXSTAGE_COLOUROP:
				return D3DTSS_COLOROP;
			case Renderer::TEXSTAGE_COLOURARG1:
				return D3DTSS_COLORARG1;
			case Renderer::TEXSTAGE_COLOURARG2:
				return D3DTSS_COLORARG2;
			case Renderer::TEXSTAGE_ALPHAOP:
				return D3DTSS_ALPHAOP;
			case Renderer::TEXSTAGE_ALPHAARG1:
				return D3DTSS_ALPHAARG1;
			case Renderer::TEXSTAGE_ALPHAARG2:
				return D3DTSS_ALPHAARG2;
			case Renderer::TEXSTAGE_TEXCOORDINDEX:
				return D3DTSS_TEXCOORDINDEX;
			case Renderer::TEXSTAGE_COLOURARG0:
				return D3DTSS_COLORARG0;
			case Renderer::TEXSTAGE_ALPHAARG0:
				return D3DTSS_ALPHAARG0;
			case Renderer::TEXSTAGE_RESULTARG:
				return D3DTSS_RESULTARG;

			default:
				debug_assert ( false, "Invalid texture stage state ID" );
		}
	}
	//End ConvertTextureStageStateTypeToD3D



    //=========================================================================
    //! @function    ConvertTextureOpToD3D
    //! @brief       Returns the equivilent member of the D3DTEXTUREOP enum
	//!				 for an entry in the ETextureOp enum
    //!              
    //! @param       texOp [in] 
    //!              
    //! @return      The equivilent entry in the D3DTEXTUREOP enum
    //=========================================================================
	D3DTEXTUREOP ConvertTextureOpToD3D ( Renderer::ETextureOp texOp )
	{
		switch ( texOp )
		{
			case Renderer::TEXOP_DISABLE:
				return D3DTOP_DISABLE;

			case Renderer::TEXOP_SELECTARG1:
				return D3DTOP_SELECTARG1;

			case Renderer::TEXOP_SELECTARG2:
				return D3DTOP_SELECTARG2;

			case Renderer::TEXOP_MODULATE:
				return D3DTOP_MODULATE;

			case Renderer::TEXOP_MODULATE2X:
				return D3DTOP_MODULATE2X;

			case Renderer::TEXOP_MODULATE4X:
				return D3DTOP_MODULATE4X;

			case Renderer::TEXOP_ADD:
				return D3DTOP_ADD;

			case Renderer::TEXOP_ADDSIGNED:
				return D3DTOP_ADDSIGNED;

			case Renderer::TEXOP_SUBTRACT:
				return D3DTOP_SUBTRACT;

			case Renderer::TEXOP_ADDSMOOTH:
				return D3DTOP_ADDSMOOTH;

			case Renderer::TEXOP_BLENDDIFFUSEALPHA:
				return D3DTOP_BLENDDIFFUSEALPHA;

			case Renderer::TEXOP_BLENDTEXTUREALPHA:
				return D3DTOP_BLENDTEXTUREALPHA;

			case Renderer::TEXOP_BLENDFACTORALPHA:
				return D3DTOP_BLENDFACTORALPHA;

			case Renderer::TEXOP_BLENDTEXTUREALPHAPM:	
				return D3DTOP_BLENDTEXTUREALPHAPM;

			case Renderer::TEXOP_BLENDCURRENTALPHA:
				return D3DTOP_BLENDCURRENTALPHA;

			case Renderer::TEXOP_PREMODULATE:
				return D3DTOP_PREMODULATE;

			case Renderer::TEXOP_MODULATEALPHA_ADDCOLOUR:
				return D3DTOP_MODULATEALPHA_ADDCOLOR;

			case Renderer::TEXOP_MODULATECOLOUR_ADDALPHA:
				return D3DTOP_MODULATECOLOR_ADDALPHA;

			case Renderer::TEXOP_DOTPRODUCT3:
				return D3DTOP_DOTPRODUCT3;

			case Renderer::TEXOP_MULTIPLYADD:
				return D3DTOP_MULTIPLYADD;

			case Renderer::TEXOP_LERP:
				return D3DTOP_LERP;

			default:
				debug_assert ( false, "Invalid tex op");
		}
	}
	//End ConvertTextureOpToD3D



    //=========================================================================
    //! @function    ConvertTextureArgumentToD3D
    //! @brief       Convert a texture argument to its Direct3D equivilent
    //!              
    //! @param       arg 
    //!              
    //! @return      The Direct3D equivilent of arg
    //=========================================================================
	DWORD ConvertTextureArgumentToD3D ( Renderer::ETextureArgument arg )
	{
		switch ( arg )
		{
			case Renderer::TEXARG_CONSTANT:
				return D3DTA_CONSTANT;	
			case Renderer::TEXARG_CURRENT:
				return D3DTA_CURRENT;										
			case Renderer::TEXARG_DIFFUSE:
				return D3DTA_DIFFUSE;		
			case Renderer::TEXARG_SPECULAR:
				return D3DTA_SPECULAR;	
			case Renderer::TEXARG_TEMP:
				return D3DTA_TEMP;		
			case Renderer::TEXARG_TEXTURE:
				return D3DTA_TEXTURE;		
			case Renderer::TEXARG_TEXTUREFACTOR:
				return D3DTA_TFACTOR;

			default:
				debug_assert ( false, "Invalid texture argument!");
		}
	}
	//End ConvertTextureArgumentToD3D



    //=========================================================================
    //! @function    ConvertBlendOpToD3D
    //! @brief       Convert a blending operation enumeration to its Direct3D equivilent
    //!              
    //! @param       op [in] Operation to convert
    //!              
    //! @return      The D3DBLENDOP equivilent of op
    //=========================================================================
	D3DBLENDOP ConvertBlendOpToD3D ( Renderer::EBlendOp op )
	{
		switch ( op )
		{
			case Renderer::BLEND_ADD:
				return D3DBLENDOP_ADD;

			case Renderer::BLEND_SUBTRACT:
				return D3DBLENDOP_SUBTRACT;

			case Renderer::BLEND_REVERSE_SUBTRACT:
				return D3DBLENDOP_REVSUBTRACT;

			case Renderer::BLEND_MIN:
				return D3DBLENDOP_MIN;

			case Renderer::BLEND_MAX:
				return D3DBLENDOP_MAX;		

			default:
				debug_assert ( false, "Invalid blend op!" );
		}
	}
	//End ConvertBlendOpToD3D



    //=========================================================================
    //! @function    ConvertBlendModeToD3D
    //! @brief       Convert a blend mode to its Direct3D equivilent
    //!              
    //! @param       factor 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	D3DBLEND ConvertBlendModeToD3D ( Renderer::EBlendMode mode )
	{
		switch ( mode )
		{
			case Renderer::BLEND_ONE:
				return D3DBLEND_ONE;

			case Renderer::BLEND_ZERO:
				return D3DBLEND_ZERO;
			
			case Renderer::BLEND_SRCCOLOUR:
				return D3DBLEND_SRCCOLOR;
	
			case Renderer::BLEND_INVSRCCOLOUR:
				return D3DBLEND_INVSRCCOLOR;
	
			case Renderer::BLEND_SRCALPHA:
				return D3DBLEND_SRCALPHA;
		
			case Renderer::BLEND_INVSRCALPHA:
				return D3DBLEND_INVSRCALPHA;
	
			case Renderer::BLEND_SRCALPHASAT:
				return D3DBLEND_SRCALPHASAT;
	
			case Renderer::BLEND_DESTALPHA:
				return D3DBLEND_DESTALPHA;
	
			case Renderer::BLEND_INVDESTALPHA:
				return D3DBLEND_INVDESTALPHA;
	
			case Renderer::BLEND_DESTCOLOUR:
				return D3DBLEND_DESTCOLOR;
	
			case Renderer::BLEND_INVDESTCOLOUR:
				return D3DBLEND_INVDESTCOLOR;

			case Renderer::BLEND_BLENDFACTOR:
				return D3DBLEND_BLENDFACTOR;
	
			case Renderer::BLEND_INVBLENDFACTOR:
				return D3DBLEND_INVBLENDFACTOR;

			case Renderer::BLEND_BOTHINVSRCALPHA:
				return D3DBLEND_BOTHINVSRCALPHA;
	
			default:
				debug_assert ( false, "Invalid blend mode" );
		}
	}
	//End ConvertBlendModeToD3D



    //=========================================================================
    //! @function    ConvertCmpFuncToD3D
    //! @brief       Convert a comparison function (for depth test/alpha test, etc)
	//!				 to its Direct3D equivilent
    //!              
    //! @param       func [in]
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	D3DCMPFUNC ConvertCmpFuncToD3D ( Renderer::ECmpFunc func )
	{
		switch ( func )
		{
			case Renderer::CMP_NEVER:
				return D3DCMP_NEVER;
	
			case Renderer::CMP_LESS:
				return D3DCMP_LESS;
	
			case Renderer::CMP_LEQUAL:
				return D3DCMP_LESSEQUAL;
	
			case Renderer::CMP_GREATER:
				return D3DCMP_GREATER;

			case Renderer::CMP_GEQUAL:
				return D3DCMP_GREATEREQUAL;
	
			case Renderer::CMP_ALWAYS:
				return D3DCMP_ALWAYS;

			case Renderer::CMP_EQUAL:
				return D3DCMP_EQUAL;

			case Renderer::CMP_NOTEQUAL:
				return D3DCMP_NOTEQUAL;
	
			default:
				debug_assert ( false, "Invalid comparison function!" ); 
		}
	}
	//End ConvertCmpFuncToD3D



    //=========================================================================
    //! @function    ConvertStencilOpToD3D
    //! @brief       Convert a stencil operation to D3DSTENCILOP equivilent
    //!              
    //! @param       op [in] Operation to convert
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	D3DSTENCILOP ConvertStencilOpToD3D ( Renderer::EStencilOp op )
	{
		switch ( op )
		{
			case Renderer::STENCILOP_KEEP:
				return D3DSTENCILOP_KEEP;
		
			case Renderer::STENCILOP_ZERO:
				return D3DSTENCILOP_ZERO;
		
			case Renderer::STENCILOP_REPLACE:
				return D3DSTENCILOP_REPLACE;
	
			case Renderer::STENCILOP_INCRSAT:
				return D3DSTENCILOP_INCRSAT;
	
			case Renderer::STENCILOP_DECRSAT:
				return D3DSTENCILOP_DECRSAT;
	
			case Renderer::STENCILOP_INVERT:
				return D3DSTENCILOP_INVERT;
		
			case Renderer::STENCILOP_INCR:
				return D3DSTENCILOP_INCR;
		
			case Renderer::STENCILOP_DECR:
				return D3DSTENCILOP_DECR;

			default:
				debug_assert( false, "Invalid stencil op" );
		}

	}
	//End ConvertStencilOpToD3D



    //=========================================================================
    //! @function    ConvertFogModeToD3D
    //! @brief       Convert a member of the EFogMode enumeration to its D3DFOGMODE equivilient
    //!              
    //! @param       mode 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	D3DFOGMODE ConvertFogModeToD3D ( Renderer::EFogMode mode )
	{
		switch ( mode )
		{
			case Renderer::FOGMODE_NONE:
				return D3DFOG_NONE;
	
			case Renderer::FOGMODE_EXP:
				return D3DFOG_EXP;
	
			case Renderer::FOGMODE_EXP2:
				return D3DFOG_EXP2;
	
			case Renderer::FOGMODE_LINEAR:
				return D3DFOG_LINEAR;

			default:
				debug_assert ( false, "Invalid fog mode!" );
		}
	}
	//End ConvertFogModeToD3D



    //=========================================================================
    //! @function    ConvertTextureAddressingModeToD3D
    //! @brief		 Convert a member of teh ETextureAddressModeType enumeration to its Direct3D equivilent       
    //!              
    //! @param       mode [in] mode to convert
    //!              
    //! @return      Trapped in Direct3D conversion function factory - send help
    //! @throw       
    //=========================================================================
	D3DTEXTUREADDRESS ConvertTextureAddressingModeToD3D( Renderer::ETextureAddressingMode mode)
	{
		switch ( mode )
		{
			case Renderer::TEXADDRESS_WRAP:
				return D3DTADDRESS_WRAP;
 
			case Renderer::TEXADDRESS_CLAMP:
				return D3DTADDRESS_CLAMP;
 
			case Renderer::TEXADDRESS_BORDER:
				return D3DTADDRESS_BORDER;

			case Renderer::TEXADDRESS_MIRROR:
				return D3DTADDRESS_MIRROR;
 
			case Renderer::TEXADDRESS_MIRRORONCE:
				return D3DTADDRESS_MIRRORONCE;

			default:
				debug_assert ( false, "Invalid addressing mode!" );
		}
	}
	//End ConvertTextureAddressingModeToD3D


    //=========================================================================
    //! @function    ConvertPixelFormatToD3D
    //! @brief       Convert a pixel format to its Direct3D equivilent
    //!              
	//!				 Not all pixel formats are compatible with Direct3D
	//!				 this function will return false, if the format is incompatible
	//!				 or we don't wish to support it
	//!
    //! @param       format	  [in]
	//! @param		 dxFormat [out]
    //!              
    //! @return      true if the format could be converted, false otherwise
    //=========================================================================
	bool ConvertPixelFormatToD3D ( Imaging::PixelFormat format, D3DFORMAT& dxFormat ) throw()
	{
			switch ( format )
			{
				case Imaging::PXFMT_A8R8G8B8:
					dxFormat = D3DFMT_A8R8G8B8;
					return true;
		 
				case Imaging::PXFMT_A8B8G8R8:
					dxFormat = D3DFMT_A8B8G8R8;
					return true;
		  
				case Imaging::PXFMT_X8R8G8B8:
					dxFormat = D3DFMT_X8R8G8B8;
					return true;

				case Imaging::PXFMT_R5G6B5:
					dxFormat = D3DFMT_R5G6B5;
					return true;
		 
				case Imaging::PXFMT_X1R5G5B5:
					dxFormat = D3DFMT_X1R5G5B5;
					return true;
		 
				case Imaging::PXFMT_A1R5G5B5:
					dxFormat = D3DFMT_A1R5G5B5;
					return true;
		 
				case Imaging::PXFMT_ALPHA8:
					dxFormat = D3DFMT_A8;
					return true;

				case Imaging::PXFMT_LUMINANCE8:
					dxFormat = D3DFMT_L8;
					return true;
		 
				case Imaging::PXFMT_DXT1:
					dxFormat = D3DFMT_DXT1;
					return true;
				
				case Imaging::PXFMT_DXT2:
					dxFormat = D3DFMT_DXT2;
					return true;

				case Imaging::PXFMT_DXT3:
					dxFormat = D3DFMT_DXT3;
					return true;
				
				case Imaging::PXFMT_DXT4:
					dxFormat = D3DFMT_DXT4;
					return true;
				
				case Imaging::PXFMT_DXT5:
					dxFormat = D3DFMT_DXT5;
					return true;

				default:
					std::cerr << __FUNCTION__ << ": couldn't convert format" << std::endl;
					return false;
			}

	}
	//End ConvertPixelFormatToD3D


    //=========================================================================
    //! @function    ConvertD3DFormatToPixelFormat
    //! @brief       Convert a Direct3D format to a pixel format
    //!              
    //! @param       dxFormat [in]
    //! @param		 format	  [out]      
	//!
    //! @return      true if succeeded, false if failed
    //! @throw       
    //=========================================================================
	bool ConvertD3DFormatToPixelFormat ( D3DFORMAT dxFormat, Imaging::PixelFormat& format ) throw()
	{

		switch ( dxFormat )
		{
			case D3DFMT_A8R8G8B8:
				format = Imaging::PXFMT_A8R8G8B8;
				return true;
		
			case D3DFMT_A8B8G8R8:
				format = Imaging::PXFMT_A8B8G8R8;
				return true;
		
			case D3DFMT_X8R8G8B8:
				format = Imaging::PXFMT_X8R8G8B8;
				return true;

			case D3DFMT_R5G6B5:
				format = Imaging::PXFMT_R5G6B5;
				return true;
		
			case D3DFMT_X1R5G5B5:
				format = Imaging::PXFMT_X1R5G5B5;
				return true;
		
			case D3DFMT_A1R5G5B5:
				format = Imaging::PXFMT_A1R5G5B5;
				return true;
		
			case D3DFMT_A8:
				format = Imaging::PXFMT_ALPHA8;
				return true;

			case D3DFMT_L8:
				format = Imaging::PXFMT_LUMINANCE8;
				return true;
		
			case D3DFMT_DXT1:
				format = Imaging::PXFMT_DXT1;
				return true;
			
			case D3DFMT_DXT2:
				format = Imaging::PXFMT_DXT2;
				return true;

			case D3DFMT_DXT3:
				format = Imaging::PXFMT_DXT3;
				return true;
			
			case D3DFMT_DXT4:
				format = Imaging::PXFMT_DXT4;
				return true;
			
			case D3DFMT_DXT5:
				format = Imaging::PXFMT_DXT5;
				return true;

			default:
				std::cerr << __FUNCTION__ << ": Couldn't convert format" << std::endl;
				return false;
		}

	}
	//End ConvertD3DFormatToPixelFormat

};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_CONVERSIONFUNCTIONS_H