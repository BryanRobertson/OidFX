//======================================================================================
//! @file         Camera.cpp
//! @brief        Base class for a camera
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
#include "Core/InputSystem.h"
#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/Frustum.h"
#include "Math/Matrix4x4.h"
#include "Math/Quaternion.h"
#include "OidFX/Camera.h"
#include "OidFX/GameApplication.h"
#include "OidFX/Scene.h"
#include "OidFX/Camera.h"
#include "OidFX/Camera.h"
#include "OidFX/EntityNode.h"



using namespace OidFX;



//=========================================================================
//! @function    Camera::Camera
//! @brief       Camera constructor
//!              
//!              
//! @param       scene				[in] Reference to the scene
//! @param       rendererHandedness [in] Handedness of the renderer
//!              
//=========================================================================
Camera::Camera ( Scene& scene, Math::EHandedness rendererHandedness )
:	m_scene(scene),
	m_rendererHandedness(rendererHandedness),
	m_fovY(90.0f),
	m_aspectRatio( 640.0f / 480.0f ),
	m_forward( Math::Vector3D::ZAxis ),
	m_up( Math::Vector3D::YAxis ),
	m_right( Math::Vector3D::XAxis ),
	m_lookAt( 0.0f, 0.0f, 1.0f ),
	m_orientation( 0.0f, 0.0f, 0.0f),
	m_zNear( 100.0f  ),
	m_zFar ( 1000.0f ),
	m_yaw  ( 0.0f ),
	m_pitch ( 0.0f ),
	m_roll  ( 0.0f ),
	m_yawDelta ( 0.0f ),
	m_pitchDelta ( 0.0f ),
	m_rollDelta ( 0.0f ),
	m_xDelta ( 0.0f ),
	m_yDelta ( 0.0f ),
	m_zDelta ( 0.0f ),
	m_camSensitivity( "cam_sensitivity", 1.0f ),
	m_camMoveSpeed	( "cam_movespeed", 700.0f ),
	m_camMaxPitch	( "cam_maxpitch", 90.0f ),
	m_offset ( 0.0f, 200.0f, 250.0f ),
	m_firstUpdate(true)

{
	
	//Register this object as a window mouse and keyboard handler
	m_mouseConnection = scene.Application().GetInputSystem().RegisterMouseHandler(*this);
	m_keyboardConnection = scene.Application().GetInputSystem().RegisterKeyboardHandler(*this);
}
//End Camera::Camera 



//=========================================================================
//! @function    Camera::Update
//! @brief       Update the camera
//!              
//! @param       timeElapsedInSeconds [in]
//!              
//=========================================================================
void Camera::Update ( Float timeElapsedInSeconds )
{
	using Math::Vector3D;
	using Math::Matrix4x4;
	using Math::Quaternion;

	//Only track the entity if it exists, and it isn't dead
	if ( m_entity )
	{

		//Check to see whether this is the first time the camera has been updated or not
		//if it is, then set the camera to its ideal position behind the
		//entity, so that it doesn't interpolate between its starting position,
		//and its position behind the entity
		if ( m_firstUpdate )
		{
			SetToIdealPosition();
			m_firstUpdate = false;
		}

		//Store the last position of the camera
		Vector3D oldPosition = m_position; 

		//Set the camera into the ideal position to follow the entity exactly
		SetToIdealPosition();

		//Create a parametric line from the camera's previous position,
		//to its current position, so we can interpolate between its new position and its old position
		Math::ParametricLine3D line( oldPosition, m_position );

		//Make the camera follow the entity more loosely, by 
		//interpolating between its ideal position for this frame, if it were following the entity perfectly
		//and its position in the previous frame.
		static Core::ConsoleFloat cam_interpolatefactor ( "cam_interpolatefactor", 0.25f );

		line.PointOnLine ( cam_interpolatefactor, m_position );
	
		//Create the view matrix

		if ( Math::LEFT_HANDED == m_rendererHandedness )
		{

			Matrix4x4::CreateUVNCameraMatrixLH ( m_viewMatrix,
												m_position,
												Vector3D::YAxis,
												m_lookAt );

		}
		else
		{
			Matrix4x4::CreateUVNCameraMatrixRH ( m_viewMatrix,
												m_position,
												Vector3D::YAxis,
												m_lookAt );
		}


		//Update the projection and frustum
		UpdateProjection();
		UpdateFrustum();

		m_forward = m_lookAt - m_position;
		m_forward.Normalise();

		Vector3D::CrossProduct( Vector3D::YAxis, m_forward, m_right );
		m_right.Normalise();

		Vector3D::CrossProduct ( m_forward, m_right, m_up );
		m_up.Normalise();

		m_xDelta = 0.0f;
		m_yDelta = 0.0f;
		m_zDelta = 0.0f;

		m_yawDelta = 0.0f;
		m_pitchDelta = 0.0f;
		m_rollDelta = 0.0f;

	}

}
//End Camera::Update



//=========================================================================
//! @function    Camera::SetToIdealPosition
//! @brief       Sets the camera position and look at
//!              to the ideal position for a camera following an entity exactly
//!              
//!              
//=========================================================================
void Camera::SetToIdealPosition ( )
{

	using Math::Vector3D;

	debug_assert ( m_entity, "SetToIdealPosition called when entity is null!" );

	//Get the entity position
	Vector3D entityPos = m_entity->GetWorldSpacePosition();
	
	//Get the basis vectors of the entity
	Vector3D entityForward = m_entity->Forward();
	entityForward.Normalise();

	Vector3D entityUp = m_entity->Up();
	entityUp.Normalise();

	Vector3D entityRight = m_entity->Right();
	entityRight.Normalise();

	//Set the camera behind the entity
	m_position = entityPos;
	m_position += (m_entity->Forward() * m_offset.Z());
	m_position += (m_entity->Up() * m_offset.Y());
	m_position += (m_entity->Right() * m_offset.X());

	//Set the look at position
	m_lookAt = entityPos;

}
//End Camera::SetToIdealPosition



//=========================================================================
//! @function    Camera::OnMouseMove
//! @brief       Camera handle for mouse move events
//!              
//! @param       movementX [in] 
//! @param       movementY [in] 
//!              
//=========================================================================
void Camera::OnMouseMove ( Int movementX, Int movementY )
{

}
//End Camera::OnMouseMove



//=========================================================================
//! @function    Camera::OnMouseButtonDown
//! @brief       Camera handler for a mouse button being pressed
//!              
//!              
//! @param       buttonIndex [in]
//!              
//=========================================================================
void Camera::OnMouseButtonDown ( UInt buttonIndex )
{
	//Does nothing
}
//End Camera::OnMouseButtonDown



//=========================================================================
//! @function    Camera::OnMouseButtonUp
//! @brief       Camera handle for a mouse button being released
//!              
//!              
//! @param       buttonIndex [in]
//!              
//=========================================================================
void Camera::OnMouseButtonUp ( UInt buttonIndex )
{
	//Does nothing
}
//End OnMouseButtonUp



//=========================================================================
//! @function    Camera::OnMouseScroll
//! @brief       Camera reaction to mouse scroll
//!              
//! @param       scroll [in]
//!              
//=========================================================================
void Camera::OnMouseScroll ( Int scroll )
{

}
//End CameraOnMouseScroll



//=========================================================================
//! @function    Camera::OnKeyDown
//! @brief       Camera reaction to a key being pressed
//!              
//! @param       keyCode [in]
//!              
//=========================================================================
void Camera::OnKeyDown ( UInt keyCode )
{
	Core::ConsoleFloat cam_movespeed ( "cam_movespeed", 1.0f );

	switch ( keyCode )
	{
		case Core::KEY_PAGEDOWN:
		{
			Math::Vector3D offsetNormalised = m_offset;
			offsetNormalised.Normalise();

			m_offset -= offsetNormalised * 10.0f;
			return;
		}

		case Core::KEY_PAGEUP:
		{
			Math::Vector3D offsetNormalised = m_offset;
			offsetNormalised.Normalise();

			m_offset += offsetNormalised * 10.0f;
			return;
		}
	}

}
//End Camera::OnKeyDown



//=========================================================================
//! @function    Camera::OnKeyUp
//! @brief       Camera reaction to a key being released
//!              
//! @param       keyCode [in]
//!              
//=========================================================================
void Camera::OnKeyUp ( UInt keyCode )
{
}
//End Camera::OnKeyUp



//=========================================================================
//! @function    Camera::OnChar
//! @brief       Camera reaction to a character being typed on the keyboard
//!              
//! @param       charValue 
//! @param       repeats 
//! @param       prevKeyState 
//!             
//=========================================================================
void Camera::OnChar ( Char charValue, UInt repeats, bool prevKeyState )
{
	//Does nothing!
}
//End Camera::OnChar


//=========================================================================
//! @function    Camera::UpdateProjection
//! @brief       Update the projection matrix from the stored parameters
//!              
//=========================================================================
void Camera::UpdateProjection ( )
{
	if ( m_rendererHandedness == Math::LEFT_HANDED )
	{
		Math::Matrix4x4::CreatePerspectiveProjectionLH ( m_projMatrix, 
														 m_fovY, 
														 m_aspectRatio, 
														 m_zNear, 
														 m_zFar );
	}
	else
	{
		Math::Matrix4x4::CreatePerspectiveProjectionRH ( m_projMatrix, 
														 m_fovY, 
														 m_aspectRatio, 
														 m_zNear, 
														 m_zFar );
	}
}
//End Camera::UpdateProjection



//=========================================================================
//! @function    Camera::UpdateFrustum
//! @brief       Update the view frustum from the view and projection matrix
//!              
//=========================================================================
void Camera::UpdateFrustum ( )
{
	m_viewFrustum = Math::Frustum ( m_viewMatrix * m_projMatrix, true );
}
//End Camera::UpdateFrustum