//======================================================================================
//! @file         Camera.h
//! @brief        Class encapsulating a camera
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

#ifndef OIDFX_CAMERA_H
#define OIDFX_CAMERA_H


#include "Math/Quaternion.h"
#include "Math/Frustum.h"
#include "Core/MouseSensitive.h"
#include "Core/KeyboardSensitive.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace Math	{	class Vector3D;					}
namespace OidFX	{	class Scene; class EntityNode;	}



//namespace OidFX
namespace OidFX
{


	//!@class	Camera
	//!@brief	Base class for a camera
	class Camera : public Core::IMouseSensitive,
				   public Core::IKeyboardSensitive
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			Camera ( Scene& scene, Math::EHandedness rendererHandedness );


            //=========================================================================
            // Public methods
            //=========================================================================
			virtual void Update ( Float timeElapsedInSeconds );

			inline void SetTargetEntity ( boost::shared_ptr<EntityNode> entity );
			inline void SetOffset ( const Math::Vector3D& offset );
			void SetToIdealPosition (  );

			//Projection
			inline void SetProjection  ( Math::Scalar fovY, Math::Scalar aspectRatio, Math::Scalar zNear, Math::Scalar zFar ) throw();
			inline void SetAspectRatio ( Float aspectRatio ) throw();
			inline void SetFOV		   ( Float fov ) throw();
			inline void SetZNear	   ( Float zNear ) throw();
			inline void SetZFar		   ( Float zFar ) throw();

			//
			inline void SetPosition ( Math::Vector3D& position ) throw();
			inline void LookAt		( Math::Vector3D& lookAt   ) throw();
			inline void LookAt		( Math::Vector3D& lookAt, const Math::Vector3D& up ) throw();

			//Accessors
			inline const Math::Frustum&	   ViewFrustum ( ) const;
			inline const Math::Matrix4x4&  ViewMatrix ( ) const;
			inline const Math::Matrix4x4&  ProjectionMatrix ( ) const;
			inline const Math::Vector3D&   GetPosition	  ( ) const;
			inline const Math::Quaternion& GetOrientation ( ) const;

			inline Float FOV() const throw();
			inline Float AspectRatio() const throw();
			inline Float ZNear() const throw();
			inline Float ZFar() const throw();

			inline const Math::Vector3D& Forward() const throw();
			inline const Math::Vector3D& Up() const throw();
			inline const Math::Vector3D& Right() const throw();

			//=========================================================================
            // IMouseSensitive implementation
            //=========================================================================
			virtual void OnMouseMove		( Int movementX, Int movementY );
			virtual void OnMouseButtonDown  ( UInt buttonIndex );	
			virtual void OnMouseButtonUp	( UInt buttonIndex );	
			virtual void OnMouseScroll		( Int scroll );			


            //=========================================================================
            // IKeyboardSensitive implementation
            //=========================================================================
			virtual void OnKeyDown ( UInt keyCode );
			virtual void OnKeyUp   ( UInt keyCode );
			virtual void OnChar	   ( Char charValue, UInt repeats, bool prevKeyState );

		protected:

            //=========================================================================
            // Protected methods
            //=========================================================================
			void UpdateProjection ( ) throw();
			void UpdateFrustum ( ) throw();


            //=========================================================================
            // Protected variables
            //=========================================================================
			Scene&				m_scene;

			Math::Vector3D		m_position;
			Math::Vector3D		m_lookAt;
			Math::Quaternion	m_orientation;

			Math::Matrix4x4		m_viewMatrix;
			Math::Matrix4x4		m_projMatrix;
			Math::Frustum		m_viewFrustum;
			Math::EHandedness	m_rendererHandedness;

			Math::Vector3D		m_right;
			Math::Vector3D		m_up;
			Math::Vector3D		m_forward;

			Float				m_fovY;
			Float				m_aspectRatio; 
			Float				m_zNear;
			Float				m_zFar;

			Float				m_yaw;
			Float				m_pitch;
			Float				m_roll;

			Float				m_yawDelta;
			Float				m_pitchDelta;
			Float				m_rollDelta;
			Float				m_xDelta;
			Float				m_yDelta;
			Float				m_zDelta;

			//Console variables
			Core::ConsoleFloat	m_camSensitivity;
			Core::ConsoleFloat	m_camMoveSpeed;
			Core::ConsoleFloat	m_camMaxPitch;

			//Input
			Core::EventConnection m_mouseConnection;
			Core::EventConnection m_keyboardConnection;

			boost::shared_ptr<EntityNode> m_entity;

			Math::Quaternion m_targetOrientation;
			Math::Vector3D	 m_offset;
			bool			 m_firstUpdate;

	};
	//End class Camera



	
    //=========================================================================
    //! @function    Camera::SetTargetEntity
    //! @brief       Set the entity that this camera targets
    //!              
    //! @param       entity [in]
    //!              
    //=========================================================================
	void Camera::SetTargetEntity ( boost::shared_ptr<EntityNode> entity )
	{
		m_entity = entity;
	}
	//End Camera::SetTargetEntity



    //=========================================================================
    //! @function    Camera::SetOffset
    //! @brief       Set the distance of the camera from the target entity
    //!              
    //! @param       offset [in]
    //!              
    //=========================================================================
	void Camera::SetOffset ( const Math::Vector3D& offset  )
	{
		m_offset = offset;
	}
	//End Camera::SetOffset



    //=========================================================================
    //! @function    Camera::SetProjection
    //! @brief       Set the projection matrix
    //!              
    //! @param       fovY			[in]	Field of view
    //! @param       aspectRatio	[in]	Aspect ratio of viewport
    //! @param       zNear			[in]	Distance from eye to near plane
    //! @param       zFar			[in]	Distance from eye to far plane
    //!              
    //=========================================================================
	void Camera::SetProjection ( Float fovY, Float aspectRatio, Float zNear, Float zFar )
	{
		m_fovY = fovY;
		m_aspectRatio = aspectRatio;
		m_zNear = zNear;
		m_zFar = zFar;
	}
	//End Camera::SetProjection



    //=========================================================================
    //! @function    Camera::SetAspectRatio
    //! @brief       Set the aspect ratio of the viewport
    //!              
    //! @param       aspectRatio [in] 
    //!              
    //=========================================================================
	void Camera::SetAspectRatio ( Float aspectRatio )
	{
		m_aspectRatio = aspectRatio;
	}
	//End Camera::SetAspectRatio



    //=========================================================================
    //! @function    Camera::SetFOV
    //! @brief       Set the field of view of the frustum
    //!              
    //! @param       fov [in]
    //!              
    //=========================================================================
	void Camera::SetFOV	( Float fov )
	{
		m_fovY = fov;
	}
	//End Camera::SetFOV



    //=========================================================================
    //! @function    Camera::SetZNear
    //! @brief       Set the distance from the eye to the near plane
    //!              
    //! @param       zNear [in] Distance to the near plane 
    //!              
    //=========================================================================
	void Camera::SetZNear ( Float zNear )
	{
		m_zNear = zNear;
	}
	//End Camera::SetZNear



    //=========================================================================
    //! @function    Camera::SetZFar
    //! @brief       Set the distance to the far plane
    //!              
    //! @param       zFar [in] Distance to the far plane
    //!              
    //=========================================================================
	void Camera::SetZFar ( Float zFar )
	{
		m_zFar = zFar;
	}
	//End Camera::SetZFar



    //=========================================================================
    //! @function    Camera::SetPosition
    //! @brief       Set the position of the camera
    //!              
    //! @param       position [in] 
    //!              
    //=========================================================================
	void Camera::SetPosition ( Math::Vector3D& position )
	{
		m_position = position;
	}
	//End Camera::SetPosition



    //=========================================================================
    //! @function    Camera::LookAt
    //! @brief       Set the location the camera is looking at
	//!				 using the existing up vector to orient the camera
    //!              
    //! @param       lookAt [in]
    //!              
    //=========================================================================
	void Camera::LookAt ( Math::Vector3D& lookAt )
	{
		using Math::Vector3D;
		using Math::Quaternion;

		m_lookAt = lookAt;

		//Recalculate the basis vectors
		m_forward = m_lookAt - m_position;
		m_forward.Normalise();

		//Get the right vector
		Vector3D::CrossProduct( m_lookAt, m_up, m_right );
		m_right.Normalise();

		//Recalculate the true up vector from the right and forward vectors
		Vector3D::CrossProduct ( m_forward, m_right, m_up );
		m_up.Normalise();

		//Calculate the yaw, pitch and roll
		m_roll  = Vector3D::AngleBetween( m_right, Vector3D::XAxis );
		m_pitch = Vector3D::AngleBetween( m_up, Vector3D::YAxis );
		m_yaw	= Vector3D::AngleBetween( m_forward, Vector3D::ZAxis );

		m_orientation = Math::Quaternion( m_roll, m_pitch, m_yaw );

	}
	//End Camera::LookAt


    //=========================================================================
    //! @function    Camera::LookAt
    //! @brief       Set the camera to look at a location, using the
    //!              provided up vector to orient the camera
	//!
    //! @param       lookAt [in]
    //! @param       up		[in]
    //!              
    //=========================================================================
	void Camera::LookAt ( Math::Vector3D& lookAt, const Math::Vector3D& up )
	{
		using Math::Vector3D;

		m_lookAt = lookAt;
		m_up = up;
		m_up.Normalise();

		LookAt(lookAt);
	}
	//End Camera::LookAt



    //=========================================================================
    //! @function    Camera::ViewFrustum
    //! @brief       Get the view frustum
    //!              
    //! @return      The view frustum
    //=========================================================================
	const Math::Frustum& Camera::ViewFrustum ( ) const
	{
		return m_viewFrustum;
	}
	//End Camera::ViewFrustum



    //=========================================================================
    //! @function    Camera::ViewMatrix
    //! @brief       Get the camera view matrix
	//!
    //! @return      The camera view matrix
    //=========================================================================
	const Math::Matrix4x4& Camera::ViewMatrix ( ) const
	{
		return m_viewMatrix;
	}
	//End Camera::ViewMatrix


    //=========================================================================
    //! @function    Camera::ProjectionMatrix
    //! @brief       Get the camera projection matrix
    //!              
    //! @return      The camera projection matrix
    //=========================================================================
	const Math::Matrix4x4& Camera::ProjectionMatrix ( ) const
	{
		return m_projMatrix;
	}
	//End Camera::ProjectionMatrix


    //=========================================================================
    //! @function    Camera::GetPosition
    //! @brief       Get the position of the camera
    //!              
    //=========================================================================
	const Math::Vector3D& Camera::GetPosition ( ) const
	{
		return m_position;
	}
	//End Camera::GetPosition



    //=========================================================================
    //! @function    Camera::GetOrientation
    //! @brief       Get the orientation of the camera
    //!              
    //! @return      The orientation of the camera
    //=========================================================================
	const Math::Quaternion& Camera::GetOrientation ( ) const
	{
		return m_orientation;
	}
	//End Camera::GetOrientation



    //=========================================================================
    //! @function    Camera::FOV
    //! @brief       Return the field of view of the camera
	//!
    //! @return		 The field of view of the camera
    //=========================================================================
	Float Camera::FOV() const
	{
		return m_fovY;
	}
	//End Camera::FOV


    //=========================================================================
    //! @function    Camera::AspectRatio
    //! @brief       Return the viewport aspect ratio
    //!              
    //! @return      The viewport aspect ratio
    //=========================================================================
	Float Camera::AspectRatio() const
	{
		return m_aspectRatio;
	}
	//End Camera::AspectRatio


    //=========================================================================
    //! @function    Camera::ZNear
    //! @brief       Return the distance from the eye to the near plane
	//!
    //! @return      The distance from the eye to the near plane
    //=========================================================================
	Float Camera::ZNear() const
	{
		return m_zNear;
	}
	//End Camera::ZNear


    //=========================================================================
    //! @function    Camera::ZFar
    //! @brief       Return the distance from the eye to the far plane
    //!              
    //! @return      The distance from the eye to the far plane
    //=========================================================================
	Float Camera::ZFar() const
	{
		return m_zFar;
	}
	//End Camera::ZFar


    //=========================================================================
    //! @function    Camera::Forward
    //! @brief       Get the forward vector of the camera (normalised)
    //!              
    //! @return      A vector representing the camera's local Z axis
    //=========================================================================
	const Math::Vector3D& Camera::Forward() const
	{
		return m_forward;
	}
	//End Camera::Forward



    //=========================================================================
    //! @function    Camera::Up
    //! @brief       Get the up vector of the camera ( normalised )
    //!              
    //! @return      A vector representing the camera's local Y axis
    //=========================================================================
	const Math::Vector3D& Camera::Up() const throw()
	{
		return m_up;
	}
	//End Camera::Up


    //=========================================================================
    //! @function    Camera::Right
    //! @brief       Get the right vector of the camera ( normalised )
    //!              
    //! @return      A vector representing the camera's local X axis
    //=========================================================================
	const Math::Vector3D& Camera::Right() const throw()
	{
		return m_right;
	}
	//End Camera::Right



}
//end namespace OidFX


#endif
//#ifndef OIDFX_CAMERA_H
