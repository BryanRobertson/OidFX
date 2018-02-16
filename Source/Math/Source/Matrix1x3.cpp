//======================================================================================
//! @file         Matrix1x3.cpp
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


#include <iostream>
#include "Math/Matrix1x3.h"
#include "Math/Matrix3x3.h"



using namespace Math;


//=========================================================================
//! @function    Matrix1x3::operator *=
//! @brief       Multiply *this by a 3x3 matrix
//!              
//! @param       rhs [in] Matrix to multiply this matrix by
//!              
//! @return      The result of multiplying this matrix by rhs
//=========================================================================
Matrix1x3& Matrix1x3::operator *= ( const Matrix3x3& rhs )
{
	Matrix1x3 mt ( *this );

	for ( UInt col = 0; col < ms_numCols; ++col )
	{
		Scalar sum = 0.0f;
		
		for ( UInt i = 0; i < ms_numCols; ++i )
		{
			sum += mt(i) * rhs(i,col);
		}

		m[col] = sum;
	}

	return (*this);
}
//end Matrix1x3:::operator* ( Matrix3x3 )

#ifdef MATH_IOSTREAM_SUPPORT
	//=========================================================================
	//! @function    operator << ( std::ostream&, const Matrix1x3& )
	//! @brief       Formatted output of a Matrix1x3 to an ostream
	//!             
	//! @param		 lhs [in] ostream to output this matrix to
	//! @param       rhs [in] Matrix to output
	//!              
	//! @return      os
	//=========================================================================
	std::ostream& operator << ( std::ostream& os, const Matrix1x3& rhs )
	{
		os << "|" << rhs(0) << " " << rhs(1) << " " << rhs(2) << "|";
		return os;
	}
	//end operator <<
#endif 
//#ifdef MATH_IOSTREAM_SUPPORT

