//======================================================================================
//! @file         Config.h
//! @brief        Contains defines for different build configurations, and 
//!               different platforms
//!
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 21 September 2005
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

#ifndef CORE_CONFIG_H
#define CORE_CONFIG_H


//=========================================================================
// Defines for different platforms
//=========================================================================
#define CORE_PLATFORM_WIN32		0
#define CORE_PLATFORM_LINUX		1
//=========================================================================
// End 
//=========================================================================


//=========================================================================
// STLPort
//=========================================================================
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#	define CORE_HASHMAP_SUPPORTED	1
#	define CORE_HASHSET_SUPPORTED	1
#endif
//=========================================================================
// End STLPort
//=========================================================================


//=========================================================================
// Win32 specific
//=========================================================================
#if defined( __WIN32__ ) || defined( _WIN32 )
#	define CORE_PLATFORM	CORE_PLATFORM_WIN32	

//Debug builds
#		ifdef _DEBUG
#			define DEBUG_BUILD		1
#			define CORE_ASSERTS		1
#		else
#			define RELEASE_BUILD	1
#		endif
//#ifdef _DEBUG

//For DLLs
#   	ifndef CORE_NONCLIENT_BUILD
#       	define CoreExport __declspec( dllexport )
#   	else
#       	define CoreExport __declspec( dllimport )
#   	endif
//#ifndef ( CORE_NONCLIENT_BUILD )

//=========================================================================
// MS Visual Studio specific
//=========================================================================
#	ifdef _MSC_VER

#		ifndef CORE_HASHMAP_SUPPORTED
#			define CORE_HASHMAP_SUPPORTED		1
#		endif

#		ifndef CORE_HASHSET_SUPPORTED
#			define CORE_HASHSET_SUPPORTED		1
#		endif

//Partial template specialisation is only supported in Visual Studio .NET 2003 or above
#		if _MSC_VER > 1300
#			define CORE_PARTIAL_TEMPLATE_SPECIALISATION		1
#		endif

#	endif
//=========================================================================
// End MS Visual Studio specific
//=========================================================================

#else
//=========================================================================
// End Win32 specific
//=========================================================================

#	pragma error "Only Win32 is supported at the moment!"
#endif
//#ifndef _WIN32



#endif
//#ifndef CORE_CONFIG_H

