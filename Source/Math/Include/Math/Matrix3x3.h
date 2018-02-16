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

#ifndef MATH_MATRIX3X3_H
#define MATH_MATRIX3X3_H

#include "Core/BasicTypes.h"
#include "Math/Math.h"
#include "Math/Vector3D.h"


//namespace Math
namespace Math
{

    //=========================================================================
    //Forward declaration
    //=========================================================================
	class Matrix3x3;
	class Matrix1x3;
	class Vector3D;
	class Quaternion;


	//!@class	Matrix3x3
	//!@brief	3x3 Matrix class
	class Matrix3x3
	{
		public:

			//Constructors
			explicit inline Matrix3x3 (	Scalar m00 = 1.0f, Scalar m01 = 0.0f, Scalar m02 = 0.0f,
										Scalar m10 = 0.0f, Scalar m11 = 1.0f, Scalar m12 = 0.0f,
										Scalar m20 = 0.0f, Scalar m21 = 0.0f, Scalar m22 = 1.0f ) throw();

			explicit Matrix3x3 ( const Quaternion& q ) throw();

			//Initalization
			inline void Zero ( ) throw();
			inline void Identity ( ) throw();

			inline void Set (  Scalar m00, Scalar m01, Scalar m02,
							   Scalar m10, Scalar m11, Scalar m12,
							   Scalar m20, Scalar m21, Scalar m22 ) throw();

			//Transforms
			inline void Translate   ( const Vector3D& translation ) throw ();
			inline void RotateXAxis ( Scalar angle ) throw ();
			inline void RotateYAxis ( Scalar angle ) throw ();
			inline void RotateZAxis ( Scalar angle ) throw ();
			inline void Rotate	    ( const Vector3D& axis, Scalar angle );
			inline void Scale		( const Vector3D& scale ) throw ();

			//Misc
			bool		Invert  ( ) throw();
			inline bool Inverse ( Matrix3x3& result ) const throw();

			void	SwapColumn	( UInt firstIndex, UInt secondIndex ) throw();
			Scalar	Determinate ( ) const throw();
			void	Transpose	( ) throw();

			//Operator overloads
			inline Matrix3x3& operator += ( const Matrix3x3& rhs ) throw();
			inline Matrix3x3& operator *= ( const Matrix3x3& rhs ) throw();
			inline Matrix3x3& operator *= ( Scalar rhs	  ) throw();

			inline Scalar operator () ( UInt row, UInt col ) const throw();
			inline Scalar& operator () ( UInt row, UInt col ) throw();

			//Formatted output to ostream. 
			#ifdef MATH_IOSTREAM_SUPPORT
				inline friend std::ostream& operator << ( std::ostream& out, const Matrix3x3& matrixToOutput ); 
			#endif

		private:

			static const UInt ms_numRows = 3;
			static const UInt ms_numCols = 3;

			union 
			{
				Scalar m[3][3];

				struct
				{
					Scalar m_00, m_01, m_02;
					Scalar m_10, m_11, m_12;
					Scalar m_20, m_21, m_22;
				};
			};

	};
	//end class Matrix3x3



    //=========================================================================
    //Prototypes for non-member functions
    //=========================================================================
	inline Vector3D operator *   ( const Vector3D& lhs, const Matrix3x3& rhs );
	inline Vector3D& operator *= ( Vector3D& lhs, const Matrix3x3& rhs );

	inline Matrix3x3  operator + ( const Matrix3x3& lhs, const Matrix3x3& rhs ) throw();
	inline Matrix3x3  operator * ( const Matrix3x3& lhs, const Matrix3x3& rhs ) throw();
	inline Matrix3x3  operator * ( const Matrix3x3& lhs, Scalar rhs ) throw();

	bool Solve3x3System ( const Matrix3x3& A, const Matrix1x3& B, Matrix1x3& X );



	//=========================================================================
	//! @function    Matrix3x3::Matrix3x3
	//! @brief       Initialise a 3x3 matrix using the values supplied
	//!					
	//=========================================================================
	Matrix3x3::Matrix3x3 ( Scalar m00, Scalar m01, Scalar m02,
						   Scalar m10, Scalar m11, Scalar m12,
						   Scalar m20, Scalar m21, Scalar m22 )
	:	m_00 (m00), m_01 (m01), m_02 (m02),
		m_10 (m10), m_11 (m11), m_12 (m12),
		m_20 (m20), m_21 (m21), m_22 (m22)					 
	{
	}
	//end Matrix3x3::Constructor()



	//=========================================================================
	//! @function    Matrix3x3::Zero
	//! @brief       Set all the elements in a matrix to 0
	//!					
	//=========================================================================
	void Matrix3x3::Zero ( )
	{
		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				m[row][col] = 0.0f;
			}
		}
	}
	//end Matrix3x3::Zero ( )



	//=========================================================================
	//! @function    Matrix3x3::Identity
	//! @brief       Set a 3x3 matrix to the identity matrix
	//!					
	//=========================================================================
	void Matrix3x3::Identity ( )
	{

		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				if ( row == col )
				{
					m[row][col] = 1.0f;
				}
				else
				{
					m[row][col] = 0.0f;
				}	
			}
		}

	}
	//end Matrix3x3::Identity



	//=========================================================================
	//! @function    Matrix3x3::Identity
	//! @brief       Set a the contents of a matrix using the values provided
	//!					
	//=========================================================================
	void Matrix3x3::Set ( Scalar m00, Scalar m01, Scalar m02,
						  Scalar m10, Scalar m11, Scalar m12,
						  Scalar m20, Scalar m21, Scalar m22 )
	{
		m_00 = m00;
		m_01 = m01;
		m_02 = m02;
		
		m_10 = m10;
		m_11 = m11;
		m_12 = m12;

		m_20 = m20;
		m_21 = m21;
		m_22 = m22;
	}
	//end Matrix3x3::set



	//=========================================================================
	//! @function    Matrix3x3::Inverse
	//! @brief       Set result to the inverse of this matrix
	//!					
	//!				 If the matrix cannot be inverted then this method will return false
	//!				 and the contents of result will be undefined
	//!
	//!	@param		 result [out] Result matrix to store the inverse in				 
	//!
	//! @return		 true if the matrix was inverted successfully
	//!				 false if the matrix could not be inverted
	//=========================================================================
	bool Matrix3x3::Inverse ( Matrix3x3& result ) const
	{
		result = *this;

        return result.Invert ( );
	}
	//end Matrix3x3::Inverse ( )



	//=========================================================================
	//! @function    Matrix3x3::operator+=
	//! @brief       Add rhs to *this
	//!
	//! @param		 rhs [in] Matrix to add
	//!					
	//!	@return		 New value of (*this)
	//=========================================================================
	Matrix3x3& Matrix3x3::operator += ( const Matrix3x3& rhs )
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
	//end Matrix3x3::operator += 


    
	//=========================================================================
	//! @function    Matrix3x3::operator*=
	//! @brief       Multiply this matrix by rhs
	//!					
	//!	@param		 rhs [in] Matrix to multiply *this by 
	//!
	//!	@return		 New value of (*this)
	//=========================================================================
	Matrix3x3& Matrix3x3::operator *= ( const Matrix3x3& rhs )
	{
		Scalar sum = 0.0f;

		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				sum = 0.0f;
				
				for ( UInt i = 0; i < ms_numRows; ++i )
				{
					sum += operator()(row,i) * rhs(i,col);
				}

				m[row][col] = sum;
			}
		}	

		return (*this);
	}
	//end Matrix3x3::operator *=



	//=========================================================================
	//! @function    Matrix3x3::operator*=
	//! @brief       Multiply this matrix by scalar value rhs
	//!					
	//!	@param		 rhs [in] Scalar value to multiply *this by 
	//!
	//!	@return		 A new matrix equal to *this + rhs
	//=========================================================================
	Matrix3x3& Matrix3x3::operator *= ( Scalar rhs )
	{
		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				m[row][col] *= rhs;
			}
		}

		return (*this);
	}
	//end Matrix3x3::operator *= ( Scalar )



	//=========================================================================
	//! @function    Matrix3x3::operator() const
	//! @brief       Access the matrix element at row,col
	//!					
	//!	@param		 row [in] Zero based row index
	//! @param		 col [in] Zero based column index
	//!
	//!	@return		 The value of the element at (row,col)
	//=========================================================================
	Scalar Matrix3x3::operator () ( UInt row, UInt col ) const
	{
		debug_assert ( (row < ms_numRows) && (col < ms_numCols), "Index out of range!" );

		return m[row][col];
	}
	//end Matrix3x3::operator () const


	//=========================================================================
	//! @function    Matrix3x3::operator()
	//! @brief       Access the matrix element at row,col
	//!					
	//!	@param		 row [in] Zero based row index
	//! @param		 col [in] Zero based column index
	//!
	//!	@return		 The value of the element at (row,col)
	//=========================================================================
	Scalar& Matrix3x3::operator () ( UInt row, UInt col )
	{
		debug_assert ( (row < ms_numRows) && (col < ms_numCols), "Index out of range!" );

		return m[row][col];
	}
	//end Matrix3x3::operator ()


	
	//=========================================================================
    // Non member-functions
    //=========================================================================



	//=========================================================================
	//! @function    operator * ( Vector3D, Matrix3x3 )
	//! @brief       Return the result of multiplying a Vector3D by a Matrix3x3
	//!					
	//!	@param		 lhs [in] Vector to multiply by the matrix
	//! @param		 rhs [in] Matrix to multiply vector by
	//!
	//!	@return		 The result of lhs * rhs
	//=========================================================================
	Vector3D operator * ( const Vector3D& lhs, const Matrix3x3& rhs )
	{
		return Vector3D(lhs) *= rhs;
	}
	//end  operator * ( Vector3D, Matrix3x3 )



	//=========================================================================
	//! @function    operator *= ( Vector3D, Matrix3x3 )
	//! @brief       Multiply a Vector3D by a Matrix3x3
	//!					
	//!	@param		 lhs [in] Vector to multiply by the matrix
	//! @param		 rhs [in] Matrix to multiply vector by
	//!
	//!	@return		 A reference to the vector, after lhs * rhs has been completed
	//=========================================================================
	Vector3D& operator *= ( Vector3D& lhs, const Matrix3x3& rhs )
	{

		lhs.Set ( lhs.X() * rhs(0,0) + lhs.Y() * rhs(1,0) + lhs.Z() * rhs(2,0),
				  lhs.X() * rhs(0,1) + lhs.Y() * rhs(1,1) + lhs.Z() * rhs(2,1),
				  lhs.X() * rhs(0,2) + lhs.Y() * rhs(1,2) + lhs.Z() * rhs(2,2) );

		return lhs;
	}
	//end operator *= ( Vector3D, Matrix3x3 )



	//=========================================================================
	//! @function    operator+
	//! @brief       Add two 3x3 matrices
	//!
	//! @param		 lhs [in] First matrix
	//! @param		 rhs [in] Second matrix
	//!					
	//!	@return		 A new matrix equal to lhs + rhs
	//=========================================================================
	Matrix3x3 operator + ( const Matrix3x3& lhs, const Matrix3x3& rhs )
	{
		return Matrix3x3( lhs ) += rhs;
	}
	//end operator+ ( Matrix3x3 )



	//=========================================================================
	//! @function    operator*
	//! @brief       Return the result of multiplying two 3x3 matrices
	//!
	//! @param		 lhs [in] First matrix
	//! @param		 rhs [in] Second matrix
	//!					
	//!	@return		 A new matrix equal to lhs * rhs
	//=========================================================================
	Matrix3x3 operator * ( const Matrix3x3 lhs, const Matrix3x3& rhs )
	{
		return Matrix3x3( lhs ) *= rhs;
	}
	//end Matrix3x3::operator*


	
	//=========================================================================
	//! @function    operator*
	//! @brief       Return the result of multiplying a 3x3 matrix by a scalar
	//!
	//! @param		 lhs [in] First matrix
	//! @param		 rhs [in] Scalar value to multiply lhs by
	//!					
	//!	@return		 A new matrix equal to lhs * rhs
	//=========================================================================
	Matrix3x3 operator * ( const Matrix3x3 lhs, Scalar rhs )
	{
		return Matrix3x3(lhs) *= rhs;
	}
	//end operator * ( Scalar )


}; //end namespace Math

#endif