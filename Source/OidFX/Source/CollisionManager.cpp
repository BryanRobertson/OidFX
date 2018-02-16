//======================================================================================
//! @file         CollisionManager.cpp
//! @brief        Manager class to deal with pairs of colliding objects
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 14 September 2005
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
#include "OidFX/Scene.h"
#include "OidFX/SceneObject.h"
#include "OidFX/EntityNode.h"
#include "OidFX/CollisionManager.h"
#include "OidFX/NewtonWrapper.h"



using namespace OidFX;


//=========================================================================
//! @function    CollisionManager::CollisionManager
//! @brief       CollisionManager constructor
//!              
//! @param       scene [in]
//!              
//=========================================================================
CollisionManager::CollisionManager ( Scene& scene )
: m_scene(scene)
{
	m_world = boost::shared_ptr<Newton::World>( new Newton::World() );
}
//End CollisionManager::CollisionManager



//=========================================================================
//! @function    CollisionManager::AddCollider
//! @brief       Add an entity to the list of objects that will be checked
//!				 for collisions
//!              
//! @param       entityNode [in]
//!              
//=========================================================================
void CollisionManager::AddCollider ( EntityNode* entityNode )
{
	debug_assert ( entityNode, "entityNode should not be null!" );

	m_colliders.push_back( entityNode );
}
//End CollisionManager::AddCollider



//=========================================================================
//! @function    CollisionManager::RemoveCollider
//! @brief       Remove an entity from the list of objects that will be checked
//!				 for collisions
//!              
//! @param       entityNode [in] 
//!              
//=========================================================================
void CollisionManager::RemoveCollider ( EntityNode* entityNode )
{
	debug_assert ( entityNode, "entityNode should not be null!" );

	ColliderStore::iterator item = std::find<ColliderStore::iterator, EntityNode*>
												(m_colliders.begin(), m_colliders.end(), entityNode);

	debug_assert ( item != m_colliders.end(), "Item not in list!" );

	m_colliders.erase ( item );
}
//End CollisionManager::RemoveCollider



//=========================================================================
//! @function    CollisionManager::AddCollision
//! @brief       Add a collision to the list of collisions that have
//!              occured this frame
//!              
//! @param       collision [in] 
//!              
//=========================================================================
void CollisionManager::AddCollision ( const CollisionRecord& collision )
{
	m_collisions.push_back(collision);
}
//End CollisionManager::AddCollision



//=========================================================================
//! @function    CollisionManager::CheckCollisions
//! @brief       Check all colliders for collisions 
//!
//=========================================================================
void CollisionManager::CheckCollisions ( )
{
	debug_assert ( m_scene.Root(), "Scene graph is empty!" );

	//Clear the collision list
	ClearCollisions();

	//Check each collider against the scene for collisions
	for ( ColliderStore::const_iterator itr = m_colliders.begin();
		  itr != m_colliders.end();
		  ++itr )
	{

		SceneNode::NodeCollisionFlags flags;

		if ( (*itr)->IsFlagSet( EF_NOCOLLIDE ) )
		{
			continue;
		}

		if ( !(*itr)->IsFlagSet( EF_NOWORLDCOLLIDE ) )
		{
			flags[NODETYPE_WORLD] = true;
		}

		if ( !(*itr)->IsFlagSet( EF_NOENTITYCOLLIDE ) )
		{
			flags[NODETYPE_ENTITY] = true;
		}

		flags[NODETYPE_SCENEPARTITION] = true;


		m_scene.Root()->CheckCollisions( *itr, (*itr)->PreferredCollisionType(), flags, *this );
	}
		  
}
//End CollisionManager::CheckCollisions



//=========================================================================
//! @function    CollisionManager::ExecuteCollisionList
//! @brief       Execute the list of collisions
//!              
//=========================================================================
void CollisionManager::ExecuteCollisionList ( )
{
	IEntity* entity2 = 0;

	Math::Vector3D v0;
	Math::Vector3D v1;

	for ( CollisionRecordStore::iterator itr = m_collisions.begin();
		  itr != m_collisions.end();
		  ++itr )
	{
		
		EntityNode* entity1 = itr->Object1();
		SceneNode*  object2 = itr->Object2();

		if ( object2->NodeType() == NODETYPE_WORLD )
		{
			entity1->OnWorldCollide( itr->CollisionNormal(), itr->Depth() );
		}
		else if ( object2->NodeType() == NODETYPE_ENTITY )
		{
			//Get
			object2->QueryInterface ( NODEINTERFACE_IENTITY, reinterpret_cast<void**>(&entity2) );
			debug_assert ( entity2, "Node type has NODETYPE_ENTITY but is not an entity!" );

			v0 = entity1->GetVelocity();

			//HACK:
			//This cast is evil, and further demonstrates why the scene graph, and entity systems
			//need a complete redesign when I get time!!!
			//
			//Having to do stuff like this is generally a sign of a very shoddy design!
			entity1->OnEntityCollide( itr->CollisionNormal(), itr->Depth(), static_cast<EntityNode&>(*entity2), 
										static_cast<EntityNode*>(entity2)->GetVelocity() );

			entity2->OnEntityCollide( itr->CollisionNormal(), itr->Depth(), *entity1, v0 );
		}
	}
}
//End CollisionManager::ExecuteCollisionList



//=========================================================================
//! @function    CollisionManager::Collide
//! @brief       Checks two Collision objects for collisions
//!
//!	@param		 colliderA		 [in]	First object
//! @param		 colliderAMatrix [in]	Offset matrix of first object
//! @param		 colliderB		 [in]	Second object
//! @param		 colloderBMatrix [in]	Offset matrix of second object
//! @param		 maxCollisions	 [in]	Maximum number of contact points/normals/penetration depths to return
//! @param		 contacts		 [out]	Array of contact points
//! @param		 normals		 [out]	Array of contract normals
//! @param		 penetration	 [out]  Array of penetration depths
//=========================================================================
UInt CollisionManager::Collide ( const CollisionManager::CollisionVolume& colliderA, 
								 const Math::Matrix4x4& colliderAMatrix,
								 const CollisionManager::CollisionVolume& colliderB,
								 const Math::Matrix4x4& colliderBMatrix,
								 UInt maxCollisions,
								 CollisionManager::CollisionInfo& contacts,
								 CollisionManager::CollisionInfo& normals,
								 CollisionManager::PenetrationInfo& penetration )
{
	return m_world->Collide( colliderA, 
							 colliderAMatrix, 
							 colliderB, 
							 colliderBMatrix, 
							 maxCollisions,
							 contacts,
							 normals,
							 penetration );
}
//End CollisionManager::Collide



//=========================================================================
//! @function    CollisionManager::Collide
//! @brief       Checks a collision volume against a line for collision
//!              
//! @param       collider 
//! @param       line 
//!              
//! @return      Parametric value on the line where collision occurs
//=========================================================================
Float CollisionManager::Collide ( const CollisionManager::CollisionVolume& collider, 
								  const Math::ParametricLine3D& line )
{
	return m_world->Collide( collider, line );
}
//End CollisionManager::Collide



//=========================================================================
//! @function    CollisionManager::SceneRaycast
//! @brief       Checks a line against all collision volumes
//!              
//! @param       line 
//!              
//! @return      Parametric value on the line where the closest collision occurs
//=========================================================================
Float CollisionManager::SceneRaycast ( const Math::ParametricLine3D& line )
{
	return m_world->SceneRaycast( line );
}
//End CollisionManager::SceneRaycast



//=========================================================================
//! @function    CollisionManager::CreateSphere
//! @brief       Create a sphere collision volume
//!              
//! @param       extents		[in] Extents of the sphere
//! @param       offsetMatrix	[in] Offset of the sphere from the object
//!              
//! @return      A sphere collision volume with the specified attributes
//=========================================================================
CollisionManager::CollisionVolume CollisionManager::CreateSphere 
										( const Math::Vector3D& extents, const Math::Matrix4x4& offsetMatrix )
{

	return m_world->CreateSphere ( extents, offsetMatrix );

}
//End CollisionManager::CreateSphere


//=========================================================================
//! @function    CollisionManager::CreateBox
//! @brief       Create a box collision volume
//!              
//! @param       extents		[in] Extents of the box
//! @param       offsetMatrix	[in] Offset of the box from the object
//!              
//! @return      A box collision volume with the specified attributes
//=========================================================================
CollisionManager::CollisionVolume CollisionManager::CreateBox 
										( const Math::Vector3D& extents, const Math::Matrix4x4& offsetMatrix )
{

	return m_world->CreateBox ( extents, offsetMatrix );

}
//End CollisionManager::CreateBox


//=========================================================================
//! @function    CollisionManager::CreateTreeCollision 
//! @brief       Create a tree collision object, for optimised mesh collision
//!              
//! @param       triangles [in]
//!              
//! @return      A tree collision object
//=========================================================================
CollisionManager::CollisionVolume CollisionManager::CreateTreeCollision 
										( const Core::Vector<Math::Triangle>::Type& triangles )
{
	return m_world->CreateTreeCollision ( triangles );
}
//End CollisionManager::CreateTreeCollision 


//=========================================================================
//! @function    CollisionManager::ClearCollisions
//! @brief       Erase all collisions from the list, called by CheckCollisions
//!              
//=========================================================================
void CollisionManager::ClearCollisions ( )
{
	m_collisions.clear();
}
//End CollisionManager::ClearCollisions
