//======================================================================================
//! @file         MissileLauncher.cpp
//! @brief        Class for an Entity which can launch projectiles.
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
#include "OidFX/Scene.h"
#include "OidFX/EntityNode.h"
#include "OidFX/TargetingComputer.h"
#include "OidFX/MissileLauncher.h"
#include "OidFX/ProjectileManager.h"



using namespace OidFX;



//=========================================================================
//! @function    MissileLauncher::MissileLauncher
//! @brief       MissileLauncher constructor
//!              
//! @param       scene				[in] Scene
//! @param       targetingComputer	[in] Targeting computer to get targets from
//! @param		 meshFileName		[in] filename of the mesh used to render the missile
//!              
//=========================================================================
MissileLauncher::MissileLauncher ( Scene& scene, 
								   TargetingComputer& targetingComputer,
								   const Char* meshFileName )
: EntityNode(scene, "Launcher", meshFileName),
  m_targetingComputer(targetingComputer),
  m_ammunition(100),
  m_reloadTime(1.0f),
  m_timeElapsedSinceLastFired(0.0f),
  m_launcherState( LS_READY )
{

	SetFlag ( EF_STATIC );
	SetFlag ( EF_ANTIGRAVITY );
	SetFlag ( EF_NODRAW );
	SetFlag ( EF_NOCOLLIDE );
	SetFlag ( EF_EXPLOSIVE );
	SetFlag ( EF_FLAMMABLE );
	SetFlag ( EF_NOEXPLOSIONKICKBACK );
	SetFlag ( EF_INVINCIBLE );
}
//End MissileLauncher::MissileLauncher



//=========================================================================
//! @function    MissileLauncher::Update
//! @brief       Update the missile launcher
//!              
//! @param       toWorldStack			[in]	
//! @param       fromWorldStack			[in]	
//! @param       timeElapsedInSeconds	[in]	
//!              
//=========================================================================
void MissileLauncher::Update ( Math::MatrixStack& toWorldStack, 
							   Math::MatrixStack& fromWorldStack, 
							   Float timeElapsedInSeconds )
{

	// HACK Fix broken scene graph implementation. 
	//
	//		This is yet another temporary fix that will not be needed, once I find time
	//		to redesign the scene graph.
	EntityNode* entity = reinterpret_cast<EntityNode*>( m_parent );

	m_objectToWorld.Identity();
	m_objectToWorld.Translate( m_position * entity->GetOrientation() );

	//
	EntityNode::Update( toWorldStack, fromWorldStack, timeElapsedInSeconds );


	//Update the launcher state
	if ( LS_RELOADING == m_launcherState )
	{
		m_timeElapsedSinceLastFired += timeElapsedInSeconds;

		if ( m_timeElapsedSinceLastFired > m_reloadTime )
		{
			m_timeElapsedSinceLastFired = 0.0f;
			m_launcherState = LS_READY;
		}
	}



}
//End MissileLauncher::Update



//=========================================================================
//! @function    MissileLauncher::LaunchMissile
//! @brief       Launches a missile if possible
//!              
//! @return      
//! @throw       
//=========================================================================
bool MissileLauncher::LaunchMissile ( )
{

	debug_assert ( m_parent, "Missile launcher must have a parent!" );

	//Can't fire a missile if we're dead, or not spawned,
	if (   (IsFlagSet(EF_DEAD)) 
		|| (!IsFlagSet(EF_SPAWNED))  )
	{
		return false;
	}

	//Can't fire if we have no ammo
	if ((!IsFlagSet(MF_INFINITEAMMO) && (0 == GetAmmunition())))
	{
		return false;
	}

	//Can't fire a missile if we're reloading
	if ( m_launcherState != LS_READY )
	{
		return false;
	}

	// HACK
	//This is evil, and further shows the need for a redesign when time permits
	EntityNode* parent = reinterpret_cast<EntityNode*>( m_parent );

	Math::Vector3D position = GetWorldSpacePosition();

	//If we got this far, then we really should fire a missile
	ProjectilePtr projectile = m_scene.GetProjectileManager().SpawnProjectile 
											( position, parent->ID(), GetMesh() );

	//No projectiles left
	if ( !projectile )
	{
		return false;
	}

	projectile->SetOrientation( parent->GetOrientation() );

	//Set friend or foe flag
	if ( parent->IsFlagSet(EF_ENEMY) )
	{
		projectile->SetFlag(EF_ENEMY);
	}
	else if ( parent->IsFlagSet(EF_ALLY) || parent->IsFlagSet(EF_PLAYER) )
	{
		projectile->SetFlag(EF_ALLY);
	}

	//Get the forward vector of the missile launcher
	Math::Vector3D forward = Forward();
	forward.Normalise();

	Core::ConsoleFloat missile_escape_velocity ( "missile_escape_velocity", 30.0f );
	Core::ConsoleFloat missile_parent_velocity ( "missile_parent_velocity", 1.0f );

	//Set the projectile's velocity to the parents velocity plus a little kick in the forward
	//direction
	projectile->SetVelocity( (parent->GetVelocity() * missile_parent_velocity)
								+ (-forward * missile_escape_velocity) );

	projectile->SetTarget( m_targetingComputer.GetCurrentTarget() );

	m_launcherState = LS_RELOADING;


	return true;
}