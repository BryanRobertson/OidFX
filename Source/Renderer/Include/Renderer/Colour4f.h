//======================================================================================
//! @file         Colour4f.h
//! @brief        Class to store a colour in floating point RGBA format
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 04 June 2005
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

#ifndef RENDERER_COLOUR4F_H
#define RENDERER_COLOUR4F_H


//namespace Renderer
namespace Renderer
{


	//!@class	Colour4f
	//!@brief	Class to store a colour in floating point RGBA format
	class Colour4f
	{

		public:

			//Constructors/Destructor
			inline Colour4f ( Float red = 1.0f, Float green = 1.0f, Float blue = 1.0f, Float alpha = 1.0f) throw();
			inline Colour4f ( UInt red, UInt green, UInt blue, UInt alpha = 255 ) throw();

			//Accessors
			Float Red	( ) const throw()		{ return m_red;		}
			Float Green	( ) const throw()		{ return m_green;	}
			Float Blue	( ) const throw()		{ return m_blue;	}
			Float Alpha	( ) const throw()		{ return m_alpha;	}

			//Mutators
			void Red	 ( Float red   ) throw()	{ m_red = red;		}
			void Green	 ( Float green ) throw()	{ m_green = green;	}
			void Blue	 ( Float blue  ) throw()	{ m_blue = blue;	}
			void Alpha	 ( Float alpha ) throw()	{ m_alpha = alpha;	}

			inline void Set ( Float red, Float green, Float blue, Float alpha ) throw();

			inline operator UInt32() const throw();

		private:

			Float m_red;
			Float m_green;
			Float m_blue;
			Float m_alpha;

	};
	//end class Colour4f



	//=========================================================================
	//! @function    Colour4f::Colour4f
	//! @param       red 
	//! @param       green 
	//! @param       blue 
	//! @param       alpha 
	//=========================================================================
	Colour4f::Colour4f ( Float red, Float green, Float blue, Float alpha ) throw()
	: m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
	{
	}
	//end Colour4f::Constructor



    //=========================================================================
    //! @function    Colour4f::Colour4f
    //! @brief       Construct a Colour4f from four integer values
    //!              
    //! @param       red	[in] Red component, should be between 0 and 255
    //! @param       green	[in] Green component, should be between 0 and 255
    //! @param       blue	[in] Blue component, should be between 0 and 255
    //! @param       alpha	[in] Alpha component, should be between 0 and 255
    //!              
    //=========================================================================
	Colour4f::Colour4f ( UInt red, UInt green, UInt blue, UInt alpha ) throw()
	{
		m_red = red / 255.0f;
		m_green = green / 255.0f;
		m_blue = blue / 255.0f;
		m_alpha = alpha / 255.0f;
	}
	//End Colour4f::Colour4f(UInt,UInt,UInt,UInt)


    //=========================================================================
    //! @function    Colour4f::Set
    //! @param       red 
    //! @param       green 
    //! @param       blue 
    //! @param       alpha 
    //=========================================================================
	void Colour4f::Set ( Float red, Float green, Float blue, Float alpha ) throw()
	{
		red = m_red;
		green = m_green;
		blue = m_blue;
		alpha = m_alpha;
	}
	//end Colour4f::Set


    //=========================================================================
    //! @function    Colour4f::operator UInt32
    //! @brief       Conversion to a UInt32. 
    //!              
    //!				 Converts the colour into a packed ARGB integer format              
	//!
    //! @return      The colour in packed ARGB format
    //=========================================================================
	Colour4f::operator UInt32() const
	{
		UInt32 temp = 0;

		temp |=	(static_cast<UInt32>(Alpha()*255.0f) << 24 ) & 0xFF000000;
		temp |= (static_cast<UInt32>(Red()*255.0f)   << 16 ) & 0x00FF0000;
		temp |= (static_cast<UInt32>(Green()*255.0f) << 8  ) & 0x0000FF00;
		temp |= (static_cast<UInt32>(Blue()*255.0f) & 0x000000FF);

		return temp;
	}
	//End Colour4f::operator UInt32

};
//end namespace Renderer


#endif
//#ifndef RENDERER_COLOUR4F_H