//======================================================================================
//! @file         DirectXInputSystem.cpp
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


#include "Core/Core.h"
#include "Core/InputSystem.h"
#include "DirectX9Input/DirectXInputSystem.h"
#include "DirectX9Input/DirectXKeyboard.h"
#include "DirectX9Input/DirectXMouse.h"
#include "DirectX9Input/ErrorCodes.h"
#include <dinput.h>



using namespace DirectX9Input;



//=========================================================================
//! @function    DirectXInputSystem::DirectXInputSystem
//! @brief       DirectXInputSystem constructor
//!              
//! @param       windowHandle [in] Window handle of the application window
//!              
//! @return      
//! @throw       
//=========================================================================
DirectXInputSystem::DirectXInputSystem ( HWND windowHandle )
: m_windowHandle(windowHandle)
{
	CreateDirectInput ( );
	CreateKeyboard ( );
	CreateMouse ( );
}
//End DirectXInputSystem::DirectXInputSystem



//=========================================================================
//! @function    DirectXInputSystem::Update
//! @brief       Update the input system
//!              
//=========================================================================
void DirectXInputSystem::Update ( )
{
	m_keyboard->Update();
	m_mouse->Update();
}
//End DirectXInputSystem::Update


//=========================================================================
//! @function    DirectXInputSystem::CreateDirectInput
//! @brief       Create the DirectInput object
//!              
//! @throw		 Core::RuntimeError if the create operation failed
//=========================================================================
void DirectXInputSystem::CreateDirectInput ( )
{
	HRESULT result = DirectInput8Create ( GetModuleHandle(NULL), 
										  DIRECTINPUT_VERSION,
										  IID_IDirectInput8A,
										  reinterpret_cast<LPVOID*>(&m_directInput),
										  0 );

	if ( SUCCEEDED(result) )
	{
		return;
	}
	else
	{
		std::stringstream errorMessage;
		errorMessage << "Error, couldn't create DirectInput device! Error code " 
					 << DirectInputErrorCodeToString ( result )
					 << std::endl;

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );

	}

}
//End DirectXInputSystem::CreateDirectInput



//=========================================================================
//! @function    DirectXInputSystem::CreateKeyboard
//! @brief       Create the keyboard object
//!              
//! @throw		 Core::RuntimeError if the create operation failed
//=========================================================================
void DirectXInputSystem::CreateKeyboard ( )
{
	m_keyboard = boost::shared_ptr<Core::Keyboard>( new DirectXKeyboard(*this) );
}
//End DirectXInputSystem::CreateKeyboard



//=========================================================================
//! @function    DirectXInputSystem::CreateMouse
//! @brief       Create the mouse object
//!
//! @throw		 Core::RuntimeError if the create operation failed
//=========================================================================
void DirectXInputSystem::CreateMouse ( )
{
	m_mouse = boost::shared_ptr<Core::Mouse>( new DirectXMouse(*this) );
}
//End  DirectXInputSystem::CreateMouse


