//======================================================================================
//! @file         EntityFactory.cpp
//! @brief        Class that uses the factory pattern to instantiate Entities
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 15 September 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================


#include "Core/Core.h"
#include "OidFX/EntityNode.h"
#include "OidFX/EntityCreator.h"
#include "OidFX/EntityFactory.h"



using namespace OidFX;



//=========================================================================
//! @function    EntityFactory::EntityFactory
//! @brief       EntityFactory constructor
//!              
//! @param       manager [in]
//!              
//=========================================================================
EntityFactory::EntityFactory ( EntityManager& manager, Scene& scene )
: m_manager(manager),
  m_scene(scene)
{
}
//End EntityFactory::EntityFactory



//=========================================================================
//! @function    EntityFactory::RegisterType
//! @brief       Register an EntityCreator with the factory
//!              
//!				 An EntityCreator allows the factory to instantiate
//!				 objects of a specific type. 
//!				 Creates a hash from the string value returned by creator->TypeName()
//!				 and searches the list of creators for a matching hash. If one is found
//!				 then the creator for this type is deemed to have been registered already
//!				 and 0 is returned. 
//!
//!				 If no creator could be found with the generated hash, then the creator
//!				 is added to the list of creators. The creator is deemed to be owned by
//!				 the EntityFactory from this point. 
//!
//! @param		 creator	[in] Pointer to an entity creator object
//!
//! @return		 If successful:
//!					The type ID number, which can be used to create an instance of 
//!					this entity type. This is a hash generated from the EntityCreator's type name
//!				 If failed:
//!					The operation may fail if a creator already exists with that type name,
//!					in which case, the method will return 0
//=========================================================================
UInt EntityFactory::RegisterType ( boost::shared_ptr<IEntityCreator> creator )
{
	UInt typeNameHash = 0;
	EntityCreatorMap::const_iterator objectSearch;

	//Hash the creator's type name
	std::string typeName ( creator->TypeName() );
	typeNameHash = Core::GenerateHashFromString ( typeName.c_str() );

	//Check to see if an EntityCreator with that type name already exists
	objectSearch = m_entityCreators.find ( typeNameHash );

	if ( objectSearch != m_entityCreators.end() )
	{
		//An object with that type name already exists
		#ifdef DEBUG_BUILD
		std::cerr	  << __FUNCTION__ " :  " << std::endl << "\t"
					  << "Failed to register EntityCreator with typeName: " 
					  << creator->TypeName() << " , typeID: " << typeNameHash << std::endl << std::endl;
		#endif

		return 0;
	}
	else
	{
		//Add the entity creator to the list, and return the type ID
		m_entityCreators[typeNameHash] = creator;

		#ifdef DEBUG_BUILD
			std::cerr << __FUNCTION__ " :  " << std::endl << "\t"
					  << "Successfully registered EntityCreator with typeName: " 
					  << creator->TypeName() << " , typeID: " << typeNameHash << std::endl << std::endl;
		#endif

		return typeNameHash;
	}

}
//end EntityFactory::RegisterType



//=========================================================================
//! @function    EntityFactory::Create
//! @brief       Return a new instance of the type specified
//!              
//! @param       type [in]	Type name of the entity
//!              
//! @return      A pointer to the entity, or a null pointer, if the
//!				 an invalid type ID was passed
//=========================================================================
boost::shared_ptr<EntityNode> 
	EntityFactory::Create ( const Char* type, const Char* name )
{
	debug_assert ( type, "Cannot create an entity with null type!" );

	UInt typeID = Core::GenerateHashFromString ( type );

	EntityCreatorMap::iterator objectSearch = m_entityCreators.find ( typeID );

	//Find the creator for the entity type
	if ( objectSearch != m_entityCreators.end() )
	{
		#ifdef DEBUG_BUILD
			std::cout << __FUNCTION__ " :  " << std::endl << "\t"
					  << "Found creator for typeName: " 
					  << type << " , typeID: " << typeID << std::endl << std::endl;
		#endif

		return objectSearch->second->Create( name, m_scene );
	}
	else
	{
		//No entity creator with the ID specified exists.
		std::stringstream errorMessage;

		errorMessage << "Failed to create object, with typeID: " << typeID
				     << ", no such EntityCreator exists" << std::endl << std::endl;

		throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
	
		return boost::shared_ptr<EntityNode>( );
	}
	
}
//end EntityFactory::Create


//=========================================================================
//! @function    EntityFactory::Create
//! @brief       Return a new instance of the type specified
//!              
//! @param       type [in]	ID number for the type to be created 
//!              
//! @return      A pointer to the entity, or a null pointer, if the
//!				 an invalid type ID was passed
//=========================================================================
boost::shared_ptr<EntityNode> 
	EntityFactory::Create ( UInt type, const Char* name )
{

	EntityCreatorMap::iterator objectSearch = m_entityCreators.find ( type );

	//Find the creator for the entity type
	if ( objectSearch != m_entityCreators.end() )
	{
		#ifdef DEBUG_BUILD
			std::cout << __FUNCTION__ " :  " << std::endl << "\t"
					  << "Found creator for typeName: " 
					  << objectSearch->second->TypeName() << " , typeID: " << type << std::endl << std::endl;
		#endif

		return objectSearch->second->Create( name, m_scene);
	}
	else
	{
		//No entity creator with the ID specified exists.
		std::cerr << __FUNCTION__ " :  " << std::endl << "\t"
					<< "Failed to create object, with typeID: " << type
				    << ", no such EntityCreator exists" << std::endl << std::endl;
	
		return boost::shared_ptr<EntityNode>( );
	}
	
}
//end EntityFactory::Create