//======================================================================================
//! @file         CollisionManager.h
//! @brief        Manager class to deal with pairs of colliding objects
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 13 September 2005
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

#ifndef OIDFX_COLLISIONMANAGER_H
#define OIDFX_COLLISIONMANAGER_H


#include "Math/Vector3D.h"
#include "OidFX/NewtonWorld.h"
#include "OidFX/NewtonCollision.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace OidFX	{ class EntityNode; class SceneObject; class Scene;	class CollisionRecord;	}
namespace Newton { }


//namespace OidFX
namespace OidFX
{



	//!@class	CollisionManager
	//!@brief	Manager class to deal with pairs of colliding objects
	//!
	//!			Any entities which want to be CollisionRecord checked against the world, and other entities
	//!			must register themselves with the CollisionRecord manager
	//!
	//!			Every frame, the CollisionRecord manager builds a list of pairs of colliding objects,
	//!			and calls their CollisionRecord callbacks
	class CollisionManager
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			CollisionManager ( Scene& scene );

			~CollisionManager() { }


            //=========================================================================
            // Public types
            //=========================================================================
			typedef Newton::Collision				CollisionVolume;
			typedef Newton::World					World;
			typedef Newton::World::CollisionInfo	CollisionInfo;
			typedef Newton::World::PenetrationInfo	PenetrationInfo;


            //=========================================================================
            // Public methods
            //=========================================================================
			void AddCollider ( EntityNode* entityNode );
			void RemoveCollider ( EntityNode* entityNode );

			void CheckCollisions ( );
			void ExecuteCollisionList ( );

			void AddCollision ( const CollisionRecord& CollisionRecord );

            //=========================================================================
            // Proxy methods for the NewtonWorld class
            //=========================================================================
			UInt Collide ( const CollisionVolume& colliderA, 
						   const Math::Matrix4x4& colliderAMatrix,
						   const CollisionVolume& colliderB,
						   const Math::Matrix4x4& colliderBMatrix,
						   UInt maxCollisions,
						   CollisionInfo& contacts,
						   CollisionInfo& normals,
						   PenetrationInfo& penetration );

			Float Collide ( const Newton::Collision& collider,
								const Math::ParametricLine3D& line );

			Float SceneRaycast ( const Math::ParametricLine3D& line );

			CollisionVolume CreateSphere ( const Math::Vector3D& extents, 
											const Math::Matrix4x4& offsetMatrix = Math::Matrix4x4::IdentityMatrix );

			CollisionVolume CreateBox    ( const Math::Vector3D& extents, 
											const Math::Matrix4x4& offsetMatrix = Math::Matrix4x4::IdentityMatrix );

			CollisionVolume CreateTreeCollision ( const Core::Vector<Math::Triangle>::Type& triangles );


		private:

            //=========================================================================
            // Private types
            //=========================================================================
			typedef Core::List<EntityNode*>::Type				ColliderStore;
			typedef Core::Vector<CollisionRecord>::Type 		CollisionRecordStore;

            //=========================================================================
            // Private methods
            //=========================================================================
			void ClearCollisions ( );

            //=========================================================================
            // Private data
            //=========================================================================
			boost::shared_ptr<Newton::World>		m_world;
			ColliderStore			m_colliders;
			CollisionRecordStore	m_collisions;

			Scene&					m_scene;

			


	};
	//End class CollisionManager


	
	//!@class	CollisionRecord
	//!@brief	Class representing a CollisionRecord between an entity and another entity, 
	//!			or an entity and another scene object
	class CollisionRecord
	{
		public:


            //=========================================================================
            // Public
            //=========================================================================
			inline CollisionRecord ( EntityNode*	object1, 
							   SceneObject* object2,
							   const Math::Vector3D& collisionNormal,
							   Float depth );


            //=========================================================================
            // Public methods
            //=========================================================================
			inline EntityNode*	Object1();
			inline SceneObject* Object2();

			inline const Math::Vector3D& CollisionNormal() const;
			inline Float				 Depth() const;

			inline bool operator < ( const CollisionRecord& rhs ) const;

		private:

			EntityNode*		m_object1;
			SceneObject*	m_object2;
			Math::Vector3D	m_collisionNormal;
			Float			m_depth;

	};
	//End class CollisionRecord



    //=========================================================================
    //! @function    CollisionRecord::CollisionRecord
    //! @brief       CollisionRecord constructor
    //!              
    //! @param       object1			[in]	Entity that has collided
    //! @param       object2			[in]	Object that the entity collided with
    //! @param       collisionNormal	[in]	Normal of the CollisionRecord plane
    //! @param       depth				[in]	Depth that the entity penetrated the CollisionRecord plane
    //!              
    //=========================================================================
	CollisionRecord::CollisionRecord ( EntityNode* object1, 
						   SceneObject* object2,
						   const Math::Vector3D& collisionNormal,
						   Float depth )
						   : m_object1(object1),
						     m_object2(object2),
							 m_collisionNormal(collisionNormal),
							 m_depth(depth)
	{
		debug_assert ( object1, "Object1 is NULL!" );
		debug_assert ( object2, "Object2 is NULL!" );
	}
	//End CollisionRecord::CollisionRecord


    //=========================================================================
    //! @function    CollisionRecord::Object1
    //! @brief       Return the entity that is colliding
    //!              
    //! @return      The entity that is colliding
    //=========================================================================
	EntityNode* CollisionRecord::Object1()
	{
		return m_object1;
	}
	//End CollisionRecord::Object1


    //=========================================================================
    //! @function    CollisionRecord::Object2
    //! @brief       The object that the entity has collided with
    //!              
    //! @return      The object that the entity has collided with
    //=========================================================================
	SceneObject* CollisionRecord::Object2()
	{
		return m_object2;
	}
	//End CollisionRecord::Object2


    //=========================================================================
    //! @function    CollisionRecord::CollisionNormal
    //! @brief       Return the normal of the plane that the entity has collided with
    //!              
    //! @return      
    //=========================================================================
	const Math::Vector3D& CollisionRecord::CollisionNormal() const
	{
		return m_collisionNormal;
	}
	//End CollisionRecord::CollisionNormal


    //=========================================================================
    //! @function    CollisionRecord::Depth
    //! @brief       The depth at which object1 has penetrated the plane
    //!              
    //! @return      The depth at which object1 has penetrated the plane
    //=========================================================================
	Float CollisionRecord::Depth() const
	{
		return m_depth;
	}
	//End CollisionRecord::Depth


    //=========================================================================
    //! @function    CollisionRecord::operator <
    //! @brief		 
    //!              
    //! @param       rhs 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	bool CollisionRecord::operator < ( const CollisionRecord& rhs ) const
	{

	}
	//End CollisionRecord::operator <





}
//end namespace OidFX


#endif
//#ifndef OIDFX_COLLISIONMANAGER_H
