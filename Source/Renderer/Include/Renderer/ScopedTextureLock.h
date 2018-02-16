//======================================================================================
//! @file         ScopedTextureLock.h
//! @brief        ScopedTextureLock class. Class that provides safe access to
//!               a locked texture, unlocking the texture when the texture lock object goes out of scope
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 20 June 2005
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


#ifndef RENDERER_SCOPEDTEXTURELOCK_H
#define RENDERER_SCOPEDTEXTURELOCK_H



//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declaration
    //=========================================================================
	class Texture;


	//!@class	ScopedTextureLock
	//!@brief	Class that provides safe access to a locked texture
	//!			unlocking the texture when the texture lock object goes out of scope
	class ScopedTextureLock
	{
		public:

			inline ScopedTextureLock () throw();
			ScopedTextureLock ( Texture& texture, Byte* lockPointer, UInt level, Int pitch ) throw();
			ScopedTextureLock ( ScopedTextureLock& lock ) throw();
			inline ~ScopedTextureLock() throw();
			
			//Get a pointer to the locked data
			inline Byte* GetLockPointer() throw();

			//Get the pitch
			inline Int Pitch() const throw();

			//Get the level
			inline UInt Level() const throw();

			//operator = overload
			ScopedTextureLock& operator = ( ScopedTextureLock& lock ) throw();

			//operator bool overload
			inline operator bool () const throw();

			//Release the lock
			void Release() throw();

			//Return the lock flags
			UInt LockOptions() const throw();

		private:

			Texture*	m_texture;
			Byte* 		m_lockPointer;
			Int			m_pitch;
			UInt		m_level;

	};
	//End class ScopedTextureLock



	
    //=========================================================================
    //! @function    ScopedTextureLock::ScopedTextureLock
    //! @brief       Construct a null lock
    //=========================================================================
	ScopedTextureLock::ScopedTextureLock()
		: m_texture(0), m_lockPointer(0), m_pitch(0)
	{
	}
	//End ScopedTextureLock::ScopedTextureLock


	//=========================================================================
    //! @function    ScopedTextureLock::~ScopedTextureLock
    //! @brief       Destroy a ScopedTextureLock. Releases the lock if the 
	//!				 lock is valid
    //!              
    //=========================================================================	
	ScopedTextureLock::~ScopedTextureLock()
	{
		if ( m_texture )
		{
			Release();
		}
	}
	//End ScopedTextureLock::~ScopedTextureLock



    //=========================================================================
    //! @function    ScopedTextureLock::GetLockPointer
    //! @brief       Returns a pointer to the locked memory of the buffer
    //!              
    //! @return      A pointer to the locked memory of the buffer
    //=========================================================================
	Byte* ScopedTextureLock::GetLockPointer()
	{
		return m_lockPointer;
	}
	//End ScopedTextureLock::GetLockPointer



    //=========================================================================
    //! @function    ScopedTextureLock::Pitch
    //! @brief       Returns the pitch of the locked texture
    //!              
    //! @return      The pitch of the locked texture
    //=========================================================================
	Int ScopedTextureLock::Pitch() const
	{
		return m_pitch;
	}
	//End ScopedTextureLock::Pitch



    //=========================================================================
    //! @function    ScopedTextureLock::Level
    //! @brief       Returns the level that has been locked
	//!
    //! @return		 The level that has been locked
    //=========================================================================
	UInt ScopedTextureLock::Level() const
	{
		return m_level;
	}
	//End ScopedTextureLock::Level


    //=========================================================================
    //! @function    ScopedTextureLock::operator bool
    //! @brief       Conversion to bool
    //!              
	//!				 Returns true if this lock is valid
	//!				 Returns false if this is a null lock
    //!              
    //! @return      true if this lock is valid
    //!		         false if this is a null lock
    //=========================================================================
	ScopedTextureLock::operator bool () const
	{
		if ( m_texture && m_lockPointer )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//End ScopedTextureLock::operator bool



};
//end namespace Renderer



#endif
//#ifndef RENDERER_SCOPEDTEXTURELOCK_H