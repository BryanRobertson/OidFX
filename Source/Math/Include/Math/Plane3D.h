//======================================================================================
//! @file         Plane3D.h
//! @brief        Class representing a 3D plane
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 25 May 2005
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


#ifndef MATH3D_PLANE_H
#define MATH3D_PLANE_H

#include "Math/Math.h"
#include "Math/Matrix4x4.h"
#include "Math/ParametricLineShared.h"
#include "Math/ParametricLine3D.h"


//namespace Math
namespace Math
{


	//!@class	Plane3D
	//!@brief	Class representing a 3D plane
	class Plane3D
	{
		public:

			//Constructors
			inline Plane3D ( ) throw()  { /* Initialization handled by member default constructors */ }
			explicit inline Plane3D ( Scalar a, Scalar b, Scalar c, Scalar d, bool normalise = false ) throw();
			explicit inline Plane3D ( const Point3D& point, const Vector3D& normal, bool normalise = false ) throw();

			//Normalise the plane
			inline void Normalise ( ) throw();

			//Compute which side of a plane a point is on
			inline Scalar PointInPlane ( const Point3D& point  ) const throw();

			//Check whether a line intersects a plane
			inline EParametricLineIntersect Intersection ( const ParametricLine3D& line, Scalar& t, Point3D& point ) const throw();

			//Operator overloads
			inline Plane3D& operator *= ( const Matrix4x4& mat ) throw();
			friend Plane3D  operator * ( const Plane3D& plane, const Matrix4x4& mat );

			//Accessors
			const Vector3D& Normal ( ) const throw()  { return m_normal; }
			Scalar A() const throw()				  { return Normal().X(); }
			Scalar B() const throw()				  { return Normal().Y(); }
			Scalar C() const throw()				  { return Normal().Z(); }
			Scalar D() const throw()				  { return m_d; }

			//Mutators
			inline void Set ( Scalar a, Scalar b, Scalar c, Scalar d );
			void SetNormal ( const Vector3D& normal ) throw() { m_normal = normal; }
			void SetD	   ( Scalar d ) throw()				  { m_d = d;		   }

			friend std::ostream& operator << ( std::ostream& os, const Plane3D& plane );

		private:

			Vector3D	m_normal; // Normal to the plane ( not necessarily a unit vector )
			Float		m_d;	  // Distance from origin

	};
	//end class Plane3D


    //=========================================================================
    // Function prototypes of non-member functions
    //=========================================================================
	inline std::ostream& operator << ( std::ostream& os, const Plane3D& plane );
	inline Plane3D operator * ( const Plane3D& plane, const Matrix4x4& mat ) throw();


    //=========================================================================
    //! @function    Plane3D::Plane3D
    //! @brief       Construct a plane from a point and normal
    //!              
    //! @param       point		[in] A point on the plane
    //! @param       normal		[in] Vector normal to the plane
    //! @param       normalise  [in] If this is true, then normal will be normalised
    //!								 otherwise, normal will be left as-is
    //=========================================================================
	Plane3D::Plane3D ( const Point3D& point, const Vector3D &normal, bool normalise )
		: m_normal (normal)
	{
		m_d = -(Vector3D::DotProduct(m_normal, point));

		if ( normalise )
		{
			Normalise ( );
		}
	}
	//end Plane3D::Constructor


    //=========================================================================
    //! @function    Plane3D::Plane3D
    //! @brief       Construct a plane from its A, B, C, and D values
    //!              
    //! @param       a [in]
    //! @param       b [in]
    //! @param       c [in]
    //! @param       d [in]
    //!              
    //=========================================================================
	Plane3D::Plane3D ( Scalar a, Scalar b, Scalar c, Scalar d, bool normalise  )
		: m_normal(a,b,c), m_d(d)
	{
		if ( normalise )
		{
			Normalise();
		}
	}
	//End Plane3D::Plane3D


    //=========================================================================
    //! @function    Plane3D::Normalise
    //! @brief       Normalise the plane
    //!           
    //=========================================================================
	void Plane3D::Normalise ()
	{
		//Get the length
		Float length = m_normal.Length();

		//Avoid a divide by zero
		if ( length == 0.0f )
		{
			return;
		}

		//Divide the plane components by the length
		m_normal /= length;
		m_d /= length;
	}
	//End Plane3D::Normalise



	//=========================================================================
	//! @function    Plane3D::PointInPlane
	//! @brief       Determines which half space the point is in, in relation to the plane
	//!				 or if the point is in the plane
	//!              
	//! @param       point [in] Point to be compared against the plane
	//!              
	//! @return      If the return value is positive, then the point is in the
	//!				 positive half-space of the plane
	//!				 If the return value is zero, then the point lies on the plane
	//!				 If the return value is negative, then the point is in the 
	//!				 negative half-space of the plane
	//=========================================================================
	Scalar Plane3D::PointInPlane ( const Point3D& point ) const
	{
		return  ( Vector3D::DotProduct(m_normal, point) + D() );
	}
	//end Plane3D::PointInPlane



	//=========================================================================
	//! @function	 Plane3D::Intersection
	//! @brief       Determines whether the passed 3D parametric line
	//!				 intersects with the plane
	//!              
	//! @param       line	[in] Line to test against the plane
	//! @param       t		[out] Parametric line t value on the line where the collision occurs, if any
	//! @param       point	[out] Point at which the collision occurs, if any
	//!              
	//! @return      NoIntersect if the plane and line do not intersect at all
	//!				 IntersectEverywhere if the line lies on the plane
	//!				 IntersectInSegment if the line intersects the plane in its segment
	//!				 IntersectOutSegment if the line intersects the plane, but not in its segment 
	//!
	//=========================================================================
	EParametricLineIntersect Plane3D::Intersection ( const ParametricLine3D& line, Scalar& t, Point3D& point ) const
	{
		/*
		Dot the plane normal with the vector of the line to determine
		whether or not they are parallel. If they are parallel, they can't intersect
		unless the line lies in the plane
		
		We can find this by finding out whether the normal of the plane is perpendicular
		to the vector representing the line from p0 to p1 of the line. Since the normal
		is also perpendicular to the plane
		*/
		Scalar planeNormalDotLine = Vector3D::DotProduct ( line.V(), Normal() );

		//If the dot product with the normal is zero then the vector from p0 to p1 is
		//perpendicular to the normal
		if ( IsZero(planeNormalDotLine) )
		{
			//Check to see whether the plane lies in the plane
			if ( IsZero(PointInPlane(line.P0())) )
			{
				return IntersectEverywhere;
			}
			else
			{
				return NoIntersect;
			}
		}

		/*	Calculate the point of intersection

					Equation of a parametric line:
						p = p0 + v*t, where 0 <= t <= 1

					Component wise:
						x = x0 + vx * t
						y = y0 + vy * t
						z = z0 + vz * t

					Equation of a 3D plane:
						n . ( p - p0 ) = 0
						nx( x-x0 ) + ny( y-y0 ) + nz( z-z0 ) = 0
						
						nx*x + ny*y + nz*z + (-nx*x0 - ny*y0 - nz*z0 ) = 0
						
						or in general form:
						a*x + b*y + c*z + d = 0
						
					Intersection of a parametric line and a plane:
						a*(x0+vx*t) + b*(y0+vy*t) + c*(z0+vz*t) + d = 0
					
					Solving for t
						t = -(a*x0 + b*y0 + c*z0 + d) / ( a*vx + b*vy + c*vz )

		*/

		t = - ( Normal().X() * line.P0().X() + Normal().Y() * line.P0().Y() + Normal().Z() * line.P0().Z() -
			  ( Normal().X() * line.P0().X()) + Normal().Y() * line.P0().Y() + Normal().Z() * line.P0().Z() ) / planeNormalDotLine;

		
		//Calculate the point of intersection using the normal parametric line equation
		//	p = p0 + v*t
		line.PointOnLine(t, point);
		
		//If t is in the range 0.0 to 1.0, then the intersection occurs in the line segment
		//otherwise the the intersection only occurs if the line is considered to be infinite
		if ( InRange(t, 0.0f, 1.0f) )
		{
			return IntersectInSegment;
		}
		else
		{
			return IntersectOutSegment;
		}

	}
	//end Plane3D::Intersection



    //=========================================================================
    //! @function    Plane3D::Set
    //! @brief       Set the plane contents
    //!              
    //! @param       a [in] 
    //! @param       b [in]
    //! @param       c [in]
    //! @param       d [in]
    //!              
    //=========================================================================
	void Plane3D::Set ( Scalar a, Scalar b, Scalar c, Scalar d )
	{
		m_normal.Set(a,b,c);
		m_d = d;
	}
	//End Plane3D::Set



    //=========================================================================
    //! @function    Plane3D::operator *=
    //! @brief       Multiplies a plane by a 4x4 matrix
	//!
	//!				 Similar to multiplying a vector by a 4x4 matrix,
	//!				 except that planes are transformed by multiplying
	//!				 with the inverse transpose of a matrix.
	//!
	//!				 This method automatically extracts the inverse transpose from
	//!				 mat, it is not necessary to do it manually.
	//!
	//!				 Note that this function uses Matrix4x4::FastInvert, so it
	//!				 will break if mat isn't orthogonal
    //!              
    //! @param       mat [in] Matrix to mutiply the plane by 
    //!              
    //! @return      *this
    //=========================================================================
	Plane3D& Plane3D::operator *= ( const Matrix4x4& mat )
	{
		Matrix4x4 invTransposeMat( mat );
		invTransposeMat.FastInvert();
		

		//invTransposeMat.Transpose();

		Scalar a = A() * mat(0,0) + B() * mat(1,0) + C() * mat(2,0) + D() * mat(3,0);
		Scalar b = A() * mat(0,1) + B() * mat(1,1) + C() * mat(2,1) + D() * mat(3,1);
		Scalar c = A() * mat(0,2) + B() * mat(1,2) + C() * mat(2,2) + D() * mat(3,2);
		Scalar d = A() * mat(0,3) + B() * mat(1,3) + C() * mat(2,3) + D() * mat(3,3);

		Set ( a, b, c, d );

		return *this;

	}
	//End Plane3D::operator *=


    //=========================================================================
    //! @function    operator * ( const Plane3D&, const Matrix4x4& )
    //! @brief       Return the result of multipying this plane by a 4x4 matrix
    //!              
	//!				 Note that planes are multiplied by the inverse transpose of
	//!
	//!				 This method automatically extracts the inverse transpose from
	//!				 mat, it is not necessary to do it manually.
	//!
    //! @param       plane [in] Plane to be multiplied
    //! @param       mat   [in] Matrix to multiply the plane by
    //!              
    //! @return      Result of multiplying plane by mat
    //=========================================================================
	Plane3D operator * ( const Plane3D& plane, const Matrix4x4& mat )
	{
		return Plane3D( plane ) *= mat;
	}
	//End operator *



    //=========================================================================
    //! @function    operator <<
    //! @brief       Formatted output of a Plane3D to an output stream
    //!              
    //! @param       os		[in]	
    //! @param       plane	[in]	
    //!              
    //! @return      os
    //=========================================================================
	std::ostream& operator << ( std::ostream& os, const Plane3D& plane )
	{
		os << plane.A() << " " 
		   << plane.B() << " "
		   << plane.C() << " "
		   << plane.D();

		return os;
	}
	//End operator <<


};
//end namespace Math


#endif
//#ifndef MATH_PLANE3D