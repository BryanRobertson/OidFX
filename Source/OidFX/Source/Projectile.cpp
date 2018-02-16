//======================================================================================
//! @file         Projectile.cpp
//! @brief        Class representing a projectile, such as a missle
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 06 September 2005
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
#include "OidFX/Constants.h"
#include "OidFX/EntityNode.h"
#include "OidFX/Projectile.h"


using namespace OidFX;



//=========================================================================
//! @function    Projectile::Projectile
//! @brief       
//!              
//! @param       scene		[in]
//! @param       name		[in]
//! @param       toWorld	[in]
//! @param       fromWorld	[in]
//!              
//=========================================================================
Projectile::Projectile ( Scene& scene, 
						 const Char* name,
						 const Math::Matrix4x4& toWorld,
						 const Math::Matrix4x4& fromWorld )
: EntityNode( scene, name, "", toWorld, fromWorld ),
  m_projectileState(PS_LAUNCHSTAGE),
  m_timeOut(0.0f),
  m_target(0)
{

	SetFlag( PF_MISSILE );

	SetFlag ( EF_ANTIGRAVITY );
	SetFlag ( EF_EXPLOSIVE );
	SetFlag ( EF_PROJECTILE );
	SetFlag ( EF_NOEXPLOSIONKICKBACK );

	m_preferredCollisionType = COLLISIONTYPE_VELOCITYRAY;

}
//End Projectile::Projectile



//=========================================================================
//! @function    Projectile::Spawn
//! @brief       Spawn a projectile
//!              
//! @param		 spawnPoint [in]	Position at which to spawn the projectile
//! @param       ownerID	[in]	ID of the owner
//! @param       mesh		[in]	Mesh to render the projectile with
//!              
//=========================================================================
void Projectile::Spawn ( const Math::Vector3D& spawnPoint, UInt ownerID, HMesh& mesh )
{
	ClearTarget();
	ClearFlag ( EF_ANTIGRAVITY );
	ClearFlag ( EF_NODRAW );
	ClearFlag ( EF_NOCOLLIDE );

	SetState ( PS_LAUNCHSTAGE );

	//Projectile can't collide with entities until it fires its rockets
	SetFlag  ( EF_NOENTITYCOLLIDE  );
	
	m_ownerID = ownerID;

	Core::ConsoleFloat missile_timetolive ( "missile_timetolive", 3.0f );
	Core::ConsoleFloat missile_strength   ( "missile_strength", 500.0f );

	m_timeOut = missile_timetolive;
	m_explosiveStrength = missile_strength;
	m_timeElapsedSinceLaunch = 0.0f;

	SetMesh(mesh);

	EntityNode::Spawn ( spawnPoint );

}
//End Projectile::Spawn



//=========================================================================
//! @function    Projectile::Update
//! @brief       
//!              
//! @param       toWorldStack			[in]
//! @param       fromWorldStack			[in]
//! @param       timeElapsedInSeconds	[in]
//!              
//=========================================================================
void Projectile::Update ( Math::MatrixStack& toWorldStack,
						  Math::MatrixStack& fromWorldStack,
						  Float timeElapsedInSeconds )
{

	//Clear target if it's dead or about to despawn
	if ( (GetTarget()) && 
		 ( (GetTarget()->IsFlagSet(EF_DEAD)) || (GetTarget()->IsFlagSet(EF_DESPAWNPENDING)) ) )
	{
		ClearTarget();
	}

	//Time between missile being launched and firing its rockets
	Core::ConsoleFloat missile_rocket_delay ( "missile_rocket_delay", 1.0f );
	
	if ( IsFlagSet(EF_SPAWNED) && (!IsFlagSet(EF_DEAD)))
	{

		if ( GetTarget() )
		{
			//Make the missile turn to face its target
			static Math::Vector3D v;
			v = GetTarget()->BoundingBox().GetCentre() - BoundingBox().GetCentre();
			v.Normalise();

			Float accelRight = Math::Vector3D::DotProduct( v, Right() );
			Float accelUp   = Math::Vector3D::DotProduct( v, Up() );

			m_angularAcceleration = Math::Vector3D( Math::DegreesToRadians(accelUp * 20.0f), 
													-Math::DegreesToRadians(accelRight * 20.0f),
														0.0f );
		}

		switch ( GetState() )
		{
			case PS_LAUNCHSTAGE:
				
				m_timeElapsedSinceLaunch += timeElapsedInSeconds;

				if ( m_timeElapsedSinceLaunch >= missile_rocket_delay )
				{
					SetState(PS_TARGETING);
					ClearFlag( EF_NOENTITYCOLLIDE  );
					SetFlag ( EF_ANTIGRAVITY );
					//In future we will attach a particle system at this point
				}
		
				break;

			case PS_TARGETING:
			{
				Math::Vector3D forward = -Forward();
				forward.Normalise();

				//Accelerate 10 meters per second
				m_acceleration += forward * 10.0f * meters;


				//Make sure the rocket times out after a set period of time
				m_timeOut -= timeElapsedInSeconds;

				if ( m_timeOut <= 0.0f )
				{
					Kill();
				}
			}
			break;
		}
	}

	EntityNode::Update( toWorldStack, fromWorldStack, timeElapsedInSeconds );

}
//End Projectile::Update



//=========================================================================
//! @function    Projectile::OnSpawn
//! @brief       Event handler for spawn event
//!              
//! @param       spawnPoint [in]
//!              
//=========================================================================
void Projectile::OnSpawn ( const Math::Vector3D& spawnPoint )
{
	
}
//End Projectile::OnSpawn


//=========================================================================
//! @function    Projectile::OnThink
//! @brief       Handle for think event
//!              
//! @param       timeElapsed [in]
//!              
//=========================================================================
void Projectile::OnThink ( Float timeElapsed )
{
}
//End Projectile::OnThink



//=========================================================================
//! @function    Projectile::OnTouch
//! @brief       Reaction to touching the player
//!              
//=========================================================================
void Projectile::OnTouch ( )
{
}
//End Projectile::OnTouch



//=========================================================================
//! @function    Projectile::OnWorldCollide
//! @brief       Event handler for colliding with the world
//!              
//! @param       collisionNormal [in] Normal of collision surface
//! @param		 depth			 [in] Depth that the object has penetrated the surface
//!              
//=========================================================================
void Projectile::OnWorldCollide (  const Math::Vector3D& collisionNormal, Float depth )
{
	Kill();
}
//End Projectile::OnWorldCollide


//=========================================================================
//! @function    Projectile::OnEntityCollide
//! @brief       Event handler for colliding with an entity
//!              
//! @param       entity [in]
//!              
//=========================================================================
void Projectile::OnEntityCollide (  const Math::Vector3D& collisionNormal, Float depth, 
									EntityNode& entity, const Math::Vector3D& entityVelocity )
{
 	Kill();

	entity.Hurt( 50.0f );
}
//End Projectile::OnEntityCollide


//=========================================================================
//! @function    Projectile::OnDeath
//! @brief       Event handler for projectile death
//!              
//=========================================================================
void Projectile::OnDeath ( )
{
	SetFlag ( EF_NODRAW );
	SetFlag ( EF_NOCOLLIDE );

	Explode();
}
//End Projectile::OnDeath



//=========================================================================
//! @function    Projectile::CanCollideWith
//! @brief       Indicates whether or not a projectile can collide with an entity
//!
//! @param		 entity [in] Entity to check
//!
//! @return		 true if the entity can collide with the projectile, false otherwise              
//=========================================================================
bool Projectile::CanCollideWith( const OidFX::EntityNode* entity ) const
{

	if ( (entity->ID() == m_ownerID) )
	{
		return false;
	}

	return EntityNode::CanCollideWith( entity );
}
//End Projectile::CanCollideWith
