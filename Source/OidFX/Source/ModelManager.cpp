//======================================================================================
//! @file         ModelManager.cpp
//! @brief        Class to manage model resources
//!               A model consists of several sub-meshes, each of which is covered by one effect
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 09 August 2005
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
#include "OidFX/ModelManager.h"



using namespace OidFX;



//=========================================================================
//! @function    ModelManager::ModelManager
//! @brief       ModelManager constructor
//!              
//!              
//=========================================================================
ModelManager::ModelManager ( )
: ResourceManager<Model>( g_maxModels )
{

}
//End ModelManager::ModelManager



//=========================================================================
//! @function    ModelManager::AcquireModel
//! @brief       Get a handle to a model resource
//!              
//!              If the model is not loaded, then it will be loaded
//!				 and a handle to the new model returned.
//!
//!				 Otherwise, a handle to the existing model will be returned
//!              
//! @param       fileName [in]
//!              
//! @return      A handle to the model
//! @throw       Core::RuntimeError
//=========================================================================
HModel ModelManager::AcquireModel ( const Char* fileName )
{
	HandleType handle = AcquireExistingResource ( fileName );

	if ( handle == Core::NullHandle() )
	{
		ModelLoader loader ( );
		boost::shared_ptr<Model> model = loader.Load( fileName );

		return AddNewResource( model );
	}
	else
	{
		return handle;
	}

}
//End ModelManager::AcquireModel 