//======================================================================================
//! @file         VertexStreamBinding.cpp
//! @brief        Class representing a set of vertex buffers bound to stream indices
//!               
//!				  Simplifies the task of binding vertex buffers to different streams
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


#include "Core/Core.h"
#include "Renderer/Renderer.h"


using namespace Renderer;



//=========================================================================
//! @function    VertexStreamBinding::Bind
//! @brief       Bind each stream to the renderer's set of streams
//!              
//! @param       renderer [in] Renderer to bind the streams to
//!              
//=========================================================================
void VertexStreamBinding::Bind ( IRenderer& renderer )
{
	for ( UInt i=0; i<Renderer::g_maxStreams; ++i )
	{
		renderer.Bind( m_bindings[i], i );
	}
}
//End VertexStreamBinding::Bind



//=========================================================================
//! @function    VertexStreamBinding::operator <
//! @brief       Used for render state sorting. Compares each stream
//!              
//! @param       rhs [in] Renderer to bind the streams to
//!              
//! @return		 true if this stream binding is less than rhs, false otherwise
//=========================================================================
bool VertexStreamBinding::operator < ( const VertexStreamBinding& rhs ) const
{
	for ( UInt i=0; i<Renderer::g_maxStreams; ++i )
	{
		if ( m_bindings[i].Value() < rhs.m_bindings[i].Value() )
		{
			return true;
		}
	}

	return false;
}
//End VertexStreamBinding::operator < 