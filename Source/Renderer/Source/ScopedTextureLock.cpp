//======================================================================================
//! @file         ScopedTextureLock.cpp
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

#include "Core/Core.h"
#include "Renderer/Texture.h"
#include "Renderer/ScopedTextureLock.h"


using namespace Renderer;




//=========================================================================
//! @function    ScopedTextureLock::ScopedTextureLock
//! @brief       Construct a lock that refers to a locked texture
//!              
//! @param       texture	 [in] Reference to the locked buffer
//! @param       lockPointer [in] Pointer to the locked data
//! @param		 level		 [in] Level that has been locked
//! @param		 pitch		 [in] Pitch of the texture
//!
//=========================================================================
ScopedTextureLock::ScopedTextureLock( Texture& texture, Byte* lockPointer, UInt level, Int pitch )
	: m_texture(&texture), m_lockPointer(lockPointer), m_level(level), m_pitch(pitch)
{
	debug_assert( m_texture != 0, "Tried to initialise a TextureLock with a null pointer" );
	debug_assert( m_lockPointer != 0, "Tried to initialise a TextureLock with a null lock pointer" );

	m_texture->SetLockPointer(this);
}
//End ScopedTextureLock::ScopedTextureLock


//=========================================================================
//! @function    ScopedTextureLock::ScopedTextureLock
//! @brief       Copy constructor
//!
//!				 Copies the value of lock, and sets lock to zero
//!				 This lock takes ownership of the lock, and the lock being
//!				 copied becomes a null lock
//!              
//! @param       lock [in] Lock to copy
//!              
//! @return      Return  *this
//=========================================================================
ScopedTextureLock::ScopedTextureLock ( ScopedTextureLock& lock ) throw()
{
	//Set *this to the old value of lock
	m_texture = lock.m_texture;
	m_lockPointer = lock.m_lockPointer;
	m_pitch = lock.m_pitch;
	m_level = lock.m_level;

	m_texture->SetLockPointer(this);
	
	//Set lock to a null lock
	lock.m_texture = 0;
	lock.m_lockPointer = 0;
	lock.m_pitch = 0;
	lock.m_level = 0;
}
//End ScopedTextureLock::ScopedTextureLock



//=========================================================================
//! @function    ScopedTextureLock::operator =
//! @brief       Sets a scoped buffer lock to the contents of another lock
//!
//!				 After this call completes, the parameter "lock" will be equal to a null lock
//!				 and *this will refer to the lock that "lock" previously referred to
//!              
//! @param       lock [in]	Reference to a lock object
//!              
//! @return      A reference to *this
//=========================================================================
ScopedTextureLock& ScopedTextureLock::operator = ( ScopedTextureLock& lock )
{
	//Set *this to the old value of lock
	m_texture = lock.m_texture;
	m_lockPointer = lock.m_lockPointer;
	m_pitch = lock.m_pitch;
	m_level = lock.m_level;

	m_texture->SetLockPointer(this);
	
	//Set lock to a null lock
	lock.m_texture = 0;
	lock.m_lockPointer = 0;
	lock.m_pitch = 0;
	lock.m_level = 0;

	return *this;
}
//End ScopedTextureLock::operator =



//=========================================================================
//! @function    ScopedTextureLock::Release
//! @brief       Release a scoped buffer lock
//!              
//!				 After this call completes, this lock will be a null lock
//!				 If this lock is already a null lock, then this method is a no-op	
//!
//=========================================================================
void ScopedTextureLock::Release()
{
	if ( m_texture )
	{
		m_texture->Unlock();
		m_texture->SetLockPointer(0);

		m_texture = 0;
		m_lockPointer = 0;
		m_pitch = 0;
		m_level = 0;
	}
}
//End ScopedTextureLock::Release


//=========================================================================
//! @function    ScopedTextureLock::LockFlags
//! @brief       Returns the flags the lock was created with
//!				 or zero if this is a null lock              
//!
//!
//! @return      Returns the flags the lock was created with,
//!				 or zero, if this is a null lock
//=========================================================================
UInt ScopedTextureLock::LockOptions() const throw()
{
	if ( m_texture )
	{
		return m_texture->LockOptions();
	}
	else
	{
		return 0;
	}
}
//End ScopedTextureLock::LockFlags
