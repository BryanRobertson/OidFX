//======================================================================================
//! @file         Controller.h
//! @brief        Base class for a controller device
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

#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <map>
#include "Input/Button.h"
#include "Input/Axis.h"


//namespace Input
namespace Input
{


	//!@class	Controller
	//!@brief	Base class for a controller device
	class Controller
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			Controller ( );
			virtual ~Controller ( );


            //=========================================================================
            // Public methods
            //=========================================================================
			void Bind ( Button& button, UInt buttonID );
			void Bind ( Axis& axis, UInt axisID );

		protected:

            //=========================================================================
            // Protected types
            //=========================================================================
			typedef std::map<UInt, Button>	ButtonStore;
			typedef std::map<UInt, Axis>	AxisStore;

            //=========================================================================
            // Protected methods
            //=========================================================================
			inline void AddButton ( Button& button );
			inline void AddAxis   ( Axis& axis );


            //=========================================================================
            // Protected data
            //=========================================================================
			ButtonStore	m_buttons;
			AxisStore	m_axis;
	};
	//End class Controller


    //=========================================================================
    //! @function    Controller::AddButton
    //! @brief       Add a button to the controllers list of buttons
    //!              
    //! @param       button [in]
    //! @throw       
    //=========================================================================
	void Controller::AddButton ( Button& button )
	{
		m_buttons[button.ID()] = button;
	}
	//End Controller::AddButton


    //=========================================================================
    //! @function    Controller::AddAxis
    //! @brief       Add an axis to the controllers list of axis's
    //!              
    //! @param       axis [in]
    //!              
    //=========================================================================
	void Controller::AddAxis ( Axis& axis )
	{
		m_axis[axis.ID()] = axis;
	}	
	//End Controller::AddAxis


}
//End namespace Input



#endif
//#ifndef INPUT_CONTROLLER_H

