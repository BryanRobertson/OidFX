//======================================================================================
//! @file         EntityManager.cpp
//! @brief        Class to manage the creation, storage, and destruction of entities
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 15 September 2005
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
#include "OidFX/SceneNode.h"
#include "OidFX/EntityNode.h"
#include "OidFX/EntityManager.h"
#include "OidFX/EntityFactory.h"
#include "OidFX/EntityCreator.h"
#include "OidFX/CollisionManager.h"
#include "OidFX/Scene.h"


using namespace OidFX;



//=========================================================================
//! @function    EntityManager::EntityManager
//! @brief       EntityManager constructor
//!              
//! @param       scene			  [in]
//! @param		 collisionManager [in]
//!              
//=========================================================================
EntityManager::EntityManager ( Scene& scene, CollisionManager& collisionManager )
: m_scene(scene), m_collisionManager(collisionManager)
{
	m_entityFactory = boost::shared_ptr<EntityFactory>( new EntityFactory(*this, scene) );
}
//End EntityManager::EntityManager



//=========================================================================
//! @function    EntityManager::RegisterType
//! @brief       Register an entity creator with the entity factory
//!              
//!              @see EntityFactory::RegisterType
//!              
//! @param       creator [in] Creator object 
//!              
//! @return      A hash value which can be used to create new entities
//!				 of the type created by creator
//=========================================================================
UInt EntityManager::RegisterType ( boost::shared_ptr<IEntityCreator> creator )
{
	return m_entityFactory->RegisterType( creator );
}
//End EntityManager::RegisterEntityType



//=========================================================================
//! @function    EntityManager::SpawnEntity
//! @brief       Spawns a new entity of the specified type, at the position specified
//!              
//!				 If there are any unspawned	entities of the same type, then the existing
//!				 entity will be spawned, and a pointer to the existing object returned.
//!				 Otherwise, a new entity will be created and spawned, and a pointer to the new
//!				 object returned
//!
//! @param       type		[in] Entity type name
//!
//! @param       position	[in] Position in the world at which to spawn the entity
//!              
//! @return      A pointer to the newly spawned entity
//=========================================================================
boost::shared_ptr<EntityNode> EntityManager::SpawnEntity ( const Char* type, const Math::Vector3D& position )
{
	debug_assert ( type, "Error, type can't be NULL!" );

	UInt typeID = Core::GenerateHashFromString ( type );

	return SpawnEntity ( typeID, position );
}
//End EntityManager::SpawnEntity



//=========================================================================
//! @function    EntityManager::SpawnEntity
//! @brief       Spawns a new entity of the specified type, at the position specified
//!              
//!				 If there are any unspawned	entities of the same type, then the existing
//!				 entity will be spawned, and a pointer to the existing object returned.
//!				 Otherwise, a new entity will be created and spawned, and a pointer to the new
//!				 object returned
//!
//! @param       type		[in] Entity type. The hash value returned from RegisterEntityType
//!								 for the relevant entity creator	
//!
//! @param       position	[in] Position in the world at which to spawn the entity
//!              
//! @return      A pointer to the newly spawned entity
//=========================================================================
boost::shared_ptr<EntityNode> EntityManager::SpawnEntity ( UInt type, const Math::Vector3D& position )
{
	
	//This might be slow the first few times we spawn an entity
	//with a type we've not seen before, as it'll construct a new std::list
	//but typically this will happen at load-time anyway, so I don't think it's a huge problem.
	if ( m_unspawnedEntities[type].empty() )
	{
		//Create a new entity of the type specified by calling ReserveEntity. 
		//When this call completes, there will be an entity of the appropriate type in the unspawned list
		ReserveEntity ( type, 1 );
	}

	//Get an iterator to the entity
	EntityList::iterator itr = m_unspawnedEntities[type].begin();

	//Spawn the existing entity
	(*itr)->Spawn( position );

	//Move the entity from the unspawned list to the spawned list
	Core::SpliceOntoEnd ( itr, m_unspawnedEntities[type], m_spawnedEntities[type] );

	//Register the entity with the collision manager if necessary
	if ( (!(*itr)->IsFlagSet( EF_NOCOLLIDE )) &&
		 (!(*itr)->IsFlagSet( EF_STATIC )) )
	{
		m_collisionManager.AddCollider( itr->get() );
	}


	//Add the entity to the scene graph
	m_scene.Root()->AddChild( *itr );

	//Return the entity
	return *itr;
}
//End EntityManager::SpawnEntity


//=========================================================================
//! @function    EntityManager::ReserveEntity
//! @brief       Create new entity objects of the type specified
//!              
//! @param       type  [in]	Type hash for entities to create. @see EntityManager::RegisterEntityType
//! @param       count [in]	Number of entities to create
//!              
//=========================================================================
void EntityManager::ReserveEntity ( UInt type, UInt count )
{
	debug_assert ( count, "Tried to reserve 0 entities" );

	for ( UInt i=0; i < count; ++i )
	{
		m_unspawnedEntities[type].push_back( m_entityFactory->Create(type) );
		debug_assert ( m_unspawnedEntities[type].back(), "Error, entity was not created!" 
						"Are you sure the type was registered with the EntityFactory?" );
	}

}
//End EntityManager::ReserveEntity



//=========================================================================
//! @function    EntityManager::Update
//! @brief       Update the entity manager, moving any newly despawned entities
//!				 to the unspawned list
//=========================================================================
void EntityManager::Update ( )
{

	//Go through each spawned entity list, making sure that there are no
	//unspawned entities in the list, moving any unspawned entities to the appropriate list
	//
	//This approach isn't ideal, but this whole system will be getting redesigned 
	//when I make the next version of this engine, after I've submitted my demo
	//
	//This approach should work fine considering the small number of entities my
	//demo will have on screen at any one time
	for ( EntityListMapping::iterator itr = m_spawnedEntities.begin();
		  itr != m_spawnedEntities.end();
		  ++itr )
	{
		UpdateSpawnedList ( itr->first, itr->second );
	}	

}
//End EntityManager::Update


//=========================================================================
//! @function    EntityManager::UpdateSpawnedList
//! @brief       Update the spawned list for a specific type, moving any
//!				 entities that have recently despawned, to the unspawned list					
//!
//! @param		 type [in]	Type of entities held by the entity list
//! @param		 list [in]	List to update
//! 
//=========================================================================
void EntityManager::UpdateSpawnedList ( UInt type, EntityManager::EntityList& list )
{
	EntityList::iterator itr = list.begin();

	while ( itr != list.end() )
	{
		if ( (*itr)->IsFlagSet( EF_DESPAWNPENDING ) )
		{
			(*itr)->Despawn();
		}

		if ( !(*itr)->IsFlagSet( EF_SPAWNED ) )
		{
			//Get the iterator after itr
			EntityList::iterator temp = itr;
			++temp;

			//Move itr from the spawned Entity list to the unspawned Entity list
			Core::SpliceOntoEnd ( itr, list, m_unspawnedEntities[type] );

			//Remove itr from the collision manager, if necessary
			if ( (!(*itr)->IsFlagSet(EF_NOCOLLIDE)) && (!(*itr)->IsFlagSet(EF_STATIC)) )
			{
				m_collisionManager.RemoveCollider( itr->get() );
			}

			//Set itr to temp, as the item referenced by itr is in another list now
			itr = temp;

		}
		else
		{
			++itr;
		}
	}	

}
//End EntityManager::UpdateSpawnedList


//=========================================================================
//! @function    EntityManager::DespawnAll
//! @brief       Despawn all entities
//!              
//!              
//=========================================================================
void EntityManager::DespawnAll ()
{
	//Go through each spawned entity list, despawning all entities
	for ( EntityListMapping::iterator itr = m_spawnedEntities.begin();
		  itr != m_spawnedEntities.end();
		  ++itr )
	{
		DespawnEntitiesInList ( itr->first, itr->second );
	}	
}
//End EntityManager::DespawnAll



//=========================================================================
//! @function    EntityManager::DespawnEntitiesInList
//! @brief       Despawn all entities in an entity list
//!              
//! @param		 type [in] Type ID of the entities in the list
//! @param		 list [in] List which stores the entities
//!              
//=========================================================================
void EntityManager::DespawnEntitiesInList( UInt type, EntityManager::EntityList& list )
{
	EntityList::iterator itr = list.begin();

	while ( itr != list.end() )
	{
		if ( (*itr)->IsFlagSet( EF_SPAWNED ) )
		{
			(*itr)->Despawn();
		}

		//Get the iterator after itr
		EntityList::iterator temp = itr;
		++temp;

		//Move itr from the spawned Entity list to the unspawned Entity list
		Core::SpliceOntoEnd ( itr, list, m_unspawnedEntities[type] );

		//Remove itr from the collision manager, if necessary
		if ( (!(*itr)->IsFlagSet(EF_NOCOLLIDE)) && (!(*itr)->IsFlagSet(EF_STATIC)) )
		{
			m_collisionManager.RemoveCollider( itr->get() );
		}

		//Set itr to temp, as the item referenced by itr is in another list now
		itr = temp;
	}	
}
//End EntityManager::DespawnEntitiesInList