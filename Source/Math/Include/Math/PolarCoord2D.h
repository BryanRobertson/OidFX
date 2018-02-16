//======================================================================================
//! @file         PolarCoord2D.h
//! @brief        2D Polar coordinate class
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


#ifndef MATH_POLARCOORD2D_H
#define MATH_POLARCOORD2D_H


#include "Math/Common.h"


namespace Math
{

	//!@class	PolarCoord2D
	//!@brief	Class representing a 2D polar coordinate
	class PolarCoord2D
	{
		public:

			//Constructor
			inline PolarCoord2D ( Scalar r, Scalar theta ) throw();
			inline explicit PolarCoord2D ( Point2D& point ) throw();

			//Static methods
			inline static void Point2DToPolarRTheta ( const Point2D& rect, Scalar& r, Scalar& theta ) throw();

			//General methods
			void ToXY ( Scalar& x, Scalar& y ) const throw();

			//Operator overloads
			Point2D operator Point2D ( ) const throw();

			//Accessors
			Scalar R	 ( ) const throw()	{ return m_r;	  }
			Scalar Theta ( ) const throw() { return m_theta; }

			//Mutators
			void R		( Scalar r	   ) throw() { m_r = r;		 }
			void Theta	( Scalar theta ) throw() { m_theta = theta; }

		private:

			Scalar m_r;	  //The radi of the point
			Scalar m_theta; //The angle of rotation in radians

	};
	//end class PolarCoord2D



    //=========================================================================
    //! @function    PolarCoord2D::PolarCoord2D
    //! @brief       Construct a polar coordinate object from a distance and rotation
    //!              
    //! @param       r		[in] Radius of the point from the origin
    //! @param       theta	[in] Rotation around the origin
    //!              
    //=========================================================================
	PolarCoord2D::PolarCoord2D ( Scalar r, Scalar theta )
		: m_r(r), m_theta (theta)
	{
	}
	//end PolarCoord2D::Constructor



    //=========================================================================
    //! @function    PolarCoord2D::PolarCoord2D
    //! @brief       Construct a polar coordinate from a point
    //!              
    //! @param       point [in] 2D Point
    //!              
    //=========================================================================
	PolarCoord2D::PolarCoord2D ( Point2D& point )
	{
		Point2DToPolarRTheta ( point, m_r, m_theta );
	}
	//end PolarCoord::Constructor



    //=========================================================================
    //! @function    PolarCoord2D::Point2DToPolarRTheta
    //! @brief       Convert a point to polar r and theta
    //!              
    //! @param       point [in]	Point to convert to polar coordinates
    //! @param       r	   [out] Radius of point from the origin
    //! @param       theta [out] Rotation around the origin
    //!              
    //=========================================================================
	void PolarCoord2D::Point2DToPolarRTheta ( const Point2D& point, Scalar& r, Scalar& theta )
	{
		r = point.Length();

		if ( rect.X() != 0.0f )
		{
			theta = ATan(rect.Y() / rect.X());
		}
		else
		{
			theta = 90.0f;
		}
	}
	//end PolarCoord::Polar2DToPolarRTheta



    //=========================================================================
    //! @function    PolarCoord2D::ToXY
    //! @brief       Convert polar coordinates to x and y in cartesian coordinates
    //!              
    //! @param       x [out] x coordinate
    //! @param       y [out] y coordinate
    //!              
    //=========================================================================
	void PolarCoord2D::ToXY ( Scalar& x, Scalar& y ) const
	{
		x = R() * Cos(Theta());
		y = R() * Sin(Theta());
	}
	//end PolarCoord2D::ToXY



    //=========================================================================
    //! @function    PolarCoord2D::operator Point2D
    //! @brief       Return a 2D point in cartesian coordinates from a polar coordinate
    //!              
    //!              
    //! @return      A 2D point representing the same point in space as this polar coordinate
    //=========================================================================
	Point2D PolarCoord2D::operator Point2D ( ) const
	{
		//Convert to cartesian coordinates
		Scalar x,y;
		ToXY (x, y);

		return Point2D( x, y );
	}
	//end PolarCoord2D::operator Point2D ( )


};
//end namespace Math


#endif
//#ifndef MATH_POLARCOORD2D