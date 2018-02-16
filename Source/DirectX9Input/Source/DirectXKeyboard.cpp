//======================================================================================
//! @file         DirectXKeyboard.cpp
//! @brief        DirectInput version of Keyboard
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 19 July 2005
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
#include "DirectX9Input/DirectXKeyboard.h"
#include "DirectX9Input/DirectXInputSystem.h"
#include "DirectX9Input/ErrorCodes.h"



using namespace DirectX9Input;



//=========================================================================
//! @function    DirectXKeyboard::DirectXKeyboard
//! @brief       DirectXKeyboard constructor
//!              
//! @param       inputSystem [in]
//!              
//=========================================================================
DirectXKeyboard::DirectXKeyboard ( DirectXInputSystem& inputSystem )
: Keyboard(inputSystem), m_currentState(0)
{
	m_directInput = inputSystem.GetDirectInput();
	m_windowHandle = inputSystem.GetWindowHandle();

	//Clear out the internal keyboard buffers
	ZeroMemory(&m_state[0], sizeof(m_state[0]));
	ZeroMemory(&m_state[1], sizeof(m_state[1]));

	CreateKeyboard();

}
//End DirectXKeyboard::DirectXKeyboard


//=========================================================================
//! @function    DirectXKeyboard::~DirectXKeyboard
//! @brief       DirectXKeyboard destructor
//=========================================================================
DirectXKeyboard::~DirectXKeyboard ()
{
	if ( m_keyboard )
	{
		m_keyboard->Unacquire();
	}
}
//End DirectXKeyboard::~DirectXKeyboard


//=========================================================================
//! @function    DirectXKeyboard::Update
//! @brief       Gets the current keyboard state, and calls any keyboard handers

//=========================================================================
void DirectXKeyboard::Update ( )
{
	//Clear out the current state buffer
	ZeroMemory(&m_state[m_currentState], sizeof(m_state[m_currentState]));

	//Get the current keyboard state
	HRESULT result = m_keyboard->GetDeviceState ( sizeof(m_state[m_currentState]), 
													m_state[m_currentState] );

	if ( FAILED(result) )
	{
		#if 0
		std::cerr << __FUNCTION__ " Error, couldn't get keyboard state. Error code "
					<< DirectInputErrorCodeToString ( result )
					<< std::endl;
		#endif

		result = m_keyboard->Acquire();

		if ( FAILED(result) )
		{
			std::cerr << __FUNCTION__ " Error, couldn't reaquire keyboard!"
					<< DirectInputErrorCodeToString ( result )
					<< std::endl;
			return;
		}
	}

	TriggerKeyDownEvents();
	TriggerKeyUpEvents();

	//Flip the current state index around, so that the current state
	//will be considered the old state when this is next called
	m_currentState = !m_currentState;

}
//End  DirectXKeyboard::Update



//=========================================================================
//! @function    DirectXKeyboard::CreateKeyboard
//! @brief       Create the DirectInput keyboard object

//=========================================================================
void DirectXKeyboard::CreateKeyboard ()
{
	HRESULT result = m_directInput->CreateDevice ( GUID_SysKeyboard, &m_keyboard, 0 );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ " Error, couldn't create mouse! Error code"
				  << DirectInputErrorCodeToString ( result )
				  << std::endl;
		return;
	}

	result = m_keyboard->SetDataFormat( &c_dfDIKeyboard );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ " Error, couldn't set keyboard data format! Error code"
				  << DirectInputErrorCodeToString ( result )
				  << std::endl;
		return;
	}

	result = m_keyboard->SetCooperativeLevel ( m_windowHandle, DISCL_FOREGROUND );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ " Error, couldn't set cooperative level! Error code"
				  << DirectInputErrorCodeToString ( result )
				  << std::endl;
		return;
	}

	m_keyboard->Acquire();

}
//End DirectXKeyboard::CreateKeyboard 



//=========================================================================
//! @function    DirectXKeyboard::TriggerKeyDownEvents
//! @brief       Trigger a keydown event for all pressed keys
//!              
//!              
//=========================================================================
void DirectXKeyboard::TriggerKeyDownEvents ( )
{
	if ( m_state[m_currentState][DIK_0] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_0 );
	}

	if ( m_state[m_currentState][DIK_1] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_1 );
	}

    if ( m_state[m_currentState][DIK_2] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_2 );
	}
		
    if ( m_state[m_currentState][DIK_3] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_3 );
	}
		
    if ( m_state[m_currentState][DIK_4] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_4 );
	}
		
    if ( m_state[m_currentState][DIK_5] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_5 );
	}
		
    if ( m_state[m_currentState][DIK_6] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_6 );
	}
		
    if ( m_state[m_currentState][DIK_7] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_7 );
	}
		
    if ( m_state[m_currentState][DIK_8] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_8 );
	}
		
    if ( m_state[m_currentState][DIK_9] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_9 );
	}
		
    if ( m_state[m_currentState][DIK_A] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_A );
	}
		

    if ( m_state[m_currentState][DIK_ADD] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_ADD );
	}
		
    if ( m_state[m_currentState][DIK_APPS] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_APPS );
	}
		

    if ( m_state[m_currentState][DIK_B] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_B );
	}
		
    if ( m_state[m_currentState][DIK_BACKSLASH] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_BACKSLASH );
	}
		
    if ( m_state[m_currentState][DIK_C] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_C );
	}
		
    if ( m_state[m_currentState][DIK_CAPITAL] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_CAPSLOCK );
	}
		

    if ( m_state[m_currentState][DIK_COMMA] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_COMMA );
	}
		

    if ( m_state[m_currentState][DIK_D] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_D );
	}
		
    if ( m_state[m_currentState][DIK_DECIMAL] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_DECIMAL );
	}
		
    if ( m_state[m_currentState][DIK_DELETE] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_DELETE );
	}
		
    if ( m_state[m_currentState][DIK_DIVIDE] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_DIVIDE );
	}
		
    if ( m_state[m_currentState][DIK_DOWN] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_DOWN );
	}
		
    if ( m_state[m_currentState][DIK_E] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_E );
	}
		
    if ( m_state[m_currentState][DIK_END] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_END );
	}
		
    if ( m_state[m_currentState][DIK_EQUALS] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_EQUALS );
	}
		
    if ( m_state[m_currentState][DIK_ESCAPE] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_ESCAPE );
	}
		
    if ( m_state[m_currentState][DIK_F] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F );
	}
		
    if ( m_state[m_currentState][DIK_F1] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F1 );
	}
		
    if ( m_state[m_currentState][DIK_F2] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F2 );
	}
		
    if ( m_state[m_currentState][DIK_F3] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F3 );
	}
		
    if ( m_state[m_currentState][DIK_F4] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F4 );
	}
		
    if ( m_state[m_currentState][DIK_F5] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F5 );
	}
		
    if ( m_state[m_currentState][DIK_F6] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F6 );
	}
		
    if ( m_state[m_currentState][DIK_F7] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F7 );
	}
		
    if ( m_state[m_currentState][DIK_F8] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F8 );
	}
		
    if ( m_state[m_currentState][DIK_F9] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F9 );
	}
		
    if ( m_state[m_currentState][DIK_F10] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F10 );
	}
		
    if ( m_state[m_currentState][DIK_F11] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F11 );
	}
		
    if ( m_state[m_currentState][DIK_F12] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_F12 );
	}
		

    if ( m_state[m_currentState][DIK_G] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_G );
	}
		
    if ( m_state[m_currentState][DIK_H] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_H );
	}
		
    if ( m_state[m_currentState][DIK_HOME] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_HOME );
	}
		
    if ( m_state[m_currentState][DIK_I] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_I );
	}
		
    if ( m_state[m_currentState][DIK_INSERT] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_INSERT );
	}
		
    if ( m_state[m_currentState][DIK_J] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_J );
	}
		
    if ( m_state[m_currentState][DIK_K] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_K );
	}
		

    if ( m_state[m_currentState][DIK_L] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_L );
	}
		
    if ( m_state[m_currentState][DIK_LBRACKET] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_LBRACKET );
	}
		
    if ( m_state[m_currentState][DIK_LCONTROL] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_LCONTROL );
	}
		
    if ( m_state[m_currentState][DIK_LEFT] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_LEFT );
	}
		
    if ( m_state[m_currentState][DIK_LMENU] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_LMENU );
	}
		
    if ( m_state[m_currentState][DIK_LSHIFT] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_LSHIFT );
	}
		
    if ( m_state[m_currentState][DIK_LWIN] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_LWIN );
	}
		
    if ( m_state[m_currentState][DIK_M] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_M );
	}
		
    if ( m_state[m_currentState][DIK_MEDIASTOP] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_MEDIA_STOP );
	}
		
    if ( m_state[m_currentState][DIK_MINUS] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_SUBTRACT );
	}
		
    if ( m_state[m_currentState][DIK_MULTIPLY] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_MULTIPLY );
	}
		
    if ( m_state[m_currentState][DIK_MUTE] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_VOLUME_MUTE );
	}
		
    if ( m_state[m_currentState][DIK_N] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_N );
	}
		
    if ( m_state[m_currentState][DIK_NEXT] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_PAGEDOWN );
	}
		
    if ( m_state[m_currentState][DIK_NEXTTRACK] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_MEDIA_NEXT_TRACK );
	}
		
    if ( m_state[m_currentState][DIK_NUMLOCK] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMLOCK );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD0] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD0 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD1] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD1 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD2] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD2 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD3] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD3 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD4] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD4 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD5] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD5 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD6] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD6 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD7] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD7 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD8] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD8 );
	}
		
    if ( m_state[m_currentState][DIK_NUMPAD9] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPAD9 );
	}
	
    if ( m_state[m_currentState][DIK_NUMPADENTER] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_NUMPADENTER );
	}
		

    if ( m_state[m_currentState][DIK_O] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_O );
	}
		
    if ( m_state[m_currentState][DIK_OEM_102] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_OEM_102 );
	}
		
    if ( m_state[m_currentState][DIK_P] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_P );
	}
		
    if ( m_state[m_currentState][DIK_PAUSE] & 0x80)
	{
		m_event.OnKeyDown ( Core::KEY_PAUSE );
	}
		
    if ( m_state[m_currentState][DIK_PERIOD] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_PERIOD );
	}
		
    if ( m_state[m_currentState][DIK_PLAYPAUSE] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_MEDIA_PLAY_PAUSE );
	}
		
    if ( m_state[m_currentState][DIK_PREVTRACK] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_MEDIA_PREV_TRACK );
	}
		
    if ( m_state[m_currentState][DIK_PRIOR] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_PAGEUP );
	}
		
    if ( m_state[m_currentState][DIK_Q] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_Q );
	}
		
    if ( m_state[m_currentState][DIK_R] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_R );
	}
		
    if ( m_state[m_currentState][DIK_RBRACKET] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_RBRACKET );
	}
		
    if ( m_state[m_currentState][DIK_RCONTROL] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_RCONTROL );
	}
		
    if ( m_state[m_currentState][DIK_RETURN] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_RETURN );
	}
		
    if ( m_state[m_currentState][DIK_RIGHT] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_RIGHT );
	}
		
    if ( m_state[m_currentState][DIK_RMENU] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_RMENU );
	}
		
    if ( m_state[m_currentState][DIK_RSHIFT] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_RSHIFT );
	}
		
    if ( m_state[m_currentState][DIK_RWIN] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_RWIN );
	}
		
    if ( m_state[m_currentState][DIK_S] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_S );
	}
		
    if ( m_state[m_currentState][DIK_SCROLL] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_SCROLL );
	}
		
    if ( m_state[m_currentState][DIK_SEMICOLON] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_SEMICOLON );
	}
		
    if ( m_state[m_currentState][DIK_SLASH] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_FORWARDSLASH );
	}
		
    if ( m_state[m_currentState][DIK_SLEEP] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_SLEEP );
	}
		
    if ( m_state[m_currentState][DIK_SPACE] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_SPACE );
	}
		
    if ( m_state[m_currentState][DIK_SUBTRACT] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_SUBTRACT );
	}
		
    if ( m_state[m_currentState][DIK_T] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_T );
	}
		
    if ( m_state[m_currentState][DIK_TAB] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_TAB );
	}
		
    if ( m_state[m_currentState][DIK_U] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_U );
	}
		
    if ( m_state[m_currentState][DIK_UP] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_UP );
	}
		
    if ( m_state[m_currentState][DIK_V] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_V );
	}
		
    if ( m_state[m_currentState][DIK_VOLUMEDOWN] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_VOLUME_DOWN );
	}
		
    if ( m_state[m_currentState][DIK_VOLUMEUP] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_VOLUME_UP );
	}

    if ( m_state[m_currentState][DIK_W] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_W );
	}
		
    if ( m_state[m_currentState][DIK_X] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_X );
	}
		
    if ( m_state[m_currentState][DIK_Y] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_Y );
	}
		
    if ( m_state[m_currentState][DIK_Z] & 0x80 )
	{
		m_event.OnKeyDown ( Core::KEY_Z );
	}

}
//End DirectXKeyboard::TriggerKeyDownEvents



//=========================================================================
//! @function    DirectXKeyboard::TriggerKeyUpEvents
//! @brief       Check each key against its previous state, and trigger a keyup
//!              if the key has just been released
//!              
//=========================================================================
void DirectXKeyboard::TriggerKeyUpEvents( )
{
	if ( (((m_state[m_currentState][DIK_0] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_0] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_0 );
	}
		
    if ( (((m_state[m_currentState][DIK_1] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_1] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_1 );
	}
		
    if ( (((m_state[m_currentState][DIK_2] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_2] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_2 );
	}
		
    if ( (((m_state[m_currentState][DIK_3] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_3] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_3 );
	}
		
    if ( (((m_state[m_currentState][DIK_4] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_4] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_4 );
	}
		
    if ( (((m_state[m_currentState][DIK_5] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_5] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_5 );
	}
		
    if ( (((m_state[m_currentState][DIK_6] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_6] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_6 );
	}
		
    if ( (((m_state[m_currentState][DIK_7] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_7] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_7 );
	}
		
    if ( (((m_state[m_currentState][DIK_8] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_8] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_8 );
	}
		
    if ( (((m_state[m_currentState][DIK_9] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_9] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_9 );
	}
		
    if ( (((m_state[m_currentState][DIK_A] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_A] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_A );
	}
	
		
    if ( (((m_state[m_currentState][DIK_ADD] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_ADD] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_ADD );
	}
		
    if ( (((m_state[m_currentState][DIK_APPS] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_APPS] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_APPS );
	}
	
		
    if ( (((m_state[m_currentState][DIK_B] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_B] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_B );
	}
		
    if ( (((m_state[m_currentState][DIK_BACK] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_BACK] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_PAGEUP );
	}
		
    if ( (((m_state[m_currentState][DIK_BACKSLASH] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_BACKSLASH] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_BACKSLASH );
	}
		
    if ( (((m_state[m_currentState][DIK_C] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_C] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_C );
	}
		
    if ( (((m_state[m_currentState][DIK_CAPITAL] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_CAPITAL] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_CAPSLOCK );
	}
		
    if ( (((m_state[m_currentState][DIK_COMMA] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_COMMA] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_COMMA );
	}
		
    if ( (((m_state[m_currentState][DIK_CONVERT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_CONVERT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_CONVERT );
	}
		
    if ( (((m_state[m_currentState][DIK_D] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_D] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_D );
	}
		
    if ( (((m_state[m_currentState][DIK_DECIMAL] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_DECIMAL] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_DECIMAL );
	}
		
    if ( (((m_state[m_currentState][DIK_DELETE] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_DELETE] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_DELETE );
	}
		
    if ( (((m_state[m_currentState][DIK_DIVIDE] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_DIVIDE] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_DIVIDE );
	}
		
    if ( (((m_state[m_currentState][DIK_DOWN] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_DOWN] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_DOWN );
	}
		
    if ( (((m_state[m_currentState][DIK_E] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_E] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_E );
	}
		
    if ( (((m_state[m_currentState][DIK_END] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_END] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_END );
	}
		
    if ( (((m_state[m_currentState][DIK_EQUALS] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_EQUALS] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_EQUALS );
	}
		
    if ( (((m_state[m_currentState][DIK_ESCAPE] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_ESCAPE] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_ESCAPE );
	}
		
    if ( (((m_state[m_currentState][DIK_F] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F );
	}
		
    if ( (((m_state[m_currentState][DIK_F1] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F1] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F1 );
	}
		
    if ( (((m_state[m_currentState][DIK_F2] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F2] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F2 );
	}
		
    if ( (((m_state[m_currentState][DIK_F3] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F3] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F3 );
	}
		
    if ( (((m_state[m_currentState][DIK_F4] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F4] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F4 );
	}
		
    if ( (((m_state[m_currentState][DIK_F5] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F5] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F5 );
	}
		
    if ( (((m_state[m_currentState][DIK_F6] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F6] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F6 );
	}
		
    if ( (((m_state[m_currentState][DIK_F7] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F7] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F7 );
	}
		
    if ( (((m_state[m_currentState][DIK_F8] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F8] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F8 );
	}
		
    if ( (((m_state[m_currentState][DIK_F9] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F9] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F9 );
	}
		
    if ( (((m_state[m_currentState][DIK_F10] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F10] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F10 );
	}
		
    if ( (((m_state[m_currentState][DIK_F11] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F11] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F11 );
	}
		
    if ( (((m_state[m_currentState][DIK_F12] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F12] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F12 );
	}
		
    if ( (((m_state[m_currentState][DIK_F13] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F13] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F13 );
	}
		
    if ( (((m_state[m_currentState][DIK_F14] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F14] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F14 );
	}
		
    if ( (((m_state[m_currentState][DIK_F15] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_F15] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_F15 );
	}
		
    if ( (((m_state[m_currentState][DIK_G] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_G] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_G );
	}
		
    if ( (((m_state[m_currentState][DIK_H] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_H] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_H );
	}
		
    if ( (((m_state[m_currentState][DIK_HOME] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_HOME] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_HOME );
	}
		
    if ( (((m_state[m_currentState][DIK_I] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_I] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_I );
	}
		
    if ( (((m_state[m_currentState][DIK_INSERT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_INSERT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_INSERT );
	}
		
    if ( (((m_state[m_currentState][DIK_J] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_J] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_J );
	}
		
    if ( (((m_state[m_currentState][DIK_K] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_K] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_K );
	}
		
    if ( (((m_state[m_currentState][DIK_KANA] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_KANA] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_KANA );
	}
		
    if ( (((m_state[m_currentState][DIK_KANJI] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_KANJI] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_KANJI );
	}
		
    if ( (((m_state[m_currentState][DIK_L] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_L] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_L );
	}
		
    if ( (((m_state[m_currentState][DIK_LBRACKET] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_LBRACKET] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_LBRACKET );
	}
		
    if ( (((m_state[m_currentState][DIK_LCONTROL] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_LCONTROL] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_LCONTROL );
	}
		
    if ( (((m_state[m_currentState][DIK_LEFT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_LEFT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_LEFT );
	}
		
    if ( (((m_state[m_currentState][DIK_LMENU] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_LMENU] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_LMENU );
	}
		
    if ( (((m_state[m_currentState][DIK_LSHIFT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_LSHIFT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_LSHIFT );
	}
		
    if ( (((m_state[m_currentState][DIK_LWIN] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_LWIN] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_LWIN );
	}
		
    if ( (((m_state[m_currentState][DIK_M] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_M] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_M );
	}
		
    if ( (((m_state[m_currentState][DIK_MEDIASTOP] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_MEDIASTOP] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_MEDIA_STOP );
	}
		
    if ( (((m_state[m_currentState][DIK_MINUS] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_MINUS] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_SUBTRACT );
	}
		
    if ( (((m_state[m_currentState][DIK_MULTIPLY] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_MULTIPLY] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_MULTIPLY );
	}
		
    if ( (((m_state[m_currentState][DIK_MUTE] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_MUTE] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_VOLUME_MUTE );
	}
		
    if ( (((m_state[m_currentState][DIK_N] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_N] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_N );
	}
		
    if ( (((m_state[m_currentState][DIK_NEXT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NEXT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_PAGEDOWN );
	}
		
    if ( (((m_state[m_currentState][DIK_NEXTTRACK] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NEXTTRACK] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_MEDIA_NEXT_TRACK );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMLOCK] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMLOCK] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMLOCK );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD0] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD0] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD0 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD1] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD1] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD1 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD2] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD2] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD2 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD3] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD3] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD3 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD4] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD4] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD4 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD5] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD5] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD5 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD6] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD6] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD6 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD7] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD7] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD7 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD8] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD8] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD8 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPAD9] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPAD9] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPAD9 );
	}
		
    if ( (((m_state[m_currentState][DIK_NUMPADENTER] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_NUMPADENTER] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_NUMPADENTER );
	}

    if ( (((m_state[m_currentState][DIK_O] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_O] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_O );
	}
		
    if ( (((m_state[m_currentState][DIK_OEM_102] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_OEM_102] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_OEM_102 );
	}
		
    if ( (((m_state[m_currentState][DIK_P] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_P] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_P );
	}
		
    if ( (((m_state[m_currentState][DIK_PAUSE] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_PAUSE] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_PAUSE );
	}
		
    if ( (((m_state[m_currentState][DIK_PERIOD] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_PERIOD] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_PERIOD );
	}
		
    if ( (((m_state[m_currentState][DIK_PLAYPAUSE] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_PLAYPAUSE] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_MEDIA_PLAY_PAUSE );
	}
		
    if ( (((m_state[m_currentState][DIK_PREVTRACK] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_PREVTRACK] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_MEDIA_PREV_TRACK );
	}
		
    if ( (((m_state[m_currentState][DIK_PRIOR] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_PRIOR] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_PAGEUP );
	}
		
    if ( (((m_state[m_currentState][DIK_Q] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_Q] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_Q );
	}
		
    if ( (((m_state[m_currentState][DIK_R] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_R] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_R );
	}
		
    if ( (((m_state[m_currentState][DIK_RBRACKET] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_RBRACKET] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_RBRACKET );
	}
		
    if ( (((m_state[m_currentState][DIK_RCONTROL] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_RCONTROL] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_RCONTROL );
	}
		
    if ( (((m_state[m_currentState][DIK_RETURN] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_RETURN] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_RETURN );
	}
		
    if ( (((m_state[m_currentState][DIK_RIGHT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_RIGHT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_RIGHT );
	}
		
    if ( (((m_state[m_currentState][DIK_RMENU] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_RMENU] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_RMENU );
	}
		
    if ( (((m_state[m_currentState][DIK_RSHIFT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_RSHIFT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_RSHIFT );
	}
		
    if ( (((m_state[m_currentState][DIK_RWIN] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_RWIN] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_RWIN );
	}
		
    if ( (((m_state[m_currentState][DIK_S] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_S] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_S );
	}
		
    if ( (((m_state[m_currentState][DIK_SCROLL] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_SCROLL] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_SCROLL );
	}
		
    if ( (((m_state[m_currentState][DIK_SEMICOLON] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_SEMICOLON] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_SEMICOLON );
	}
		
    if ( (((m_state[m_currentState][DIK_SLASH] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_SLASH] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_FORWARDSLASH );
	}
		
    if ( (((m_state[m_currentState][DIK_SLEEP] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_SLEEP] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_SLEEP );
	}
		
    if ( (((m_state[m_currentState][DIK_SPACE] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_SPACE] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_SPACE );
	}
		
    if ( (((m_state[m_currentState][DIK_SUBTRACT] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_SUBTRACT] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_SUBTRACT );
	}
		
    if ( (((m_state[m_currentState][DIK_T] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_T] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_T );
	}
		
    if ( (((m_state[m_currentState][DIK_TAB] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_TAB] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_TAB );
	}
		
    if ( (((m_state[m_currentState][DIK_U] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_U] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_U );
	}
		
    if ( (((m_state[m_currentState][DIK_UP] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_UP] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_UP );
	}
		
    if ( (((m_state[m_currentState][DIK_V] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_V] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_V );
	}
		
    if ( (((m_state[m_currentState][DIK_VOLUMEDOWN] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_VOLUMEDOWN] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_VOLUME_DOWN );
	}
		
    if ( (((m_state[m_currentState][DIK_VOLUMEUP] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_VOLUMEUP] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_VOLUME_UP );
	}
		
    if ( (((m_state[m_currentState][DIK_W] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_W] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_W );
	}
		
    if ( (((m_state[m_currentState][DIK_X] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_X] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_X );
	}
		
    if ( (((m_state[m_currentState][DIK_Y] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_Y] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_Y );
	}
		
    if ( (((m_state[m_currentState][DIK_Z] & 0x80) == 0))
	&& (m_state[!m_currentState][DIK_Z] & 0x80) )
	{
		m_event.OnKeyUp ( Core::KEY_Z );
	}
		
}
//End DirectXKeyboard::TriggerKeyUpEvents
