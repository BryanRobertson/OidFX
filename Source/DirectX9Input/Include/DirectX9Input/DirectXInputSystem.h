//======================================================================================
//! @file         DirectXInputSystem.h
//! @brief        DirectInput version of InputSystem
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


#ifndef DIRECTX9INPUT_INPUTSYSTEM_H
#define DIRECTX9INPUT_INPUTSYSTEM_H


#include <atlbase.h>
#include "Core/InputSystem.h"
#include <dinput.h>


//namespace DirectX9Input
namespace DirectX9Input
{



	//!@class	DirectXInputSystem
	//!@brief	DirectInput version of InputSystem
	class DirectXInputSystem : public Core::InputSystem
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			DirectXInputSystem ( HWND windowHandle );


            //=========================================================================
            // Public methods
            //=========================================================================
			void Update();

			HWND GetWindowHandle ( ) const				{ return m_windowHandle;	}
			CComPtr<IDirectInput8>	GetDirectInput ( )  { return m_directInput;		}


		private:


            //=========================================================================
            // Private methods 
            //=========================================================================
			void CreateDirectInput ( );
			void CreateKeyboard ( );
			void CreateMouse ( );


            //=========================================================================
            // Private data
            //=========================================================================
			CComPtr<IDirectInput8>	m_directInput;
			HWND					m_windowHandle;


	};
	//End class DirectXInputSystem



};
//End namespace DirectX9Input


#endif
//#ifndef DIRECTX9INPUT_INPUTSYSTEM_H
