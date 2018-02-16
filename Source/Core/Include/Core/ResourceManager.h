//======================================================================================
//! @file         ResourceManager.h
//! @brief        Template for a handle based resource manager class
//!               
//!               This class is responsible for:
//!					creation and deletion of resources, 
//!					giving out handles to resources,
//!					determining which resources are no longer needed
//!
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 13 January 2005
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

#ifndef CORE_RESOURCEMANAGER_H
#define CORE_RESOURCEMANAGER_H

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/Hash.h"
#include "Core/ManagedPool.h"
#include "Core/HandleManager.h"
#include <boost/shared_ptr.hpp>


//namespace Core
namespace Core
{
	
	//! @class ResourceManager
	//! @brief Template for an abstract base class for a handle based resource manager
	//!
	//!		This class is responsible for:
	//!   		creation and deletion of resources, 
	//!   		giving out handles to resources,
	//!			determining which resources are no longer needed
	template <class ResourceType>
	class ResourceManager
	{
		public: 



            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			ResourceManager ( UInt maxResources );
			virtual ~ResourceManager ( );

			
            //=========================================================================
            // Public types
            //=========================================================================
			typedef Handle<ResourceType> HandleType;
			
            //=========================================================================
            // Friends
            //=========================================================================
			friend class HandleType;

		protected:

			
            //=========================================================================
            // Protected methods
            //=========================================================================
			HandleType				AcquireExistingResource ( const Char* name );
			HandleType				AcquireExistingResource ( UInt id );
			HandleType				AddNewResource	( boost::shared_ptr<ResourceType>& newResource );
			void					ReleaseResource (  const HandleType& resourceHandle );

			ResourceType*			GetResourcePointer ( const HandleType& resourceHandle );
			void					IncrementReferenceCount ( const HandleType& resourceHandle );

			bool					IsHandleValid ( const HandleType& resourceHandle ) const;

			
            //=========================================================================
            // Protected types
            //=========================================================================
			typedef ManagedPool<boost::shared_ptr<ResourceType> > ResourceStore;
			typedef ResourceStore::iterator                       iterator;
			typedef ResourceStore::const_iterator                 const_iterator;

			
            //=========================================================================
            // Protected methods
            //=========================================================================
			iterator          Begin( )                   { return m_resources.Begin();	    }
			iterator          End( )                     { return m_resources.End();		}
			const_iterator    Begin( ) const 	          { return m_resources.Begin();	    }
			const_iterator    End( )   const 		      { return m_resources.End();		}

		private:

			
            //=========================================================================
            // Static private methods
            //=========================================================================
			static ResourceManager*	GetManager();

			
            //=========================================================================
            // Static private data
            //=========================================================================
			static ResourceManager* ms_manager;

			
            //=========================================================================
            // Private data
            //=========================================================================
			ResourceStore				m_resources;	  //!< Data stored by the resource manager
			HandleManager<ResourceType>	m_handleManager;  //!< Controls creation, storage and validation of handle data
			
			UInt m_maxResources;

	};
	//end class ResourceManager


	
    //=========================================================================
    // Static definitions
    //=========================================================================
	template <class ResourceType>
	ResourceManager<ResourceType>* ResourceManager<ResourceType>::ms_manager = 0;



	//=========================================================================
	//! @function    ResourceManager<ResourceType>::ResourceManager
	//! @brief       ResourceManager::Constructor
	//!              
	//!              
	//!              
	//! @param       maxResources [in] Maximum number of resources that will
	//!								   be loaded at any one time
	//=========================================================================
	template <class ResourceType>
	ResourceManager<ResourceType>::ResourceManager ( UInt maxResources )
	: m_maxResources(maxResources), m_resources(maxResources)
	{
		debug_assert ( maxResources != 0, "0 is not a valid value for maxResources" );

		ms_manager = this;
	}
	//end ResourceManager<ResourceType>::ResourceManager




	//=========================================================================
	//! @function    ResourceManager<ResourceType>::~ResourceManager
	//! @brief       ResourceManager::Destructor
	//!                        
	//=========================================================================
	template <class ResourceType>
	ResourceManager<ResourceType>::~ResourceManager ( )
	{
		ms_manager = 0;
	}
	//ResourceManager<ResourceType>::~ResourceManager


	
    //=========================================================================
    // Protected methods
    //=========================================================================



	//=========================================================================
	//! @function    ResourceManager<ResourceType>::AddNewResource
	//! @brief       Add a new resource to the internal resource store
	//!              
	//!              Adds a new resource to the internal resource store
	//!				 and generates a handle for it.
	//!              
	//! @param       filename [in]	fileName of resource to add
	//!              
	//! @return      A handle to the new resource
	//! @throw		 OutOfFreeSlots<DataType> if there were no free slots to add a new item
	//=========================================================================
	template <class ResourceType>
	ResourceManager<ResourceType>::HandleType ResourceManager<ResourceType>::AddNewResource 
															( boost::shared_ptr<ResourceType>& newResource )
	{
		UInt newIndex = 0;
		UInt result = 0;

		try
		{
			//Add a new item to the resource store
			m_resources.AddItem( newResource, newIndex );
		}
		catch ( ... )
		{
			std::cerr << "Couldn't add " << newResource->Name() << " ResourceManager full!" << std::endl;
			
			throw;
		}

		//Generate a valid handle for the new resource
		m_handleManager.GenerateHandleForIndex ( newIndex );

		return m_handleManager.GetHandle(newIndex);
	}
	//end ResourceManager<ResourceType>::AddNewResource




	//=========================================================================
	//! @function    ResourceManager<ResourceType>::AcquireExistingResource
	//! @brief       Get a handle to an existing resource, using a name string as the key
	//!              
	//!              Searches the resource store for a resource with the name
	//!				 specified. 
	//!
	//! @param       name [in]	Filename of the resource
	//!              
	//! @return		 If the resource couldn't be found, then the null handle is returned
	//!				 otherwise, a handle to the resource is returned
	//=========================================================================
	template <class ResourceType>
	ResourceManager<ResourceType>::HandleType ResourceManager<ResourceType>::AcquireExistingResource ( const Char* name )
	{
		debug_assert ( name != 0, "Attempted to pass a null pointer as a resource name!" );

		//Generate a hash value from the name, for quicker searching.
		//This way we can just compare the hash values, rather than doing a 
		//string compare for every resource in the resource store
		UInt nameHash = Core::GenerateHashFromString ( name );

		UInt index = 0;
		bool found = false;
		ResourceStore::iterator it = m_resources.Begin();
		ResourceStore::iterator end = m_resources.End();

		//Iterate through the resource store, looking for a resource with 
		//a matching filename hash value
		while ( (false == found) && (it != end) )
		{
			//Check the namehash for the resource at that location
			//if it exists
			if ( (it->get()) && ((*it)->ID() == nameHash) )
			{
				//found it
				found = true;
				continue;
			}

			++it;
			++index;
		}

		//Load the resource if it could not be found, or return
		//a handle to the resource if it could
		if ( found == false )
		{
			return NullHandle();
		}
		else
		{
			#ifdef DEBUG_BUILD
					std::clog << __FUNCTION__ ": Received request for existing resource " << name << " returning handle" << std::endl;
			#endif

			m_resources[index]->IncrementReferenceCount();
			return m_handleManager.GetHandle(index);
		}

	}
	//end ResourceManager<ResourceType>::AcquireExistingResource




	//=========================================================================
	//! @function    ResourceManager<ResourceType>::AcquireExistingResource
	//! @brief       Get a handle to an existing resource, using an integer ID as the key
	//!
	//!              Searches the resource store for a resource with the name
	//!				 specified. 
	//!
	//! @param       name [in]	Filename of the resource
	//!              
	//! @return		 If the resource couldn't be found, then the null handle is returned
	//!				 otherwise, a handle to the resource is returned
	//=========================================================================
	template <class ResourceType>
	ResourceManager<ResourceType>::HandleType ResourceManager<ResourceType>::AcquireExistingResource ( UInt id )
	{
		debug_assert ( id != 0, "0 is not an acceptable value for ID!" );


		UInt index = 0;
		bool found = false;
		ResourceStore::iterator it = m_resources.Begin();
		ResourceStore::iterator end = m_resources.End();

		//Iterate through the resource store, looking for a resource with 
		//a matching filename hash value
		while ( (false == found) && (it != end) )
		{
			//Check the namehash for the resource at that location
			//if it exists
			if ( (it->get()) && ((*it)->ID() == id) )
			{
				//found it
				found = true;
				continue;
			}

			++it;
			++index;
		}

		//Load the resource if it could not be found, or return
		//a handle to the resource if it could
		if ( found == false )
		{
			return NullHandle();
		}
		else
		{
			#ifdef DEBUG_BUILD
					std::clog << __FUNCTION__ ": Received request for existing resource with id " << id << " returning handle" << std::endl;
			#endif

			m_resources[index]->IncrementReferenceCount();
			return m_handleManager.GetHandle(index);
		}

	}
	//end ResourceManager<ResourceType>::AcquireExistingResource





	//=========================================================================
	//! @function    ResourceManager<ResourceType>::ReleaseResource
	//! @brief       Decrement the reference count for a resource.
	//!				 If the newly decremented reference count is zero, then
	//!				 deletes the resource
	//!				
	//!              The handle is checked for validity, if the handle is invalid
	//!				 then nothing will happen
	//!              
	//! @param       resourceHandle [in]	Handle to the resource to be deleted
	//=========================================================================
	template <class ResourceType>
	void ResourceManager<ResourceType>::ReleaseResource ( const ResourceManager<ResourceType>::HandleType& resourceHandle )
	{

		#ifdef DEBUG_BUILD
				//std::clog << __FUNCTION__ ": Called on handle with value: " << resourceHandle.Value() << std::endl;
		#endif

		//Check the handle for validity
		if ( !IsHandleValid(resourceHandle) )
		{
			#ifdef DEBUG_BUILD
			std::cerr << "Warning, invalid handle " << resourceHandle.Value() << " passed to " __FUNCTION__ << "." << std::endl;
			#endif

			return;
		}

		//Decrement the reference count of the handle
		//Note that we use the Index property of the handle class, to index into the resource array
		m_resources[resourceHandle.Index()]->DecrementReferenceCount ( );

		if ( m_resources[resourceHandle.Index()]->ReferenceCount ( ) <= 0 )
		{

			std::clog << __FUNCTION__ ": Ref count for handle " << resourceHandle.Value() 
					  << " == 0, freeing resource" << std::endl;

			//Delete the resource
			m_resources[resourceHandle.Index()] = boost::shared_ptr<ResourceType>();
			//Set the associated handle to null
			m_handleManager.ClearHandle ( resourceHandle.Index() );
			//Put the resource slot back into the free slot list
			m_resources.RemoveItem(resourceHandle.Index());
		}

	}
	//end ResourceManager<ResourceType>::ReleaseResource





	//=========================================================================
	//! @function    ResourceManager<ResourceType>::GetResourcePointer
	//! @brief		 Get a pointer to a resource from its handle
	//!				 Note that the handle will be checked for validity in debug builds
	//!				 and will throw an exception if the handle is invalid, 
	//!				 but will not be checked in release builds
	//!              
	//! @param       resourceHandle [in] Handle to the resource
	//!              
	//! @return		 A pointer to the resource referenced by the handle      
	//! @throw       BadHandle if the handle is invalid
	//=========================================================================
	template <class ResourceType>
	ResourceType* ResourceManager<ResourceType>::GetResourcePointer ( const ResourceManager<ResourceType>::HandleType& resourceHandle )
	{
		#ifdef DEBUG_BUILD
		
			if (!IsHandleValid(resourceHandle))
			{
				throw BadHandle("Handle is not valid", 0, __FILE__, __FUNCTION__, __LINE__ );
			}

		#endif

		debug_assert ( !resourceHandle.IsNull(), "Tried to dereference a null handle" );
		debug_assert ( m_resources[resourceHandle.Index()].get() != 0, "Bad handle!" );

		return m_resources[resourceHandle.Index()].get();
	}
	//end ResourceManager<ResourceType>::GetResourcePointer




	//=========================================================================
	//! @function    ResourceManager<ResourceType>::IncrementReferenceCount
	//! @brief       Increment the reference count for the resource referenced by the handle provided
	//!				 In debug builds, the handle will be checked for validity, but release builds
	//!				 will assume that the handle is valid
	//!
	//! @param       resourceHandle [in] Handle to the resource which should have its count incremented
	//!              
	//! @throw       
	//=========================================================================
	template <class ResourceType>
	void ResourceManager<ResourceType>::IncrementReferenceCount ( const ResourceManager<ResourceType>::HandleType& resourceHandle )
	{

		#ifdef DEBUG_BUILD
		
			if (!IsHandleValid(resourceHandle))
			{
				throw BadHandle("Handle is not valid", 0, __FILE__, __FUNCTION__, __LINE__ );
			}

			//std::clog << __FUNCTION__ ": Called on handle with value: " << resourceHandle.Value() << std::endl;

		#endif


		debug_assert ( IsHandleValid(resourceHandle), "Passed an invalid handle to IncrementReferenceCount" );
		debug_assert ( m_resources[resourceHandle.Index()].get() != 0, "Called IncrementReferenceCount on a bad handle!" );

		m_resources[resourceHandle.Index()]->IncrementReferenceCount();
	}
	//end ResourceManager<ResourceType>::IncrementReferenceCount





	//=========================================================================
	//! @function    ResourceManager<ResourceType>::IsHandleValid
	//! @brief       Checks that the handle provided, actually refers to a resource
	//!              
	//! @param       resourceHandle [in]	 Handle to be checked
	//!              
	//! @return      true if the handle is valid, false otherwise
	//=========================================================================
	template <class ResourceType>
	bool ResourceManager<ResourceType>::IsHandleValid ( const ResourceManager<ResourceType>::HandleType& resourceHandle ) const
	{
		return m_handleManager.IsHandleValid( resourceHandle );
	}
	//end ResourceManager<ResourceType>::IsHandleValid




	//=========================================================================
	//! @function    ResourceManager<ResourceType>::GetManager
	//! @brief		 Get a pointer to the instance of the manager class       
	//!              
	//!              Allows handles to resources owned by the resource manager
	//!              to be dereferenced, without having a pointer to the resource manager
	//!              
	//! @return      A pointer to the resource manager
	//=========================================================================
	template <class ResourceType>
	ResourceManager<ResourceType>* ResourceManager<ResourceType>::GetManager ()
	{
		debug_assert ( ms_manager, "No instance of the manager class has been created!" );

		return ms_manager;
	}
	//end ResourceManager<ResourceType>::GetManager

};
//end namespace Core

#endif //#ifndef CORE_RESOURCEMANAGER_H