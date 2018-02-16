//======================================================================================
//! @file         Explosion.cpp
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


#include "Core/Core.h"
#include "Math/Matrix4x4.h"
#include "Renderer/EffectManager.h"
#include "OidFX/Scene.h"
#include "OidFX/Constants.h"
#include "OidFX/Explosion.h"
#include "OidFX/GameApplication.h"
#include "OidFX/BillboardManager.h"




using namespace OidFX;



//=========================================================================
// Static initialisation
//=========================================================================
boost::shared_ptr<ExplosionCreator> Explosion::ms_explosionCreator = boost::shared_ptr<ExplosionCreator>();


//=========================================================================
// Static methods
//=========================================================================
boost::shared_ptr<ExplosionCreator> Explosion::GetExplosionCreator()
{
	if ( !ms_explosionCreator )
	{
		ms_explosionCreator = boost::shared_ptr<ExplosionCreator>( new ExplosionCreator() );
	}

	return ms_explosionCreator;
}



//=========================================================================
//! @function    Explosion::Explosion
//! @brief       Explosion constructor
//!              
//! @param       scene [in]
//!              
//=========================================================================
Explosion::Explosion ( Scene& scene )
: EntityNode ( scene, "Boom!", ""),
  m_billboard( scene.Application().GetEffectManager().AcquireEffect("Data/Art/Effects/Explosion.ofx") )
{
	SetFlag(EF_NOCOLLIDE);
	SetFlag(EF_NOEXPLOSIONKICKBACK);
	SetFlag(EF_ANTIGRAVITY);

}
//End Explosion::Explosion




//=========================================================================
//! @function    Explosion::Update
//! @brief       
//!              
//! @param       toWorldStack         [in]
//! @param		 fromWorldStack		  [in]
//! @param		 timeElapsedInSeconds [in]
//!              
//=========================================================================
void Explosion::Update ( Math::MatrixStack& toWorldStack,
						 Math::MatrixStack& fromWorldStack,
						 Float timeElapsedInSeconds )
{

	EntityNode::Update( toWorldStack, fromWorldStack, timeElapsedInSeconds );

	if (!IsFlagSet(EF_DEAD) )
	{
		Kill();
	}

	m_billboard.SetPosition( GetWorldSpacePosition() );
	m_billboard.Update ( timeElapsedInSeconds );
	m_scene.Application().GetBillboardManager().AddToBillboardList( m_billboard );

}
//End  Explosion::Update




//=========================================================================
//! @function    Explosion::OnSpawn
//! @brief       
//!              
    
//=========================================================================
void Explosion::OnSpawn( const Math::Vector3D& spawnPoint )
{
	//Clear flags so that the explosion doesn't become ineffective when it respawns
	ClearFlag(EF_ENEMY);
	ClearFlag(EF_ALLY);

	EntityNode::OnSpawn( spawnPoint );

	m_billboard.SetOpacity	   ( 1.0f );
	m_billboard.SetOpacityAnim ( -0.6f );
	m_billboard.SetScaleAnim   ( 500.0f );
}
//End Explosion::OnSpawn



//=========================================================================
//! @function    Explosion::OnDeath
//! @brief       
//!              
    
//=========================================================================
void Explosion::OnDeath()
{

	Math::BoundingSphere3D areaOfEffect( GetExplosiveStrength() * meters, GetWorldSpacePosition() );

	//Create explosion sprite
	m_billboard.SetScale ( areaOfEffect.Radius() );

	//Find all entities within the area of effect
	EntityQueryResult results;

	m_scene.QueryScene( areaOfEffect, results );

	for ( EntityQueryResult::iterator itr = results.begin(); 
		  itr != results.end();
		  ++itr )
	{
		
		//Friendly fire on?
		static Core::ConsoleBool friendly_fire( "friendly_fire", false );

		//Ignore entity if approriate flags are set
		if ( !friendly_fire )
		{
			if (	(*itr)->IsFlagSet(EF_ENEMY) && IsFlagSet(EF_ENEMY)
				|| ((*itr)->IsFlagSet(EF_ALLY) && IsFlagSet(EF_ALLY))
				|| ((*itr)->IsFlagSet(EF_PLAYER) && IsFlagSet(EF_ALLY)))
			{
				continue;
			}
		}
		
		//Get the distance between the explosion and the entity
		Math::Vector3D displacement = (*itr)->BoundingBox().GetCentre() - GetWorldSpacePosition();
		Float distance = displacement.Length(); 

		//Calculate the explosive strength
		Float explosionStrength = 0.0f;
		
		explosionStrength = GetExplosiveStrength() * (1.0f - (distance / areaOfEffect.Radius()));

		//Kick back from explosion
		if ( !(*itr)->IsFlagSet(EF_NOEXPLOSIONKICKBACK) )
		{
			static Core::ConsoleFloat explosion_kickback_coefficient ( "explosion_kickback_coefficient", 0.5 );

			Math::Vector3D velocity = ((*itr)->GetVelocity() + (displacement * explosionStrength))
									 * explosion_kickback_coefficient;

			//Sanity check for the new velocity
			if ( velocity.Length() > 100.0f )
			{
				velocity.Normalise();
				velocity *= 100.0f;
			}

			displacement.Normalise();
			(*itr)->SetVelocity( velocity );
		}

		//Hurt the other entity based on its proximity to the explosion, and the explosive strength
		(*itr)->Hurt(explosionStrength);

		std::clog << __FUNCTION__ ": Hurt entity " << (*itr)->ID() << " by " << explosionStrength
			<< " radius = " << areaOfEffect.Radius() << std::endl;
	}

}
//End Explosion::OnDeath
