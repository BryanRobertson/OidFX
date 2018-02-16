//======================================================================================
//! @file         VertexDeclarationManager.h
//! @brief        Resource manager for vertex declaration resources
//!               
//!				  VertexDeclaration objects describe a format for vertex data
//!               contained in an arbitrary number of vertex "streams"
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 28 July 2005
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


#ifndef RENDERER_VERTEXDECLARATION_MANAGER
#define RENDERER_VERTEXDECLARATION_MANAGER


#include <boost/noncopyable.hpp>
#include "Core/ResourceManager.h"
#include "Renderer/VertexDeclaration.h"



//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer { class IVertexDeclarationCreator; class VertexDeclarationDescriptor; }



//namespace Renderer
namespace Renderer
{

	//!@class	VertexDeclarationManager
	//!@brief	
	class VertexDeclarationManager : public Core::ResourceManager<VertexDeclaration>,
									 public boost::noncopyable
	{
		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			VertexDeclarationManager ( IVertexDeclarationCreator& creator );


            //=========================================================================
            // Public methods
            //=========================================================================
			HandleType	AcquireVertexDeclaration ( VertexDeclarationDescriptor& declaration );


		private:

            //=========================================================================
            // Private data
            //=========================================================================
			IVertexDeclarationCreator*	m_creator;

	};
	//End class VertexDeclarationManager

}
//end namespace Renderer


#endif 
//#ifndef RENDERER_VERTEXDECLARATION_MANAGER