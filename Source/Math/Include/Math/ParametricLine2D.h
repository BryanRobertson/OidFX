//======================================================================================
//! @file         ParametricLine2D.h
//! @brief        Class to represent a 2D parametric line
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


#ifndef MATH_PARAMETRICLINE2D_H
#define MATH_PARAMETRICLINE2D_H

#include "Math/Vector2D.h"
#include "Math/ParametricLineShared.h"


//namespace Math
namespace Math
{

	//!@class	ParametricLine2D
	//!@brief	Class representing a parametric 2D line
	class ParametricLine2D
	{
		public:

			//Constructors
			inline ParametricLine2D ( ) throw() { /* Members initialized by their default constructors */ };
			inline ParametricLine2D ( const Point2D& begin, const Point2D& end ) throw();
	
			//Compute point on line at t. The line is traced from p0 to p1 as 0 <= t <= 1
			inline void PointOnLine ( Scalar t, Point2D& point ) const throw();
            
			//Determine whether the line intersects another
			inline EParametricLineIntersect Intersection ( ParametricLine2D& line, Scalar& t1, Scalar& t1 ) const throw();
			inline EParametricLineIntersect Intersection ( ParametricLine2D& line, Point2D& pointOfIntersection ) const throw();

			//Accessors
			inline const Point2D& P0 ( ) const throw() { return m_p0; }
			inline const Point2D& P1 ( ) const throw() { return m_p1; }
			inline const Vector2D& V ( ) const throw() { return m_v;  }
			
			//Mutators
			inline void Set throw() ( const Point2D& p0, const Point2D& p1 );
			inline void P0  throw() ( const Point2D& p0 );
			inline void P1  throw() ( const Point2D& p1 );

		private:

			Point2D  m_p0; //Start point of line
			Point2D  m_p1; //End point of line
			Vector2D m_v;  //Direction vector of line segment
						//|v| = |p0->p1|

	}; 
	//end class ParametricLine2D

	

	//=========================================================================
	//! @function    ParametricLine2D::ParametricLine2D
	//! @brief       Construct a parametric line between points begin and end
	//!              
	//! @param       begin [in] Beginning of the line
	//! @param       end   [in] End of the line
	//=========================================================================
	ParametricLine2D::ParametricLine2D ( const Point2D& begin, const Point2D& end )
	: P0 ( begin ), P1 ( end ), V ( end - begin )
	{
	}
	//end ParamtericLine2D::Constructor



    //=========================================================================
    //! @function    ParametricLine2D::PointOnLine
    //! @brief       Return the point on the line at position t.
	//!				 Where 0 <= t <= 1
	//! 
	//!
	//!				 p(x,y) = p0 + v¹ * t
	//!
	//!				 Where p0 is the starting point of the line, 
	//!				 v¹ is the vector between p0 and the end point, 
	//!				 and t is a value between 0 and 1
    //!              
    //! @param       t		[in]	t value
    //! @param       point  [out]	Point on the line at t
    //=========================================================================
	void ParametricLine2D::PointOnLine ( Scalar t, Point2D& point ) const
	{
		//p(x,y) = p0 + v¹ * t
		point = P0() + (V() * t);
	}
	//end ParametricLine2D::PointOnLine

	

    //=========================================================================
    //! @function    ParametricLine2D::Intersection
    //! @brief       This function returns the intersection of two parametric line segments
	//!
	//!				Sets the value of t1 and t2 to the values on the parametric lines 
	//!				where any collision occurs
    //!              
    //! @param       line [in]	Line to test intersection against
    //! @param       t1	  [out] Value of t where intersection occurs on (*this)
    //! @param       t2	  [out] Value of t where intersection occurs on line
    //!              
    //! @return      NoIntersect if the lines do not intersect
	//!				 IntersectInSegment if the lines intersect within their line segments
	//!				 IntersectOutSegment if the lines intersect but not within the line segments
	//!				 IntersectEverywhere if the lines are the same and intersect everywhere    
    //=========================================================================
	EParametricLineIntersect ParametricLine2D::Intersection ( ParametricLine2D& line, Scalar& t1, Scalar& t2 ) const
	{

		/*
			Calculate the intersection of two parametric lines by solving a linear
			equations

			let p01(p0,p1) and p12(p2,p3) be the lines for which intersection is to be tested

			v1 = p1-p0
			v2 = p3-p1

			p01 = p0 + v1 * t1,  where 0 <= t1 <= 1
			p23 = p1 + v2 * t2,  where 0 <= t2 <= 1

			We are looking for the values of t1 and t2 where p01.x = p23.x and p01.y = p23.y

			x = p0.x + v1.x * t1 = p1.x * v2.x * t2
			y = p0.y + v1.y * t1 = p1.y * v2.y * t2

			v1.x * t1 - v2.x * t2 = p1.x - p0.x
			v1.y * t2 - v2.y * t2 = p1.y - p0.y

			We can use cramers rule to solve

			A * X = B

			       A             X                B
			| v0.x   v1.x |    | t1 |     | (p1.x - p0.x) |
			|             |  * |    |  =  |               |
			| v0.y   v1.y |    | t2 |     | (p1.y - p0.y) |

			X = A¯¹ * B

		*/

		//Step 1. Find the determinant of A
		//		  If the determinant is zero then there is no inverse to A
		//		  and the lines do not intersect. (or they are the same lines)
		//		  We may need to amend this to deal with identical lines
		//		  as they may intersect at one or many points along the segments
		Scalar detA = ( V().X() * line.V().Y() - V().Y() * line.V().X() );

		if ( Equal ( detA, 0.0f ) )
		{
			return NoIntersect;
		}

		//Step 2. Find t1 and t2 by multiplying B with the inverse of A
		//		  This calculation is the end result of multiplying the two matrices
		
		//t1 = (v1.y * ( p1.x - p0.x) ) - ( v1.x * ( p1.y - p0.y) ) / det ( A )
		t1 = ( line.V().Y() * ( P1().X() - P0().X() ) - ( line.V().X() * ( P1().Y() - P0().Y() ) ) / detA;
		//t2 = (v0.x * ( p1.y - p0.y) ) - ( v0.y * ( p1.y - p0.y) ) / det ( A )
		t2 = ( V().X() * ( P1.Y() - P0.Y() ) - ( V().Y() * ( P1().Y() - P0().Y() ) ) ) / detA;


		//Step 3. Check to see whether t1 and t2 are both in the range 0,1
		if ( (InRange ( t1, 0.0f, 1.0f )) && (InRange ( t2, 0.0f, 1.0f ) ) )
		{
			return IntersectInSegment;
		}
		else
		{
			return IntersectOutSegment;
		}

	}
	//end ParametricLine2D::Intersection



	//=========================================================================
    //! @function    ParametricLine2D::Intersection
    //! @brief       This function returns the point of intersection
	//!				 another parametric line makes on this one
    //!              
    //! @param       line				 [in]  Line to test intersection against
    //! @param       pointOfIntersection [out] Point where line intersects (*this)
    //!              
    //! @return      NoIntersect if the lines do not intersect
	//!				 IntersectInSegment if the lines intersect within their line segments
	//!				 IntersectOutSegment if the lines intersect but not within the line segments
	//!				 IntersectEverywhere if the lines are the same and intersect everywhere    
    //=========================================================================
	EParametricLineIntersect ParametricLine2D::Intersection ( ParametricLine2D& line, Point2D& pointOfIntersection ) const
	{
		Scalar t1 = 0.0f;
		Scalar t2 = 0.0f;

		//Use the other intersection method to find the values of t1 and t2 for which the lines collide
		UInt retVal = Intersection ( line, t1, t2 );
		//Use the equation p0 + v1 * t1 to calcuate point of intersection
		PointOnLine ( t1, pointOfIntersection );
			
		return retVal;
	}
	//end ParametricLine2D::Intersection



	//=========================================================================
    //! @function    ParametricLine2D::Set
    //! @brief       Set the parametric line between the points p0 and p1
    //!              
    //! @param       p0 [in] New beginning of line
    //! @param       p1 [in] New end of line
    //!             
    //=========================================================================
	void ParametricLine2D::Set ( const Point2D& p0, const Point2D& p1 ) throw()
	{ 
		m_p0 = p0; 
		m_p1 = p1; 
		m_v = p1 - p0; 
	}
	//End ParametricLine2D::Set



    //=========================================================================
    //! @function    ParametricLine2D::P0
    //! @brief       Set the start point of the line
    //!              
    //! @param       p0 [in] New start point of line
    //=========================================================================
	void ParametricLine2D::P0  ( const Point2D& p0 ) throw()
	{ 
		m_p0 = p0; 
		m_v = p1; 
		m_v -= p0; 
	}
	//End ParametricLine2D::P0



    //=========================================================================
    //! @function    ParametricLine2D::P1
    //! @brief       Set the end point of the line
    //!              
    //! @param       p1 [in] New end point of the line
    //=========================================================================
	void ParametricLine2D::P1  ( const Point2D& p1 ) throw()	
	{ 
		m_p1 = p1; 
		m_v = p1; 
		m_v -= p0; 
	}
	//End ParametricLine2D::P1


};
//end namespace Math3D

#endif //#ifndef MATH_PARAMETRICLINE2D_H