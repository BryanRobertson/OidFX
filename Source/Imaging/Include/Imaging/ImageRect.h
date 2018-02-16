//======================================================================================
//! @file         ImageRect.h
//! @brief        Class representing a rectangle on an image
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 22 June 2005
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

#ifndef IMAGERECT_H
#define IMAGERECT_H


//namespace Imaging
namespace Imaging
{

	//!@class	ImageRect
	//!@brief	Class representing a rectangle on an image
	class ImageRect
	{
		public:

			inline ImageRect ( UInt left, UInt right, UInt top, UInt bottom )
				: m_left(left), m_right(right), m_top(top), m_bottom(bottom)
			{
			}

			inline UInt Left() const		{ return m_left;   }
			inline UInt Right() const		{ return m_right;  }
			inline UInt Top() const			{ return m_top;	   }
			inline UInt Bottom() const		{ return m_bottom; }

		private:

			UInt m_left;
			UInt m_right;
			UInt m_top;
			UInt m_bottom;
	};
	//End class ImageRect

};
//end namespace Imaging


#endif
//#ifndef IMAGERECT_H
