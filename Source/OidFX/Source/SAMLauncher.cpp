//======================================================================================
//! @file         SAMLauncher.cpp
//! @brief        Class representing a SAM launcher, that fires at the player
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 04 October 2005
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
#include "Math/MatrixStack.h"
#include "OidFX/Scene.h"
#include "OidFX/EntityNode.h"
#include "OidFX/GameApplication.h"
#include "OidFX/MeshManager.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/Constants.h"
#include "OidFX/MissileLauncher.h"
#include "OidFX/TargetingComputer.h"
#include "OidFX/SAMLauncher.h"



using namespace OidFX;



//=========================================================================
// Static initialisation
//=========================================================================
boost::shared_ptr<SAMLauncherCreator> SAMLauncher::ms_samLauncherCreator = boost::shared_ptr<SAMLauncherCreator>();


//=========================================================================
// Static methods
//=========================================================================
boost::shared_ptr<SAMLauncherCreator> SAMLauncher::GetSAMLauncherCreator()
{
	if ( !ms_samLauncherCreator )
	{
		ms_samLauncherCreator = boost::shared_ptr<SAMLauncherCreator>( new SAMLauncherCreator() );
	}

	return ms_samLauncherCreator;
}


//=========================================================================
//! @function    SAMLauncher::SAMLauncher
//! @brief       SAMLauncher constructor
//!
//=========================================================================
SAMLauncher::SAMLauncher ( Scene& scene, 
						   const Char* name,
						   const Math::Matrix4x4& toWorld,
						   const Math::Matrix4x4& fromWorld )
						   :	EntityNode ( scene, 
											 name, 
											 "Data/Art/Models/SAMLauncher.ms3d",
											 toWorld,
											 fromWorld ),
							    m_launchTimeOut(3.0f),
								m_launchTimer(0.0f),
								m_maxTurnRate(10.0f)

{

	
	//Set flags
	SetFlag(EF_ENEMY);
	SetFlag(EF_SPAWNONGROUND);
	//SetFlag(EF_STATIC);
	SetFlag(EF_FLAMMABLE);
	SetFlag(EF_ANTIGRAVITY);
	SetFlag(EF_NOEXPLOSIONKICKBACK);
	
	Core::ConsoleFloat sam_targetrange ( "sam_targetrange", 800.0 );
	Core::ConsoleFloat sam_reloadtime  ( "sam_reloadtime", 1.0f );

	//Create the targeting computer
	m_targetingComputer = boost::shared_ptr<TargetingComputer>( new TargetingComputer(scene) );
	m_targetingComputer->SetFlag( TCF_TARGETPLAYERS );
	m_targetingComputer->SetMaxRange( sam_targetrange * meters );
	m_targetingComputer->SetFlag( TCF_IGNOREANGLE );
	m_targetingComputer->Spawn ( Math::Vector3D(0.0f, 0.0f, 0.0f) );

	//Create two missile launchers
	m_missileLauncher = boost::shared_ptr<MissileLauncher>(new MissileLauncher(scene, *m_targetingComputer,
																			   "Data/Art/Models/Missile.ms3d"));
	
	//Spawn and initialise the missile launchers
	m_missileLauncher->Spawn( Math::Vector3D(0.0f, m_boundingBox.ExtentY(), 0.0f) );
	m_missileLauncher->SetReloadTime( sam_reloadtime );
	m_missileLauncher->SetFlag( MF_INFINITEAMMO );

	AddChild(m_targetingComputer);
	AddChild(m_missileLauncher);

}
//End SAMLauncher::SAMLauncher




//=========================================================================
//! @function    SAMLauncher::Update
//! @brief       Update the SAMLauncher
//!              
//! @param       toWorldStack			[in]  
//! @param       fromWorldStack			[in]  
//! @param       timeElapsedInSeconds	[in]  
//!              
//=========================================================================
void SAMLauncher::Update ( Math::MatrixStack& toWorldStack, 
						   Math::MatrixStack& fromWorldStack, 
						   Float timeElapsedInSeconds )
{

	//SAM will fire at its target if the absolute value of the dot product between
	//the vector from the launcher to the target, and the right vector of the launcher
	//is less than this value
	static Core::ConsoleFloat sam_firethreshold( "sam_firethreshold", 0.3f );

	//Disable enemy fire debug switch
	static Core::ConsoleBool dbg_disableenemyfire ( "dbg_disableenemyfire", false );

	//Rotate the SAMLauncher to face its target
	if ( m_targetingComputer->GetCurrentTarget() 
		&& (!IsFlagSet(EF_DEAD))
		&& (IsFlagSet(EF_SPAWNED)))
	{
		
		//Get the normalised vector from the SAMLauncher to the target
		Math::Vector3D v = m_targetingComputer->GetCurrentTarget()->GetWorldSpacePosition()
							- GetWorldSpacePosition();

		v.Normalise();

		//Get the dot product between v, and our right vector
		Float vDotr = Math::Vector3D::DotProduct( v, Right() );

		//
		m_angularVelocity = Math::Vector3D( 0.0f, Math::DegreesToRadians(10.0f) * -vDotr, 0.0f );

		if ( (vDotr < Math::Abs<Float>(sam_firethreshold))
			&& (!dbg_disableenemyfire))
		{
			LaunchMissile();
		}
	}

	EntityNode::Update( toWorldStack, fromWorldStack, timeElapsedInSeconds );
}
//End SAMLauncher::Update



//=========================================================================
//! @function    SAMLauncher::LaunchMissile
//! @brief       Make the SAMLauncher launch a missile at its target
//!              
//!              
//=========================================================================
void SAMLauncher::LaunchMissile ( )
{
	m_missileLauncher->LaunchMissile();
}
//End SAMLauncher::LaunchMissile



//=========================================================================
//! @function    SAMLauncher::OnSpawn
//! @brief       
//!              
//! @param       spawnPoint 
//!              
//=========================================================================
void SAMLauncher::OnSpawn ( const Math::Vector3D& spawnPoint )
{
	static Core::ConsoleFloat samhealth ( "samhealth", 20.0f );

	ClearFlag(EF_NODRAW);
	ClearFlag(EF_DEAD);

	SetHealth(samhealth);
}
//End SAMLauncher::OnSpawn



//=========================================================================
//! @function    SAMLauncher::OnThink
//! @brief       
//!              
//! @param       timeElapsed 
//!              
//=========================================================================
void SAMLauncher::OnThink ( Float timeElapsed )
{


}
//End SAMLauncher::OnThink



//=========================================================================
//! @function    SAMLauncher::OnTouch
//! @brief       
//!              
//=========================================================================
void SAMLauncher::OnTouch ( )
{
}
//End SAMLauncher::OnTouch



//=========================================================================
//! @function    SAMLauncher::OnEntityCollide
//! @brief       
//!              
//! @param       collisionNormal	[in]	
//! @param       depth				[in]	
//! @param		 entity				[in]	
//! @param		 entityVelocity		[in]	
//!
//!              
//=========================================================================
void SAMLauncher::OnEntityCollide ( const Math::Vector3D& collisionNormal, Float depth, 
						EntityNode& entity, const Math::Vector3D& entityVelocity )
{
}
//End SAMLauncher::OnEntityCollide



//=========================================================================
//! @function    SAMLauncher::OnDeath
//! @brief       
//!             
//=========================================================================
void SAMLauncher::OnDeath ( )
{
	EntityNode::OnDeath();
}
//End SAMLauncher::OnDeath