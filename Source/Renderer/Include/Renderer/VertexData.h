//======================================================================================
//! @file         VertexData.h
//! @brief        Class holding stream bindings, and a vertex declaration describing
//!				  those streams
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

#ifndef RENDERER_VERTEXDATA_H
#define RENDERER_VERTEXDATA_H


#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "Renderer/VertexElement.h"
#include "Renderer/VertexBuffer.h"


//namespace Renderer
namespace Renderer
{

    //=========================================================================
    // Forward declarations
    //=========================================================================
	class VertexStreamBinding;
	class IRenderer;


	//!@class	VertexData
	//!@brief	Class holding stream bindings, and a vertex declaration describing those streams
	class VertexData : public boost::noncopyable
	{
		public:

			VertexData( IRenderer& renderer ) throw();

			//Bind the vertex data
			void Bind ( IRenderer& renderer );

			//Get/SetStream for the stream binding
			void		  SetStream ( HVertexBuffer buffer, UInt streamIndex ) throw();
			HVertexBuffer GetStream ( UInt streamIndex ) throw();

			boost::shared_ptr<VertexStreamBinding>	StreamBinding() {	return m_streamBinding;		} 

		private:

			boost::shared_ptr<VertexStreamBinding> m_streamBinding;
	};
	//End Class VertexData

};
//end namespace Renderer


#endif
//#ifndef VERTEXDATA_H
