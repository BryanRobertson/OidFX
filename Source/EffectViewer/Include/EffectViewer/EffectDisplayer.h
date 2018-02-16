//======================================================================================
//! @file         EffectDisplayer.h
//! @brief        Class designed to test an effect by displaying the effect on a quad 
//!               
//! @author       Bryan Robertson
//! @date         Friday, 01 July 2005
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

#ifndef EFFECTVIEWER_EFFECTDISPLAYER_H
#define EFFECTVIEWER_EFFECTDISPLAYER_H


#include <boost/shared_ptr.hpp>
#include "Renderer/Renderer.h"
#include "Renderer/RenderQueue.h"
#include "Renderer/EffectManager.h"
#include "Renderer/Renderable.h"
#include "Renderer/Effect.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexData.h"


//namespace EffectViewer
namespace EffectViewer
{


	//!@class	EffectDisplayer
	//!@brief	Class designed to test an effect by displaying the effect on a quad
	class EffectDisplayer : public Renderer::IRenderable
	{
		public:

            //=========================================================================
            // Constructor
            //=========================================================================
			inline EffectDisplayer ( Renderer::IRenderer& renderer, Renderer::EffectManager& effectManager, const Char* effectName );
			

            //=========================================================================
            // Public methods
            //=========================================================================
			void QueueForRendering ( Renderer::RenderQueue& queue )
			{
				for ( UInt i=0; i < m_effect->Techniques(0).PassCount(); ++i )
				{
					queue.QueueForRendering ( *this, m_effect, 0, i, m_vertexData, m_indexBuffer );
				}
			}

			void Render ( Renderer::IRenderer& renderer )
			{
				renderer.DrawIndexedPrimitive ( Renderer::PRIM_TRIANGLESTRIP, 0, 0, 4 );
			}


		private:


            //=========================================================================
            // Private data
            //=========================================================================
			Renderer::HEffect						m_effect;
			Renderer::HIndexBuffer					m_indexBuffer;
			boost::shared_ptr<Renderer::VertexData>	m_vertexData;

	};
	//End EffectDisplayer



    //=========================================================================
    //! @function    EffectDisplayer::EffectDisplayer
    //! @brief       EffectDisplayer constructor
    //!              
    //! @param       renderer 
    //! @param       effectManager 
    //! @param       effectName 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	EffectDisplayer::EffectDisplayer ( Renderer::IRenderer& renderer, 
		                     Renderer::EffectManager& effectManager, 
		                     const Char* effectName )
	{
		using namespace Renderer;

		struct TestVertex
		{
			Float position[3];
			UInt32 colour;
			Float texCoord0[2];
		};

		//Setup the vertex buffer
		HVertexBuffer vertexBuffer = renderer.CreateVertexBuffer ( sizeof(TestVertex), 4, Renderer::USAGE_STATICWRITEONLY );
		
		if ( !vertexBuffer )
		{
			throw Core::RuntimeError ( "Couldn't create vertex buffer!", 0, __FILE__, __FUNCTION__, __LINE__);
		}

		ScopedVertexBufferLock vLock = vertexBuffer->LockAll( Renderer::LOCK_NORMAL );

		if ( !vLock )
		{
			throw Core::RuntimeError ( "Couldn't lock vertex buffer!", 0, __FILE__, __FUNCTION__, __LINE__ );
		}

		Float halfWidth = static_cast<Float>(renderer.ScreenWidth()) / 2;
		Float halfHeight = static_cast<Float>(renderer.ScreenHeight()) / 2;
		Float quadWidth = Core::Min<Float>(static_cast<Float>(renderer.ScreenHeight()), 512.0f);
		Float halfQuadWidth = quadWidth / 2;

		TestVertex* vertexPointer = static_cast<TestVertex*>(vLock.GetLockPointer());
		vertexPointer->position[0] = halfWidth - halfQuadWidth;
		vertexPointer->position[1] = halfHeight - halfQuadWidth;
		vertexPointer->position[2] = 1.0f;
		vertexPointer->colour = 0xFFFFFFFF;
		vertexPointer->texCoord0[0] = 0.0f;
		vertexPointer->texCoord0[1] = 0.0f;

		++vertexPointer;
		vertexPointer->position[0] = halfWidth - halfQuadWidth;
		vertexPointer->position[1] = halfHeight + halfQuadWidth;
		vertexPointer->position[2] = 1.0f;
		vertexPointer->colour = 0xFFFFFFFF;
		vertexPointer->texCoord0[0] = 0.0f;
		vertexPointer->texCoord0[1] = 1.0f;

		++vertexPointer;
		vertexPointer->position[0] = halfWidth + halfQuadWidth;
		vertexPointer->position[1] = halfHeight - halfQuadWidth;
		vertexPointer->position[2] = 1.0f;
		vertexPointer->colour = 0xFFFFFFFF;
		vertexPointer->texCoord0[0] = 1.0f;
		vertexPointer->texCoord0[1] = 0.0f;

		++vertexPointer;
		vertexPointer->position[0] = halfWidth + halfQuadWidth;
		vertexPointer->position[1] = halfHeight + halfQuadWidth;
		vertexPointer->position[2] = 1.0f;
		vertexPointer->colour = 0xFFFFFFFF;
		vertexPointer->texCoord0[0] = 1.0f;
		vertexPointer->texCoord0[1] = 1.0f;
		vLock.Release();

		//Set up the vertex data
		m_vertexData = boost::shared_ptr<Renderer::VertexData> ( new Renderer::VertexData(renderer) );
		m_vertexData->AddElement ( 0, 0,  Renderer::DECLTYPE_FLOAT3, Renderer::DECLUSAGE_POSITION, 0 );
		m_vertexData->AddElement ( 0, 12, Renderer::DECLTYPE_COLOUR, Renderer::DECLUSAGE_DIFFUSE,  0 );
		m_vertexData->AddElement ( 0, 16, Renderer::DECLTYPE_FLOAT2, Renderer::DECLUSAGE_TEXCOORD, 0 );
		
		m_vertexData->SetStream(vertexBuffer, 0 );

		//Setup index buffer
		m_indexBuffer = renderer.CreateIndexBuffer( Renderer::INDEX_16BIT, 
													 4, 
													 Renderer::USAGE_STATICWRITEONLY);

		//Fill the index buffer
		ScopedIndexBufferLock iLock = m_indexBuffer->LockAll ( Renderer::LOCK_NORMAL );

		if ( !iLock )
		{
			throw Core::RuntimeError ( "Couldn't lock index buffer!", 0, __FILE__, __FUNCTION__, __LINE__ );
		}
		
		UInt16* indexPointer = static_cast<UInt16*>(iLock.GetLockPointer());
		*indexPointer = 0;
		*(++indexPointer) = 1;
		*(++indexPointer) = 2;
		*(++indexPointer) = 3;
		iLock.Release();

		//Set up effect
		m_effect = effectManager.AcquireEffect( effectName );
	
 	}
	//End EffectDisplayer::EffectDisplayer


};
//end namespace EffectViewer



#endif
//#ifndef EFFECTDISPLAYER_H