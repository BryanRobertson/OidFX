//======================================================================================
//! @file         Dialogue.cpp
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


#include "Resources/Resources.h"
#include <iostream>
#include <cstring>
#include <windows.h>
#include "Core/Core.h"
#include "SettingsDialogue/Dialogue.h"
#include "Renderer/DisplayModeList.h"
#include "Renderer/DisplayMode.h"



using namespace SettingsDialogue;



//=========================================================================
//! @function    Dialogue::Dialogue
//! @brief       Dialogue constructor
//!              
//! @param       modeList	[in] List of display modes the 
//!								 renderer supports
//! @param       startFunc	[in] Functor object called when the dialogue's 
//!								 "Start" button is clicked
//! @param		 exitFunc	[in] Functor object called when the dialogue's 
//!								 "Exit" button is clicked
//!              
//=========================================================================
Dialogue::Dialogue( const Renderer::DisplayModeList& modeList, 
				    IStartFunc& startFunc,
					IExitFunc& exitFunc )
: Core::Singleton<Dialogue>(this), m_modeList(modeList), m_startFunc(startFunc), m_exitFunc(exitFunc),
  m_displayModeList(0), m_colourModeList(0), m_fullScreenCheckBox(0), m_consoleDisplay(0),
  m_displayModeIndex("init_mode", 0), m_bitsPerPixel("init_bpp", 32), m_fullScreen("init_fullscreen", false)
{

}
//End Dialogue::Dialogue


//=========================================================================
//! @function    Dialogue::ShowDialogue
//! @brief       Shows the dialogue, and blocks until the dialogue is closed
//!              
//=========================================================================
void Dialogue::ShowDialogue()
{
	LoadLibrary("Resources.dll");

	Int errorVal =  DialogBoxParam(GetModuleHandle("Resources.dll"), MAKEINTRESOURCE(IDD_SETTINGSDIALOGUE), 

		NULL, DialogProc, 0);

	if ( (errorVal == 0) || (errorVal == -1) )
	{
		throw Core::RuntimeError("Error, couldn't create settings dialogue window!", GetLastError(),
						 __FILE__, __FUNCTION__, __LINE__ );
	}
}
//End Dialogue::ShowDialogue()



//=========================================================================
//! @function    Dialogue::DestroyDialogue
//! @brief       Destroy the dialogue window
//!				 Calling this method will result in 
//=========================================================================
void Dialogue::DestroyDialogue()
{
	INT result = 1;
	EndDialog(m_dialogHwnd, reinterpret_cast<INT_PTR>(&result) );
}
//End Dialogue::DestroyDialogue



//=========================================================================
//! @function    Dialogue::SetupConsoleRedirection
//! @brief       Redirect console output to our dialogue
//!              
//!              
//=========================================================================
void Dialogue::SetupConsoleRedirection()
{
	m_consoleOutput = Core::Console::GetSingleton().AddOutputListener(*this);
}
//End Dialogue::SetupConsoleRedirection()


//=========================================================================
//! @function    Dialogue::OnConsoleTextOutput
//! @brief       Update the console display when text is written to the console
//!              
//! @param       text [in] Text that was written to the console
//!              
//=========================================================================
void Dialogue::OnConsoleTextOutput ( const Char* text )
{

	if ( text == 0 )
	{
		return;
	}

	//Make a copy of the string and replace \n with \r\n
	std::string str;
	while ( *text != '\0' )
	{
		if (*text == '\n' )
		{
			str += "\r\n";
		}
		else
		{
			str.push_back(*text);
		}

		++text;
	}

	//Append the text to the end of the text box, by selecting the last
	//character and replacing the selection
	Int length = GetWindowTextLength(m_consoleDisplay);
	SendMessage(m_consoleDisplay, EM_SETSEL,    (WPARAM)length, (LPARAM)(length));
	SendMessage(m_consoleDisplay, EM_REPLACESEL,(WPARAM)FALSE, (LPARAM)(str.c_str()));
	SendMessage(m_consoleDisplay, EM_SCROLLCARET,(WPARAM)FALSE, (LPARAM)FALSE);

	length = GetWindowTextLength(m_consoleDisplay);

	//Scroll to the bottom of the text window
	SendMessage ( m_consoleDisplay, EM_LINESCROLL, 0, length );

}
//End Dialogue::OnConsoleTextOutput



//=========================================================================
//! @function    Dialogue::DialogProc
//! @brief       
//!              
//! @param       hwndDlg [in]
//! @param       uMsg	 [in]
//! @param       wParam  [in]
//! @param       lParam  [in]
//!              
//! @return      
//! @throw       
//=========================================================================
BOOL CALLBACK Dialogue::DialogProc( HWND hwndDlg, UINT uMsg, 
									WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

		case WM_INITDIALOG:
			Dialogue::GetSingleton().InitialiseControls(hwndDlg);

			break;

		case WM_COMMAND:

			switch(LOWORD(wParam))
			{
				case IDC_DISPLAYMODELIST:
					Dialogue::GetSingleton().UpdateModeIndexFromControls();
					break;

				case IDC_COLOURDEPTHLIST:
					Dialogue::GetSingleton().ClearDisplayModeList();
					Dialogue::GetSingleton().UpdateColourDepthFromControls();
					Dialogue::GetSingleton().UpdateDisplayModeList();
					Dialogue::GetSingleton().UpdateModeIndexFromControls();
					Dialogue::GetSingleton().InitialiseFullScreenSetting();
					
					break;

				case IDC_FULLSCREEN:
					Dialogue::GetSingleton().UpdateFullScreenFromControls();
					Dialogue::GetSingleton().InitialiseFullScreenSetting();
					
					break;

				case IDSTART:

					//Disable the controls, to make sure they don't get
					//changed during initialisation
					EnableWindow ( GetDlgItem(hwndDlg, IDSTART), FALSE );
					EnableWindow ( GetDlgItem(hwndDlg, IDEXIT), FALSE );
					EnableWindow ( GetDlgItem(hwndDlg, IDC_DISPLAYMODELIST), FALSE );
					EnableWindow ( GetDlgItem(hwndDlg, IDC_COLOURDEPTHLIST), FALSE );
					EnableWindow ( GetDlgItem(hwndDlg, IDC_FULLSCREEN), FALSE );
					EnableWindow ( GetDlgItem(hwndDlg, IDC_COMMANDLINE), FALSE );
					EnableWindow ( GetDlgItem(hwndDlg, IDC_EXECUTE), FALSE );


					Dialogue::GetSingleton().m_startFunc();
					Dialogue::GetSingleton().DestroyDialogue();
					return FALSE;
				
				case IDEXIT:

					Dialogue::GetSingleton().m_exitFunc();
					Dialogue::GetSingleton().DestroyDialogue();
					return FALSE;

				case IDC_EXECUTE:
				{
					//Get the window handle of the command line text box
					HWND hWndCommandLine = GetDlgItem(hwndDlg, IDC_COMMANDLINE);

					//Create a string to hold the contents
					std::string str;
					str.resize( 1024 );
					
					//The EM_GETLINE message requires that we set the first word of the 
					//string to the length of the string
					*(reinterpret_cast<WORD*>(&str[0])) = 1024;

					LRESULT lResult = SendMessage( hWndCommandLine, 
													(UINT)EM_GETLINE, 
													(WPARAM)0, 
													(LPARAM)(LPCTSTR)&str[0] );  

					str.resize( lResult );

					Core::Console::GetSingleton().ExecuteString ( str );

					SendMessage(hWndCommandLine, EM_SETSEL,    (WPARAM)0, (LPARAM)(str.length()));
					SendMessage(hWndCommandLine, EM_REPLACESEL,(WPARAM)FALSE, (LPARAM)(""));

				}
			}

		break;

		case WM_CLOSE:
			Dialogue::GetSingleton().m_exitFunc();
			UInt returnVal = 1;
			EndDialog(hwndDlg, (WPARAM)&returnVal);
			return FALSE;
			
	}

	return FALSE;
}
//End Dialogue::DialogProc



//=========================================================================
//! @function    Dialogue::InitialiseControls
//! @brief       Set the controls on the dialogue to their initial states
//!              
//! @param       hWnd [in] Window handle for the dialogue
//=========================================================================
void Dialogue::InitialiseControls ( HWND hWnd )
{
	m_dialogHwnd = hWnd;

	//Get handles to the controls on the dialogue
	m_displayModeList = GetDlgItem(m_dialogHwnd, IDC_DISPLAYMODELIST);
	m_colourModeList  = GetDlgItem(m_dialogHwnd, IDC_COLOURDEPTHLIST);
	m_fullScreenCheckBox = GetDlgItem(m_dialogHwnd, IDC_FULLSCREEN);
	m_consoleDisplay  = GetDlgItem(m_dialogHwnd, IDC_CONSOLEDISPLAY);

	//Validate and change the values of any console variables
	//that may be out of acceptable ranges
	if ( (m_bitsPerPixel != 16) && (m_bitsPerPixel != 32) )
	{
		m_bitsPerPixel = 32;
		std::clog << "Invalid value for init_bpp - setting to 32" << std::endl;
	}	

	if ( m_displayModeIndex > m_modeList.ModeCount(m_bitsPerPixel) )
	{
		m_displayModeIndex = 0;
		std::clog << "Invalid value for init_modeindex - setting to 0" << std::endl;
	}

	//First set the initial mode of the fullscreen checkbox
	InitialiseFullScreenSetting();

	//Populate the controls

	//Populate the display depth list
	InitialiseColourDepthList();

	//Populate the display mode list based in the current colour depth choice
	UpdateDisplayModeList();

	//Write the current contents of the console so that console output
	//written before the console output is redirected to the dialogue,
	//can still be read in the console output text box
	Core::ConsoleBuffer::const_iterator itr = Core::Console::GetSingleton().Buffer().Begin();
	Core::ConsoleBuffer::const_iterator end = Core::Console::GetSingleton().Buffer().End();

	std::string currentConsole;

	while ( itr != end )
	{
		//Copy the string to the text box, converting \n into \r\n
		std::string::const_iterator strItr = itr->begin();
		std::string::const_iterator strEnd = itr->end();

		currentConsole += *itr;
		currentConsole += "\r\n";

		++itr;
	}

	//Set the contents of the text box
	SendMessage(m_consoleDisplay, WM_SETTEXT, 
				0, (LPARAM)(currentConsole.c_str()));
	//Scroll to the bottom of the text window
	UInt length = GetWindowTextLength(m_consoleDisplay);
	SendMessage ( m_consoleDisplay, EM_LINESCROLL, 0, length );

	//Redirect console output to our console text box
	SetupConsoleRedirection();

}
//End Dialogue::InitialiseControls



//=========================================================================
//! @function    Dialogue::InitialiseColourDepthList
//! @brief       Populate the colour depth list with a list of supported colour depths
//!              
//=========================================================================
void Dialogue::InitialiseColourDepthList ()
{
	//Indicates whether ANY screen modes are supported
	UInt lastIndexAdded = 0;

	if ( m_modeList.ModeCount(m_bitsPerPixel) > 0 )
	{
		SendMessage(m_colourModeList, CB_ADDSTRING, 0 , (LPARAM)(const Char*)"32 Bit");
		LRESULT result = SendMessage(m_colourModeList, CB_SETITEMDATA, lastIndexAdded++, 32);

		debug_assert ( result != CB_ERR, "Couldn't set item data!" );
	}

	if ( m_modeList.ModeCount(m_bitsPerPixel) > 0 )
	{

		SendMessage(m_colourModeList, CB_ADDSTRING, 0 , (LPARAM)(const Char*)"16 Bit");
		LRESULT result = SendMessage(m_colourModeList, CB_SETITEMDATA, lastIndexAdded++, 16);

		debug_assert ( result != CB_ERR, "Couldn't set item data!" );

		//If lastIndexAdded == 1 then it means we don't support 32 bit mode
		//so we have to change the m_bitsPerPixel variable to 16, if it's not set
		//to that already
		if ( (lastIndexAdded == 1) && (static_cast<Core::ConsoleUInt>(m_bitsPerPixel) == 32) )
		{
			m_bitsPerPixel = 16;
		}
	}


	//If lastIndexAdded == 0 then none were added,  which means we don't support any graphics modes
	if ( lastIndexAdded == 0 )
	{
		throw Core::RuntimeError ( "Error! Your graphics card does not support hardware acceleration\n"
								   "Unfortunately your graphics card does not meet the requirements for this demo.",
								   0, __FILE__, __FUNCTION__, __LINE__ );
	}

	SendMessage(m_colourModeList, CB_SETCURSEL , 0, 0);

}
//End Dialogue::InitialiseColourDepthList



//=========================================================================
//! @function    Dialogue::InitialiseFullScreenSetting
//! @brief       Set the initial state of the full-screen checkbox from
//!				 the initial value of its console variable
//=========================================================================
void Dialogue::InitialiseFullScreenSetting ()
{
	if ( m_modeList.ModeCount(m_bitsPerPixel) > 0 )
	{
		if ( m_modeList.GetMode(0, m_bitsPerPixel).SupportsWindowed() )
		{
			if ( m_fullScreen == true )
			{
				SendMessage ( m_fullScreenCheckBox, BM_SETCHECK, BST_CHECKED, 0); 
				
			}

			//Enable the checkbox so the user can choose windowed modes
			EnableWindow ( GetDlgItem(m_dialogHwnd, IDC_FULLSCREEN), TRUE );
			return;
		}
	}
	
	//If we got this far then disable the checkbox, and check it
	EnableWindow ( GetDlgItem(m_dialogHwnd, IDC_FULLSCREEN), FALSE );
	SendMessage ( m_fullScreenCheckBox, BM_SETCHECK, BST_CHECKED, 0 );
	m_fullScreen = true;
}
//End Dialogue::InitialiseFullScreenSetting



//=========================================================================
//! @function    Dialogue::ClearDisplayModeList
//! @brief       Empty out the list of display modes
//=========================================================================
void Dialogue::ClearDisplayModeList ()
{
	SendMessage(m_displayModeList, CB_RESETCONTENT, 0, 0);
}
//End Dialogue::ClearDisplayModeList 



//=========================================================================
//! @function    Dialogue::UpdateDisplayModeList
//! @brief       Fill the list of display modes
//!              
//=========================================================================
void Dialogue::UpdateDisplayModeList ()
{

	UInt modeCount = m_modeList.ModeCount(m_bitsPerPixel); 

	debug_assert ( modeCount, "Error, modeCount should not be 0 at this point!" );

	UInt itemIndex = 0;

	std::ostringstream modeDesc;

	//Populate the list of display modes
	for ( UInt index=0; index < modeCount; ++index )
	{

		modeDesc.str("");
		modeDesc << "Mode " << index << ":   " << m_modeList.GetMode(index, m_bitsPerPixel).Description();

		itemIndex = SendMessage(m_displayModeList, CB_ADDSTRING, 0 , 
						(LPARAM)(modeDesc.str().c_str()));

		
		SendMessage(m_displayModeList, CB_SETITEMDATA, (WPARAM)itemIndex, (LPARAM)index );

		#if 0
		std::clog << "Adding display mode " 
				  << m_modeList.GetMode(index, m_bitsPerPixel).Description() 
				  << std::endl;
		#endif				  
	}

	//Set the current selection in the display mode list
	if ( m_displayModeIndex < modeCount )
	{
		SendMessage(m_displayModeList, CB_SETCURSEL , (WPARAM)m_displayModeIndex, 0);
	}
	else
	{
		SendMessage(m_displayModeList, CB_SETCURSEL , 0, 0);
	}
}
//End Dialogue::UpdateDisplayModeList



//=========================================================================
//! @function    Dialogue::UpdateColourDepthFromControls
//! @brief       Update the init_bpp console variable based on the selection
//!              of colour depth on the dialogue
//=========================================================================
void Dialogue::UpdateColourDepthFromControls ()
{
	UInt selectedIndex = 0;

	selectedIndex = SendMessage( m_colourModeList, CB_GETCURSEL, 0, 0 );
	m_bitsPerPixel = SendMessage( m_colourModeList, CB_GETITEMDATA, (WPARAM)selectedIndex, 0 );

	debug_assert ( (m_bitsPerPixel == 16) || (m_bitsPerPixel == 32), "Invalid value for m_bitsPerPixel!" );
}
//End Dialogue::UpdateColourDepthFromControls



//=========================================================================
//! @function    Dialogue::UpdateModeIndexFromControls
//! @brief       Update the init_mode console variable based on the selection
//!              of display mode on the dialogue
//=========================================================================
void Dialogue::UpdateModeIndexFromControls ()
{
	UInt selectedIndex = 0;
	
	selectedIndex = SendMessage( m_displayModeList, CB_GETCURSEL, 0, 0 );
	m_displayModeIndex = SendMessage( m_displayModeList, CB_GETITEMDATA, (WPARAM)selectedIndex, 0 );

	debug_assert ( m_displayModeIndex < m_modeList.ModeCount(m_bitsPerPixel), "Invalid setting for m_modeIndex!" );
}
//End Dialogue::UpdateModeIndexFromControls



//=========================================================================
//! @function    Dialogue::UpdateFullScreenFromControls
//! @brief       Update the init_fullscreen console variable based on the
//!              state of the full screen check box
//=========================================================================
void Dialogue::UpdateFullScreenFromControls()
{
	if ( SendMessage(m_fullScreenCheckBox, BM_GETCHECK, 0, 0) )
	{
		m_fullScreen = true;
	}
	else
	{
		m_fullScreen = false;
	}
}
//End Dialogue::UpdateFullScreenFromControls