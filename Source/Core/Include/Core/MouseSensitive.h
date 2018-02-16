//======================================================================================
//! @file         MouseSensitive.h
//! @brief        IMouseSensitive interface. Interface for classes interested in
//!				  mouse state
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


#ifndef CORE_MOUSESENSITIVE_H
#define CORE_MOUSESENSITIVE_H


//namespace Core
namespace Core
{

	enum EMouseButton
	{
		MOUSEBUTTON_LEFT,
		MOUSEBUTTON_RIGHT,
		MOUSEBUTTON_MIDDLE
	};

	//!@class	IMouseSensitive
	//!@brief	Interface for classes interested in keyboard events
	class IMouseSensitive
	{
		public:

			virtual void OnMouseMove		( Int movementX, Int movementY ) = 0;
			virtual void OnMouseButtonDown  ( UInt buttonIndex ) = 0; 
			virtual void OnMouseButtonUp	( UInt buttonIndex ) = 0;
			virtual void OnMouseScroll		( Int scroll ) = 0;

	};
	//end class IMouseSensitive


};
//end namespace Core


#endif
//#ifndef CORE_MOUSESENSITIVE_H