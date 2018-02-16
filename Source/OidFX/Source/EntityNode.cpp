//======================================================================================
//! @file         EntityNode.cpp
//! @brief        Scene node representing an entity in the game world
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 17 August 2005
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
#include "Math/Matrix4x4.h"
#include "Math/MatrixStack.h"
#include "Math/IntersectionTests.h"
#include "OidFX/Scene.h"
#include "OidFX/EntityNode.h"
#include "OidFX/GameApplication.h"
#include "OidFX/MeshManager.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/Constants.h"
#include "OidFX/EntityManager.h"


using namespace OidFX;



//=========================================================================
//! @function    EntityNode::EntityNode
//! @brief       EntityNode constructor
//!              
//!              
//! @param       scene		  [in] Reference to the scene of which this entity is part
//! @param		 name		  [in] Name of the entity
//! @param		 meshFileName [in] Filename of the mesh, if this is null or "", then
//!								   no mesh will be loaded
//! @param       toWorld	  [in] To world transformation
//! @param       fromWorld    [in] From world transformation
//!              
//=========================================================================
EntityNode::EntityNode ( Scene& scene,
						 const Char* name,
						 const Char* meshFileName,
						 const Math::Matrix4x4& toWorld, 
						 const Math::Matrix4x4& fromWorld )
:
   SceneObject(scene, NODETYPE_ENTITY, toWorld, fromWorld ),
   m_name(name), 
   m_health(100.0f), 
   m_deathTimer(0.0f),
   m_preferredCollisionType(COLLISIONTYPE_SPHERE),
   m_explosiveStrength(100.0f)
{

	//If there is a mesh filename, then load the mesh
	if ( ( meshFileName != 0 )
		&& ( meshFileName != "" ) )
	{
		SetMesh( scene.Application().GetMeshManager().AcquireMesh( meshFileName ) );
	}
}
//End EntityNode::EntityNode



//=========================================================================
//! @function    EntityNode::Spawn 
//! @brief       Spawn an entity into the game world
//!
//! @param		 spawnPoint [in] Position within the game world at which              
//!								 to spawn the entity
//=========================================================================
void EntityNode::Spawn ( const Math::Vector3D& spawnPoint)
{
	m_position = spawnPoint;

	//If the entity is to spawn on the ground, then cast a ray
	//through the scene, to find the proper height to spawn the entity at

	if ( false )// this is broken at the moment ( IsFlagSet(EF_SPAWNONGROUND) )
	{

		//Cast a ray through the terrain to get the terrain height
		Math::ParametricLine3D ray( Math::Vector3D(m_position.X(), 10000.0f, m_position.Z()), 
									Math::Vector3D(m_position.X(), -10000.0f, m_position.Z()));

		SceneQueryResult results;
		m_scene.QueryScene ( ray, true, results );

		if ( results.empty() )
		{
			std::cerr << __FUNCTION__ << ": Error, failed to spawn entity on ground!" << std::endl;
		}
		else
		{

			std::clog << __FUNCTION__ << ": ray intersects " << results.size() << " triangles" << std::endl;

			ray.PointOnLine( results[0], m_position );
			std::clog << __FUNCTION__ << ": Spawned entity on ground at position " << m_position 
					  << ". t on line = " << results[0] << std::endl;
		}
	}

	//


	//Initialise physics 
	m_velocity.Set ( 0.0f, 0.0f, 0.0f );
	m_acceleration.Set ( 0.0f, 0.0f, 0.0f );
	m_angularVelocity.Set(0.0f, 0.0f, 0.0f );
	m_angularAcceleration.Set(0.0f, 0.0f, 0.0f);

	m_orientation = Math::Quaternion(Math::Vector3D::XAxis, 0);

	m_health = 100.0f;

	SetFlag ( EF_SPAWNED );
	ClearFlag ( EF_DEAD );
	ClearFlag ( EF_DESPAWNPENDING );
	

	OnSpawn( spawnPoint );

	UpdatePhysics(0.0f);
}
//End EntityNode::Spawn 



//=========================================================================
//! @function    EntityNode::UpdatePhysics
//! @brief       Update position, velocity and acceleration
//!				 also simulate the effects of friction and gravity
//!              
//! @param       timeElapsedInSeconds [in] 
//!              
//! @return      
//! @throw       
//=========================================================================
void EntityNode::UpdatePhysics ( Float timeElapsedInSeconds )
{
	static Core::ConsoleFloat friction ( "phys_friction", 0.01f );
	static Core::ConsoleFloat gravity  ( "phys_gravity", 0.98f * meters  );

	if ( !IsFlagSet ( EF_ANTIGRAVITY ) )
	{
		//Simulate the effects of gravity
		m_acceleration += Math::Vector3D ( 0.0f, -gravity, 0.0f );
	}

	m_velocity += m_acceleration * timeElapsedInSeconds;

	m_velocity += -m_velocity * friction;

	m_position += m_velocity;

	//Update rotational velocity
	m_angularVelocity += m_angularAcceleration * timeElapsedInSeconds;
	m_angularVelocity += -m_angularVelocity * friction;

	Math::Quaternion rotation ( m_angularVelocity.Z(), m_angularVelocity.Y(), m_angularVelocity.X() );

	m_orientation *= rotation;
}
//End EntityNode::UpdatePhysics



//=========================================================================
//! @function    EntityNode::Update
//! @brief       Update the entity
//!              
//! @param       toWorldStack 
//! @param       fromWorldStack 
//! @param       timeElapsedInSeconds 
//!              
//! @return      
//! @throw       
//=========================================================================
void EntityNode::Update ( Math::MatrixStack& toWorldStack,
						 Math::MatrixStack& fromWorldStack,
						 Float timeElapsedInSeconds )
{

	if ( (IsFlagSet(EF_SPAWNED)) && (!IsFlagSet(EF_STATIC)) )
	{
		UpdatePhysics( timeElapsedInSeconds );

		m_orientation.Normalise();
	}

	m_objectToWorld = Math::Matrix4x4 ( m_orientation );
	m_objectToWorld.Translate ( m_position );

	m_objectFromWorld = Math::Matrix4x4 ( -m_orientation );
	m_objectFromWorld.Translate ( -m_position );

	SceneObject::Update( toWorldStack, fromWorldStack, timeElapsedInSeconds );

	OnThink ( timeElapsedInSeconds );

	m_acceleration.Set ( 0.0f, 0.0f, 0.0f );
	m_angularAcceleration.Set ( 0.0f, 0.0f, 0.0f );

	//Create a timer that despawns the entity shortly after death
	static Core::ConsoleFloat deathtimeout ( "deathtimeout", 10.0f );

	if ( IsFlagSet(EF_DEAD) )
	{
		m_deathTimer += timeElapsedInSeconds;

		if ( m_deathTimer > deathtimeout )
		{
			#ifdef DEBUG_BUILD
					std::clog << __FUNCTION__ ": Entity " << ID() << " has been despawned" << std::endl;
			#endif

			SetFlag(EF_DESPAWNPENDING);
		}
	}
	else
	{	
		m_deathTimer = 0.0f;
	}
}
//End EntityNode::Update



//=========================================================================
//! @function    EntityNode::FillVisibleObjectList
//! @brief       Add the entity to the list of visible objects if it is within the
//!				 camera's view frustum
//!              
//! @param       visibleObjectList [in]	
//! @param       camera			   [in]	
//!              
//=========================================================================
void EntityNode::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera ) 
{

	//Call the SceneNode version of this method to add all children, regardless
	//of whether this object is visible or not
	SceneNode::FillVisibleObjectList ( visibleObjectList, camera );

	if ( (IsFlagSet(EF_SPAWNED) && (!IsFlagSet(EF_NODRAW)) && m_mesh ) )
	{

		//Always draw the player
		if ( (Math::Intersects ( m_boundingBox, camera.ViewFrustum())) 
			|| (IsFlagSet(EF_PLAYER)) )
		{
			//If we got here the object is in the camera's view frustum, so add it to the visible list
			visibleObjectList.AddObject ( *this );		
		}
	}

}
//End EntityNode::FillVisibleObjectList



//=========================================================================
//! @function    EntityNode::OnSpawn ( Math::Vector3D spawnPoint )
//! @brief		 
//!
//! @param		 spawnPoint [in] Location at which to spawn the entity
//!              
//=========================================================================
void EntityNode::OnSpawn ( const Math::Vector3D& spawnPoint )
{
}
//End EntityNode::OnSpawn



//=========================================================================
//! @function    EntityNode::OnThink
//! @brief		 Called to update the entity's AI every frame
//!
//! @param		 timeElapsed [in]
//!              
//=========================================================================
void EntityNode::OnThink ( Float timeElapsed )
{
}
//End EntityNode::OnThink



//=========================================================================
//! @function    EntityNode::OnTouch
//! @brief       Called when the entity touches a player
//!              
//!              
//=========================================================================
void EntityNode::OnTouch ( )
{
}
//End EntityNode::OnTouch



//=========================================================================
//! @function    EntityNode::OnWorldCollide
//! @brief       Called when the entity collides with world geometry
//!              
//!              
//! @param       collisionNormal [in] Normal of collision surface
//! @param		 depth			 [in] Depth that the object has penetrated the surface
//=========================================================================
void EntityNode::OnWorldCollide (  const Math::Vector3D& collisionNormal, Float depth  )
{
}
//End EntityNode::OnWorldCollide


//=========================================================================
//! @function    EntityNode::OnEntityCollide
//! @brief       Called when the entity collides with another entity
//!              
//=========================================================================
void EntityNode::OnEntityCollide ( const Math::Vector3D& collisionNormal, Float depth, 
								   EntityNode& entity, const Math::Vector3D& entityVelocity )
{
}
//End EntityNode::OnEntityCollide


//=========================================================================
//! @function    EntityNode::OnDeath ( )
//! @brief       Called when the entity dies
//!              
//=========================================================================
void EntityNode::OnDeath ( )
{
	SetFlag( EF_NODRAW );

	if ( IsFlagSet(EF_FLAMMABLE) )
	{
		Ignite();
	}

	if ( IsFlagSet(EF_EXPLOSIVE) )
	{
		Explode();
	}
}
//End EntityNode::OnDeath


//=========================================================================
//! @function    EntityNode::QueueForRendering
//! @brief       Add the node to the render queue for rendering
//!              
//!              
//! @param       queue [in] Render queue to add the node to
//!              
//=========================================================================
void EntityNode::QueueForRendering ( Renderer::RenderQueue& queue )
{

	//Queue the mesh for rendering
	m_mesh->QueueForRendering ( queue, m_concatObjectToWorld, m_lodLevel );

}
//End EntityNode::QueueForRendering



//=========================================================================
//! @function    EntityNode::Render
//! @brief       Render the entity node
//!              
//! @param       renderer [in]
//!              
//=========================================================================
void EntityNode::Render ( Renderer::IRenderer& renderer )
{
	//Rendering is handled by the mesh class
}
//End EntityNode::Render


//=========================================================================
//! @function    EntityNode::Explode
//! @brief       Make the entity explode.
//!              
//!              The entity will explode by creating an explosion object
//!              which does all the work
//=========================================================================
void EntityNode::Explode ( )
{
	SetFlag(EF_DESPAWNPENDING);

	Math::Vector3D position = BoundingBox().GetCentre();

	boost::shared_ptr<EntityNode> explosion = m_scene.GetEntityManager().SpawnEntity( "Explosion", position );
	//explosion->SetVelocity( GetVelocity() );
	explosion->SetExplosiveStrength( GetExplosiveStrength() );

	if ( IsFlagSet(EF_ALLY) )
	{
		explosion->SetFlag(EF_ALLY);
	}
	else if ( IsFlagSet(EF_ENEMY) )
	{
		explosion->SetFlag(EF_ENEMY);
	}
}
//End EntityNode::Explode


//=========================================================================
//! @function    EntityNode::Ignite
//! @brief       Makes the entity burst into flames
//!              
//!				 In future, this will attach a fire particle effect to the entity
//=========================================================================
void EntityNode::Ignite ( )
{

}
//End EntityNode::Ignite


//=========================================================================
//! @function    EntityNode::CanCollideWith
//! @brief       Indicates whether or not an entity can collide with another entity
//=========================================================================
bool EntityNode::CanCollideWith ( const EntityNode* entity ) const
{
	if ( (IsFlagSet(EF_NOENTITYCOLLIDE)) 
		|| (IsFlagSet(EF_NOCOLLIDE))
		|| (ID() == entity->ID())
		|| (IsFlagSet(EF_DESPAWNPENDING)) )
	{
		return false;
	}
	else
	{
		return true;
	}

}
//End EntityNode::CanCollideWith


//=========================================================================
//! @function    EntityNode::QueryScene
//! @brief       Query the scene for entities inside a bounding sphere
//!              
//! @param       sphere [in]
//! @param       result [in]
//!              
//=========================================================================
void EntityNode::QueryScene ( const Math::BoundingSphere3D& sphere, EntityQueryResult& result )
{

	if ( IsFlagSet(EF_DEAD) || IsFlagSet(EF_DESPAWNPENDING) )
	{
		return;
	}

	if ( Math::Intersects(sphere, Math::BoundingSphere3D(m_boundingBox)) )
	{
		result.push_back(this);
	}
}
//End EntityNode::QueryScene




//=========================================================================
//! @function    EntityNode::RegisterDeathHandler
//! @brief       Register an object to be notified when this entity dies
//!              
//!				 Note that the event connection will be severed when this
//!				 entity is killed
//!              
//! @param       handler [in]	Object to be notified of this entities death
//!              
//! @return      A connection to the death event of this entity
//=========================================================================
Core::EventConnection EntityNode::RegisterDeathHandler ( IEntityDeathSensitive& handler )
{
	return m_deathEvent.Connect( handler );
}
//End EntityNode::RegisterDeathHandler