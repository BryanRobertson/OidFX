//======================================================================================
//! @file         Dialogue.h
//! @brief        Class representing a settings dialogue, allowing the user to choose
//!				  a display mode for the game, and to see console output, should things
//!				  go wrong.
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 30 May 2005
//! @copyright    Bryan Robertson 2005
//
//				  This file is part of OidFX Engine.
//
//  			  OidFX Engine is free software; you can redistribute it and/or modify
//  			  it under the terms of the GNU General Public License as published by
//  			  the Free Software Foundation; either version 2 of the License, or
//  			  (at your option) any later version.
//
//  			  OidFX Engine is distributed in the hope that it will be useful,
//  			  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  			  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  			  GNU General Public License for more details.
//
//  			  You should have received a copy of the GNU General Public License
//  			  along with OidFX Engine; if not, write to the Free Software
//  			  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================

#ifndef SETTINGSDIALOGUE_SETTINGSDIALOGUE_H
#define SETTINGSDIALOGUE_SETTINGSDIALOGUE_H

#include <windows.h>
#include "Core/Singleton.h"
#include "Core/EventConnection.h"
#include "Core/ConsoleOutputListener.h"


//=========================================================================
//Forward declarations
//=========================================================================
namespace Renderer { class DisplayModeList; }



//namespace SettingsDialogue
namespace SettingsDialogue
{

	//!@class	IStartFunc
	//!@brief	Interface for a functor object that gets called when
	//!			the Start button of the dialogue is pressed
	class IStartFunc
	{
		public:

			virtual void operator()() = 0;
	};
	//End IStartFunc


	//!@class	IExitFunc
	//!@brief	Interface for a functor object that gets called when
	//!			the Exit button of the dialogue is pressed
	class IExitFunc
	{
		public:

			virtual void operator()() = 0;
	};
	//End IExitFunc


	//!@class	Dialogue
	//!@brief	Class representing a settings dialogue, allowing the user to choose
	//!			a display mode for the game, and to see console output, should things
	//!			go wrong.
	//!
	//!			The settings dialogue is displayed until the renderer can take over
	//!			and display the game window. 
	//!
	//!			The settings dialogue takes two functor objects, to be called when 
	//!			the Start, or Exit buttons are clicked.
	class Dialogue : protected Core::Singleton<Dialogue>, public Core::IConsoleOutputListener
	{
		public:

			//Public methods
			Dialogue ( const Renderer::DisplayModeList& modeList, IStartFunc& startFunc, IExitFunc& exitFunc );
			
			void ShowDialogue();
			void DestroyDialogue();
			void SetupConsoleRedirection();

			//Implementation of IConsoleOutputListener
			void OnConsoleTextOutput ( const Char* text );
			
			//Miscellaneous functions to maniplate the controls on the dialogue
			void InitialiseControls( HWND hWnd );
			void InitialiseColourDepthList();
			void InitialiseFullScreenSetting();

			void ClearDisplayModeList();
			void UpdateDisplayModeList();

			void UpdateModeIndexFromControls();
			void UpdateColourDepthFromControls();
			void UpdateFullScreenFromControls();

		private:
		
			//Private static functions
			static BOOL CALLBACK DialogProc( HWND hwndDlg, UINT uMsg, 
											 WPARAM wParam, LPARAM lParam);

			//Private data
			HWND				m_dialogHwnd;	//!< Window handle for the dialogue
			IStartFunc&			m_startFunc;	//!< Reference to functor called when start button is pressed
			IExitFunc&			m_exitFunc;		//!< Reference to functor called when exit button is pressed
			const Renderer::DisplayModeList& m_modeList; //!< List of display modes

			//Console variables
			Core::ConsoleUInt	m_displayModeIndex;
			Core::ConsoleUInt	m_bitsPerPixel;
			Core::ConsoleBool	m_fullScreen;

			//Handles to dialogue controls
			HWND m_displayModeList;
			HWND m_colourModeList;
			HWND m_fullScreenCheckBox;
			HWND m_consoleDisplay;

			Core::EventConnection m_consoleOutput;

	};
	//End class Dialogue


};
//End namespace SettingsDialogue


#endif
//#ifndef SETTINGSDIALOGUE_SETTINGSDIALOGUE_H
