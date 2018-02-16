//======================================================================================
//! @file         EffectManager.cpp
//! @brief        Manager class responsible for managing effects. 
//!				  An effect is a text file containing a series of techniques
//!				  which specify how to render an object with various render states, in a variable number of passes
//!
//!				  Effects are loaded from ASCII .ofx files which describe the effect in a human editable format    
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 28 June 2005
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
#include "Renderer/Renderer.h"
#include "Renderer/EffectManager.h"
#include "Renderer/EffectParser.h"
#include "Renderer/StateManager.h"
#include "Renderer/TexturePrecacheList.h"



using namespace Renderer;



//=========================================================================
//! @function    EffectManager::EffectManager
//! @brief       EffectManager constructor
//!              
//!	@param		 renderer [in] Reference to the renderer so that the
//!							   effect manager can request resources
//!
//=========================================================================
EffectManager::EffectManager( IRenderer& renderer )
: m_renderer(renderer), Core::ResourceManager<Effect>( g_maxEffects )
{
}
//End EffectManager::EffectManager



//=========================================================================
//! @function    EffectManager::AcquireEffect
//! @brief       Get a handle to an effect, loading it if it does not exist
//!              
//! @param       fileName [in]
//!              
//! @return      A handle to the effect
//! @throw       
//=========================================================================
HEffect EffectManager::AcquireEffect ( const Char* fileName )
{
	debug_assert ( fileName, "Null filenames are not valid!" );
	HandleType handle ( AcquireExistingResource(fileName) );

	if ( handle.IsNull() )
	{
		std::clog << __FUNCTION__ ": Effect " << fileName << " not loaded. Loading..." << std::endl;

		EffectParser parser;
		boost::shared_ptr<Effect> effect = parser.ParseEffectFromFile ( fileName, m_renderer );

		return AddNewResource ( effect );
	}
	else
	{
		return handle;
	}

}
//End EffectManager::AcquireEffect



//=========================================================================
//! @function    EffectManager::Precache
//! @brief		 Creates a list of textures that need to be loaded for
//!				 all effects
//!
//! @param		 precacheList [in] List of textures to be loaded
//! 
//=========================================================================
void EffectManager::Precache ( TexturePrecacheList& precacheList )
{
	iterator current = Begin();
	iterator end = End();

	for ( ; current != end; ++current )
	{
		(*current)->Precache(precacheList);
	}
}
//End EffectManager::Precache




//=========================================================================
//! @function    EffectManager::UpdateEffects
//! @brief       Update all effects.
//!
//!				 Effects need to be updated every frame, in order for effects like
//!				 texture coordinate animations to work
//!              
//! @param       timeElapsedInSeconds [in] 
//!              
//=========================================================================
void EffectManager::UpdateEffects ( Float timeElapsedInSeconds )
{
	iterator current = Begin();
	iterator end = End();

	for ( ; current != end; ++current )
	{
		if ( current->get() != 0 )
		{
			(*current)->Update(timeElapsedInSeconds);
		}
	}
}
//End EffectManager::UpdateEffects