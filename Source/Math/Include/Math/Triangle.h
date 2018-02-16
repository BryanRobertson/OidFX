//======================================================================================
//! @file         Triangle.h
//! @brief        Class representing a triangle
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 07 September 2005
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

#ifndef MATH_TRIANGLE_H
#define MATH_TRIANGLE_H


#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/Plane3D.h"


//namespace Math
namespace Math
{


	//!@class	Triangle
	//!@brief	Class representing a triangle
	class Triangle
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			inline Triangle ( const Vector3D& v0, const Vector3D& v1, const Vector3D& v2 );


            //=========================================================================
            // Public methods
            //=========================================================================
			inline const Vector3D& V0() const throw();
			inline const Vector3D& V1() const throw();
			inline const Vector3D& V2() const throw();
			inline const Plane3D& Plane() const throw();
			inline const Vector3D& Normal() const throw();

			bool PointInTriangle ( const Math::Vector3D& point ) const throw();

		private:

            //=========================================================================
            // Private data
            //=========================================================================
			Vector3D			m_v0;
			Vector3D			m_v1;
			Vector3D			m_v2;

			Plane3D  m_plane;

	};
	//End class Triangle



	//=========================================================================
    //! @function    Triangle::Triangle
    //! @brief       Triangle contructor.
    //!              
	//! @param		 v0 [in]	First vertex
	//! @param		 v1 [in]	Second vertex
	//! @param		 v2 [in]	Third vertex
	//!
    //=========================================================================
	Triangle::Triangle ( const Vector3D& v0, const Vector3D& v1, const Vector3D& v2 )
		: m_v0(v0), m_v1(v1), m_v2(v2)
	{
		//Calculate the normal
		Vector3D v0v1 = v1 - v0;
		Vector3D v0v2 = v2 - v0;

		Vector3D normal;
		Vector3D::CrossProduct ( v0v1, v0v2, normal );

		normal.Normalise();

		//Create the plane
		m_plane = Plane3D ( v0, normal, true );

		//Create the bounding sphere


	}
	//End Triangle::Triangle


	//=========================================================================
    //! @function    Triangle::V0
    //! @brief       Get the first vertex of the triangle
	//!
	//! @return		 The first vertex of the triangle
    //=========================================================================
	const Vector3D& Triangle::V0() const
	{
		return m_v0;
	}
	//End Triangle::V0


	//=========================================================================
    //! @function    Triangle::V1
    //! @brief       Get the second vertex of the triangle 
	//!
	//! @return		 The second vertex of the triangle
    //=========================================================================
	const Vector3D& Triangle::V1() const
	{
		return m_v1;
	}
	//End Triangle::V1


	//=========================================================================
    //! @function    Triangle::V2
    //! @brief       Get the third vertex of the triangle
	//!
	//! @return		 The third vertex of the triangle
    //=========================================================================
	const Vector3D& Triangle::V2() const
	{
		return m_v2;
	}
	//End Triangle::V2


	//=========================================================================
    //! @function    Triangle::Plane
    //! @brief       Get the plane of the triangle
	//!
	//! @return		 The plane of the triangle
    //=========================================================================
	const Plane3D& Triangle::Plane() const
	{
		return m_plane;
	}
	//End Triangle::Plane


	//=========================================================================
    //! @function    Triangle::Normal
    //! @brief       Get the normal of the triangle
	//!
    //=========================================================================
	const Vector3D& Triangle::Normal() const
	{
		return m_plane.Normal();
	}
	//End Triangle::Normal


}
//end namespace Math


#endif
//#ifndef MATH_TRIANGLE_H
