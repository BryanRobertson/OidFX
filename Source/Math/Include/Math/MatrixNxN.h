//======================================================================================
//! @file         MatrixNxN.h
//! @brief        NxN Matrix template class
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


#ifndef MATH_MATRIXNXN_H
#define MATH_MATRIXNXN_H

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Math/Math.h"


//namespace Math
namespace Math
{


    //=========================================================================
    // Forward declarations
    //=========================================================================


	//!@class	MatrixNxN
	//!@brief	Template class for an arbitrarily sized matrix
	//!
	//!			This is mainly supplied to make guassian elimination more readable
	//!			rather than to be used as a matrix
	template <UInt cols, UInt rows>
	class Matrix
	{
		public:
			
			//Constructors
			Matrix ( ) throw() { /*default constructor has no implementation*/ }
			
			//operator overloads
			inline Scalar operator () ( UInt row, UInt col ) const throw ();   
			inline Scalar& operator () ( UInt row, UInt col ) throw ();		

			//Elementary row operations
			void SwapRows ( UInt firstIndex, UInt secondIndex );
			void MultiplyRow ( UInt index, Scalar value );
			void AddMultipleOfRowToRow( UInt firstIndex, UInt secondIndex, Scalar multiplier );

			//friend functions
			#ifdef MATH_IOSTREAM_SUPPORT
				friend std::ostream& operator << ( std::ostream& os, const Matrix& rhs ); 
			#endif

			//Public static variables
			static const UInt ms_numRows = rows;
			static const UInt ms_numCols = cols;

		private:

			union 
			{
				Scalar m[rows][cols];
			};

	};
	//end class Matrix


    //=========================================================================
    //! @function    Matrix<cols,rows>::operator ()
    //! @brief       Return the value of the element at row,col
    //!              
    //! @param       row 
    //! @param       col 
    //!              
    //! @return      The value of the element at row,col
    //=========================================================================
	template <UInt cols, UInt rows>
		Scalar Matrix<cols,rows>::operator ()(UInt row, UInt col) const
	{
		debug_assert( row < ms_numRows, "row index out of range!" );
		debug_assert( col < ms_numCols, "col index out of range!" );

		return m[row][col];
	}
	//End Matrix<cols,rows>::operator ()



    //=========================================================================
    //! @function    Matrix<cols,rows>::operator ()
    //! @brief       Return a reference to the element at row,col
    //!              
    //! @param       row 
    //! @param       col 
    //!              
    //! @return      A reference to the element at row,col
    //=========================================================================
	template <UInt cols, UInt rows>
		Scalar& Matrix<cols,rows>::operator ()(UInt row, UInt col)
	{
		debug_assert( row < ms_numRows, "row index out of range!" );
		debug_assert( col < ms_numCols, "col index out of range!" );

		return m[row][col];
	}
	//End Matrix<cols,rows>::operator ()


	
	//=========================================================================
	//! @function    Matrix<cols,rows>::SwapRows
	//! @brief       Swap the row at firstIndex with the row at secondIndex
	//!              
	//! @param       firstIndex  [in] Index of
	//! @param       secondIndex [in]
	//!              
	//! @return      
	//! @throw       
	//=========================================================================
	template <UInt cols, UInt rows>
	void Matrix<cols,rows>::SwapRows ( UInt firstIndex, UInt secondIndex )
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

		//Swap the rows
		for ( UInt col = 0; col < ms_numCols; ++col )
		{
			std::swap ( m[firstIndex][col], m[secondIndex][col] );
		}
	}
	//End Matrix<cols,rows>::SwapRows



	//=========================================================================
	//! @function    Matrix<cols,rows>::MultiplyRow
	//! @brief       Multiply the row at index by value
	//!              
	//! @param       index [in] Index of row to multiply
	//! @param       value [in] Value to multiply row by
	//!              
	//=========================================================================
	template <UInt cols, UInt rows>
	void Matrix<cols,rows>::MultiplyRow ( UInt index, Scalar value )
	{
			//Make sure firstIndex and secondIndex are in range
		debug_assert ( (index < ms_numRows), "index out of range!" );

		//Multiply the row
		for ( UInt col = 0; col < ms_numCols; ++col )
		{
			m[index][col] *= value;
		}
	}
	//End Matrix<cols,rows>::MultiplyRow


	//=========================================================================
	//! @function    Matrix<cols,rows>::AddMultipleOfRowToRow
	//! @brief       Add a multiple of one row to another
	//!              
	//! @param       firstIndex  [in] Index of row to get values from
	//! @param       secondIndex [in] Index of row to add multiple of row first index to
	//! @param       multiplier  [in] Scalar multiplier for row values from row firstIndex
	//!              
	//=========================================================================
	template <UInt cols, UInt rows>
	void Matrix<cols,rows>::AddMultipleOfRowToRow( UInt firstIndex, UInt secondIndex, Scalar multiplier )
	{
		//Make sure firstIndex and secondIndex are in range
		debug_assert ( (firstIndex < ms_numCols), "firstIndex out of range!" );
		debug_assert ( (secondIndex < ms_numCols), "secondIndex out of range!" ); 

		//Check to see if firstIndex and secondIndex are equal
		if ( firstIndex == secondIndex )
		{
			std::cerr << "Matrix<" << cols << ", " << rows << ">::AddMultipleOfRowToRow. firstIndex == secondIndex!" << std::endl;
		}

		//Swap the rows
		for ( UInt col = 0; col < ms_numCols; ++col )
		{
			m[secondIndex][col] += (multiplier * m[firstIndex][col]);
		}
	}
	//End Matrix<cols,rows>::AddMultipleOfRowToRow




	//=========================================================================
	//! @function    operator << 
	//! @brief       Formatted output of a Matrix to an ostream
	//!              
	//! @param       os  [in] Output stream to write to
	//! @param       rhs [in] Matrix to write
	//!              
	//! @return      os
	//=========================================================================
	template <UInt cols, UInt rows>
	std::ostream& operator << ( std::ostream& os, const Matrix<cols,rows>& rhs )
	{
		os << std::endl;

		for ( UInt row = 0; row < rhs.ms_numRows; ++row )
		{

			os << "| ";

			for ( UInt col = 0; col < rhs.ms_numCols; ++col )
			{
				os << rhs( row, col ) << "  ";
			}

			os << "|" << std::endl;

		}

		return os;
	}
	//End operator << ( std::ostream&, const Matrix& )




};
//end namespace Math

#endif 
//#ifndef MATH_MATRIXNxN_H
