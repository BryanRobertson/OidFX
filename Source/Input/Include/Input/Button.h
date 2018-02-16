//======================================================================================
//! @file         Button.h
//! @brief        Class representing a button on a controller
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 18 July 2005
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

#ifndef INPUT_BUTTON_H
#define INPUT_BUTTON_H


#include "Input/ControlledValueType.h"
#include "Input/Control.h"


//namespace Input
namespace Input
{

	typedef Control<bool, UInt>				Button;
	typedef Button::ControlledValueType		ButtonControlledValue;	

};
//end namespace Input



#endif
//#ifndef INPUT_BUTTON_H

