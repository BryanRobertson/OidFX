//======================================================================================
//! @file         Game.cpp
//! @brief        Class encapsulating the helicopter game
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


#include "Core/Core.h"
#include "Core/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/EffectManager.h"
#include "OidFX/Scene.h"
#include "OidFX/GameApplication.h"
#include "OidFX/EntityNode.h"
#include "OidFX/EntityManager.h"
#include "OidFX/EntityFactory.h"
#include "OidFX/Chopper.h"
#include "OidFX/TreeEntity.h"
#include "OidFX/SAMLauncher.h"
#include "OidFX/Explosion.h"
#include "TerrainDemo/Game.h"



using namespace TerrainDemo;



//=========================================================================
//! @function    Game::Game
//! @brief       Game constructor
//!              
//! @param       application [in]	
//! @param       scene		 [in]	
//!              
//=========================================================================
Game::Game( OidFX::GameApplication& application, OidFX::Scene& scene )
: m_application(application), 
  m_scene(scene),
  m_state(GAMESTATE_INTRO),
  m_time(0.0f),
  m_bestTime(38.0f),
  m_currentStateTimer(0.0f),
  m_newRecord(false)
{

	//Register entity creators with the entity factory
	scene.GetEntityManager().RegisterType ( OidFX::Chopper::GetChopperCreator() );
	scene.GetEntityManager().RegisterType ( OidFX::TreeEntity::GetTreeCreator() );
	scene.GetEntityManager().RegisterType ( OidFX::SAMLauncher::GetSAMLauncherCreator() );
	scene.GetEntityManager().RegisterType ( OidFX::Explosion::GetExplosionCreator() );

	//Register this object as a window mouse and keyboard handler
	m_mouseConnection = scene.Application().GetInputSystem().RegisterMouseHandler(*this);
	m_keyboardConnection = scene.Application().GetInputSystem().RegisterKeyboardHandler(*this);

	//Call CleanUpForNextGame so that the intro screen is set up properly
	CleanUpForNextGame();

	//Precache any resources we need
	m_scene.Application().PrecacheResources();
}
//End Game::Game



//=========================================================================
//! @function    Game::Update
//! @brief       Called every frame to update the game
//!              
//! @param       timeElapsedInSeconds [in]
//=========================================================================
void Game::Update ( Float timeElapsedInSeconds )
{

	switch ( m_state )
	{
		case GAMESTATE_INTRO:
			GameIntro( timeElapsedInSeconds );
			break;

		case GAMESTATE_MAIN:
			GameMain ( timeElapsedInSeconds );
			break;

		case GAMESTATE_OVERLOSE:
			GameOverLose( timeElapsedInSeconds );
			break;

		case GAMESTATE_OVERWIN:
			GameOverWin( timeElapsedInSeconds );
			break;

		default:
			debug_error("Invalid game state!" );
			break;
	}

	//Update the amount of time we have spent in the current state
	m_currentStateTimer += timeElapsedInSeconds;

}
//End Game::Update



//=========================================================================
//! @function    Game::Initialise
//! @brief       Initialises the game
//!
//!				 Spawns all entities, ready for a new game              
//=========================================================================
void Game::Initialise ( )
{
	m_scene.GetEntityManager().DespawnAll();

	//Create the player, and set the camera to target them
	m_player = m_scene.GetEntityManager().SpawnEntity( "Chopper", Math::Vector3D(7052.0f, 1980.0f, 5216.0f) );
	m_scene.Application().GetCamera().SetTargetEntity ( m_player );
	m_scene.Application().GetCamera().SetOffset( Math::Vector3D(0.0f, 200.0f, 250.0f) );

	//Set the camera to its ideal position, so that it doesn't interpolate
	//between its current position, and its new position, looking at the player's helicopter
	m_scene.Application().GetCamera().SetToIdealPosition();

	//Clear the score
	m_time = 0.0f;

	//Clear the new record, so we'll know if the player breaks the record next time
	m_newRecord = false;

	//Create some trees
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 5075, 1270, 6517 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 5275, 1270, 6617 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 5375, 1270, 6417 ));

	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 7484, 438, 5396 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 2370, 1047, 2326 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 5679, 607, 1024 ));

	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 150, 700, -730 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 250, 700, -630 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 190, 700, -530 ));

	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 3374, 700, 1667 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 3374, 700, 1867 ));
	m_scene.GetEntityManager().SpawnEntity( "Tree", Math::Vector3D ( 3574, 700, 1867 ));

	//Spawn all SAM launchers, and register event handlers for their deaths
	m_samDeathHandlers.clear();

	m_samDeathHandlers.push_back(
		m_scene.GetEntityManager().SpawnEntity( "SAMLauncher", Math::Vector3D ( 3841, 700, -876 ))->RegisterDeathHandler( *this )
	);

	m_samDeathHandlers.push_back(
		m_scene.GetEntityManager().SpawnEntity( "SAMLauncher", Math::Vector3D ( -1523, 700, -3248 ))->RegisterDeathHandler( *this )
	);

	m_samDeathHandlers.push_back(
		m_scene.GetEntityManager().SpawnEntity( "SAMLauncher", Math::Vector3D ( 1390, 200, -7538 ))->RegisterDeathHandler( *this )
	);

	m_samDeathHandlers.push_back(
		m_scene.GetEntityManager().SpawnEntity( "SAMLauncher", Math::Vector3D ( -3777, 900, -10624 ))->RegisterDeathHandler( *this )
	);

	m_samDeathHandlers.push_back(
		m_scene.GetEntityManager().SpawnEntity( "SAMLauncher", Math::Vector3D ( -5158, 2600, -14600 ))->RegisterDeathHandler( *this )
	);
	
	m_samDeathHandlers.push_back(
		m_scene.GetEntityManager().SpawnEntity( "SAMLauncher", Math::Vector3D ( 4625, 700, -17044 ))->RegisterDeathHandler( *this )
	);


	//HACK - will fix this later, but at the moment this is needed to 
	//		 keep the explosion effect in memory at all times
	boost::shared_ptr<OidFX::EntityNode> explosion 
			= m_scene.GetEntityManager().SpawnEntity( "Explosion", Math::Vector3D(0.0f, 9999999.0f, 0.0f) );

	explosion->SetExplosiveStrength(0);
	
	//Change this if the number of SAMLaunchers changes
	m_deadSAMCount = 0;

	//Precache all required resources
	m_scene.Application().PrecacheResources();

}
//End Game::Initialise


//=========================================================================
//! @function    Game::OnEntityDeath
//! @brief       Event handler for entity death
//!              
//! @param       entity 
//!              
//=========================================================================
void Game::OnEntityDeath ( OidFX::EntityNode* entity )
{
	++m_deadSAMCount;

	if ( (m_samDeathHandlers.size() == m_deadSAMCount) && (GAMESTATE_MAIN == m_state) )
	{
		SetGameState(GAMESTATE_OVERWIN);
	}
}
//End Game::OnEntityDeath


//=========================================================================
//! @function    Game::DisplayText
//! @brief       Display any in-game text
//!              
//! @param       font [in] Font to use
//!              
//=========================================================================
void Game::DisplayText ( Renderer::HFont font )
{

	switch ( m_state )
	{

		case GAMESTATE_OVERLOSE:
			font->WriteText ( "Your helicopter was destroyed, you lose.\n\n"
							  "Better luck next time.",
							  150.0f, 150.0f );
			break;

		case GAMESTATE_OVERWIN:

			if ( m_newRecord )
			{
				font->WriteText ( "Congratulations!\n"
								  "You've set a new time record!\n\n",
								  250.0f, 150.0f );
			}
			else
			{
				font->WriteText ( "No new time record for you!\n\n"
									  "Better luck next time",
								250.0f, 150.0f );
			}

			break;

		case GAMESTATE_INTRO:
			font->WriteText ( "Helicopter demo:\n\n"
							  "Destroy all the missile launchers in\n"
							  "the shortest time possible\n\n"
							  "Press any key to play\n",
							  250.0f, 150.0f );
			
			//Fall through to the next case statement
			//so that instructions are printed in 
			//both intro mode, and in main mode

		case GAMESTATE_MAIN:
			font->WriteText ( "Controls:\n"
								"W - Forward\n"
								"S - Backward\n"
								"A - Strafe left\n"
								"D - Strafe right\n"
								"R - Gain height\n"
								"F - Lose height\n"
								"Esc - Exit program\n\n"
								"Mouse Move - Turn\n"
								"Mouse1 - Fire Missile\n", 50.0, 290.0 );
			break;

	}

	//Write the score, and best score
	static Core::PooledStringStream text;
	text.str("");
	text << "Time: " << m_time << " sec\n"
		<< "Best : " << m_bestTime << " sec";

	// HACK
	//
	//Perhaps in the next version we will have some kind of system where the game can get access to 
	//variables like the screen width, without doing evil things like this
	font->WriteText ( text.str().c_str(), 
					  static_cast<Float>(m_scene.Application().GetRenderer().ScreenWidth()) - 250.0f
					  , 50.0f );

	if ( m_player && (GAMESTATE_MAIN == m_state) )
	{
		//Display the player's health
		text.str("");
		text << "Health: " << m_player->GetHealth();

		font->WriteText ( text.str().c_str(), 
						static_cast<Float>(m_scene.Application().GetRenderer().ScreenWidth()) - 250.0f
						, 150.0f );

		text.str("");
		text << "SAMS left: " << (m_samDeathHandlers.size() - m_deadSAMCount);

		font->WriteText ( text.str().c_str(), 
						static_cast<Float>(m_scene.Application().GetRenderer().ScreenWidth()) - 250.0f
						, 200.0f );


	}


}
//End Game::DisplayText



//=========================================================================
//! @function    Game::GameIntro
//! @brief       Update the game state for intro mode
//!              
//! @param       timeElapsedInSeconds [in]
//!              
//=========================================================================
void Game::GameIntro ( Float timeElapsedInSeconds )
{
	if ( (true == m_startGame) && ( m_currentStateTimer > 1.0f ) )
	{
		Initialise();
		SetGameState( GAMESTATE_MAIN );
	}
}
//End Game::GameIntro



//=========================================================================
//! @function    Game::GameMain
//! @brief       Update the game state for game mode
//!              
//! @param       timeElapsedInSeconds [in]
//!           
//=========================================================================
void Game::GameMain ( Float timeElapsedInSeconds )
{

	m_time += timeElapsedInSeconds;

	if ( m_player->IsFlagSet(OidFX::EF_DEAD) )
	{
		SetGameState(GAMESTATE_OVERLOSE);
	}
}
//End Game::GameMain



//=========================================================================
//! @function    Game::GameOverLose
//! @brief       Update the game state for game over, lose state
//!              
//! @param       timeElapsedInSeconds [in]
//!              
//=========================================================================
void Game::GameOverLose ( Float timeElapsedInSeconds )
{
	if (  m_currentStateTimer > 5.0f )
	{
		Initialise();
		SetGameState( GAMESTATE_INTRO );
		CleanUpForNextGame();
	}
}
//End Game::GameOverLose



//=========================================================================
//! @function    Game::GameOverWin
//! @brief       Update the game state for game over, win state
//!              
//! @param       timeElapsedInSeconds [in]
//!              
//=========================================================================
void Game::GameOverWin ( Float timeElapsedInSeconds )
{

	if ( m_time < m_bestTime )
	{
		m_bestTime = m_time;
		m_newRecord = true;
	}

	if ( m_currentStateTimer > 5.0f )
	{
		Initialise();
		SetGameState( GAMESTATE_INTRO );
		CleanUpForNextGame();
	}
}
//End Game::GameOverWin



//=========================================================================
//! @function    Game::CleanUpForNextGame
//! @brief		 Clean up the game state for the next game
//!              
//=========================================================================
void Game::CleanUpForNextGame ( )
{

	m_scene.GetEntityManager().DespawnAll();

	//Spawn a tree, and point the camera at it (for the intro screen)
	boost::shared_ptr<OidFX::EntityNode> tree = m_scene.GetEntityManager().SpawnEntity( "Tree", 
																						Math::Vector3D ( 2474, 900, 1368 ));

	m_scene.Application().GetCamera().SetTargetEntity ( tree );
	m_scene.Application().GetCamera().SetOffset ( Math::Vector3D( 0.0f, 500.0f, -900.0f ) );

	//Set the camera to its ideal position, so that it doesn't interpolate
	//between its current position, and its new position, looking at the tree
	m_scene.Application().GetCamera().SetToIdealPosition();

}
//End Game::CleanUpForNextGame



//=========================================================================
//! @function    Game::OnKeyDown
//! @brief       React to a key being pushed down
//!              
//! @param       keyCode [in] Key code of the key that was pressed
//!              
//=========================================================================
void Game::OnKeyDown ( UInt keyCode )
{

	m_startGame = true;

}
//End Game::OnKeyDown


//=========================================================================
//! @function    Game::OnChar
//! @brief       React to to a readable character being pressed on the keyboard
//!              
//! @param       charValue	  [in]
//! @param       repeats	  [in]
//! @param       prevKeyState [in]
//!              
//=========================================================================
void Game::OnChar ( Char charValue, UInt repeats, bool prevKeyState )
{
}
//End Game::OnChar


//=========================================================================
//! @function    Game::OnKeyUp
//! @brief       React to a readable character being released on the keyboard
//!              
//! @param       keyCode [in]
//!              
//=========================================================================
void Game::OnKeyUp ( UInt keyCode )
{
	m_startGame = false;
}
//End Game::OnKeyUp


//=========================================================================
//! @function    Game::OnMouseMove
//! @brief       React to the mouse being moved
//!              
//! @param       movementX 
//! @param       movementY 
//!              
//=========================================================================
void Game::OnMouseMove ( Int movementX, Int movementY )
{
}
//End Game::OnMouseMove


//=========================================================================
//! @function    Game::OnMouseButtonDown
//! @brief       React to a mouse button being pressed
//!              
//! @param       buttonIndex [in]
//!              
//=========================================================================
void Game::OnMouseButtonDown ( UInt buttonIndex )
{
}
//End Game::OnMouseButtonDown



//=========================================================================
//! @function    Game::OnMouseButtonUp
//! @brief       React to a mouse button being released
//!              
//! @param       buttonIndex [in]
//!              
//=========================================================================
void Game::OnMouseButtonUp ( UInt buttonIndex )
{
}
//End Game::OnMouseButtonUp



//=========================================================================
//! @function    Game::OnMouseScroll
//! @brief       React to the mouse scroll wheel being moved
//!              
//!              
//! @param       scroll [in] 
//!              
//=========================================================================
void Game::OnMouseScroll ( Int scroll )
{
}
//End Game::OnMouseScroll