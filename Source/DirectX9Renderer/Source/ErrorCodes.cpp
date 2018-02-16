//======================================================================================
//! @file         ErrorCodes.cpp
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


#include <d3d9.h>
#include <map>
#include "Core/Core.h"
#include "DirectX9Renderer/ErrorCodes.h"



using namespace DirectX9Renderer;


//!Class to map Direct3D error messages to strings. Used in ErrorCodes.cpp
class ErrorCodeMapper
{
	public:

		ErrorCodeMapper()
		{
			m_errors[D3D_OK]										= "D3D_OK";
			m_errors[D3DOK_NOAUTOGEN]								= "D3DOK_NOAUTOGEN";
			m_errors[D3DERR_CONFLICTINGRENDERSTATE]					= "D3DERR_CONFLICTINGRENDERSTATE";
			m_errors[D3DERR_CONFLICTINGTEXTUREFILTER]				= "D3DERR_CONFLICTINGTEXTUREFILTER";
			m_errors[D3DERR_CONFLICTINGTEXTUREPALETTE]				= "D3DERR_CONFLICTINGTEXTUREPALETTE";
			m_errors[D3DERR_DEVICELOST]								= "D3DERR_DEVICELOST";
			m_errors[D3DERR_DEVICENOTRESET]							= "D3DERR_DEVICENOTRESET";
			m_errors[D3DERR_DRIVERINTERNALERROR]					= "D3DERR_DRIVERINTERNALERROR";
			m_errors[D3DERR_DRIVERINVALIDCALL]						= "D3DERR_DRIVERINVALIDCALL";
			m_errors[D3DERR_INVALIDCALL]							= "D3DERR_INVALIDCALL";
			m_errors[D3DERR_INVALIDDEVICE]							= "D3DERR_INVALIDDEVICE";
			m_errors[D3DERR_MOREDATA]								= "D3DERR_MOREDATA";
			m_errors[D3DERR_INVALIDCALL]							= "D3DERR_INVALIDCALL";
			m_errors[D3DERR_INVALIDDEVICE]							= "D3DERR_INVALIDDEVICE";
			m_errors[D3DERR_NOTAVAILABLE]							= "D3DERR_NOTAVAILABLE";
			m_errors[D3DERR_NOTFOUND]								= "D3DERR_NOTFOUND";
			m_errors[D3DERR_OUTOFVIDEOMEMORY]						= "D3DERR_OUTOFVIDEOMEMORY";
			m_errors[D3DERR_TOOMANYOPERATIONS]						= "D3DERR_TOOMANYOPERATIONS";
			m_errors[D3DERR_UNSUPPORTEDALPHAARG]					= "D3DERR_UNSUPPORTEDALPHAARG";
			m_errors[D3DERR_UNSUPPORTEDALPHAOPERATION]				= "D3DERR_UNSUPPORTEDALPHAOPERATION";
			m_errors[D3DERR_UNSUPPORTEDCOLORARG]					= "D3DERR_UNSUPPORTEDCOLORARG";
			m_errors[D3DERR_UNSUPPORTEDCOLOROPERATION]				= "D3DERR_UNSUPPORTEDCOLOROPERATION";
			m_errors[D3DERR_UNSUPPORTEDFACTORVALUE]					= "D3DERR_UNSUPPORTEDFACTORVALUE";
			m_errors[D3DERR_UNSUPPORTEDTEXTUREFILTER]				= "D3DERR_UNSUPPORTEDTEXTUREFILTER";
			m_errors[D3DERR_WASSTILLDRAWING]						= "D3DERR_WASSTILLDRAWING";
			m_errors[D3DERR_WRONGTEXTUREFORMAT]						= "D3DERR_WRONGTEXTUREFORMAT";
			m_errors[E_FAIL]										= "E_FAIL";
			m_errors[E_INVALIDARG]									= "E_INVALIDARG";
			//m_errors[E_INVALIDCALL]									= "E_INVALIDCALL";
			m_errors[E_NOINTERFACE]									= "E_NOINTERFACE";
			m_errors[E_NOTIMPL]										= "E_NOTIMPL";
			m_errors[E_OUTOFMEMORY]									= "E_OUTOFMEMORY";
			m_errors[S_OK]											= "S_OK";
		}

		const std::string& MapErrorCodeToString(HRESULT errorCode)
		{
			return m_errors[errorCode];
		}

	private:

		std::map<HRESULT, std::string> m_errors;

};
//End ErrorCodeMapper


//=========================================================================
// Create a static member of the ErrorCodeMapper class to do the mappings
//=========================================================================
static ErrorCodeMapper s_mapper;



//=========================================================================
//! @function    DirectX9Renderer::D3DErrorCodeToString
//! @brief       Return a string for a Direct3D error code
//!       
//!	@param		 errorCode [in] Error code from Direct3D
//!
//! @return		 A string representing the error code
//=========================================================================
const std::string& DirectX9Renderer::D3DErrorCodeToString ( HRESULT errorCode )
{
	return s_mapper.MapErrorCodeToString(errorCode);
}
//End DirectX9Renderer::D3DErrorCodeToString