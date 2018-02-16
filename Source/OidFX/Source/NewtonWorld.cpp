//======================================================================================
//! @file         NewtonWorld.cpp
//! @brief        Classes to wrap the Newton world for the Newton physics library
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 21 September 2005
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


#include <boost/bind.hpp>
#include <boost/multi_array.hpp>
#include "Core/Core.h"
#include "Math/Vector3D.h"
#include "Math/Matrix4x4.h"
#include "Math/Triangle.h"
#include "Math/ParametricLine3D.h"
#include "OidFX/NewtonWorld.h"
#include "OidFX/NewtonCollision.h"


//namespace OidFX
namespace OidFX
{

//namespace Newton
namespace Newton
{


    //=========================================================================
    //! @function    World::World
    //! @brief       World constructor
    //=========================================================================
	World::World ()
	{

		Impl::NewtonWorld* world = Impl::NewtonCreate( 0, 0 );

		m_world = boost::shared_ptr<Impl::NewtonWorld>( world, 
														Impl::NewtonDestroy );

	}
	//End World::World


	//=========================================================================
    //! @function    World::Collide
    //! @brief       Checks two Collision objects against each other for collisions
	//!
	//!	@param		 colliderA		 [in]	First object
	//! @param		 colliderAMatrix [in]	Offset matrix of first object
	//! @param		 colliderB		 [in]	Second object
	//! @param		 colloderBMatrix [in]	Offset matrix of second object
	//! @param		 maxCollisions	 [in]	Unused at the moment, reserved for future use
	//! @param		 contacts		 [out]	Array of contact points
	//! @param		 normals		 [out]	Array of contract normals
	//! @param		 penetration	 [out]  Array of penetration depths
    //=========================================================================
	UInt World::Collide ( const Collision& colliderA,
						  const Math::Matrix4x4& colliderAMatrix,
						  const Collision& colliderB,
						  const Math::Matrix4x4& colliderBMatrix,
						  UInt  maxCollisions,
						  World::CollisionInfo& contacts,
						  World::CollisionInfo& normals,
						  World::PenetrationInfo& penetration )
	{

		static Float point[3];
		static Float normal[3];
		static Float penetra;

		UInt count = Impl::NewtonCollisionCollide(  m_world.get(), 
													1, 
													colliderA.GetCollision(), 
													colliderAMatrix.GetPointer(), 
													colliderB.GetCollision(), 
													colliderBMatrix.GetPointer(), 
													&point[0], 
													&normal[0],
													&penetra);

		//Copy the contact data to contacts
		contacts.push_back( Math::Vector3D( point[0], point[1], point[2] ) );

		//Copy the normals data to normals
		normals.push_back( Math::Vector3D( normal[0], normal[1], normal[2] ) );
		normals.back().Normalise();
		penetration.push_back( penetra );

		return count;
	}
	//End World::Collide



	//=========================================================================
    //! @function    World::Collide
    //! @brief       Check to see if an object collides with a line
	//!
	//! @param		 collider	[in]
	//! @param		 line	    [in]
	//!
	//! @return		 parametric point on the line at which the collision occurs
	//=========================================================================
	Float World::Collide ( const Newton::Collision& collider,
						   const Math::ParametricLine3D& line )
	{

		//Copy the line data into the format required by newton
		Float p0[3];
		p0[0] = line.P0().X();
		p0[1] = line.P0().Y();
		p0[2] = line.P0().Z();

		Float p1[3];
		p1[0] = line.P1().X();
		p1[1] = line.P1().Y();
		p1[2] = line.P1().Z();

		//Data returned by newton
		Float normal[3];
		Int attribute = 0;

		return Impl::NewtonCollisionRayCast ( collider.GetCollision(), p0, p1, normal, &attribute );
	}
	//End World::Collide



    //=========================================================================
    // The following variable and function is used internally by World::SceneRaycast
    //=========================================================================
	static Float g_rayIntersection;

	Float RaycastCallBack ( const Impl::NewtonBody* body, 
							const Float* hitNormal, 
							Int collisionID, 
							void* userData, 
							Float intersectParam )
	{
		if ( g_rayIntersection < intersectParam )
		{
			g_rayIntersection = intersectParam;
		}

		return intersectParam;
	}
	//


    //=========================================================================
    //! @function    World::SceneRaycast
    //! @brief       Cast a ray through the scene, and return the closest intersection
    //!              on the line
    //!              
    //! @param       line [in]
    //!              
    //! @return      The closest intersection on the line. If this is greater than 1, then
	//!				 no collisions occured
    //=========================================================================
	Float World::SceneRaycast ( const Math::ParametricLine3D& line )
	{
		//Set g_rayIntersection to a value greater than 1.1f, 
		//so that we don't get any false collisions
		g_rayIntersection = 1.1f;

		//Copy the line data into the format required by newton
		Float p0[3];
		p0[0] = line.P0().X();
		p0[1] = line.P0().Y();
		p0[2] = line.P0().Z();

		Float p1[3];
		p1[0] = line.P1().X();
		p1[1] = line.P1().Y();
		p1[2] = line.P1().Z();

		//Call NewtonWorldRayCast to cast a ray through the scene
		Impl::NewtonWorldRayCast( m_world.get(), p0, p1, RaycastCallBack, 0); 

		//Return the point of intersection
		return g_rayIntersection;
	}
	//End World::SceneRaycast



	//=========================================================================
    //! @function    World::CreateSphere
    //! @brief       Creates a sphere collision object
	//!
	//! @param		 extents		[in] Extents of the sphere
	//! @param		 offsetMatrix	[in] Offset matrix of the sphere, from the centre of the object it contains
	//!
	//! @return		 A new collision object
	//=========================================================================
	Collision World::CreateSphere ( const Math::Vector3D& extents, 
									const Math::Matrix4x4& offsetMatrix )
	{

		return Newton::Collision ( this, Impl::NewtonCreateSphere(m_world.get(),
																	 extents.X(),
																	 extents.Y(),
																	 extents.Z(),
																	 offsetMatrix.GetPointer() ) );
	}
	//End World::CreateSphere


	//=========================================================================
    //! @function    World::CreateBox
    //! @brief       Creates a box collision object
	//!
	//! @param		 extents		[in] Extents of the box
	//! @param		 offsetMatrix	[in] Offset matrix of the box,  from the centre of the object it contains
	//!
	//! @return		 A new collision object
	//=========================================================================
	Collision World::CreateBox ( const Math::Vector3D& extents, 
								 const Math::Matrix4x4& offsetMatrix )
	{
		return Newton::Collision ( this, Impl::NewtonCreateBox(m_world.get(),
																	 extents.X(),
																	 extents.Y(),
																	 extents.Z(),
																	 offsetMatrix.GetPointer() ) );
	}
	//End World::CreateBox



    //=========================================================================
    //! @function    World::CreateTreeCollision
    //! @brief       Create a tree collider
	//!
	//!				 A tree collider is used for large meshes, such as a game level
    //!              
    //! @param       triangles [in]	An array of triangles used for the collision mesh
    //!              
    //! @return      A new collision tree
    //=========================================================================
	Collision World::CreateTreeCollision ( const Core::Vector<Math::Triangle>::Type& triangles )
	{

		//Create an array of vertices 
		Float verts[3][3];

		//Create the collision object
		Newton::Collision collisionTree ( this, Impl::NewtonCreateTreeCollision(GetWorld(), 0) ); 

		//Set up the tree to start building
		Impl::NewtonTreeCollisionBeginBuild ( collisionTree.GetCollision() );

		//Add the triangles to the tree
		for ( Core::Vector<Math::Triangle>::Type::const_iterator itr = triangles.begin();
			  itr != triangles.end();
			  ++itr )
		{
			
			//Fill up the verts structure with vertex data from the triangles
			verts[0][0] = itr->V0().X();
			verts[0][1] = itr->V0().Y();
			verts[0][2] = itr->V0().Z();

			verts[1][0] = itr->V1().X();
			verts[1][1] = itr->V1().Y();
			verts[1][2] = itr->V1().Z();

			verts[2][0] = itr->V2().X();
			verts[2][1] = itr->V2().Y();
			verts[2][2] = itr->V2().Z();

			//Add the triangle to the tree
			Impl::NewtonTreeCollisionAddFace( collisionTree.GetCollision(), //Collision object
											 3,								//Number of vertices
											 verts[0],						//Pointer to vertices
											 12,							//Stride in bytes
											 0								//Face attribute 
											 );				 
			
		}


		//End building the tree
		Impl::NewtonTreeCollisionEndBuild ( collisionTree.GetCollision(), 1 );


		return collisionTree;

	}
	//End World::CreateTreeCollision



}
//End namespace Newton
}
//End namespace OidFX
