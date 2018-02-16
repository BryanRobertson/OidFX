//======================================================================================
//! @file         BillboardManager.cpp
//! @brief        Manager class for billboarded sprites. Provides
//!               a method to efficiently render multiple billboards
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 17 October 2005
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


#include "Core/Core.h"
#include "Math/Matrix4x4.h"
#include "Renderer/Renderer.h"
#include "Renderer/StateManager.h"
#include "OidFX/Billboard.h"
#include "OidFX/BillboardManager.h"



using namespace OidFX;



//=========================================================================
//! @function    BillboardManager::BillboardManager
//! @brief       BillboardManager constructor
//!              
//! @param       renderer		[in]
//! @param       stateManager	[in]
//! @param       maxBillboards	[in]
//!              
//=========================================================================
BillboardManager::BillboardManager ( Renderer::IRenderer& renderer,
									 Renderer::StateManager& stateManager,
									 UInt maxBillboards )
									 : m_maxBillboards(maxBillboards),
									   m_renderer(renderer),
									   m_stateManager(stateManager)
{

	//Create the vertex declaration
	Renderer::VertexDeclarationDescriptor desc;
	desc.AddElement ( 0, 0,  Renderer::DECLTYPE_FLOAT3, Renderer::DECLUSAGE_POSITION, 0 );
	desc.AddElement ( 0, 12, Renderer::DECLTYPE_COLOUR, Renderer::DECLUSAGE_DIFFUSE, 0 );
	desc.AddElement ( 0, 16, Renderer::DECLTYPE_FLOAT2, Renderer::DECLUSAGE_TEXCOORD, 0 ); 

	m_vertexDeclaration = renderer.AcquireVertexDeclaration ( desc );


	Renderer::HVertexBuffer stream0 = renderer.CreateVertexBuffer ( sizeof(Vertex), 
																	maxBillboards * 6, 
																	Renderer::USAGE_DYNAMICWRITEONLY );

	m_streamBinding.SetStream( stream0, 0 );

	//Reserve some space in the render queue and render list
	//renderQueue.reserve( maxBillboards );
	//renderList.reserve( maxBillboards );
}
//End BillboardManager::BillboardManager



//=========================================================================
//! @function    BillboardManager::CompileRenderQueue
//! @brief       Compiles the render list into a list of startindices
//!              and vertex counts for each effect (the render queue).
//!
//=========================================================================
void BillboardManager::CompileRenderQueue ( )
{
	
	Renderer::HEffect currentEffect;
	UInt			  startIndex = 0;
	UInt			  count = 1;

	if ( m_billboardList.size() > 0 )
	{
		currentEffect = m_billboardList.begin()->first;
	}
	else
	{
		return;
	}

	for ( BillboardList::const_iterator itr = m_billboardList.begin();
		  itr != m_billboardList.end();
		  ++itr )
	{

		BillboardList::const_iterator temp = itr;
		++temp;

		if ( (itr->first != currentEffect) 
			|| (temp == m_billboardList.end()) )
		{
			//Add the list of billboards with the previous effect
			//to the render queue
			RenderQueueEntry entry;
			entry.effect = currentEffect;
			entry.startIndex = startIndex;
			entry.vertexCount = count * 6;

			m_renderQueue.push_back( entry );

			//Reset the variables for the next queue entry
			startIndex += count * 6;
			currentEffect = itr->first;
			count = 0;
		}

		++count;
	}

}
//End BillboardManager::CompileRenderQueue



//=========================================================================
//! @function    BillboardManager::Render 
//! @brief       Renders all billboards in the billboard list
//!
//!				 Updates all billboards to face the camera
//!				 Copies the billboards vertices to the vertex buffer
//!				 Renders all items in the render queue
//!
//! @param		 renderer [in]	Renderer to draw the billboard list with
//! @param		 camera	  [in]	Camera from which to render the billboards
//!								the billboards will be aligned to this camera
//!								
//!
//=========================================================================
void BillboardManager::Render ( Renderer::IRenderer& renderer, Camera& camera )
{
	if ( m_renderQueue.empty() )
	{
		return;
	}

	Renderer::ScopedVertexBufferLock lock = 
		m_streamBinding.GetStream(0)->LockAll(Renderer::LOCK_NORMAL);

	if ( !lock )
	{
		throw Core::RuntimeError ( "Error, couldn't lock vertex buffer!", 0,
									__FILE__, __FUNCTION__, __LINE__ );
	}

	BillboardManager::Vertex* buffer = reinterpret_cast<Vertex*>(lock.GetLockPointer());

	//Update the billboards to face the camera
	for ( BillboardList::iterator itr = m_billboardList.begin();
		  itr != m_billboardList.end();
		  ++itr )
	{
		//Recalculate the vertices so that they face the camera
		itr->second->RecalculateVertices( camera );

		//Copy the new vertices to the vertex buffer
		(buffer)->position[0] = itr->second->GetVertex( Billboard::VERT_TOPLEFT ).X();
		(buffer)->position[1] = itr->second->GetVertex( Billboard::VERT_TOPLEFT ).Y();
		(buffer)->position[2] = itr->second->GetVertex( Billboard::VERT_TOPLEFT ).Z();
		(buffer)->texCoord0[0] = 0.0f;
		(buffer)->texCoord0[1] = 0.0f;
		(buffer)->colour	  = Renderer::Colour4f( 1.0f, 1.0f, 1.0f, itr->second->GetOpacity());
		++buffer;

		(buffer)->position[0] = itr->second->GetVertex( Billboard::VERT_BOTTOMLEFT ).X();
		(buffer)->position[1] = itr->second->GetVertex( Billboard::VERT_BOTTOMLEFT ).Y();
		(buffer)->position[2] = itr->second->GetVertex( Billboard::VERT_BOTTOMLEFT ).Z();
		(buffer)->texCoord0[0] = 0.0f;
		(buffer)->texCoord0[1] = 1.0f;
		(buffer)->colour	  = Renderer::Colour4f( 1.0f, 1.0f, 1.0f, itr->second->GetOpacity());
		++buffer;
		
		(buffer)->position[0] = itr->second->GetVertex( Billboard::VERT_TOPRIGHT ).X();
		(buffer)->position[1] = itr->second->GetVertex( Billboard::VERT_TOPRIGHT ).Y();
		(buffer)->position[2] = itr->second->GetVertex( Billboard::VERT_TOPRIGHT ).Z();
		(buffer)->texCoord0[0] = 1.0f;
		(buffer)->texCoord0[1] = 0.0f;
		(buffer)->colour	  = Renderer::Colour4f( 1.0f, 1.0f, 1.0f, itr->second->GetOpacity());
		++buffer;

		(buffer)->position[0] = itr->second->GetVertex( Billboard::VERT_TOPRIGHT ).X();
		(buffer)->position[1] = itr->second->GetVertex( Billboard::VERT_TOPRIGHT ).Y();
		(buffer)->position[2] = itr->second->GetVertex( Billboard::VERT_TOPRIGHT ).Z();
		(buffer)->texCoord0[0] = 1.0f;
		(buffer)->texCoord0[1] = 0.0f;
		(buffer)->colour	  = Renderer::Colour4f( 1.0f, 1.0f, 1.0f, itr->second->GetOpacity());
		++buffer;

		(buffer)->position[0] = itr->second->GetVertex( Billboard::VERT_BOTTOMLEFT ).X();
		(buffer)->position[1] = itr->second->GetVertex( Billboard::VERT_BOTTOMLEFT ).Y();
		(buffer)->position[2] = itr->second->GetVertex( Billboard::VERT_BOTTOMLEFT ).Z();
		(buffer)->texCoord0[0] = 0.0f;
		(buffer)->texCoord0[1] = 1.0f;
		(buffer)->colour	  = Renderer::Colour4f( 1.0f, 1.0f, 1.0f, itr->second->GetOpacity());
		++buffer;
	
		(buffer)->position[0] = itr->second->GetVertex( Billboard::VERT_BOTTOMRIGHT ).X();
		(buffer)->position[1] = itr->second->GetVertex( Billboard::VERT_BOTTOMRIGHT ).Y();
		(buffer)->position[2] = itr->second->GetVertex( Billboard::VERT_BOTTOMRIGHT ).Z();
		(buffer)->texCoord0[0] = 1.0f;
		(buffer)->texCoord0[1] = 1.0f;
		(buffer)->colour	  = Renderer::Colour4f( 1.0f, 1.0f, 1.0f, itr->second->GetOpacity());
		++buffer;
	}

	lock.Release();

	//Bind the vertex buffer for rendering
	m_stateManager.ActivateVertexStreamBinding( m_streamBinding );
	m_stateManager.ActivateVertexDeclaration( m_vertexDeclaration );
	m_renderer.SetMatrix( Renderer::MAT_WORLD, Math::Matrix4x4::IdentityMatrix );

	//Render all billboards in the render queue
	for ( RenderQueue::iterator itr = m_renderQueue.begin();
		  itr != m_renderQueue.end();
		  ++itr )
	{
		
		for ( UInt i=0; i < itr->effect->Techniques(0).PassCount(); ++i )
		{
			m_stateManager.ActivateRenderState( itr->effect, 0, i );

			m_renderer.DrawPrimitive ( Renderer::PRIM_TRIANGLELIST, 
									   itr->startIndex, 
									   itr->vertexCount );
		}

	}

}
//End BillboardManager::Render
