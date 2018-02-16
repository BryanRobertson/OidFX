//======================================================================================
//! @file         Colour4i.h
//! @brief        Class to store a 32 bit RGBA colour in integer format
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 19 January 2005
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


#ifndef CORE_COLOUR4I_H
#define CORE_COLOUR4I_H


//namespace Core
namespace Core
{

	//!@class	Colour4i
	//!@brief	Class to store a colour in 32 bit RGBA format
	class Colour4i
	{

		public:

			//Constructors/Destructor
			inline Colour4i ( UInt red = 255, UInt green = 255, UInt blue = 255, UInt alpha = 255) throw();

			//Accessors
			UInt Red	( ) const throw()		{ return m_red;		}
			UInt Green	( ) const throw()		{ return m_green;	}
			UInt Blue	( ) const throw()		{ return m_blue;	}
			UInt Alpha	( ) const throw()		{ return m_alpha;	}
			UInt ToInteger ( ) const throw()	{ return m_rgba;	}

			//Mutators
			void Red	 ( UInt red   ) throw()	{ m_red = red;		}
			void Green	 ( UInt green ) throw()	{ m_green = green;	}
			void Blue	 ( UInt blue  ) throw()	{ m_blue = blue;	}
			void Alpha	 ( UInt alpha ) throw()	{ m_alpha = alpha;	}

			inline void Set ( UInt red, UInt green, UInt blue, UInt alpha ) throw();

		private:

			union
			{
				UInt32 m_rgba;

				struct
				{
					UInt8 m_red;
					UInt8 m_green;
					UInt8 m_blue;
					UInt8 m_alpha;
				};
			};

	};
	//end class Colour4i



	//=========================================================================
	//! @function    Core::Colour4i::Colour4i
	//! @param       red 
	//! @param       green 
	//! @param       blue 
	//! @param       alpha 
	//=========================================================================
	Colour4i::Colour4i ( UInt red, UInt green, UInt blue, UInt alpha ) throw()
	: m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
	{
	}
	//end Colour4i::Constructor



    //=========================================================================
    //! @function    Core::Colour4i::Set
    //! @param       red 
    //! @param       green 
    //! @param       blue 
    //! @param       alpha 
    //=========================================================================
	void Colour4i::Set ( UInt red, UInt green, UInt blue, UInt alpha ) throw()
	{
		red = m_red;
		green = m_green;
		blue = m_blue;
		alpha = m_alpha;
	}
	//end Colour4i::Set


};//end namespace Core


#endif
//ifndef CORE_COLOUR4I_H
