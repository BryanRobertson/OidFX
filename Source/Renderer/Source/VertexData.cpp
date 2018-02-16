//======================================================================================
//! @file         VertexData.cpp
//! @brief        Class holding stream bindings, and a vertex declaration describing
//!				  those streams
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


#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexData.h"
#include "Renderer/VertexStreamBinding.h"
#include "Renderer/VertexDeclaration.h"



using namespace Renderer;



//=========================================================================
//! @function    VertexData::VertexData
//! @brief       VertexData constructor
//!
//! @param		 renderer [in] Reference to the renderer. Used to request a vertex declaration
//!
//=========================================================================
VertexData::VertexData( IRenderer& renderer ) 
{
	m_declaration = renderer.CreateVertexDeclaration();
	m_streamBinding = boost::shared_ptr<VertexStreamBinding>( new VertexStreamBinding() ) ;
}
//End VertexData::VertexData



//=========================================================================
//! @function    VertexData::Bind
//! @brief       Bind the vertex data's stream binding and vertex declaration to the renderer
//!
//! @param		 renderer [in] Renderer to bind to
//!
//=========================================================================
void VertexData::Bind ( IRenderer& renderer )
{
	renderer.Bind ( *m_declaration );
	m_streamBinding->Bind( renderer );
}
//End VertexData::Bind



//=========================================================================
//! @function    VertexData::SetStream
//! @brief       Set one of the stream bindings
//!              
//! @param       buffer 
//! @param       streamIndex 
//!              
//=========================================================================
void VertexData::SetStream ( HVertexBuffer buffer, UInt streamIndex )
{
	m_streamBinding->SetStream(buffer, streamIndex);
}
//End VertexData::SetStream



//=========================================================================
//! @function    VertexData::GetStream
//! @brief       Get one of the stream bindings
//!              
//! @param       streamIndex 
//!              
//! @return      The stream binding for stream Index
//! @throw       
//=========================================================================
HVertexBuffer VertexData::GetStream ( UInt streamIndex )
{
	return m_streamBinding->GetStream(streamIndex);
}
//End VertexData::GetStream

