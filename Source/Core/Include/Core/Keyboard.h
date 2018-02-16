//======================================================================================
//! @file         Keyboard.h
//! @brief        Controller class representing a keyboard
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

#ifndef CORE_KEYBOARD_H
#define CORE_KEYBOARD_H


#include "Core/Event.h"
#include "Core/VirtualKeyCodes.h"
#include "Core/KeyboardEvent.h"
#include "Core/KeyboardSensitive.h"


//=========================================================================
// Forward declaration
//=========================================================================
namespace Core { class InputSystem;	}



//namespace Core
namespace Core
{


	//!@class	Keyboard
	//!@brief	Base class for the keyboard, allowing objects to be notified of keyboard events
	class Keyboard
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			inline Keyboard( InputSystem& inputSystem );
			virtual ~Keyboard() {}


            //=========================================================================
            // Public methods
            //=========================================================================
			virtual void Update ( ) = 0;	

			EventConnection	RegisterEventHandler ( IKeyboardSensitive& keyboardHandler ) 
											{ return m_event.Connect(keyboardHandler);	}


   		protected:

            //=========================================================================
            // Private data
            //=========================================================================
			KeyboardEvent	m_event;
			InputSystem&	m_inputSystem;

	};
	//End class Keyboard



    //=========================================================================
    //! @function    Keyboard::Keyboard
    //! @brief       Keyboard constructor
    //!              
    //! @param       inputSystem 
    //!              
    //=========================================================================
	Keyboard::Keyboard ( InputSystem& inputSystem )
		: m_inputSystem(inputSystem)
	{

	}
	//End Keyboard::Keyboard

}
//end namespace Core


#endif
//#ifndef CORE_KEYBOARD_H
