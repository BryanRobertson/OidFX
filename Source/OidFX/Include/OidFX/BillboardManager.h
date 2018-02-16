//======================================================================================
//! @file         BillboardManager.h
//! @brief        Manager class for billboarded sprites. Provides
//!               a method to efficiently render multiple billboards
//!               
//!				  All billboards to be rendered in a frame, are added to the BillboardManager's
//!				  list of billboards. These are then put into batches, by their effect allowing
//!				  them to be rendered efficiently.
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 15 October 2005
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

#ifndef OIDFX_BILLBOARDMANAGER_H
#define OIDFX_BILLBOARDMANAGER_H


#include "Renderer/Effect.h"
#include "Renderer/VertexStreamBinding.h"
#include "Renderer/VertexDeclaration.h"
#include "OidFX/Constants.h"
#include "OidFX/Billboard.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer		{ class IRenderer; class StateManager;	}
namespace OidFX			{ class Camera; class Billboard;		}


//namespace OidFX
namespace OidFX
{


	//!@class	BillboardManager
	//!@brief	Manager class for billboarded sprites. Provides
	//!         a method to efficiently render multiple billboards
	class BillboardManager
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			BillboardManager ( Renderer::IRenderer& renderer,
							   Renderer::StateManager& stateManager,
							   UInt maxBillboards = g_maxBillboards );


            //=========================================================================
            // Public methods
            //=========================================================================
			void CompileRenderQueue();
			void Render ( Renderer::IRenderer& renderer, Camera& camera );

			inline void Update ( Float timeElapsedInSeconds );

			inline void ClearBillboardList();
			inline void AddToBillboardList ( Billboard& billboard );

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			
			//! Keeps track of a set of vertices to be rendered with a specific effect
			struct RenderQueueEntry
			{
				Renderer::HEffect	effect;
				UInt				startIndex;
				UInt				vertexCount;
			};

			//! Stores vertex data for the renderer
			struct Vertex
			{
				Float	position[3];
				UInt32  colour;
				Float	texCoord0[2];
			};

			//! List of billboards to be rendered this frame
			typedef std::multimap<Renderer::HEffect, Billboard*>	BillboardList;

			//! Stores data about batches of billboards with the same effect
			typedef Core::Deque<RenderQueueEntry>::Type	RenderQueue;								

            //=========================================================================
            // Private methods
            //=========================================================================
			

            //=========================================================================
            // Private data
            //=========================================================================
			UInt							m_maxBillboards;

			//Rendering related
			Renderer::IRenderer&			m_renderer;
			Renderer::StateManager&			m_stateManager;
			Renderer::VertexStreamBinding	m_streamBinding;
			Renderer::HVertexDeclaration	m_vertexDeclaration;

			BillboardList					m_billboardList;
			RenderQueue						m_renderQueue;

	};
	//End class BillboardManager


    //=========================================================================
    //! @function    BillboardManager::Update
    //! @brief       Update the billboard manager
    //!              
    //! @param       timeElapsedInSeconds [in]
    //!              
    //=========================================================================
	void BillboardManager::Update ( Float timeElapsedInSeconds )
	{
		CompileRenderQueue();
	}
	//End BillboardManager::Update



    //=========================================================================
    //! @function    BillboardManager::ClearBillboardList
    //! @brief       
    //=========================================================================
	void BillboardManager::ClearBillboardList()
	{
		m_billboardList.clear();
		m_renderQueue.clear();
	}
	//End BillboardManager::ClearBillboardList



    //=========================================================================
    //! @function    BillboardManager::AddToBillboardList
    //! @brief       Add a billboard to the billboard list
    //!              
	//!				 A billboard must add itself to the billboard list, in order to be rendered
	//!
    //! @param       billboard [in]
    //!              
    //=========================================================================
	void BillboardManager::AddToBillboardList ( Billboard& billboard )
	{
		m_billboardList.insert( BillboardList::value_type(billboard.GetEffect(), &billboard) );
	}
	//End BillboardManager::AddToBillboardList



}
//End namespace OidFX




#endif
//#ifndef OIDFX_BILLBOARDMANAGER_H

