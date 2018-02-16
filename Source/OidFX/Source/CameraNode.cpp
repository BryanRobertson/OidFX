//======================================================================================
//! @file         CameraNode.cpp
//! @brief        Scene graph node representing a camera
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 14 July 2005
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


#include "Core/Core.h"
#include "Core/InputSystem.h"
#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "Math/MatrixStack.h"
#include "Renderer/Renderer.h"
#include "OidFX/GameApplication.h"
#include "OidFX/Scene.h"
#include "OidFX/SceneNode.h"
#include "OidFX/CameraNode.h"



using namespace OidFX;



//=========================================================================
//! @function    CameraNode::CameraNode
//! @brief       Camera node constructor
//!              
//! @param       scene				[in] Reference to the scene
//!
//! @param       rendererHandedness [in] Handedness of the renderer
//!										 this will affect the matrix generated
//=========================================================================
CameraNode::CameraNode ( Scene& scene,
						Math::EHandedness rendererHandedness )
: 
	SceneNode(scene), 
	m_rendererHandedness(rendererHandedness),
	m_movementDeltaZ(0.0f),
	m_movementDeltaX(0.0f),
	m_rotationDeltaX(0.0f),
	m_rotationDeltaY(0.0f),
	m_rotationX(0.0f),
	m_rotationY(0.0f),
	m_maxRotationXInDegrees(80),
	m_camSensitivity( "cam_sensitivity", 0.0055f ),
	m_camMoveSpeed ( "cam_move", 500.0f ),
	m_camMaxRotation ( "cam_maxrotation", 0.8f ),
	m_fovY(0.0f),
	m_aspectRatio(0.0f),
	m_zNear(0.0f),
	m_zFar(0.0f)

{
	
	//Register this class as a window mouse and keyboard handler
	m_mouseConnection = scene.Application().GetInputSystem().RegisterMouseHandler(*this);
	m_keyboardConnection = scene.Application().GetInputSystem().RegisterKeyboardHandler(*this);

}
//End CameraNode::CameraNode


//=========================================================================
//! @function    CameraNode::LookAt
//! @brief       Sets the camera transform
//!              
//! @param       position [in] 
//! @param       up		  [in] 
//! @param       lookAt	  [in] 
//!              
//=========================================================================
void CameraNode::LookAt ( const Math::Vector3D& position, 
						  const Math::Vector3D& up, 
						  const Math::Vector3D& lookAt )
{
	
	m_position = position;

	m_viewVector = position - lookAt;
	m_viewVector.Normalise();

	m_up = up;

}
//End CameraNode::LookAt



//=========================================================================
//! @function    CameraNode::SetProjection
//! @brief       Set the projection matrix
//!              
//!              
//! @param       fovY			[in] Field of view in the y direction, in degrees
//! @param       aspectRatio	[in] Aspect ratio of screen
//! @param       zNear			[in] Near clipping plane
//! @param       zFar			[in] Far clipping plane
//!              
//=========================================================================
void CameraNode::SetProjection ( Math::Scalar fovY, 
								 Math::Scalar aspectRatio, 
								 Math::Scalar zNear, 
								 Math::Scalar zFar )
{

	m_fovY = fovY;
	m_aspectRatio = aspectRatio;
	m_zNear = zNear;
	m_zFar = zFar;

	if ( m_rendererHandedness == Math::LEFT_HANDED )
	{
		Math::Matrix4x4::CreatePerspectiveProjectionLH ( m_projMatrix, Math::DegreesToRadians(fovY),
														 aspectRatio, zNear, zFar );
	}
	else
	{
		Math::Matrix4x4::CreatePerspectiveProjectionRH ( m_projMatrix, Math::DegreesToRadians(fovY),
														 aspectRatio, zNear, zFar );
	}
}
//End CameraNode::SetProjection


//=========================================================================
//! @function    CameraNode::Update
//! @brief       Update the camera matrices
//!              
//! @param       toWorldStack			[in]
//! @param		 fromWorldStack			[in]
//! @param       timeElapsedInSeconds	[in]	
//!              
//=========================================================================
void CameraNode::Update ( Math::MatrixStack& toWorldStack, 
						  Math::MatrixStack& fromWorldStack, 
						  Float timeElapsedInSeconds )
{
	using Math::Quaternion;
	using Math::Matrix4x4;
	using Math::Vector3D;

	//Temporary view vector. The actual view vector is left unchanged
	//and we perform all required rotations every frame.
	//This allows us to perform sanity checks on the view vector,
	//so that it doesn't mess up when we rotate too much around the X axis
	Vector3D tempViewVector( m_viewVector );

	//Update the X and Y rotation, based on user input
	m_rotationX += m_rotationDeltaX * m_camSensitivity;
	m_rotationY += m_rotationDeltaY * m_camSensitivity;

	//Zero out the rotation delta, so that rotation from this frame doesn't affect
	//future frames
	m_rotationDeltaX = 0.0f;
	m_rotationDeltaY = 0.0f;

	//Make sure the X rotation is within a suitable range. Otherwise we can
	//get odd behaviour when the camera is looking straight up or down.
	//
	//Since we're just going for a simple first person camera, we don't need
	//to fix this problem. However, if we're going for a flightsim style camera,
	//we'll need to fix this problem
	if ( m_rotationX > Math::DegreesToRadians(m_maxRotationXInDegrees) )
	{
		m_rotationX = Math::DegreesToRadians( m_maxRotationXInDegrees);
	}

	if ( m_rotationX < -Math::DegreesToRadians(m_maxRotationXInDegrees) )
	{
		m_rotationX = Math::DegreesToRadians( -m_maxRotationXInDegrees);
	}

	//First rotate our temporary view vector around the y axis
	Quaternion rotation ( Vector3D::YAxis, m_rotationY );
	Quaternion view		( 0.0f, tempViewVector.X(), tempViewVector.Y(), tempViewVector.Z() );
	Quaternion result	( Quaternion::TripleProduct ( rotation, view, rotation.Conjugate() ) );

	//Set the temporary view vector to the result
	tempViewVector.Set( result.X(), result.Y(), result.Z() );
	tempViewVector.Normalise();


	//Now rotate our temporary view vector around the x axis

	//First we need to get the X axis vector for the camera
	Vector3D right;
	Vector3D::CrossProduct( tempViewVector, m_up, right );
	right.Normalise();

	//Now rotate around the camera's x axis
	rotation = Quaternion( right, -m_rotationX );
	view	 = Quaternion( 0.0f, tempViewVector.X(), tempViewVector.Y(), tempViewVector.Z() );
	result   = Quaternion::TripleProduct ( rotation, view, rotation.Conjugate() );

	//Set the temporary view vector to the result
	tempViewVector.Set( result.X(), result.Y(), result.Z() );
	tempViewVector.Normalise();

	//Now that we've calculated our new view vector, we can use it to translate the 
	//camera along its Z and X axis, depending on user input

	//Move the position vector, based on keyboard input
	m_position += tempViewVector * m_movementDeltaZ * (m_camMoveSpeed * timeElapsedInSeconds);

	//Deal with movement along the X axis if any
	if ( m_movementDeltaX != 0.0f )
	{
		//Get the cam right vector, and use it to translate the position
		Vector3D right;
		Vector3D::CrossProduct( tempViewVector, m_up, right );

		right.Normalise();
		m_position += right * m_movementDeltaX * (m_camMoveSpeed * timeElapsedInSeconds);
	}

	//First we set the fromWorld matrix, which will become our view matrix

	//Reset the fromWorld matrix
	m_objectFromWorld.Identity();

	if ( m_rendererHandedness = Math::LEFT_HANDED )
	{
		Matrix4x4::CreateUVNCameraFromViewVectorLH  ( m_viewMatrix, m_position, tempViewVector, m_up );
		m_objectFromWorld = m_viewMatrix;

		//Flip the third column of the matrix, because the view matrix compensates
		//for the left handed renderer
		m_objectFromWorld(2,0) = -m_objectFromWorld(2,0);
		m_objectFromWorld(2,1) = -m_objectFromWorld(2,1);
		m_objectFromWorld(2,2) = -m_objectFromWorld(2,2);
		m_objectFromWorld(2,3) = -m_objectFromWorld(2,3);
	}
	else
	{
		Matrix4x4::CreateUVNCameraFromViewVectorRH  ( m_viewMatrix, m_position, tempViewVector, m_up );
	}

	//Set the objectToWorld matrix
	if ( !m_objectToWorld.Invert() )
	{
		debug_assert ( false, "Couldn't invert matrix!" );
	}

	//Call the base class update method to propagate the call to children,
	SceneNode::Update ( toWorldStack, fromWorldStack, timeElapsedInSeconds );

	//Multiply the concatenated object from world matrix with the view matrix
	//so that the camera can act properly as a child node
	m_viewMatrix = m_concatObjectFromWorld * m_viewMatrix;

	//Update the view frustum
	UpdateFrustum();

	//Set the world space position
	m_worldSpacePosition = m_position * m_concatObjectToWorld;

}
//End CameraNode::Update



//=========================================================================
//! @function    CameraNode::UpdateFrustum
//! @brief       Updates the cameras view frustum
//!              
//!              
//=========================================================================
void CameraNode::UpdateFrustum ( )
{
	m_frustum = Math::Frustum ( m_viewMatrix * m_projMatrix, true );
	/*
	using Math::Plane3D;
	using Math::Scalar;

	const Scalar& a = m_aspectRatio;
	const Scalar& n = m_zNear;
	const Scalar& f = m_zFar;
	const Scalar  e = 1.0 / ( Math::Tan( m_fovY / 2.0 ) );

	const Scalar sqrtESquaredPlusOne = Math::Sqrt( (e * e) + 1 );
	const Scalar sqrtESquaredPlusASquared = Math::Sqrt( (e * e) + (a * a) );

	Plane3D nearPlane ( 0.0f, 0.0f, -1.0f, n, true );
	Plane3D farPlane  ( 0.0f, 0.0f, 1.0f, -f, true );

	Plane3D leftPlane ( e / sqrtESquaredPlusOne, 0.0f, -(1.0f / sqrtESquaredPlusOne), 0.0f, true );
	Plane3D rightPlane( -(e / sqrtESquaredPlusOne), 0.0f, -(1.0f / sqrtESquaredPlusOne), 0.0f, true );

	Plane3D bottomPlane ( 0.0f, e / sqrtESquaredPlusASquared, -(a / sqrtESquaredPlusASquared), 0.0f, true );
	Plane3D topPlane	 ( 0.0f, -(e / sqrtESquaredPlusASquared), -(a / sqrtESquaredPlusASquared), 0.0f, true );

	nearPlane *= m_viewMatrix;
	farPlane  *= m_viewMatrix;
	leftPlane *= m_viewMatrix;
	rightPlane *= m_viewMatrix;
	bottomPlane *= m_viewMatrix;
	topPlane *= m_viewMatrix;

	m_frustum = Math::Frustum ( nearPlane, farPlane, leftPlane, rightPlane, topPlane, bottomPlane );
*/
}
//End CameraNode::UpdateFrustum



//=========================================================================
//! @function    CameraNode::FillVisibleObjectList
//! @brief       Add child nodes to the visible object list
//!				 we might add the camera to this later, so we can draw the frustum
//!				 for debugging purposes
//!              
//! @param       visibleObjectList [in]
//! @param		 camera			   [in]
//!              
//=========================================================================
void CameraNode::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const CameraNode& camera )
{
	SceneNode::FillVisibleObjectList ( visibleObjectList, camera );
}
//End CameraNode::FillVisibleObjectList


//=========================================================================
//! @function    CameraNode::QueueForRendering
//! @brief       Doesn't do anything special at the moment, but might be used
//!				 in future if we decide to render a debug frustum display
//=========================================================================
void CameraNode::QueueForRendering ( Renderer::RenderQueue& queue )
{
	//Can't render a camera, but might use this for debug later
}
//End CameraNode::QueueForRendering



//=========================================================================
//! @function    CameraNode::Render
//! @brief       Doesn't do anything special at the moment, but might be used
//!				 in future if we decide to render a debug frustum display
//=========================================================================
void CameraNode::Render ( Renderer::IRenderer& renderer )
{
	//Can't render a camera, but might use this for debug
}
//End CameraNode::Render



//=========================================================================
//! @function    CameraNode::OnMouseMove
//! @brief       Called when the mouse is moved
//!              
//! @param       movementX [in]
//! @param       movementY [in]
//!              
//=========================================================================
void CameraNode::OnMouseMove ( Int movementX, Int movementY )
{
	m_rotationDeltaX = -static_cast<Float>(movementY); 
	m_rotationDeltaY = -static_cast<Float>(movementX); 
}
//End CameraNode::OnMouseMove



//=========================================================================
//! @function    CameraNode::OnKeyDown
//! @brief       
//!              
//! @param       keyCode 
//! @param       repeats 
//! @param       prevKeyState 
//!              
//! @return      
//! @throw       
//=========================================================================
void CameraNode::OnKeyDown ( UInt keyCode )
{
	switch ( keyCode )
	{
		case Core::KEY_W:
			m_movementDeltaZ -= 1.0f;
			return;

		case Core::KEY_S:
			m_movementDeltaZ += 1.0f;
			return;

		case Core::KEY_A:
			m_movementDeltaX += 1.0f;
			return;

		case Core::KEY_D:
			m_movementDeltaX -= 1.0f;
			return;
	}
}
//End CameraNode::OnKeyDown


//=========================================================================
//! @function    CameraNode::OnKeyUp
//! @brief       
//!              
//! @param       keyCode 
//=========================================================================
void CameraNode::OnKeyUp ( UInt keyCode )
{
	switch ( keyCode )
	{
		case Core::KEY_W:
			m_movementDeltaZ = 0.0f;
			return;

		case Core::KEY_S:
			m_movementDeltaZ = 0.0f;
			return;

		case Core::KEY_A:
			m_movementDeltaX = 0.0f;
			return;

		case Core::KEY_D:
			m_movementDeltaX = 0.0f;
			return;
	}
}
//End CameraNode::OnKeyUp
