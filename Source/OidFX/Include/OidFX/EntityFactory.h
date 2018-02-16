//======================================================================================
//! @file         EntityFactory.h
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


#ifndef OIDFX_ENTITYFACTORY_H
#define OIDFX_ENTITYFACTORY_H


//=========================================================================
// Forward declarations
//=========================================================================
namespace OidFX	   { class EntityNode; class IEntityCreator; class EntityManager; }


//namespace OidFX
namespace OidFX
{
	

	//! @class	EntityFactory
	//! @brief	Uses the factory design pattern to instantiate Entity objects
	class EntityFactory
	{

		public:


            //=========================================================================
            // Constructors
            //=========================================================================
			EntityFactory ( EntityManager& manager, Scene& scene );

            //=========================================================================
            // Public methods
            //=========================================================================
			UInt							RegisterType   ( boost::shared_ptr<IEntityCreator> creator );
			boost::shared_ptr<EntityNode> 	Create ( const Char* type, const Char* name = "DefaultName" );
			boost::shared_ptr<EntityNode> 	Create ( UInt type, const Char* name = "DefaultName" );


		private:

			//=========================================================================
            // Private types
            //=========================================================================
			typedef std::map <UInt, boost::shared_ptr<IEntityCreator> > EntityCreatorMap;

            //=========================================================================
            // Private data
            //=========================================================================
			EntityCreatorMap	m_entityCreators;
			EntityManager&		m_manager;
			Scene&				m_scene;

	};
	//end class EntityFactory


};
//end namespace OidFX


#endif 
//#ifndef ENTITYFACTORY_H