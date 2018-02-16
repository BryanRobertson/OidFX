//======================================================================================
//! @file         TargetingComputer.cpp
//! @brief        Class representing the targeting computer in an entity which
//!               can fire projectiles.
//!
//!				  The targeting computer searches the immediate area for targetable entities
//!				  and assigns a target.
//!
//!				  In future versions, this will be used to draw a target billboard over
//!               the target
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 06 September 2005
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
#include "Renderer/EffectManager.h"
#include "OidFX/Constants.h"
#include "OidFX/Scene.h"
#include "OidFX/TargetingComputer.h"
#include "OidFX/GameApplication.h"
#include "OidFX/BillboardManager.h"



using namespace OidFX;


//=========================================================================
//! @function    TargetingComputer::TargetingComputer
//! @brief       
//!              
//! @param       scene [in]
//!              
//=========================================================================
TargetingComputer::TargetingComputer ( Scene& scene )
: EntityNode(scene, "Target-O-Tron-3000", "" ),
  m_currentTarget(0),
  m_timeSinceLastUpdate(0.0f),
  m_targetDisplay( scene.Application().GetEffectManager().AcquireEffect("Data/Art/Effects/Target.ofx") )
{

	m_maxRange = 100.0f * meters;


	SetFlag( EF_NODRAW );
	SetFlag( EF_NOCOLLIDE );
	SetFlag( EF_INVINCIBLE );
	SetFlag( EF_ANTIGRAVITY );
	SetFlag( EF_NOEXPLOSIONKICKBACK );

	m_targetDisplay.SetRotateAnim( Math::DegreesToRadians(40.0f) );
	
	m_targetDisplay.AddWaveTransform ( Billboard::XFORM_SCALE, 
									   Billboard::WAVE_SINE,
									   300.0f,
									   1.0f,
									   0.0f,
									   100.0f );
}
//End TargetingComputer::TargetingComputer



//=========================================================================
//! @function    TargetingComputer::Update
//! @brief       Update the targeting computer
//!              
//! @param       toWorldStack 
//! @param       fromWorldStack 
//! @param       timeElapsedInSeconds 
//!              
//=========================================================================
void TargetingComputer::Update ( Math::MatrixStack& toWorldStack,
								Math::MatrixStack& fromWorldStack,
								Float timeElapsedInSeconds )
{
	EntityNode::Update ( toWorldStack, fromWorldStack, timeElapsedInSeconds );

	m_timeSinceLastUpdate += timeElapsedInSeconds;

	if ( m_timeSinceLastUpdate > 1.0f )
	{
		AcquireTarget();
		m_timeSinceLastUpdate = 0.0f;
	}

	if ( IsFlagSet(TCF_DRAWTARGET) && GetCurrentTarget() )
	{
		m_targetDisplay.Update( timeElapsedInSeconds );
		m_targetDisplay.SetPosition( GetCurrentTarget()->BoundingBox().GetCentre() );
		m_scene.Application().GetBillboardManager().AddToBillboardList(m_targetDisplay);

	}
}
//End TargetingComputer::Update



//=========================================================================
//! @function    TargetingComputer::AcquireTarget
//! @brief       Find the closest target
//!              
//!              
//=========================================================================
void TargetingComputer::AcquireTarget ( )
{

	EntityNode* closestTarget = 0;
	Float distanceSquared = std::numeric_limits<Float>::max();

	//Find all entities within the target radius
	EntityQueryResult results;
	Math::BoundingSphere3D targetRadius( GetMaxRange(), BoundingBox().GetCentre() );
	m_scene.QueryScene ( targetRadius, results );

	//Find the closest target
	for ( EntityQueryResult::iterator itr = results.begin();
		  itr != results.end();
		  ++itr )
	{
		if ( CanTarget(*itr) )
		{
			Math::Vector3D v = (*itr)->BoundingBox().GetCentre() - BoundingBox().GetCentre();
			Float currentDistanceSquared = v.LengthSquared();

			static Core::ConsoleFloat target_threshold( "target_threshold", 0.7f );

			//Only target the object if it's within our view cone
			if (   ( IsFlagSet(TCF_IGNOREANGLE) )
				|| (Math::Vector3D::DotProduct( -Forward(), v.Normalise() ) >= target_threshold) )
			{
				if ( currentDistanceSquared < distanceSquared )
				{
					closestTarget = *itr;
					distanceSquared = currentDistanceSquared;
				}
			}
		}
	}

	m_currentTarget = closestTarget;
}
//End  TargetingComputer::AcquireTarget



//=========================================================================
//! @function    TargetingComputer::CanTarget
//! @brief       Indicates whether or not the targeting computer can target the entity
//!              
//! @param       entity [in]
//!              
//! @return      true if the targeting computer can target this entity, false otherwise
//=========================================================================
bool TargetingComputer::CanTarget ( const EntityNode* entity ) const
{
	if (  (!entity->IsFlagSet(EF_DEAD)) 
			&& (!entity->IsFlagSet(EF_DESPAWNPENDING))
			&& (!entity->IsFlagSet(EF_PROJECTILE)) )
	{

		if  (   (entity->IsFlagSet(EF_PLAYER) && IsFlagSet(TCF_TARGETPLAYERS))
			|| (entity->IsFlagSet(EF_ALLY)	 && IsFlagSet(TCF_TARGETALLIES))
			|| (entity->IsFlagSet(EF_ENEMY)	 && IsFlagSet(TCF_TARGETENEMIES)))
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}
//End TargetingComputer::CanTarget