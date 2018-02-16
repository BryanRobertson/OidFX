//======================================================================================
//! @file         Image.h
//! @brief        Class to store image data in various formats
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

#ifndef IMAGE_H
#define IMAGE_H


#include <boost/shared_array.hpp>
#include "Core/Colour4i.h"
#include "Imaging/PixelFormat.h"


//namespace Imaging
namespace Imaging
{

	//! @class	Image
	//! @brief	Class to store image data in various formats
	class Image
	{
		public:

			Image	( UInt width, UInt height, UInt pitch, PixelFormat format ) throw();
	
			//Public types
	
			//Buffer
			inline UChar*		GetBufferPointer ( ) throw();
			inline const UChar* GetBufferPointer ( ) const throw();

			//Dump to file
			void DumpToRAWFile ( const Char* fileName );

			//Accessors
			inline UInt		Width ( ) const	throw()				{ return m_width;		}
			inline UInt		Height( ) const throw()				{ return m_height;		}
			inline UInt		Pitch ( ) const throw()				{ return m_pitch;		}
			inline UInt		BitsPerPixel ( ) const throw()		{ return GetFormatBitsPerPixel ( m_format ); }
			inline PixelFormat Format( ) const throw()			{ return m_format;		}
			inline UInt Size ( ) const							{ return m_pixelData.size();	}

		private:

			//private methods
			void AllocateImageBuffer ( UInt width, UInt height, PixelFormat format );


			//private data
			std::vector<UChar>	m_pixelData;

			UInt				m_width;
			UInt				m_height;
			UInt				m_pitch;
			PixelFormat			m_format;

	};
	//end class Image



    //=========================================================================
    //! @function    Image::GetBufferPointer
    //! @brief       Get a pointer to the image's pixel buffer
    //!              
    //!              
    //! @return      A pointer to the image's pixel buffer
    //! @throw       
    //=========================================================================
	UChar* Image::GetBufferPointer ( )
	{
		return &(m_pixelData[0]);
	}
	//end Image::GetBufferPointer



	//=========================================================================
    //! @function    Image::GetBufferPointer
    //! @brief       Const version of GetBufferPointer
    //!              
    //!              
    //! @return      A const pointer to the image's pixel buffer
    //! @throw       
    //=========================================================================
	const UChar* Image::GetBufferPointer ( ) const
	{
		return &(m_pixelData[0]);
	}
	//end Image::GetBufferPointer


};
//end namespace Imaging

#endif
//#ifndef IMAGE_H
