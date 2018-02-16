//======================================================================================
//! @file         CylindricalCoord3D.h
//! @brief        3D cylindrical coordinate class
//!			        
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 24 May 2005
//! @copyright    Bryan Robertson
//======================================================================================


#ifndef MATH_CYLINDRICALCOORD3D_H
#define MATH_CYLINDRICALCOORD3D_H

#include "Math/Math.h"


namespace Math
{

	//!@class	CylindricalCoord3D
	//!@brief	Class representing cylindrical coordinates
	class CylindricalCoord3D
	{
		public:

			//Constructors
			inline CylindricalCoord3D ( Scalar r, Scalar theta, Scalar z ) throw();
			explicit inline CylindricalCoord3D ( const Point3D& point ) throw();

			//Static methods
			inline static void Point3DToCylindricalRThetaZ ( const Point3D& point, Scalar& r, Scalar& theta, Scalar& z ) throw();

			//General methods
			void ToXYZ ( Scalar& x, Scalar& y , Scalar& z ) const throw();

			//Operator overloads
			Point3D operator Point3D ( ) const throw();

			//Accessors
			Scalar R	 ( ) const throw()	{ return m_r;	  }
			Scalar Theta ( ) const throw() { return m_theta; }
			Scalar Z	 ( ) const throw() { return m_z;	  }

			//Mutators
			void R		( Scalar r	   ) throw() { m_r = r;		 }
			void Theta	( Scalar theta ) throw() { m_theta = theta; }
			void Z		( Scalar z	   ) throw() { m_z = z;		 }

		private:

			Scalar m_r;		//!< The radii of the point
			Scalar m_theta; //!< The angle of rotation in radians
			Scalar m_z;		//!< The distance up the z axis

	}; //end class CylindricalCoord3D



	//=========================================================================
	//! @function    CylindricalCoord3D::Constructor
	//! @brief       Initialise a cylindrical coordinate from r, theta, z
	//!              
	//! @param		 r	   [in]	Radius of the point
	//! @param		 theta [in]	Rotation around the origin in radians
	//! @param		 z	   [in] Distance up the Z axis
	//=========================================================================
	CylindricalCoord3D::CylindricalCoord3D ( Scalar r, Scalar theta, Scalar z )
		: m_r(r), m_theta(theta), m_z(z)
	{
	}
	//end CylindricalCoord3D::Constructor (r,theta,z)



	//=========================================================================
	//! @function    CylindricalCoord3D::Constructor
	//! @brief       Initialise a cylindrical coordinate from a Point3D representing a point
	//!              
	//! @param		 point [in] Point representing a point in 3D space
	//=========================================================================
	CylindricalCoord3D::CylindricalCoord3D ( const Point3D& point )
	{
		Point3DToCylindricalRThetaZ ( point, m_r, m_theta, m_z );
	}
	//end CylindricalCoord3D::Constructor (point)



	//=========================================================================
	//! @function    CylindricalCoord3D::Point3DToCylindricalRThetaZ
	//! @brief       Convert a Point to cylindrical r, theta, z
	//!              
	//! @param		 point [in]		Point to convert to cylindrical coordinates  
	//! @param		 r	   [out]	Radius of the point
	//! @param		 theta [out]	Rotation around the origin in radians
	//! @param		 z	   [out]	Distance up the Z axis
	//=========================================================================
	void CylindricalCoord3D::Point3DToCylindricalRThetaZ ( const Point3D& point, Scalar& r, Scalar& theta, Scalar& z )
	{
		r = point.Length();

		if ( point.X() != 0.0f )
		{
			theta = ATan( rect.Y() / rect.X() );
		}
		else
		{
			theta = 90.0f;
		}

		z = point.Z();
	}
	//end CylindricalCoord3D::Point3DToCylindricalRThetaZ


	//=========================================================================
	//! @function    CylindricalCoord3D::ToXYZ
	//! @brief       Convert a cylindrical coordinate to cartesian x,y,z
	//!               
	//! @param		 x	   [out]	x coordinate
	//! @param		 y	   [out]	y coordinate
	//! @param		 z	   [out]	z coordinate
	//=========================================================================
	void CylindricalCoord3D::ToXYZ ( Scalar& x, Scalar& y, Scalar& z ) const
	{
		x = R() * Cos(Theta());
		y = R() * Sin(Theta());
		z = Z();
	}
	//end CylindricalCoord3D::ToXYZ


	//=========================================================================
	//! @function    CylindricalCoord3D::ToXYZ
	//! @brief       Convert a cylindrical coordinate to a Point3D
	//!               
	//! @return		 A point in cartesian coordinates
	//=========================================================================
	Point3D CylindricalCoord3D::operator Point3D () const
	{
		Scalar x,y,z;
		ToXYZ( x,y,z );

		return Point3D( x,y,z );
	}
	//end CylindricalCoord3D::operator Point3D



};//end namespace Math

#endif