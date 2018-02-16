//======================================================================================
//! @file         DeviceCapabilities.cpp
//! @brief        Functions relating to device capabilities
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 12 June 2005
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


#include <d3d9.h>
#include "Core/Core.h"
#include "Renderer/RendererCapabilities.h"
#include "DirectX9Renderer/DeviceCapabilities.h"



using namespace Renderer;



//namespace DirectX9Renderer
namespace DirectX9Renderer
{


    //=========================================================================
    //! @function    Supports
    //! @brief       Determines whether a set of Direct3D device capabilities
	//!				 supports a renderer capability
    //!              
    //! @param       d3dCaps 
    //! @param       capability 
    //!              
    //! @return      true if supported, false otherwise
    //=========================================================================
	bool Supports ( const D3DCAPS9& d3dCaps, Renderer::ERendererCapability capability )
	{

			switch ( capability )
			{

				case CAP_HWRASTERISATION:
					if ( d3dCaps.DevCaps & D3DDEVCAPS_HWRASTERIZATION)
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_HWTRANSFORMANDLIGHT:
					if ( d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ANISOTROPICFILTERING:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_ANISOTROPY)
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_FOGRANGE:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGRANGE)
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_FOGTABLE:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGTABLE)
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_FOGVERTEX:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGVERTEX)
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_MIPMAPLODBIAS:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_MIPMAPLODBIAS)
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SCISSORTEST:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_SCISSORTEST )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SLOPESCALEDEPTHBIAS:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_SLOPESCALEDEPTHBIAS )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ZFOG:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_ZFOG )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Depth test capabilities
				case CAP_DEPTHBIAS:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_DEPTHBIAS )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST:
					if ( d3dCaps.RasterCaps & D3DPRASTERCAPS_ZTEST )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_ALWAYS:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_ALWAYS )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_EQUAL:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_EQUAL )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_GREATER:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_GREATER )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_GEQUAL:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_LESS:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_LESS )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_LEQUAL:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_LESSEQUAL )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_NEVER:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_NEVER )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DEPTHTEST_NOTEQUAL:
					if ( d3dCaps.ZCmpCaps & D3DPCMPCAPS_NOTEQUAL )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Source blend capabilities
				case CAP_SRCBLEND_FACTOR:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_BLENDFACTOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_BOTHINVSRCALPHA:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_BOTHINVSRCALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_DESTALPHA:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_DESTALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_DESTCOLOUR:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_DESTCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_INVDESTALPHA:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_INVDESTALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_INVDESTCOLOUR:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_INVDESTCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_INVSRCALPHA:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_INVSRCALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_INVSRCCOLOUR:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_INVSRCCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_ONE:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_ONE )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_SRCALPHA:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_SRCALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_SRCALPHASAT:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_SRCALPHASAT )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SRCBLEND_SRCCOLOUR:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_SRCCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}
				case CAP_SRCBLEND_ZERO:
					if ( d3dCaps.SrcBlendCaps & D3DPBLENDCAPS_ZERO )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Destination blend capabilities
				case CAP_DESTBLEND_FACTOR:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_BLENDFACTOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_BOTHINVSRCALPHA:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_BOTHINVSRCALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_DESTALPHA:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_DESTALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_DESTCOLOUR:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_DESTCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_INVDESTALPHA:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_INVDESTALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}
				case CAP_DESTBLEND_INVDESTCOLOUR:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_INVDESTCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_INVSRCALPHA:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_INVSRCCOLOUR:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_INVSRCCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_ONE:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_ONE )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_SRCALPHA:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_SRCALPHA )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_SRCALPHASAT:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_SRCALPHASAT )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_SRCCOLOUR:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_SRCCOLOR )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DESTBLEND_ZERO:
					if ( d3dCaps.DestBlendCaps & D3DPBLENDCAPS_ZERO )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Alpha test capabilities
				case CAP_ALPHATEST:
					if ( (d3dCaps.AlphaCmpCaps == D3DPCMPCAPS_ALWAYS) || (d3dCaps.AlphaCmpCaps == D3DPCMPCAPS_NEVER)  )
					{
						//If the caps contain only D3DPCMDCAPS_ALWAYS or D3DPCMDCAPS_NEVER
						//then alpha testing is not supported
						return false;
					}
					else
					{
						return true;
					}

				case CAP_ALPHATEST_ALWAYS:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_ALWAYS) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ALPHATEST_EQUAL:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_EQUAL) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ALPHATEST_GREATER:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_GREATER) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ALPHATEST_GEQUAL:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ALPHATEST_LESS:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_LESS) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ALPHATEST_LEQUAL:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_LESSEQUAL) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ALPHATEST_NEVER:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_NEVER) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_ALPHATEST_NOTEQUAL:
					if ( (d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_NOTEQUAL) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Shading capabilities
				case CAP_SHADE_ALPHAGOURAUD:
					if ( (d3dCaps.ShadeCaps & D3DPSHADECAPS_ALPHAGOURAUDBLEND) )
					{
						return true;
					}
					else
					{
						return false;
					}
				case CAP_SHADE_COLOURGOURAUD:
					if ( (d3dCaps.ShadeCaps & D3DPSHADECAPS_COLORGOURAUDRGB) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SHADE_FOGGOURAUD:
					if ( (d3dCaps.ShadeCaps & D3DPSHADECAPS_FOGGOURAUD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_SHADE_SPECULARGOURAUD:
					if ( (d3dCaps.ShadeCaps & D3DPSHADECAPS_SPECULARGOURAUDRGB) )
					{
						return true;
					}
					else
					{
						return false;
					}
				//Texture capabilities
				case CAP_TEXTURE_ALPHA:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_ALPHA) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_CUBEMAP:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_CUBEMAP) )
					{
						return true;
					}
					else
					{
						return false;
					}
				/*
				case CAP_TEXTURE_CUBEMAP_NONPOW2:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_CUBEMAP_POW2) )
					{
						return true;
					}
					else
					{
						return false;
					}
				*/
				case CAP_TEXTURE_MIPCUBEMAP:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_MIPCUBEMAP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_MIPMAP:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_MIPMAP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_MIPVOLUMEMAP:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_MIPVOLUMEMAP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_PERSPECTIVE:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_PERSPECTIVE) )
					{
						return true;
					}
					else
					{
						return false;
					}
/*
				case CAP_TEXTURE_NONPOW2_CONDITIONAL:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_NONPOW2CONDITIONAL) )
					{
						return true;
					}
					else
					{
						return false;
					}
*/
				case CAP_TEXTURE_PROJECTED:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_PROJECTED) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_NONSQUARE:
					if ( !(d3dCaps.TextureCaps & D3DPTEXTURECAPS_SQUAREONLY) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_VOLUMEMAP:
					if ( (d3dCaps.TextureCaps & D3DPTEXTURECAPS_VOLUMEMAP) )
					{
						return true;
					}
					else
					{
						return false;
					}
				/*
				case CAP_TEXTURE_VOLUMEMAP_NONPOW2:
					if ( !(d3dCaps.TextureCaps & D3DPTEXTURECAPS_VOLUMEMAP_POW2) )
					{
						return true;
					}
					else
					{
						return false;
					}
				*/

				//Texture filter capabilities
				case CAP_TEXTURE_FILTER_MAG_POINT:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MAGFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MIN_POINT:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MINFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MAG_ANISOTROPIC:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MAGFANISOTROPIC) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MIN_ANISOTROPIC:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MINFANISOTROPIC) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MIN_PYRAMIDALQUAD:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MINFPYRAMIDALQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MAG_PYRAMIDALQUAD:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MAGFPYRAMIDALQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MIN_GAUSSIANQUAD:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MINFGAUSSIANQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MAG_GAUSSIANQUAD:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MAGFGAUSSIANQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MIP_POINT:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_MIP_LINEAR:
					if ( (d3dCaps.TextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Cubemap filter capabilities
				case CAP_TEXTURE_FILTER_CUBE_MAG_POINT:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MAGFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MIN_POINT:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MINFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MAG_ANISOTROPIC:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MAGFANISOTROPIC) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MIN_ANISOTROPIC:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MINFANISOTROPIC) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MIN_PYRAMIDALQUAD:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MINFPYRAMIDALQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MAG_PYRAMIDALQUAD:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MAGFPYRAMIDALQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MIN_GAUSSIANQUAD:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MINFGAUSSIANQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MAG_GAUSSIANQUAD:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MAGFGAUSSIANQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MIP_POINT:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_CUBE_MIP_LINEAR:
					if ( (d3dCaps.CubeTextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Volume filter capabilities
				case CAP_TEXTURE_FILTER_VOLUME_MAG_POINT:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MIN_POINT:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MINFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MAG_ANISOTROPIC:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MAGFANISOTROPIC) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MIN_ANISOTROPIC:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MINFANISOTROPIC) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MIN_PYRAMIDALQUAD:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MINFPYRAMIDALQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MAG_PYRAMIDALQUAD:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MAGFPYRAMIDALQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MIN_GAUSSIANQUAD:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MINFGAUSSIANQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MAG_GAUSSIANQUAD:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MAGFGAUSSIANQUAD) )
					{
						return true;
					}
					else
					{
						return false;
					}
				case CAP_TEXTURE_FILTER_VOLUME_MIP_POINT:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_FILTER_VOLUME_MIP_LINEAR:
					if ( (d3dCaps.VolumeTextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Texture address capabilities
				case CAP_TEXTURE_ADDRESS_BORDER:
					if ( (d3dCaps.TextureAddressCaps & D3DPTADDRESSCAPS_BORDER) )
					{
						return true;
					}
					else
					{
						return false;
					}
				case CAP_TEXTURE_ADDRESS_CLAMP:
					if ( (d3dCaps.TextureAddressCaps & D3DPTADDRESSCAPS_CLAMP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_ADDRESS_INDEPENDENTUV:
					if ( (d3dCaps.TextureAddressCaps & D3DPTADDRESSCAPS_INDEPENDENTUV) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_ADDRESS_MIRROR:
					if ( (d3dCaps.TextureAddressCaps & D3DPTADDRESSCAPS_MIRROR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_ADDRESS_MIRRORONCE:
					if ( (d3dCaps.TextureAddressCaps & D3DPTADDRESSCAPS_MIRRORONCE) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXTURE_ADDRESS_WRAP:
					if ( (d3dCaps.TextureAddressCaps & D3DPTADDRESSCAPS_WRAP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Stencil capabilities
				case CAP_STENCIL_KEEP:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_KEEP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_STENCIL_ZERO:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_ZERO) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_STENCIL_REPLACE:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_REPLACE) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_STENCIL_INCRSAT:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_INCRSAT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_STENCIL_DECRSAT:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_DECRSAT) )
					{
						return true;
					}
					else
					{
						return false;
					}
				case CAP_STENCIL_INVERT:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_INVERT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_STENCIL_INCR:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_INCR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_STENCIL_DECR:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_DECR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_STENCIL_TWOSIDED:
					if ( (d3dCaps.StencilCaps & D3DSTENCILCAPS_TWOSIDED) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Texture operation capabilities
				case CAP_TEXOP_ADD:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_ADD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_ADDSIGNED:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_ADDSIGNED2X:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED2X) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_ADDSMOOTH:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_ADDSMOOTH) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_BLENDCURRENTALPHA:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_BLENDCURRENTALPHA) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_BLENDDIFFUSEALPHA:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_BLENDDIFFUSEALPHA) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_BLENDFACTORALPHA:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_BLENDFACTORALPHA) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_BLENDTEXTUREALPHA:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_BLENDTEXTUREALPHA) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_BLENDTEXTUREALPHAPM:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_BLENDTEXTUREALPHAPM) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_DISABLE:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_DISABLE) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_DOTPRODUCT3:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_DOTPRODUCT3) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_LERP:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_LERP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MODULATE:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATE) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MODULATE2X:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATE2X) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MODULATE4X:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATE4X) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MODULATE_ALPHA_ADDCOLOUR:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MODULATE_COLOUR_ADDALPHA:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATECOLOR_ADDALPHA) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MODULATE_INVALPHA_ADDCOLOUR:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MODULATE_INVCOLOUR_ADDALPHA:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_MULTIPLYADD:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MULTIPLYADD) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_PREMODULATE:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_PREMODULATE) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_SELECTARG1:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_SELECTARG1) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_SELECTARG2:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_SELECTARG2) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXOP_SUBTRACT:
					if ( (d3dCaps.TextureOpCaps & D3DTEXOPCAPS_SUBTRACT) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Light caps
				case CAP_LIGHT_DIRECTIONAL:
					if ( (d3dCaps.VertexProcessingCaps & D3DVTXPCAPS_DIRECTIONALLIGHTS) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_LIGHT_SPECULARLOCALVIEWER:
					if ( (d3dCaps.VertexProcessingCaps & D3DVTXPCAPS_LOCALVIEWER) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_LIGHT_POSITIONAL:
					if ( (d3dCaps.VertexProcessingCaps & D3DVTXPCAPS_POSITIONALLIGHTS) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Texgen
				case CAP_TEXGEN:
					if ( (d3dCaps.VertexProcessingCaps & D3DVTXPCAPS_TEXGEN) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_TEXGEN_SPHEREMAP:
					if ( (d3dCaps.VertexProcessingCaps & D3DVTXPCAPS_TEXGEN_SPHEREMAP) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Material caps
				case CAP_MATERIAL_SOURCECOLOUR:
					if ( (d3dCaps.VertexProcessingCaps & D3DVTXPCAPS_MATERIALSOURCE7) )
					{
						return true;
					}
					else
					{
						return false;
					}
				
				//Declaration types
				case CAP_DECL_UBYTE4:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_UBYTE4) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_UBYTE4N:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_UBYTE4N) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_SHORT2N:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_SHORT2N) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_SHORT4N:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_SHORT4N) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_USHORT2N:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_USHORT2N) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_USHORT4N:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_USHORT4N) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_DEC3N:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_DEC3N) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_FLOAT16_2:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_FLOAT16_2) )
					{
						return true;
					}
					else
					{
						return false;
					}

				case CAP_DECL_FLOAT16_4:
					if ( (d3dCaps.DeclTypes & D3DDTCAPS_FLOAT16_4) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//Shader caps
				case CAP_SHADER_DIRECTX_VERTEXSHADER_ASM:
					if ( (d3dCaps.VertexShaderVersion != 0) )
					{
						return true;
					}
					else
					{
						return false;
					}

				//case CAP_SHADER_DIRECTX_VERTEXSHADER_HLSL:
				case CAP_SHADER_DIRECTX_PIXELSHADER_ASM:
					if ( (d3dCaps.PixelShaderVersion != 0) )
					{
						return true;
					}
					else
					{
						return false;
					}	
				//case CAP_SHADER_DIRECTX_PIXELSHADER_HLSL:

				case CAP_SHADER_OPENGL_ARB_VERTEXPROGRAM:
				case CAP_SHADER_OPENGL_VERTEXPROGRAM_GLSL:
				case CAP_SHADER_OPENGL_ARB_FRAGMENTPROGRAM:
				case CAP_SHADER_OPENGL_FRAGMENTPROGRAM_GLSL:
					return false;

				default:
					std::cerr << __FUNCTION__ << ": Invalid cap!" << std::endl;
			}

			return false;
	}
	//End Supports




    //=========================================================================
    //! @function    GetPropertyFromDeviceCaps
    //! @brief       Get an integer device property from direct 3D device caps
    //!              
    //! @param       d3dCaps 
    //! @param       capability 
    //!              
    //=========================================================================
	UInt GetPropertyFromDeviceCaps ( const D3DCAPS9& d3dCaps, Renderer::EIntegerRendererCapability capability )
	{

		switch ( capability )
		{
			//Texture caps:
			case CAP_TEXTURE_MAX_WIDTH:
				return d3dCaps.MaxTextureWidth;

			case CAP_TEXTURE_MAX_HEIGHT:
				return d3dCaps.MaxTextureHeight;
			
			case CAP_TEXTURE_MAX_VOLUMEEXTENT:
				return d3dCaps.MaxVolumeExtent;
			
			case CAP_TEXTURE_MAX_TEXTUREREPEAT:
				return d3dCaps.MaxTextureRepeat;
			
			case CAP_TEXTURE_MAX_ASPECTRATIO:
				return d3dCaps.MaxTextureAspectRatio;
			
			case CAP_TEXTURE_MAX_ANISOTROPY:
				return d3dCaps.MaxAnisotropy;
			
			case CAP_TEXTURE_MAX_BLENDSTAGES:
				return d3dCaps.MaxTextureBlendStages;
			
			case CAP_TEXTURE_MAX_SIMULTANEOUS:
				return d3dCaps.MaxSimultaneousTextures;

			//Light caps
			case CAP_LIGHT_MAX_ACTIVE:
				return d3dCaps.MaxActiveLights;
			
			//Misc caps
			case CAP_MAX_CLIPPLANES:
				return d3dCaps.MaxUserClipPlanes;
			
			case CAP_MAX_VERTEXBLENDMATRICES:
				return d3dCaps.MaxVertexBlendMatrices;
			
			case CAP_MAX_VERTEXBLENDMATRIXINDEX:
				return d3dCaps.MaxVertexBlendMatrixIndex;
			
			case CAP_MAX_PRIMITIVECOUNT:
				return d3dCaps.MaxPrimitiveCount;
			
			case CAP_MAX_VERTEXINDEX:
				return d3dCaps.MaxVertexIndex;

			case CAP_MAX_STREAMS:
				return d3dCaps.MaxStreams;
			
			case CAP_MAX_STREAMSTRIDE:
				return d3dCaps.MaxStreamStride;
			
			case CAP_VERTEXSHADERVERSION:
				return d3dCaps.VertexShaderVersion;
			
			case CAP_PIXELSHADERVERSION:
				return d3dCaps.PixelShaderVersion;
			
			case CAP_MAX_SIMULTANEOUS_RENDERTARGETS:
				return d3dCaps.NumSimultaneousRTs;

			default:
				std::cerr << __FUNCTION__ ":Invalid cap" << std::endl;

		}
	}
	//End GetPropertyFromDeviceCaps



    //=========================================================================
    //! @function    GetPropertyFromDeviceCaps
    //! @brief       Get a floating point device property from direct 3D device caps
    //!              
    //! @param       d3dCaps 
    //! @param       capability 
	//!
    //=========================================================================
	Float GetPropertyFromDeviceCaps ( const D3DCAPS9& d3dCaps, Renderer::EFloatRendererCapability capability )
	{

		switch( capability )
		{
			case CAP_GUARDBAND_LEFT:
				return d3dCaps.GuardBandLeft;

			case CAP_GUARDBAND_RIGHT:
				return d3dCaps.GuardBandRight;
				
			case CAP_GUARDBAND_TOP:
				return d3dCaps.GuardBandTop;
				
			case CAP_GUARDBAND_BOTTOM:
				return d3dCaps.GuardBandBottom;
				
			case CAP_EXTENTSADJUST:
				return d3dCaps.ExtentsAdjust;
				
			case CAP_MAX_POINTSIZE:
				return d3dCaps.MaxPointSize;
		
			default:
				std::cerr << __FUNCTION__ ": Invalid capability" << std::endl;
		}
		
		return 0.0f;
	}
	//End GetPropertyFromDeviceCaps



};
//end namespace DirectX9Renderer