//======================================================================================
//! @file         DirectXKeyboard.h
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


#ifndef DIRECTX9INPUT_KEYBOARD_H
#define DIRECTX9INPUT_KEYBOARD_H


#include "Core/Keyboard.h"
#include <dinput.h>
#include <atlbase.h>



//=========================================================================
// Forward declarations
//=========================================================================
namespace DirectX9Input { class DirectXInputSystem;	}


//namespace DirectX9Input
namespace DirectX9Input
{


	//!@class	DirectXKeyboard
	//!@brief	DirectInput version of Keyboard 
	class DirectXKeyboard : public Core::Keyboard
	{

		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			DirectXKeyboard ( DirectXInputSystem& inputSystem );
			~DirectXKeyboard();


            //=========================================================================
            // Public methods
            //=========================================================================
			void Update();

		private:


            //=========================================================================
            // Private methods
            //=========================================================================
			void CreateKeyboard();

			void TriggerKeyDownEvents ( );
			void TriggerKeyUpEvents ( );

            //=========================================================================
            // Private data
            //=========================================================================
			HWND						 m_windowHandle;
			CComPtr<IDirectInputDevice8> m_keyboard; 
			CComPtr<IDirectInput8>		 m_directInput;

			UChar						 m_state[2][256];
			UInt						 m_currentState;
	};
	//End class DirectXKeyboard


}
//end namespace DirectX9Input


#endif
//#ifndef DIRECTX9INPUT_KEYBOARD_H
