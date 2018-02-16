//======================================================================================
//! @file         DirectXVertexDeclarationCreator.h
//! @brief        Implementation of the IVertexDeclarationCreator interface that creates
//!               DirectXVertexDeclaration objects
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 29 July 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================

#ifndef DIRECTX9RENDERER_DIRECTXVERTEXDECLARATIONCREATOR_H
#define DIRECTX9RENDERER_DIRECTXVERTEXDECLARATIONCREATOR_H


#include "Renderer/VertexDeclarationCreator.h"


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


	//!@class	DirectXVertexDeclarationCreator
	//!@brief	Implementation of the IVertexDeclarationCreator interface that creates
	//!         DirectXVertexDeclaration objects
	class DirectXVertexDeclarationCreator : public Renderer::IVertexDeclarationCreator
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			DirectXVertexDeclarationCreator ( DirectXRenderer& renderer ) : m_renderer(renderer) {}


            //=========================================================================
            // Public methods
            //=========================================================================
			inline boost::shared_ptr<Renderer::VertexDeclaration> CreateVertexDeclaration 
																	( const Renderer::VertexDeclarationDescriptor& desc );

		private:

            //=========================================================================
            // Private data
            //=========================================================================
			DirectXRenderer& m_renderer;

	};
	//End class DirectXVertexDeclarationCreator




    //=========================================================================
    //! @function    DirectXVertexDeclarationCreator::CreateVertexDeclaration
    //! @brief       Create a new DirectXVertexDeclaration object
    //!              
    //! @param       desc [in] Descriptor for the vertex format
    //!              
    //! @return      A new DirectXVertexDeclaration object
    //! @throw       
    //=========================================================================
	boost::shared_ptr<Renderer::VertexDeclaration> DirectXVertexDeclarationCreator::CreateVertexDeclaration 
														( const Renderer::VertexDeclarationDescriptor& desc )
	{
		return boost::shared_ptr<Renderer::VertexDeclaration>( new DirectXVertexDeclaration(m_renderer, desc) );
	}
	//End DirectXVertexDeclarationCreator::CreateVertexDeclaration


}
//end namespace DirectX9Renderer


#endif 
//#ifndef DIRECTX9RENDERER_DIRECTXVERTEXDECLARATIONCREATOR_H

