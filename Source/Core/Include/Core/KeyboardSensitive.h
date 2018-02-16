//======================================================================================
//! @file         KeyboardSensitive.h
//! @brief        IKeyboardSensitive interface. Interface for classes interested in
//!				  keyboard state
//!               
//! @author       Bryan Robertson
//! @date         Monday, 28 February 2005
//! @copyright    Bryan Robertson 2005
//
//				  This file is part of OidFX Engine.
//
//  			  OidFX Engine is free software; you can redistribute it and/or modify
//  			  it under the terms of the GNU General Public License as published by
//  			  the Free Software Foundation; either version 2 of the License, or
//  			  (at your option) any later version.
//
//  			  OidFX Engine is distributed in the hope that it will be useful,
//  			  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  			  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  			  GNU General Public License for more details.
//
//  			  You should have received a copy of the GNU General Public License
//  			  along with OidFX Engine; if not, write to the Free Software
//  			  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================


#ifndef CORE_KEYBOARDSENSITIVE_H
#define CORE_KEYBOARDSENSITIVE_H


#include "Core/VirtualKeyCodes.h"


//namespace Core
namespace Core
{

	//!@class	IKeyboardSensitive
	//!@brief	Interface for classes interested in keyboard events
	class IKeyboardSensitive
	{
		public:

			virtual void OnKeyDown ( UInt keyCode ) = 0;
			virtual void OnChar	   ( Char charValue, UInt repeats, bool prevKeyState ) = 0;
			virtual void OnKeyUp   ( UInt keyCode ) = 0;

	};
	//end class IKeyboardSensitive


};
//end namespace Core


#endif
//#ifndef CORE_KEYBOARDSENSITIVE_H