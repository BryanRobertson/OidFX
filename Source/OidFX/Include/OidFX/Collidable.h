//======================================================================================
//! @file         Collidable.h
//! @brief        Interface for objects which support collision detection, using
//!				  Newton Colliders
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

#ifndef OIDFX_COLLIDABLE_H
#define OIDFX_COLLIDABLE_H


//namespace OidFX
namespace OidFX
{


	//!@class	ICollidable
	//!@brief	Interface for objects which support collision detection, using Newton Colliders
	class ICollidable
	{

		public:

            //=========================================================================
            // Destructor
            //=========================================================================
			virtual ~ICollidable = 0 {}

            //=========================================================================
            // Public methods
            //=========================================================================
			virtual const Newton::Collision&	GetCollision() const = 0;
			virtual const Math::Matrix4x4&		GetCollisionWorldMatrix() const = 0;
		
	};
	//End class ICollidable


}
//End namespace OidFX



#endif
//#ifndef OIDFX_COLLIDABLE_H
