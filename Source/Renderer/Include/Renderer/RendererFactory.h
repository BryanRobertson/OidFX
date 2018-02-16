//======================================================================================
//! @file         RendererFactory.h
//! @brief        RendererFactory class. Implements the abstract factory pattern
//!               to instantiate concrete renderer classes
//!
//!				  Allows different renderers to be created, without having to
//!				  know anything about how the details of those renderers are implemented.
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 31 May 2005
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

#ifndef RENDERER_RENDERERFACTORY_H
#define RENDERER_RENDERERFACTORY_H

#include "Core/BasicTypes.h"
#include <map>
#include <boost/shared_ptr.hpp>



//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declaration
    //=========================================================================
	class IRenderer;
	class RendererCreator;


	//!@class	RendererFactory
	//!@brief	Implements the abstract factory pattern
	//!         to instantiate concrete renderer classes
	//!
	class RendererFactory
	{
		public:

			//Renderer factory
			RendererFactory();

			//Create a renderer
			boost::shared_ptr<IRenderer> Create( const Char* rendererType ) const;

			//Register a renderer creator
			void RegisterCreator ( boost::shared_ptr<RendererCreator> creator );

		private:

			//Private static methods
			static boost::shared_ptr<RendererFactory> ms_singleton;

			typedef std::map<UInt,boost::shared_ptr<RendererCreator> > CreatorStore;
			CreatorStore m_creators;

	};
	//End class RendererFactory

};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERERFACTORY_H