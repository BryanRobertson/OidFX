//======================================================================================
//! @file         QuadtreeNode.cpp
//! @brief        Scene graph node for a quadtree.
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 26 July 2005
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
#include "Math/MatrixStack.h"
#include "Math/IntersectionTests.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/SceneNode.h"
#include "OidFX/Camera.h"
#include "OidFX/Scene.h"
#include "OidFX/SceneObject.h"
#include "OidFX/QuadtreeNode.h"


using namespace OidFX;



//=========================================================================
//! @function    QuadtreeNode::QuadtreeNode
//! @brief       Quadtree constructor
//!              
//!              
//! @param       scene			[in] The scene to which this quadtree belongs
//! @param       boundingVolume [in] The volume of this node
//!				
//!              
//! @return      
//! @throw       
//=========================================================================
QuadtreeNode::QuadtreeNode ( Scene& scene, 
							const Math::AxisAlignedBoundingBox& boundingVolume,
							const Math::Matrix4x4& toWorld, 
						    const Math::Matrix4x4& fromWorld )

: SceneObject(scene, NODETYPE_SCENEPARTITION, toWorld, fromWorld ), 
  m_treeLevel(0), 
  m_isLeafNode(false)
{
	SetBoundingBox( boundingVolume );

#if 0
	std::clog << "Quadtree root node created " << std::endl;
#endif

}
//End QuadtreeNode::QuadtreeNode



//=========================================================================
//! @function    QuadtreeNode::QuadtreeNode
//! @brief       Quadtree constructor
//!              
//!              Builds the quadtree down to its lowest level
//!				 The lowest level is defined as the first level in which
//!				 the child nodes are smaller than leafVolume
//!              
//! @param       scene			[in] The scene to which this quadtree belongs
//! @param		 toWorld		[in] The objectToWorld transform
//! @param		 fromWorld		[in] The objectFromWorld transform
//!
//! @param       boundingVolume [in] The volume of this node
//!				
//!              
//! @return      
//! @throw       
//=========================================================================
QuadtreeNode::QuadtreeNode ( Scene& scene, 
							const Math::AxisAlignedBoundingBox& boundingVolume, 
							UInt level,
							const Math::Matrix4x4& toWorld, 
							const Math::Matrix4x4& fromWorld )

: SceneObject(scene, NODETYPE_SCENEPARTITION, toWorld, fromWorld), 
  m_treeLevel(level), 
  m_isLeafNode(false)
{
	SetBoundingBox( boundingVolume );

#if 0
	std::clog << "Quadtree node for level " << m_treeLevel << "created" << std::endl;
#endif

}
//End QuadtreeNode::QuadtreeNode



//=========================================================================
//! @function    QuadtreeNode::AddSortedChild
//! @brief       Add a child to this node, and sort it into the quadtree
//!              
//!				 Sorts the child node into the appropriate child quadtree node
//!              
//! @param       node [in]
//!              
//=========================================================================
void QuadtreeNode::AddSortedChild ( boost::shared_ptr<SceneObject> node )
{
	
	//Check to see if this is a leaf node
	//or if the node is bigger than our child nodes,
	//if it is, then add it to this level of the sub tree
	if ( (!m_parent) 
		 || ( m_isLeafNode ) 
		 || ( node->BoundingBox().ExtentX() > (BoundingBox().ExtentX() * 0.5f))
		 || ( node->BoundingBox().ExtentZ() > (BoundingBox().ExtentZ() * 0.5f))
	   )
	{
		AddChild(node);
	}
	else
	{

		//Otherwise, find the sub tree to add the node to

		//Keep count of the number of nodes that node intersects with.
		//If it rises above 1, then the node spans several of our child nodes,
		//and the object belongs in this node, rather than in one of its children
		UInt intersectionCount = 0;

		//Index of the child node that node belongs to
		UInt nodeIndex = 4;

		for ( UInt i=0; i < 4; ++i )
		{
			
#if 0
			std::clog << __FUNCTION__ << " level: " << m_treeLevel+1 << "\n"
					  <<  "Quadtree box = " << m_quadtreeChildren[i]->BoundingBox() << "\n"
					  <<  "Node box = " << node->BoundingBox() << "\n" << std::endl;
#endif
			debug_assert ( m_quadtreeChildren[i], "Node has no children!" );

			//Check that the bounding volume intersects with the quadtree childnode 
			if ( Math::IntersectXZ( m_quadtreeChildren[i]->BoundingBox(), node->BoundingBox() ) )
			{

#if 0
				std::clog << "Node box collides with quadtree node " 
						  << m_treeLevel+1 << "," << i << "\n" << std::endl;
#endif

				//Increment the intersection count
				++intersectionCount;

				//Set the quadtree child node index that the node belongs to
				nodeIndex = i;
			}
		}

	
		//If the node spans more than one child node, then 
		//add it to this level of the sub tree
		if ( intersectionCount > 1 )
		{
			AddChild(node);
		}
		else
		{
			if ( intersectionCount == 0 )
			{
				std::cerr << __FUNCTION__ << ": Box doesn't collide with any of the child nodes. "
						  << " Adding to tree level " << m_treeLevel << std::endl;
				AddChild(node);
			}
			else
			{

#if 0
				std::clog << __FUNCTION__ << ": Adding to subnode " 
								<< m_treeLevel + 1 << "," << nodeIndex << std::endl;
#endif

				//Call AddSortedChild on the appropriate child node to recursively add the
				//object to the correct child node
				m_quadtreeChildren[nodeIndex]->AddSortedChild(node);
			}
		}

	}

}
//End QuadtreeNode::AddChild



//=========================================================================
//! @function    QuadtreeNode::FillVisibleObjectList
//! @brief       Fills the visible object with visible nodes
//!              
//!              
//! @param       visibleObjectList [out] List of visible objects to append to
//! @param       camera			   [in] Camera to test visibility against
//!              
//=========================================================================
void QuadtreeNode::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera )
{

	//Check whether the bounding box is in the view frustum
	if ( (Math::Intersects ( m_boundingBox, camera.ViewFrustum())) )
	{
		//Call the base class FillVisibleObjectList to add all children
		SceneNode::FillVisibleObjectList ( visibleObjectList, camera );
	}

}
//End QuadtreeNode::FillVisibleObjectList



//=========================================================================
//! @function    QuadtreeNode::BuildQuadtree
//! @brief       Recursively adds quadtree nodes, until the quadtree node
//!              leafVolume will no longer fit into the tree
//!              
//! @param       leafVolume [in] Size at which to stop building the tree
//!              
//=========================================================================
void QuadtreeNode::BuildQuadtree ( const Math::AxisAlignedBoundingBox& leafVolume )
{

	//If the leaf volume is less than half of this bounding volume, then
	//create a subtree
	if (   (leafVolume.ExtentX() < (m_boundingBox.ExtentX() * 0.5f) ) 
		&& (leafVolume.ExtentZ() < (m_boundingBox.ExtentZ() * 0.5f) ) )
	{

		Math::Vector3D min = m_boundingBox.Min();
		Math::Vector3D max = m_boundingBox.Max();
		Float halfExtentX = m_boundingBox.ExtentX() / 2;
		Float halfExtentZ = m_boundingBox.ExtentZ() / 2;


		//Create the bounding volume for the top left node
		Math::AxisAlignedBoundingBox boundingVolume ( min, 
													  Math::Vector3D(min.X() + halfExtentX, max.Y(), min.Z() + halfExtentZ) );
		boundingVolume.SetPosition ( m_boundingBox.Position() );
		
		//Create the top left child node
		boost::shared_ptr<QuadtreeNode> topLeft	( new QuadtreeNode( m_scene, boundingVolume, m_treeLevel + 1, 
																	Math::Matrix4x4::IdentityMatrix, Math::Matrix4x4::IdentityMatrix ) );
		
		//

		//Create the bounding volume for the top right node
		boundingVolume = Math::AxisAlignedBoundingBox ( Math::Vector3D(min.X() + halfExtentX, min.Y(), min.Z() ), 
														Math::Vector3D(max.X(), max.Z(), min.Z() + halfExtentZ) );
		boundingVolume.SetPosition ( m_boundingBox.Position() );

		//Create the top right node
		boost::shared_ptr<QuadtreeNode> topRight	( new QuadtreeNode( m_scene, boundingVolume, m_treeLevel + 1,
																		Math::Matrix4x4::IdentityMatrix, Math::Matrix4x4::IdentityMatrix) );
		
		//

		//Create the bounding volume for the bottom left node
		boundingVolume  = Math::AxisAlignedBoundingBox ( Math::Vector3D(min.X(), min.Y(), min.Z() + halfExtentX), 
														 Math::Vector3D(min.X() + halfExtentX, max.Y(), max.Z()) );
		boundingVolume.SetPosition ( m_boundingBox.Position() );

		//Create the bottom left node
		boost::shared_ptr<QuadtreeNode> bottomLeft ( new QuadtreeNode( m_scene,	boundingVolume, m_treeLevel + 1,
																		Math::Matrix4x4::IdentityMatrix, Math::Matrix4x4::IdentityMatrix) );

		//

		//Create the bounding volume for the bottom right node
		boundingVolume  = Math::AxisAlignedBoundingBox ( Math::Vector3D(min.X() + halfExtentX, min.Y(), min.Z() + halfExtentZ), 
														 max );
		boundingVolume.SetPosition ( m_boundingBox.Position() );


		//Create the bottom right node
		boost::shared_ptr<QuadtreeNode> bottomRight( new QuadtreeNode( m_scene, boundingVolume, m_treeLevel + 1,
																	   Math::Matrix4x4::IdentityMatrix, Math::Matrix4x4::IdentityMatrix) );
		
		//

		AddChild(topLeft);
		AddChild(topRight);
		AddChild(bottomLeft);
		AddChild(bottomRight);
		
		//Keep track of the child quatree nodes, so we don't have to mess around with
		//reinterpret_cast every time we add something to the tree
		m_quadtreeChildren[0] = topLeft;
		m_quadtreeChildren[1] = topRight;
		m_quadtreeChildren[2] = bottomLeft;
		m_quadtreeChildren[3] = bottomRight;


		//Build the rest of the quadtree
		topLeft->BuildQuadtree ( leafVolume );
		topRight->BuildQuadtree ( leafVolume );
		bottomLeft->BuildQuadtree ( leafVolume );
		bottomRight->BuildQuadtree ( leafVolume );

	}
	else
	{
		m_isLeafNode = true;
	}
}
//End QuadtreeNode::BuildQuadtree