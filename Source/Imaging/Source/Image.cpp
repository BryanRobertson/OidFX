//======================================================================================
//! @file         Image.cpp
//! @brief        Class to store image data in various formats
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
#include "Imaging/Image.h"



using namespace Imaging;



//=========================================================================
//! @function    Imaging::Image::Constructor
//! @brief       
//!              
//=========================================================================
Image::Image ( UInt width, UInt height, UInt pitch, PixelFormat format )
: m_width(width), m_height(height), m_pitch(pitch), m_format(format)
{
	AllocateImageBuffer(width, height, format);
}
//end Imaging::Image::Constructor



//=========================================================================
//! @function    Imaging::Image::AllocateImageBuffer
//! @brief       Allocates memory for the image's data buffer
//!              
//!				 Depending on the platform, the image may have a pitch,
//!				 that is, an unused area of the image, at the end of every row.
//!				 So the buffer may be slightly bigger than requested.
//!              
//! @param       width		[in] Width of image buffer
//! @param       height		[in] Height of image buffer
//! @param       format		[in] Pixel format of the image buffer
//=========================================================================
void Image::AllocateImageBuffer ( UInt width, UInt height, PixelFormat format )
{
	debug_assert ( width != 0, "Invalid width" );
	debug_assert ( height != 0, "Invalid height" );
	debug_assert ( format != PXFMT_END, "Invalid pixel format" );

	if ( IsFormatIndexed(format) )
	{
		debug_assert ( false, "Indexed pixel formats not supported yet!" );
	}
	else
	{
		UInt size = (width+m_pitch) * height * GetFormatBitsPerPixel(format);
		m_pixelData.resize ( size );
		m_width = width;
		m_height = height;
		m_format = format;
	}
}
//end Image::AllocateImageBuffer



//=========================================================================
//! @function    Image::DumpToRAWFile
//! @brief       Dump the contents of the image to a RAW file
//!              
//! @param       fileName [in] Filename of the image to write
//!              
//=========================================================================
void Image::DumpToRAWFile ( const Char* fileName )
{

	debug_assert ( fileName, "Null pointer passed as file name!" );

	std::ofstream outFile( fileName );

	for ( UInt y=0; y < Height(); ++y )
	{
		for ( UInt x=0; x < Width(); ++x )
		{
			outFile.write( (std::ofstream::char_type*)&m_pixelData[(x + (y * (Pitch() + Width()))) ], 1 );
		}
	}

	outFile.close();

}
//End Image::DumpToRAWFile