//======================================================================================
//! @file         RendererConstantToString.h
//! @brief        Contains functions for converting between Renderer constants and
//!				  strings
//!
//! @author       Bryan Robertson
//! @date         Monday, 06 June 2005
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

#ifndef RENDERER_RENDERERCONSTANTTOSTRING_H
#define RENDERER_RENDERERCONSTANTTOSTRING_H


#include <string>
#include "Renderer/RendererBuffer.h"
#include "Renderer/RendererTypes.h"
#include "Renderer/RendererStateConstants.h"


//namespace Renderer
namespace Renderer
{

	std::string RendererBufferUsageToString		  ( EUsage usage );
	std::string RendererBufferLockOptionsToString ( ELock lockOptions );
	std::string PrimTypeToString ( EPrimType type );
	std::string BoolStateIDToString ( EBoolStateID stateID );
	std::string UIntStateIDToString ( EUIntStateID stateID );
	std::string FloatStateIDToString ( EFloatStateID stateID );
	std::string TextureStageStateIDToString ( ETextureStageStateID stateID );
	std::string TextureOpToString ( ETextureOp op );
	std::string BlendOpToString ( EBlendOp op );
	std::string BlendModeToString ( EBlendMode mode );
	std::string CmpFuncToString ( ECmpFunc func );
	std::string StencilOpToString ( EStencilOp op );
	std::string FogModeToString ( EFogMode mode );
	std::string TextureAddressingModeToString ( ETextureAddressingMode mode );
	std::string TextureFilterToString ( ETextureFilter filter );
	std::string TextureArgumentToString ( ETextureArgument arg );

};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERERCONSTANTTOSTRING_H
