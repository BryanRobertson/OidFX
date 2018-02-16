//======================================================================================
//! @file         SphericalCoord3D.h
//! @brief        3D spherical coordinate class
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


#ifndef MATH_CYLINDRICALCOORD3D_H
#define MATH_CYLINDRICALCOORD3D_H


#include "Math/Common.h"


namespace Math
{

	//!@class	SphericalCoord3D
	//!@brief	Class representing 3D spherical coordinates
	class SphericalCoord3D
	{
		public:

			//Constructors
			inline SphericalCoord3D ( Scalar rho, Scalar phi, Scalar theta ) throw();
			inline explicit SphericalCoord3D ( const Point3D& point ) throw();

			//Static methods
			inline static void Point3DToSphericalRhoPhiTheta ( const Point3D& rect, Scalar& rho, Scalar& phi, Scalar& theta ) throw();

			//General methods
			void ToXYZ ( Scalar& x, Scalar& y , Scalar& z ) const throw();

			//Operator overloads
			Point3D operator Point3D ( ) const throw();

			//Accessors
			Scalar Rho	 ( ) const throw()	{ return m_rho;	  }
			Scalar Phi	 ( ) const throw() { return m_phi;	  }
			Scalar Theta ( ) const throw() { return m_theta; }
			

			//Mutators
			void Rho	( Scalar rho   ) throw() { m_rho = rho;	 }
			void Phi	( Scalar phi   ) throw() { m_phi = phi;	 }
			void Theta	( Scalar theta ) throw() { m_theta = theta; }
			

		private:

			Scalar m_rho;	//Distance from the origin
			Scalar m_phi;	//Rotation from the Z axis and the line o->p
			Scalar m_theta; //The angle the projection of the line onto the xy axis makes

	}; //end class SphericalCoord3D



    //=========================================================================
    //! @function    SphericalCoord3D::SphericalCoord3D
    //! @brief       SphericalCoord3D constructor
    //!              
    //! @param       rho	[in] Distance from the origin to the point
    //! @param       phi	[in] The angle that the directed line segment from the origin
	//!							 to the point, makes on the positive z-axis
    //! @param       theta	[in] The angle that the projection of the line from origin to 
	//!							 the point, makes on the x-y plane, which is just the standard
	//!							 polar theta.
    //!              
    //=========================================================================
	SphericalCoord3D::SphericalCoord3D ( Scalar rho, Scalar phi, Scalar theta )
	: m_rho ( rho ), m_phi (phi), m_theta (theta)
	{
	}
	//end SphericalCoord3D::Constructor (r,theta,z)



    //=========================================================================
    //! @function    SphericalCoord3D::SphericalCoord3D
    //! @brief       Construct a spherical coordinate from a point in 3D cartesian coordinates
    //!              
    //! @param       point [in] Point in 3D cartesian coordinates
	//!
    //=========================================================================
	SphericalCoord3D::SphericalCoord3D ( const Point3D& point )
	{
		Point3DToSphericalRhoPhiTheta ( point, m_rho, m_phi, m_theta );
	}
	//end SphericalCoord3D::Constructor (point)




    //=========================================================================
    //! @function    SphericalCoord3D::Point3DToSphericalRhoPhiTheta
    //! @brief       Convert a point in 3D cartesian coordinates, to 
	//!				 spherical rho, phi, theta
    //!              
    //! @param       point [in]		Point in 3D cartesian coordinates
    //! @param       rho   [out]	spherical rho
    //! @param       phi   [out]	spherical phi
    //! @param       theta [out]	spherical theta
    //=========================================================================
	void SphericalCoord3D::Point3DToSphericalRhoPhiTheta ( const Point3D& point, Scalar& rho, Scalar phi, Scalar& theta )
	{
		
		rho = point.Length();
		phi = arccos ( rect.Z() / rho );

		if ( rect.X() != 0.0f )
		{
			theta = ATan(rect.Y() / rect.X());
		}
		else
		{
			theta = 90.0f
		}

	}
	//end SphericalCoord3D::Point3DToSphericalRThetaZ



    //=========================================================================
    //! @function    SphericalCoord3D::ToXYZ
    //! @brief       Convert a spherical coordinate to cartesian x,y,z
    //!              
    //! @param       x [out] x coordinate 
    //! @param       y [out] y coordinate
    //! @param       z [out] z coordinate
    //=========================================================================
	void SphericalCoord3D::ToXYZ ( Scalar& x, Scalar& y, Scalar& z ) const
	{
		x = Rho() * Sin(Phi()) * Cos (Theta());
		y = Rho() * Sin(Phi()) * Sin (Theta());
		z = Rho() * Cos(Theta());
	}
	//end SphericalCoord3D::ToXYZ


    //=========================================================================
    //! @function    SphericalCoord3D::operator Point3D
    //! @brief       Convert a spherical coordinate to a 3D point in cartesian coordinates
    //!              
    //!              
    //! @return      A point in 3D cartesian coordinates, representing the
	//!				 same location in space
    //=========================================================================
	Point3D SphericalCoord3D::operator Point3D () const
	{
		Scalar x,y,z;
		ToXYZ ( x,y,z );

		return Point3D ( x,y,z );
	}
	//end SphericalCoord3D::operator Point3D


};//end namespace Math


#endif
//#ifndef MATH_SPHERICALCOORD3D