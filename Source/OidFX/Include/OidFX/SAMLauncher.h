//======================================================================================
//! @file         SAMLauncher.h
//! @brief        Class representing a SAM launcher, that fires at the player
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 16 September 2005
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


#ifndef OIDFX_SAMLAUNCHER_H
#define OIDFX_SAMLAUNCHER_H


#include "OidFX/EntityCreator.h"
#include "OidFX/EntityNode.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Math		{ class Matrix4x4; class MatrixStack; }
namespace OidFX		{ class Scene; class MissileLauncher; class TargetingComputer; class SAMLauncherCreator; }



//namespace OidFX
namespace OidFX
{



	//!@class	SAMLauncher
	//!@brief	Class representing a SAM Launcher, which can fire missiles at the player
	class SAMLauncher : public EntityNode
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			SAMLauncher	(	Scene& scene,
							const Char* name,
							const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
							const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );


            //=========================================================================
            // Public static methods
            //=========================================================================
			static boost::shared_ptr<SAMLauncherCreator> GetSAMLauncherCreator();


			//=========================================================================
            // Public methods
            //=========================================================================
			virtual void Update ( Math::MatrixStack& toWorldStack, Math::MatrixStack& fromWorldStack, Float timeElapsedInSeconds );

			virtual void OnSpawn ( const Math::Vector3D& spawnPoint );
			virtual void OnThink ( Float timeElapsed );
			virtual void OnTouch ( );
			virtual void OnEntityCollide ( const Math::Vector3D& collisionNormal, Float depth, 
											EntityNode& entity, const Math::Vector3D& entityVelocity );
			virtual void OnDeath ( );

		
		private:

            //=========================================================================
            // Static private data
            //=========================================================================
			static boost::shared_ptr<SAMLauncherCreator>		ms_samLauncherCreator;

            //=========================================================================
            // Private methods
            //=========================================================================
			void LaunchMissile();

            //=========================================================================
            // Private data
            //=========================================================================
			bool				  m_launch; //!< Indicates whether or not a missile should be launched this frame
			Float				  m_launchTimeOut;
			Float				  m_launchTimer;
			Float				  m_maxTurnRate;

			boost::shared_ptr<TargetingComputer> m_targetingComputer;
			boost::shared_ptr<MissileLauncher>	 m_missileLauncher;

	};
	//End class SAMLauncher



	//!@class	SAMLauncherCreator
	//!@brief	Class used in the EntityFactory to instantiate SAMLauncher entities
	class SAMLauncherCreator : public IEntityCreator
	{
		public:

			boost::shared_ptr<EntityNode> Create( const Char* name, Scene& scene )	
									{ return boost::shared_ptr<EntityNode>( new SAMLauncher(scene, name) ); }
			const Char* TypeName() const
									{ return "SAMLauncher";	}
		private:

	};
	//End SAMLauncherCreator



}
//End namespace OidFX



#endif
//#ifndef OIDFX_SAMLAUNCHER_H
