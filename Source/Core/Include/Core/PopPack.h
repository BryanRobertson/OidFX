//======================================================================================
//! @file         PopPack.h
//! @brief        Platform independent header to restore the packing for data structures
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 15 August 2005
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


#ifdef WIN32

//#pragma pack(pop)
//#pragma pack(show)

#include <poppack.h>

#else

#error PopPack functionality not implemented for this platform yet!

#endif