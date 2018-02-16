//======================================================================================
//! @file         Game.h
//! @brief        Class encapsulating the helicopter game
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


#ifndef TERRAINDEMO_GAME_H
#define TERRAINDEMO_GAME_H


#include "Renderer/Font.h"
#include "OidFX/EntityDeathEvent.h"


//=========================================================================
// Forward declarations
//=========================================================================


//namespace TerrainDemo
namespace TerrainDemo
{


	//!@class	Game
	//!@brief	Class encapsulating the gameplay of the helicopter game
	class Game : 
				 public OidFX::IEntityDeathSensitive,
				 public Core::IKeyboardSensitive,
				 public Core::IMouseSensitive
	{

		public:

            //=========================================================================
            // Constructor
            //=========================================================================
			Game( OidFX::GameApplication& application, OidFX::Scene& scene );


            //=========================================================================
            // Public methods
            //=========================================================================
			void Update ( Float timeElapsedInSeconds );

			void DisplayText ( Renderer::HFont font );

			//Input handling
			void OnKeyDown ( UInt keyCode );
			void OnChar	   ( Char charValue, UInt repeats, bool prevKeyState );
			void OnKeyUp   ( UInt keyCode );

			void OnMouseMove		( Int movementX, Int movementY );
			void OnMouseButtonDown  ( UInt buttonIndex ); 
			void OnMouseButtonUp	( UInt buttonIndex );
			void OnMouseScroll		( Int scroll );

			void OnEntityDeath ( OidFX::EntityNode* entity );

		private:


            //=========================================================================
            // Private types
            //=========================================================================
			enum GameState
			{
				GAMESTATE_INTRO,
				GAMESTATE_MAIN,
				GAMESTATE_OVERLOSE,
				GAMESTATE_OVERWIN
			};

            //=========================================================================
            // Private methods
            //=========================================================================
			
			//One time initialisation of the game
			void Initialise ( );

			//The following methods are called to update the different game states
			void GameIntro ( Float timeElapsedInSeconds );		// The intro before the game starts
			void GameMain  ( Float timeElapsedInSeconds );		// The main game
			void GameOverLose  ( Float timeElapsedInSeconds );	// Game over, player has lost
			void GameOverWin   ( Float timeElapsedInSeconds );	// Game over, player has won

			void CleanUpForNextGame ( );

			inline void SetGameState ( GameState state );

            //=========================================================================
            // Private data
            //=========================================================================
			OidFX::GameApplication&					m_application;
			OidFX::Scene&							m_scene;

			//Game related
			boost::shared_ptr<OidFX::EntityNode>	m_player;
			GameState								m_state;

			//Input related
			Core::EventConnection					m_keyboardConnection;
			Core::EventConnection					m_mouseConnection;

			//Misc game stuff
			bool									m_startGame;

			//Score
			Float									m_time;
			Float									m_bestTime;
			bool									m_newRecord;

			//Time spent in current state
			Float									m_currentStateTimer;

			Core::Vector<Core::EventConnection>::Type		m_samDeathHandlers;
			UInt											m_deadSAMCount;

	};
	//End class Game



    //=========================================================================
    //! @function    Game::SetGameState
    //! @brief       Set the current game state, and reset the timer for the length of
    //!              time spent in the current state
    //!              
    //!              
    //! @param       state [in] new game state
    //!              
    //=========================================================================
	void Game::SetGameState( Game::GameState state )
	{
		m_state = state;
		m_currentStateTimer = 0.0f;

		m_startGame = false;
	}
	//End Game::SetGameState



}
//end namespace TerrainDemo


#endif
//#ifndef OIDFX_GAME_H

