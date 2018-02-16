//======================================================================================
//! @file         TexturePrecacheList.h
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

#ifndef RENDERER_TEXTUREPRECACHELIST_H
#define RENDERER_TEXTUREPRECACHELIST_H


#include <deque>
#include "Renderer/Texture.h"


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declaration
    //=========================================================================
	class IRenderer;


	//!@class	TexturePrecacheList
	//!@brief	Contains a list of textures to be precached, and references to handles
	//!			to be initialised.
	//!
	//!			Effects add textures that need to be loaded to a TexturePrecacheList.
	//!			The application can then load all textures in one go, making it easier
	//!			for the application to track which texures are being loaded.      
	class TexturePrecacheList
	{
	
		public:

            //=========================================================================
            // Public methods
            //=========================================================================
			
			//Add a texture to be precached
			void AddToPrecacheList ( HTexture& handle, ETextureType type, const Char* fileName, 
									 UInt quality, UInt usage, UInt flags );

			//Precache all textures in the list, emptying out the list
			void PrecacheAll ( IRenderer& renderer );

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			struct Entry
			{
				Entry ( HTexture& handle, ETextureType type, std::string fileName,
						UInt quality, UInt usage, UInt flags )
						: m_handle(handle), m_type(type), m_fileName(fileName),
						 m_quality(quality), m_usage(usage), m_flags(flags)
				{
				}

				HTexture&		m_handle;
				ETextureType	m_type;
				std::string		m_fileName;
				UInt			m_quality;
				UInt			m_usage;
				UInt			m_flags;
			};

			typedef std::deque<Entry> PrecacheList;

            //=========================================================================
            // Private data
            //=========================================================================
			PrecacheList m_precacheList;

	};
	//End TexturePrecacheList


};
//end namespace Renderer




#endif
//#ifndef RENDERER_TEXTUREPRECACHELIST_H