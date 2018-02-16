//======================================================================================
//! @file         ProjectileManager.h
//! @brief        Manager class for projectiles
//!               
//!				  Manages a store of spawned and unspawned projectiles
//!				  allowing projectiles to be reused, so that new projectiles
//!				  can be launched without having to create
//!				  a new object on the heap
//!
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


#ifndef OIDFX_PROJECTILEMANAGER_H
#define OIDFX_PROJECTILEMANAGER_H


#include "OidFX/Constants.h"
#include "OidFX/EntityNode.h"
#include "OidFX/Projectile.h"
#include <boost/pool/pool_alloc.hpp>


//namespace OidFX
namespace OidFX
{


	//!@class	ProjectileManager
	//!@brief	Manager class for projectiles
	//!               
	//!			Manages a store of spawned and unspawned projectiles
	//!		    allowing projectiles to be reused, so that new projectiles
	//!			can be launched without having to create
	//!		    a new object on the heap
	class ProjectileManager
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			ProjectileManager ( Scene& scene, UInt maxProjectiles, CollisionManager&	collisionManager );

			
            //=========================================================================
            // Public methods
            //=========================================================================
			void Update ( );

			ProjectilePtr SpawnProjectile ( const Math::Vector3D& spawnPoint,
											UInt ownerID,
											HMesh& mesh );

			void DestroyAll ( );


		private:

            //=========================================================================
            // Private methods
            //=========================================================================
			void Populate();

            //=========================================================================
            // Private types
            //=========================================================================
			typedef std::list< ProjectilePtr, boost::fast_pool_allocator<ProjectilePtr> > ProjectileList;
			typedef ProjectileList::iterator		iterator;
			typedef ProjectileList::const_iterator  const_iterator;


            //=========================================================================
            // Private data
            //=========================================================================
			ProjectileList	m_spawnedProjectiles;
			ProjectileList	m_unspawnedProjectiles;

			UInt				m_maxProjectiles;
			Scene&				m_scene;
			CollisionManager&	m_collisionManager;

	};
	//End class ProjectileManager


}
//End namespace OidFX


#endif
//#ifndef OIDFX_PROJECTILEMANAGER_H

