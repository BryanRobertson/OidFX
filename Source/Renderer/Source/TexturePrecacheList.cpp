//======================================================================================
//! @file         TexturePrecacheList.cpp
//! @brief        Contains a list of textures to be precached, and references to handles
//!				  to be initialised.
//!
//!				  Effects add textures that need to be loaded to a TexturePrecacheList.
//!				  The application can then load all textures in one go, making it easier
//!				  for the application to track which texures are being loaded.
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 28 June 2005
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
#include "Renderer/TexturePrecacheList.h"


using namespace Renderer;


//=========================================================================
//! @function    TexturePrecacheList::AddToPrecacheList
//! @brief       Add an entry to the list of textures to be precached
//!              
//!				 It is not guaranteed that the quality, usage, and flags 
//!				 of the texture will match those passed to this function.
//!				 This is unavoidable, due to the fact that only one copy of
//!				 the texture is loaded
//!				 
//! @param       handle		[out] Texture handle. This will be set to a handle
//!								  to the texture
//! @param       type		[in]  Texture type
//! @param       fileName	[in]  Filename
//! @param       quality	[in]  Quality
//! @param       usage		[in]  Usage
//! @param       flags		[in]  Flags
//!              
//! @return      
//! @throw       
//=========================================================================
void TexturePrecacheList::AddToPrecacheList ( HTexture& handle, ETextureType type, const Char* fileName,
											  UInt quality, UInt usage, UInt flags )
{
	Entry entry ( handle, type, fileName, quality, usage, flags );

	m_precacheList.push_back(entry);
}
//End TexturePrecacheList::AddToPrecacheList



//=========================================================================
//! @function    TexturePrecacheList::PrecacheAll
//! @brief       Precache all textures in the list, removing entries from the list
//!				 as they are precached
//! 
//! @param		 renderer [in] Renderer to request resources from
//!      
//=========================================================================
void TexturePrecacheList::PrecacheAll( IRenderer& renderer )
{
	for ( UInt i=0; i < m_precacheList.size(); ++i )
	{
		Entry& entry = m_precacheList[i];

		try
		{
			entry.m_handle = renderer.AcquireTexture( entry.m_type, 
													  entry.m_fileName.c_str(),
													  entry.m_quality,
													  entry.m_usage,
													  entry.m_flags );
		}
		catch ( Core::RuntimeError& exp )
		{
			std::cerr << __FUNCTION__ << ": Couldn't load " << entry.m_fileName << std::endl;
			entry.m_handle = Core::NullHandle();
		}
	}

	m_precacheList.clear();
}
//End TexturePrecacheList::PrecacheAll