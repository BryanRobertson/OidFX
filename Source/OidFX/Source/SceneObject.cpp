//======================================================================================
//! @file         SceneObject.cpp
//! @brief        Class representing a scene node which has a bounding box
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 17 July 2005
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

#include "Core/Core.h"
#include "Math/MatrixStack.h"
#include "Math/ParametricLine3D.h"
#include "Math/IntersectionTests.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/SceneNode.h"
#include "OidFX/Camera.h"
#include "OidFX/Scene.h"
#include "OidFX/SceneObject.h"
#include "OidFX/CollisionManager.h"
#include "OidFX/EntityNode.h"


using namespace OidFX;



//=========================================================================
//! @function    SceneObject::SceneObject
//! @brief       
//!            
//! @param       scene		[in]
//! @param		 nodeType	[in] 
//! @param       toWorld	[in]
//! @param       fromWorld	[in]
//!              
//========================================================================
SceneObject::SceneObject ( Scene& scene, 
						  ENodeType nodeType,
						  const Math::Matrix4x4& toWorld, 
						  const Math::Matrix4x4& fromWorld
						  )
: SceneNode(scene, nodeType, toWorld, fromWorld )
{
	UpdateBoundsPositionFromLocalTransform();
}
//End SceneObject::SceneObject




//=========================================================================
//! @function    SceneObject::Update
//! @brief       Update a scene object, updating its bounding box if it has moved
//!              
//!              
//! @param       toWorldStack 
//! @param       fromWorldStack 
//! @param       timeElapsedInSeconds 
//!              
//=========================================================================
void SceneObject::Update ( Math::MatrixStack& toWorldStack, Math::MatrixStack& fromWorldStack, Float timeElapsedInSeconds )
{

	//Call the base class SceneNode::Update, to do the default update
	SceneNode::Update( toWorldStack, fromWorldStack, timeElapsedInSeconds );

	UpdateBoundsPositionFromConcatTransform();

}
//End SceneObject::Update



//=========================================================================
//! @function    SceneObject::FillVisibleObjectList
//! @brief       Add this object to the visible object list if it is visible
//!              
//! @param       visibleObjectList [in] List of visible objects to add this object to
//! @param       camera			   [in] Camera to test visibility with
//!              
//=========================================================================
void SceneObject::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera )
{
	//Call the base class FillVisibleObjectList to add all children
	SceneNode::FillVisibleObjectList ( visibleObjectList, camera );

	if ( !Math::Intersects ( m_boundingBox, camera.ViewFrustum() ) )
	{
		return;
	}

	//If we got here the object is in the camera's view frustum, so add it to the visible list
	visibleObjectList.AddObject ( *this );

}
//End SceneObject::FillVisibleObjectList



//=========================================================================
//! @function    SceneObject::UpdateBoundsPositionFromLocalTransform
//! @brief       Update the scene object position from its local transform
//!              matrix
//!              
//=========================================================================
void SceneObject::UpdateBoundsPositionFromLocalTransform ( )
{
	//Multiply the object's position by its concatenated world matrix
	Math::Vector3D position ( 0, 0, 0 );
	position *= m_objectToWorld;

	m_boundingBox.SetPosition ( position );
}
//End SceneObject::UpdateBoundsPositionFromLocalTransform



//=========================================================================
//! @function    SceneObject::UpdateBoundsPositionFromConcatTransform
//! @brief       Update the scene object position from its concatenated transform
//!              
//!              
//! @return      
//! @throw       
//=========================================================================
void SceneObject::UpdateBoundsPositionFromConcatTransform ( )
{
	//Multiply the object's position by its concatenated world matrix
	Math::Vector3D position ( 0, 0, 0 );
	position *= m_concatObjectToWorld;

	m_boundingBox.SetPosition ( position );
}
//End SceneObject::UpdateBoundsPositionFromWorldTransform



//=========================================================================
//! @function    SceneObject::ConcatenateTransformFromParent
//! @brief       Concatenate the transforms from the parent node,
//!              and update the node bounding box position
//! @return      
//! @throw       
//=========================================================================
void SceneObject::ConcatenateTransformFromParent ( )
{
	//First call the base class version
	SceneNode::ConcatenateTransformFromParent ();

	//Then update the bounds from the concatenated transform
	UpdateBoundsPositionFromConcatTransform();
}
//End SceneObject::ConcatenateTransformFromParent




//=========================================================================
//! @function    SceneObject::CollidesWith
//! @brief       Indicates whether or not an entity collides with an object
//!              
//!              
//! @param       entity			[in]	Entity to check collision against
//! @param       collisionType	[in]	Type of collision to check
//! @param       normal			[out]	Normal of collision
//! @param       depth			[out]	Depth of collision
//!              
//! @return      
//! @throw       
//=========================================================================
bool SceneObject::CollidesWith   (  EntityNode* entity,
									ECollisionType collisionType,
									Math::Vector3D& normal,
									Float& depth )
{

	if ( ID() != entity->ID() )
	{

		if ( Math::Intersects( m_boundingBox, entity->BoundingBox() ) )
		{

			if ( (NodeType() != NODETYPE_SCENEPARTITION ) 
					&& (!GetCollisionVolume().IsNull()) && (!entity->GetCollisionVolume().IsNull()) )
			{
				
				CollisionManager::CollisionInfo contacts;
				CollisionManager::CollisionInfo normals;
				CollisionManager::PenetrationInfo penetration;

				if ( m_scene.GetCollisionManager(). CollisionManager::Collide ( GetCollisionVolume(),
																				ConcatObjectToWorld(),
																				entity->GetCollisionVolume(),
																				entity->ConcatObjectToWorld(),
																				1,
																				contacts,
																				normals,
																				penetration ) )
				{
					normal = normals[0];
					depth = penetration[0];

					return true;
				}

			}
			else
			{
				return true;
			}

		}
	
	}

	return false;
}
//End SceneObject::CollidesWith



//=========================================================================
//! @function    SceneObject::CheckCollisions
//! @brief       Check to see if a scene object collides with this one
//!              
//! @param       entity				[in]
//! @param       collisionType		[in]
//! @param       collisionFlags		[in]
//! @param       collisionManager	[in]
//!              
//=========================================================================
void SceneObject::CheckCollisions ( EntityNode* entity, 
									ECollisionType collisionType,
									const NodeCollisionFlags& collisionFlags,
									CollisionManager& collisionManager )
{

	debug_assert ( entity, "Entity should not be NULL!" );

	// HACK
	//This is evil, the scene graph needs to be redesigned when I find time
	if ( (NodeType() == NODETYPE_ENTITY) )
	{
		if (( (!CanCollideWith(entity)) 
		|| (!entity->CanCollideWith(static_cast<EntityNode*>(this)) ) ) )
		{
			return;
		}
	}

	//
	Math::Vector3D normal;
	Float		   depth = 0.0f;

	if ( CollidesWith( entity, collisionType, normal, depth ) )
	{
		if ( (NodeType() == NODETYPE_WORLD) || (NodeType() == NODETYPE_ENTITY) )
		{
			collisionManager.AddCollision( CollisionRecord(entity, this, normal, depth) );
		}

		//Check collisions for child nodes
		SceneNode::CheckCollisions ( entity,
									 collisionType,
									 collisionFlags,
									 collisionManager );
	}

}
//End SceneObject::CheckCollisions



//=========================================================================
//! @function    SceneObject::QueryScene
//! @brief       Checks to see if the ray intersects the node's bounding box,
//!				 and if it does, then forwards the query on to all children              
//!
//! @param       ray	[in]	Ray to check scene object against
//!
//! @param              
//=========================================================================
void SceneObject::QueryScene ( const Math::ParametricLine3D& ray, SceneQueryResult& result )
{
	Float t = 0.0f;

	if ( Math::Intersects(ray, m_boundingBox, t) != Math::NoIntersect )
	{
		SceneNode::QueryScene( ray, result );
	}
}
//End SceneObject::QueryScene



//=========================================================================
//! @function    SceneObject::QueryScene
//! @brief       Find all entities inside a bounding sphere
//!              
//! @param       sphere [in]
//! @param       result [in]
//!              
//=========================================================================
void SceneObject::QueryScene ( const Math::BoundingSphere3D& sphere, EntityQueryResult& result )
{
	//If the sphere intersects a sphere that bounds the 
	if ( Math::Intersects(sphere, Math::BoundingSphere3D(m_boundingBox)) )
	{
		SceneNode::QueryScene( sphere, result );
	}
}
//End SceneObject::QueryScene

