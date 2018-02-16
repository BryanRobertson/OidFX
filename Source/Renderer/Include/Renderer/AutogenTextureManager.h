//======================================================================================
//! @file         AutogenTextureManager.h
//! @brief        Class that manages auto-generated textures. 
//!
//!				  Auto generated textures, are any textures that are generated at run-time
//!				  but should be accessable to effects. 
//!
//!				  Textures in the autogen list are accessable by name, and the texture
//!               associated with that name can be changed at any time
//!
//!				  When an effect with an auto generated texture is loaded, an integer ID
//!				  for the texture is generated. Applications can associate any texture with
//!				  this ID at any time, as they see fit. 
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 13 July 2005
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

#ifndef RENDERER_AUTOGENTEXTUREMANAGER_H
#define RENDERER_AUTOGENTEXTUREMANAGER_H


#include <boost/noncopyable.hpp>
#include "Renderer/Texture.h"


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declaration
    //=========================================================================
	class IRenderer;


	//!@class	AutogenTextureManager
	//!@brief	Class that manages auto-generated textures
	//!
	//!			Auto generated textures, are any textures that are generated at run-time
	//!			but should be accessable to effects.
	//!			Textures in the autogen list are accessable by name, and the texture
	//!         associated with that name can change at any time
	//!
	//!			When an effect with an auto generated texture is loaded, an integer ID
	//!			for the texture is generated. Applications can associate any texture with
	//!			this ID at any time, as they see fit. 
	//!
	class AutogenTextureManager : public boost::noncopyable
	{
		public:
	
            //=========================================================================
            // Constructors
            //=========================================================================
			AutogenTextureManager ( IRenderer& renderer ) throw();


            //=========================================================================
            // Public methods
            //=========================================================================
			bool BindAutogenTexture ( ETextureStageID stageID, UInt textureID ) throw();
			void UnbindAutogenTexture ( ETextureStageID stageID ) throw();

			void	 SetAutogenHandle ( UInt textureID, HTexture handle ) throw();
			HTexture GetAutogenHandle ( UInt textureID ) throw();
			
		private:

            //=========================================================================
            // Private types
            //=========================================================================
			typedef std::map<UInt, HTexture>	IDToTextureMapping;

            //=========================================================================
            // Private data
            //=========================================================================
			UInt					 m_bindings[TEXTURE_STAGE_COUNT];
			IDToTextureMapping		 m_textures;
			IRenderer&				 m_renderer;

	};
	//End class AutogenTextureManager


};
//end namespace Renderer



#endif
//#ifndef RENDERER_AUTOGENTEXTUREMANAGER_H
