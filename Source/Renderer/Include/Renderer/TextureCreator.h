//======================================================================================
//! @file         TextureCreator.h
//! @brief        ITextureCreator interface. Interface for objects that
//!				  instantiate a specific sub-class derived from Texture
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 15 June 2005
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


#ifndef RENDERER_TEXTURECREATOR_H
#define RENDERER_TEXTURECREATOR_H


#include "Renderer/RendererTypes.h"


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declarations
    //=========================================================================
	class Texture;



	//!@class	ITextureCreator
	//!@brief	ITextureCreator interface. Interface for objects that instantiate
	//!			subclasses of Texture
	class ITextureCreator
	{
		public:

			virtual ~ITextureCreator()	{		};

			virtual boost::shared_ptr<Texture> CreateTextureFromFile( ETextureType type, const Char* fileName, UInt quality, UInt usage, UInt flags ) = 0;
			virtual boost::shared_ptr<Texture> CreateTexture ( ETextureType type, UInt width, UInt height, Imaging::PixelFormat format,
																UInt quality, UInt usage, UInt flags ) = 0;
	};
	//End class ITextureCreator


};
//end namespace Renderer


#endif
//#ifndef RENDERER_TEXTURECREATOR_H
