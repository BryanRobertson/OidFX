//======================================================================================
//! @file         FontManager.h
//! @brief        Resource manager for fonts
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

#ifndef RENDERER_FONTMANAGER_H
#define RENDERER_FONTMANAGER_H


#include "Core/ResourceManager.h"


//namespace Renderer
namespace Renderer
{

    //=========================================================================
    // Forward declaration
    //=========================================================================
	class Font;


	//!@class	FontManager
	//!@brief	Resource manager for fonts
	//!
	//!			A font is a resource which renders one of the system fonts into a texture,
	//!			and allows characters from that font to be drawn to the screen using the rendering API
	//!
	//!			Each font represents a rendering of a single system font at a particular size
	class FontManager : public Core::ResourceManager<Font>
	{

		public:

			FontManager( IRenderer& renderer, UInt maxFonts = 30 );

			HandleType CreateFontObject ( const Char* fontName, UInt fontSize, UInt fontWeight,
											UInt mipmapLevels, bool italic, UInt quality );

		private:

			IRenderer& m_renderer;
	};
	//End class FontManager


};
//end namespace Renderer



#endif
//#ifndef FONTMANAGER_H