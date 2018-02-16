//======================================================================================
//! @file         DirectXTexture.cpp
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

#include "Core/Core.h"
#include "Imaging/Image.h"
#include "Imaging/ImageRect.h"
#include "DirectX9Renderer/DirectX9Renderer.h"
#include "DirectX9Renderer/DirectXTexture.h"
#include "DirectX9Renderer/Formats.h"
#include "DirectX9Renderer/ErrorCodes.h"
#include "DirectX9Renderer/ConversionFunctions.h"



using namespace DirectX9Renderer;



//=========================================================================
//! @function    DirectXTexture::DirectXTexture
//! @brief       DirectXTexture constructor for a texture loaded from file
//!              
//! @param       renderer [in] Reference to the DirectX renderer, so 
//!							   the texture can access the Direct3D device
//! @param       type	  [in] Texture type. TEXTURE_1D, TEXTURE_2D or TEXTURE_CUBEMAP
//! @param       name	  [in] File name of the texture
//! @param		 quality  [in] Quality of the texture. Unused, reserved for future use, set to zero
//! @param       usage	  [in] Usage for the texture. Unused, reserved for future use
//!							   set to 0
//! @param       flags	  [in] Flags for the texture. Unused, reserved for future use 
//!              
//! @return      
//! @throw		 Core::RuntimeError if        
//=========================================================================
DirectXTexture::DirectXTexture ( DirectXRenderer& renderer, Renderer::ETextureType type, const Char* name, 
								 UInt quality, UInt usage, UInt flags )
: Texture(type, name, quality, usage, flags), 
  m_renderer(renderer), 
  m_requiresRestore(false),
  m_pool(D3DPOOL_MANAGED)
{
	
	if ( type == Renderer::TEXTURE_CUBEMAP )
	{
		throw Core::RuntimeError( "Error, cubemap textures are not supported yet!", 0,
								  __FILE__, __FUNCTION__, __LINE__ );
	}
}
//End DirectXTexture::DirectXTexture



//=========================================================================
//! @function    DirectXTexture::DirectXTexture
//! @brief       Construct an empty texture
//!              
//! @param		 renderer[in] Reference to the renderer             
//! @param       type    [in] Type of texture TEXTURE_1D, TEXTURE_2D, or TEXTURE_CUBE	
//! @param       width	 [in] Width of the texture
//! @param       height	 [in] Height of the texture
//! @param       format	 [in] Pixel format of the texture. Note that not all formats are supported
//! @param       quality [in] Quality. Reserved for future use, set to zero.
//! @param		 usage	 [in] Usage. Reserved for future use, set to zero.
//! @param       flags	 [in] Flags. Reserved for future use, set to zero.  
//=========================================================================
DirectXTexture::DirectXTexture ( DirectXRenderer& renderer, Renderer::ETextureType type, UInt width, UInt height, 
								 Imaging::PixelFormat format, UInt quality, UInt usage, UInt flags )
: Texture(type, width, height, format, quality, usage, flags),
  m_renderer(renderer),  
  m_requiresRestore(false),
  m_pool(D3DPOOL_MANAGED)

{

}
//End DirectXTexture::DirectXTexture



//=========================================================================
//! @function    DirectXTexture::Bind
//! @brief       Bind a texture to one of the renderer's texture stages
//!              
//! @param       stageIndex [in] Texture stage to bind to
//!              
//! @return      true if succeded, false if failed
//=========================================================================
bool DirectXTexture::Bind ( Renderer::ETextureStageID stageIndex )
{
	HRESULT result = m_renderer.Device()->SetTexture( static_cast<DWORD>(stageIndex), m_texture );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't bind texture to stageIndex " 
				  << static_cast<UInt>(stageIndex) << "! Error code " << D3DErrorCodeToString(result) << std::endl;
		
		return false;
	}
}
//End DirectXTexture::Bind



//=========================================================================
//! @function    DirectXTexture::SetFromImage
//! @brief       Set the contents of the texture from an image
//!				 Scales and converts formats automatically as necessary.              
//!
//! @param       image [in]
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXTexture::SetFromImage ( const Imaging::Image& image )
{
	//Convert the format
	D3DFORMAT sourceFormat;
	if ( !DirectX9Renderer::ConvertPixelFormatToD3D (image.Format(), sourceFormat) )
	{
		std::cerr << __FUNCTION__ ": Error, invalid image format!" << std::endl;
		return false;
	}

	//Get a pointer to the surface
	CComPtr<IDirect3DSurface9> surface;
	HRESULT result = m_texture->GetSurfaceLevel( 0, &surface );

	if ( SUCCEEDED(result) )
	{
		//Get a source rect
		RECT sourceRect;
		sourceRect.left = 0;
		sourceRect.right = image.Width()-1;
		sourceRect.top = 0;
		sourceRect.bottom = image.Height()-1;

		//Load the surface from memory
		result = D3DXLoadSurfaceFromMemory( surface,											//Destination surface
											0,													//Destination palette
											0,													//Destination rect
                                            (LPCVOID)(image.GetBufferPointer()),				 //Source pointer
											sourceFormat,										 //Source format
											(image.Width() + image.Pitch()) * (image.BitsPerPixel()/8),	//Source pitch
											0,													//Source palette
											&sourceRect,										//Source rect
											D3DX_DEFAULT,										//Filter
											0													//Colour key
										  );

		m_texture->GenerateMipSubLevels();

		if ( SUCCEEDED(result) )
		{
			return true;
		}
		else
		{
			std::cerr << __FUNCTION__ ": Error, couldn't load surface from memory!" << D3DErrorCodeToString(result) << std::endl;
		}

	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't get surface level! Error code " << D3DErrorCodeToString(result) << std::endl; 
		return false;
	}
}
//End DirectXTexture::SetFromImage



//=========================================================================
//! @function    DirectXTexture::RequiresRestore
//! @brief       Indicates whether or not a restore is required
//!              
//!              
//! @return      true if a restore is required, false if it is not required
//=========================================================================
bool DirectXTexture::RequiresRestore() const
{
	return m_requiresRestore;
}
//End DirectXTexture::IsLos



//=========================================================================
//! @function    DirectXTexture::PrepareForRestore
//! @brief       Prepare the texture to be restored when the device is lost
//!              
//!				 In the case of DirectXTexture, it releases the texture
//!				 so that it can be reloaded. Textures created in managed
//!				 memory may ignore this request, so long as forceRestore is false
//!
//! @param		 forceRestore [in] Forces a restore, regardless of whether it is
//!								   required
//=========================================================================
void DirectXTexture::PrepareForRestore( bool forceRestore )
{
	if ( (forceRestore) || (m_pool != D3DPOOL_MANAGED) )
	{
		m_requiresRestore = true;
		m_texture.Release();
	}
}
//End DirectXTexture::PrepareForRestore



//=========================================================================
//! @function    DirectXTexture::Restore
//! @brief       Restore the texture
//!
//!				 In the case of DirectXTexture, this recreates the 
//!				 texture object
//!              
//! @param       forceRestore [in]
//!              
//! @return      
//! @throw       
//=========================================================================
void DirectXTexture::Restore( bool forceRestore )
{
	if ( forceRestore || m_requiresRestore )
	{
		if (!m_requiresRestore)
		{
			//Failsafe to make sure we don't leak memory
			PrepareForRestore(true);
		}

		Create();
		m_requiresRestore = false;
	}
}
//End DirectXTexture::Restore



//=========================================================================
//! @function    DirectXTexture::Create
//! @brief       Create the texture
//!
//!				 Creates the Direct3D texture object
//!              
//! @throw       Core::RuntimeError if the texture could not be created
//=========================================================================
void DirectXTexture::Create ( )
{
	if ( CreatedFromFile() == true )
	{
		CreateFromFile();
	}
	else
	{
		CreateEmpty();
	}	
}
//End DirectXTexture::Create



//=========================================================================
//! @function    DirectXTexture::CreateFromFile
//! @brief       Create the texture from file
//!              
//! @throw       Core::RuntimeError if the texture could not be created
//=========================================================================
void DirectXTexture::CreateFromFile ( )
{
	D3DXIMAGE_INFO info;
	
	DWORD usageFlags = 0;

	if ( Usage() & Renderer::TEXUSAGE_DYNAMIC )
	{
		usageFlags |= D3DUSAGE_DYNAMIC;	
		//m_pool = D3DPOOL_SYSTEMMEM;
	}

	if ( Usage() & Renderer::TEXUSAGE_AUTOGENERATE_MIPMAPS  )
	{
		usageFlags |= D3DUSAGE_AUTOGENMIPMAP;
	}

	if ( Usage() & Renderer::TEXUSAGE_RENDERTARGET )
	{
		usageFlags |= D3DUSAGE_RENDERTARGET;
	}


	std::clog << "Loading texture " << Name() << std::endl;
	HRESULT result = D3DXCreateTextureFromFileEx ( m_renderer.Device(), //Device
												   Name().c_str(),		//File name
												   D3DX_DEFAULT,		//Width
												   D3DX_DEFAULT,		//Height
												   D3DX_DEFAULT,		//Mip levels
												   usageFlags,			//Usage
												   D3DFMT_UNKNOWN,		//Take the format from the file
												   m_pool,				//Memory pool to put file into
												   D3DX_DEFAULT,		//Filter
												   D3DX_DEFAULT,		//Mip filter
												   0,					//Colour keep, not used
												   &info,				//Pointer to our image info
												   0,					//Pointer to a pallete structure
                                                   &m_texture			//Pointer to our texture pointer
												   );

	if ( SUCCEEDED(result) )
	{
		m_width = info.Width;
		m_height = info.Height;

		ConvertD3DFormatToPixelFormat ( info.Format, m_format );

		std::clog << "Texture " << Name() << " loaded successfully" << std::endl;
		std::clog << "\tTexture dimensions = " << m_width << "x" << m_height << std::endl;
		std::clog << "\tTexture format = " << D3DFormatToString ( info.Format ) << std::endl;
	}
	else
	{
		
		std::ostringstream errorMessage;

		errorMessage << __FUNCTION__ << ": Error, couldn't load texture " << Name() 
				  << "! Error code " << D3DErrorCodeToString(result) << std::endl;

		std::cerr << errorMessage;

		throw Core::RuntimeError ( errorMessage.str().c_str(), result, __FILE__, __FUNCTION__, __LINE__ );
	}
}
//End DirectXTexture::CreateFromFile



//=========================================================================
//! @function    DirectXTexture::CreateEmpty
//! @brief       Create an empty texture
//!              
//! @throw       Core::RuntimeError if the texture could not be created
//=========================================================================
void DirectXTexture::CreateEmpty ()
{
	DWORD usageFlags = 0;

	if ( Usage() & Renderer::TEXUSAGE_DYNAMIC )
	{
		usageFlags |= D3DUSAGE_DYNAMIC;	
		//m_pool = D3DPOOL_SYSTEMMEM;
	}

	if ( Usage() & Renderer::TEXUSAGE_AUTOGENERATE_MIPMAPS  )
	{
		usageFlags |= D3DUSAGE_AUTOGENMIPMAP;
	}

	if ( Usage() & Renderer::TEXUSAGE_RENDERTARGET )
	{
		usageFlags |= D3DUSAGE_RENDERTARGET;
	}

	//Get the format
	D3DFORMAT format;

	if ( !ConvertPixelFormatToD3D( Format(), format) )
	{
		throw Core::RuntimeError ( "Invalid texture format", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

    HRESULT result = m_renderer.Device()->CreateTexture ( Width(),		//Width 
														  Height(),		//Height
														  0,			//Levels
														  usageFlags,	//Usage
														  format,		//Format
														  m_pool,		//Pool
														  &m_texture,	//Texture pointer
														  0);			//Shared handle, unused

	if ( SUCCEEDED(result) )
	{
		std::clog << __FUNCTION__ << ": Created texture successfully. "
					"Width = " << Width() << ", Height = " << Height() 
					<< ". Bits per pixel = " << BitsPerPixel() << std::endl;
		return;
	}
	else
	{
		std::ostringstream errorMessage;

		errorMessage << "Error, couldn't create texture! Error code " << D3DErrorCodeToString(result) << std::endl;

		throw Core::RuntimeError( errorMessage.str().c_str(), result, __FILE__, __FUNCTION__, __LINE__);
	}
}
//End DirectXTexture::CreateEmpty




//=========================================================================
//! @function    DirectXTexture::LockImplementation
//! @brief       Lock the texture
//!              
//! @param       level			[in] 
//! @param       lockOptions	[in]
//!              
//! @return      An object representing the lock, or a null lock if the lock failed
//=========================================================================
Renderer::ScopedTextureLock DirectXTexture::LockImplementation ( UInt level, Renderer::ELock lockOptions )
{
	
	DWORD dxFlags = 0;
	if ( lockOptions == Renderer::LOCK_DISCARD )
	{		
		dxFlags |= D3DLOCK_DISCARD;
	}

	if ( lockOptions == Renderer::LOCK_READONLY )
	{
		dxFlags |= D3DLOCK_READONLY;
	}

	D3DLOCKED_RECT rect;
	HRESULT result = m_texture->LockRect ( level, &rect, 0, dxFlags );

	if ( SUCCEEDED(result) )
	{
		Renderer::ScopedTextureLock lock(*this, reinterpret_cast<Byte*>(rect.pBits), level, rect.Pitch );
		std::clog << __FUNCTION__ << ": Texture locked successfully. Pointer = " << reinterpret_cast<UInt>(rect.pBits)
				  << " pitch = " << rect.Pitch << std::endl;

		return lock;
	}
	else
	{
		std::cerr << __FUNCTION__ << ": Texture lock failed: Error code " << D3DErrorCodeToString(result) << std::endl;
		return Renderer::ScopedTextureLock();
	}

}
//End DirectXTexture::LockImplementation


//=========================================================================
//! @function    DirectXTexture::UnlockImplementation
//! @brief       Unlock the texture
//!              
//=========================================================================
void DirectXTexture::UnlockImplementation ()
{
	HRESULT result = m_texture->UnlockRect ( GetLockObject().Level() );

	if ( SUCCEEDED(result) )
	{
		std::clog << __FUNCTION__ << "Texture level " << GetLockObject().Level() << " unlocked successfully" << std::endl;
	}
	else
	{
		std::cerr << __FUNCTION__ << ": Error, failed to unlock texture level " << GetLockObject().Level() 
				  << "! Error code " << D3DErrorCodeToString(result) << std::endl;
	}
}
//End DirectXTexture::UnlockImplementation