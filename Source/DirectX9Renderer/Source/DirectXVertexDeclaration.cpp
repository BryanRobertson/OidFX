//======================================================================================
//! @file         DirectXVertexDeclaration.cpp
//! @brief        Specialisation of VertexDeclaration for DirectX9
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


#include "Core/Core.h"
#include "Renderer/VertexDeclarationDescriptor.h"
#include "DirectX9Renderer/DirectX9Renderer.h"
#include "DirectX9Renderer/DirectXVertexDeclaration.h"
#include "DirectX9Renderer/ErrorCodes.h"


using namespace DirectX9Renderer;



//=========================================================================
//! @function    DirectXVertexDeclaration::DirectXVertexDeclaration
//! @brief       DirectXVertexDeclaration constructor
//!              
//! @param       renderer [in] Reference to the renderer that created the declaration
//!              
//=========================================================================
DirectXVertexDeclaration::DirectXVertexDeclaration( DirectXRenderer& renderer,
													 const Renderer::VertexDeclarationDescriptor& desc )
: VertexDeclaration(desc), m_renderer(renderer)
{
	Compile();
}
//End DirectXVertexDeclaration::DirectXVertexDeclaration



//=========================================================================
//! @function    DirectXVertexDeclaration::Compile
//! @brief       Compile the vertex declaration into an IDirect3DVertexDeclaration9 
//!              object
//!              
//! @return      true if successful
//!				 false if failed
//=========================================================================
bool DirectXVertexDeclaration::Compile()
{
	using namespace Renderer;

	m_dxElements.clear();
	D3DVERTEXELEMENT9 element;
	
	VertexDeclarationDescriptor::const_iterator itr;

	//Create an array of D3DVERTEXELEMENT9 structures
	//to match our declaration
	for ( itr = m_desc.Begin(); itr != m_desc.End(); ++itr )
	{

		#ifdef DEBUG_BUILD
			std::clog << __FUNCTION__ << ": Compiling vertex element " 
					  << *itr 
					  << std::endl;
		#endif

		element.Stream = itr->StreamIndex();
		element.Offset = itr->Offset();
		element.Method = D3DDECLMETHOD_DEFAULT;
		element.UsageIndex = itr->UsageIndex();
		
		switch ( itr->Type() )
		{
			case DECLTYPE_FLOAT1:		
				element.Type = D3DDECLTYPE_FLOAT1;
				break;

			case DECLTYPE_FLOAT2:		
				element.Type = D3DDECLTYPE_FLOAT2;
				break;

			case DECLTYPE_FLOAT3:		
				element.Type = D3DDECLTYPE_FLOAT3;
				break;
			
			case DECLTYPE_FLOAT4:		
				element.Type = D3DDECLTYPE_FLOAT4;
				break;

			case DECLTYPE_COLOUR:		
				element.Type = D3DDECLTYPE_D3DCOLOR;
				break;

			case DECLTYPE_UBYTE4:		
				element.Type = D3DDECLTYPE_UBYTE4;
				break;

			case DECLTYPE_SHORT2:		
				element.Type = D3DDECLTYPE_SHORT2;
				break;

			case DECLTYPE_SHORT4:		
				element.Type = D3DDECLTYPE_SHORT4;
				break;

			case DECLTYPE_UBYTE4N:		
				element.Type = D3DDECLTYPE_UBYTE4N;
				break;

			case DECLTYPE_SHORT2N:
				element.Type = D3DDECLTYPE_SHORT2N;
				break;
			
			case DECLTYPE_SHORT4N:
				element.Type = D3DDECLTYPE_SHORT4N;
				break;

			case DECLTYPE_USHORT2N:
				element.Type = D3DDECLTYPE_USHORT2N;
				break;

			case DECLTYPE_USHORT4N:
				element.Type = D3DDECLTYPE_USHORT4N;
				break;

			case DECLTYPE_UDEC3:
				element.Type = D3DDECLTYPE_UDEC3;
				break;

			case DECLTYPE_DEC3N:
				element.Type = D3DDECLTYPE_DEC3N;
				break;
			
			case DECLTYPE_FLOAT16_2:
				element.Type = D3DDECLTYPE_FLOAT16_2;
				break;

			case DECLTYPE_FLOAT16_4:
				element.Type = D3DDECLTYPE_FLOAT16_4;
				break;

			default:
				debug_assert ( false, "Invalid type!" );
		}
		//End switch ( itr->Type() )

		switch ( itr->Usage() )
		{
			case DECLUSAGE_POSITION:		
				element.Usage = D3DDECLUSAGE_POSITION;
				break;

			case DECLUSAGE_POSITIONT:
				element.Usage = D3DDECLUSAGE_POSITIONT;
				break;

			case DECLUSAGE_BLENDWEIGHT:
				element.Usage = D3DDECLUSAGE_BLENDWEIGHT;
				break;

			case DECLUSAGE_BLENDINDEX:
				element.Usage = D3DDECLUSAGE_BLENDINDICES;
				break;

			case DECLUSAGE_NORMAL:
				element.Usage = D3DDECLUSAGE_NORMAL;
				break;

			case DECLUSAGE_POINTSIZE:
				element.Usage = D3DDECLUSAGE_PSIZE;
				break;

			case DECLUSAGE_TEXCOORD:
				element.Usage = D3DDECLUSAGE_TEXCOORD;
				break;

			case DECLUSAGE_TANGENT:
				element.Usage = D3DDECLUSAGE_TANGENT;
				break;

			case DECLUSAGE_BINORMAL:
				element.Usage = D3DDECLUSAGE_BINORMAL;
				break;

			case DECLUSAGE_DIFFUSE:
				element.Usage = D3DDECLUSAGE_COLOR;
				element.UsageIndex = 0;
				break;

			case DECLUSAGE_SPECULAR:
				element.Usage = D3DDECLUSAGE_COLOR;
				element.UsageIndex = 1;
				break;

			default:
				debug_assert ( false, "Invalid usage!" );
				break;
		}
		//End switch ( itr->Usage() )

		m_dxElements.push_back(element);
	}
	//End for ( ; itr != m_elements.end(); ++itr )

	D3DVERTEXELEMENT9 end = D3DDECL_END();
	m_dxElements.push_back( end );

	//Now that we have an array of D3DVERTEXELEMENT9 structures
	//we can use it to create a vertex declaration
	HRESULT result = m_renderer.Device()->CreateVertexDeclaration( &m_dxElements[0], &m_declaration );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ ": Failed! Couldn't create vertex declaration! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}	
	else
	{
		return true;
	}

}
//End DirectXVertexDeclaration::Compile



//=========================================================================
//! @function    DirectXVertexDeclaration::Bind
//! @brief       Bind the vertex declaration as the renderer's current declaration
//!              
//! @return      true if the bind succeeded
//!				 false if the bind failed
//=========================================================================
bool DirectXVertexDeclaration::Bind()
{
	HRESULT result = m_renderer.Device()->SetVertexDeclaration( m_declaration );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ ": SetVertexDeclaration failed! Error code " 
				  << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return true;
}
//End DirectXVertexDeclaration::Bind



//=========================================================================
//! @function    DirectXVertexDeclaration::ToFVFCode
//! @brief       Convert the declaration to an FVF code
//!              
//!              
//! @return      An FVF code for the declaration
//=========================================================================
DWORD DirectXVertexDeclaration::ToFVFCode() const
{
	if ( !m_declaration )
	{
		return 0;
	}

	DWORD    fvf = 0;
	HRESULT  result = D3DXFVFFromDeclarator ( &m_dxElements[0], &fvf );

	if ( FAILED(result) )
	{
		fvf = 0;
		std::cerr << __FUNCTION__ ": Failed creating FVF code from vertex declaration!" << std::endl;
	}

	return fvf;
}
//End DirectXVertexDeclaration::ToFVFCode