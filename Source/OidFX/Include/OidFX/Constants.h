//======================================================================================
//! @file         Constants.h
//! @brief        OidFX engine constants
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 22 August 2005
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


#ifndef OIDFX_CONSTANTS_H
#define OIDFX_CONSTANTS_H


//namespace OidFX
namespace OidFX
{


	//! Constant representing one meter in game units
	const Float meters = 10.0f;
	const Float kilometers = meters * 1000.0f;

	//! Distance at which the LOD level changes from level 0 to the other levels
	const Float g_initialLODPopDistance = 210.0f * meters;

	//! Distance at which the LOD level changes
	const Float g_lodPopDistance = 100.0f * meters;
	
	//! Max LOD level. (0 is the highest detail level)
	const UInt g_lodMax = 5;

	//! Maximum number of projectiles that can be active at any one time
	const UInt g_maxProjectiles = 32;

	//! Maximum number of billboards that can be renderered per frame
	const UInt g_maxBillboards = 128;


}
//end namespace OidFX


#endif
//#ifndef OIDFX_CONSTANTS_H
