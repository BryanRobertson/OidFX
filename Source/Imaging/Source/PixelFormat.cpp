//======================================================================================
//! @file         PixelFormat.cpp
//! @brief        Types and functions relating to pixel formats
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 19 January 2005
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
#include "Imaging/PixelFormat.h"



using namespace Imaging;



//=========================================================================
//! @function    Imaging::GetFormatBitsPerPixel
//! @brief		 Returns the bits required to store one pixel in the format provided
//! @return      Return the bits required per pixel for format.
//=========================================================================
UInt Imaging::GetFormatBitsPerPixel ( PixelFormat format )
{

	switch ( format )
	{
		case PXFMT_A8R8G8B8:
				return 32;
 
		case PXFMT_R8G8B8A8:
				return 32;
 
		case PXFMT_A8B8G8R8:
				return 32;
 
		case PXFMT_B8G8R8A8:
				return 32;

		case PXFMT_X8R8G8B8:
				return 32; 

		case PXFMT_R8G8B8:
				return 24;
 
		case PXFMT_B8G8R8:
				return 24;
 
		case PXFMT_R5G6B5:
				return 16;
 
		case PXFMT_X1R5G5B5:
				return 16;
 
		case PXFMT_A1R5G5B5:
				return 16;
 
		case PXFMT_ALPHA8:
				return 8;
 
		case PXFMT_LUMINANCE8:
				return 8;
 
		case PXFMT_INDEXED8:
				return 8;
 
		case PXFMT_INDEXED4:
				return 4;
 
		case PXFMT_INDEXED2:
				return 2;
 
		case PXFMT_INDEXED1:
				return 1;

		case PXFMT_DXT1:
				return 24;
		
		case PXFMT_DXT2:
				return 24;

		case PXFMT_DXT3:
				return 32;
		
		case PXFMT_DXT4:
				return 32;
		
		case PXFMT_DXT5:
				return 32;

		default:
				return 0;
	}
}
//end Imaging::GetFormatBitsPerPixel



//=========================================================================
//! @function    Imaging::IsFormatIndexed
//! @brief
//! @return       True if the format is indexed, false otherwise
//=========================================================================
bool Imaging::IsFormatIndexed ( PixelFormat format )
{
	switch ( format )
	{
		case PXFMT_INDEXED8:
		case PXFMT_INDEXED4:
		case PXFMT_INDEXED2:
		case PXFMT_INDEXED1:
			return true;

		default:
			return false;
	}
}
//end Imaging::IsFormatIndexed
