//======================================================================================
//! @file         VirtualKeyCodes.cpp
//! @brief        Virtual key codes for keyboard input.
//!               
//!               Allows use of virtual key codes without using the platform specific 
//!				  windows code defines
//!               
//! @author       Bryan Robertson
//! @date         Monday, 7 April 2005
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


#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/VirtualKeyCodes.h"
#include <windows.h>


using namespace Core;



#ifdef WIN32

	Core::WindowsKeyToVirtualKeyMapping Core::MapWindowsKeyToVirtualKey;


	//!Set up the mapping between Windows keys and Virtual key constants
	//!
	//!TODO: Fix this. Some of the VK_ constants are undefined so I've had to comment out some
	//!		 of the lines in the meantime. It only affects rarely used keys, so it's not high priority,
	//!		 the worst that could happen is that someone will get a random character pressed when they press the browser back
	//!		 button on their keyboard
	WindowsKeyToVirtualKeyMapping::WindowsKeyToVirtualKeyMapping ()
	{
				m_keyMapping[0]			  = KEY_UNDEFINED;
				m_keyMapping[VK_LBUTTON]  = KEY_UNDEFINED;
				m_keyMapping[VK_RBUTTON]  = KEY_UNDEFINED;
				m_keyMapping[VK_CANCEL]	  = KEY_CANCEL;
				m_keyMapping[VK_MBUTTON]  = KEY_UNDEFINED;
				//m_keyMapping[VK_XBUTTON1] = KEY_UNDEFINED;
				//m_keyMapping[VK_XBUTTON2] = KEY_UNDEFINED;
                m_keyMapping[0x07]		  = KEY_UNDEFINED; 
				m_keyMapping[VK_BACK]	  = KEY_BACKSPACE;
                m_keyMapping[VK_TAB]	  = KEY_TAB;
				m_keyMapping[0xA0]		  = KEY_UNDEFINED;
				m_keyMapping[0xB0]		  = KEY_UNDEFINED;
                m_keyMapping[VK_CLEAR]	  = KEY_CLEAR;
				m_keyMapping[VK_RETURN]	  = KEY_RETURN;
				m_keyMapping[0xE0]		  = KEY_UNDEFINED;
				m_keyMapping[0x0F]		  = KEY_UNDEFINED;
				m_keyMapping[VK_SHIFT]	  = KEY_SHIFT;
				m_keyMapping[VK_CONTROL]  = KEY_CONTROL;
				m_keyMapping[VK_MENU]	  = KEY_ALT;
				m_keyMapping[VK_PAUSE]	  = KEY_PAUSE;
                m_keyMapping[VK_CAPITAL]  = KEY_CAPSLOCK;
                m_keyMapping[VK_KANA]	  = KEY_UNDEFINED;
				m_keyMapping[0x16]		  = KEY_UNDEFINED;
				m_keyMapping[VK_JUNJA]	  = KEY_JUNJA;
				m_keyMapping[VK_FINAL]	  = KEY_FINAL;
                m_keyMapping[VK_HANJA]	  = KEY_UNDEFINED;
				m_keyMapping[0x1A]		  = KEY_UNDEFINED;
				m_keyMapping[VK_ESCAPE]	  = KEY_ESCAPE;
				m_keyMapping[VK_CONVERT]  = KEY_CONVERT;
				m_keyMapping[VK_NONCONVERT] = KEY_NONCONVERT;
				m_keyMapping[VK_ACCEPT]		= KEY_ACCEPT;
				m_keyMapping[VK_MODECHANGE]	= KEY_MODECHANGE;
				m_keyMapping[VK_SPACE]	  = KEY_SPACE;
				m_keyMapping[VK_PRIOR]	  = KEY_PAGEUP;
				m_keyMapping[VK_NEXT]	  = KEY_PAGEDOWN;
				m_keyMapping[VK_END]	  = KEY_END;
				m_keyMapping[VK_HOME]	  = KEY_HOME;
				m_keyMapping[VK_LEFT]	  = KEY_LEFT;
				m_keyMapping[VK_UP]		  = KEY_UP;
                m_keyMapping[VK_RIGHT]	  = KEY_RIGHT;
				m_keyMapping[VK_DOWN]	  = KEY_DOWN;
				m_keyMapping[VK_SELECT]	  = KEY_SELECT;
				m_keyMapping[VK_PRINT]	  = KEY_PRINT;
				m_keyMapping[VK_EXECUTE]  = KEY_UNDEFINED; //KEY_EXECUTE is #defined by windows and causes an error.
				m_keyMapping[VK_SNAPSHOT] = KEY_PRINTSCREEN;
				m_keyMapping[VK_INSERT]	  = KEY_INSERT;
				m_keyMapping[VK_DELETE]	  = KEY_DELETE;
				m_keyMapping[VK_HELP]	  = KEY_HELP;
				m_keyMapping[0x30]		  = KEY_0; 
				m_keyMapping[0x31]		  = KEY_1;
				m_keyMapping[0x32]		  = KEY_2;
				m_keyMapping[0x33]		  = KEY_3;
				m_keyMapping[0x34]		  = KEY_4;
				m_keyMapping[0x35]		  = KEY_5;
				m_keyMapping[0x36]		  = KEY_6;
				m_keyMapping[0x37]		  = KEY_7;
				m_keyMapping[0x38]		  = KEY_8;
				m_keyMapping[0x39]		  = KEY_9;
				m_keyMapping[0x3A]		  = KEY_UNDEFINED;
				m_keyMapping[0x3B]		  = KEY_UNDEFINED;
				m_keyMapping[0x3C]		  = KEY_UNDEFINED;
				m_keyMapping[0x3D]		  = KEY_UNDEFINED;
				m_keyMapping[0x3E]		  = KEY_UNDEFINED;
				m_keyMapping[0x3F]		  = KEY_UNDEFINED;
				m_keyMapping[0x40]		  = KEY_UNDEFINED;
				m_keyMapping[0x41]		  = KEY_A;
				m_keyMapping[0x42]		  = KEY_B;
				m_keyMapping[0x43]		  = KEY_C;
				m_keyMapping[0x44]		  = KEY_D;
				m_keyMapping[0x45]		  = KEY_E;
				m_keyMapping[0x46]		  = KEY_F;
				m_keyMapping[0x47]		  = KEY_G;
				m_keyMapping[0x48]		  = KEY_H;
				m_keyMapping[0x49]		  = KEY_I;
				m_keyMapping[0x4A]		  = KEY_J;
				m_keyMapping[0x4B]		  = KEY_K;
				m_keyMapping[0x4C]		  = KEY_L;
				m_keyMapping[0x4D]		  = KEY_M;
				m_keyMapping[0x4E]		  = KEY_N;
				m_keyMapping[0x4F]		  = KEY_O;
				m_keyMapping[0x50]		  = KEY_P;
				m_keyMapping[0x51]		  = KEY_Q;
				m_keyMapping[0x52]		  = KEY_R;
				m_keyMapping[0x53]		  = KEY_S;
				m_keyMapping[0x54]		  = KEY_T;
				m_keyMapping[0x55]		  = KEY_U;
				m_keyMapping[0x56]		  = KEY_V;
				m_keyMapping[0x57]		  = KEY_W;
				m_keyMapping[0x58]		  = KEY_X;
				m_keyMapping[0x59]		  = KEY_Y;
				m_keyMapping[0x5A]		  = KEY_Z;
				m_keyMapping[VK_LWIN]	  = KEY_LWIN;
				m_keyMapping[VK_RWIN]	  = KEY_RWIN;
				m_keyMapping[VK_APPS]	  = KEY_APPS;
				m_keyMapping[0x5E]		  = KEY_UNDEFINED;
				m_keyMapping[VK_SLEEP]	  = KEY_SLEEP;
				m_keyMapping[VK_NUMPAD0]  = KEY_NUMPAD0;
				m_keyMapping[VK_NUMPAD1]  = KEY_NUMPAD1;
				m_keyMapping[VK_NUMPAD2]  = KEY_NUMPAD2;
				m_keyMapping[VK_NUMPAD3]  = KEY_NUMPAD3;
				m_keyMapping[VK_NUMPAD4]  = KEY_NUMPAD4;
				m_keyMapping[VK_NUMPAD5]  = KEY_NUMPAD5;
				m_keyMapping[VK_NUMPAD6]  = KEY_NUMPAD6;
				m_keyMapping[VK_NUMPAD7]  = KEY_NUMPAD7;
				m_keyMapping[VK_NUMPAD8]  = KEY_NUMPAD8;
				m_keyMapping[VK_NUMPAD9]  = KEY_NUMPAD9;
				m_keyMapping[VK_MULTIPLY] = KEY_MULTIPLY;
                m_keyMapping[VK_ADD]	  = KEY_ADD;
				m_keyMapping[VK_SEPARATOR] = KEY_SEPARATOR;
                m_keyMapping[VK_SUBTRACT] = KEY_SUBTRACT;
                m_keyMapping[VK_DECIMAL]  = KEY_DECIMAL;
                m_keyMapping[VK_DIVIDE]	  = KEY_DIVIDE;
				m_keyMapping[VK_F1]		  = KEY_F1;
				m_keyMapping[VK_F2]		  = KEY_F2;
                m_keyMapping[VK_F3]		  = KEY_F3;
                m_keyMapping[VK_F4]		  = KEY_F4;
                m_keyMapping[VK_F5]		  = KEY_F5;
                m_keyMapping[VK_F6]		  = KEY_F6;
				m_keyMapping[VK_F7]		  = KEY_F7;
				m_keyMapping[VK_F8]		  = KEY_F8;
                m_keyMapping[VK_F9]		  = KEY_F9;
                m_keyMapping[VK_F10]	  = KEY_F10;
				m_keyMapping[VK_F11]	  = KEY_F11;
				m_keyMapping[VK_F12]	  = KEY_F12;
                m_keyMapping[VK_F13]	  = KEY_F13;
                m_keyMapping[VK_F14]	  = KEY_F14;
                m_keyMapping[VK_F15]	  = KEY_F15;
                m_keyMapping[VK_F16]	  = KEY_F16;
				m_keyMapping[VK_F17]	  = KEY_F17;
				m_keyMapping[VK_F18]	  = KEY_F18;
                m_keyMapping[VK_F19]	  = KEY_F19;
                m_keyMapping[VK_F20]	  = KEY_F20;
				m_keyMapping[VK_F10]	  = KEY_F10;
				m_keyMapping[VK_F11]	  = KEY_F11;
				m_keyMapping[VK_F12]	  = KEY_F12;
                m_keyMapping[VK_F13]	  = KEY_F13;
                m_keyMapping[VK_F14]	  = KEY_F14;
                m_keyMapping[VK_F15]	  = KEY_F15;
                m_keyMapping[VK_F16]	  = KEY_F16;
				m_keyMapping[VK_F17]	  = KEY_F17;
				m_keyMapping[VK_F18]	  = KEY_F18;
                m_keyMapping[VK_F19]	  = KEY_F19;
                m_keyMapping[VK_F20]	  = KEY_F20;
				m_keyMapping[VK_F21]	  = KEY_F21;
				m_keyMapping[VK_F22]	  = KEY_F22;
                m_keyMapping[VK_F23]	  = KEY_F23;
				m_keyMapping[VK_F24]	  = KEY_F24;
				m_keyMapping[0x88]		  = KEY_UNDEFINED;
				m_keyMapping[0x89]		  = KEY_UNDEFINED;
				m_keyMapping[0x8A]		  = KEY_UNDEFINED;
				m_keyMapping[0x8B]		  = KEY_UNDEFINED;
				m_keyMapping[0x8C]		  = KEY_UNDEFINED;
				m_keyMapping[0x8D]		  = KEY_UNDEFINED;
				m_keyMapping[0x8E]		  = KEY_UNDEFINED;
				m_keyMapping[0x8F]		  = KEY_UNDEFINED;
				m_keyMapping[VK_NUMLOCK]  = KEY_NUMLOCK;
				m_keyMapping[VK_SCROLL]	  = KEY_SCROLL;
				m_keyMapping[0x92]		  = KEY_UNDEFINED;
				m_keyMapping[0x93]		  = KEY_UNDEFINED;
				m_keyMapping[0x94]		  = KEY_UNDEFINED;
				m_keyMapping[0x95]		  = KEY_UNDEFINED;
				m_keyMapping[0x96]		  = KEY_UNDEFINED;
				m_keyMapping[0x97]		  = KEY_UNDEFINED;
				m_keyMapping[0x98]		  = KEY_UNDEFINED;
				m_keyMapping[0x99]		  = KEY_UNDEFINED;
				m_keyMapping[0x9A]		  = KEY_UNDEFINED;
				m_keyMapping[0x9B]		  = KEY_UNDEFINED;
				m_keyMapping[0x9C]		  = KEY_UNDEFINED;
				m_keyMapping[0x9D]		  = KEY_UNDEFINED;
				m_keyMapping[0x9E]		  = KEY_UNDEFINED;
				m_keyMapping[0x9F]		  = KEY_UNDEFINED;
				m_keyMapping[VK_LSHIFT]	  = KEY_LSHIFT;
                m_keyMapping[VK_RSHIFT]	  = KEY_RSHIFT;
                m_keyMapping[VK_LCONTROL] = KEY_LCONTROL;
                m_keyMapping[VK_RCONTROL] = KEY_RCONTROL;
				m_keyMapping[VK_LMENU]	  = KEY_LALT;
				m_keyMapping[VK_RMENU]	  = KEY_RALT;
				/*m_keyMapping[VK_BROWSER_BACK] = KEY_BROWSER_BACK;
				m_keyMapping[VK_BROWSER_FORWARD] = KEY_BROWSER_FORWARD;
                m_keyMapping[VK_BROWSER_REFRESH] = KEY_BROWSER_REFRESH;
                m_keyMapping[VK_BROWSER_STOP] = KEY_BROWSER_STOP;
                m_keyMapping[VK_BROWSER_SEARCH] = KEY_BROWSER_SEARCH;
				m_keyMapping[VK_BROWSER_FAVORITES] = KEY_BROWSER_FAVORITES;
                m_keyMapping[VK_BROWSER_HOME] = KEY_BROWSER_HOME;
                m_keyMapping[VK_VOLUME_MUTE] = KEY_VOLUME_MUTE;
                m_keyMapping[VK_VOLUME_DOWN] = KEY_VOLUME_DOWN;
                m_keyMapping[VK_VOLUME_UP]	 = KEY_VOLUME_UP;
				m_keyMapping[VK_MEDIA_NEXT_TRACK] = KEY_MEDIA_NEXT_TRACK;
                m_keyMapping[VK_MEDIA_PREV_TRACK] = KEY_MEDIA_PREV_TRACK;
                m_keyMapping[VK_MEDIA_STOP]	 = KEY_MEDIA_STOP;
                m_keyMapping[VK_MEDIA_PLAY_PAUSE] = KEY_MEDIA_PLAY_PAUSE;
                m_keyMapping[VK_LAUNCH_MAIL] = KEY_LAUNCH_MAIL;
				m_keyMapping[VK_LAUNCH_MEDIA_SELECT] = KEY_LAUNCH_MEDIA_SELECT;
                m_keyMapping[VK_LAUNCH_APP1] = KEY_LAUNCH_APP1;
				m_keyMapping[VK_LAUNCH_APP2] = KEY_LAUNCH_APP2;
				*/
				m_keyMapping[0xB8]			 = KEY_UNDEFINED;
				m_keyMapping[0xB9]			 = KEY_UNDEFINED;
				m_keyMapping[VK_OEM_1]		 = KEY_OEM_1;
				m_keyMapping[VK_OEM_PLUS]	 = KEY_OEM_PLUS;
                m_keyMapping[VK_OEM_COMMA]	 = KEY_OEM_COMMA;
				m_keyMapping[VK_OEM_MINUS]	 = KEY_OEM_MINUS;
                m_keyMapping[VK_OEM_PERIOD]  = KEY_OEM_PERIOD;
				m_keyMapping[VK_OEM_2]		 = KEY_OEM_2;
				m_keyMapping[VK_OEM_3]		 = KEY_OEM_3;
				m_keyMapping[0xC0]			 = KEY_UNDEFINED;
				m_keyMapping[0xC1]			 = KEY_UNDEFINED;
				m_keyMapping[0xC2]			 = KEY_UNDEFINED;
				m_keyMapping[0xC3]			 = KEY_UNDEFINED;
				m_keyMapping[0xC4]			 = KEY_UNDEFINED;
				m_keyMapping[0xC5]			 = KEY_UNDEFINED;
				m_keyMapping[0xC6]			 = KEY_UNDEFINED;
				m_keyMapping[0xC7]			 = KEY_UNDEFINED;
				m_keyMapping[0xC8]			 = KEY_UNDEFINED;
				m_keyMapping[0xC9]			 = KEY_UNDEFINED;
				m_keyMapping[0xCA]			 = KEY_UNDEFINED;
				m_keyMapping[0xCB]			 = KEY_UNDEFINED;
				m_keyMapping[0xCC]			 = KEY_UNDEFINED;
				m_keyMapping[0xCD]			 = KEY_UNDEFINED;
				m_keyMapping[0xCE]			 = KEY_UNDEFINED;
				m_keyMapping[0xCF]			 = KEY_UNDEFINED;
				m_keyMapping[0xD0]			 = KEY_UNDEFINED;
				m_keyMapping[0xD1]			 = KEY_UNDEFINED;
				m_keyMapping[0xD2]			 = KEY_UNDEFINED;
				m_keyMapping[0xD3]			 = KEY_UNDEFINED;
				m_keyMapping[0xD4]			 = KEY_UNDEFINED;
				m_keyMapping[0xD5]			 = KEY_UNDEFINED;
				m_keyMapping[0xD6]			 = KEY_UNDEFINED;
				m_keyMapping[0xD7]			 = KEY_UNDEFINED;
				m_keyMapping[0xD8]			 = KEY_UNDEFINED;
				m_keyMapping[0xD9]			 = KEY_UNDEFINED;
				m_keyMapping[0xDA]			 = KEY_UNDEFINED;
                m_keyMapping[VK_OEM_4]		 = KEY_OEM_4;
				m_keyMapping[VK_OEM_5]		 = KEY_OEM_5;
				m_keyMapping[VK_OEM_6]		 = KEY_OEM_6;
				m_keyMapping[VK_OEM_7]		 = KEY_OEM_7;
				m_keyMapping[VK_OEM_8]		 = KEY_OEM_8;
				m_keyMapping[0xE0]			 = KEY_UNDEFINED;
				m_keyMapping[0xE1]			 = KEY_UNDEFINED;
				m_keyMapping[VK_OEM_102]	 = KEY_OEM_102;
                m_keyMapping[0xE3]			 = KEY_UNDEFINED;
				m_keyMapping[0xE4]			 = KEY_UNDEFINED;
                m_keyMapping[VK_PROCESSKEY]	 = KEY_PROCESSKEY;
				m_keyMapping[0xE6]			 = KEY_UNDEFINED;
                //m_keyMapping[VK_PACKET]		 = KEY_PACKET;
                m_keyMapping[0xE8]			 = KEY_UNDEFINED;
				m_keyMapping[0xE9]			 = KEY_UNDEFINED;
				m_keyMapping[0xEA]			 = KEY_UNDEFINED;
				m_keyMapping[0xEB]			 = KEY_UNDEFINED;
				m_keyMapping[0xEC]			 = KEY_UNDEFINED;
				m_keyMapping[0xED]			 = KEY_UNDEFINED;
				m_keyMapping[0xEE]			 = KEY_UNDEFINED;
                m_keyMapping[0xEF]			 = KEY_UNDEFINED;
				m_keyMapping[0xF0]			 = KEY_UNDEFINED;
				m_keyMapping[0xF1]			 = KEY_UNDEFINED;
				m_keyMapping[0xF2]			 = KEY_UNDEFINED;
				m_keyMapping[0xF3]			 = KEY_UNDEFINED;
                m_keyMapping[0xF4]			 = KEY_UNDEFINED;
				m_keyMapping[0xF5]			 = KEY_UNDEFINED;
				m_keyMapping[VK_ATTN]		 = KEY_ATTN;
				m_keyMapping[VK_CRSEL]		 = KEY_CRSEL;
				m_keyMapping[VK_EXSEL]		 = KEY_EXSEL;
                m_keyMapping[VK_EREOF]		 = KEY_EREOF;
				m_keyMapping[VK_PLAY]		 = KEY_PLAY;
                m_keyMapping[VK_ZOOM]		 = KEY_ZOOM;
				m_keyMapping[VK_NONAME]		 = KEY_NONAME;
				m_keyMapping[VK_PA1]		 = KEY_PA1;
                m_keyMapping[VK_OEM_CLEAR]	 = KEY_OEM_CLEAR;
		}

#endif

