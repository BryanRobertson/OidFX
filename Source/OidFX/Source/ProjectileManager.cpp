//======================================================================================
//! @file         ProjectileManager.cpp
//! @brief        Manager class for projectiles
//!               
//!				  Manages a store of spawned and unspawned projectiles
//!				  allowing projectiles to be reused, so that new projectiles
//!				  can be launched without having to create
//!				  a new object on the heap
//! 
//! @author       Bryan Robertson
//! @date         Monday, 05 September 2005
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
#include "OidFX/ProjectileManager.h"
#include "OidFX/Projectile.h"
#include "OidFX/CollisionManager.h"



using namespace OidFX;



//=========================================================================
//! @function    ProjectileManager::ProjectileManager
//! @brief       ProjectileManager constructor
//!              
//! @param       scene			[in] Reference to the scene
//! @param       maxProjectiles [in] Maximum number of projectiles that can
//!									 exist at any one time
//!              
//=========================================================================
ProjectileManager::ProjectileManager ( Scene& scene, UInt maxProjectiles, CollisionManager&	collisionManager )
: m_maxProjectiles(maxProjectiles), 
  m_scene(scene), 
  m_collisionManager(collisionManager)
{
	//Populate the unspawned projectile list
	Populate();
}
//End ProjectileManager::ProjectileManager



//=========================================================================
//! @function    ProjectileManager::Populate
//! @brief       Populate the unspawned projectile list with projectiles
//=========================================================================
void ProjectileManager::Populate ()
{
	Core::PooledStringStream name;
	
	for ( UInt i=0; i < m_maxProjectiles; ++i )
	{
		//Clear out the string
		name.str("");
		name << "Projectile " << i;

		m_unspawnedProjectiles.push_back ( ProjectilePtr(new Projectile( m_scene, name.str().c_str())) );
	}

}
//End ProjectileManager::Populate



//=========================================================================
//! @function    ProjectileManager::Update
//! @brief       Removes any unspawned projectiles from the spawned projectile list
//!              
//=========================================================================
void ProjectileManager::Update ( )
{

	iterator itr = m_spawnedProjectiles.begin();

	while ( itr != m_spawnedProjectiles.end() )
	{
		if ( (*itr)->IsFlagSet( EF_DESPAWNPENDING ) )
		{
			(*itr)->Despawn();
		}

		if ( !(*itr)->IsFlagSet( EF_SPAWNED ) )
		{
			//Get the iterator after itr
			iterator temp = itr;
			++temp;

			//Move itr from the spawned projectile list to the unspawned projectile list
			Core::SpliceOntoEnd ( itr, m_spawnedProjectiles, m_unspawnedProjectiles );

			//Remove the projectile from the collision list
			m_collisionManager.RemoveCollider( itr->get() );

			//Set itr to temp, as the item referenced by itr is in another list now
			itr = temp;
		}
		else
		{
			++itr;
		}
	}	

}
//End ProjectileManager::Update



//=========================================================================
//! @function    ProjectileManager::SpawnProjectile
//! @brief       Spawn a projectile
//!
//!				 Gets a projectile from the unspawned projectile list
//!				 spawns it, and adds it to the spawned projectile list
//!				 
//!              
//! @param		 spawnPoint [in] Position at which to spawn the projectile
//! @param       ownerID	[in] Integer ID of Entity that owns the projectile
//! @param       mesh		[in] Mesh used to render the projectile
//!              
//! @return		 If there are no free projectiles left, then a null pointer will
//!				 be returned, otherwise a pointer to the projectile is returned
//=========================================================================
ProjectilePtr ProjectileManager::SpawnProjectile (	const Math::Vector3D& spawnPoint,
													UInt ownerID,
													HMesh& mesh )
{
	//If there are no unspawned projectiles left
	if ( m_unspawnedProjectiles.empty() )
	{
		std::cerr << __FUNCTION__ ": No unspawned projectiles left!" << std::endl;
		return ProjectilePtr();
	}
	
	//Get an entity from the spawned projectiles list
	iterator itr = m_unspawnedProjectiles.begin();

	//Spawn the entity
	(*itr)->Spawn ( spawnPoint, ownerID, mesh );

	//Add the entity to the collision list
	m_collisionManager.AddCollider( itr->get() );

	//Add the entity to the scene graph
	m_scene.Root()->AddChild( *itr );

	//Move the projectile to the spawned list
	Core::SpliceOntoEnd ( itr, m_unspawnedProjectiles, m_spawnedProjectiles );

	return *itr;
}
//End ProjectileManager::SpawnProjectile



//=========================================================================
//! @function    ProjectileManager::DestroyAll
//! @brief       Destroy all projectiles, moving them all into the unspawned list
//!              
//=========================================================================
void ProjectileManager::DestroyAll ( )
{
	for ( iterator itr = m_spawnedProjectiles.begin();
		  itr != m_spawnedProjectiles.end();
		  ++itr )
	{

		//Despawn the entity
		(*itr)->Despawn();

		//Move the projectile to the spawned list
		Core::SpliceOntoEnd ( itr, m_spawnedProjectiles, m_unspawnedProjectiles );


	}
}
//End ProjectileManager::DestroyAll