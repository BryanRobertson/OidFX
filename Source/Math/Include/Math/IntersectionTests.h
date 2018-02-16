//======================================================================================
//! @file         IntersectionTests.h
//! @brief        Intersection tests for bounding volumes/planes/etc
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 21 July 2005
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

#ifndef MATH_INTERSECTIONTESTS_H
#define MATH_INTERSECTIONTESTS_H


//=========================================================================
// Foward declarations
//=========================================================================
namespace Math	{ class AxisAlignedBoundingBox; class Frustum; class Vector3D;
				  class BoundingSphere3D; class Triangle; class ParametricLine3D; enum EParametricLineIntersect; }


//namespace Math
namespace Math
{


    //=========================================================================
    // Constants
    //=========================================================================

    //=========================================================================
    // Function prototypes
    //=========================================================================
	bool Intersects ( const AxisAlignedBoundingBox& box, const Frustum& frustum  );
	bool Intersects ( const AxisAlignedBoundingBox& box1, const AxisAlignedBoundingBox& box2 );
	bool Intersects ( const AxisAlignedBoundingBox& box, const BoundingSphere3D& sphere );
	bool Intersects ( const BoundingSphere3D& sphere, const Triangle& triangle );
	bool Intersects ( const BoundingSphere3D& sphere1, const BoundingSphere3D& sphere2 );
	bool Intersects ( const BoundingSphere3D& sphere, const Math::Vector3D& velocity, const Triangle& triangle, Float& d );

	EParametricLineIntersect Intersects ( const ParametricLine3D& line, const AxisAlignedBoundingBox& box, Float& t );

	bool Intersects ( const ParametricLine3D& line, const Triangle& triangle );

	bool IntersectXZ ( const AxisAlignedBoundingBox& box1, const AxisAlignedBoundingBox& box2 );

}
//end namespace Math



#endif
//#ifndef MATH_INTERSECTIONTESTS_H

