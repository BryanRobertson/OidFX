//======================================================================================
//! @file         TextureManager.cpp
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


#include "Core/Core.h"
#include "Renderer/Texture.h"
#include "Renderer/TextureCreator.h"
#include "Renderer/TextureManager.h"


using namespace Renderer;




//=========================================================================
//! @function    TextureManager::AcquireTexture
//! @brief       Get a handle to a texture. If the texture is already
//!				 loaded, then a handle to the existing texture is returned
//!				 otherwise, the texture is loaded from disk
//!
//!				 If the texture is already loaded, but with a different type,
//!				 or if the texture could not be loaded, then the acquire will fail, and a RuntimeError will be thrown
//!
//!
//! @param       type	 [in] Type of texture TEXTURE_1D, TEXTURE_2D, or TEXTURE_CUBE	
//! @param       name	 [in] File name of the texture
//! @param		 quality [in] Quality level for the texture. Reserved for future use, set to zero.
//! @param       usage	 [in] Usage. Combination of flags from the ETextureUsage enumeration 
//! @param       flags	 [in] Flags. Reserved for future use, set to zero.
//!                            
//! @return      A handle to the texture, or a null handle if the texture could not be loaded
//! @throw       Core::RuntimeError
//=========================================================================
TextureManager::HandleType TextureManager::AcquireTexture ( ETextureType type, const Char* fileName, UInt quality, UInt usage, UInt flags )
{
	HandleType handle ( AcquireExistingResource(fileName) );

	if ( handle == Core::NullHandle() )
	{
		
		boost::shared_ptr<Texture> texture = m_creator->CreateTextureFromFile( type, fileName, quality, usage, flags );
		return AddNewResource ( texture );
	
	}
	else
	{
		if ( handle->Type() != type )
		{
			std::stringstream errorMessage;
			errorMessage << __FUNCTION__ << ": Error, texture " << fileName << " found, but is of different texture type!\n" 
						" Loading a texture twice with different texture types is not supported!" << std::endl;

			throw Core::RuntimeError( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
		}

		return handle;
	}

}
//End TextureManager::AcquireTexture



//=========================================================================
//! @function    TextureManager::CreateTexture
//! @brief       Create an empty texture
//!              
//! @param       type	 [in] Type of texture TEXTURE_1D, TEXTURE_2D, or TEXTURE_CUBE	
//! @param       width	 [in] Width 
//! @param       height  [in] Height
//! @param       format	 [in] Format of the texture
//! @param       quality [in] Quality level for the texture. Reserved for future use, set to zero
//! @param       usage   [in] Usage. Combination of flags from the ETextureUsage enumeration
//! @param       flags   [in] Flags. Reserved for future use, set to zero.
//!              
//! @return      A handle to the texture
//! @throw       Core::RuntimeError if the texture could not be created
//=========================================================================
TextureManager::HandleType TextureManager::CreateTexture  ( ETextureType type, UInt width, UInt height, 
															Imaging::PixelFormat format, UInt quality, UInt usage, UInt flags )
{
	
	boost::shared_ptr<Texture> texture = m_creator->CreateTexture( type, width, height, format, quality, usage, flags );
	
	return AddNewResource ( texture );	
}
//End TextureManager::CreateTexture


//=========================================================================
//! @function    TextureManager::RequiresRestore
//! @brief       Doesn't make much sense in this context, just returns false
//!              
//! @return      false
//=========================================================================
bool TextureManager::RequiresRestore() const
{
	return false;
}
//End TextureManager::RequiresRestore



//=========================================================================
//! @function    TextureManager::PrepareForRestore
//! @brief       Calls the PrepareForRestore method on all textures
//!              
//! @param       forceRestore [in] Force all textures to prepare for restore if true
//!              
//=========================================================================
void TextureManager::PrepareForRestore ( bool forceRestore )
{
	TextureManager::ResourceStore::iterator itr;

	for ( itr = Begin(); itr != End(); ++itr )
	{
		//If the object itr refers to is a valid texture
		//then restore it
		if ( *itr )
		{
			(*itr)->PrepareForRestore(forceRestore);
		}
	}
}
//End TextureManager::PrepareForRestore



//=========================================================================
//! @function    TextureManager::Restore
//! @brief       Calls the Restore method on all textures
//!              
//! @param       forceRestore [in] Force all textures to restore if true
//!              
//=========================================================================
void TextureManager::Restore ( bool forceRestore )
{
	TextureManager::ResourceStore::iterator itr;

	for ( itr = Begin(); itr != End(); ++itr )
	{
		//If the object itr refers to is a valid texture
		//then restore it
		if ( *itr )
		{
			(*itr)->Restore(forceRestore);
		}
	}
}
//End TextureManager::Restore