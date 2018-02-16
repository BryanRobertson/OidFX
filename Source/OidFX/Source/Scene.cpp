//======================================================================================
//! @file         Scene.h
//! @brief        Class representing the entire scene
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


#include "Core/Core.h"
#include "Math/MatrixStack.h"
#include "Renderer/Renderer.h"
#include "OidFX/GameApplication.h"
#include "OidFX/VisibleObjectList.h"
#include "OidFX/Scene.h"
#include "OidFX/SceneNode.h"
#include "OidFX/ProjectileManager.h"
#include "OidFX/CollisionManager.h"
#include "OidFX/EntityManager.h"
#include "OidFX/Constants.h"



using namespace OidFX;



//=========================================================================
//! @function    Scene::Scene
//! @brief       Scene constructor
//!              
//!              Creates the root node of the scene graph
//=========================================================================
Scene::Scene ( GameApplication& application )
: m_application(application)
{
	m_rootNode = boost::shared_ptr<SceneNode>( new SceneNode(*this) );

	m_collisionManager  = boost::shared_ptr<CollisionManager>  ( new CollisionManager(*this) );
	m_projectileManager = boost::shared_ptr<ProjectileManager> ( new ProjectileManager(*this, g_maxProjectiles, *m_collisionManager) );
	m_entityManager		= boost::shared_ptr<EntityManager>	   ( new EntityManager(*this, GetCollisionManager()) );
}
//End Scene::Scene



//=========================================================================
//! @function    Scene::~Scene
//! @brief       Scene destructor
//=========================================================================
Scene::~Scene ()
{

}
//End Scene::~Scene



//=========================================================================
//! @function    Scene::Update
//! @brief       Update the scene
//!              
//!				 Calls update on the root of the scene graph, which propagates
//!				 the update call down to all of its children
//!
//! @param       timeElapsedInSeconds [in]	Time elapsed since last update
//!              
//=========================================================================
void Scene::Update ( Float timeElapsedInSeconds )
{
	Math::MatrixStack toWorldStack;
	Math::MatrixStack fromWorldStack;

	m_rootNode->Update ( toWorldStack, fromWorldStack, timeElapsedInSeconds );

	GetProjectileManager().Update();
	GetEntityManager().Update();

	//Create a list of colliding objects
	GetCollisionManager().CheckCollisions();

	//Execute the results of the collisions
	GetCollisionManager().ExecuteCollisionList();
}
//End Scene::Update



//=========================================================================
//! @function    Scene::Restore
//! @brief       Restore all nodes in the scene graph
//!              
//!				 Calls Restore on the root of the scene graph, which
//!				 propogates it down to its children
//=========================================================================
void Scene::Restore ( )
{
	m_rootNode->Restore();
}
//End Scene::Restore



//=========================================================================
//! @function    Scene::FillVisibleObjectList
//! @brief       Gets a list of visible objects which can be seen in the
//!				 camera's viewing volume
//!
//!				 Calls FillVisibleObjectList on the root node, which recursively
//!				 propagates the call down to its children
//!              
//!	@param		 visibleObjectList [in] List of visible objects to populate
//! @param		 camera			   [in] Camera from which the scene is viewed
//!                
//=========================================================================
void Scene::FillVisibleObjectList ( VisibleObjectList& visibleObjectList, const Camera& camera )
{
	m_rootNode->FillVisibleObjectList( visibleObjectList, camera );
}
//End Scene::FillVisibleObjectList



//=========================================================================
//! @function    Scene::QueryScene
//! @brief       Get a list of triangles which collide with the ray provided
//!              
//! @param       ray		 [in]	Ray to check collision with
//! @param		 sortResults [in]	Indicates whether or not the triangles should be sorted by distance from the ray origin
//! @param       result		 [out]	Array of triangles holding the results of the scene query
//!              
//=========================================================================
void Scene::QueryScene ( const Math::ParametricLine3D& ray, bool sortResults, SceneQueryResult& result )
{
	Root()->QueryScene( ray, result );

	//Sort the results if need be
	if ( sortResults )
	{
		std::sort( result.begin(), result.end() );
	}
}
//End Scene::QueryScene



//=========================================================================
//! @function    Scene::QueryScene
//! @brief       Query the scene for entities within a bounding sphere
//!              
//! @param       sphere [in]	
//! @param       result [in]	
//!              
//=========================================================================
void Scene::QueryScene ( const Math::BoundingSphere3D& sphere, EntityQueryResult& result )
{
	Root()->QueryScene( sphere, result );
}
//End Scene::QueryScene



