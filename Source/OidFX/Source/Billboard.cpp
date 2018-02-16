//======================================================================================
//! @file         Billboard.cpp
//! @brief        Class representing a billboarded sprite
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
#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "OidFX/Camera.h"
#include "OidFX/Billboard.h"
#include "OidFX/BillboardManager.h"



using namespace OidFX;



//=========================================================================
//! @function    Billboard::Billboard
//! @brief       Billboard constructor
//!              	
//! @param		 effect	 [in]	
//!              
//=========================================================================
Billboard::Billboard ( Renderer::HEffect& effect )
: m_effect(effect),
  m_scale(1.0f),
  m_rotation(0.0f),
  m_opacity(1.0f),
  m_scaleAnim(0.0f),
  m_rotateAnim(0.0f),
  m_opacityAnim(0.0f),
  m_wavePosition(0.0f)
{

}
//End Billboard::Billboard


//=========================================================================
//! @function    Billboard::Update
//! @brief       Update the billboard
//!              
//! @param       timeElapsedInSeconds [in]
//!              
//=========================================================================
void Billboard::Update ( Float timeElapsedInSeconds )
{
	UpdateTransforms( timeElapsedInSeconds );
}
//End Billboard::Update


//=========================================================================
//! @function    Billboard::UpdateTransforms
//! @brief       Update the scale, rotation, and opacity values from 
//!				 the wave transforms, and animation values
//!              
//! @param       timeElapsedInSeconds [in] Time elapsed since last update
//!              
//=========================================================================
void Billboard::UpdateTransforms ( Float timeElapsedInSeconds )
{
	m_wavePosition += timeElapsedInSeconds;

	for ( WaveXFormStore::const_iterator itr = m_transforms.begin(); 
		  itr < m_transforms.end(); 
		  ++itr )
	{
		Float waveValue = 0.0f;

		switch ( itr->waveType )
		{
			case WAVE_SINE:
				waveValue = (Math::Sin((itr->phase + m_wavePosition) 
										* itr->frequency * Math::TwoPi) * itr->amplitude) + itr->base;
				break;

			case WAVE_TRIANGLE:
				waveValue = (Math::TriangleWaveFunction((itr->phase + m_wavePosition) 
								* itr->frequency) * itr->amplitude) 
							 + itr->base;
				break;

			case WAVE_SQUARE:
				waveValue = (Math::SquareWaveFunction((itr->phase + m_wavePosition) 
								* itr->frequency) * itr->amplitude) 
							 + itr->base;
				break;

			case WAVE_SAWTOOTH:
				waveValue = (Math::SawToothFunction((itr->phase + m_wavePosition) 
								* itr->frequency) * itr->amplitude) 
							 + itr->base;
				break;

			case WAVE_INVERSE_SAWTOOTH:
				waveValue = itr->base + (itr->amplitude *
											(Math::SawToothFunction((itr->phase + m_wavePosition) 
											* itr->frequency) * itr->amplitude) );
				break;
		}

		switch ( itr->transformType )
		{
			case XFORM_ROTATE:
				SetRotation( waveValue );
				break;

			case XFORM_SCALE:
				SetScale( waveValue );
				break;

			case XFORM_OPACITY:
				SetOpacity( waveValue );
				break;
		}

	}

	//Now update from the static animations
	SetOpacity( GetOpacity() + (GetOpacityAnim() * timeElapsedInSeconds) );
	SetRotation( GetRotation() + (GetRotateAnim() * timeElapsedInSeconds) );
	SetScale(  GetScale() + (GetScaleAnim() * timeElapsedInSeconds) );

}
//End Billboard::UpdateWaveTransforms



//=========================================================================
//! @function    Billboard::RecalculateVertices
//! @brief       Recalulate the vertices to face a camera
//!              
//! @param       camera [in]
//!              
//=========================================================================
void Billboard::RecalculateVertices ( const Camera& camera )
{

	debug_assert ( (VERT_TOPRIGHT < 4), "VERT_TOPRIGHT out of range!" );
	debug_assert ( (VERT_TOPLEFT < 4), "VERT_TOPLEFT out of range!" );
	debug_assert ( (VERT_BOTTOMRIGHT < 4), "VERT_BOTTOMRIGHT out of range!" );
	debug_assert ( (VERT_BOTTOMLEFT < 4), "VERT_BOTTOMLEFT out of range!" );

	//First get the scaled vertices, around the origin
	m_vertices[VERT_TOPLEFT]		= -(camera.Right() - camera.Up()) * GetScale();
	m_vertices[VERT_TOPRIGHT]		=  (camera.Right() + camera.Up()) * GetScale();
	m_vertices[VERT_BOTTOMLEFT]		=  -(camera.Right() + camera.Up()) * GetScale();
	m_vertices[VERT_BOTTOMRIGHT]	= (camera.Right() - camera.Up()) * GetScale();

	//Rotate the scaled vertices around the billboard centre
	Math::Quaternion rotation( -camera.Forward(), GetRotation() );

	m_vertices[VERT_TOPLEFT]	 *= rotation;
	m_vertices[VERT_TOPRIGHT]	 *= rotation;
	m_vertices[VERT_BOTTOMLEFT]	 *= rotation;
	m_vertices[VERT_BOTTOMRIGHT] *= rotation;

	//Move the vertices to their final position
	m_vertices[VERT_TOPLEFT]	 += m_position;
	m_vertices[VERT_TOPRIGHT]	 += m_position;
	m_vertices[VERT_BOTTOMLEFT]	 += m_position;
	m_vertices[VERT_BOTTOMRIGHT] += m_position;

}
//End Billboard::RecalculateVertices