//======================================================================================
//! @file         DirectXRendererCreator.cpp
//! @brief        RendererCreator that insantiates the DirectXRenderer class
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 01 June 2005
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
#include "DirectX9Renderer/DirectXRendererCreator.h"
#include "DirectX9Renderer/DirectX9Renderer.h"


//namespace DirectX9Renderer
namespace DirectX9Renderer
{

    //=========================================================================
    //! @function    DirectXRendererCreator::Create
    //! @brief       Create a new DirectXRenderer object
    //!              
    //!              
    //! @return      A new DirectXRenderer
    //=========================================================================
	boost::shared_ptr<Renderer::IRenderer> DirectXRendererCreator::Create() const
	{
		return boost::shared_ptr<Renderer::IRenderer>(new DirectXRenderer());
	}
	//End DirectXRendererCreator::Create

}
//end namespace DirectX9Renderer