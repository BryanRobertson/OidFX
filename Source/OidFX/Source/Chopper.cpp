//======================================================================================
//! @file         Chopper.cpp
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

#include "Core/Core.h"
#include "Core/InputSystem.h"
#include "Math/Math.h"
#include "Math/Matrix4x4.h"
#include "Math/MatrixStack.h"
#include "Math/IntersectionTests.h"
#include "OidFX/Scene.h"
#include "OidFX/EntityNode.h"
#include "OidFX/GameApplication.h"
#include "OidFX/MeshManager.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/Constants.h"
#include "OidFX/Chopper.h"
#include "OidFX/MissileLauncher.h"
#include "OidFX/TargetingComputer.h"



using namespace OidFX;


//=========================================================================
// Static initialisation
//=========================================================================
boost::shared_ptr<ChopperEntityCreator> Chopper::ms_chopperCreator = boost::shared_ptr<ChopperEntityCreator>();


//=========================================================================
// Static methods
//=========================================================================
boost::shared_ptr<ChopperEntityCreator> Chopper::GetChopperCreator()
{
	if ( !ms_chopperCreator )
	{
		ms_chopperCreator = boost::shared_ptr<ChopperEntityCreator>( new ChopperEntityCreator() );
	}

	return ms_chopperCreator;
}


//=========================================================================
// Globals
//=========================================================================
const Float g_chopperAcceleration = 7.0f * meters;


//=========================================================================
//! @function    Chopper::Chopper 
//! @brief       Chopper constructor
//!              
//! @param       scene [in] Reference to the scene
//! @param       name  [in] Name of the helicopter
//! @param		 toWorld [in] To world matrix
//! @param		 fromWorld [in] From world matrix
//=========================================================================
Chopper::Chopper ( Scene& scene, 
				   const Char* name,
				   const Math::Matrix4x4& toWorld,
				   const Math::Matrix4x4& fromWorld )
				   : EntityNode ( scene, 
								  name, 
								  "Data/Art/Models/Copter.ms3d",
								  toWorld,
								  fromWorld ),

					m_accelX(0.0f),
					m_accelY(0.0f),
					m_accelZ(0.0f),
					m_launch(false)
{

	Core::ConsoleFloat chopper_targetrange ( "chopper_targetrange", 500.0f );

	//Create the targeting computer
	m_targetingComputer = boost::shared_ptr<TargetingComputer>( new TargetingComputer(scene) );
	m_targetingComputer->Spawn( Math::Vector3D(0.0f, 0.0f, 0.0f) );
	m_targetingComputer->SetFlag( TCF_TARGETENEMIES );
	m_targetingComputer->SetFlag ( TCF_DRAWTARGET );
	m_targetingComputer->SetMaxRange( chopper_targetrange * meters );

	//Create two missile launchers
	m_missileLaunchers.push_back( boost::shared_ptr<MissileLauncher>(new MissileLauncher(scene, *m_targetingComputer,
																						"Data/Art/Models/Missile.ms3d")) );
	m_missileLaunchers.push_back( boost::shared_ptr<MissileLauncher>(new MissileLauncher(scene, *m_targetingComputer,
																						"Data/Art/Models/Missile.ms3d")) );
	
	//At the moment, the missile launchers have a fixed offset. In future versions
	//we'll probably load this from file, but we won't be using much of this chopper
	//code in future versions anyway
	m_missileLaunchers[0]->Spawn( Math::Vector3D(60.0f, 0.0f, 10.0f) );
	m_missileLaunchers[1]->Spawn( Math::Vector3D(-60.0f, 0.0f, 10.0f) );

	m_missileLaunchers[0]->SetAmmunition ( 50 );
	m_missileLaunchers[1]->SetAmmunition ( 50 );

	m_missileLaunchers[0]->SetFlag ( MF_INFINITEAMMO );
	m_missileLaunchers[1]->SetFlag ( MF_INFINITEAMMO );

	AddChild(m_missileLaunchers[0]);
	AddChild(m_missileLaunchers[1]);
	AddChild(m_targetingComputer);

}
//End Chopper::Chopper


//=========================================================================
//! @function    Chopper::Update
//! @brief       Called to update the chopper every frame
//!              
//!              
//! @param       toWorldStack			[in]
//! @param       fromWorldStack			[in]
//! @param       timeElapsedInSeconds	[in]
//!              
//=========================================================================
void Chopper::Update ( Math::MatrixStack& toWorldStack, Math::MatrixStack& fromWorldStack, Float timeElapsedInSeconds )
{

	//Make the chopper accelerate in the direction it is facing

	m_orientation.Normalise();

	//Get the basis vectors from the orientation
	Math::Vector3D forward = Math::Vector3D::ZAxis * m_orientation;
	Math::Vector3D right   = Math::Vector3D::XAxis * m_orientation;
	Math::Vector3D up	   = Math::Vector3D::YAxis * m_orientation;

	forward.Normalise();
	right.Normalise();
	up.Normalise();

	//Update the acceleration based on user input
	m_acceleration += forward * m_accelZ;
	m_acceleration += right	  * m_accelX;
	m_acceleration += up	  * m_accelY;

	//Update orientation
	if ( IsFlagSet(EF_SPAWNED) )
	{
		UpdatePhysics( timeElapsedInSeconds );

		m_orientation.Normalise();
		
		m_objectToWorld.Identity();
		m_objectToWorld *= Math::Matrix4x4 ( m_orientation );
		m_objectToWorld.Translate ( m_position );
		
		m_objectFromWorld.Identity();
		m_objectFromWorld *= Math::Matrix4x4 ( -m_orientation );
		m_objectFromWorld.Translate ( -m_position );
	}

	SceneObject::Update( toWorldStack, fromWorldStack, timeElapsedInSeconds );

	//If the launch button was pressed, then launch a missile
	static Float timeSinceLastLaunch = 1000.0f;	
	timeSinceLastLaunch += timeElapsedInSeconds;
	
	static Core::ConsoleFloat copter_minlaunchwindow ( "copter_minlaunchwindow", 1.0f );

	if ( (m_launch) && (timeSinceLastLaunch > copter_minlaunchwindow) )
	{
		LaunchMissile();

		timeSinceLastLaunch = 0.0f;
	}

	//Clear out the acceleration
	m_acceleration.Set ( 0.0f, 0.0f, 0.0f );
	m_angularAcceleration.Set ( 0.0f, 0.0f, 0.0f );

	m_accelX = 0.0f;
	m_accelY = 0.0f;
	m_accelZ = 0.0f;

	m_launch = false;

	OnThink ( timeElapsedInSeconds );
}
//End Chopper::Update



//=========================================================================
//! @function    Chopper::LaunchMissile
//! @brief       Launch a missile if possible
//=========================================================================
void Chopper::LaunchMissile ( )
{

	static UInt currentLauncher = 0;

	debug_assert( m_missileLaunchers[currentLauncher], "Missile launcher does not exist!" );


	m_missileLaunchers[currentLauncher]->LaunchMissile();

	//Alternate between the different missile launchers
	currentLauncher = (currentLauncher + 1) % m_missileLaunchers.size();

}
//End Chopper::LaunchMissile



//=========================================================================
//! @function    Chopper::OnSpawn
//! @brief		 Event handler for chopper spawn
//!
//! @param		 spawnPoint [in] 
//=========================================================================
void Chopper::OnSpawn ( const Math::Vector3D& spawnPoint )
{
	SetFlag ( EF_PLAYER );
	SetFlag ( EF_ANTIGRAVITY );
	
	static Core::ConsoleFloat chopper_inithealth( "chopper_inithealth", 300.0f );
	SetHealth ( chopper_inithealth );

	static Core::ConsoleBool cam_firstperson ( "cam_firstperson", false );

	if ( !cam_firstperson )
	{
		//Register this object as a window mouse and keyboard handler
		m_mouseConnection	 = m_scene.Application().GetInputSystem().RegisterMouseHandler(*this);
		m_keyboardConnection = m_scene.Application().GetInputSystem().RegisterKeyboardHandler(*this);
	}

}
//End Chopper::OnSpawn



//=========================================================================
//! @function    Chopper::OnThink
//! @brief       Called every frame to update chopper AI
//!              
//! @param       timeElapsed [in]
//!              
//=========================================================================
void Chopper::OnThink ( Float timeElapsed )
{

	//If the chopper is dead, then make it rotate around its y axis,
	//as if its tail rotor was damaged
	if ( IsFlagSet(EF_DEAD) )
	{
		m_angularAcceleration += Math::Vector3D( 0.0f, 2.0f * timeElapsed, 0.0f );
	}
}
//End Chopper::OnThink



//=========================================================================
//! @function    Chopper::OnTouch
//! @brief       Called when the chopper hits the player. Since the chopper 
//!              is the player, this doesn't actually do anything
//!              
//=========================================================================
void Chopper::OnTouch ( )
{

}
//End Chopper::OnTouch


//=========================================================================
//! @function    Chopper::OnWorldCollide
//! @brief       Called when the chopper collides with the world
//!              
//! @param       collisionNormal [in] Normal of collision surface
//! @param		 depth			 [in] Depth that the object has penetrated the surface
//=========================================================================
void Chopper::OnWorldCollide (  const Math::Vector3D& collisionNormal, Float depth )
{

	if ( IsFlagSet(EF_DEAD) )
	{
		//Make the helicopter explode if it hits the ground, and it's dead
		Explode();
	}

	m_position -= m_velocity;

	//Project -velocity onto the collision normal 
	Float proj = Math::Vector3D::DotProduct(-m_velocity, collisionNormal);

	//Get the reflection vector
	Math::Vector3D reflect = (collisionNormal * proj) * 2.0f;

	//Make the chopper bounce back from the terrain a bit
	m_velocity =  reflect + m_velocity;

	m_position += m_velocity;
}
//End Chopper::OnWorldCollide



//=========================================================================
//! @function    Chopper::OnEntityCollide
//! @brief       Called when the chopper collides with an entity
//!              
//! @param		 collisionNormal [in] Normal of the point of collision
//! @param		 depth			 [in] Depth of penetration into the collision plane
//! @param       entity			 [in] Entity that collided with this one
//! @param		 entityVelocity  [in] Velocity of the entity at time of collision
//!              
//=========================================================================
void Chopper::OnEntityCollide ( const Math::Vector3D& collisionNormal, Float depth, 
								EntityNode& entity, const Math::Vector3D& entityVelocity )
{
	//Cheap collision response! 
	//m_position -= collisionNormal * (depth+0.1f);

	//Project -velocity onto the collision normal 
	Float proj = Math::Vector3D::DotProduct(-m_velocity, collisionNormal);

	//Get the reflection vector
	Math::Vector3D reflect = (collisionNormal * proj) * 2.0f;

	//Make the chopper bounce back from the object a bit
	m_velocity =  reflect + m_velocity;

	m_position += m_velocity;

}
//End Chopper::OnEntityCollide



//=========================================================================
//! @function    Chopper::OnDeath
//! @brief       Called when the chopper dies
//!              
//=========================================================================
void Chopper::OnDeath ( )
{
	//Clear the antigravity flag so that the chopper falls under gravity
	ClearFlag ( EF_ANTIGRAVITY );

	//Kill the keyboard and mouse controls
	m_mouseConnection.Disconnect();
	m_keyboardConnection.Disconnect();
}
//End Chopper::OnDeath



//=========================================================================
//! @function    Chopper::OnMouseMove
//! @brief       Called when the mouse is moved
//!              
//! @param       movementX 
//! @param       movementY 
//!              
//! @return      
//! @throw       
//=========================================================================
void Chopper::OnMouseMove ( Int movementX, Int movementY )
{

	Core::ConsoleFloat gam_copterrotatefactor ( "gam_copterrotatefactor", 0.8f );

	m_angularAcceleration += Math::Vector3D ( 0.0f,
											  Math::DegreesToRadians(-movementX * gam_copterrotatefactor), 
											  0.0f );
}
//End Chopper::OnMouseMove


//=========================================================================
//! @function    Chopper::OnMouseButtonDown
//! @brief       Called when a mouse button is pressed
//!              
//! @param       buttonIndex [in] Button that was pressed
//!              
//=========================================================================
void Chopper::OnMouseButtonDown ( UInt buttonIndex )
{
	switch ( buttonIndex )
	{
		case Core::MOUSEBUTTON_LEFT:

			m_launch = true;

		break;
	}
}
//End Chopper::OnMouseButtonDown



//=========================================================================
//! @function    Chopper::OnMouseButtonUp
//! @brief       Called when mouse button is released
//!              
//! @param       buttonIndex [in] button that was released
//!              
//=========================================================================
void Chopper::OnMouseButtonUp ( UInt buttonIndex )		
{
}
//End Chopper::OnMouseButtonUp



//=========================================================================
//! @function    Chopper::OnMouseScroll
//! @brief       Called when the mouse scroll wheel is moved
//!              
//! @param       scroll 
//!              
//=========================================================================
void Chopper::OnMouseScroll	( Int scroll )				
{

}
//End Chopper::OnMouseScroll


//=========================================================================
//! @function    Chopper::OnKeyDown
//! @brief       Called when a key is pressed
//!              
//! @param       keyCode [in] Key code of key that was pressed
//!              
//=========================================================================
void Chopper::OnKeyDown ( UInt keyCode )					
{
	
	switch ( keyCode )
	{
		case Core::KEY_W:
			m_accelZ += -g_chopperAcceleration;
			break;

		case Core::KEY_S:
			m_accelZ += g_chopperAcceleration;
			break;

		case Core::KEY_A:
			m_accelX += 0.5f * -g_chopperAcceleration;
			break;

		case Core::KEY_D:
			m_accelX += 0.5f * g_chopperAcceleration;
			break;

		case Core::KEY_R:
			m_accelY += 0.8f * g_chopperAcceleration;
			break;

		case Core::KEY_F:
			m_accelY -= 0.8f * g_chopperAcceleration;
			break;

		case Core::KEY_SPACE:
			m_launch = true;
			break;

	}

}
//End Chopper::OnKeyDown


//=========================================================================
//! @function    Chopper::OnKeyUp
//! @brief       Called when a key is released
//!              
//! @param       keyCode [in] Key code of key that was released
//!              
//=========================================================================
void Chopper::OnKeyUp ( UInt keyCode )					
{
}
//End Chopper::OnKeyUp


