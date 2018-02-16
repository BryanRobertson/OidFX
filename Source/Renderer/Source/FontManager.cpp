//======================================================================================
//! @file         FontManager.cpp
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


#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/FontManager.h"
#include "Renderer/Font.h"


using namespace Renderer;



//=========================================================================
//! @function    FontManager::FontManager
//! @brief       FontManager constructor
//!              
//! @param       renderer [in] Reference to the renderer
//! @param       maxFonts [in] Maximum number of fonts that can exist
//!							   at any one time
//!              
//! @return      
//! @throw       
//=========================================================================
FontManager::FontManager ( IRenderer& renderer, UInt maxFonts )
: Core::ResourceManager<Font>(maxFonts), m_renderer(renderer)
{

}
//End FontManager::FontManager



//=========================================================================
//! @function    FontManager::CreateFontObject
//! @brief       Create a new font object, and return a handle to it
//!				 If the Create fails, then an exception will be thrown
//!         
//!	@see		 Font::Font
//!
//! @return      A handle to the new font
//! @throw       Core::RuntimeError if the creation of the font failed
//=========================================================================
FontManager::HandleType FontManager::CreateFontObject ( const Char* fontName, UInt fontSize, UInt fontWeight, UInt mipmapLevels,
												  bool italic, UInt quality )
{
	boost::shared_ptr<Font> newFont( new Font(m_renderer, fontName, fontSize, fontWeight, mipmapLevels,
											  italic, quality) );

	return AddNewResource(newFont);
}
//End FontManager::CreateFontObject