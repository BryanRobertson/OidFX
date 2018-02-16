//======================================================================================
//! @file         TextureManager.h
//! @brief        Resource manager class for textures
//!				  Responsible for the creation, storage, and destruction of textures.
//!				  Provides access to Texture objects, through handles 
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

#ifndef RENDERER_TEXTUREMANAGER_H
#define RENDERER_TEXTUREMANAGER_H


#include <boost/noncopyable.hpp>
#include "Core/ResourceManager.h"
#include "Core/Restorable.h"
#include "Renderer/RendererTypes.h"
#include "Renderer/RendererConstants.h"
#include "Imaging/PixelFormat.h"


//namespace Renderer
namespace Renderer
{


	//=========================================================================
    // Forward declaration
    //=========================================================================
	class ITextureCreator;


	//!@class	TextureManager
	//!@brief	Resource manager class for texture resources
	//!			
	//!			Responsible for the creation, storage, and destruction of textures.
	//!			Provides access to Texture objects, through handles
	class TextureManager : public Core::ResourceManager<Texture>, 
						   public Core::IRestorable, 
						   public boost::noncopyable
	{
		
		public:

			inline TextureManager ( ITextureCreator& creator );
			~TextureManager () { std::clog << "Texture manager destroyed" << std::endl; }

			HandleType AcquireTexture ( ETextureType type, const Char* fileName, UInt quality, UInt usage, UInt flags );
			
			HandleType CreateTexture  ( ETextureType type, UInt width, UInt height, Imaging::PixelFormat format, 
									    UInt quality, UInt usage, UInt flags );

			//IRestorable implementation
			bool RequiresRestore() const;
			void PrepareForRestore( bool forceRestore );
			void Restore( bool forceRestore );

		private:

			ITextureCreator* m_creator;
	
	};
	//End class TextureManager



    //=========================================================================
    //! @function    TextureManager::TextureManager
    //! @brief       Construct the texture manager
    //!              
    //! @param       creator [in] Creator object used to create textures
    //!              
    //=========================================================================
	TextureManager::TextureManager ( ITextureCreator& creator )
		: Core::ResourceManager<Texture>(g_maxTextures), m_creator(&creator)
	{
		std::clog << __FUNCTION__ ": Texture manager initialised" << std::endl;		
	}
	//End TextureManager::TextureManager


};
//end namespace Renderer


#endif
//#ifndef RENDERER_TEXTUREMANAGER_H