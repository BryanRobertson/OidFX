//======================================================================================
//! @file         ParametricLine3D.h
//! @brief        Class to represent a 3D parametric line
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


#ifndef MATH_PARAMETRICLINE3D_H
#define MATH_PARAMETRICLINE3D_H

#include "Math/Vector3D.h"
#include "Math/ParametricLineShared.h"



//namespace Math
namespace Math
{

	//!@class	ParametricLine3D
	//!@brief	Class representing a 3D parametric line
	class ParametricLine3D
	{
		public:

			inline ParametricLine3D ( ) throw() { /* Initialization handled by constructors of members */ };
			inline ParametricLine3D ( const Point3D& begin, const Point3D& end ) throw();
	
			//Compute point on line at t. The line is traced from p0 to p1 as 0 <= t <= 1
			inline void PointOnLine ( Scalar t, Point3D& point ) const throw();

			//Accessors
			inline const Point3D& P0() const throw()	{ return m_p0; }
			inline const Point3D& P1() const throw()	{ return m_p1; }
			inline const Vector3D& V() const throw()	{ return m_v;  }
			
			//Mutators
			inline void Set ( const Point3D& p0, const Point3D& p1 ) throw();
			inline void P0  ( const Point3D& p0 ) throw();	
			inline void P1  ( const Point3D& p1 ) throw();

		private:

			Point3D		m_p0; //Start point of line
			Point3D		m_p1; //End point of line
			Vector3D	m_v;  //Direction vector of line segment

	}; //end class ParametricLine3D



    //=========================================================================
    //! @function    ParametricLine3D::ParametricLine3D
    //! @brief       Construct a parametric line between the points begin and end
    //!              
    //! @param       begin [in] Beginning of the line segment
    //! @param       end   [in] End of the line segment
    //!              
    //=========================================================================
	ParametricLine3D::ParametricLine3D ( const Point3D& begin, const Point3D& end )
	: m_p0 ( begin ), m_p1 ( end ), m_v( end - begin )
	{
	}
	//end ParamtericLine2D::Constructor



	//=========================================================================
	//! @function    ParametricLine3D::PointOnLine
	//! @brief       Return the point on the line at position t.
	//!				 
	//!				 Where 0 <= t <= 1. 
	//!				 0.0 Returns P0, 1.0 returns P1
	//!              
	//! @param       t		[in] Real number in the interval 0-1
	//!							 where 0 is the beginning of the line, and 1 is the end
	//!
	//! @param       point	[out] Point on the line at t
	//!              
	//=========================================================================
	void ParametricLine3D::PointOnLine ( Scalar t, Point3D& point ) const
	{
		//p(x,y,z) = p0 + v¹ * t
		point = P0() + (V() * t);
	}
	//end ParametricLine2D::PointOnLine



    //=========================================================================
    //! @function    ParametricLine3D::Set
    //! @brief       Set the parametric line between the points p0 and p1
    //!              
    //! @param       p0 [in] New beginning of line
    //! @param       p1 [in] New end of line
    //!             
    //=========================================================================
	void ParametricLine3D::Set ( const Point3D& p0, const Point3D& p1 ) throw()
	{ 
		m_p0 = p0; 
		m_p1 = p1; 
		m_v = m_p1 - m_p0;
	}
	//End ParametricLine3D::Set



    //=========================================================================
    //! @function    ParametricLine3D::P0
    //! @brief       Set the start point of the line
    //!              
    //! @param       p0 [in] New start point of line
    //=========================================================================
	void ParametricLine3D::P0  ( const Point3D& p0 ) throw()
	{ 
		m_p0 = p0; 
		m_v = m_p1 - m_p0; 
	}
	//End ParametricLine3D::P0



    //=========================================================================
    //! @function    ParametricLine3D::P1
    //! @brief       Set the end point of the line
    //!              
    //! @param       p1 [in] New end point of the line
    //=========================================================================
	void ParametricLine3D::P1  ( const Point3D& p1 ) throw()	
	{ 
		m_p1 = p1; 
		m_v = m_p1 - m_p0; 
	}
	//End ParametricLine3D::P1


}; 
//end namespace Math


#endif
//#ifndef MATH_PARAMETRICLINE3D_H