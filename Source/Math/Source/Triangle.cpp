//======================================================================================
//! @file         Triangle.cpp
//! @brief        Class representing a triangle
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 15 September 2005
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
#include "Math/Vector2D.h"
#include "Math/Triangle.h"


using namespace Math;



//=========================================================================
//! @function    Triangle::PointInTriangle ( const Math::Vector3D& point )
//! @brief       Indicates whether or not a point is inside a triangle
//!              
//! @param       line		[in]
//! @param       point		[in]
//!              
//! @return      true if the point is inside the triangle, false otherwise
//=========================================================================
bool Triangle::PointInTriangle ( const Math::Vector3D& point ) const throw()
{
	
	debug_assert ( Normal().Length() > 0.0f, "Triangle has zero length normal!" );

	if ( Normal().Length() == 0.0f )
	{
		return false;
	}

	//We discard one of the coordinates, based on which is the largest
	Vector2D verts[3];

	if (  (Normal().X() > Normal().Y())
		&&(Normal().X() > Normal().Z()) )
	{
		//X is the largest, so we discard it, and
		//rename the remaining axes x and y
		verts[0].X(V0().Y());
		verts[0].Y(V0().Z());

		verts[1].X(V1().Y());
		verts[1].Y(V1().Z());

		verts[2].X(V2().Y());
		verts[2].Y(V2().Z());
	}
	else if ( (Normal().Y() > Normal().X())
		&&    (Normal().Y() > Normal().Z()) )
	{
		//Y is the largest, so we discard it, and
		//rename the remaining axes x and y
		verts[0].X(V0().X());
		verts[0].Y(V0().Z());

		verts[1].X(V1().X());
		verts[1].Y(V1().Z());

		verts[2].X(V2().X());
		verts[2].Y(V2().Z());

	}
	else if ( (Normal().Z() > Normal().X())
		&&	  (Normal().Z() > Normal().Y()) )
	{
		//Z is the largest, so we discard it
		verts[0].X(V0().X());
		verts[0].Y(V0().Y());

		verts[1].X(V1().X());
		verts[1].Y(V1().Y());

		verts[2].X(V2().X());
		verts[2].Y(V2().Y());
	}

	Vector2D pointOfIntersection( point.X(), point.Y());

	//For each triangle edge, we check to see
	for ( UInt i=0; i < 2; ++i )
	{
		Vector2D e = verts[(i+1)%3]	- verts[i];
		Vector2D f = verts[(1+2)%3] - verts[i];
		Vector2D g = pointOfIntersection - verts[i];

		//Rotate e by 90 degrees, it doesn't matter in which direction
		//
		//Since we know the angle in advance, we'll just use the known values of cos ( 0.5 * pi )
		//and sin ( 0.5 * pi ), rather than using Sin and Cos
		Vector2D eRotated ( (e.X() * 6.1230317691118863e-017) + (e.Y() * 1.0f),
							(e.X()) + (e.Y() * 6.1230317691118863e-017) );

		//If this is false, then the point lies on the exterior of one of the edges
		if ( Vector2D::DotProduct( eRotated, f ) 
			* Vector2D::DotProduct( eRotated, g ) < 0.0f )
		{
			return false;
		}
	}

	return true;
}
//End  Triangle::PointInTriangle ( const Math::Vector3D& point )
