//======================================================================================
//! @file         IntersectionTests.cpp
//! @brief        Intersection tests for bounding volumes/planes/etc
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 22 July 2005
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
#include "Math/Math.h"
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"
#include "Math/BoundingBox3D.h"
#include "Math/Frustum.h"
#include "Math/BoundingSphere3D.h"
#include "Math/ParametricLine3D.h"
#include "Math/Plane3D.h"
#include "Math/Triangle.h"
#include "Math/IntersectionTests.h"



namespace Math
{

//=========================================================================
//! @function    Intersects (const AxisAlignedBoundingBox&, const Frustum&)
//! @brief       Returns true if a bounding box is contained within a frustum
//!              false otherwise
//!              
//! @param       box		[in]
//! @param       frustum	[in]
//!              
//! @return      true if the bounding box is inside the frustum, false otherwise
//! @throw       
//=========================================================================
bool Intersects ( const AxisAlignedBoundingBox& box, const Frustum& frustum  ) throw()
{
	Vector3D minXminYminZ = box.GetCorner(AxisAlignedBoundingBox::MIN_X_MIN_Y_MIN_Z);
	Vector3D minXminYmaxZ = box.GetCorner(AxisAlignedBoundingBox::MIN_X_MIN_Y_MAX_Z);
	Vector3D minXmaxYminZ = box.GetCorner(AxisAlignedBoundingBox::MIN_X_MAX_Y_MIN_Z);
	Vector3D minXmaxYmaxZ = box.GetCorner(AxisAlignedBoundingBox::MIN_X_MAX_Y_MAX_Z);
	Vector3D maxXminYminZ = box.GetCorner(AxisAlignedBoundingBox::MAX_X_MIN_Y_MIN_Z);
	Vector3D maxXminYmaxZ = box.GetCorner(AxisAlignedBoundingBox::MAX_X_MIN_Y_MAX_Z);
	Vector3D maxXmaxYminZ = box.GetCorner(AxisAlignedBoundingBox::MAX_X_MAX_Y_MIN_Z);
	Vector3D maxXmaxYmaxZ = box.GetCorner(AxisAlignedBoundingBox::MAX_X_MAX_Y_MAX_Z);
	

	Plane3D planes[6];

	planes[0] = frustum.Far(); 
	planes[1] = frustum.Near();
	planes[2] = frustum.Left();
	planes[3] = frustum.Right();
	planes[4] = frustum.Top();
	planes[5] = frustum.Bottom();

	//Tests each point against each plane for intersection
	//if all points are completely behind plane, then
	//the object is not in the frustum

	for ( UInt plane=0; plane < 6; ++plane )
	{
		/*
		//Check the centre. Otherwise boxes that are bigger than the frustum will get clipped
		if ( planes[plane].PointInPlane(centre)  >= 0 )
		{
			continue;
		
		}*/

		if ( planes[plane].PointInPlane(minXminYminZ)  >= 0 )
		{
			continue;
		}

		if ( planes[plane].PointInPlane(minXminYmaxZ)  >= 0 )
		{
			continue;
		}

		if ( planes[plane].PointInPlane(minXmaxYminZ)  >= 0 )
		{
			continue;
		}

		if ( planes[plane].PointInPlane(minXmaxYmaxZ)  >= 0 )
		{
			continue;
		}

		if ( planes[plane].PointInPlane(maxXminYminZ)  >= 0 )
		{
			continue;
		}

		if ( planes[plane].PointInPlane(maxXminYmaxZ)  >= 0 )
		{
			continue;
		}

		if ( planes[plane].PointInPlane(maxXmaxYminZ)  >= 0 )
		{
			continue;
		}

		if ( planes[plane].PointInPlane(maxXmaxYmaxZ)  >= 0 )
		{
			continue;
		}

		return false;

	}

	return true;
}
//End Intersects (const AxisAlignedBoundingBox&, const Frustum&)



//=========================================================================
//! @function    Intersects ( const AxisAlignedBoundingBox&, const AxisAlignedBoundingBox& )
//! @brief       Tests whether two boxes intersect
//!              
//! @param       box1 
//! @param       box2 
//!              
//! @return      true if they intersect, false otherwise
//=========================================================================
bool Intersects ( const AxisAlignedBoundingBox& box1, const AxisAlignedBoundingBox& box2 )
{

	const Vector3D box1Min = box1.GetCorner( AxisAlignedBoundingBox::MIN_X_MIN_Y_MIN_Z );
	const Vector3D box1Max = box1.GetCorner( AxisAlignedBoundingBox::MAX_X_MAX_Y_MAX_Z );

	const Vector3D box2Min = box2.GetCorner( AxisAlignedBoundingBox::MIN_X_MIN_Y_MIN_Z );
	const Vector3D box2Max = box2.GetCorner( AxisAlignedBoundingBox::MAX_X_MAX_Y_MAX_Z );

	if (	((box1Min.X() < box2Max.X()) && (box2Min.X() < box1Max.X()))
		&&	((box1Min.Y() < box2Max.Y()) && (box2Min.Y() < box1Max.Y()))
		&&	((box1Min.Z() < box2Max.Z()) && (box2Min.Z() < box1Max.Z())) )
	{
		return true;
	}
	else
	{
		return false;
	}


}
//End Intersects ( const AxisAlignedBoundingBox&, const AxisAlignedBoundingBox& )




//=========================================================================
//! @function    Intersects ( const AxisAlignedBoundingBox& const BoundingSphere3D& sphere )
//! @brief       Indicates whether an axis aligned box and sphere intersect
//!              
//! @param       box 
//! @param       sphere 
//!              
//! @return      true if the box and sphere intersect, false otherwise
//=========================================================================
bool Intersects ( const AxisAlignedBoundingBox& box, const BoundingSphere3D& sphere )
{
	not_implemented_yet;
	return false;
}
//End Intersects ( const AxisAlignedBoundingBox& const BoundingSphere3D& sphere )



//=========================================================================
//! @function    Intersects ( const ParametericLine3D& line, const Triangle& triangle )
//! @brief       Indicates whether a parametric line and triangle intersect
//!              
//!              
//! @param       line		[in]
//! @param       triangle	[in]
//!              
//! @return      NoIntersect			: If there is no intersection
//!				 IntersectInSegment		: If the intersection occurs within the line segment
//!				 IntersectOutSegment	: If the intersection occurs outside the line segment
//!				 IntersectEverywhere	: If the line is on the plane of the triangle
//!
//=========================================================================
bool Intersects ( const ParametricLine3D& line, const Triangle& triangle )
{

	//First determine whether or not the line will cross the plane of the triangle
	//by checking to see if both points are on the same side of the plane
	Float p0 = triangle.Plane().PointInPlane ( line.P0() );
	Float p1 = triangle.Plane().PointInPlane ( line.P1() );

	if (   ((p0 < 0.0f) && (p1 < 0.0f))
		|| ((p0 > 0.0f) && (p1 > 0.0f)) )
	{
		//If both points are on the same side of the plane then 
		//there can be no intersection
		return false;
	}

	//Get the point of intersection
	Scalar		t = 0.0f;
	Vector3D	point;

	EParametricLineIntersect planeIntersection 
							= triangle.Plane().Intersection( line, t, point );

	//If the line doesn't pierce the plane of the triangle, then
	//it is impossible for the line to intersect the triangle
	if ( NoIntersect == planeIntersection )
	{
		return false;
	}

	//Otherwise we have to find out whether the point of intersection is inside
	//the triangle
	return triangle.PointInTriangle ( point );

}
//End Intersects ( const ParametericLine3D& line, const Triangle& triangle )




//=========================================================================
//! @function    IntersectXZ ( const AxisAlignedBoundingBox&, const AxisAlignedBoundingBox& )
//! @brief       Indicates whether or not two bounding boxes intersect in the X,Z dimensions
//!              
//! @param       box1 [in] 
//! @param       box2 [in]
//!              
//! @return      true if the boxes intersect in the X,Z dimensions, false otherwise
//=========================================================================
bool IntersectXZ ( const AxisAlignedBoundingBox& box1, const AxisAlignedBoundingBox& box2 )
{
	const Vector3D box1Min = box1.GetCorner( AxisAlignedBoundingBox::MIN_X_MIN_Y_MIN_Z );
	const Vector3D box1Max = box1.GetCorner( AxisAlignedBoundingBox::MAX_X_MAX_Y_MAX_Z );

	const Vector3D box2Min = box2.GetCorner( AxisAlignedBoundingBox::MIN_X_MIN_Y_MIN_Z );
	const Vector3D box2Max = box2.GetCorner( AxisAlignedBoundingBox::MAX_X_MAX_Y_MAX_Z );

	if (	((box1Min.X() < box2Max.X()) && (box2Min.X() < box1Max.X()))
		&&	((box1Min.Y() < box2Max.Y()) && (box2Min.Y() < box1Max.Y())) )
	{
		return true;
	}
	else
	{
		return false;
	}

}
//End IntersectXZ ( const AxisAlignedBoundingBox&, const AxisAlignedBoundingBox& ) 


//=========================================================================
//! @function    Intersects ( const BoundingSphere3D&, const BoundingSphere3D& )
//! @brief       Indicates whether or not two spheres intersect
//!              
//! @param       sphere1 [in]
//! @param       sphere2 [in] 
//!              
//! @return      true if they intersect, false otherwise
//=========================================================================
bool Intersects ( const BoundingSphere3D& sphere1, const BoundingSphere3D& sphere2 )
{
	
	//Two spheres intersect if the distance between them is less than the
	//sum of their radii
	Vector3D distance = sphere2.GetPosition() - sphere1.GetPosition();

	if ( distance.LengthSquared() < ( sphere1.RadiusSquared() - sphere2.RadiusSquared() ) )
	{
		return true;
	}
	else
	{
		return false;
	}

}
//End Intersects ( const BoundingSphere3D&, const BoundingSphere3D& )



//=========================================================================
//! @function    Intersects ( const BoundingSphere3D&, const Math::Vector3D&, const Triangle& )
//! @brief       Indicates whether or not a moving sphere intersects a triangle
//!              
//! @param       sphere		[in] Bounding sphere to check against triangle
//! @param		 velocity	[in] Velocity of the bounding sphere
//! @param       triangle   [in] Triangle to check the moving sphere against
//! @param		 d			[out] Depth of penetration into the plane of the triangle
//!              
//! @return      true if the sphere intersects, false otherwise
//=========================================================================
bool Intersects ( const BoundingSphere3D& sphere, const Math::Vector3D& velocity, const Triangle& triangle, Float& d )
{
	//Get the position and next position of the sphere
	const Math::ParametricLine3D line( sphere.GetPosition() - velocity, sphere.GetPosition() );


	//First we get the intersection point of the plane of the triangle, and the sphere

	//First find the time of intersection, if this is in the range [0,1], then the sphere intersects the plane
	//
	//For an explanation of this equation, read Mathematics for Game Developers, by Christopher Tremblay,
	//page 265-266
	Float t = sphere.Radius() - triangle.Plane().D() - Vector3D::DotProduct(triangle.Normal(), line.P1())
			  / Vector3D::DotProduct(triangle.Normal(), line.P0() - line.P1());

	if ( !InRange( t, 0.0f, 1.0f ) )
	{
		return false;
	}

	//Find out if the point of intersection is inside the triangle
	Math::Vector3D pointOfIntersection;

	//First get the point of intersection between the line and the plane
	line.PointOnLine(t, pointOfIntersection );

	//Now find out if the point of intersection is in the triangle
	if ( !triangle.PointInTriangle(pointOfIntersection) )
	{
		return false;
	}
	else
	{
		//Set d to the depth of penetration into the plane
		d = (triangle.Plane().A() *  sphere.GetPosition().X()) +
			(triangle.Plane().B() *  sphere.GetPosition().Y()) +
			(triangle.Plane().C() *  sphere.GetPosition().Z()) +
			triangle.Plane().D() - sphere.Radius();

		return true;
	}
}
//End Intersects ( const BoundingSphere3D&, const Math::Vector3D&, const Triangle& )



//=========================================================================
//! @function    Intersects  ( const ParametricLine3D&, const AxisAlignedBoundingBox& )
//! @brief       Test whether or not a ray intersects a bounding box
//!              
//!				 For an explanation of the algorithm used, see the book
//!				 Mathematics for 3D game programming & computer graphics, by Eric Lengyel
//!
//! @param       line  [in]		Ray to test
//! @param       box   [in]		Box to test
//! @param		 t	   [out]	Point on line, where intersection occurs
//!              
//! @return      
//!
//!
//=========================================================================
EParametricLineIntersect Intersects ( const ParametricLine3D& line, const AxisAlignedBoundingBox& box,
										Float& t )
{

	const Vector3D boxMin = box.GetCorner( AxisAlignedBoundingBox::MIN_X_MIN_Y_MIN_Z );
	const Vector3D boxMax = box.GetCorner( AxisAlignedBoundingBox::MAX_X_MAX_Y_MAX_Z );

	const Vector3D& rayOrigin = line.P0();
	const Vector3D& rayDir	  = line.V();
	const Vector3D& rayEnd	  = line.P1();

	t = 0.0f;

	//If the ray origin is inside the box, then
	//the ray collides with the box at its origin
	if ( (rayOrigin > boxMin) && (rayOrigin < boxMax) )
	{
		//t is left at its default value of 0.0,
		//since the collision occurs at the beginning of the ray
		if ( (rayEnd > boxMin) && (rayEnd < boxMax) )
		{
			//If the end of the line segment is in the box too, then
			//the line intersects the box everywhere
			return IntersectEverywhere;
		}
		else
		{
			//Otherwise the line intersects within the line segment
			return IntersectInSegment;
		}
	}

	//Check each box plane in turn. We determine which planes need to be tested
	//by checking the components of rayDir one at a time

	//At most, three planes need to be tested for intersection, because
	//three planes face away from the ray's direction rayDir.
	//
	//If rayDir.X() == 0, then we don't need to test the box planes x = boxMin.X(), 
	//or x = boxMax.X() as the ray is parallel to them

	//Variable to store the smallest value of t.
	//We want the smallest value, because we want the first point of intersection with
	//the box
	Float smallestT = 0.0f;

	//Vector used to store the point of intersection
	Vector3D pointOnPlane;

	//Store the intersection type
	EParametricLineIntersect intersectionType = NoIntersect;


	// Min x (plane x = boxMin.X() )
	//
	// If rayOrigin.X() isn't less than min.X(), then the first collision can't
	// possibly be with the Min X plane, as the ray would have to collide
	// with some other plane first, or not collide at all
	//
	// If rayDir.X <= 0, then it can't possibly collide with the Min x plane
	// as it is pointing in the wrong direction
	//
	// These comments apply similarly for the other box faces
	if ( (rayOrigin.X() < boxMin.X()) &&  (rayDir.X() > 0) )
	{
		
		t = boxMin.X() - rayOrigin.X() 
			/ rayDir.X();

		//To lie within the corresponding face of the box, the y and z coordinates
		//of the point P(t) must satisfy
		//
		// min.Y() <= P(t).Y() <= max.Y()
		// min.Z() <= P(t).Z() <= max.Z()
		line.PointOnLine( t, pointOnPlane );

		if (   ((pointOnPlane.Y() >= boxMin.Y()) && (pointOnPlane.Y() <= boxMax.Y()) )
			&& ((pointOnPlane.Z() >= boxMin.Z()) && (pointOnPlane.Z() <= boxMax.Z()) ) )
		{
			if (  (t > 0.0f) && ((t < smallestT) || ( intersectionType != IntersectInSegment )))
			{
				t = smallestT;

				if ( t <= 1.0f )
				{
					intersectionType = IntersectInSegment;
				}
				else
				{
					intersectionType = IntersectOutSegment;
				}
			}
		}

	}

	//Max x
	if ( (rayOrigin.X() > boxMax.X()) &&  (rayDir.X() < 0) )
	{
		
		t = boxMax.X() - rayOrigin.X() 
			/ rayDir.X();

		line.PointOnLine( t, pointOnPlane );

		if (   ((pointOnPlane.Y() >= boxMin.Y()) && (pointOnPlane.Y() <= boxMax.Y()) )
			&& ((pointOnPlane.Z() >= boxMin.Z()) && (pointOnPlane.Z() <= boxMax.Z()) ) )
		{
			if (  (t > 0.0f) && ((t < smallestT) || ( intersectionType != IntersectInSegment )))
			{
				smallestT = t;

				if ( t <= 1.0f )
				{
					intersectionType = IntersectInSegment;
				}
				else
				{
					intersectionType = IntersectOutSegment;
				}
			}
		}

	}

	//Min y
	if ( (rayOrigin.Y() < boxMin.Y()) &&  (rayDir.Y() > 0) )
	{
		
		t = boxMin.Y() - rayOrigin.Y() 
			/ rayDir.Y();

		line.PointOnLine( t, pointOnPlane );

		if (   ((pointOnPlane.X() >= boxMin.X()) && (pointOnPlane.X() <= boxMax.X()) )
			&& ((pointOnPlane.Z() >= boxMin.Z()) && (pointOnPlane.Z() <= boxMax.Z()) ) )
		{
			if (  (t > 0.0f) && ((t < smallestT) || ( intersectionType != IntersectInSegment )))
			{
				t = smallestT;

				if ( t <= 1.0f )
				{
					intersectionType = IntersectInSegment;
				}
				else
				{
					intersectionType = IntersectOutSegment;
				}
			}
		}
	}

	//Max y
	if ( (rayOrigin.Y() > boxMax.Y()) &&  (rayDir.Y() < 0) )
	{
		
		t = boxMax.Y() - rayOrigin.Y() 
			/ rayDir.Y();

		line.PointOnLine( t, pointOnPlane );

		if (   ((pointOnPlane.X() >= boxMin.X()) && (pointOnPlane.X() <= boxMax.X()) )
			&& ((pointOnPlane.Z() >= boxMin.Z()) && (pointOnPlane.Z() <= boxMax.Z()) ) )
		{
			if (  (t > 0.0f) && ((t < smallestT) || ( intersectionType != IntersectInSegment )))
			{
				t = smallestT;

				if ( t <= 1.0f )
				{
					intersectionType = IntersectInSegment;
				}
				else
				{
					intersectionType = IntersectOutSegment;
				}
			}
		}
	}

	//Min z
	if ( (rayOrigin.Z() < boxMin.Z()) &&  (rayDir.Z() > 0) )
	{
		
		t = boxMin.Z() - rayOrigin.Z() 
			/ rayDir.Z();

		line.PointOnLine( t, pointOnPlane );

		if (   ((pointOnPlane.X() >= boxMin.X()) && (pointOnPlane.X() <= boxMax.X()) )
			&& ((pointOnPlane.Y() >= boxMin.Y()) && (pointOnPlane.Y() <= boxMax.Y()) ) )
		{
			if (  (t > 0.0f) && ((t < smallestT) || ( intersectionType != IntersectInSegment )))
			{
				t = smallestT;

				if ( t <= 1.0f )
				{
					intersectionType = IntersectInSegment;
				}
				else
				{
					intersectionType = IntersectOutSegment;
				}
			}
		}
	}

	//Max z
	if ( (rayOrigin.Z() > boxMin.Z()) &&  (rayDir.Z() < 0) )
	{
		
		t = boxMax.Z() - rayOrigin.Z() 
			/ rayDir.Z();

		line.PointOnLine( t, pointOnPlane );

		if (   ((pointOnPlane.X() >= boxMin.X()) && (pointOnPlane.X() <= boxMax.X()) )
			&& ((pointOnPlane.Y() >= boxMin.Y()) && (pointOnPlane.Y() <= boxMax.Y()) ) )
		{
			if (  (t > 0.0f) && ((t < smallestT) || ( intersectionType != IntersectInSegment )))
			{
				t = smallestT;

				if ( t <= 1.0f )
				{
					intersectionType = IntersectInSegment;
				}
				else
				{
					intersectionType = IntersectOutSegment;
				}
			}
		}
	}

	t = smallestT;

	if ( InRange(t, 0.0f, 1.0f) )
	{
		return IntersectInSegment;
	}
	else
	{
		return IntersectOutSegment;
	}

}
//End Intersects  ( const ParametricLine3D&, const AxisAlignedBoundingBox& )




}
