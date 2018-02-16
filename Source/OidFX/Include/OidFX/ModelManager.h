//======================================================================================
//! @file         ModelManager.h
//! @brief        Class to manage model resources
//!               A model consists of several sub-meshes, each of which is covered by one effect
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 02 August 2005
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

#ifndef OIDFX_MODELMANAGER_H
#define OIDFX_MODELMANAGER_H


#include <boost/shared_ptr.hpp>
#include "Core/ResourceManager.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace OidFX		{ class MeshManager; }



//namespace OidFX
namespace OidFX
{


    //=========================================================================
    // Constants
    //=========================================================================
	const UInt g_maxModels;



	//!@class	ModelManager
	//!@brief	Class to manage model resources
	//!
	//!			A model consists of several sub-meshes, each of which is covered by one effect
	class ModelManager : public Core::ResourceManager<Model>,
						 public boost::noncopyable
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			ModelManager ( );


            //=========================================================================
            // Public methods
            //=========================================================================
			HModel AcquireModel ( const Char* fileName );


		private:

			boost::shared_ptr<MeshManager>	m_meshManager;

	};
	//End class ModelManager
	

}
//end namespace OidFX


#endif
//#ifndef OIDFX_MODELMANAGER_H



#endif
