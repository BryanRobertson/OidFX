//======================================================================================
//! @file         DeviceCapabilities.h
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

#ifndef DIRECTX9RENDERER_DEVICECAPABILITIES_H
#define DIRECTX9RENDERER_DEVICECAPABILITIES_H


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


	//Determine whether a set of Direct3D device capabilities supports a renderer capability
	bool Supports ( const D3DCAPS9& d3dCaps, Renderer::ERendererCapability capability );

	//Get an integer device property from device caps
	UInt  GetPropertyFromDeviceCaps ( const D3DCAPS9& d3dCaps, Renderer::EIntegerRendererCapability capability );

	//Get a floating point device property from device caps
	Float GetPropertyFromDeviceCaps ( const D3DCAPS9& d3dCaps, Renderer::EFloatRendererCapability capability );


};
//end namespace DirectX9Renderer



#endif
//#ifndef DIRECTX9RENDERER_DEVICECAPABILITIES_H
