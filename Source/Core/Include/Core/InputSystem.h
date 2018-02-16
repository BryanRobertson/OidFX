//======================================================================================
//! @file         InputSystem.h
//! @brief        Base class for objects that manage an underlying input API
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


#ifndef CORE_INPUTSYSTEM_H
#define CORE_INPUTSYSTEM_H


#include <boost/shared_ptr.hpp>
#include "Core/Keyboard.h"
#include "Core/Mouse.h"
#include "Core/Restorable.h"


//namespace Core
namespace Core
{


	//!@class	 InputSystem
	//!@brief	 Base class for objects that manage an underlying input API
	class InputSystem
	{
		public:

			inline InputSystem ( ) throw();
			virtual ~InputSystem ( ) {}


            //=========================================================================
            // Public methods
            //=========================================================================
			virtual void Update() = 0;

			inline EventConnection	RegisterKeyboardHandler ( IKeyboardSensitive& keyboardHandler );
			inline EventConnection	RegisterMouseHandler ( IMouseSensitive& mouseHandler );

			Keyboard&	GetKeyboard()	{ return *m_keyboard;	}
			Mouse&		GetMouse()		{ return *m_mouse;		}

		protected:

			boost::shared_ptr<Keyboard> m_keyboard;
			boost::shared_ptr<Mouse>	m_mouse;
	};
	//End class InputSystem



    //=========================================================================
    //! @function    InputSystem::InputSystem
    //! @brief       InputSystem constructor
    //!              
    //=========================================================================
	InputSystem::InputSystem (  )
	{
	}
	//End InputSystem::InputSystem



    //=========================================================================
    //! @function    InputSystem::RegisterKeyboardHandler
    //! @brief       Register a keyboard handler to recieve keyboard input
    //!              
    //! @param       keyboardHandler 
    //!              
    //! @return      
    //=========================================================================
	EventConnection InputSystem::RegisterKeyboardHandler ( IKeyboardSensitive& keyboardHandler )
	{
		return m_keyboard->RegisterEventHandler(keyboardHandler);
	}
	//End InputSystem::RegisterKeyboardHandler



    //=========================================================================
    //! @function    InputSystem::RegisterMouseHandler
    //! @brief       Register a mouse handler to recieve mouse input
    //!              
    //! @param       mouseHandler 
    //!              
    //! @return      
    //=========================================================================
	EventConnection InputSystem::RegisterMouseHandler ( IMouseSensitive& mouseHandler )
	{
		return m_mouse->RegisterEventHandler(mouseHandler);
	}
	//End InputSystem::RegisterMouseHandler


}
//end namespace Core




#endif
//#ifndef CORE_INPUTSYSTEM_H