//======================================================================================
//! @file         Matrix2x2.h
//! @brief        2x2 matrix class
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
#include "Math/Matrix1x2.h"
#include "Math/Matrix2x2.h"



using namespace Math;



//=========================================================================
//! @function    Matrix2x2::Invert
//! @brief       Invert the matrix if possible. 
//!              
//!              
//! @return     true if succeeded
//!				false if inverse does not exist. Contents of matrix
//!				will be undefined if false was returned  
//=========================================================================
bool Matrix2x2::Invert ( )
{
	//Calculate determinant of the matrix 
	Scalar det =  m_00 * m_11 - m_01 * m_10;

	//If the determinant is zero then no inverse exists
	if ( IsZero ( det ) )
	{
		return false;
	}

	//Calculate the reciprocal of the determinant to avoid
	//calculating it for each element
	Scalar invDet = 1.0f / det;

	//A¯¹ = (1/det(A)) * | d  -b |
	//					 | -c  a |
	
	Set ( m_11 * invDet, -m_01 * invDet,
			-m_10 * invDet, m_00 * invDet );

	return true;

}
//end Matrix2x2::Invert ( )



//=========================================================================
//! @function    Matrix2x2::SwapColumn
//! @brief       Swap the column referenced by firstIndex by the column
//!				 referenced by secondIndex
//!              
//! @param       firstIndex  [in]
//! @param       secondIndex [in]
//!              
//=========================================================================
void Matrix2x2::SwapColumn ( UInt firstIndex, UInt secondIndex )
{
	//Make sure firstIndex and secondIndex are in range
	debug_assert ( (firstIndex < ms_numCols), "firstIndex out of range!" );
	debug_assert ( (secondIndex < ms_numCols), "secondIndex out of range!" ); 

	//Check to see if firstIndex and secondIndex are equal, and we can avoid swapping them
	if ( firstIndex == secondIndex )
	{
		//No need to swap, as firstIndex and secondIndex refer to the same column
		return;
	}

	//Swap the columns
	for ( UInt row = 0; row < ms_numRows; ++row )
	{
		std::swap ( m[row][firstIndex], m[row][secondIndex] );
	}
}
//end Matrix2x2::SwapColumn



//=========================================================================
//! @function    Matrix2x2::Determinate
//! @brief       Return the determinate of the matrix
//!
//! @return      The determinate of the matrix
//=========================================================================
Scalar Matrix2x2::Determinate ( ) const
{
	return ( m_00 * m_11 - m_01 * m_10 );
}
//end Matrix2x2::Determinate ( )


#ifdef MATH_IOSTREAM_SUPPORT
	//=========================================================================
	//! @function    operator <<
	//! @brief       Formatted output of a Matrix2x2 to an ostream
	//!              
	//! @param       out			[in] Output stream
	//! @param       matrixToOutput [in] Matrix to write to stream
	//!              
	//! @return      out
	//=========================================================================
	std::ostream& operator << ( std::ostream& out, const Matrix2x2& matrixToOutput )
	{
		out << std::endl;

		for ( UInt row = 0; row < matrixToOutput.ms_numRows; ++row )
		{

			out << "| ";

			for ( UInt col = 0; col < matrixToOutput.ms_numCols; ++col )
			{
				out << matrixToOutput( row, col ) << "  ";
			}

			out << "|" << std::endl;

		}

		return out;
	}
	//operator << ( std::ostream, Matrix2x2 )

#endif
//#ifdef MATH_IOSTREAM_SUPPORT

//=========================================================================
//! @function    Solve2x2System
//! @brief       Solves the system of equations A*X=B using Cramers rule
//!				 and returns the results in X
//!              
//! @param       A [in] 2x2 matrix
//! @param       B [in] 1x2 matrix
//! @param       X [out] 1x2 output matrix
//!              
//! @return      true if a solution exists
//!			     false if no solution could be found, in which case the contents of X are undefined
//=========================================================================
bool Solve2x2System ( const Matrix2x2& A, const Matrix1x2& B, Matrix1x2& X )
{
	Scalar detA = A.Determinate ( );

	if ( IsZero ( detA ) )
	{
		return false;
	}
	else
	{
		Matrix2x2 invA;
		//Invert A and store result in invA
		A.Inverse ( invA );

		//X = B * invA
		X(0) = B(0) * A(0,0) + B(1) * A(0,1);
		X(1) = B(0) * A(1,0) + B(1) * A(1,1); 
		return true;
	}
}
//end Solve2x2System