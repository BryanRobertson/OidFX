//======================================================================================
//! @file         RendererFactory.cpp
//! @brief        RendererFactory class. Implements the abstract factory pattern
//!               to instantiate concrete renderer classes
//!
//!				  Allows different renderers to be created, without having to
//!				  know anything about how the details of those renderers are implemented.
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 31 May 2005
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

#include <map>
#include "Core/Core.h"
#include "Renderer/RendererCreator.h"
#include "Renderer/RendererFactory.h"


using namespace Renderer;


//=========================================================================
// Static initialisation
//=========================================================================
boost::shared_ptr<RendererFactory> RendererFactory::ms_singleton 
											= boost::shared_ptr<Renderer::RendererFactory>();




//=========================================================================
//! @function    RendererFactory::RendererFactory
//! @brief       RendererFactory constructor
//=========================================================================
RendererFactory::RendererFactory ( )
{

}
//End RendererFactory::RendererFactory



//=========================================================================
//! @function    RendererFactory::RegisterCreator
//! @brief       Register a renderer creator
//!              
//! @param       creator [in] Pointer to a new IRendererCreator.
//!							  Once this call is completed, creator is
//!							  assumed to belong to this instance of RendererFactory 
//!							  and will be kept around until the RendererFactory is destroyed
//!
//!
//=========================================================================
void RendererFactory::RegisterCreator ( boost::shared_ptr<RendererCreator> creator )
{
	//Make sure that there's not already a creator with a matching creator type
	CreatorStore::const_iterator itr = m_creators.find(creator->TypeID());
	
	//If we found a creator object, then create the renderer
	if ( itr == m_creators.end() )
	{
		std::clog << "Successfully registered renderer creator with Type ID: " << creator->TypeID() << std::endl;
		
		std::pair<CreatorStore::key_type, CreatorStore::mapped_type> item(creator->TypeID(), creator);
		m_creators.insert ( item );
	}
	else
	{
		std::cerr << "Error: type ID clash trying to register RendererCreator with typeID " << creator->TypeID() << std::endl;
	}
}
//End RendererFactory::RegisterCreator


//=========================================================================
//! @function    RendererFactory::Create
//! @brief       
//!              
//! @param       rendererType [in]	String identified for the type of renderer
//!									to be created              
//!
//! @return      
//! @throw       
//=========================================================================
boost::shared_ptr<IRenderer> RendererFactory::Create ( const Char* rendererType ) const
{

	UInt typeHash = Core::GenerateHashFromString(rendererType);

	//Try to find a creator with a matching creator type
	RendererFactory::CreatorStore::const_iterator iter = m_creators.find(typeHash);

	//If we found a creator object, then create the renderer
	if ( iter != m_creators.end() )
	{
		return (*iter).second->Create();
	}
	else
	{
		std::cerr << "Error: Couldn't find renderer creator for renderer type " << rendererType << std::endl;
		throw Core::RuntimeError ( "Error! Couldn't find renderer creator! RenderFactory::Create failed!", typeHash,
									__FILE__, __FUNCTION__, __LINE__ );
	}

}
//End RendererFactory::Create