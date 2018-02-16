//======================================================================================
//! @file         RendererCreator.h
//! @brief        RendererCreator base class
//!               
//!				  Base class for an object that instantiate concrete implementations of
//!				  the IRenderer interface
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

#ifndef RENDERER_RENDERERCREATOR_H
#define RENDERER_RENDERERCREATOR_H


#include <boost/shared_ptr.hpp>


//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Forward declaration
    //=========================================================================
	class IRenderer;


	//!@class	RendererCreator
	//!@brief	Base class for an object that instantiate concrete implementations of
	//!			the IRenderer interface
	class RendererCreator
	{
		public:

			//Constructor
			RendererCreator ( const Char* typeName );

			virtual ~RendererCreator () 
			{	
				std::clog << "Destroying RendererCreator with TypeID: " << TypeID() << std::endl;
			}

			//Create method
			virtual boost::shared_ptr<IRenderer> Create() const = 0;

			//Accessors
			inline UInt TypeID() const { return m_typeID; }

		private:

			UInt m_typeID;
	};
	//End RendererCreator


};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERERCREATOR_H