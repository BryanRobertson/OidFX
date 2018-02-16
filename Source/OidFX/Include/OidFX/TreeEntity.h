//======================================================================================
//! @file         Tree.h
//! @brief        EntityNode for a tree
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 16 September 2005
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

#ifndef OIDFX_TREE_H
#define OIDFX_TREE_H

#include "OidFX/EntityCreator.h"
#include "OidFX/EntityNode.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Math		{ class Matrix4x4; class MatrixStack; }
namespace OidFX		{ class Scene; class TreeEntityCreator; }



//namespace OidFX
namespace OidFX
{


	//!@class	TreeEntity
	//!@brief	Class representing a tree in the game world
	class TreeEntity : public EntityNode
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			TreeEntity	(	Scene& scene,
						const Char* name,
						const Math::Matrix4x4& toWorld = Math::Matrix4x4::IdentityMatrix, 
						const Math::Matrix4x4& fromWorld = Math::Matrix4x4::IdentityMatrix );


            //=========================================================================
            // Public static methods
            //=========================================================================
			static boost::shared_ptr<TreeEntityCreator> GetTreeCreator();

		
		private:

            //=========================================================================
            // Static private data
            //=========================================================================
			static boost::shared_ptr<TreeEntityCreator>		ms_treeCreator;

	};
	//End class TreeEntity




	//!@class	TreeEntityCreator
	//!@brief	Class used in the EntityFactory to instantiate Tree entities
	class TreeEntityCreator : public IEntityCreator
	{
		public:

			boost::shared_ptr<EntityNode> Create( const Char* name, Scene& scene )	
									{ return boost::shared_ptr<EntityNode>( new TreeEntity(scene, name) ); }
			const Char* TypeName() const
									{ return "Tree";	}
		private:

	};
	//End TreeEntityCreator




}
//end namespace OidFX



#endif
//#ifndef OIDFX_TREE_H

