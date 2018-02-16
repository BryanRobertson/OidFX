//======================================================================================
//! @file         FirstPersonCamera.h
//! @brief        Class for a camera with a first-person view
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 31 August 2005
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

#ifndef OIDFX_FIRSTPERSONCAMERA_H
#define OIDFX_FIRSTPERSONCAMERA_H


#include "OidFX/Camera.h"


//namespace OidFX
namespace OidFX
{

	//!@class	FirstPersonCamera
	//!@brief	Class representing a first person camera
	class FirstPersonCamera : public Camera
	{

		public:


            //=========================================================================
            // Constructors
            //=========================================================================
			FirstPersonCamera ( Scene& scene, Math::EHandedness rendererHandedness );

            //=========================================================================
            // Public methods
            //=========================================================================
			void Update ( Float timeElapsedInSeconds );

		private:


	};
	//End class FirstPersonCamera

}
//end namespace OidFX


#endif
//#ifndef OIDFX_FIRSTPERSONCAMERA_H