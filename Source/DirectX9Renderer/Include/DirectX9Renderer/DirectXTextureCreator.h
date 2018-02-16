//======================================================================================
//! @file         DirectXTextureCreator.h
//! @brief        Implementation of ITextureCreator that instantiates DirectXTexture objects
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


#ifndef DIRECTX9RENDERER_DIRECTXTEXTURECREATOR_H
#define DIRECTX9RENDERER_DIRECTXTEXTURECREATOR_H



#include "Renderer/TextureCreator.h"
#include "DirectX9Renderer/DirectXTexture.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace Renderer
{
	class Texture;
}


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


	//!@class	DirectXTextureCreator
	//!@brief	Implementation of ITextureCreator that instantiates DirectXTexture objects
	class DirectXTextureCreator : public Renderer::ITextureCreator
	{
		public:

			//Constructor
			inline DirectXTextureCreator ( DirectXRenderer& renderer );

			//Create texture
			inline boost::shared_ptr<Renderer::Texture> CreateTextureFromFile( Renderer::ETextureType type, const Char* fileName, 
																				UInt quality, UInt usage, UInt flags );

			inline boost::shared_ptr<Renderer::Texture> CreateTexture ( Renderer::ETextureType type, 
																		UInt width, UInt height, Imaging::PixelFormat format, 
																		UInt quality, UInt usage, UInt flags );

		private:

			//Private data
			DirectXRenderer& m_renderer;

	};
	//End class DirectXTextureCreator



    //=========================================================================
    //! @function    DirectXTextureCreator::DirectXTextureCreator
    //! @brief       DirectXTextureCreator constructor
    //!              
    //! @param       renderer [in] Reference to the renderer.
    //!              
    //=========================================================================
	DirectXTextureCreator::DirectXTextureCreator ( DirectXRenderer& renderer )
		: m_renderer(renderer)
	{
	}
	//End DirectXTextureCreator::DirectXTextureCreator



    //=========================================================================
    //! @function    DirectX9Renderer::CreateTextureFromFile
    //! @brief       Create a DirectXTexture object from file
    //!              
    //! @param       type		[in] 
    //! @param       fileName	[in]
    //! @param       usage		[in]
    //! @param       flags		[in]
    //!              
    //! @return      A pointer to a new DirectXTexture object
    //! @throw       Core::RuntimeError if the texture could not be created
    //=========================================================================
	boost::shared_ptr<Renderer::Texture> DirectXTextureCreator::CreateTextureFromFile ( Renderer::ETextureType type, const Char* fileName, 
																					UInt quality, UInt usage, UInt flags )
	{

		boost::shared_ptr<DirectXTexture> texturePointer;

		//In future we could create different texture objects, based on whether or not the 
		//type is TEXTURE_CUBEMAP. For the moment, cubemaps are not supported
		switch ( type )
		{
			case Renderer::TEXTURE_1D:
			case Renderer::TEXTURE_2D:
			case Renderer::TEXTURE_CUBEMAP:
			{
					 texturePointer = boost::shared_ptr<DirectXTexture>( new DirectXTexture(m_renderer, type, fileName, quality, usage, flags) );
			}
		}

		texturePointer->Create();

		return texturePointer;
	}
	//End DirectX9Renderer::CreateTexture




    //=========================================================================
    //! @function    DirectXTextureCreator::CreateTexture
    //! @brief       Create an empty texture
    //!              
    //! @param       type 	 [in]
    //! @param       format  [in]
    //! @param       width	 [in]
    //! @param       height  [in]
    //! @param       quality [in]
    //! @param       usage   [in]
    //! @param       flags	 [in]
    //!              
    //! @return      A pointer to the new texture
    //! @throw       Core::RuntimeError if the texture could not be created
    //=========================================================================
	boost::shared_ptr<Renderer::Texture> DirectXTextureCreator::CreateTexture ( Renderer::ETextureType type, 
																				UInt width, UInt height, Imaging::PixelFormat format,
																				UInt quality, UInt usage, UInt flags )
	{
		
		boost::shared_ptr<DirectXTexture> texturePointer;

		//In future we could create different texture objects, based on whether or not the 
		//type is TEXTURE_CUBEMAP. For the moment, cubemaps are not supported
		switch ( type )
		{
			case Renderer::TEXTURE_1D:
			case Renderer::TEXTURE_2D:
			case Renderer::TEXTURE_CUBEMAP:
			{
					 texturePointer = boost::shared_ptr<DirectXTexture>( new DirectXTexture(m_renderer, type, width, height,
																							format, quality, usage, flags) );
			}
		}

		texturePointer->Create();

		return texturePointer;
	}
	//End DirectXTextureCreator::CreateTexture



};
//end namespace DirectX9Renderer



#endif
//#ifndef DIRECTX9RENDERER_DIRECTXTEXTURECREATOR_H
