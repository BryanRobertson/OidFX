//======================================================================================
//! @file         DisplayMode.h
//! @brief        Class encapsulating information about a display mode
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 30 May 2005
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

#ifndef RENDERER_DISPLAYMODE_H
#define RENDERER_DISPLAYMODE_H


#include <sstream>


//namespace Renderer
namespace Renderer
{

	//!@class	DisplayMode
	//!@brief	Class encapsulating information about a display mode
	class DisplayMode
	{
		public:

			inline DisplayMode ( UInt index, UInt width, UInt height, 
								 UInt bitsPerPixel, UInt refreshRate, 
								bool supportsWindowed, bool supportsStencil );

			inline UInt Index () const throw();
			inline UInt Width () const throw();
			inline UInt Height() const throw();
			inline UInt BitsPerPixel() const throw();
			inline UInt RefreshRate() const throw();
			inline const std::string& Description() const;
			inline bool SupportsWindowed() const throw();
			inline bool SupportsStencil() const throw();

		private:

			UInt m_index;
			UInt m_width;
			UInt m_height;
			UInt m_bitsPerPixel;
			UInt m_refreshRate;
			std::string m_description;
			bool m_supportsWindowed;
			bool m_supportsStencil;
	};
	//End class DisplayMode




    //=========================================================================
    //! @function    DisplayMode::DisplayMode
    //! @brief       DisplayMode constructor
    //!              
    //! @param       index			 [in]	Index of the display mode in the renderer's
	//!										display mode list. Note that this may not
	//!										be the same at the index of this mode in a
	//!										DisplayModeList object, due to the fact that
	//!										DisplayModeList might only be populated with 
	//!										display modes >= 640x480
	//!
    //! @param       width			 [in]	Width of the display mode in pixels
    //! @param       height			 [in]	Height of the display mode in pixels
    //! @param       bitsPerPixel	 [in]	Bits per pixel of the display mode
    //! @param       refreshRate	 [in]	Refresh rate of the display mode
    //! @param       supportsStencil [in]	Boolean indication whether or not the 
	//!										renderer supports stencil buffering in this mode
	//! @param		 supportsWindowed [in]  Supported in windowed mode
    //!              
    //=========================================================================
	DisplayMode::DisplayMode ( UInt index, UInt width, UInt height, 
								UInt bitsPerPixel, UInt refreshRate,
								bool supportsWindowed, bool supportsStencil )
	: m_index(index), m_width(width), m_height(height), m_bitsPerPixel(bitsPerPixel),
	  m_refreshRate(refreshRate), m_supportsWindowed(supportsWindowed),
	  m_supportsStencil(supportsStencil)
	{
		std::ostringstream desc;
		desc << m_width << "x" << m_height << "  -  " << m_refreshRate << "Hz";

		m_description = desc.str();
	}
	//End DisplayMode::DisplayMode



    //=========================================================================
    //! @function    DisplayMode::Index
    //! @brief       Return the index of the display mode
	//!
	//!				 Note that this might not be the same at the index of this mode in a
	//!				 DisplayModeList object, due to the fact that DisplayModeList might 
	//!				 only be populated with display modes >= 640x480, or some other
    //!              arbitrary size.
    //!              
    //! @return      Return the index of the display mode
    //=========================================================================
	UInt DisplayMode::Index () const
	{
	}
	//End DisplayMode::Index



    //=========================================================================
    //! @function    DisplayMode::Width
    //! @brief       Return the width of the display mode in pixels
    //! @return      The width of the display mode in pixels
    //=========================================================================
	UInt DisplayMode::Width () const
	{
		return m_width;
	}
	//End DisplayMode::Width 


    //=========================================================================
    //! @function    DisplayMode::Height
    //! @brief       Return the height of the display mode in pixels
    //! @return      The height of the display mode in pixels
    //=========================================================================
	UInt DisplayMode::Height() const
	{
		return m_height;
	}
	//End DisplayMode::Height


    //=========================================================================
    //! @function    DisplayMode::BitsPerPixel
    //! @brief       Return the number of bits per pixel of the display mode
    //!              
    //! @return      The number of the bits per pixel of the display mode
    //=========================================================================
	UInt DisplayMode::BitsPerPixel() const
	{
		return m_bitsPerPixel;
	}
	//End DisplayMode::BitsPerPixel



    //=========================================================================
    //! @function    DisplayMode::RefreshRate
    //! @brief       Return the refresh rate of the display mode
    //!              
    //! @return      The refresh rate of the display mode
    //=========================================================================
	UInt DisplayMode::RefreshRate() const
	{
		return m_refreshRate;
	}
	//End DisplayMode::RefreshRate



    //=========================================================================
    //! @function    DisplayMode::Description
    //! @brief       Return the text description of the display mode
    //!              
    //! @return      The text description of the display mode
    //=========================================================================
	const std::string& DisplayMode::Description () const
	{
		return m_description;
	}
	//End DisplayMode::Description



    //=========================================================================
    //! @function    DisplayMode::SupportsStencil
    //! @brief       Return whether or not the renderer supports use of the stencil
    //!              buffer in this mode
    //!              
    //! @return      true if the renderer supports use of the stencil buffer in this mode
	//!				 false if the renderer does not support use of the stencil buffer in this mode
    //=========================================================================
	bool DisplayMode::SupportsStencil() const
	{
		return m_supportsStencil;
	}
	//End DisplayMode::SupportsStencil



    //=========================================================================
    //! @function    DisplayMode::SupportsWindowed
    //! @brief       Indicates whether or not the display mode can be
    //!              supported in windowed mode
    //!              
    //! @return      true if the display mode can be used in windowed mode
	//!				 false if the display mode cannot be used in windowed mode
    //=========================================================================
	bool DisplayMode::SupportsWindowed() const
	{
		return m_supportsWindowed;
	}
	//End DisplayMode::SupportsWindowed

};
//end namespace Renderer


#endif
//#ifndef RENDERER_DISPLAYMODE_H

