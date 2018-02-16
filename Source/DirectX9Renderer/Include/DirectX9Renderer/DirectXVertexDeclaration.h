//======================================================================================
//! @file         DirectXVertexDeclaration.h
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

#ifndef DIRECTX9RENDERER_DIRECTXVERTEXDECLARATION_H
#define DIRECTX9RENDERER_DIRECTXVERTEXDECLARATION_H


#include <atlbase.h>


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


    //=========================================================================
    // Forward declarations
    //=========================================================================
	class DirectXRenderer;



	//!@class	DirectXVertexDeclaration
	//!@brief	Specialisation of VertexDeclaration for DirectX9
	class DirectXVertexDeclaration : public Renderer::VertexDeclaration
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			DirectXVertexDeclaration ( DirectXRenderer&	renderer, 
									   const Renderer::VertexDeclarationDescriptor& desc );


            //=========================================================================
            // Public methods
            //=========================================================================
			bool Bind();

			DWORD ToFVFCode() const;


		private:

            //=========================================================================
            // Private methods
            //=========================================================================
			bool Compile(); 

            //=========================================================================
            // Private data
            //=========================================================================
			DirectXRenderer& m_renderer;
			CComPtr<IDirect3DVertexDeclaration9> m_declaration;
			std::vector<D3DVERTEXELEMENT9> m_dxElements; //<! Caches the result of converting the elements
													   //<! into an array of D3DVERTEXELEMENT9 structures

	};
	//end class DirectXVertexDeclaration


};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_DIRECTXVERTEXDECLARATION_H