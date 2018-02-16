//======================================================================================
//! @file         Chopper.h
//! @brief        Entity representing a player controllable helicopter
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 29 August 2005
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

#ifndef OIDFX_CHOPPER_H
#define OIDFX_CHOPPER_H


#include "Core/KeyboardSensitive.h"
#include "Core/MouseSensitive.h"
#include "OidFX/EntityCreator.h"
#include "OidFX/EntityNode.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Math		{ class Matrix4x4; class MatrixStack; }
namespace OidFX		{ class Scene; class MissileLauncher; class TargetingComputer; class ChopperEntityCreator; }



//namespace OidFX
namespace OidFX
{


	//!@class Chopper
	//!@brief Class representing a player controllable helicopter
	class Chopper : public EntityNode,
					public Core::IMouseSensitive,
					public Core::IKeyboardSensitive
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			Chopper (	Scene& scene,
						const Char* name,
						const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
						const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );


            //=========================================================================
            // Public static methods
            //=========================================================================
			static boost::shared_ptr<ChopperEntityCreator> GetChopperCreator();

            //=========================================================================
            // Public methods
            //=========================================================================

			virtual void Update ( Math::MatrixStack& toWorldStack, Math::MatrixStack& fromWorldStack, Float timeElapsedInSeconds );

			virtual void OnSpawn ( const Math::Vector3D& spawnPoint );
			virtual void OnThink ( Float timeElapsed );
			virtual void OnTouch ( );
			virtual void OnWorldCollide ( const Math::Vector3D& collisionNormal, Float depth );
			virtual void OnEntityCollide ( const Math::Vector3D& collisionNormal, Float depth, 
											EntityNode& entity, const Math::Vector3D& entityVelocity );
			virtual void OnDeath ( );

			 
			//=========================================================================
            // IMouseSensitive implementation
            //=========================================================================
			void OnMouseMove		( Int movementX, Int movementY );

			void OnMouseButtonDown  ( UInt buttonIndex );		
			void OnMouseButtonUp	( UInt buttonIndex );		
			void OnMouseScroll		( Int scroll );		


            //=========================================================================
            // IKeyboardSensitive implementation
            //=========================================================================
			void OnKeyDown ( UInt keyCode );
			void OnKeyUp   ( UInt keyCode );

			//Not implementing this at the moment
			void OnChar	   ( Char charValue, UInt repeats, bool prevKeyState ) {}

		private:


            //=========================================================================
            // Private methods
            //=========================================================================
			void LaunchMissile ( );


            //=========================================================================
            // Static private data
            //=========================================================================
			static boost::shared_ptr<ChopperEntityCreator>	ms_chopperCreator;

            //=========================================================================
            // Private data
            //=========================================================================
			Core::EventConnection m_mouseConnection;
			Core::EventConnection m_keyboardConnection;

			Float				  m_accelX;	//!< Acceleration along local x axis
			Float				  m_accelY; //!< Acceleration along local y axis
			Float				  m_accelZ; //!< Acceleration along local z axis

			bool				  m_launch; //!< Indicates whether or not a missile should be launched this frame

			boost::shared_ptr<TargetingComputer> m_targetingComputer;
			std::vector<boost::shared_ptr<MissileLauncher> >	 m_missileLaunchers;

	};
	//End class Chopper




	//!@class	ChopperEntityCreator
	//!@brief	Class used in the EntityFactory to instantiate Chopper entities
	class ChopperEntityCreator : public IEntityCreator
	{
		public:

			boost::shared_ptr<EntityNode> Create( const Char* name, Scene& scene )	
									{ return boost::shared_ptr<EntityNode>( new Chopper(scene, name) ); }
			const Char* TypeName() const
									{ return "Chopper";	}
		private:

	};
	//End ChopperEntityCreator




}
//end namespace OidFX


#endif
//#ifndef OIDFX_CHOPPER_H
