//======================================================================================
//! @file         Formats.h
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

#ifndef DIRECTX9RENDERER_FORMATS_H
#define DIRECTX9RENDERER_FORMATS_H


#include <d3d9.h>


//namespace DirectX9Renderer
namespace DirectX9Renderer
{

	const std::string& D3DFormatToString ( D3DFORMAT format );
	UInt FormatBitsPerPixel ( D3DFORMAT format );

};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_FORMATS_H
