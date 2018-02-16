//======================================================================================
//! @file         SceneNode.cpp
//! @brief        Class representing a basic node in the scene graph
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
#include "Math/Matrix4x4.h"
#include "Math/MatrixStack.h"
#include "Math/BoundingSphere3D.h"
#include "OidFX/Scene.h"
#include "OidFX/SceneNode.h"
#include "OidFX/Camera.h"
#include "OidFX/Constants.h"
#include "OidFX/EntityNode.h"
#include "OidFX/CollisionManager.h"



using namespace OidFX;



//=========================================================================
//! @function    SceneNode::SceneNode
//! @brief       SceneNode constructor
//!              
//! @param       scene		[in] Scene that this node belongs to
//! @param		 toWorld	[in] Object to world transform
//! @param		 fromWorld  [in] Object from world transform
//!              
//=========================================================================
SceneNode::SceneNode ( Scene& scene, 
					   ENodeType nodeType,
					   const Math::Matrix4x4& toWorld, 
					   const Math::Matrix4x4& fromWorld
					   )
: m_scene(scene), m_parent(0), 
  m_objectToWorld(toWorld), 
  m_objectFromWorld(fromWorld), 
  m_lodLevel(0),
  m_nodeType(nodeType)
{	
	static UInt id = 0;
	m_id = ++id;
}
//End SceneNode::SceneNode


//=========================================================================
//! @function    SceneNode::AddChild
//! @brief       Add a scene node as a child of this one
//!              
//!
//! @param       node [in] Node to add
//!              
//=========================================================================
void SceneNode::AddChild ( boost::shared_ptr<SceneNode> node )
{
	debug_assert ( node.get() != this, "Error, tried to add a node as a child of itself!" );

	try
	{
		node->SetParent(this);
		m_children.push_back( node );

		node->ConcatenateTransformFromParent();

	}
	catch (...)
	{
		//Undo the set parent call if m_children.push_back throws
		node->SetParent(0);
	}

}
//End SceneNode::AddChild


//=========================================================================
//! @function    SceneNode::RemoveChild
//! @brief       Remove the child node with the id specified
//!              
//!				 If there is no child node with the specified ID, then nothing will happen
//!
//! @param       id [in] ID of the child node to remove
//!              
//=========================================================================
void SceneNode::RemoveChild ( UInt id )
{
	for ( iterator itr = m_children.begin(); itr != m_children.end(); ++itr )
	{
		if ( (*itr)->ID() == id )
		{
			m_children.erase( itr );
			
			//We've erased it, just return. Since IDs are unique, the
			//entity shouldn't be in the scene graph more than once
			return;
		}
	}

	std::cerr << __FUNCTION__ ": Error, no children with ID of " << id << std::endl;
}
//End SceneNode::RemoveChild



//=========================================================================
//! @function    SceneNode::CanCollideWith
//! @brief       Indicates whether a scene node, or its children can collide with an entity
//!              
//! @param       entity [in] 
//!              
//! @return      true if the node can collide, false otherwise
//=========================================================================
bool SceneNode::CanCollideWith ( const EntityNode* entity ) const
{
	if ( (ID() == entity->ID()) 
		|| (entity->IsFlagSet(EF_NOCOLLIDE))
		|| ((NodeType() == NODETYPE_WORLD) && (entity->IsFlagSet(EF_NOWORLDCOLLIDE))))
	{

		return false;
	}
	else
	{
		return true;
	}
}
//End SceneNode::CanCollideWith



//=========================================================================
//! @function    SceneNode::CollidesWith
//! @brief       Returns true if this node collides with an entity
//!              
//! @param       entity			[in] Entity to check collision against
//! @param		 collisionType  [in] Type of collision check to perform 
//! @param		 normal			[out] Normal of collision plane (if any)
//!									  may be excluded for tests against non-world geometry
//! @param		 depth			[out] Depth of penetration into collision plane
//!									  may be excluded for tests against non-world geometry
//!
//! @return		 true if collision occured, false otherwise
//=========================================================================
bool SceneNode::CollidesWith ( EntityNode* entity,
							   ECollisionType collisionType,
							   Math::Vector3D& normal,
							   Float& depth )
{
	return false;
}
//End SceneNode::CollidesWith



//=========================================================================
//! @function    SceneNode::CheckCollisions
//! @brief       Check the scene node and all children for collisions
//!              
//! @param       entity			[in]
//! @param		 collisionType	[in]
//! @param		 collisionFlags	[in]
//!              
//=========================================================================
void SceneNode::CheckCollisions ( EntityNode* entity, 
								  ECollisionType collisionType,
								  const NodeCollisionFlags& collisionFlags,
								  CollisionManager& collisionManager )
{

	debug_assert ( entity, "Entity should not be NULL!" );

	iterator itr = ChildrenBegin();
	iterator end = ChildrenEnd();

	for ( ; itr != end; ++itr )
	{
		if ( (collisionFlags[(*itr)->NodeType()]) )
		{
			(*itr)->CheckCollisions( entity, collisionType, collisionFlags, collisionManager );
		}
	}

}
//End SceneNode::CheckCollisions



//=========================================================================
//! @function    SceneNode::ConcatenateTransformFromParent
//! @brief       Concatenates this nodes transform with that of its parent
//!              
//=========================================================================
void SceneNode::ConcatenateTransformFromParent ( )
{
	debug_assert ( m_parent, "ConcatenateTransformFromParent called on root node!" );

	m_concatObjectToWorld = m_parent->ConcatObjectToWorld() * m_objectToWorld;
	m_concatObjectFromWorld = m_parent->ConcatObjectFromWorld() * m_objectFromWorld;

}
//End SceneNode::ConcatenateTransformFromParent


//=========================================================================
//! @function    SceneNode::PropagateTransformsToChildren
//! @brief       Causes all scene nodes to update their concatenated
//!              matrices from their parents
//!              
//=========================================================================
void SceneNode::PropagateTransformsToChildren ( )
{
	if ( m_parent )
	{
		ConcatenateTransformFromParent();
	}

	iterator current = ChildrenBegin();
	iterator end = ChildrenEnd();

	for ( ; current != end; ++current )
	{
		PropagateTransformsToChildren();
	}
	
}
//End SceneNode::PropagateTransformsToChildren



//=========================================================================
//! @function    SceneNode::SetTransform
//! @brief       Set the toWorld transformation
//!
//!				 Sets the toWorld transformation, and calculates the 
//!				 fromWorld transformation from it. You should prefer the 
//!				 other SetTransform method to this one, as this version carries the
//!				 overhead of a matrix inversion.
//!				 This should only be used in situations where there is no method
//!				 other than matrix inversion, to get the fromWorld transformation
//!              
//! @param       toWorld [in]	
//!              
//=========================================================================
void SceneNode::SetTransform ( const Math::Matrix4x4& toWorld )
{

	m_objectToWorld = toWorld;
	m_objectFromWorld = toWorld;

	if ( !m_objectFromWorld.Invert() )
	{
		std::cerr << __FUNCTION__ << ": Error, couldn't invert toWorld matrix";
	}

}
//End SceneNode::SetTransform



//=========================================================================
//! @function    SceneNode::SetTransform
//! @brief       Set the toWorld and fromWorld transformations
//!              
//!              Sets the toWorld and fromWorld transformations
//!				 This should be the preferred method of this function
//!				 as it does not carry the overhead of a matrix inversion
//!              
//! @param       toWorld	[in] Matrix to transform object space to world space
//! @param       fromWorld	[in] Matrix to transform world space to object space
//!              
//=========================================================================
void SceneNode::SetTransform ( const Math::Matrix4x4& toWorld, const Math::Matrix4x4& fromWorld )
{

	m_objectToWorld = toWorld;
	m_objectFromWorld = fromWorld;

}
//End SceneNode::SetTransform



//=========================================================================
//! @function    SceneNode::SetConcatTransform
//! @brief       Set the concatenated transform matrices
//!              
//!              Sets the concatToWorld and concatFromWorld matrices.
//!				 Note that these will be overwritten the next time the scene node
//!				 is updated.
//!
//!				 This method is provided, for situations in which the concatenated transform
//!				 is needed before the scene node has been added to the scene graph.
//!              
//! @param       toWorld	[in] Matrix to transform object space to world space
//! @param       fromWorld	[in] Matrix to transform world space to object space
//!              
//=========================================================================
void SceneNode::SetConcatTransform ( const Math::Matrix4x4& concatToWorld, const Math::Matrix4x4& concatFromWorld )
{
	m_concatObjectToWorld = concatToWorld;
	m_concatObjectFromWorld = concatFromWorld;
}
//End SceneNode::SetConcatTransform


//=========================================================================
//! @function    SceneNode::Restore
//! @brief       SceneNode restore
//!              
//!				 This should be called after a Renderer Restore
//!              Simply calls restore on all children nodes
//!
//!				 Overloads of this method should either call this version
//!				 or ensure that they propagate the call to their children
//!              
//=========================================================================
void SceneNode::Restore ( )
{

	iterator current = m_children.begin();
	iterator end = m_children.end();

	for ( ; current != end; ++current )
	{
		(*current)->Restore();
	}

}
//End SceneNode::Restore



//=========================================================================
//! @function    SceneNode::Update
//! @brief       Updates the scene node and all children
//!              
//!				 Updates the m_concatObjectToWorld and m_concatObjectFromWorld matrices
//!				 pushes the current toWorld and fromWorld matrices onto the appropriate stacks
//!				 Updates all children, and pops the matrices from the stacks
//!              
//! @param       toWorldStack		  [in] Matrix stack for the toWorld transform
//! @param		 fromWorldStack		  [in] Matrix stack for the fromWorld transform
//! @param       timeElapsedInSeconds [in] Time elapsed since last update
//!              
//=========================================================================
void SceneNode::Update ( Math::MatrixStack& toWorldStack,
						 Math::MatrixStack& fromWorldStack, 
						 Float timeElapsedInSeconds )
{

	toWorldStack.Push ( );
	toWorldStack.Top() *= m_objectToWorld;
	m_concatObjectToWorld = toWorldStack.Top();

	fromWorldStack.Push ( );
	fromWorldStack.Top() *= m_objectFromWorld;
	m_concatObjectFromWorld = fromWorldStack.Top();

	iterator current = m_children.begin();
	iterator end	 = m_children.end();

	for ( ; current != end; ++current )
	{

		(*current)->Update ( toWorldStack, fromWorldStack, timeElapsedInSeconds );
		
	}

	toWorldStack.Pop();
	fromWorldStack.Pop();

}
//End SceneNode::Update


//=========================================================================
//! @function    SceneNode::FillVisibleObjectList
//! @brief		 Add this node to the visible object list if it is in the
//!				 camera's view frustum, and do the same for all children
//!
//!				 Since a normal scene node can't be rendered, it simply
//!				 calls FillVisibleObjectList for all child nodes
//!              
//=========================================================================
void SceneNode::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera )
{
	iterator current = m_children.begin();
	iterator end	 = m_children.end();

	for ( ; current != end; ++current )
	{
		(*current)->FillVisibleObjectList ( visibleObjectList, camera );
	}

	//Update our LOD level
	UpdateLODLevel(camera);
}
//End SceneNode::FillVisibleObjectList



//=========================================================================
//! @function    SceneNode::UpdateLODLevel
//! @brief       Update the level of detail of this node, based on camera position
//!              
//=========================================================================
void SceneNode::UpdateLODLevel ( const Camera& camera )
{
	//Get the vector from the camera to the node
	Math::Vector3D position;
	position *= m_concatObjectToWorld;

	//Calculate the LOD level, using the distance of the node from the near plane
	Float nearPlaneDistance = (camera.GetPosition() - position).Length();

	//If the near plane distance is less than the pop distance, then the LOD level is 0
	if ( nearPlaneDistance < g_initialLODPopDistance )
	{
		m_lodLevel = 0;
		return;
	}

	//Otherwise, calculate the LOD level
	m_lodLevel = static_cast<UInt>( Math::Floor((nearPlaneDistance) / (g_lodPopDistance) ));

	if ( m_lodLevel > g_lodMax )
	{
		m_lodLevel = g_lodMax;
	}
}
//End SceneNode::UpdateLODLevel



//=========================================================================
//! @function    SceneNode::QueueForRendering
//! @brief       Queue the node for rendering
//!              
//! @param       queue [in] RenderQueue to add the object to 
//!              
//=========================================================================
void SceneNode::QueueForRendering ( Renderer::RenderQueue& queue )
{

}
//End SceneNode::QueueForRendering



//=========================================================================
//! @function    SceneNode::Render
//! @brief       Render the node
//!              
//! @param       renderer [in] Renderer to draw the node
//!              
//=========================================================================
void SceneNode::Render ( Renderer::IRenderer& renderer )
{

}
//End SceneNode::Render



//=========================================================================
//! @function    SceneNode::SetParent
//! @brief       Set the node's pointer to its parent
//!              
//! @param       node [in]
//!              
//=========================================================================
void SceneNode::SetParent ( SceneNode* node )
{
	m_parent = node;	
}
//End SceneNode::SetParent


//=========================================================================
//! @function    SceneNode::QueryScene 
//! @brief       Query the scene to check for triangles intersected by a ray
//!
//!				 Not really meaningful for a base-class scene node
//!				 simply forwards the request on to children unconditionally
//!
//! @param		 ray	[in]	Ray to test intersection with
//! @param		 result [out]	Array of intersection points
//=========================================================================
void SceneNode::QueryScene ( const Math::ParametricLine3D& ray, SceneQueryResult& result )
{
	
	for ( const_iterator itr = ChildrenBegin(); itr != ChildrenEnd(); ++itr )
	{
		(*itr)->QueryScene( ray, result );
	}

}
//End SceneNode::QueryScene 


//=========================================================================
//! @function    SceneNode::QueryScene
//! @brief       Query the scene for entities inside a bounding sphere
//!              
//! @param       sphere [in]
//! @param       result [in]
//!              
//=========================================================================
void SceneNode::QueryScene ( const Math::BoundingSphere3D& sphere, EntityQueryResult& result )
{
	for ( const_iterator itr = ChildrenBegin(); itr != ChildrenEnd(); ++itr )
	{
		(*itr)->QueryScene( sphere, result );
	}
}
//End SceneNode::QueryScene



