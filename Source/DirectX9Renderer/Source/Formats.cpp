//======================================================================================
//! @file         Formats.cpp
//! @brief        Provides functions to map between Direct3D format codes, and format strings
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 02 June 2005
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
#include "DirectX9Renderer/Formats.h"
#include <map>

using namespace DirectX9Renderer;


//!Class to map Direct3D format codes to strings. Used in FormatCodes.cpp
class FormatCodeMapper
{
	public:

		FormatCodeMapper()
		{
			m_formats[D3DFMT_A2R10G10B10]		= "D3DFMT_A2R10G10B10";
			m_formats[D3DFMT_A8R8G8B8]			= "D3DFMT_A8R8G8B8";
			m_formats[D3DFMT_X8R8G8B8]			= "D3DFMT_X8R8G8B8";
			m_formats[D3DFMT_A1R5G5B5]			= "D3DFMT_A1R5G5B5";
			m_formats[D3DFMT_X1R5G5B5]			= "D3DFMT_X1R5G5B5";
			m_formats[D3DFMT_R5G6B5]			= "D3DFMT_R5G6B5";
			m_formats[D3DFMT_D16_LOCKABLE]		= "D3DFMT_D16_LOCKABLE";
			m_formats[D3DFMT_D32]				= "D3DFMT_D32";
			m_formats[D3DFMT_D15S1]				= "D3DFMT_D15S1";
			m_formats[D3DFMT_D24S8]				= "D3DFMT_D24S8";
			m_formats[D3DFMT_D24X8]				= "D3DFMT_D24X8";
			m_formats[D3DFMT_D24X4S4]			= "D3DFMT_D24X4S4";
			m_formats[D3DFMT_D32F_LOCKABLE]		= "D3DFMT_D32F_LOCKABLE";
			m_formats[D3DFMT_D24FS8]			= "D3DFMT_D24FS8";
			m_formats[D3DFMT_D16]				= "D3DFMT_D16";
			m_formats[D3DFMT_VERTEXDATA]		= "D3DFMT_VERTEXDATA";
			m_formats[D3DFMT_INDEX16]			= "D3DFMT_INDEX16";
			m_formats[D3DFMT_INDEX32]			= "D3DFMT_INDEX32";
			m_formats[D3DFMT_DXT1]				= "D3DFMT_DXT1";
			m_formats[D3DFMT_DXT2]				= "D3DFMT_DXT2";
			m_formats[D3DFMT_DXT3]				= "D3DFMT_DXT3";
			m_formats[D3DFMT_DXT4]				= "D3DFMT_DXT42";
			m_formats[D3DFMT_DXT5]				= "D3DFMT_DXT5";
			m_formats[D3DFMT_R16F]				= "D3DFMT_R16F";
			m_formats[D3DFMT_G16R16F]			= "D3DFMT_G16R16F";
			m_formats[D3DFMT_A16B16G16R16F]		= "D3DFMT_A16B16G16R16F";
			m_formats[D3DFMT_MULTI2_ARGB8]		= "D3DFMT_MULTI2_ARGB8";
			m_formats[D3DFMT_G8R8_G8B8]			= "D3DFMT_G8R8_G8B8";
			m_formats[D3DFMT_R8G8_B8G8]			= "D3DFMT_R8G8_B8G8";
			m_formats[D3DFMT_UYVY]				= "D3DFMT_UYVY";
			m_formats[D3DFMT_YUY2]				= "D3DFMT_YUY2";
			m_formats[D3DFMT_R32F]				= "D3DFMT_R32F";
			m_formats[D3DFMT_G32R32F]			= "D3DFMT_G32R32F";
			m_formats[D3DFMT_A32B32G32R32F]		= "D3DFMT_A32B32G32R32F";
			m_formats[D3DFMT_L6V5U5]			= "D3DFMT_L6V5U5";
			m_formats[D3DFMT_X8L8V8U8]			= "D3DFMT_X8L8V8U8";
			m_formats[D3DFMT_A2W10V10U10]		= "D3DFMT_A2W10V10U10";
			m_formats[D3DFMT_V8U8]				= "D3DFMT_V8U8";
			m_formats[D3DFMT_Q8W8V8U8]			= "D3DFMT_Q8W8V8U8";
			m_formats[D3DFMT_V16U16]			= "D3DFMT_V16U16";
			m_formats[D3DFMT_Q16W16V16U16]		= "D3DFMT_Q16W16V16U16";
			m_formats[D3DFMT_CxV8U8]			= "D3DFMT_CxV8U8";
			m_formats[D3DFMT_R8G8B8]			= "D3DFMT_R8G8B8";
			m_formats[D3DFMT_A8R8G8B8]			= "D3DFMT_A8R8G8B8";
			m_formats[D3DFMT_X8R8G8B8]			= "D3DFMT_X8R8G8B8";
			m_formats[D3DFMT_R5G6B5]			= "D3DFMT_R5G6B5";
			m_formats[D3DFMT_X1R5G5B5]			= "D3DFMT_X1R5G5B5";
			m_formats[D3DFMT_A1R5G5B5]			= "D3DFMT_A1R5G5B5";
			m_formats[D3DFMT_A4R4G4B4]			= "D3DFMT_A4R4G4B4";
			m_formats[D3DFMT_R3G3B2]			= "D3DFMT_R3G3B2";
			m_formats[D3DFMT_A8]				= "D3DFMT_A8";
			m_formats[D3DFMT_A8R3G3B2]			= "D3DFMT_A8R3G3B2";
			m_formats[D3DFMT_X4R4G4B4]			= "D3DFMT_X4R4G4B4";
			m_formats[D3DFMT_A2B10G10R10]		= "D3DFMT_A2B10G10R10";
			m_formats[D3DFMT_A8B8G8R8]			= "D3DFMT_A8B8G8R8";
			m_formats[D3DFMT_X8B8G8R8]			= "D3DFMT_X8B8G8R8";
			m_formats[D3DFMT_G16R16]			= "D3DFMT_G16R16";
			m_formats[D3DFMT_A2R10G10B10]		= "D3DFMT_A2R10G10B10";
			m_formats[D3DFMT_A16B16G16R16]		= "D3DFMT_A16B16G16R16";
			m_formats[D3DFMT_A8P8]				= "D3DFMT_A8P8";
			m_formats[D3DFMT_P8]				= "D3DFMT_P8";
			m_formats[D3DFMT_L8]				= "D3DFMT_L8";
			m_formats[D3DFMT_L16]				= "D3DFMT_L16";
			m_formats[D3DFMT_A8L8]				= "D3DFMT_A8L8";
			m_formats[D3DFMT_A4L4]				= "D3DFMT_A4L4";
			m_formats[D3DFMT_UNKNOWN]			= "D3DFMT_UNKNOWN";							 
		}										 
												
		const std::string& MapFormatCodeToString (D3DFORMAT formatCode)
		{
			return m_formats[formatCode];
		}

	private:

		std::map<D3DFORMAT, std::string> m_formats;

};
//End FormatCodeMapper


//=========================================================================
// Create a static member of the ErrorCodeMapper class to do the mappings
//=========================================================================
static FormatCodeMapper s_formatMapper;



//=========================================================================
//! @function    DirectX9Renderer::D3DFormatToString
//! @brief       Return a string for a Direct3D format code
//!       
//!	@param		 format [in] Format code from Direct3D
//!
//! @return		 A string representing the format code
//=========================================================================
const std::string& DirectX9Renderer::D3DFormatToString ( D3DFORMAT format )
{
	return s_formatMapper.MapFormatCodeToString(format);
}
//End DirectX9Renderer::D3DFormatToString



//=========================================================================
//! @function    DirectX9Renderer::FormatBitsPerPixel
//! @brief       Return the number of bits per pixel of a D3DFORMAT
//!       
//!	@param		 format [in] Format code from Direct3D
//!
//! @return		 The bits per pixel for the format
//=========================================================================
UInt DirectX9Renderer::FormatBitsPerPixel ( D3DFORMAT format ){
		switch ( format )
		{
			case D3DFMT_DXT1:
				return 24;

			case D3DFMT_DXT2:
				return 32;

			case D3DFMT_DXT3:
				return 32;

			case D3DFMT_DXT4:
				return 32;

			case D3DFMT_DXT5:
				return 32;

			case D3DFMT_D16_LOCKABLE:
				return 16;

			case D3DFMT_D32:
				return 32;

			case D3DFMT_D15S1:
				return 16;

			case D3DFMT_D24S8:
				return 32;

			case D3DFMT_D24X8:
				return 32;

			case D3DFMT_D24X4S4:
				return 32;

			case D3DFMT_D32F_LOCKABLE:
				return 32;

			case D3DFMT_D24FS8:
				return 32;

			case D3DFMT_D16:
				return 16;

			case D3DFMT_INDEX16:
				return 16;

			case D3DFMT_INDEX32:
				return 32;

			case D3DFMT_R8G8B8:
				return 24;
				
			case D3DFMT_A8R8G8B8:
				return 32;
				
			case D3DFMT_X8R8G8B8:
				return 32;
				
			case D3DFMT_R5G6B5:
				return 16;
				
			case D3DFMT_X1R5G5B5:
				return 16;
				
			case D3DFMT_A1R5G5B5:
				return 16;
				
			case D3DFMT_A4R4G4B4:
				return 16;
				
			case D3DFMT_R3G3B2:
				return 8;
				
			case D3DFMT_A8:
				return 8;
				
			case D3DFMT_A8R3G3B2:
				return 16;
				
			case D3DFMT_X4R4G4B4:
				return 16;
				
			case D3DFMT_A2B10G10R10:
				return 32;
				
			case D3DFMT_A8B8G8R8:
				return 32;
				
			case D3DFMT_X8B8G8R8:
				return 32;
				
			case D3DFMT_G16R16:
				return 32;
				
			case D3DFMT_A2R10G10B10:
				return 32;
				
			case D3DFMT_A16B16G16R16:
				return 64;
				
			case D3DFMT_A8P8:
				return 16;

			case D3DFMT_P8:
				return 8;

			case D3DFMT_L8:
				return 8;
				
			case D3DFMT_L16:
				return 16;

			case D3DFMT_A8L8:
				return 16;

			case D3DFMT_A4L4:
				return 16;

			default:
				return 0;
		}
}
//End DirectX9Renderer::FormatBitsPerPixel