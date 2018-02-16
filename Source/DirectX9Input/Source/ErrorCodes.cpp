//======================================================================================
//! @file         ErrorCodes.cpp
//! @brief        Functions to convert DirectInput error codes to strings for debugging
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 19 July 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================


#include "Core/Core.h"
#include <dinput.h>
#include "DirectX9Input/ErrorCodes.h"


namespace DirectX9Input
{


//!Class to map Direct3D error messages to strings. Used in ErrorCodes.cpp
class DInputErrorCodeMapper
{
	public:

		DInputErrorCodeMapper()
		{
			m_errors[DI_BUFFEROVERFLOW]				= "DI_BUFFEROVERFLOW";
			m_errors[DI_DOWNLOADSKIPPED]			= "DI_DOWNLOADSKIPPED";
			m_errors[DI_EFFECTRESTARTED]			= "DI_EFFECTRESTARTED";
			m_errors[DI_NOEFFECT]					= "DI_NOEFFECT";
			m_errors[DI_NOTATTACHED]				= "DI_NOTATTACHED";
			m_errors[DI_OK]							= "DI_OK";
			m_errors[DI_POLLEDDEVICE]				= "DI_POLLEDDEVICE";
			m_errors[DI_PROPNOEFFECT]				= "DI_PROPNOEFFECT";
			m_errors[DI_SETTINGSNOTSAVED]			= "DI_SETTINGSNOTSAVED";
			m_errors[DI_TRUNCATED]					= "DI_TRUNCATED";
			m_errors[DI_TRUNCATEDANDRESTARTED]		= "DI_TRUNCATEDANDRESTARTED";
			m_errors[DI_WRITEPROTECT]				= "DI_WRITEPROTECT";
			m_errors[DIERR_ACQUIRED]				= "DIERR_ACQUIRED";
			m_errors[DIERR_ALREADYINITIALIZED]		= "DIERR_ALREADYINITIALIZED";
			m_errors[DIERR_BADDRIVERVER]			= "DIERR_BADDRIVERVER";
			m_errors[DIERR_BETADIRECTINPUTVERSION]	= "DIERR_BETADIRECTINPUTVERSION";
			m_errors[DIERR_DEVICEFULL]				= "DIERR_DEVICEFULL";
			m_errors[DIERR_DEVICENOTREG]			= "DIERR_DEVICENOTREG";
			m_errors[DIERR_EFFECTPLAYING]			= "DIERR_EFFECTPLAYING";
			m_errors[DIERR_GENERIC]					= "DIERR_GENERIC";
			m_errors[DIERR_HANDLEEXISTS]			= "DIERR_HANDLEEXISTS";
			m_errors[DIERR_HASEFFECTS]				= "DIERR_HASEFFECTS";
			m_errors[DIERR_INCOMPLETEEFFECT]		= "DIERR_INCOMPLETEEFFECT";
			m_errors[DIERR_INPUTLOST]				= "DIERR_INPUTLOST";
			m_errors[DIERR_INVALIDPARAM]			= "DIERR_INVALIDPARAM";
			m_errors[DIERR_MAPFILEFAIL]				= "DIERR_MAPFILEFAIL";
			m_errors[DIERR_MOREDATA]				= "DIERR_MOREDATA";
			m_errors[DIERR_NOAGGREGATION]			= "DIERR_NOAGGREGATION";
			m_errors[DIERR_NOINTERFACE]				= "DIERR_NOINTERFACE";
			m_errors[DIERR_NOTACQUIRED]				= "DIERR_NOTACQUIRED";
			m_errors[DIERR_NOTBUFFERED]				= "DIERR_NOTBUFFERED";
			m_errors[DIERR_NOTDOWNLOADED]			= "DIERR_NOTDOWNLOADED";
			m_errors[DIERR_NOTEXCLUSIVEACQUIRED]	= "DIERR_NOTEXCLUSIVEACQUIRED";
			m_errors[DIERR_NOTFOUND]				= "DIERR_NOTFOUND";
			m_errors[DIERR_NOTINITIALIZED]			= "DIERR_NOTINITIALIZED";
			m_errors[DIERR_OBJECTNOTFOUND]			= "DIERR_OBJECTNOTFOUND";
			m_errors[DIERR_OLDDIRECTINPUTVERSION]	= "DIERR_OLDDIRECTINPUTVERSION";
			m_errors[DIERR_OTHERAPPHASPRIO]			= "DIERR_OTHERAPPHASPRIO";
			m_errors[DIERR_OUTOFMEMORY]				= "DIERR_OUTOFMEMORY";
			m_errors[DIERR_READONLY]				= "DIERR_READONLY";
			m_errors[DIERR_REPORTFULL]				= "DIERR_REPORTFULL";
			m_errors[DIERR_UNPLUGGED]				= "DIERR_UNPLUGGED";
			m_errors[DIERR_UNSUPPORTED]				= "DIERR_UNSUPPORTED";
			m_errors[E_HANDLE]						= "E_HANDLE";
			m_errors[E_PENDING]						= "E_PENDING";
			m_errors[E_POINTER]						= "E_POINTER";
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
//! @function    DirectX9Input::DirectInputErrorCodeToString
//! @brief       Return a string for a DirectInput error code
//!       
//!	@param		 errorCode [in] Error code from DirectInput
//!
//! @return		 A string representing the error code
//=========================================================================
const std::string& DirectX9Input::DirectInputErrorCodeToString ( HRESULT errorCode )
{
	static DInputErrorCodeMapper mapper;
	return mapper.MapErrorCodeToString(errorCode);
}
//End DirectX9Input::D3DErrorCodeToString


}
//end namespace DirectX9Input