//======================================================================================
//! @file         RendererBuffer.h
//! @brief        Abstract base template class for a renderer buffer, such as a vertex or index buffer
//!               
//!               
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

#ifndef RENDERER_RENDERERBUFFER_H
#define RENDERER_RENDERERBUFFER_H



#include "Renderer/ScopedBufferLock.h"



//namespace Renderer
namespace Renderer
{

	
    //=========================================================================
    // Related types
    //=========================================================================
	
	//! Flags that determine how a buffer is to be used
	enum EUsage
	{  
		//! For buffers that won't be modified on a regular basis,
		//! locking this buffer will encounter a performance penalty.
		//! Static buffers are usually placed in video memory
		USAGE_STATIC = 1,

		//! For buffers that will be modified on a regular basis
		//! Dynamic buffers are usually kept in AGP memory
		//! LOCK_DISCARD and LOCK_NOOVERWRITE can only be used with dynamic buffers
		USAGE_DYNAMIC = 2, 
		
		//! Indicates that the application will only write to the buffer. 
		//! This allows the driver to put the buffer in the most optimal location
		//! for writing memory
		USAGE_WRITEONLY = 4, 
		
		//! Indicates that the application will be generating the contents of the
		//! buffer from scratch on a regular basis, and therefore does not mind
		//! if the contents of the buffer are lost, and have to be recreated
		//! Only valid on buffers created with USAGE_DYNAMIC
		USAGE_DISCARDABLE = 8, 
		
		//! Combination of static and write only
		USAGE_STATICWRITEONLY = 5, 
		
		//! Combination of dynamic and write only
		USAGE_DYNAMICWRITEONLY = 6,
		
		//! Combination of dynamic, write only, and discardable
		USAGE_DYNAMICWRITEONLYDISCARDABLE = 14
	};

	//! Flags that indicate how a buffer is to be locked
	enum ELock		
	{ 
		//! Lock operation that allows reading, and writing
		//! and the contents are not overwritten
		LOCK_NORMAL,

		//! Just like LOCK_NORMAL, but the application promises not to overwrite the contents that
		//! were written to the buffer this frame. If this is not specified, then
		//! rendering from the buffer will have to complete before the lock can complete.
		//! Only valid on buffers created with USAGE_DYNAMIC
		LOCK_NOOVERWRITE,

		//! Indicates that all locations in the buffer are to be overwritten
		//! with a write-only operation. Only allowed on buffers created with USAGE_DYNAMIC.
		LOCK_DISCARD,

		//! Lock the buffer for reading. Not allowed on buffers created with the
		//! USAGE_WRITEONLY flag
		LOCK_READONLY 
	};

	//!@class	RendererBuffer
	//!@brief	Abstract base template class for a renderer buffer, such as a vertex or index buffer
	template <class BufferType>
	class RendererBuffer
	{

		public:

			//Friends
			friend class ScopedBufferLock;

			//Public methods
			inline RendererBuffer ( EUsage usage );
			virtual ~RendererBuffer() {	 }

			inline ScopedBufferLock<BufferType> Lock( size_t lockBegin, size_t lockSize, ELock lockOptions ) throw();

			//Non virtual methods
			inline bool   IsLocked() const throw();
			inline EUsage Usage() const throw();
			inline size_t LockStart() const throw();
			inline size_t LockSize() const throw();
			inline ELock  LockOptions() const throw();

		protected:

			//Protected methods
			void Unlock();

			//Implementation of lock and unlock
			virtual void UnlockImplementation() = 0;
			virtual ScopedBufferLock<BufferType> LockImplementation( size_t lockBegin, size_t lockSize, ELock lockOptions ) throw() = 0;

		private:

			//Private methods
			inline void SetLockPointer( ScopedBufferLock<BufferType>* lock );
		
			//Private data
			EUsage	m_usage;
			size_t	m_lockStart;
			size_t	m_lockSize;
			ELock	m_lockOptions;
			ScopedBufferLock<BufferType>* m_lock;

	};
	//End class RendererBuffer



	//=========================================================================
	//! @function    RendererBuffer::RendererBuffer
	//! @brief       Constructs a renderer buffer object
	//!              
	//! @param		 usage [in] Usage settings for the buffer             
	//=========================================================================
	template <class BufferType>
	RendererBuffer<BufferType>::RendererBuffer ( EUsage usage )
		: m_usage(usage), m_lockStart(0), m_lockSize(0), m_lock(0)
	{
	}
	//End RendererBuffer::RendererBuffer



	//=========================================================================
	//! @function    RendererBuffer::IsLocked
	//! @brief       Returns true if the buffer is locked, false otherwise
	//!              
	//! @return      true if the buffer is locked, false otherwise
	//=========================================================================
	template <class BufferType>
		bool RendererBuffer<BufferType>::IsLocked() const
	{
		if ( m_lock != 0 )
		{
			return true;
		}
		else
		{
			return false;	
		}
	}
	//End RendererBuffer::IsLocked


	
	//=========================================================================
	//! @function    RendererBuffer::Usage
	//! @brief       Returns the usage settings the buffer was created with
	//!              
	//! @return      The usage settings the buffer was created with
	//=========================================================================
	template <class BufferType>
		EUsage RendererBuffer<BufferType>::Usage() const
	{
		return m_usage;
	}
	//End RendererBuffer::UsageFlags



	//=========================================================================
	//! @function    RendererBuffer::LockStart
	//! @brief       Returns the offset from the beginning of the buffer
	//!				 to the beginning of the lock
	//!
	//!				 Returns zero if the buffer is not locked
	//!              
	//! @return      The offset from the beginning of the buffer
	//!				 to the beginning of the lock. Or zero for an unlocked buffer
	//=========================================================================
	template <class BufferType>
		size_t RendererBuffer<BufferType>::LockStart() const
	{
		if ( IsLocked() )
		{
			return m_lockStart;
		}
		else
		{
			return static_cast<size_t>(0);
		}
	}
	//End RendererBuffer::LockStart



	//=========================================================================
	//! @function    RendererBuffer::LockSize
	//! @brief       Returns the offset from the beginning of the lock
	//!				 to the end of the lock
	//!
	//!				 Returns zero if the buffer is not locked
	//!              
	//! @return      The offset from the beginning of the lock
	//!				 to the end of the lock. Or zero for an unlocked buffer
	//=========================================================================
	template <class BufferType>
		size_t RendererBuffer<BufferType>::LockSize() const
	{
		if ( IsLocked() )
		{
			return m_lockSize;
		}
		else
		{
			return static_cast<size_t>(0);
		}
	}
	//End RendererBuffer::LockSize



	//=========================================================================
	//! @function    RendererBuffer::LockOptions
	//! @brief       Returns the options used to lock the buffer
	//!
	//!				 If the buffer is not locked, then the return value is undefined
	//!              
	//! @return      The flags used to lock the buffer
	//=========================================================================
	template <class BufferType>
		ELock RendererBuffer<BufferType>::LockOptions() const
	{
		return m_lockFlags;
	}
	//End RendererBuffer::LockFlags


	
	//=========================================================================
	//! @function    RendererBuffer::SetLockPointer
	//! @brief       Sets the lock pointer of the object
	//!
	//!				 When the renderer buffer is locked, it stores an internal pointer
	//!				 to the lock object. This allows the lock to be released
	//!				 if the buffer object is destroyed before the lock 
	//! 
	//=========================================================================
	template <class BufferType>
		void RendererBuffer<BufferType>::SetLockPointer( ScopedBufferLock<BufferType>* lock )
	{
		m_lock = lock;
	}
	//End RendererBuffer::SetLockPointer



	//=========================================================================
	//! @function    RendererBuffer::Lock
	//! @brief       Lock a portion of the buffer
	//!
	//! @param		 lockBegin [in]	Offset from the beginning of the buffer to the
	//!								beginning of the lock
	//! @param		 lockSize  [in] Offset from the beginning of the lock to the
	//!								end of the lock
	//! @param		 options	   [in] Options used to lock the buffer
	//!
	//=========================================================================
	template <class BufferType>
		ScopedBufferLock<BufferType> RendererBuffer<BufferType>::Lock( UInt lockBegin, UInt lockSize, ELock lockOptions )
	{
		return LockImplementation ( lockBegin, lockSize, lockOptions );
	}
	//End RendererBuffer::Lock



	//=========================================================================
	//! @function    RendererBuffer::Unlock
	//! @brief       Unlock the buffer
	//!
	//=========================================================================
	template <class BufferType>
		void RendererBuffer<BufferType>::Unlock()
	{
		m_lock = 0;
		UnlockImplementation();
	}
	//End RendererBuffer::Unlock



};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERERBUFFER_H
