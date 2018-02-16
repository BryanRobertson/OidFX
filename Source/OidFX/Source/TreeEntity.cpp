//======================================================================================
//! @file         Tree.cpp
//! @brief        EntityNode for a tree
//!               
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


#include "Core/Core.h"
#include "Math/Matrix4x4.h"
#include "Math/MatrixStack.h"
#include "OidFX/Scene.h"
#include "OidFX/EntityNode.h"
#include "OidFX/GameApplication.h"
#include "OidFX/MeshManager.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/Constants.h"
#include "OidFX/TreeEntity.h"



using namespace OidFX;



//=========================================================================
// Static initialisation
//=========================================================================
boost::shared_ptr<TreeEntityCreator> TreeEntity::ms_treeCreator = boost::shared_ptr<TreeEntityCreator>();


//=========================================================================
// Static methods
//=========================================================================
boost::shared_ptr<TreeEntityCreator> TreeEntity::GetTreeCreator()
{
	if ( !ms_treeCreator )
	{
		ms_treeCreator = boost::shared_ptr<TreeEntityCreator>( new TreeEntityCreator() );
	}

	return ms_treeCreator;
}



//=========================================================================
//! @function    TreeEntity::TreeEntity
//! @brief       TreeEntity constructor
//!              
//! @param       scene	   [in]	Reference to the scene
//! @param       name	   [in]	Name of the helicopter
//! @param		 toWorld   [in]	To world matrix
//! @param		 fromWorld [in] From world matrix
//=========================================================================
TreeEntity::TreeEntity ( Scene& scene,
						const Char* name,
						const Math::Matrix4x4& toWorld, 
						const Math::Matrix4x4& fromWorld )
						: EntityNode( scene,
									  "Tree",
									  "Data/Art/Models/Tree.ms3d")
{

	SetFlag(EF_SPAWNONGROUND);
	SetFlag(EF_STATIC);
	SetFlag(EF_FLAMMABLE);
	SetFlag(EF_ANTIGRAVITY);
	SetFlag(EF_NOEXPLOSIONKICKBACK);
}
//End TreeEntity::TreeEntity