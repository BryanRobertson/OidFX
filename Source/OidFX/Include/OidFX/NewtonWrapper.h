//======================================================================================
//! @file         NewtonWrapper.h
//! @brief        Wraps the Newton physics library in a namespace
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

#ifndef OIDFX_NEWTONWRAPPER_H
#define OIDFX_NEWTONWRAPPER_H


//namespace OidFX
namespace OidFX
{

	//namespace Newton
	namespace Newton
	{

		//namespace Impl
		namespace Impl
		{
			//Include the Newton library in the Newton namespace
#			include <Newton.h>
		
		}
		//end namespace Impl

	}
	//End namespace Newton
}

#endif
//#ifndef OIDFX_NEWTONWRAPPER_H