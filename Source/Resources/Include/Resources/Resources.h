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

#include "resource.h"

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RESOURCES_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RESOURCES_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RESOURCES_EXPORTS
#define RESOURCES_API __declspec(dllexport)
#else
#define RESOURCES_API __declspec(dllimport)
#endif


// This class is exported from the Resources.dll
class RESOURCES_API Resources {
public:
	Resources(void);
	// TODO: add your methods here.
};

extern RESOURCES_API int nResources;

/*
#define IDD_OPTIONS                     106
#define IDD_SETTINGSDIALOGUE            106
#define IDC_DISPLAYMODELIST             1005
#define IDEXIT                          1006
#define IDC_FULLSCREEN                  1007
#define IDSTART                         1008
#define IDC_CONSOLEFRAME                1011
#define IDC_CONSOLEDISPLAY              1012
#define IDC_COLOURDEPTH                 1013
#define IDC_COLOURDEPTHLIST             1014
#define IDC_COMMANDLINE                 1019
#define IDC_EXECUTE                     1020
*/

RESOURCES_API int fnResources(void);
