//======================================================================================
//! @file         DirectXTexture.h
//! @brief        Specialisation of Texture for DirectX
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

#ifndef DIRECTX9RENDERER_DIRECTXTEXTURE_H
#define DIRECTX9RENDERER_DIRECTXTEXTURE_H


#include <atlbase.h> //CComPtr
#include "Renderer/Texture.h"
#include "Imaging/PixelFormat.h"



//=========================================================================
// Forward declarations
//=========================================================================
class ID3DTexture9;
namespace DirectX9Renderer { class DirectXRenderer; }


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


	//!@class	DirectXTexture
	//!@brief	Specialisation of Texture for DirectX
	class DirectXTexture : public Renderer::Texture
	{
		public:

			DirectXTexture ( DirectXRenderer& renderer, Renderer::ETextureType type, const Char* name, 
							UInt quality, UInt usage, UInt flags );
			
			DirectXTexture( DirectXRenderer& renderer, Renderer::ETextureType type, UInt width, UInt height, 
							Imaging::PixelFormat format, UInt quality, UInt usage, UInt flags );

			//Bind the texture to a texture stage
			bool Bind( Renderer::ETextureStageID stageIndex ) throw();

			//Set from image
			bool SetFromImage ( const Imaging::Image& image ) throw();

			//IRestorable implementation
			virtual bool RequiresRestore () const throw();
			virtual void PrepareForRestore( bool forceRestore ) throw();
			virtual void Restore( bool forceRestore ) throw();

			//Resource method implementations
			void Unload() {  /*Doesn't do anything at the moment*/  }

			//Create the texture
			void Create ( );

		protected:

			virtual void CreateFromFile ( );
			virtual void CreateEmpty ( );

			//Protected methods
			Renderer::ScopedTextureLock LockImplementation ( UInt level, Renderer::ELock lockOptions );
			void UnlockImplementation ( );

			//Protected data
			DirectXRenderer&			m_renderer;
			CComPtr<IDirect3DTexture9>	m_texture;
			bool						m_requiresRestore;
			D3DPOOL						m_pool;

	};
	//End DirectXTexture


};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_DIRECTXTEXTURE_H
