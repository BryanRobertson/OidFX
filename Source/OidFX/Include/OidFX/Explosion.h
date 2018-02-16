//======================================================================================
//! @file         Explosion.h
//! @brief        Entity representing an explosion
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 05 October 2005
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


#ifndef OIDFX_EXPLOSION_H
#define OIDFX_EXPLOSION_H


#include "OidFX/EntityNode.h"
#include "OidFX/EntityCreator.h"
#include "OidFX/Billboard.h"




//=========================================================================
// Forward declarations
//=========================================================================
namespace Math	{ class Matrix4x4; class Vector3D;	}
namespace OidFX { class ExplosionCreator; 		    }



//namespace OidFX
namespace OidFX
{

	//!@class	Explosion
	//!@brief	Entity representing an explosion
	class Explosion : public EntityNode
	{

		public:


            //=========================================================================
            // Constructors
            //=========================================================================
			Explosion ( Scene& scene );


			//=========================================================================
            // Public static methods
            //=========================================================================
			static boost::shared_ptr<ExplosionCreator> GetExplosionCreator();


            //=========================================================================
            // Public methods
            //=========================================================================
			void Update( Math::MatrixStack& toWorldStack, 
						 Math::MatrixStack& fromWorldStack, 
						 Float timeElapsedInSeconds );

			virtual void OnSpawn( const Math::Vector3D& spawnPoint );
			virtual void OnDeath();

		private:

			//=========================================================================
            // Static private data
            //=========================================================================
			static boost::shared_ptr<ExplosionCreator>		ms_explosionCreator;

            //=========================================================================
            // Private data
            //=========================================================================
			Billboard	m_billboard;

	};
	//End class Explosion


	
	//!@class	ExplosionCreator
	//!@brief	Class used in the EntityFactory to instantiate Explosion entities
	class ExplosionCreator : public IEntityCreator
	{
		public:

			boost::shared_ptr<EntityNode> Create( const Char* name, Scene& scene )	
									{ return boost::shared_ptr<EntityNode>( new Explosion(scene) ); }
			const Char* TypeName() const
									{ return "Explosion";	}
		private:

	};
	//End ExplosionCreator


}
//End namespace OidFX


#endif
//#ifndef OIDFX_EXPLOSION_H
