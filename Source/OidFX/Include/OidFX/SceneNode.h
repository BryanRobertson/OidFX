//======================================================================================
//! @file         SceneNode.h
//! @brief        Class representing a basic node in the scene graph
//!				  with its own transformation matrix.  
//!
//!				  Note that I'm not happy with the implementation of the scene graph, and this
//!				  is all going to be scrapped later. The only reason I'm not scrapping it now,
//!				  is due to the time constraints I'm under. I just need to get something that works
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


#ifndef OIDFX_SCENENODE_H
#define OIDFX_SCENENODE_H


#include <list>
#include <boost/pool/pool_alloc.hpp>
#include "Math/Matrix4x4.h"
#include "Renderer/Renderable.h"
#include "OidFX/SceneQueryResult.h"


//=========================================================================
// Forward declaration
//=========================================================================
namespace Math	{ class MatrixStack; class ParametricLine3D; class BoundingSphere3D;	}
namespace OidFX { class VisibleObjectList; class Camera; class Scene; class EntityNode; class CollisionManager;  }


//namespace OidFX
namespace OidFX
{


    //=========================================================================
    // Types
    //=========================================================================

	//! Type of a scene node
	enum ENodeType
	{
		NODETYPE_WORLD,
		NODETYPE_SCENEPARTITION,
		NODETYPE_SKY,
		NODETYPE_TRANSFORM,
		NODETYPE_ENTITY,

		NODETYPE_COUNT
	};
	//End enum ENodeType


	//! Collision type to check
	enum ECollisionType
	{
		COLLISIONTYPE_SPHERE,
		COLLISIONTYPE_VELOCITYRAY
	};
	//End enum ECollisionType


	//! Interface types supported by SceneNode::QueryInterface
	enum ENodeInterfaceType
	{
		NODEINTERFACE_IENTITY
	};
	//End enum 


	//!@class	SceneNode
	//!@brief	Class representing a basic node in the scene graph
	//!
	//!			Note that I'm not happy with the implementation of the scene graph, and this
	//!			is all going to be scrapped later. The only reason I'm not scrapping it now,
	//!			is due to the time constraints I'm under. I just need to get something that works
	class SceneNode : public Renderer::IRenderable
	{
		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			SceneNode ( Scene& scene, 
						ENodeType nodeType = NODETYPE_TRANSFORM,
						const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
						const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );

			virtual ~SceneNode() {}


            //=========================================================================
            // Public types
            //=========================================================================
			typedef std::list<boost::shared_ptr<SceneNode>, 
							  boost::fast_pool_allocator<boost::shared_ptr<SceneNode> > > List;
			typedef List::iterator			iterator;
			typedef List::const_iterator	const_iterator;
		
			typedef std::bitset<NODETYPE_COUNT> NodeCollisionFlags;


            //=========================================================================
            // Public methods
            //=========================================================================
			void AddChild ( boost::shared_ptr<SceneNode> node );
			void RemoveChild ( UInt id );
			
			//Transformation
			void SetTransform ( const Math::Matrix4x4& toWorld );
			void SetTransform ( const Math::Matrix4x4& toWorld, const Math::Matrix4x4& fromWorld );

			void SetConcatTransform ( const Math::Matrix4x4& concatToWorld, const Math::Matrix4x4& concatFromWorld );

			void UpdateLODLevel ( const Camera& camera );

			inline const Math::Matrix4x4& ObjectToWorld () const		{ return m_objectToWorld;		  }
			inline const Math::Matrix4x4& ObjectFromWorld() const		{ return m_objectFromWorld;		  }

			inline const Math::Matrix4x4& ConcatObjectToWorld() const	{ return m_concatObjectToWorld;	  }
			inline const Math::Matrix4x4& ConcatObjectFromWorld() const	{ return m_concatObjectFromWorld; }

			inline Math::Vector3D Forward() const throw();
			inline Math::Vector3D Up() const throw();
			inline Math::Vector3D Right() const throw();

			inline Math::Vector3D GetWorldSpacePosition() const throw();

			UInt ID () const				{ return m_id;			}
			ENodeType NodeType() const		{ return m_nodeType;	}

			//Restore
			virtual void Restore( );

			//Update
			virtual void Update ( Math::MatrixStack& toWorldStack, 
								  Math::MatrixStack& fromWorldStack, 
								  Float timeElapsedInSeconds );

			virtual void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );
			
			//Collisions
			virtual bool CanCollideWith ( const EntityNode* entity ) const;
			virtual bool CollidesWith   ( EntityNode* entity,
										  ECollisionType collisionType,
										  Math::Vector3D& normal,
										  Float& depth );

			virtual void CheckCollisions ( EntityNode* entity, 
										   ECollisionType collisionType,
										   const NodeCollisionFlags& collisionFlags,
										   CollisionManager& collisionManager );

			virtual void QueryScene ( const Math::ParametricLine3D& ray, 
									  SceneQueryResult& result );

			virtual void QueryScene ( const Math::BoundingSphere3D& sphere,
									  EntityQueryResult& result );

			// HACK
			//
			//Query interface
			//
			//I'm rather dubious about using this technique. Once I get time, I'm
			//going to redesign the scene-graph, because this is just evil.
			virtual inline bool QueryInterface ( enum ENodeInterfaceType type, void** receiver );


            //=========================================================================
            // IRenderable implementation
            //=========================================================================
			virtual void QueueForRendering ( Renderer::RenderQueue& queue );
			virtual void Render ( Renderer::IRenderer& renderer );


			 //=========================================================================
            // Iterator methods
            //=========================================================================
			inline iterator				ChildrenBegin()			{ return m_children.begin();	}
			inline iterator				ChildrenEnd()			{ return m_children.end();		}
			inline const_iterator		ChildrenBegin()	const	{ return m_children.begin();	}
			inline const_iterator		ChildrenEnd()	const	{ return m_children.end();		}
			inline size_t				ChildrenCount() const	{ return m_children.size();		}
			

		protected:

            //=========================================================================
            // Private methods
            //=========================================================================
			void SetParent ( SceneNode* node );
			virtual void ConcatenateTransformFromParent ( );
			void PropagateTransformsToChildren( );


            //=========================================================================
            // Private data
            //=========================================================================

			SceneNode*	 m_parent;
			Scene&		 m_scene;
			List		 m_children;

			UInt		 m_lodLevel;

			Math::Matrix4x4  m_objectToWorld;
			Math::Matrix4x4	 m_objectFromWorld;
			Math::Matrix4x4	 m_concatObjectToWorld;		//!< toWorld concatenated with concatenated toWorld matrix from parents
			Math::Matrix4x4	 m_concatObjectFromWorld;	//!< fromWorld concatenated with concatenated fromWorld matrix from parents

			UInt			 m_id;

			ENodeType		 m_nodeType;
			
	};
	//End SceneNode


    //=========================================================================
    //! @function    SceneNode::Forward
    //! @brief       Return the forward vector of the scene node
    //!              
	//!				 Note that the vector is not guaranteed to be normalised
    //!              
    //! @return      The forward vector of the scene node
    //=========================================================================
	Math::Vector3D SceneNode::Forward() const
	{
		return Math::Vector3D ( m_concatObjectToWorld(2,0), m_concatObjectToWorld(2,1), m_concatObjectToWorld(2,2) );
	}
	//End SceneNode::Forward


    //=========================================================================
    //! @function    SceneNode::Up
    //! @brief       Return the up vector of the scene node
    //!      
	//!				 Note that the vector is not guaranteed to be normalised
	//!
    //! @return      The up vector of the scene node
    //=========================================================================
	Math::Vector3D SceneNode::Up() const
	{
		return Math::Vector3D ( m_concatObjectToWorld(1,0), m_concatObjectToWorld(1,1), m_concatObjectToWorld(1,2) );
	}
	//End SceneNode::Up



    //=========================================================================
    //! @function    SceneNode::Right
    //! @brief       Return the right vector of the scene node
	//!
	//!				 Note that the vector is not guaranteed to be normalised
	//!
    //! @return		 The right vector of the scene node
    //=========================================================================
	Math::Vector3D SceneNode::Right() const
	{
		return Math::Vector3D ( m_concatObjectToWorld(0,0), m_concatObjectToWorld(0,1), m_concatObjectToWorld(0,2) );
	}
	//End SceneNode::Right


    //=========================================================================
    //! @function    SceneNode::GetWorldSpacePosition
    //! @brief       Get the position of the node in world space
    //!              
    //!              
    //! @return      The position of the node in world space
    //=========================================================================
	Math::Vector3D SceneNode::GetWorldSpacePosition () const
	{
		Math::Vector3D position;
		position *= m_concatObjectToWorld;

		return position;
	}
	//End SceneNode::GetWorldSpacePosition


	//=========================================================================
    //! @function    SceneNode::QueryInterface
    //! @brief       Query the node to see if it supports an interface
    //!              
    //! @param       type	 [in]
    //! @param       pointer [out]
    //!              
    //! @return      true if supported, false if not supported
    //=========================================================================
	 bool SceneNode::QueryInterface ( enum ENodeInterfaceType type, void** receiver )
	 {
		 receiver = 0;

		 return false;
	 }
	 //End SceneNode::QueryInterface


}
//end namespace OidFX


#endif
//#ifndef OIDFX_SCENENODE_H
