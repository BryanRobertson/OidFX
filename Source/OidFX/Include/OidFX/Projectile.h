//======================================================================================
//! @file         Projectile.h
//! @brief        Class representing a projectile, such as a missle
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 02 September 2005
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

#ifndef OIDFX_PROJECTILE_H
#define OIDFX_PROJECTILE_H


//namespace OidFX
namespace OidFX
{


	//! Flags that govern the behaviour of projectiles
	enum EProjectileFlag
	{
		PF_MISSILE,						//!< Projectile is a missile
	
		PF_COUNT
	};
	//End EProjectileFlag


	//!@class	Projectile
	//!@brief	Class representing a projectile, such as a missile
	//!
	class Projectile : public EntityNode
	{
		
		public:

            //=========================================================================
            //  Constructors/Destructor
            //=========================================================================
			Projectile (	Scene& scene,
							const Char* name,
							const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
							const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );

            //=========================================================================
            // Public types
            //=========================================================================
			enum EProjectileState
			{
				PS_LAUNCHSTAGE,		//!< Projectile is newly launched
				PS_TARGETING		//!< Projectile has been launched
			};


            //=========================================================================
            // Public methods
            //=========================================================================
			void Spawn ( const Math::Vector3D& spawnPoint,
						 UInt ownerID,
						 HMesh& mesh );

			void Update( Math::MatrixStack& toWorldStack, 
						 Math::MatrixStack& fromWorldStack, 
						 Float timeElapsedInSeconds );

			//Mutators
			inline void SetTimeout ( Float timeOut ) throw();
			inline void ClearTarget ( ) throw();
			inline void SetTarget ( EntityNode* target ) throw();

			//Accessors
			inline Float	 GetTimeout () const throw();
			inline EntityNode* GetTarget ( ) throw();

			//Collision related
			bool CanCollideWith( const OidFX::EntityNode* entity ) const;


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

            //=========================================================================
            // Flags 
            //=========================================================================
			
			//Import the parent methods, so that our new flag methods don't hide them
			using EntityNode::SetFlag;
			using EntityNode::ClearFlag;
			using EntityNode::IsFlagSet;

			inline void SetFlag ( OidFX::EProjectileFlag flag );
			inline void ClearFlag ( OidFX::EProjectileFlag flag );
			inline bool IsFlagSet ( OidFX::EProjectileFlag flag ) const;

		private:

            //=========================================================================
            // Private methods
            //=========================================================================
			inline EProjectileState GetState () const throw();
			inline void				SetState ( EProjectileState state ) throw();

			//Make EntityNode::Spawn private
			using EntityNode::Spawn;


            //=========================================================================
            // Private data
            //=========================================================================
			std::bitset<PF_COUNT>		m_projectileFlags;
			EProjectileState			m_projectileState;

			EntityNode*					m_target;
			UInt						m_ownerID;
			Float						m_timeOut;

			Float						m_timeElapsedSinceLaunch;
	};
	//End class Projectile



    //=========================================================================
    // Typedefs
    //=========================================================================
	typedef boost::shared_ptr<Projectile>	ProjectilePtr;



    //=========================================================================
    //! @function    Projectile::SetTimeout
    //! @brief       Set the time before the projectile explodes
    //!              
    //! @param       timeOut [in]
    //=========================================================================
	void Projectile::SetTimeout ( Float timeOut )
	{
		m_timeOut = timeOut;
	}
	//End Projectile::SetTimeout


    //=========================================================================
    //! @function    Projectile::ClearTarget
    //! @brief       Clear the projectile's target
    //!              
    //!              Without a target the projectile will just travel in a straight line
    //!              until it hits something
    //=========================================================================
	void Projectile::ClearTarget ( )
	{
		m_target = 0;
	}
	//End Projectile::ClearTarget


    //=========================================================================
    //! @function    Projectile::SetTarget
    //! @brief       Set the target of the projectile
	//!				 Once the projectile is in the targeting stage, it will 
	//!				 pursue this target
    //!              
    //! @param       target [in]
    //!              
    //=========================================================================
	void Projectile::SetTarget ( EntityNode* target )
	{
		m_target = target;
	}
	//End Projectile::SetTarget



    //=========================================================================
    //! @function    Projectile::GetTarget
    //! @brief       Return the target of the projectile
    //!              
	//!				 If the projectile is not targeting anything, then a null
	//!				 pointer will be returned
    //!              
    //! @return      A pointer to the target
    //=========================================================================
	EntityNode* Projectile::GetTarget ( )
	{
		return m_target;
	}
	//End Projectile::GetTarget



    //=========================================================================
    //! @function    Projectile::GetState
    //! @brief       Get the current state of the projectile
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	Projectile::EProjectileState Projectile::GetState () const
	{
		return m_projectileState;
	}
	//End Projectile::GetState



    //=========================================================================
    //! @function    Projectile::SetState
    //! @brief       Set the current state of the projectile
    //!              
    //! @param       state [in] New state
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	void Projectile::SetState ( Projectile::EProjectileState state )
	{
		m_projectileState = state;
	}
	//End Projectile::SetState


    //=========================================================================
    //! @function    Projectile::SetFlag
    //! @brief       Set one of the projectile's flags
    //!              
    //! @param       flag [in]
    //=========================================================================
	inline void Projectile::SetFlag ( OidFX::EProjectileFlag flag )
	{
		m_projectileFlags[flag] = true;
	}
	//End Projectile::SetFlag



    //=========================================================================
    //! @function    Projectile::ClearFlag
    //! @brief       Clear one of the projectile's flags
    //!              
    //! @param       flag [in]
    //!              
    //=========================================================================
	inline void Projectile::ClearFlag ( OidFX::EProjectileFlag flag )
	{
		m_projectileFlags[flag] = false;
	}
	//End Projectile::ClearFlag



    //=========================================================================
    //! @function    Projectile::IsFlagSet
    //! @brief       Indicates whether or not the specified flag is set
    //!              
    //! @param       flag 
    //!              
    //! @return      true if the flag is set, false otherwise
    //=========================================================================
	inline bool Projectile::IsFlagSet ( OidFX::EProjectileFlag flag ) const
	{
		return m_projectileFlags[flag];
	}
	//End Projectile::IsFlagSet


}
//end namespace OidFX



#endif
//#ifndef OIDFX_PROJECTILE_H
