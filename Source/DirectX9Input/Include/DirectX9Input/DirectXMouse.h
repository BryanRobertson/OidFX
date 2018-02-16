//======================================================================================
//! @file         DirectXMouse.h
//! @brief        DirectInput version of Mouse
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


#ifndef DIRECTX9INPUT_MOUSE_H
#define DIRECTX9INPUT_MOUSE_H


#include "Core/Mouse.h"
#include <dinput.h>



//namespace DirectX9Input
namespace DirectX9Input
{

	//!@class	DirectXMouse
	//!@brief	DirectInput version of Mouse 
	class DirectXMouse : public Core::Mouse
	{

		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			DirectXMouse ( DirectXInputSystem& inputSystem );
			~DirectXMouse ();


            //=========================================================================
            // Public methods
            //=========================================================================
			void Update();

		private:

            //=========================================================================
            // Private methods
            //=========================================================================
			void CreateMouse();

			inline HRESULT AcquireMouse();


            //=========================================================================
            // Private data
            //=========================================================================
			CComPtr<IDirectInputDevice8> m_mouse; 
			CComPtr<IDirectInput8>		 m_directInput;
			HWND						 m_windowHandle;

			DIMOUSESTATE				 m_oldMouseState;
			
	};
	//End class DirectXMouse


    //=========================================================================
    //! @function    DirectXMouse::AcquireMouse
    //! @brief       Acquire the mouse
    //! @throw       
    //=========================================================================
	HRESULT DirectXMouse::AcquireMouse ( )
	{
		static Core::ConsoleBool dbg_disablemouse ( "dbg_disablemouse", false );

		if ( !dbg_disablemouse )
		{
			return m_mouse->Acquire();
		}
		else
		{
			return S_OK;	
		}
	}
	//End DirectXMouse::AcquireMouse

}
//end namespace DirectX9Input


#endif
//#ifndef DIRECTX9INPUT_MOUSE_H
