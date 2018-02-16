//======================================================================================
//! @file         NewtonWorld.h
//! @brief        Classes to wrap the Newton world for the Newton physics library
//!               
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


#ifndef OIDFX_NEWTONWORLD_H
#define OIDFX_NEWTONWORLD_H



#include "Math/Matrix4x4.h"
#include "OidFX/NewtonWrapper.h"



//=========================================================================
// Forward declarations
//=========================================================================
namespace Math	{	class Triangle; class Vector3D;	 class ParametricLine3D;	}
namespace OidFX	{  namespace Newton { class Collision; } }


//namespace OidFX
namespace OidFX
{


	//namespace Newton
	namespace Newton
	{

		//!@class	World
		//!@brief	Class that wraps the NewtonWorld class, automatically creating
		//!			it on construction, and destroying it on destruction
		class World
		{
			public:

                //=========================================================================
                // Constructors
                //=========================================================================
				World ( );


                //=========================================================================
                // Public types
                //=========================================================================
				typedef  Core::Vector<Math::Vector3D>::Type	CollisionInfo;
				typedef	 Core::Vector<Float>::Type			PenetrationInfo;


                //=========================================================================
                // Public methods
                //=========================================================================
				UInt Collide ( const Newton::Collision& colliderA, 
							   const Math::Matrix4x4& colliderAMatrix,
							   const Newton::Collision& colliderB,
							   const Math::Matrix4x4& colliderBMatrix,
							   UInt maxCollisions,
							   CollisionInfo& contacts,
							   CollisionInfo& normals,
							   PenetrationInfo& penetration );

				Float Collide ( const Newton::Collision& collider,
								const Math::ParametricLine3D& line );

				Float SceneRaycast ( const Math::ParametricLine3D& line );

				Collision CreateSphere ( const Math::Vector3D& extents, 
										 const Math::Matrix4x4& offsetMatrix = Math::Matrix4x4::IdentityMatrix );

				Collision CreateBox    ( const Math::Vector3D& extents, 
										 const Math::Matrix4x4& offsetMatrix = Math::Matrix4x4::IdentityMatrix );

				Collision CreateTreeCollision ( const Core::Vector<Math::Triangle>::Type& triangles );



                //=========================================================================
                // Accessors
                //=========================================================================
				inline const Impl::NewtonWorld*	GetWorld() const;
				

			private:

                //=========================================================================
                // Private types
                //=========================================================================

                //=========================================================================
                // Private data
                //=========================================================================
				boost::shared_ptr<Impl::NewtonWorld> 	m_world;


		};
		//End Class World



        //=========================================================================
        //! @function    World::GetWorld
        //! @brief       Get a pointer to the Newton world object
        //!              
        //=========================================================================
		const Impl::NewtonWorld* World::GetWorld() const
		{
			return m_world.get();
		}
		//End World::GetWorld


	}
	//End namespace Newton

}
//end namespace OidFX



#endif
//#ifndef OIDFX_NEWTONWORLD_H
