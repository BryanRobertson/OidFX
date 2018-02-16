//======================================================================================
//! @file         EntityManager.h
//! @brief        Class to manage the creation, storage, and destruction of entities
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

#ifndef OIDFX_ENTITYMANAGER_H
#define OIDFX_ENTITYMANAGER_H


//=========================================================================
// Forward declaration
//=========================================================================
namespace Math			{ class Vector3D;	}
namespace OidFX			{ class EntityNode;	class IEntityCreator; class EntityFactory; }


//namespace OidFX
namespace OidFX
{

	//!@class	EntityManager
	//!@brief	Class to manage the creation, storage, and destruction of entities
	//!
	//!
	class EntityManager
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			EntityManager ( Scene& scene, CollisionManager& collisionManager ); 


            //=========================================================================
            // Public methods
            //=========================================================================
			UInt RegisterType ( boost::shared_ptr<IEntityCreator> creator );

			boost::shared_ptr<EntityNode> SpawnEntity ( const Char* type, const Math::Vector3D& position );
			boost::shared_ptr<EntityNode> SpawnEntity ( UInt type, const Math::Vector3D& position );

			void ReserveEntity ( UInt type, UInt count );

			void Update();

			void DespawnAll();

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			typedef std::list<boost::shared_ptr<EntityNode>, boost::fast_pool_allocator<boost::shared_ptr<EntityNode> > > EntityList;
			typedef std::map<UInt, EntityList>  EntityListMapping;

			typedef std::vector<boost::shared_ptr<EntityNode>, boost::fast_pool_allocator<boost::shared_ptr<EntityNode> > >
					EntityStore;


            //=========================================================================
            // Private methods
            //=========================================================================
			void UpdateSpawnedList ( UInt type, EntityList& list );
			void DespawnEntitiesInList ( UInt type, EntityList& list );


            //=========================================================================
            // Private data
            //=========================================================================
			EntityStore				m_entities;
			EntityListMapping		m_spawnedEntities;
			EntityListMapping		m_unspawnedEntities;

			boost::shared_ptr<EntityFactory> m_entityFactory;
			Scene&							 m_scene;
			CollisionManager&				 m_collisionManager;
			


	};
	//End class EntityManager

}
//end namespace OidFX



#endif
//#ifndef OIDFX_ENTITYMANAGER_H
