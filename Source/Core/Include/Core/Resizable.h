//======================================================================================
//! @file         Resizable.h
//! @brief        Defines the Resizable interface, defining an object that can be resized
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 13 January 2005
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

#ifndef CORE_RESIZABLE_H
#define CORE_RESIZABLE_H



//namespace Core
namespace Core
{
	
	//! @class IResizable
	//! @brief Interface for an object that can be resized
	class IResizable
	{
		public:

			virtual void Resize ( UInt width, UInt height ) = 0;

	};
	//end class Resizable

};
//end namespace Core

#endif
//#ifndef CORE_RESIZABLE_H
