//======================================================================================
//! @file         Handle.h
//! @brief        Template for a Handle to a resource. Allows a resource manager class
//!				  to give out handles to a resource, rather than a pointer. This way
//!				  
//!               
//!                
//! @author       Bryan Robertson
//! @date         Saturday, 15 January 2005
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

#ifndef CORE_HANDLE_H
#define CORE_HANDLE_H



//namespace Core
namespace Core
{

	//Forward declarations
	template <class T>
		class HandleManager;

	template <class T>
		class ResourceManager;

	//Exception classes
	class NullHandleDereference : public RuntimeError
	{
		public:
			NullHandleDereference	( const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
										const Char* function = "Unknown", const UInt line = 0 )
										: RuntimeError ( what, errorCode, file, function, line )
			{
			}
	};

	class BadHandle : public InvalidArgument
	{
		public:
			BadHandle	(	const Char* what, UInt errorCode = 0, const Char* file = "Unknown",
							const Char* function = "Unknown", const UInt line = 0 )
								: InvalidArgument ( what, errorCode, file, function, line )
			{
			}	
	};


	//! @class	NullHandle
	//! @brief	When assigned to a handle, sets it to zero
	class NullHandle
	{
	};
	//end class NullHandle


	//! @class	Handle
	//! @brief	Template for a Handle to a resource
	template <class T>
	class Handle
	{
		public:
	
			//Constructor/Destructor
			inline Handle ( ) throw();
			inline Handle ( const NullHandle& null ) throw();
			inline Handle ( const Handle& handle );
			inline ~Handle ( );

			//Friends
			friend class HandleManager;

			//Accessors
			UInt Index ( ) const throw()		{ return m_index;		}
			UInt MagicNumber ( ) const throw()	{ return m_magicNumber; }
			UInt Value ( ) const throw()		{ return m_value;		}

			//! Check if handle is null
			inline bool IsNull ( ) const throw();

			//Safe dereferencing.
			inline T*			SafeDereference();
			inline const T*		SafeDereference() const;

			//Operator overloads
			inline operator UInt ( ) const throw();
			inline Handle& operator = ( const NullHandle& null ) throw();
			inline Handle& operator = ( const Handle& handle ) throw();
			inline bool operator == ( const NullHandle& null ) const throw();
			inline bool operator != ( const NullHandle& null ) const throw();
			inline T* operator-> ( );
			inline const T* operator-> ( ) const;
			inline T* operator* ( );

			//Public constants
			enum 
			{
				MaxMagicNumber = (1 << sizeof(UShort)) -1,
				MaxIndex	   = (1 << sizeof(UShort)) -1
			};

		private:

			//Private constructors
			//private so that a non-null handle can only be instantiated
			//from the HandleManager friend class
			inline Handle ( UInt index, UInt magic );

			//
			inline T* Dereference();
			inline const T* Dereference() const;


			//Private data
			union
			{
				struct
				{
					UShort m_magicNumber;	//!< Magic number used to validate the handle
					UShort m_index;			//!< Index into the resource managers storage, used for quick lookup of resource.
											//!< although obviously this is dependent on the implementation of the resource manager
											//!< the resource manager class might not actually implement it that way
				};

				UInt m_value;
			};
			
	};
	//end class Handle



	//=========================================================================
	//! @function    Resource::Handle<T>::Handle
	//! @brief       Default constructor. Creates a null handle
	//!                           
	//=========================================================================
	template <class T>
		Handle<T>::Handle ( )
		: m_value(0)
	{
	}
	//end Resource::Handle<T>::Handle



	//=========================================================================
	//! @function    Resources::Handle<T>::Handle (NullHandle)
	//! @brief       Construct a null handle
	//!
	//! @param       null 
	//=========================================================================
	template <class T>
		Handle<T>::Handle ( const NullHandle& null )
		: m_value (0)
	{

	}
	//end Handle::Handle(NullHandle)



	//=========================================================================
	//! @function    Resource::Handle<T>::Handle
	//! @brief       Private constructor. Initializes a non-null handle object/
	//!				 Can only be called from the HandleManager class
	//=========================================================================
	template <class T>
		Handle<T>::Handle  ( UInt index, UInt magic )
		: m_index(index), m_magicNumber(magic)
	{
		debug_assert ( ResourceManager<T>::GetManager() != 0 , "Error, Attempted to construct a non-null Handle object when no manager exists!" );
	}
	//end Resource::Handle<T>::Handle ( index )



	//=========================================================================
	//! @function    Resource::Handle<T>::Handle
	//! @brief       Copy constructor
	//!                           
	//=========================================================================
	template <class T>
		Handle<T>::Handle ( const Handle<T>& handle )
		: m_value(handle.m_value)
	{
		//Increment reference count of object this handle refers to
		if ( m_value != 0 )
		{
			ResourceManager<T>::GetManager()->IncrementReferenceCount ( *this );
		}
	}
	//end Resource::Handle<T,Manager>::CopyConstructor



	//=========================================================================
	//! @function    Resource::Handle<T>::Destructor
	//! @brief       Calls ms_manager->ReleaseResource, to decrement the reference count
	//!				 of the resource this handle refers to. (or does nothing if the handle is null)
	//!                           
	//=========================================================================
	template <class T>
		Handle<T>::~Handle()
	{
		if ( m_value == 0 )
			return;
     
		ResourceManager<T>::GetManager()->ReleaseResource ( *this );
	}
	//end Resource::Handle<T>::Destructor



	//=========================================================================
	//! @function    Resources::Handle<T>::IsNull
	//! @brief       Returns true if the handle is a null handle
	//!              
	//! @return      true if the handle is null, false otherwise
	//=========================================================================
	template <class T>
		bool Handle<T>::IsNull () const
	{
		return (m_value == 0);
	}
	//end Resources::Handle<T>::IsNull
	


	//=========================================================================
	//! @function    Resources::Handle<T>::operator UInt
	//! @brief       Returns m_value
	//! @return      value
	//=========================================================================
	template <class T>
		Handle<T>::operator UInt ( ) const
	{
		return m_value;
	}
	//end Resources::Handle<T>::operator UInt

	

	//=========================================================================
	//! @function    Resources::Handle<T>::operator =
	//! @brief       Set the handle to null
	//!				 The NullHandle parameter is to 
	//!				 readability, since we only want clients to be able to set a
	//!				 handle to null, this makes more sense than operator = (UInt)
	//!
	//!				 myHandle = NullHandle; makes it much easier to see what is going on
	//!				 than myHandle = 0; because it makes it clearer that myHandle = 10 isn't allowed
	//!
	//! @param		 null - Instance of NullHandle class. 
	//!              
	//! @return      Contents of now null handle
	//=========================================================================
	template <class T>
		Handle<T>& Handle<T>::operator = ( const NullHandle& null )
	{
		m_value = 0;

		return *this;
	}
	//end Resources::Handle<T>::operator =



	//=========================================================================
	//! @function    Resources::Handle<T>::operator == (NullHandle)
	//! @brief       Returns whether or not the handle is equal to zero
	//! @return      IsNull()
	//=========================================================================
	template <class T>
		bool Handle<T>::operator== ( const NullHandle& null ) const
	{
		return IsNull();
	}
	//end Resources::Handle<T>::operator ==



	//=========================================================================
	//! @function    Resources::Handle<T>::operator != (NullHandle)
	//! @brief       Returns whether the handle is not equal to zero
	//! @return      !IsNull()
	//=========================================================================
	template <class T>
		bool Handle<T>::operator!= ( const NullHandle& null ) const
	{
		return !IsNull();
	}
	//end Resources::Handle<T>::operator !=



	//=========================================================================
	//! @function    Resources::Handle<T>::operator =
	//! @brief       Set the handle to the value of another handle
	//!				 Incrementing the reference count of the handle
	//!              
	//! @param       handle 
	//!              
	//! @return      *this
	//=========================================================================
	template <class T>
		Handle<T>& Handle<T>::operator = ( const Handle<T>& handle )
	{
		m_value = handle.m_value;

		//Increment reference count of object this handle refers to
		if ( m_value != 0 )
		{
			ResourceManager<T>::GetManager()->IncrementReferenceCount ( *this );
		}

		return *this;
	}



	//=========================================================================
	//! @function   Resource::Handle<T>::operator ->
	//! @brief		Call a method of the resource referred to by this handle
	//!
	//!				Uses SafeDereference in debug builds, so errors can be caught more easily
	//!				
	//! @throw		NullHandleDereference if the handle is null (debug builds only)
	//! @throw		BadHandle if the handle does not refer to a valid resource (debug builds only)
	//=========================================================================
	template <class T>
		T* Handle<T>::operator -> ( )
	{ 
		#ifndef RELEASE_BUILD
			return SafeDereference();
		#else
			return Dereference();
		#endif
	}
	//end  Resource::Handle<T>::operator ->



	//=========================================================================
	//! @function   Resource::Handle<T>::operator -> const
	//! @brief		Call a method of the resource referred to by this handle
	//!  
	//!				Uses SafeDereference in debug builds, so errors can be caught more easily
	//!
	//! @throw		NullHandleDereference if the handle is null (debug builds only)
	//! @throw		BadHandle if the handle does not refer to a valid resource (debug builds only)
	//=========================================================================
	template <class T>
		const T* Handle<T>::operator -> ( ) const
	{ 
		#ifndef RELEASE_BUILD
			return SafeDereference();
		#else
			return Dereference();
		#endif
	}
	//end  Resource::Handle<T>::operator -> const



    //=========================================================================
    //! @function    Handle<T>::Dereference
    //! @brief       Unsafe dereferencing of a handle
    //!              
    //!              Called by operator -> and operator * in release builds
	//!				 so that they can avoid the overhead of checking the handle for validity
	//!				 every time it is dereferenced
	//!
    //! @return      A pointer to the resource
    //! @throw       
    //=========================================================================
	template <class T>
		T* Handle<T>::Dereference()
	{
		#ifdef DEBUG_BUILD
		std::cerr << __FUNCTION__ ": Warning! Unsafe dereference used in a debug build! This is not recommended!" << std::endl;
		#endif
		
		return ResourceManager<T>::GetManager()->GetResourcePointer( *this );
	}
	//End Handle<T>::Dereference



    //=========================================================================
    //! @function    Handle<T>::Dereference const
    //! @brief       Unsafe dereferencing of a handle ( const version )
    //!              
    //!              Called by operator -> and operator * in release builds
	//!				 so that they can avoid the overhead of checking the handle for validity
    //!				 every time it is dereferences              
	//!
    //! @return      
    //! @throw       
    //=========================================================================
	template <class T>
		const T* Handle<T>::Dereference() const
	{
		#ifdef DEBUG_BUILD
		std::cerr << __FUNCTION__ ": Warning! Unsafe dereference used in a debug build! This is not recommended!" << std::endl;
		#endif
		
		return ResourceManager<T>::GetManager()->GetResourcePointer( *this );
	}
	//End Handle<T>::Dereference const



    //=========================================================================
    //! @function    Handle<T>::SafeDereference
    //! @brief       Safe dereferencing of a handle
	//!
	//!				 Checks the handle is valid before dereferencing it
	//!				 This is used internally by operator -> and operator * in debug builds.
	//!				 If a dereference method is to be exposed to a scripting language,
	//!				 then it is recommended that this method be the one exposed, to avoid
	//!				 crashes caused by the dereferencing of invalid handles
	//!
	//!				 If the handle is null then a NullHandleDereference will be thrown
	//!				 If there is no such resource with that handle, then a BadHandle exception will be thrown
	//!				 this could happen, if the resource was deleted prematurely (which shouldn't happen)
	//!  
    //! @return		 A pointer to the dereferenced object      
    //! @throw       NullHandleDereference if the handle is null
	//!				 BadHandle if the handle does not point to a valid resource
    //=========================================================================
	template <class T>
		T* Handle<T>::SafeDereference()
	{
		if ( IsNull() )
		{
			throw NullHandleDereference ( "Tried to dereference a null handle!", 0, __FILE__, __FUNCTION__, __LINE__ );
		}

		T* resourcePointer = ResourceManager<T>::GetManager()->GetResourcePointer( *this );

		if ( resourcePointer == 0 )
		{
			throw BadHandle ( "Handle is not valid!", 0, __FILE__, __FUNCTION__, __LINE__ );
		}

		return resourcePointer;
	}
	//End Handle<T>::SafeDereference



    //=========================================================================
    //! @function    Handle<T>::SafeDereference const
    //! @brief		 Const version of SafeDereference
	//!
	//!				 Checks the handle is valid before dereferencing it
	//!				 This is used internally by operator -> and operator * in debug builds.
	//!				 If a dereference method is to be exposed to a scripting language,
	//!				 then it is recommended that this method be the one exposed, to avoid
	//!				 crashes caused by the dereferencing of invalid handles
	//!
	//!				 If the handle is null then a NullHandleDereference will be thrown
	//!				 If there is no such resource with that handle, then a BadHandle exception will be thrown
	//!				 this could happen if the resource was deleted ( which shouldn't happen )
	//!  
    //! @return		 A const pointer to the dereferenced object      
    //! @throw       NullHandleDereference if the handle is null
	//!				 BadHandle if the handle does not point to a valid resource
    //=========================================================================
	template <class T>
		const T* Handle<T>::SafeDereference() const
	{
		if ( IsNull() )
		{
			throw NullHandleDereference ( "Tried to dereference a null handle!", 0, __FILE__, __FUNCTION__, __LINE__ );
		}

		T* resourcePointer = ResourceManager<T>::GetManager()->GetResourcePointer( *this );

		if ( resourcePointer == 0 )
		{
			throw BadHandle ( "Handle is not valid!", 0, __FILE__, __FUNCTION__, __LINE__ );
		}

		return resourcePointer;

	}
	//End Handle<T>::SafeDereference const



	//=========================================================================
	//! @function   Resource::Handle<T>::operator *
	//! @brief		Dereference the handle		
	//!
	//!  
	//! @throw		NullHandleDereference
	//! @throw		BadHandle
	//=========================================================================
	template <class T>
		T* Handle<T>::operator * ( )
	{
		#ifndef RELEASE_BUILD
			return SafeDereference();
		#else
			return Dereference();
		#endif
	}
	//end Handle::operator*


};
//end namespace Core


#endif //#ifndef CORE_HANDLE_H

