//======================================================================================
//! @file         Matrix1x3.h
//! @brief        1x3 Matrix class
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 27 May 2005
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

#ifndef MATH_MATRIX1X3_H
#define MATH_MATRIX1X3_H

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Math/Math.h"


//namespace Math
namespace Math
{

    //=========================================================================
    // Forward declaration
    //=========================================================================
	class Matrix3x3;


	//!@class	Matrix1x3
	//!@brief	1x3 matrix class
	class Matrix1x3
	{
		public:
			
			//Constructors
			Matrix1x3 ( ) throw() { /*default constructor has no implementation*/ }
			explicit Matrix1x3 ( Scalar m00, Scalar m01, Scalar m02 ) throw () : m_00 (m00), m_01 (m01), m_02 (m02) {  }

			//
			inline void Set (  Scalar m00, Scalar m01, Scalar m02 ) throw () { m_00 = m00; m_01 = m01; m_02 = m02; }

			//operator overloads
			inline Matrix1x3 operator *  ( const Matrix3x3& rhs ) const throw ();
			Matrix1x3& operator *= ( const Matrix3x3& rhs ) throw ();

			inline Scalar operator () ( UInt col ) const throw ()	  { return m[col]; }
			inline Scalar& operator() ( UInt col ) throw ()			  { return m[col]; }

			//friend functions
			#ifdef MATH_IOSTREAM_SUPPORT
				friend std::ostream& operator << ( std::ostream& os, const Matrix1x3& rhs ); 
			#endif

			//Public static variables
			static const UInt ms_numRows = 1;
			static const UInt ms_numCols = 3;


		private:

			union 
			{
				Scalar m[3];

				struct
				{
					Scalar m_00, m_01, m_02;
				};
			};

	};
	//end class Matrix1x3



	//=========================================================================
	//! @function    Matrix1x3::operator *
	//! @brief       Return the result of multiplying a matrix by a 3x3 matrix
	//!              
	//! @param       rhs [in] Matrix to multiply this matrix by
	//!              
	//! @return      The result of multiplying this matrix by rhs
	//=========================================================================
	Matrix1x3 Matrix1x3::operator* ( const Math::Matrix3x3& rhs ) const
	{
		return Matrix1x3( *this ) *= rhs;
	}
	//end Matrix1x3:::operator* ( Matrix3x2 )


};
//end namespace Math

#endif 
//#ifndef MATH_MATRIX1X3_H
