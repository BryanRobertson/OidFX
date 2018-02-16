//======================================================================================
//! @file         QuadtreeNode.h
//! @brief        Scene graph node for a quadtree.
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

#ifndef OIDFX_QUADTREENODE_H
#define OIDFX_QUADTREENODE_H


#include "OidFX/SceneObject.h"


//namespace OidFX
namespace OidFX
{


	//!@class	QuadtreeNode
	//!@brief	Scene graph node for a quadtree.
	//!
	//!			Automatically builds the quadtree on construction, and any children are placed into
	//!			the appropriate node
	class QuadtreeNode : public SceneObject
	{
		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			QuadtreeNode (  Scene& scene, 
							const Math::AxisAlignedBoundingBox& boundingVolume,
							const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
						    const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );

			QuadtreeNode (  Scene& scene, 
							const Math::AxisAlignedBoundingBox& boundingVolume,
							UInt level,
							const Math::Matrix4x4& toWorld,
							const Math::Matrix4x4& fromWorld );


            //=========================================================================
            // Public methods
            //=========================================================================
			void BuildQuadtree ( const Math::AxisAlignedBoundingBox& leafVolume );
            
			void AddSortedChild ( boost::shared_ptr<SceneObject> object );

			//Fill visible object list
			void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );

		private:

            //=========================================================================
            // Private methods
            //=========================================================================
			void PrintDebugInfo ( );

            //=========================================================================
            // Private data
            //=========================================================================
			boost::shared_ptr<QuadtreeNode>	m_quadtreeChildren[4];
			UInt							m_treeLevel;
			bool							m_isLeafNode;

	};
	//End class QuadtreeNode


}
//End namespace OidFX


#endif
//#ifndef OIDFX_QUADTREENODE_H

