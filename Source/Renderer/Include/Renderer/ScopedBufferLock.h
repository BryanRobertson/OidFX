//======================================================================================
//! @file         ScopedBufferLock.h
//! @brief        Template class for a scoped buffer lock
//!               
//!               A scoped buffer lock, provides safe access to the data of a lockable object,
//!				  unlocking the buffer object when the lock object goes out of scope
//!
//! @author       Bryan Robertson
//! @date         Sunday, 05 June 2005
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


#ifndef RENDERER_SCOPEDBUFFERLOCK_H
#define RENDERER_SCOPEDBUFFERLOCK_H


//namespace Renderer
namespace Renderer
{

	//!@class	ScopedBufferLock
	//!@brief	A scoped buffer lock, provides safe access to the data of a lockable object,
	//!			 unlocking the buffer object when the lock object goes out of scope
	//!
	//!			The template parameter is merely for type safety, so a lock between
	//!			two different buffer types is not interchangable
	//!
	//!			Care should be taken, that the lifetime of the lock does not exceed the
	//!			lifetime of the buffer, to which the lock refers. The ScopedBufferLock
	//!			class does not 
	template <class BufferType>
	class ScopedBufferLock
	{
		public:

			inline ScopedBufferLock () throw();
			inline ScopedBufferLock ( BufferType& buffer, void* lockPointer ) throw();
			inline ScopedBufferLock ( ScopedBufferLock& lock ) throw();
			inline ~ScopedBufferLock() throw();
			
			//Get a pointer to the locked data
			inline void* GetLockPointer();

			//operator = overload
			inline ScopedBufferLock& operator = ( ScopedBufferLock& lock ) throw();

			//operator bool overload
			inline operator bool () const throw();

			//Release the lock
			inline void Release() throw();

			//Accessors for lock information
			inline size_t LockStart() const throw();
			inline size_t LockSize() const throw();
			inline UInt LockFlags() const throw();

		private:

			//Disallow copy construction
			//inline ScopedBufferLock ( const ScopedBufferLock& lock ) throw() {		}

			//Private data
			BufferType* m_buffer;
			void* 		m_lockPointer;
	};
	//End class ScopedBufferLock



    //=========================================================================
    //! @function    ScopedBufferLock<BufferType>::ScopedBufferLock
    //! @brief       Construct a null lock
    //=========================================================================
	template <class BufferType>
		ScopedBufferLock<BufferType>::ScopedBufferLock()
		: m_buffer(0), m_lockPointer(0)
	{
	}
	//End ScopedBufferLock<BufferType>::ScopedBufferLock



    //=========================================================================
    //! @function    ScopedBufferLock<BufferType>::ScopedBufferLock
    //! @brief       Construct a lock that refers to a locked buffer
    //!              
    //! @param       buffer		 [in] Reference to the locked buffer
    //! @param       lockPointer [in] Pointer to the locked data
    //=========================================================================
	template <class BufferType>
		ScopedBufferLock<BufferType>::ScopedBufferLock( BufferType& buffer, void* lockPointer )
		: m_buffer(&buffer), m_lockPointer(lockPointer)
	{
		debug_assert( m_buffer != 0, "Tried to initialise a ScopedBufferLock with a null pointer" );
		debug_assert( m_lockPointer != 0, "Tried to initialise a ScopedBufferLock with a null lock pointer" );

		m_buffer->SetLockPointer(this);
	}
	//End ScopedBufferLock<BufferType>::ScopedBufferLock


    //=========================================================================
    //! @function    ScopedBufferLock<BufferType>::ScopedBufferLock
    //! @brief       Copy constructor
	//!
	//!				 Copies the value of lock, and sets lock to zero
    //!              
    //! @param       lock [in] Lock to copy
    //!              
    //! @return      Return  *this
    //=========================================================================
	template <class BufferType>
		ScopedBufferLock<BufferType>::ScopedBufferLock ( ScopedBufferLock<BufferType>& lock ) throw()
	{
		//Set *this to the old value of lock
		m_buffer = lock.m_buffer;
		m_lockPointer = lock.m_lockPointer;

		m_buffer->SetLockPointer(this);
		
		//Set lock to a null lock
		lock.m_buffer = 0;
		lock.m_lockPointer = 0;
	}
	//End ScopedBufferLock<BufferType>::ScopedBufferLock


	//=========================================================================
    //! @function    ScopedBufferLock<BufferType>::~ScopedBufferLock
    //! @brief       Destroy a ScopedBufferLock. Releases the lock if the 
	//!				 lock is valid
    //!              
    //=========================================================================
	template <class BufferType>
		ScopedBufferLock<BufferType>::~ScopedBufferLock()
	{
		if ( m_buffer )
		{
			Release();
		}
	}
	//End ScopedBufferLock<BufferType>::~ScopedBufferLock



    //=========================================================================
    //! @function    ScopedBufferLock<BufferType>::GetLockPointer
    //! @brief       Returns a pointer to the locked memory of the buffer
    //!              
    //! @return      A pointer to the locked memory of the buffer
    //=========================================================================
	template <class BufferType>
		void* ScopedBufferLock<BufferType>::GetLockPointer()
	{
		return m_lockPointer;
	}
	//End ScopedBufferLock<BufferType>::GetLockPointer



    //=========================================================================
    //! @function    ScopedBufferLock<BufferType>::operator =
    //! @brief       Sets a scoped buffer lock to the contents of another lock
	//!
	//!				 After this call completes, the parameter "lock" will be equal to a null lock
	//!				 and *this will refer to the lock that "lock" previously referred to
    //!              
    //! @param       lock [in]	Reference to a lock object
    //!              
    //! @return      A reference to *this
    //=========================================================================
    template <class BufferType>
		ScopedBufferLock<BufferType>& ScopedBufferLock<BufferType>::operator = ( ScopedBufferLock<BufferType>& lock )
	{
		//Set *this to the old value of lock
		m_buffer = lock.m_buffer;
		m_lockPointer = lock.m_lockPointer;

		m_buffer->SetLockPointer(this);
		
		//Set lock to a null lock
		lock.m_buffer = 0;
		lock.m_lockPointer = 0;

		return *this;
	}
	//End ScopedBufferLock<BufferType>::operator =



    //=========================================================================
    //! @function    ScopedBufferLock<BufferType>::operator bool
    //! @brief       Conversion to bool
    //!              
	//!				 Returns true if this lock is valid
	//!				 Returns false if this is a null lock
    //!              
    //! @return      true if this lock is valid
    //!		         false if this is a null lock
    //=========================================================================
	template <class BufferType>
		ScopedBufferLock<BufferType>::operator bool () const
	{
		if ( m_buffer && m_lockPointer )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//End ScopedBufferLock<BufferType>::operator bool



	//=========================================================================
	//! @function    ScopedBufferLock<BufferType>::Release
	//! @brief       Release a scoped buffer lock
	//!              
	//!				 After this call completes, this lock will be a null lock
	//!				 If this lock is already a null lock, then this method is a no-op	
	//!
	//=========================================================================
	template <class BufferType>
		void ScopedBufferLock<BufferType>::Release()
	{
		if ( m_buffer )
		{
			m_buffer->Unlock();
			m_buffer->SetLockPointer(0);

			m_buffer = 0;
			m_lockPointer = 0;	
		}
	}
	//End ScopedBufferLock<BufferType>::Release



	//=========================================================================
	//! @function    ScopedBufferLock<BufferType>::LockStart
	//! @brief       Returns the offset of the start of the lock, from the
	//!              beginning of the buffer
	//!
	//!				 Returns 0 if this is a null lock
	//!              
	//! @return      The offset of the start of the lock, from the beginning of the buffer
	//!				 Or zero, if this is a null lock
	//=========================================================================
	template <class BufferType>
		size_t ScopedBufferLock<BufferType>::LockStart() const throw()
	{
		if ( m_buffer )
		{
			return m_buffer->LockStart();
		}
		else
		{
			return 0;
		}
	}
	//End ScopedBufferLock<BufferType>::LockStart()



	//=========================================================================
	//! @function    ScopedBufferLock<BufferType>::LockSize
	//! @brief       Returns the offset of the end of the lock, from the beginning
	//!				 of the lock
	//!              
	//!              Returns zero if this is a null lock
	//!
	//! @return      The offset of the end of the lock, from the beginning
	//!				 of the lock. Or zero, if this is a null lock
	//=========================================================================
	template <class BufferType>
		size_t ScopedBufferLock<BufferType>::LockSize() const throw()
	{
		if ( m_buffer )
		{
			return m_buffer->LockSize();
		}
		else
		{
			return 0;
		}
	}
	//End ScopedBufferLock<BufferType>::LockSize



	//=========================================================================
	//! @function    ScopedBufferLock<BufferType>::LockFlags
	//! @brief       Returns the flags the lock was created with
	//!				 or zero if this is a null lock              
	//!
	//!
	//! @return      Returns the flags the lock was created with,
	//!				 or zero, if this is a null lock
	//=========================================================================
	template <class BufferType>
		UInt ScopedBufferLock<BufferType>::LockFlags() const throw()
	{
		if ( m_buffer )
		{
			return m_buffer->LockFlags();
		}
		else
		{
			return 0;
		}
	}
	//End ScopedBufferLock<BufferType>::LockFlags



};
//end namespace Renderer


#endif
//#ifndef RENDERER_SCOPEDBUFFERLOCK_H
