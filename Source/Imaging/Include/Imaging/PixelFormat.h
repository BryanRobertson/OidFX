//======================================================================================
//! @file         PixelFormat.h
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


#ifndef PIXELFORMATS_H
#define PIXELFORMATS_H


//namespace Imaging
namespace Imaging
{
	//! If you change this, then change the pixelFormatBitsPerPixel array
	//! in PixelFormat.cpp also!!!
	//!
	//! @see pixelFormatBitsPerPixel
	enum PixelFormat
	{
		PXFMT_A8R8G8B8	, //!< 32 bit ARGB
		PXFMT_R8G8B8A8	, //!< 32 bit RGBA
		PXFMT_A8B8G8R8	, //!< 32 bit ABGR
		PXFMT_X8R8G8B8	, //!< 32 bit RGB
		PXFMT_B8G8R8A8	, //!< 32 bit BGRA
		PXFMT_R8G8B8	, //!< 24 bit RGB
		PXFMT_B8G8R8	, //!< 24 bit BGR
		PXFMT_R5G6B5	, //!< 16 bit 565 format
		PXFMT_X1R5G5B5	, //!< 16 bit 555 format
		PXFMT_A1R5G5B5	, //!< 16 bit 555 format, with 1 bit alpha
		PXFMT_ALPHA8	, //!< 8 bit alpha
		PXFMT_LUMINANCE8, //!< 8 bit luminance only
		PXFMT_INDEXED8	, //!< 8 bit indexed
		PXFMT_INDEXED4	, //!< 4 bit indexed
		PXFMT_INDEXED2	, //!< 2 bit indexed
		PXFMT_INDEXED1	, //!< 1 bit indexed
		
		//S3TC compressed formats
		PXFMT_DXT1,		//!< S3TC compressed RGB, no alpha, or 1 bit alpha
		PXFMT_DXT2,
		PXFMT_DXT3,		//!< S3TC compressed ARGB - explicit alpha
		PXFMT_DXT4,		
		PXFMT_DXT5,		//!< S3TC compressed ARGB - interpolated alpha

		PXFMT_END
	};

	UInt GetFormatBitsPerPixel ( PixelFormat format );
	bool IsFormatIndexed ( PixelFormat format );
};
//end namespace Imaging

#endif
//#ifndef PIXELFORMATS_H