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


#ifndef MATH_MATRIX2X2_H
#define MATH_MATRIX2X2_H

#include "Core/BasicTypes.h"
#include "Math/Math.h"
#include "Math/Matrix1x2.h"


//namespace Math
namespace Math
{

	//!@class	Matrix2x2
	//!@brief	
	class Matrix2x2
	{
		public:

			//Constructors
			inline Matrix2x2 ( ) throw() {};
			inline Matrix2x2 ( Scalar m00, Scalar m01,
							   Scalar m10, Scalar m11 ) throw();

			//Initalization
			inline void Zero ( ) throw();
			inline void Identity ( ) throw();

			inline void Set (  Scalar m00, Scalar m01,
							   Scalar m10, Scalar m11 ) throw();

			//Misc
			bool		Invert  ( ) throw();
			inline bool Inverse ( Matrix2x2& result ) const throw();  

			void	SwapColumn  ( UInt firstIndex, UInt secondIndex ) throw();
			void	Transpose   ( ) throw();
			Scalar	Determinate ( ) const throw();

			//Operator overloads
			
			inline Matrix2x2& operator += ( const Matrix2x2& rhs ) throw();
			inline Matrix2x2& operator *= ( const Matrix2x2& rhs ) throw();
			inline Matrix2x2& operator *= ( Scalar rhs ) throw();

			inline Scalar operator () ( UInt row, UInt col ) const throw();
			inline Scalar& operator() ( UInt row, UInt col ) throw();

			//Formatted output to ostream. 
			//NOTE: Remember to #include <iostream> before this header if you want use ostream::operator << with this class
			#ifdef MATH_IOSTREAM_SUPPORT
				friend std::ostream& operator << ( std::ostream& out, const Matrix2x2& matrixToOutput ); 
			#endif

			//Public static variables
			static const UInt ms_numRows = 2;
			static const UInt ms_numCols = 2;


		private:

			union 
			{
				Scalar m[2][2];

				struct
				{
					Scalar m_00, m_01;
					Scalar m_10, m_11;
				};
			};

	};
	//end class Matrix2x2


	
    //=========================================================================
    // Protoypes for non-member functions
    //=========================================================================
	bool Solve2x2System ( const Matrix2x2& A, const Matrix1x2& B, Matrix1x2& X );
	inline Matrix2x2  operator +  ( const Matrix2x2& lhs, const Matrix2x2& rhs ) throw();
	inline Matrix2x2  operator *  ( const Matrix2x2& lhs, const Matrix2x2& rhs ) throw();
	inline Matrix2x2  operator *  ( const Matrix2x2& lhs, Scalar rhs ) throw();





    //=========================================================================
    //! @function    Matrix2x2::Matrix2x2
    //! @brief       Initialise a matrix with scalar values for each element
    //!              
    //! @param       m00 [in]
    //! @param       m01 [in]
    //! @param       m10 [in]
    //! @param       m11 [in]
    //=========================================================================
	Matrix2x2::Matrix2x2 ( Scalar m00, Scalar m01, 
						   Scalar m10, Scalar m11 )
	:	m_00 (m00), m_01 (m01),
		m_10 (m10), m_11 (m11)				 
	{
	}
	//end Matrix2x2::Constructor()



    //=========================================================================
    //! @function    Matrix2x2::Zero
    //! @brief       Set each element of the matrix to zero
    //=========================================================================
	void Matrix2x2::Zero ( )
	{
		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				operator()(row, col) = 0.0f;
			}
		}
	}
	//end Matrix2x2::Zero ( )



	//=========================================================================
	//! @function    Matrix2x2::Identity
	//! @brief       Set the matrix to the identity matrix
	//!              
	//=========================================================================
	void Matrix2x2::Identity ( )
	{
		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				if ( row == col )
				{
					operator()(row,col) = 1.0f;
				}
				else
				{
					operator()(row,col) = 0.0f;
				}	
			}
		}

	}
	//end Matrix2x2::Identity



	//=========================================================================
	//! @function    Matrix2x2::Set
	//! @brief       Set the contents of the matrix
	//!              
	//! @param       m00 [in]
	//! @param       m01 [in]
	//! @param       m10 [in]
	//! @param       m11 [in]
	//=========================================================================
	void Matrix2x2::Set ( Scalar m00, Scalar m01, 
						  Scalar m10, Scalar m11 )
	{
		m_00 = m00;
		m_01 = m01;

		m_10 = m10;
		m_11 = m11;
	
	}
	//end Matrix2x2::set



    //=========================================================================
    //! @function    Math::Matrix2x2::Inverse
    //! @brief       Return the inverse of the matrix in result if possible. 
	//!				 
    //!              
    //! @param       result [out] Result of the inverse calculation
    //!      
	//! @return		 Returns true if the inverse could be calculated.
	//!					result will then contain the inverse of this matrix
	//!				 Returns false if the inverse could not be calculated
	//!					the contents of result will be undefined
    //=========================================================================
	bool Matrix2x2::Inverse ( Matrix2x2& result ) const
	{
		result = *this;

        return result.Invert ( );
	}
	//end Matrix2x2::Inverse ( )



    //=========================================================================
    //! @function    Matrix2x2::operator +=
    //! @brief       Add a matrix to *this
    //!              
    //! @param       rhs [in] Matrix to add to *this
    //!              
    //! @return      *this
    //=========================================================================
	Matrix2x2& Matrix2x2::operator += ( const Matrix2x2& rhs )
	{
		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				m[row][col] += rhs(row,col);
			}
		}

		return (*this);
	}
	//end Matrix2x2::operator += 

	

    //=========================================================================
    //! @function    Matrix2x2::operator *=
    //! @brief       Multiply this matrix by another matrix
    //!              
    //! @param       rhs [in]
    //!              
    //! @return      *this
    //=========================================================================
	Matrix2x2& Matrix2x2::operator *= ( const Matrix2x2& rhs )
	{
		Matrix2x2 mt ( *this );

		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				Scalar sum = 0.0f;
				
				for ( UInt i = 0; i < ms_numRows; ++i )
				{
					sum += mt(row,i) * rhs(i,col);
				}

				m[row][col] = sum;
			}
		}	

		return (*this);

	}
	//end Matrix2x2::operator *=



    //=========================================================================
    //! @function    Matrix2x2::operator *=
    //! @brief       Multiply this matrix by a scalar
    //!              
    //! @param       rhs [in]
    //!              
    //! @return      *this
    //=========================================================================
	Matrix2x2& Matrix2x2::operator *= ( Scalar rhs )
	{
		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				m[row][col] *= rhs;
			}
		}
	}
	//end operator *= ( Scalar )



    //=========================================================================
    //! @function    Matrix2x2::operator ()
    //! @brief       Return the element at row,col
    //!              
    //! @param       row [in]
    //! @param       col [in]
    //!              
    //! @return      The element at row,col
    //=========================================================================
	Scalar Matrix2x2::operator () ( UInt row, UInt col ) const
	{
		debug_assert ( (row < ms_numRows), "Row index out of range!");
		debug_assert ( (col < ms_numCols), "Column index out of range!" );
		return m[row][col];
	}
	//end operator ()


	//=========================================================================
    //! @function    Matrix2x2::operator ()
    //! @brief       Return a reference to the element at row,col
    //!              
    //! @param       row [in]
    //! @param       col [in]
    //!              
    //! @return      A reference to the element at row,col
    //=========================================================================
	Scalar& Matrix2x2::operator () ( UInt row, UInt col )
	{
		debug_assert ( (row < ms_numRows), "Row index out of range!");
		debug_assert ( (col < ms_numCols), "Column index out of range!" );
		return m[row][col];
	}
	//end operator ()


    //=========================================================================
    //! @function    operator + ( const Matrix2x2&, conat Matrix2x2& )
    //! @brief       Return the result of adding lhs to rhs
    //!              
    //! @param       lhs [in]
    //! @param       rhs [in]
    //!              
    //! @return      The result of adding lhs to rhs
    //=========================================================================
	Matrix2x2 operator+ ( const Matrix2x2& lhs, const Matrix2x2& rhs )
	{
		return Matrix2x2( lhs ) += rhs;
	}
	//end Matrix2x2:::operator+ ( Matrix2x2 )


	
	//=========================================================================
    //! @function    operator + ( const Matrix2x2&, conat Matrix2x2& )
    //! @brief       Return the result of multiplying a matrix by a matrix
    //!              
    //! @param       lhs [in]
    //! @param       rhs [in]
    //!              
    //! @return      The result of  multiplying lhs by rhs
    //=========================================================================
	Matrix2x2 operator * ( const Matrix2x2& lhs, const Matrix2x2& rhs )
	{
		return Matrix2x2( lhs ) *= rhs;
	}
	//end Matrix2x2::operator*


	//=========================================================================
    //! @function    operator + ( const Matrix2x2&, conat Matrix2x2& )
    //! @brief       Return the result of multiplying a matrix by a scalar
    //!              
    //! @param       lhs [in]
    //! @param       rhs [in]
    //!              
    //! @return      The result of  multiplying lhs by rhs
    //=========================================================================
	Matrix2x2 operator *  ( const Matrix2x2& lhs, Scalar rhs )
	{
		return (Matrix2x2 ( lhs ) *= rhs);
	}
	//end operator * ( Scalar )



}; //end namespace Math3D

#endif