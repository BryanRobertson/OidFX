//======================================================================================
//! @file         Mouse.h
//! @brief        Class representing a mouse
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

#ifndef CORE_MOUSE_H
#define CORE_MOUSE_H


#include "Core/Event.h"
#include "Core/MouseEvent.h"
#include "Core/MouseSensitive.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace Core { class InputSystem;	}


//namespace Core
namespace Core
{

	//!@class	Mouse
	//!@brief	Class representing a mouse, allowing objects to be notified
	//!			of mouse events
	class Mouse
	{

		public:

			//=========================================================================
            // Constructors/Destructor
            //=========================================================================
			inline Mouse( InputSystem& inputSystem );
			virtual ~Mouse()	{}


            //=========================================================================
            // Public methods
            //=========================================================================
			virtual void Update ( ) = 0;	

			EventConnection	RegisterEventHandler ( IMouseSensitive& mouseHandler ) 
										{ return m_event.Connect(mouseHandler);	}


   		protected:

            //=========================================================================
            // Private data
            //=========================================================================
			MouseEvent		m_event;
			InputSystem&	m_inputSystem;

	};
	//End class Mouse



    //=========================================================================
    //! @function    Mouse::Mouse
    //! @brief       Mouse constructor
    //!              
    //! @param       inputSystem 
    //!              
    //=========================================================================
	Mouse::Mouse ( InputSystem& inputSystem )
		: m_inputSystem(inputSystem)
	{

	}
	//End Mouse::Mouse

}
//end namespace Core


#endif
//#ifndef CORE_MOUSE_H

