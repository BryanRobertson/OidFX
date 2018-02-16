//======================================================================================
//! @file         RendererConstants.h
//! @brief        Constants used by the renderer
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 12 June 2005
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


#ifndef RENDERER_RENDERERCONSTANTS_H
#define RENDERER_RENDERERCONSTANTS_H


#include "Renderer/RendererStateConstants.h"



//namespace Renderer
namespace Renderer
{

    //=========================================================================
    // Constants
    //=========================================================================
	const UInt g_maxStreams = 16;				//!< The maximum number of streams a renderer can support

	//Resource management
	const UInt g_maxIndexBuffers = 8192;  //!< Maximum number of index buffers that can exist at any one time
	const UInt g_maxVertexBuffers = 8192; //!< Maximum number of vertex buffers that can exist at any one time
	const UInt g_maxTextures = 128;		  //!< Maximum number of textures that can be loaded at any one time
	const UInt g_maxEffects = 128;		  //!< Maximum number of effects that can be loaded at any one time
	const UInt g_maxVertexDeclarations = 16; //!< Maximum number of vertex declarations that can be loaded at any one time

};
//end namespace Renderer

#endif
//#ifndef RENDERER_RENDERERCONSTANTS_H

