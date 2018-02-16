//======================================================================================
//! @file         Matrix3x3.h
//! @brief        3x3 Matrix class
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 24 May 2005
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
#include <algorithm> //std::swap
#include "Math/Vector3D.h"
#include "Math/Matrix1x3.h"
#include "Math/Matrix3x3.h"
#include "Math/Quaternion.h"



using namespace Math;



//=========================================================================
//! @function    Matrix3x3::Constructor
//! @brief       Construct a 3x3 matrix from a quaternion
//!              
//! @param       q [in] Quaternion from which to create the matrix     
//=========================================================================
Matrix3x3::Matrix3x3 ( const Quaternion& q )
{
	m_00 = 1.0f - 2.0f * (q.Y()*q.Y());	
	m_01 = 2.0f * (q.X() * q.Y()) + (q.W() * q.Z());
	m_02 = (2.0f * q.X() * q.Z()) - (2.0f * q.W() * q.Y());
	//m_03 = 0.0f;

	m_10 = (2.0f * q.X() * q.Y()) - (2.0f * q.W() * q.Z());
	m_11 = 1.0f - (2.0f * q.X() * q.X()) - (2.0f * q.Z() * q.Z());
	m_12 = (2.0f * q.Y() * q.Z()) + (2.0f * q.W() * q.Z());
	//m_13 = 0.0f;

	m_20 = (2.0f * q.X() * q.Z()) + (2.0f * q.W() * q.Y());
	m_21 = (2.0f * q.Y() * q.Z()) - (2.0f * q.W() * q.Z());
	m_22 = 1.0f - (2.0f * q.X() * q.X()) - (2.0f * q.Y() * q.Y());
	//m_23 = 0.0f;

	//m_30 = 0.0f;
	//m_31 = 0.0f;
	//m_32 = 0.0f;
	//m_33 = 0.0f;
}
//End Matrix3x3::Constructor



//=========================================================================
//! @function    Matrix3x3::Invert
//! @brief       Invert a 3x3 matrix, if possible
//!					
//!				 If the matrix cannot be inverted then this method will return false
//!				 and the contents of result will be undefined		 
//!
//! @return		 true if the matrix was inverted successfully
//!				 false if the matrix could not be inverted
//=========================================================================
bool Matrix3x3::Invert ( )
{
	//Calculate determinate of the matrix 
	Scalar det =  m_00 * ( m_11 * m_22 - m_21 * m_12 ) 
				- m_01 * ( m_10 * m_22 - m_20 - m_12 )
				- m_02 * ( m_10 * m_21 - m_20 * m_11 );

	//If the determinant is zero then no inverse exists
	if ( IsZero ( det ) )
	{
		return false;
	}

	//Calculate the reciprocal of the determinant to avoid
	//calculating it for each element
	Scalar invDet = 1.0f / det;

	//Calculate the inverse of the matrix using the determinant

	//Make a copy of current matrix so that we can read the unchanged values
	//
	//Readability has been chosen over efficiency until a profiler indicates this method is too inefficient
	Matrix3x3 mt( *this );
	
	//http://mathworld.wolfram.com/MatrixInverse.html
	//http://mathworld.wolfram.com/mimg1065.gif
	//Check the above links if you can't see what is going on here

	//TODO: Check this thoroughly for errors
	m_00 = invDet * (mt(1,1) * mt(2,2) - mt(1,2) * mt(2,1));
	m_01 = invDet * (mt(0,2) * mt(2,1) - mt(0,1) * mt(2,2));
	m_02 = invDet * (mt(0,1) * mt(1,2) - mt(0,2) * mt(1,1));

	m_10 = invDet * (mt(1,2) * mt(2,0) - mt(1,0) * mt(2,2));
	m_11 = invDet * (mt(0,0) * mt(2,2) - mt(0,2) * mt(2,0));
	m_12 = invDet * (mt(0,2) * mt(1,0) - mt(0,0) * mt(1,2));

	m_20 = invDet * (mt(1,0) * mt(2,1) - mt(1,1) * mt(2,0));
	m_21 = invDet * (mt(0,1) * mt(2,0) - mt(0,0) * mt(2,1));
	m_22 = invDet * (mt(0,0) * mt(1,1) - mt(0,1) * mt(1,0));

	return true;

}
//end Matrix3x3::Invert ( )



//=========================================================================
//! @function    Matrix3x3::Inverse
//! @brief       Swap the column indexed by firstIndex, with the column indexed by secondIndex
//!				
//!	@param		 firstIndex  [in] First column index
//! @param		 secondIndex [in] Second column index
//=========================================================================
void Matrix3x3::SwapColumn ( UInt firstIndex, UInt secondIndex )
{
	//Make sure firstIndex and secondIndex are in range
	debug_assert ( (firstIndex < ms_numCols) && (secondIndex < ms_numCols), "Index out of range!" ); 

	//Check to see if firstIndex and secondIndex are equal, and we can avoid swapping them
	if ( firstIndex == secondIndex )
	{
		//No need to swap, as firstIndex and secondIndex refer to the same column
		return;
	}

	//Swap the columns
	for ( UInt row = 0; row < ms_numCols; ++row )
	{
		std::swap ( m[row][firstIndex], m[row][secondIndex] );
	}
}
//end Matrix3x3::SwapColumn



//=========================================================================
//! @function    Matrix3x3::Determinate
//! @brief       Return the determinate of the matrix
//!				
//! @return		 The determinate of the matrix
//=========================================================================
Scalar Matrix3x3::Determinate ( ) const
{
	return (  m_00 * ( m_11 * m_22 - m_21 * m_12 ) 
			- m_01 * ( m_10 * m_22 - m_20 - m_12 )
			- m_02 * ( m_10 * m_21 - m_20 * m_11 ) );
}
//end Matrix3x3::Determinate ( )


//=========================================================================
//! @function    Matrix3x3::Transpose ( )
//! @brief       Transpose the matrix
//!
//!				 Swap the rows of the matrix with the columns, such that m[i,j] becomes m[j,i]
//!				
//=========================================================================
void Matrix3x3::Transpose ( )
{
	std::swap ( m_01 , m_10 );
	std::swap ( m_02 , m_20 );
	std::swap ( m_12 , m_21 );
}
//Matrix3x3::Transpose ( )



//=========================================================================
//! @function   Solve3x3System ( )
//! @brief      Solves the system of equations A*X=B and returns the results in X
//!
//!	@param		A[in]
//! @param		B[in]
//! @param		X[out]
//!
//! @return		true if a solution exists
//!				false if no solution could be found, in which case the contents of X are undefined
//=========================================================================
bool Math::Solve3x3System ( const Matrix3x3& A, const Matrix1x3& B, Matrix1x3& X )
{
	Scalar detA = A.Determinate ( );

	if ( IsZero ( detA ) )
	{
		//If the determinate of A is zero, then there is no solution
		return false;
	}
	else
	{
		Scalar invDetA = 1.0f / detA;

		//TODO: Double check all of this for errors ( Solve3x3System )

		/*			 
						| b0	a01	  a02 |
						|				  |
			x = Det	  ( | b1	a11	  a12 | )
						|				  |
						| b2	a21	  a22 |

			x =  b0 * ( a11 * a22 - a21 * a12 ) - a01 * ( b1 * a22 - b2 * a12 ) - a02 * ( b1 * a21 - b2 * a11 )
		*/
		X(0) = ( B(0) * ( A(1,1) * A(2,2) - A(2,1) * A(1,2))
						  -A(0,1) * ( B(1)   * A(2,2) - B(2)   * A(1,2))
						  -A(0,2) * ( B(1)   * A(2,1) - B(2)   * A(1,1))) * invDetA;

		/*
						| a00	b0  a02 |
						|				|
			y = Det   ( | a10	b1  a12 | )
						|				|
						| a20	b2	a22 |
		*/
		X(1) = (  A(0,0) * ( B(1  ) * A(2,2) - B(2  ) * A(1,2)) 
						-B(0)   * ( A(1,0) * A(2,2) - A(2,0) * A(1,2))	
						-A(0,2) * ( A(1,0) * B(2)  - A(2,0)  * B(1))) * invDetA;


		/*
						| a00	a01  b0 |
						|				|
			z = Det(    | a10	a11  b1 | )
						|				|
						| a20	a21	 b2 |
		*/
		X(2) = ( A(0,0)  * ( A(1,1) * B(2)   - A(2,1) * B(1))
							-A(0,1) * ( A(1,0) * B(2)   - A(2,0) * B(1)) 
							-A(0,2) * ( A(1,0) * A(2,1) - A(2,0) * A(1,1))) * invDetA;

		return true;
	}
}
//end Solve3x3System



//=========================================================================
//! @function    operator << (std::ostream&, const Matrix3x3& )
//! @brief       Formatted output of a Matrix3x3 to a standard ostream
//!              
//! @param       out			[in] ostream to write to
//! @param       matrixToOutput [in] Matrix to write
//!              
//! @return      out, after having the matrix written to it
//=========================================================================
std::ostream& operator << ( std::ostream& out, const Matrix3x3& matrixToOutput )
{
	out << std::endl;

	for ( UInt row = 0; row < 3; ++row )
	{

		out << "| ";

		for ( UInt col = 0; col < 3; ++col )
		{
			out << matrixToOutput( row, col ) << "  ";
		}

		out << "|" << std::endl;

	}

	return out;
}
//operator << ( std::ostream, Matrix3x3 )
