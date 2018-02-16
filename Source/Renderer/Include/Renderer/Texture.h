//======================================================================================
//! @file         Texture.h
//! @brief        Base class for a texture resource
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

#ifndef RENDERER_TEXTURE_H
#define RENDERER_TEXTURE_H


#include <boost/noncopyable.hpp>
#include "Core/Resource.h"
#include "Core/Handle.h"
#include "Core/Restorable.h"
#include "Imaging/PixelFormat.h"
#include "Renderer/RendererTypes.h"
#include "Renderer/RendererStateConstants.h"
#include "Renderer/RendererBuffer.h" //ELock
#include "Renderer/ScopedTextureLock.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace Imaging
{
	class Image;
	class ImageRect;
}



//namespace Renderer
namespace Renderer
{


	//=========================================================================
    // Texture flags
    //=========================================================================
	enum ETextureFlags
	{
	};


    //=========================================================================
    // Texture usage
    //=========================================================================
	//! Flags which determine how a texture will be used
	enum ETextureUsage
	{
		TEXUSAGE_DEFAULT,					//! Default
		TEXUSAGE_DYNAMIC = 1,				//! Texture will be changed on a regular basis
		TEXUSAGE_RENDERTARGET = 2,			//! Texture will be used as a render target
		TEXUSAGE_AUTOGENERATE_MIPMAPS = 4,	//! Mipmaps will automatically be generated for the texture
		TEXUSAGE_DISCARDABLE = 8			//! Contents of the buffer can be discarded
	};



	//!@class	Texture
	//!@brief	Base class for a texture resource
	class Texture : public Core::Resource,
					public Core::IRestorable,
					public boost::noncopyable

	{
		public:

			//Friends
			friend class ScopedTextureLock;

			inline Texture( ETextureType type, const Char* name, UInt quality, UInt usage, UInt flags );
			inline Texture( ETextureType type, UInt width, UInt height, Imaging::PixelFormat format, 
							UInt quality, UInt usage, UInt flags );
			virtual ~Texture( ) { }

			//Bind the texture to a stageIndex
			virtual bool Bind( ETextureStageID stageIndex ) throw() = 0;

			//Set from image
			virtual bool SetFromImage ( const Imaging::Image& image ) throw() = 0;

			//Lock/Unlock
			inline ScopedTextureLock Lock( UInt level, ELock lockOptions );
			inline void Unlock ( );

			//Accessors
			inline ETextureType Type() const	{ return m_type;	}
			inline UInt	Quality() const			{ return m_quality; }
			inline UInt	Flags() const			{ return m_flags;	}
			inline UInt Usage() const			{ return m_usage;	}

			inline UInt Width() const			{ return m_width;	}
			inline UInt Height() const			{ return m_height;	}
			inline UInt BitsPerPixel() const	{ return Imaging::GetFormatBitsPerPixel(m_format);	}
			inline Imaging::PixelFormat Format() const { return m_format; }

			inline bool	 IsLocked() const throw()		{ return m_isLocked;	}
			inline ELock LockOptions() const throw()	{ return m_lockOptions; }
		
			inline bool CreatedFromFile() const throw()	{ return m_createdFromFile; }

		protected:

			//Protected methods
			virtual ScopedTextureLock LockImplementation ( UInt level, ELock lockOptions ) = 0;
			virtual void UnlockImplementation ( ) = 0;

			inline ScopedTextureLock& GetLockObject() { return *m_lock; }

			bool CreatedFromFile() { return m_createdFromFile; }

			//Protected data
			UInt				 m_width;
			UInt				 m_height;
			Imaging::PixelFormat m_format;

		private:

			//Private methods
			inline void SetLockPointer( ScopedTextureLock* lock ) { m_lock = lock;	}
		
			//Private data
			ETextureType m_type;
			UInt		 m_quality;
			UInt		 m_flags;
			UInt		 m_usage;
			
			bool		m_createdFromFile;
		
			ELock			   m_lockOptions;
			ScopedTextureLock* m_lock;
			bool			   m_isLocked;

	};
	//end class Texture


    //=========================================================================
    // Typedefs
    //=========================================================================
	typedef Core::Handle<Texture> HTexture;



    //=========================================================================
    //! @function    Texture::Texture
    //! @brief       Construct a texture that is to be loaded from file
    //!              
    //! @param       type		[in] Type of texture TEXTURE_1D, TEXTURE_2D, or TEXTURE_CUBE	
    //! @param       name		[in] File name of the texture
	//! @param		 quality	[in] Quality. Reserved for future use, set to zero.
    //! @param       usage		[in] Usage. Combination of the usage flags in the ETextureUsage enumeration
    //! @param       flags		[in] Flags. Reserved for future use, set to zero.
    //!              
    //=========================================================================
	Texture::Texture ( ETextureType type, const Char* name, UInt quality, UInt usage, UInt flags )
		: Resource(name), m_quality(quality), m_usage(usage), m_flags(flags),
		 m_width(0), m_height(0), m_format(Imaging::PXFMT_END), m_isLocked(false), m_createdFromFile(true), m_type(type)
	{

	}
	//End Texture::Texture



    //=========================================================================
    //! @function    Texture::Texture
    //! @brief       Construct an empty texture
    //!              
    //! @param       type    [in] Type of texture TEXTURE_1D, TEXTURE_2D, or TEXTURE_CUBE	
    //! @param       width	 [in] Width of the texture
    //! @param       height	 [in] Height of the texture
    //! @param       format	 [in] Pixel format of the texture. Note that not all formats are supported
    //! @param       quality [in] Quality. Reserved for future use, set to zero.
	//! @param		 usage	 [in] Usage. Combination of flags from the ETextureUsage enumeration
    //! @param       flags	 [in] Flags. Reserved for future use, set to zero.
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	Texture::Texture ( ETextureType type, UInt width, UInt height, Imaging::PixelFormat format, 
					   UInt quality, UInt usage, UInt flags )
	:	 Resource(""), m_quality(quality), m_usage(usage), m_flags(flags), m_type(type),
		 m_width(width), m_height(height), m_format(format), m_isLocked(false), m_createdFromFile(false)
	{
		
	}
	//End Texture::Texture


    //=========================================================================
    //! @function    Texture::Lock
    //! @brief       Lock the texture
	//!
	//!				 The lock may fail on certain rendering APIs, depending on
	//!				 the way the texture was created. 
	//!
	//!				 Locking multiple levels of a texture at the same time is not supported
	//!				 if the texture is already locked, then a null lock will be returned
    //!              
    //! @param       level		 [in]
    //! @param       lockOptions [in]
    //!              
    //! @return      A texture lock, or a null lock if the lock failed
    //=========================================================================
	ScopedTextureLock Texture::Lock ( UInt level, ELock lockOptions )
	{
		if ( IsLocked() )
		{
			std::cerr << __FUNCTION__ << ": Error, attempted to lock an already locked texture. This is not supported!" << std::endl;
			return ScopedTextureLock();
		}
		else
		{
			ScopedTextureLock lock = LockImplementation ( level, lockOptions );

			if ( lock )
			{
				m_isLocked = true;
				m_lockOptions = lockOptions;
			}

			return lock;
		}
	}	
	//End Texture::Lock


    //=========================================================================
    //! @function    Texture::Unlock
    //! @brief       Unlock the texture
    //!              
    //=========================================================================
	void Texture::Unlock ()
	{
		UnlockImplementation();
		m_isLocked = false;
	}
	//End Texture::Unlock


};
//end namespace Renderer


#endif
//#ifndef RENDERER_TEXTURE_H
