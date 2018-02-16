//======================================================================================
//! @file         SceneObject.h
//! @brief        Class representing a scene node which has a bounding box
//!
//!				  Note that I'm not happy with the implementation of the scene graph, and this
//!				  is all going to be scrapped later. The only reason I'm not scrapping it now,
//!				  is due to the time constraints I'm under. I just need to get something that works
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 16 July 2005
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
//======================================================================================

#ifndef OIDFX_SCENEOBJECT
#define OIDFX_SCENEOBJECT


#include "Math/BoundingBox3D.h"
#include "Math/BoundingSphere3D.h"
#include "OidFX/SceneNode.h"
#include "OidFX/CollisionManager.h"
#include "OidFX/Scene.h"


//namespace OidFX
namespace OidFX
{


	//!@class	SceneObject
	//!@brief	Class representing a scene node which has a bounding box
	//!
	//!	
	//!			Note that I'm not happy with the implementation of the scene graph, and this
	//!			is all going to be scrapped later. The only reason I'm not scrapping it now,
	//!			is due to the time constraints I'm under. I just need to get something that works
	class SceneObject : public SceneNode
	{
		public:

			SceneObject ( Scene& scene,
						  ENodeType nodeType,
						  const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
						  const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );

			virtual void Update( Math::MatrixStack& toWorldStack, 
								 Math::MatrixStack& fromWorldStack, 
								 Float timeElapsedInSeconds );

			//Fill visible object list
			void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );

			//Update position
			void UpdateBoundsPositionFromLocalTransform ( );
			void UpdateBoundsPositionFromConcatTransform ( );

			//Get bounding box
			const Math::AxisAlignedBoundingBox& BoundingBox() const		{ return m_boundingBox; }

			//Set bounding box
			inline void SetBoundingBox ( const Math::AxisAlignedBoundingBox& box );

			//Collisions
			virtual bool CollidesWith   ( EntityNode* entity,
										  ECollisionType collisionType,
										  Math::Vector3D& normal,
										  Float& depth );

			virtual void CheckCollisions ( EntityNode* entity, 
										   ECollisionType collisionType,
										   const NodeCollisionFlags& collisionFlags,
										   CollisionManager& collisionManager );

			inline const CollisionManager::CollisionVolume& GetCollisionVolume() const throw();

			virtual void QueryScene ( const Math::ParametricLine3D& ray, 
									   SceneQueryResult& result );

			virtual void QueryScene ( const Math::BoundingSphere3D& sphere,
									   EntityQueryResult& result );

		protected:


            //=========================================================================
            // Protected methods
            //=========================================================================
			virtual void ConcatenateTransformFromParent ( );


            //=========================================================================
            // Protected data
            //=========================================================================
			Math::AxisAlignedBoundingBox	m_boundingBox;

			//Collision related
			CollisionManager::CollisionVolume	m_collisionVolume;
		

	};
	//End class SceneObject



	//=========================================================================
    //! @function    SceneObject::GetCollisionVolume
    //! @brief       Return the collision volume of the object
    //!              
    //!              
    //! @return      The collision volume of the object
    //=========================================================================
	const CollisionManager::CollisionVolume& SceneObject::GetCollisionVolume() const
	{
		return m_collisionVolume;
	}
	//SceneObject::GetCollisionVolume



    //=========================================================================
    //! @function    SceneObject::SetBoundingBox
    //! @brief       Set the bounding box of the object
    //!              
    //! @param       box [in] New bounding volume
    //!              
    //=========================================================================
	void SceneObject::SetBoundingBox ( const Math::AxisAlignedBoundingBox& box )
	{
		m_boundingBox = box;

		m_collisionVolume = m_scene.GetCollisionManager().CreateSphere( Math::Vector3D(m_boundingBox.ExtentX(), 
																						m_boundingBox.ExtentY(),
																						m_boundingBox.ExtentZ() ) );
	}
	//End SceneObject::SetBoundingBox


}
//end namespace OidFX


#endif
//#ifndef OIDFX_SCENEOBJECT
