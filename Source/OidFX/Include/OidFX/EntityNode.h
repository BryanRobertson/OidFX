//======================================================================================
//! @file         EntityNode.h
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

#ifndef OIDFX_ENTITYNODE_H
#define OIDFX_ENTITYNODE_H


#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "OidFX/Mesh.h"
#include "OidFX/SceneObject.h"
#include "OidFX/Scene.h"
#include "OidFX/EntityDeathEvent.h"



//=========================================================================
// Forward declarations
//=========================================================================
namespace Math		{ class Matrix4x4; class MatrixStack; class Plane3D; }
namespace OidFX		{ class Scene; }



//namespace OidFX
namespace OidFX
{


	//! Flags that determine entity behaviour
	enum EEntityFlag
	{
		EF_STATIC,					//!< Entity is static, and cannot move under any circumstances (except through parent-child relationships)
		EF_NODRAW,					//!< Entity should not be rendered, even if it is in the view frustum
		EF_SPAWNED,					//!< Entity has been spawned
		EF_DEAD,					//!< Entity has been spawned but it is dead
		EF_SPAWNONGROUND,			//!< If this flag is set, then the game engine will spawn the entity on the ground
		EF_NOWORLDCOLLIDE,			//!< Entity never checks collision against the world
		EF_NOENTITYCOLLIDE,			//!< Entity never checks collision against other entities
		EF_NOPROJECTILECOLLIDE,		//!< Entity never checks collision against projectiles
		EF_NOCOLLIDE,				//!< Entity never does any collision checks
		EF_PROJECTILE,				//!< Entity is a projectile
		EF_FLAMMABLE,				//!< Entity is flammable
		EF_EXPLOSIVE,				//!< Entity is explosive
		EF_PLAYER,					//!< Entity is the player
		EF_INVINCIBLE,				//!< Entity cannot be hurt
		EF_ANTIGRAVITY,				//!< Entity is immune to the effects of gravity
		EF_ENEMY,					//!< Entity is an enemy of the player
		EF_ALLY,					//!< Entity is an ally of the player
		EF_POWERUP,					//!< Entity is a power-up
		EF_BUILDING,				//!< Entity is a building
		EF_NOEXPLOSIONKICKBACK,		//!< Entity doesn't get kicked back by explosions
		EF_OBJECTIVEDESTROY,		//!< Entity is to be destroyed as part of an objective
		EF_OBJECTIVEPROTECT,		//!< Game will end if the entity is destroyed
		EF_DESPAWNPENDING,			//!< Entity requests that it be despawned soon

		EF_COUNT			//!< Maximum entity flag count
	};
	//End enum EEntityFlag


	//!@class	IEntity
	//!@brief	Interface which all entities must adhere to
	class IEntity
	{

		public:

			virtual ~IEntity() {}

			virtual void OnSpawn ( const Math::Vector3D& spawnPoint ) = 0;
			virtual void OnThink ( Float timeElapsed ) = 0;
			virtual void OnTouch ( ) = 0;
			virtual void OnWorldCollide ( const Math::Vector3D& collisionNormal, Float depth ) = 0;
			virtual void OnEntityCollide ( const Math::Vector3D& collisionNormal, Float depth, 
											EntityNode& entity, const Math::Vector3D& entityVelocity ) = 0;
			virtual void OnDeath ( ) = 0;
	};
	//End class IEntity



	//!@class	EntityNode
	//!@brief	Scene node representing an entity in the game world
	class EntityNode : public SceneObject, public IEntity
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			EntityNode ( Scene& scene,
						 const Char* name,
						 const Char* meshFileName,
						 const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
						 const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );


            //=========================================================================
            // Public methods
            //=========================================================================
			void Spawn ( const Math::Vector3D& spawnPoint );
			void UpdatePhysics ( Float timeElapsedInSeconds );
			
			void Update( Math::MatrixStack& toWorldStack, 
						 Math::MatrixStack& fromWorldStack, 
						 Float timeElapsedInSeconds );

			//Fill visible object list
			void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );

			bool CanCollideWith ( const EntityNode* entity ) const;

			void QueryScene ( const Math::BoundingSphere3D& sphere, EntityQueryResult& result );

			
            //=========================================================================
            // Event handler registration
            //=========================================================================
			Core::EventConnection RegisterDeathHandler ( IEntityDeathSensitive& handler );

			
            //=========================================================================
            // Accessors for physics properites
            //=========================================================================
			inline const Math::Quaternion& GetOrientation() const throw();
			inline const Math::Vector3D&   GetAcceleration() const throw();
			inline const Math::Vector3D&   GetVelocity() const throw();
			inline const Math::Vector3D&   GetAngularAcceleration() const throw();
			inline const Math::Vector3D&   GetAngularVelocity() const throw();

			inline void SetOrientation( const Math::Quaternion& orientation );
			inline void SetAcceleration( const Math::Vector3D& acceleration );
			inline void SetVelocity( const Math::Vector3D& velocity );
			inline void SetAngularAcceleration ( const Math::Vector3D& angularAccel );
			inline void SetAngularVelocity ( const Math::Vector3D& angularVelocity );

			//=========================================================================
            // AI events
            //=========================================================================
			virtual void OnSpawn ( const Math::Vector3D& spawnPoint );
			virtual void OnThink ( Float timeElapsed );
			virtual void OnTouch ( );
			virtual void OnWorldCollide ( const Math::Vector3D& collisionNormal, Float depth );
			virtual void OnEntityCollide ( const Math::Vector3D& collisionNormal, Float depth, 
											EntityNode& entity, const Math::Vector3D& entityVelocity );
			virtual void OnDeath ( );

			inline void Kill ( );
			inline void Despawn ( );

			void Explode ( );
			void Ignite ( );

            //=========================================================================
            // Attributes
            //=========================================================================
			inline Float GetHealth ( ) const throw();
			inline void  SetHealth ( Float health ) throw();
			inline void  Hurt ( Float amount ) throw();
			inline void  Heal ( Float amount ) throw();
			inline bool  IsDead ( ) const throw();
			inline bool	 IsSpawned ( ) const throw();

			inline void SetFlag ( EEntityFlag flag ) throw();
			inline void ClearFlag ( EEntityFlag flag ) throw();
			inline bool IsFlagSet ( EEntityFlag flag ) const throw();

			inline void SetExplosiveStrength( Float strength ) throw();
			inline Float GetExplosiveStrength () const throw();

			inline ECollisionType PreferredCollisionType() const throw();

			//=========================================================================
            // IRenderable implementation
            //=========================================================================
			void QueueForRendering ( Renderer::RenderQueue& queue );
			void Render ( Renderer::IRenderer& renderer );

            //=========================================================================
            // QueryInterface
            //=========================================================================
			virtual inline bool QueryInterface ( enum ENodeInterfaceType type, void** receiver );

            //=========================================================================
            // Mesh related
            //=========================================================================
			inline void	 SetMesh ( HMesh& mesh ) throw();
			inline HMesh GetMesh ( ) throw();



		protected:


            //=========================================================================
            // Protected data
            //=========================================================================
			Math::Vector3D				m_position;
			Math::Quaternion			m_orientation;
			Math::Vector3D				m_acceleration;
			Math::Vector3D				m_velocity;
			Math::Vector3D				m_angularVelocity;
			Math::Vector3D				m_angularAcceleration;

			Float						m_explosiveStrength;

			ECollisionType				m_preferredCollisionType;

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			typedef std::bitset<EF_COUNT>	EntityFlagSet;

            //=========================================================================
            // Private data
            //=========================================================================

			//Gameplay related
			Float				m_health;
			EntityFlagSet		m_flags;

			//Misc
			Core::PooledString	m_name;
			
			//Rendering related
			HMesh				m_mesh;

			//
			Float				m_deathTimer;

			//
			EntityDeathEvent	m_deathEvent;

			

	};
	//End class EntityNode


    //=========================================================================
    // Typedefs
    //=========================================================================
	typedef boost::shared_ptr<EntityNode> EntityPtr;



    //=========================================================================
    //! @function    EntityNode::PreferredCollisionType
    //! @brief       Type of collision test to perform when testing this 
    //!              entity against the world
	//!
    //! @return		 Type of collision test to perform
    //=========================================================================
	ECollisionType EntityNode::PreferredCollisionType() const
	{
		return m_preferredCollisionType;
	}
	//End EntityNode::PrefferedCollisionType


	//=========================================================================
    //! @function    EntityNode::GetExplosiveStrength
    //! @brief       Get the strength of the explosion that this entity will create
    //!              
    //! @return      The explosive strength of the entity
    //=========================================================================
	Float EntityNode::GetExplosiveStrength ( ) const
	{
		return m_explosiveStrength;
	}
	//End EntityNode::GetExplosiveStrength


    //=========================================================================
    //! @function    EntityNode::SetExplosiveStrength
    //! @brief       Set the strength at which the entity will explode
    //!              
    //! @param       explosiveStrength [in]
    //!              
    //=========================================================================
	void EntityNode::SetExplosiveStrength ( Float explosiveStrength )
	{
		m_explosiveStrength = explosiveStrength;
	}
	//End EntityNode::SetExplosiveStrength



    //=========================================================================
    //! @function    EntityNode::GetOrientation
    //! @brief       Get the orientation of the entity
    //!              
	//! @return		 The orientation of the entity
    //=========================================================================
	const Math::Quaternion& EntityNode::GetOrientation() const
	{
		return m_orientation;
	}
	//End EntityNode::GetOrientation



    //=========================================================================
    //! @function    EntityNode::GetHealth
    //! @brief       Return the health of the entity
	//!
	//!				 The health of the entity is stored as a floating point number.
	//!				 the health value is not normalised, the default value is 100.0
    //!              
    //! @return      The health of the entity
    //=========================================================================
	Float EntityNode::GetHealth ( ) const
	{
		return m_health;
	}
	//End EntityNode::GetHealth



    //=========================================================================
    //! @function    EntityNode::SetHealth
    //! @brief       Set the health of the entity
    //!              
	//!				 If the health 
	//!
    //! @param       health [in] New value for the entity's health
    //!              
    //=========================================================================
	void EntityNode::SetHealth ( Float health )
	{
		m_health = health;

		if ( m_health <= 0.0f )
		{
			//Call the event handlers for death
			m_deathEvent.OnEntityDeath ( this );

			//Kill all event handlers
			m_deathEvent.DisconnectAll();

			SetFlag ( EF_DEAD );
			OnDeath();
		}
	}
	//End EntityNode::SetHealth



    //=========================================================================
    //! @function    EntityNode::Hurt
    //! @brief       Hurt an entity. Reducing its health
    //!              
	//!				 If the new health value is <= 0, then the entity will be killed.
	//!
	//!				 If the entity is invincible, then its health will not be affected.
	//!
    //! @param       amount [in] Amount to reduce the entity's health by
    //!              
    //=========================================================================
	void EntityNode::Hurt ( Float amount )
	{
		if ( !IsFlagSet( EF_INVINCIBLE ) )
		{
			SetHealth ( m_health - amount );
		}
	}
	//End EntityNode::Hurt



    //=========================================================================
    //! @function    EntityNode::Heal
    //! @brief       Heal the entity, increasing its health by the amount specified
    //!              
    //! @param       amount [in] Amount to increase the entity's health by
    //!              
    //=========================================================================
	void  EntityNode::Heal ( Float amount )
	{
		SetHealth ( m_health + amount );
	}
	//End EntityNode::Heal



    //=========================================================================
    //! @function    EntityNode::SetMesh
    //! @brief       Set the entity's mesh
    //!              
    //! @param       mesh [in]
    //!              
    //=========================================================================
	void EntityNode::SetMesh ( HMesh& mesh )
	{
		m_mesh = mesh;
		SetBoundingBox( mesh->GetObjectSpaceBoundingBox() );
	}
	//End EntityNode::SetMesh



    //=========================================================================
    //! @function    EntityNode::GetMesh
    //! @brief       Get the entity's mesh
    //!              
    //=========================================================================
	HMesh EntityNode::GetMesh ( )
	{
		return m_mesh;
	}
	//End EntityNode::GetMesh



    //=========================================================================
    //! @function    EntityNode::SetFlag
    //! @brief       Set one of the entity's flags
    //!              
    //! @param       flag [in]
    //!              
    //=========================================================================
	void EntityNode::SetFlag ( EEntityFlag flag )
	{
		debug_assert ( flag != EF_COUNT, "Error, invalid flag" );

		m_flags[flag] = true;
	}
	//End EntityNode::SetFlag



    //=========================================================================
    //! @function    EntityNode::ClearFlag
    //! @brief       Clear one of the entity's flags
    //!              
    //! @param       flag [in]
    //!              
    //=========================================================================
	void EntityNode::ClearFlag ( EEntityFlag flag )
	{
		debug_assert ( flag != EF_COUNT, "Error, invalid flag" );

		m_flags[flag] = false;
	}
	//End EntityNode::ClearFlag



    //=========================================================================
    //! @function    EntityNode::IsFlagSet
    //! @brief       Indicates whether or not a flag is set
    //!              
    //! @param       flag [in]
    //!              
    //=========================================================================
	bool EntityNode::IsFlagSet ( EEntityFlag flag ) const
	{
		debug_assert ( flag != EF_COUNT, "Error, invalid flag!" );

		return m_flags[flag];
	}
	//End EntityNode::IsFlagSet



    //=========================================================================
    //! @function    EntityNode::Kill
    //! @brief       Kill the entity by setting its health to 0
    //!              
    //=========================================================================
	void EntityNode::Kill ( )
	{
		SetHealth( 0.0f );
	}
	//End EntityNode::Kill


    //=========================================================================
    //! @function    EntityNode::Despawn
    //! @brief       Call this to remove an entity from the world
    //!              
    //!              
    //=========================================================================
	void EntityNode::Despawn ( )
	{
		//Clear the spawned flag
		ClearFlag ( EF_SPAWNED );

		if ( m_parent )
		{
			//Remove the entity from the scene graph
			m_parent->RemoveChild ( ID() );
		}

	}
	//End EntityNode::Despawn


    //=========================================================================
    //! @function    EntityNode::GetAcceleration
    //! @brief       Return the acceleration of the entity
    //!              
    //! @return      The acceleration of the entity
    //=========================================================================
	const Math::Vector3D& EntityNode::GetAcceleration() const
	{
		return m_acceleration;
	}
	//End EntityNode::GetAcceleration


    //=========================================================================
    //! @function    EntityNode::GetVelocity
    //! @brief       Return the velocity of the entity
    //!              
    //! @return      The velocity of the entity
    //=========================================================================
	const Math::Vector3D& EntityNode::GetVelocity() const
	{
		return m_velocity;
	}
	//End EntityNode::GetVelocity


    //=========================================================================
    //! @function    EntityNode::GetAngularAcceleration
    //! @brief       Get the angular acceleration of the entity
	//!
    //! @return      The angular acceleration of the entity
    //=========================================================================
	const Math::Vector3D& EntityNode::GetAngularAcceleration() const
	{
		return m_angularAcceleration;
	}
	//End EntityNode::GetAngularAcceleration


    //=========================================================================
    //! @function    EntityNode::GetAngularVelocity
    //! @brief       Return the angular velocity of the entity
    //!              
    //! @return      The angular velocity of the entity
    //=========================================================================
	const Math::Vector3D& EntityNode::GetAngularVelocity() const
	{
		return m_angularVelocity;
	}
	//End EntityNode::GetAngularVelocity


    //=========================================================================
    //! @function    EntityNode::SetOrientation
    //! @brief       Set the orientation of the entity
    //!              
    //! @param       orientation [in]
    //!              
    //=========================================================================
	void EntityNode::SetOrientation( const Math::Quaternion& orientation )
	{
		m_orientation = orientation;
	}
	//End EntityNode::SetOrientation


    //=========================================================================
    //! @function    EntityNode::SetAcceleration
    //! @brief       Set acceleration
    //!              
    //! @param       acceleration [in] 
    //=========================================================================
	void EntityNode::SetAcceleration( const Math::Vector3D& acceleration )
	{
		m_acceleration = acceleration;
	}
	//End EntityNode::SetAcceleration


    //=========================================================================
    //! @function    EntityNode::SetVelocity
    //! @brief       Set the velocity of the entity
    //!              
    //! @param       velocity [in]
    //=========================================================================
	void EntityNode::SetVelocity( const Math::Vector3D& velocity )
	{
		m_velocity = velocity;
	}
	//End EntityNode::SetVelocity


    //=========================================================================
    //! @function    EntityNode::SetAngularAcceleration
    //! @brief       Set the angular acceleration of the entity
    //!              
    //! @param       angularAccel [in]
    //!              
    //=========================================================================
	void EntityNode::SetAngularAcceleration ( const Math::Vector3D& angularAccel )
	{
		m_angularAcceleration = angularAccel;
	}
	//End EntityNode::SetAngularAcceleration


    //=========================================================================
    //! @function    EntityNode::SetAngularVelocity
    //! @brief       Set the angular velocity of the entity
    //!              
    //! @param       angularVelocity [in]
    //!              
    //=========================================================================
	void EntityNode::SetAngularVelocity ( const Math::Vector3D& angularVelocity )
	{
		m_angularVelocity = angularVelocity;
	}
	//End Entitynode::SetAngularVelocity


    //=========================================================================
    //! @function    EntityNode::QueryInterface
    //! @brief       Query the entity to see if it supports an interface
    //!              
    //! @param       type	 [in]
    //! @param       pointer [out]
    //!              
    //! @return      true if supported, false if not supported
    //=========================================================================
	bool EntityNode::QueryInterface ( enum ENodeInterfaceType type, void** receiver )
	{
		if ( type == NODEINTERFACE_IENTITY )
		{
			*receiver = static_cast<void*>( static_cast<IEntity*>(this) );
			return true;
		}

		return false;
	}
	//End EntityNode::QueryInterface


}
//end namespace OidFX


#endif
//#ifndef OIDFX_ENTITYNODE_H

