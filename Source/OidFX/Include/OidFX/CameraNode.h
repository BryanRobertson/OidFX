//======================================================================================
//! @file         CameraNode.h
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

#ifndef OIDFX_CAMERANODE_H
#define OIDFX_CAMERANODE_H


#include "Core/KeyboardSensitive.h"
#include "Core/MouseSensitive.h"
#include "Math/Frustum.h"
#include "OidFX/SceneNode.h"




//=========================================================================
// Forward declaration
//=========================================================================
namespace Math		{ class Vector3D; enum EHandedness;	}
namespace Renderer	{ class IRenderer;					}



//namespace OidFX
namespace OidFX
{

	//!@class	CameraNode
	//!@brief	Scene graph node representing a camera
	class CameraNode : public SceneNode, 
					   public Core::IMouseSensitive,
					   public Core::IKeyboardSensitive
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			CameraNode ( Scene& scene, Math::EHandedness rendererHandedness );


            //=========================================================================
            // Public methods
            //=========================================================================
			void LookAt ( const Math::Vector3D& position, const Math::Vector3D& up, const Math::Vector3D& lookAt );
			void SetProjection ( Math::Scalar fovY, Math::Scalar aspectRatio, Math::Scalar zNear, Math::Scalar zFar );

			const Math::Matrix4x4& ViewMatrix() const		{ return m_viewMatrix;	}
			const Math::Matrix4x4& ProjMatrix() const		{ return m_projMatrix;	}

			const Math::Frustum& ViewFrustum() const		{ return m_frustum;		}

			const Math::Vector3D Position() const			{ return m_position;	}
			const Math::Vector3D WorldSpacePosition() const	{ return m_worldSpacePosition; }

			//Update
			virtual void Update ( Math::MatrixStack& toWorldStack, Math::MatrixStack& fromWorldStack, Float timeElapsedInSeconds );
			virtual void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const CameraNode& camera );


            //=========================================================================
            // IMouseSensitive implementation
            //=========================================================================
			void OnMouseMove		( Int movementX, Int movementY );
	
			//Not implementing these at the moment
			void OnMouseButtonDown  ( UInt buttonIndex )		{} 
			void OnMouseButtonUp	( UInt buttonIndex )		{}
			void OnMouseScroll		( Int scroll )				{}


            //=========================================================================
            // IKeyboardSensitive implementation
            //=========================================================================
			void OnKeyDown ( UInt keyCode );
			void OnKeyUp   ( UInt keyCode );

			//Not implementing this at the moment
			void OnChar	   ( Char charValue, UInt repeats, bool prevKeyState ) {}

            //=========================================================================
            // IRenderable implementation
            //=========================================================================
			virtual void QueueForRendering ( Renderer::RenderQueue& queue );	
			virtual void Render ( Renderer::IRenderer& renderer );			

		private:


            //=========================================================================
            // Private methods
            //=========================================================================
			void UpdateFrustum ( );

            //=========================================================================
            // Private data
            //=========================================================================
			Float			  m_movementDeltaZ;
			Float			  m_movementDeltaX;
			Float			  m_rotationX;
			Float			  m_rotationY;

			Float			  m_rotationDeltaX;
			Float			  m_rotationDeltaY;

			Float			  m_maxRotationXInDegrees;

			Core::ConsoleFloat m_camSensitivity;
			Core::ConsoleFloat m_camMoveSpeed;
			Core::ConsoleFloat m_camMaxRotation;

			Core::EventConnection m_mouseConnection;
			Core::EventConnection m_keyboardConnection;

			Math::Matrix4x4	  m_viewMatrix;
			Math::Matrix4x4	  m_projMatrix;
			Math::EHandedness m_rendererHandedness;
			Math::Vector3D	  m_position;
			Math::Vector3D	  m_worldSpacePosition;
			Math::Vector3D	  m_up;
			Math::Vector3D	  m_viewVector;

			Math::Frustum	  m_frustum;

			//Properties of the projection matrix
			Float			  m_fovY;
			Float			  m_aspectRatio; 
			Float			  m_zNear;
			Float			  m_zFar;
	};
	//end class CameraNode

};
//end namespace OidFX


#endif
//#ifndef OIDFX_CAMERANODE_H
