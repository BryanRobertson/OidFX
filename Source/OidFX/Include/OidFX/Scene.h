//======================================================================================
//! @file         Scene.h
//! @brief        Class representing a scene graph
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 12 July 2005
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


#ifndef OIDFX_SCENE_H
#define OIDFX_SCENE_H


#include <boost/noncopyable.hpp>
#include "Math/Triangle.h"
#include "Renderer/Renderable.h"
#include "OidFX/SceneNode.h"
#include "OidFX/Camera.h"
#include "OidFX/SceneQueryResult.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer { class RenderQueue; class IRenderer;				}
namespace OidFX	   { class VisibleObjectList; class GameApplication; class ProjectileManager; 
					 class CollisionManager; class EntityManager; class SceneNode;	}


//namespace OidFX
namespace OidFX
{


	//!@class	Scene
	//!@brief	Class representing a scene graph
	class Scene : public boost::noncopyable
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			Scene( GameApplication& application );
			virtual ~Scene();

            //=========================================================================
            // Public methods
            //=========================================================================
			virtual void Update  ( Float timeElapsedInSeconds );
			virtual void Restore ();
			virtual void FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera );

			virtual void QueryScene ( const Math::ParametricLine3D& ray, bool sortResults, SceneQueryResult& result );
			
			virtual void QueryScene ( const Math::BoundingSphere3D& sphere, EntityQueryResult& result );

			boost::shared_ptr<SceneNode> Root()			{ return m_rootNode;	}
			GameApplication&			 Application()  { return m_application; }

			ProjectileManager& GetProjectileManager() { return *m_projectileManager; }	
			CollisionManager&  GetCollisionManager()  { return *m_collisionManager;  }
			EntityManager&	   GetEntityManager()	  { return *m_entityManager;	 }

		protected:
		
            //=========================================================================
            //  Private data
            //=========================================================================
			boost::shared_ptr<CollisionManager>	 m_collisionManager;
			boost::shared_ptr<ProjectileManager> m_projectileManager;
			boost::shared_ptr<EntityManager>	 m_entityManager;

			boost::shared_ptr<SceneNode> m_rootNode;
			GameApplication&			 m_application;



	};
	//End class Scene


};
//end namespace OidFX


#endif
//#ifndef OIDFX_SCENE_H
