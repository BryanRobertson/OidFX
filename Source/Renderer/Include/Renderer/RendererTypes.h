//======================================================================================
//! @file         RendererTypes.h
//! @brief        Types used by the renderer
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

#ifndef RENDERER_RENDERERTYPES_H
#define RENDERER_RENDERERTYPES_H


//namespace Renderer
namespace Renderer
{

	enum EPrimType
	{
		PRIM_POINTLIST,		//!< Render as a list of points
		PRIM_LINELIST,		//!< Render as a list of lines
		PRIM_LINESTRIP,		//!< Render as a contigous, connected set of lines
		PRIM_TRIANGLELIST,	//!< Render as a list of seperate triangles
		PRIM_TRIANGLESTRIP, //!< Render as a strip of connected triangles
		PRIM_TRIANGLEFAN	//!< Render as a fan of triangles
	};

	enum ETextureType
	{
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_CUBEMAP
	};

};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERERTYPES_H
