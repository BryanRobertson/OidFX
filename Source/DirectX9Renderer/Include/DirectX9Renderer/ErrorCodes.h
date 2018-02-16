//======================================================================================
//! @file         ErrorCodes.h
//! @brief        Provides functions to map between Direct3D error codes, and error messages
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 01 June 2005
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

#ifndef DIRECTX9RENDERER_ERRORCODES_H
#define DIRECTX9RENDERER_ERRORCODES_H


#include <d3d9.h>


//namespace DirectX9Renderer
namespace DirectX9Renderer
{

	inline std::string D3DErrorCodeToString ( HRESULT errorCode );


	//=========================================================================
	//! @function    DirectX9Renderer::D3DErrorCodeToString
	//! @brief       Return a string for a Direct3D error code
	//!       
	//!	@param		 errorCode [in] Error code from Direct3D
	//!
	//! @return		 A string representing the error code
	//=========================================================================
	std::string DirectX9Renderer::D3DErrorCodeToString ( HRESULT errorCode )
	{
		switch ( errorCode )
		{
			case D3D_OK:
				return "D3D_OK/S_OK";

			case D3DOK_NOAUTOGEN:
				return "D3DOK_NOAUTOGEN";

			case D3DERR_CONFLICTINGRENDERSTATE:
				return "D3DERR_CONFLICTINGRENDERSTATE";

			case D3DERR_CONFLICTINGTEXTUREFILTER:
				return "D3DERR_CONFLICTINGTEXTUREFILTER";

			case D3DERR_CONFLICTINGTEXTUREPALETTE:
				return "D3DERR_CONFLICTINGTEXTUREPALETTE";

			case D3DERR_DEVICELOST:
				return "D3DERR_DEVICELOST";

			case D3DERR_DEVICENOTRESET:
				return "D3DERR_DEVICENOTRESET";

			case D3DERR_DRIVERINTERNALERROR:
				return "D3DERR_DRIVERINTERNALERROR";

			case D3DERR_DRIVERINVALIDCALL:
				return "D3DERR_DRIVERINVALIDCALL";

			case D3DERR_INVALIDCALL:
				return "D3DERR_INVALIDCALL";

			case D3DERR_INVALIDDEVICE:
				return "D3DERR_INVALIDDEVICE";

			case D3DERR_MOREDATA:
				return "D3DERR_MOREDATA";

			case D3DERR_NOTAVAILABLE:
				return "D3DERR_NOTAVAILABLE";

			case D3DERR_NOTFOUND:
				return "D3DERR_NOTFOUND";

			case D3DERR_OUTOFVIDEOMEMORY:
				return "D3DERR_OUTOFVIDEOMEMORY";

			case D3DERR_TOOMANYOPERATIONS:
				return "D3DERR_TOOMANYOPERATIONS";

			case D3DERR_UNSUPPORTEDALPHAARG:
				return "D3DERR_UNSUPPORTEDALPHAARG";

			case D3DERR_UNSUPPORTEDALPHAOPERATION:
				return "D3DERR_UNSUPPORTEDALPHAOPERATION";

			case D3DERR_UNSUPPORTEDCOLORARG:
				return "D3DERR_UNSUPPORTEDCOLORARG";

			case D3DERR_UNSUPPORTEDCOLOROPERATION:
				return "D3DERR_UNSUPPORTEDCOLOROPERATION";

			case D3DERR_UNSUPPORTEDFACTORVALUE:
				return "D3DERR_UNSUPPORTEDFACTORVALUE";

			case D3DERR_UNSUPPORTEDTEXTUREFILTER:
				return "D3DERR_UNSUPPORTEDTEXTUREFILTER";

			case D3DERR_WASSTILLDRAWING:
				return "D3DERR_WASSTILLDRAWING";

			case D3DERR_WRONGTEXTUREFORMAT:
				return "D3DERR_WRONGTEXTUREFORMAT";

			case E_FAIL:
				return "E_FAIL";

			case E_INVALIDARG:
				return "E_INVALIDARG";

			case E_NOINTERFACE:
				return "E_NOINTERFACE";

			case E_NOTIMPL:
				return "E_NOTIMPL";

			case E_OUTOFMEMORY:
				return "E_OUTOFMEMORY";

			default:
				return "Unknown error code!";
		}

	}
	//End DirectX9Renderer::D3DErrorCodeToString

};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_ERRORCODES_H
