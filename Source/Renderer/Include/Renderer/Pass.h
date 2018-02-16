//======================================================================================
//! @file         Pass.h
//! @brief        Pass class
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 24 June 2005
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


#ifndef RENDERER_PASS_H
#define RENDERER_PASS_H



#include "Renderer/RenderState.h"



//namespace Renderer
namespace Renderer
{

	//=========================================================================
    // Forward declaration
    //=========================================================================
	class IRenderer;
	class TexturePrecacheList;


	//!@class	Pass
	//!@brief	Class containing the complete render state for a single pass of a rendered object
	class Pass
	{
		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			Pass( const RenderState& renderState );


            //=========================================================================
            // Public methods
			//=========================================================================

			//Precache
			void Precache ( TexturePrecacheList& precacheList );

			//Update
			void Update( Float timeElapsedInSeconds );

			//Get render state
			inline const RenderState& GetRenderState() const;

		private:

            //=========================================================================
            // Private data
            //=========================================================================
			RenderState m_renderState;
	};
	//End class Pass



    //=========================================================================
    //! @function    Pass::GetRenderState
    //! @brief       Return the render state of the pass
    //!              
    //!              
    //! @return      The render state
    //=========================================================================
	const RenderState& Pass::GetRenderState() const
	{
		return m_renderState;
	}
	//End Pass::GetRenderState


};
//end namespace Renderer


#endif
//#ifndef RENDERER_PASS_H
