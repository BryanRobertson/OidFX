//======================================================================================
//! @file         EffectManager.h
//! @brief        Manager class responsible for managing effects. 
//!				  An effect is essentially a material, it completely defines the 
//!               render state for an object, including the setting for all texture units,
//!				  any any vertex and pixel shaders.
//!
//!				  Effects are parsed from ASCII text ".ofx" files, which define them in a human-readable
//!				  format
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


#ifndef RENDERER_EFFECTMANAGER_H
#define RENDERER_EFFECTMANAGER_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "Core/ResourceManager.h"
#include "Renderer/Effect.h"


//namespace Renderer
namespace Renderer
{


	//=========================================================================
	// Forward declaration
	//=========================================================================
	class TexturePrecacheList;


	//!@class	EffectManager
	//!@brief	Manager class responsible for managing effects. 
	//!			An effect is a text file containing a series of techniques
	//!			which specify how to render an object with various render states, in a variable number of passes
	//!
	//!			Effects are loaded from ASCII .ofx files which describe the effect in a human editable format               
	class EffectManager : public Core::ResourceManager<Effect>, public boost::noncopyable
	{
		public:


            //=========================================================================
            // Constructor
            //=========================================================================
			EffectManager( IRenderer& renderer );
						
            //=========================================================================
            // Public methods
            //=========================================================================
			
			//Acquire Effect
			HEffect AcquireEffect( const Char* fileName );

			//Precache resources
			void Precache ( TexturePrecacheList& precacheList );

			//Update all effects
			void UpdateEffects ( Float timeElapsedInSeconds );

		private:

			IRenderer&								m_renderer;
   	};
	//End class EffectManager


};
//end namespace Renderer




#endif