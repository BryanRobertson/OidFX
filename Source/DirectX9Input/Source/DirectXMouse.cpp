//======================================================================================
//! @file         DirectXMouse.cpp
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


#include "Core/Core.h"
#include "Core/Mouse.h"
#include "DirectX9Input/DirectXInputSystem.h"
#include "DirectX9Input/DirectXMouse.h"
#include "DirectX9Input/ErrorCodes.h"



using namespace DirectX9Input;



//=========================================================================
//! @function    DirectXMouse::DirectXMouse
//! @brief       DirectXMouse constructor
//!
//! @param       inputSystem [in] Input system that created this mouse
//!              
//! @throw       Core::RuntimeError if the DirectX mouse object couldn't be created
//=========================================================================
DirectXMouse::DirectXMouse ( DirectXInputSystem& inputSystem )
: Mouse(inputSystem)
{
	ZeroMemory(&m_oldMouseState, sizeof(m_oldMouseState) );

	m_directInput = inputSystem.GetDirectInput();
	m_windowHandle = inputSystem.GetWindowHandle();

	CreateMouse();
}
//End DirectXMouse::DirectXMouse


//=========================================================================
//! @function    DirectXMouse::~DirectXMouse
//! @brief       DirectXMouse Destructor
//=========================================================================
DirectXMouse::~DirectXMouse ()
{
	if ( m_mouse )
	{
		m_mouse->Unacquire();
	}
}
//End DirectXMouse::~DirectXMouse


//=========================================================================
//! @function    DirectXMouse::Update
//! @brief       Updates the mouse and calls any event handlers
//!              
//=========================================================================
void DirectXMouse::Update ( )
{
	DIMOUSESTATE mouseState;
	ZeroMemory(&mouseState, sizeof(mouseState));

	HRESULT result = m_mouse->GetDeviceState( sizeof(DIMOUSESTATE), &mouseState );

	if ( FAILED(result) )
	{
		result = AcquireMouse();

		if ( FAILED(result) )
		{
			
			#if 0
			std::cerr << __FUNCTION__ " Error, couldn't get mouse state. Error code "
					<< DirectInputErrorCodeToString ( result )
					<< std::endl;
			#endif

			return;
		}
	}

	//Handle mouse move events
	if ( (mouseState.lX != 0) || (mouseState.lY !=0) )
	{
		m_event.OnMouseMove ( mouseState.lX, mouseState.lY );
	}

	//Handle mouse scroll wheel events
	if ( mouseState.lZ !=0 )
	{
		m_event.OnMouseScroll ( mouseState.lZ );
	}

	//Handle mouse button down events
	if ( (mouseState.rgbButtons[0] & 0x80) )
	{	
		m_event.OnMouseButtonDown(Core::MOUSEBUTTON_LEFT);
	}

	if ( (mouseState.rgbButtons[1] & 0x80) )
	{	
		m_event.OnMouseButtonDown(Core::MOUSEBUTTON_RIGHT);
	}

	if ( (mouseState.rgbButtons[2] & 0x80) )
	{	
		m_event.OnMouseButtonDown(Core::MOUSEBUTTON_MIDDLE);
	}

	//Handle mouse button up events
	if ( (!(mouseState.rgbButtons[0] & 0x80)) 
		&& (m_oldMouseState.rgbButtons[0] & 0x80) )
	{	
		m_event.OnMouseButtonUp(Core::MOUSEBUTTON_LEFT);
	}

	if ( (!(mouseState.rgbButtons[1] & 0x80)) 
		&& (m_oldMouseState.rgbButtons[1] & 0x80) )
	{	
		m_event.OnMouseButtonUp(Core::MOUSEBUTTON_RIGHT);
	}

	if ( (!(mouseState.rgbButtons[2] & 0x80)) 
		&& (m_oldMouseState.rgbButtons[2] & 0x80) )
	{	
		m_event.OnMouseButtonUp(Core::MOUSEBUTTON_MIDDLE);
	}

	m_oldMouseState = mouseState;
	
}
//End DirectXMouse::Update



//=========================================================================
//! @function    DirectXMouse::CreateMouse
//! @brief       
//!              
//! @return      
//! @throw       
//=========================================================================
void DirectXMouse::CreateMouse ()
{
	
	//Create the mouse
	HRESULT result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);

	if ( FAILED(result) )
	{
		std::stringstream errorMessage;
		errorMessage << "Error, couldn't create mouse object! Error code " 
					 << DirectInputErrorCodeToString(result)
					 << std::endl;

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	//Set the data format
	result = m_mouse->SetDataFormat(&c_dfDIMouse);

	if ( FAILED(result) )
	{
		std::stringstream errorMessage;
		errorMessage << "Error, couldn't set mouse data format! Error code " 
					 << DirectInputErrorCodeToString(result)
					 << std::endl;

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	//Set the cooperative level
	result = m_mouse->SetCooperativeLevel( m_windowHandle, DISCL_EXCLUSIVE | DISCL_FOREGROUND );

	if ( FAILED(result) )
	{
		std::stringstream errorMessage;
		errorMessage << "Error, couldn't set mouse cooperative level! Error code " 
					 << DirectInputErrorCodeToString(result)
					 << std::endl;

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	//Acquire the mouse
	AcquireMouse();

}
//End DirectXMouse::CreateMouse


