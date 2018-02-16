//======================================================================================
//! @file         DisplayModeList.h
//! @brief        Class containing a list of display modes
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

#ifndef RENDERER_DISPLAYMODELIST_H
#define RENDERER_DISPLAYMODELIST_H


#include "Renderer/DisplayMode.h"


//namespace Renderer
namespace Renderer
{

	//!@class	DisplayModeList
	//!@brief	Class containing a list of display modes
	class DisplayModeList
	{
		public:

			//Public types
			enum DisplayDepth
			{
				BITS_32 = 32,
				BITS_16 = 16
			};

			inline void  AddMode ( UInt bitsPerPixel, const DisplayMode& mode );
			inline const DisplayMode& GetMode ( UInt index, UInt bitsPerPixel ) const;

			inline UInt ModeCount( UInt bitsPerPixel ) const;

			inline bool IsEmpty() const throw();
		
		private:

			std::vector<DisplayMode> m_displayModes32Bit;
			std::vector<DisplayMode> m_displayModes16Bit;
	};
	//End class DisplayModeList



    //=========================================================================
    //! @function    DisplayModeList::AddMode
    //! @brief       Add a display mode to the list of display modes for
	//!				 that colour depth
	//!
	//!				 The index of the display mode within the display mode list 
	//!				 will be its order within the internal list.
	//!				 Note, this is not the same as the index assigned to it by
	//!				 the renderer, which can be accessed by calling the display mode's
	//!				 Index() method
    //!             
    //! @param       bitsPerPixel [in] Bits per pixel of the display mode
    //! @param       mode		  [in] Display mode to add
    //!              
    //! @throw       
    //=========================================================================
	void DisplayModeList::AddMode ( UInt bitsPerPixel, 
									const DisplayMode& mode ) 
	{
		switch ( bitsPerPixel )
		{
			case BITS_32:
				m_displayModes32Bit.push_back(mode);
				return;

			case BITS_16:
				m_displayModes16Bit.push_back(mode);
				return;

			default:
				debug_assert ( false, "Error! Invalid display mode!" );
				return;
		}

	}
	//End DisplayModeList::AddMode



    //=========================================================================
    //! @function    DisplayModeList::GetMode
    //! @brief       Get the display mode at index for the colour depth specified
    //!              
    //! @param       index		  [in] Zero based index of the display mode
    //! @param       bitsPerPixel [in] Bits per pixel of the display mode
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	const DisplayMode& DisplayModeList::GetMode ( UInt index, UInt bitsPerPixel ) const
	{
		switch ( bitsPerPixel )
		{
			case BITS_32:
				debug_assert ( index < m_displayModes32Bit.size(), "Invalid display mode index" );
				return m_displayModes32Bit[index];
				

			case BITS_16:
				debug_assert ( index < m_displayModes16Bit.size(), "Invalid display mode index" );
				return m_displayModes16Bit[index];

			default:
				debug_assert ( false, "Error! Invalid display mode!" );
		}
	}
	//End DisplayModeList::GetMode



    //=========================================================================
    //! @function    DisplayModeList::ModeCount
    //! @brief       Return the number of modes for the colour depth specified
    //!              
	//! @param		 bitsPerPixel [in]
    //!              
    //! @return      The number of display modes for the colour depth specified
    //! @throw       
    //=========================================================================
	UInt DisplayModeList::ModeCount(UInt bitsPerPixel) const
	{
		switch ( bitsPerPixel )
		{
			case BITS_32:
				return m_displayModes32Bit.size();
				

			case BITS_16:
				return m_displayModes16Bit.size();

			default:
				debug_assert ( false, "Error! Invalid display mode!" );
				return 0;
		}
	}
	//End DisplayModeList::ModeCount 


    //=========================================================================
    //! @function    DisplayModeList::IsEmpty
    //! @brief       Return true if the list is empty, false otherwise
    //!              
    //!              
    //! @return      true if the list is empty, false otherwise
    //=========================================================================
	bool DisplayModeList::IsEmpty() const
	{
		if ( (!m_displayModes32Bit.empty()) && (!m_displayModes16Bit.empty()) )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	//End DisplayModeList::IsEmpty


};
//end namespace Renderer


#endif
//#ifndef RENDERER_DISPLAYMODELIST_H

