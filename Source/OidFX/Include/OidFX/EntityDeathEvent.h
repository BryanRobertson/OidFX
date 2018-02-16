//======================================================================================
//! @file         EntityDeathEvent.h
//! @brief        Event handling for entity death
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 13 October 2005
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


#ifndef OIDFX_ENTITYDEATHEVENT_H
#define OIDFX_ENTITYDEATHEVENT_H



//=========================================================================
// Forward declaration
//=========================================================================
namespace OidFX	{	class EntityNode;	}



//Namespace OidFX
namespace OidFX
{


	//!@class	IEntityDeathSensitive
	//!@brief	Interface for classes sensitive to the death of an entity 
	class IEntityDeathSensitive
	{
		public:

			virtual ~IEntityDeathSensitive() = 0 {}
			virtual void OnEntityDeath ( EntityNode* entity ) = 0;

	};
	//End class IEntityDeathSensitive



	//!@class	EntityDeathEventHandler
	//!@brief	Informs objects about the death of an entity
	class EntityDeathEventHandler : public Core::EventHandler<IEntityDeathSensitive>,
									public IEntityDeathSensitive
	{
		public:

			EntityDeathEventHandler ( IEntityDeathSensitive& deathSensitiveObject )
				: Core::EventHandler<IEntityDeathSensitive>( deathSensitiveObject ) { }

			void OnEntityDeath ( EntityNode* entity ) 
				{ m_reciever.OnEntityDeath(entity); }
		
	};
	//end class EntityDeathEventHandler


	//!@class	EntityDeathEvent
	//!@brief	Event class that informs IEntityDeathSensitive objects of a entity death events
	class EntityDeathEvent : public Core::Event<EntityDeathEventHandler, IEntityDeathSensitive>, 
							 public IEntityDeathSensitive
	{
		public:

			EntityDeathEvent () : Core::Event<EntityDeathEventHandler, IEntityDeathSensitive>() {}

			void OnEntityDeath ( EntityNode* entity );
	};
	//end class KeyboardEvent


}
//End namespace OidFX


#endif
//#ifndef OIDFX_ENTITYDEATHEVENT_H