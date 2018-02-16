//======================================================================================
//! @file         VirtualKeyCodes.h
//! @brief        Virtual key codes for keyboard input.
//!               
//!               Allows use of virtual key codes without using the platform specific 
//!				  windows code defines
//!               
//! @author       Bryan Robertson
//! @date         Monday, 28 February 2005
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

#ifndef CORE_VIRTUALKEYCODES_H
#define CORE_VIRTUALKEYCODES_H

//namespace Core
namespace Core
{
	
	//! Virtual key constants
	enum VirtualKey
	{
		KEY_UNDEFINED,
		KEY_CANCEL, 
		KEY_BACKSPACE, 
		KEY_TAB,
		KEY_CLEAR,
		KEY_RETURN,
		KEY_SHIFT,
		KEY_CONTROL,
		KEY_ALT,
		KEY_PAUSE,
		KEY_CAPSLOCK,
		KEY_KANA,
		KEY_HANGUEL,
		KEY_HANGUL,
		KEY_JUNJA,
		KEY_FINAL,
		KEY_HANJA,
		KEY_KANJI,
		KEY_ESCAPE,
		KEY_CONVERT,
		KEY_NONCONVERT,
		KEY_ACCEPT,
		KEY_MODECHANGE,
		KEY_SPACE,
		KEY_PAGEUP,
		KEY_PAGEDOWN,
		KEY_END,
		KEY_HOME,
		KEY_LEFT,
		KEY_UP,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_SELECT,
		KEY_PRINT,
		//KEY_EXECUTE,
		KEY_PRINTSCREEN,
		KEY_INSERT,
		KEY_DELETE,
		KEY_HELP,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_LWIN,
		KEY_RWIN,
		KEY_APPS,
		KEY_SLEEP,
		KEY_NUMPAD0,
		KEY_NUMPAD1,
		KEY_NUMPAD2,
		KEY_NUMPAD3,
		KEY_NUMPAD4,
		KEY_NUMPAD5,
		KEY_NUMPAD6,
		KEY_NUMPAD7,
		KEY_NUMPAD8,
		KEY_NUMPAD9,
		KEY_MULTIPLY,
		KEY_ADD,
		KEY_SEPARATOR,
		KEY_SUBTRACT,
		KEY_DECIMAL,
		KEY_DIVIDE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_F13,
		KEY_F14,
		KEY_F15,
		KEY_F16,
		KEY_F17,
		KEY_F18,
		KEY_F19,
		KEY_F20,
		KEY_F21,
		KEY_F22,
		KEY_F23,
		KEY_F24,
		KEY_NUMLOCK,
		KEY_SCROLL,
		KEY_LSHIFT,
		KEY_RSHIFT,
		KEY_LCONTROL,
		KEY_RCONTROL,
		KEY_LALT,
		KEY_RALT,
		KEY_BROWSER_BACK,
		KEY_BROWSER_FORWARD,
		KEY_BROWSER_REFRESH,
		KEY_BROWSER_STOP,
		KEY_BROWSER_SEARCH,
		KEY_BROWSER_FAVORITES,
		KEY_BROWSER_HOME,
		KEY_VOLUME_MUTE,
		KEY_VOLUME_DOWN,
		KEY_VOLUME_UP,
		KEY_MEDIA_NEXT_TRACK,
		KEY_MEDIA_PREV_TRACK,
		KEY_MEDIA_STOP,
		KEY_MEDIA_PLAY_PAUSE,
		KEY_LAUNCH_MAIL,
		KEY_LAUNCH_MEDIA_SELECT,
		KEY_LAUNCH_APP1,
		KEY_LAUNCH_APP2,
		KEY_OEM_1,
		KEY_OEM_PLUS,
		KEY_OEM_COMMA,
		KEY_OEM_MINUS,
		KEY_OEM_PERIOD,
		KEY_OEM_2,
		KEY_OEM_3,
		KEY_OEM_4,
		KEY_OEM_5,
		KEY_OEM_6,
		KEY_OEM_7,
		KEY_OEM_8,
		KEY_OEM_102,
		KEY_PROCESSKEY,
		KEY_PACKET,
		KEY_ATTN,
		KEY_CRSEL,
		KEY_EXSEL,
		KEY_EREOF,
		KEY_PLAY,
		KEY_ZOOM,
		KEY_NONAME,
		KEY_PA1,
		KEY_OEM_CLEAR,
		
		KEY_BACKSLASH,
		KEY_FORWARDSLASH,
		KEY_COMMA,
		KEY_EQUALS,
		KEY_LBRACKET,
		KEY_RBRACKET,
		KEY_LMENU,
		KEY_RMENU,
		KEY_SEMICOLON,
		KEY_NUMPADENTER,
		KEY_PERIOD

	};


	#ifdef WIN32

	//!@class	WindowsKeyToVirtualMapping
	//!@brief	Stores an array of mappings between windows keys and the VirtualKey enumeration
	class WindowsKeyToVirtualKeyMapping
	{
		public:

			WindowsKeyToVirtualKeyMapping();

			inline UInt operator() ( UChar windowsValue )
			{
				return m_keyMapping[windowsValue];
			}

		private:

			UChar m_keyMapping[255];
	};

	extern WindowsKeyToVirtualKeyMapping MapWindowsKeyToVirtualKey;


	#endif



};
//end namespace Core


#endif
//#ifndef CORE_VIRTUALKEYCODES_H
