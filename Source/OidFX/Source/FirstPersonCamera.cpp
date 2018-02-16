//======================================================================================
//! @file         FirstPersonCamera.cpp
//! @brief        Class representing a first person camera
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 31 August 2005
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
#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4x4.h"
#include "OidFX/FirstPersonCamera.h"



using namespace OidFX;



//=========================================================================
//! @function    FirstPersonCamera::FirstPersonCamera
//! @brief       FirstPersonCamera constructor
//!              
//! @param       scene 
//! @param       rendererHandedness 
//!              
//! @return      
//! @throw       
//=========================================================================
FirstPersonCamera::FirstPersonCamera ( Scene& scene, Math::EHandedness rendererHandedness )
: Camera(scene, rendererHandedness )
{
	
}
//End FirstPersonCamera::FirstPersonCamera



//=========================================================================
//! @function    FirstPersonCamera::Update
//! @brief       Update the camera
//!              
//! @param       timeElapsedInSeconds [in]
//!              
//! @return      
//! @throw       
//=========================================================================
void FirstPersonCamera::Update ( Float timeElapsedInSeconds )
{

	using Math::Vector3D;
	using Math::Matrix4x4;
	using Math::Quaternion;

	//Update camera rotation
	m_orientation = Quaternion ( Math::DegreesToRadians(m_roll), 
								 Math::DegreesToRadians(m_yaw),
								 Math::DegreesToRadians(m_pitch) );

	m_yaw += m_yawDelta;
	m_pitch += m_pitchDelta;
	m_roll += m_rollDelta;

	if ( (m_pitch >= m_camMaxPitch) )
	{
		m_pitch = m_camMaxPitch;
	}

	if ( (m_pitch <= -m_camMaxPitch) )
	{
		m_pitch = -m_camMaxPitch;
	}

	Quaternion m_orientationDelta ( Math::DegreesToRadians(m_rollDelta), 
									Math::DegreesToRadians(m_yawDelta),
									Math::DegreesToRadians(m_pitchDelta) );
	m_orientation *= m_orientationDelta; 

	//Update the up, forward, and right vectors
	m_forward = Vector3D::ZAxis * m_orientation;
	m_up	  = Vector3D::YAxis * m_orientation;
	m_right   = Vector3D::XAxis * m_orientation;

	//Normalise the new vectors
	m_forward.Normalise();
	m_up.Normalise();
	m_right.Normalise();

	static Core::ConsoleFloat cam_speedfactor ( "cam_speedfactor", 0.5f );

	//Update the camera position
	m_position += m_forward * (cam_speedfactor * m_zDelta * timeElapsedInSeconds);
	m_position += m_right	* (cam_speedfactor * m_xDelta * timeElapsedInSeconds);
	m_position += m_up		* (cam_speedfactor * m_yDelta * timeElapsedInSeconds);

	//Update the view matrix
	m_viewMatrix.Identity();
	m_viewMatrix.Translate( -m_position );
	m_viewMatrix *= Matrix4x4(-m_orientation);

	//
	Camera::Update( timeElapsedInSeconds );

}
//End FirstPersonCamera::Update