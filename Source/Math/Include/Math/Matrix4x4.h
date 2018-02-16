//======================================================================================
//! @file         Matrix4x4.h
//! @brief        4x4 Matrix class
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


#ifndef MATH_MATRIX4X4_H
#define MATH_MATRIX4X4_H

#include "Core/BasicTypes.h"
#include "Math/Math.h"
#include "Math/Vector3D.h"


//namespace Math
namespace Math
{

	//=========================================================================
    //Forward declaration
    //=========================================================================
	class Vector3D;
	class Quaternion;



	//!@class	Matrix4x4
	//!@brief	4x4 Matrix class
	//!
	//!			Matrix is stored in row-major format (DirectX order)
	//!			so that the matrix row,column indices match the order that they are stored in memory
	//!			For example, a translation matrix would take the form of
	//!
	//!			| 1,  0,  0,  0 |
	//!			| 0,  1,  0,  0 |
	//!			| 0,  0,  1,  0 |
	//!			| Tx, Ty, Tz, 1 |
	class Matrix4x4
	{
		public:

			//Constructors
			explicit inline Matrix4x4 (  Scalar m00 = 1.0f, Scalar m01 = 0.0f, Scalar m02 = 0.0f, Scalar m03 = 0.0f,
										 Scalar m10 = 0.0f, Scalar m11 = 1.0f, Scalar m12 = 0.0f, Scalar m13 = 0.0f,
										 Scalar m20 = 0.0f, Scalar m21 = 0.0f, Scalar m22 = 1.0f, Scalar m23 = 0.0f,
										 Scalar m30 = 0.0f, Scalar m31 = 0.0f, Scalar m32 = 0.0f, Scalar m33 = 1.0f) throw ();

			explicit Matrix4x4 ( const Quaternion& q ) throw();

			static void CreateTranslationMatrix ( Matrix4x4& mat, const Vector3D& translation ) throw();
			static void CreateRotationMatrixXAxis ( Matrix4x4& mat, Scalar angle ) throw();
			static void CreateRotationMatrixYAxis ( Matrix4x4& mat, Scalar angle ) throw();
			static void CreateRotationMatrixZAxis ( Matrix4x4& mat, Scalar angle ) throw();
			static void CreateRotationMatrix	  ( Matrix4x4& mat, const Vector3D& axis, Scalar angle ) throw();
			static void CreateScalingMatrix		  ( Matrix4x4& mat, const Vector3D& scaleFactor ) throw();
			static void CreateUVNCameraMatrixLH	  ( Matrix4x4& mat, const Vector3D& eye, const Vector3D& up, const Vector3D& lookAt ) throw();
			static void CreateUVNCameraMatrixRH	  ( Matrix4x4& mat, const Vector3D& eye, const Vector3D& up, const Vector3D& lookAt ) throw();

			static void CreateUVNCameraFromViewVectorLH	( Matrix4x4& mat, const Vector3D& eye, const Vector3D& view, const Vector3D& up ) throw();
			static void CreateUVNCameraFromViewVectorRH	( Matrix4x4& mat, const Vector3D& eye, const Vector3D& view, const Vector3D& up ) throw();

			static void CreatePerspectiveProjectionRH  ( Matrix4x4& mat, Scalar fovY, Scalar aspectRatio, Scalar zNear, Scalar zFar ) throw();
			static void CreatePerspectiveProjectionLH  ( Matrix4x4& mat, Scalar fovY, Scalar aspectRatio, Scalar zNear, Scalar zFar ) throw();
			static void CreateOrthographicProjectionRH ( Matrix4x4& mat, Scalar left, Scalar right, Scalar bottom, Scalar top, 
														Scalar zNear, Scalar zFar ) throw();
			static void CreateOrthographicProjectionLH ( Matrix4x4& mat, Scalar left, Scalar right, Scalar bottom, Scalar top, 
														Scalar zNear, Scalar zFar ) throw();

			//Initalization
			inline void Zero ( ) throw ();
			inline void Identity ( ) throw ();

			//Set
			inline void Set ( Scalar m00, Scalar m01, Scalar m02, Scalar m03,
							  Scalar m10, Scalar m11, Scalar m12, Scalar m13,
							  Scalar m20, Scalar m21, Scalar m22, Scalar m23,
							  Scalar m30, Scalar m31, Scalar m32, Scalar m33 ) throw ();

			//Get a pointer to the array of Scalars
			inline const Scalar* GetPointer() const; 

			//Transforms
			inline void Translate   ( const Vector3D& translation ) throw ();
			inline void RotateXAxis ( Scalar angle ) throw ();
			inline void RotateYAxis ( Scalar angle ) throw ();
			inline void RotateZAxis ( Scalar angle ) throw ();
			inline void Rotate	    ( const Vector3D& axis, Scalar angle );
			inline void Scale		( const Vector3D& scale ) throw ();

			//Misc
			inline Matrix4x4 FastInvert ( ) const throw();
			inline void FastInvert ( Matrix4x4& result ) const throw();
			inline bool Inverse ( Matrix4x4& result ) const throw();
			void		InvertByTranspose ( ) throw();
			bool		Invert  ( ) throw ();
			Scalar		Determinate () const;
			void		SwapColumn ( UInt firstIndex, UInt secondIndex ) throw ();
			void		Transpose ( ) throw ();

			//Operator overloads
			inline Matrix4x4& operator += ( const Matrix4x4& rhs ) throw ();
			inline Matrix4x4& operator *= ( const Matrix4x4& rhs ) throw ();
			inline Matrix4x4& operator *= ( Scalar rhs	  ) throw ();
			inline Scalar& operator () ( UInt row, UInt col ) throw();
			inline Scalar  operator () ( UInt row, UInt col ) const throw ();
			
			//Formatted output to ostream.
			#ifdef MATH_IOSTREAM_SUPPORT
				inline friend std::ostream& operator << ( std::ostream& out, const Matrix4x4& matrixToOutput ); 
			#endif
				
			//Public static variables
			static const UInt ms_numRows = 4;
			static const UInt ms_numCols = 4;

			static Matrix4x4 IdentityMatrix;

		private:

			union 
			{
				Scalar m[4][4];

				struct
				{
					Scalar m_00, m_01, m_02, m_03;
					Scalar m_10, m_11, m_12, m_13;
					Scalar m_20, m_21, m_22, m_23;
					Scalar m_30, m_31, m_32, m_33;
				};
			};

	};
	//end class Matrix4x4


    //=========================================================================
    // Prototypes for non-member functions
    //=========================================================================
	inline Matrix4x4  operator +  ( const Matrix4x4& lhs, const Matrix4x4& rhs ) throw ();
	inline Matrix4x4  operator *  ( const Matrix4x4& lhs, const Matrix4x4& rhs ) throw ();
	inline Matrix4x4  operator *  ( const Matrix4x4& lhs, Scalar rhs ) throw ();

	inline bool operator == ( const Matrix4x4& lhs, const Matrix4x4& rhs ) throw ();

	//Vector multiply by Matrix4x4
	inline Vector3D  operator *   ( const Vector3D& lhs, const Matrix4x4& rhs );
	inline Vector3D& operator *= ( Vector3D& lhs, const Matrix4x4& rhs );
	

    //=========================================================================
    //! @function    Matrix4x4::Matrix4x4
    //! @brief       Construct a 4x4 matrix with values for each element
    //!              
    //! @param       m00 [in]
    //! @param       m01 [in]
    //! @param       m02 [in]
    //! @param       m03 [in]
    //! @param       m10 [in]
    //! @param       m11 [in]
    //! @param       m12 [in]
    //! @param       m13 [in]
    //! @param       m20 [in]
    //! @param       m21 [in]
    //! @param       m22 [in]
    //! @param       m23 [in]
    //! @param       m30 [in]
    //! @param       m31 [in]
    //! @param       m32 [in]
    //! @param       m33 [in]
    //=========================================================================
	Matrix4x4::Matrix4x4 ( Scalar m00, Scalar m01, Scalar m02, Scalar m03,
						   Scalar m10, Scalar m11, Scalar m12, Scalar m13,
						   Scalar m20, Scalar m21, Scalar m22, Scalar m23,
						   Scalar m30, Scalar m31, Scalar m32, Scalar m33 )
	:	m_00 (m00), m_01 (m01), m_02 (m02), m_03 (m03),
		m_10 (m10), m_11 (m11), m_12 (m12), m_13 (m13),
		m_20 (m20), m_21 (m21), m_22 (m22), m_23 (m23),
		m_30 (m30), m_31 (m31), m_32 (m32), m_33 (m33)
							 
	{
	}
	//end Matrix4x4::Matrix4x4



    //=========================================================================
    //! @function    Matrix4x4::Zero
    //! @brief       Set a matrix to zero
    //!              
    //=========================================================================
	void Matrix4x4::Zero ( )
	{
		for ( UInt row = 0; row < ms_numRows; ++row )
		{
			for ( UInt col = 0; col < ms_numCols; ++col )
			{
				operator()( row, col) = 0.0f;
			}
		}
	}
	//end Matrix4x4::Zero ( )



	//=========================================================================
	//! @function    Matrix4x4::Identity
	//! @brief       Set a matrix to the identity matrix
	//!              
	//=========================================================================
	void Matrix4x4::Identity ( )
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
	//end Matrix4x4::Identity



    //=========================================================================
    //! @function    Matrix4x4::Set
    //! @brief       Set the contents of the matrix
    //!              
    //! @param       m00 [in]
    //! @param       m01 [in]
    //! @param       m02 [in]
    //! @param       m03 [in]
    //! @param       m10 [in]
    //! @param       m11 [in]
    //! @param       m12 [in]
    //! @param       m13 [in]
    //! @param       m20 [in]
    //! @param       m21 [in]
    //! @param       m22 [in]
    //! @param       m23 [in]
    //! @param       m30 [in]
    //! @param       m31 [in]
    //! @param       m32 [in]
    //! @param       m33 [in]
    //=========================================================================
	void Matrix4x4::Set ( Scalar m00, Scalar m01, Scalar m02, Scalar m03,
						  Scalar m10, Scalar m11, Scalar m12, Scalar m13,
						  Scalar m20, Scalar m21, Scalar m22, Scalar m23,
						  Scalar m30, Scalar m31, Scalar m32, Scalar m33)
	{
		m_00 = m00;
		m_01 = m01;
		m_02 = m02;
		m_03 = m03;
		
		m_10 = m10;
		m_11 = m11;
		m_12 = m12;
		m_13 = m13;

		m_20 = m20;
		m_21 = m21;
		m_22 = m22;
		m_23 = m23;

		m_30 = m30;
		m_31 = m31;
		m_32 = m32;
		m_33 = m33;

	}
	//end Matrix4x4::Set



    //=========================================================================
    //! @function    Matrix4x4::GetPointer
    //! @brief       Get a pointer to the Matrix data, as an array of floats
    //!              
	//!				 Usage of this method is not recommended, and is provided
	//!				 only for usage with external APIs, which take in matrices
	//!				 as arrays of floats.
	//!
    //! @return      A pointer to the start of the matrix array
    //=========================================================================
	inline const Scalar* Matrix4x4::GetPointer() const
	{
		return reinterpret_cast<const Scalar*>(&m[0][0]);
	}
	//End Matrix4x4::GetPointer



    //=========================================================================
    //! @function    Matrix4x4::Translate
    //! @brief       Multiply a matrix by a translation matrix
    //!              
    //! @param       translation [in] Translation component of translation matrix
    //!              
    //=========================================================================
	void Matrix4x4::Translate ( const Vector3D& translation )
	{
		Matrix4x4 translationMatrix;
		CreateTranslationMatrix( translationMatrix, translation );
	
		(*this) *= translationMatrix;
	}
	//End Matrix4x4::Translate



    //=========================================================================
    //! @function    Matrix4x4::RotateXAxis
    //! @brief       Multiply a matrix by a matrix for a rotation around the x axis
    //!              
    //! @param       angle [in]	Angle to rotate around the x axis
    //=========================================================================
	void Matrix4x4::RotateXAxis ( Scalar angle )
	{
		Matrix4x4 rotationMatrix;
		CreateRotationMatrixXAxis( rotationMatrix, angle );
	
		(*this) *= rotationMatrix;
	}
	//End Matrix4x4::RotateXAxis



	 //=========================================================================
    //! @function    Matrix4x4::RotateYAxis
    //! @brief       Multiply a matrix by a matrix for a rotation around the y axis
    //!              
    //! @param       angle [in]	Angle to rotate around the y axis
    //=========================================================================
	void Matrix4x4::RotateYAxis ( Scalar angle )
	{
		Matrix4x4 rotationMatrix;
		CreateRotationMatrixYAxis( rotationMatrix, angle );
	
		(*this) *= rotationMatrix;
	}
	//End Matrix4x4::RotateYAxis



	//=========================================================================
    //! @function    Matrix4x4::RotateZAxis
    //! @brief       Multiply a matrix by a matrix for a rotation around the z axis
    //!              
    //! @param       angle [in]	Angle to rotate around the z axis
    //=========================================================================
	void Matrix4x4::RotateZAxis ( Scalar angle )
	{
		Matrix4x4 rotationMatrix;
		CreateRotationMatrixZAxis( rotationMatrix, angle );
	
		(*this) *= rotationMatrix;
	}
	//End Matrix4x4::RotateZAxis



	//=========================================================================
    //! @function    Matrix4x4::Rotate
    //! @brief       Multiply a matrix by a matrix for a rotation around an arbitrary axis
    //!              
	//! @param		 axis  [in] Axis around which to rotate
    //! @param       angle [in]	Angle to rotate around the x axis
    //=========================================================================
	void Matrix4x4::Rotate ( const Vector3D& axis, Scalar angle )
	{
		Matrix4x4 rotationMatrix;
		CreateRotationMatrix( rotationMatrix, axis, angle );
	
		(*this) *= rotationMatrix;
	}
	//End Matrix4x4::Rotate



	//=========================================================================
    //! @function    Matrix4x4::Scale
    //! @brief       Multiply a matrix by a scalng matrix
    //!              
	//! @param		 scale [in] Vector representing the scaling factor for each component
    //=========================================================================
	void Matrix4x4::Scale ( const Vector3D& scale )
	{
		Matrix4x4 scaleMatrix;
		CreateScalingMatrix( scaleMatrix, scale );
	
		(*this) *= scaleMatrix;
	}
	//End Matrix4x4::Scale



    //=========================================================================
    //! @function    Matrix4x4::Inverse
    //! @brief       Return the inverse of a matrix
    //!              
    //! @param       result [out] Result matrix
    //!              
    //! @return      true if matrix was inverted
	//!				 false if matrix could not be inverted. The contents of result
	//!				 will be undefined
    //=========================================================================
	bool Matrix4x4::Inverse ( Matrix4x4& result ) const
	{
		result = *this;

        return result.Invert ( );
	}
	//end Matrix4x4::Inverse ( )



    //=========================================================================
    //! @function    Matrix4x4::FastInvert
    //! @brief       Return the inverse of an orthogonal matrix by transposing it
    //!              
    //! @return      The inverse transpose of *this
    //=========================================================================
	Matrix4x4 Matrix4x4::FastInvert () const 
	{
		Matrix4x4 mat(*this);
		mat.InvertByTranspose();

		return mat;
	}
	//End Matrix4x4::FastInvert



    //=========================================================================
    //! @function    Matrix4x4::FastInvert
    //! @brief       Return the inverse of an orthogonal matrix by transposing it
    //!              
	//!				 Note that the transpose is only equal to the inverse
	//!				 of a matrix, if that matrix represents an orthonormal basis.
	//!				 This doesn't work in the general case.
	//!
    //! @param       result [out] Result matrix
    //!              
    //=========================================================================
	void Matrix4x4::FastInvert ( Matrix4x4& result ) const throw()
	{
		result = *this;

        return result.InvertByTranspose ( );
	}
	//End Matrix4x4::FastInvert
	

    //=========================================================================
    //! @function    Matrix4x4::operator ()
    //! @brief       Access the element at row,col
    //!              
    //! @param       row 
    //! @param       col 
    //!              
    //! @return      The value of the element at row,col
    //=========================================================================
	Scalar Matrix4x4::operator ()(UInt row, UInt col ) const
	{
		debug_assert ( row < ms_numRows, "row index out of range!" );
		debug_assert ( col < ms_numCols, "col index out of range!" );

		return m[row][col];
	}
	//End Matrix4x4::operator ()



    //=========================================================================
    //! @function    Matrix4x4::operator ()
    //! @brief       Return a reference to the element at row,col
    //!              
    //! @param       row 
    //! @param       col 
    //!              
    //! @return      A reference to the element at row,col
    //=========================================================================
	Scalar& Matrix4x4::operator ()(UInt row, UInt col )
	{
		debug_assert ( row < ms_numRows, "row index out of range!" );
		debug_assert ( col < ms_numCols, "col index out of range!" );

		return m[row][col];
	}
	//End Matrix4x4::operator () 



    //=========================================================================
    //! @function    Matrix4x4::operator +=
    //! @brief       Add another matrix to this one
    //!              
    //! @param       rhs [in] Matrix to add to *this
    //!              
    //! @return      *this
    //=========================================================================
	Matrix4x4& Matrix4x4::operator += ( const Matrix4x4& rhs )
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
	//end Matrix4x4::operator += 

	

    //=========================================================================
    //! @function    Matrix4x4::operator *=
    //! @brief       Multiply another matrix by this one
    //!              
    //! @param       rhs [in] Matrix to multiply *this by
    //!              
    //! @return      *this
    //=========================================================================
	Matrix4x4& Matrix4x4::operator *= ( const Matrix4x4& rhs )
	{
		Scalar m00 = m_00;
		Scalar m01 = m_01;
		Scalar m02 = m_02;
		Scalar m03 = m_03;

		Scalar m10 = m_10;
		Scalar m11 = m_11;
		Scalar m12 = m_12;
		Scalar m13 = m_13;

		Scalar m20 = m_20;
		Scalar m21 = m_21;
		Scalar m22 = m_22;
		Scalar m23 = m_23;

		Scalar m30 = m_30;
		Scalar m31 = m_31;
		Scalar m32 = m_32;
		Scalar m33 = m_33;
			
		m_00 = (m00 * rhs(0,0)) + (m01 * rhs(1,0)) + (m02 * rhs(2,0)) + (m03 * rhs(3,0)); 
		m_01 = (m00 * rhs(0,1)) + (m01 * rhs(1,1)) + (m02 * rhs(2,1)) + (m03 * rhs(3,1));
		m_02 = (m00 * rhs(0,2)) + (m01 * rhs(1,2)) + (m02 * rhs(2,2)) + (m03 * rhs(3,2));
		m_03 = (m00 * rhs(0,3)) + (m01 * rhs(1,3)) + (m02 * rhs(2,3)) + (m03 * rhs(3,3));

		m_10 = (m10 * rhs(0,0)) + (m11 * rhs(1,0)) + (m12 * rhs(2,0)) + (m13 * rhs(3,0));
		m_11 = (m10 * rhs(0,1)) + (m11 * rhs(1,1)) + (m12 * rhs(2,1)) + (m13 * rhs(3,1));
		m_12 = (m10 * rhs(0,2)) + (m11 * rhs(1,2)) + (m12 * rhs(2,2)) + (m13 * rhs(3,2));
		m_13 = (m10 * rhs(0,3)) + (m11 * rhs(1,3)) + (m12 * rhs(2,3)) + (m13 * rhs(3,3));

		m_20 = (m20 * rhs(0,0)) + (m21 * rhs(1,0)) + (m22 * rhs(2,0)) + (m23 * rhs(3,0));
		m_21 = (m20 * rhs(0,1)) + (m21 * rhs(1,1)) + (m22 * rhs(2,1)) + (m23 * rhs(3,1));
		m_22 = (m20 * rhs(0,2)) + (m21 * rhs(1,2)) + (m22 * rhs(2,2)) + (m23 * rhs(3,2));
		m_23 = (m20 * rhs(0,3)) + (m21 * rhs(1,3)) + (m22 * rhs(2,3)) + (m23 * rhs(3,3));

		m_30 = (m30 * rhs(0,0)) + (m31 * rhs(1,0)) + (m32 * rhs(2,0)) + (m33 * rhs(3,0));
		m_31 = (m30 * rhs(0,1)) + (m31 * rhs(1,1)) + (m32 * rhs(2,1)) + (m33 * rhs(3,1));
		m_32 = (m30 * rhs(0,2)) + (m31 * rhs(1,2)) + (m32 * rhs(2,2)) + (m33 * rhs(3,2));
		m_33 = (m30 * rhs(0,3)) + (m31 * rhs(1,3)) + (m32 * rhs(2,3)) + (m33 * rhs(3,3));

		return (*this);
	}
	//end Matrix4x4::operator *=



    //=========================================================================
    //! @function    Matrix4x4::operator *=
    //! @brief       Multiply the current matrix by a scalar
    //!              
    //! @param       rhs [in] Scalar to multiply *this by
    //!              
    //! @return      *this
    //=========================================================================
	Matrix4x4& Matrix4x4::operator *= ( Scalar rhs )
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
    // Non member functions
    //=========================================================================


    //=========================================================================
    //! @function    operator == (const Matrix4x4&, const Matrix4x4& )
    //! @brief       Check two matrices for equality
    //!					
	//!				 Doesn't do a direct compare of the values, due to floating
	//!				 point inaccuracy, we have to check that the difference
	//!				 between each element isn't greater than a certain epsilon value
	//!
    //! @param       lhs 
    //! @param       rhs 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	bool operator == ( const Matrix4x4& lhs, const Matrix4x4& rhs ) throw ()
	{
		for ( UInt row = 0; row < Matrix4x4::ms_numRows; ++row )
		{
			for ( UInt col = 0; col < Matrix4x4::ms_numCols; ++col )
			{
				if (!Equal(lhs(row,col), rhs(row,col)))
				{
					return false;
				}
			}
		}

		return true;
	}
	//End operator == (const Matrix4x4&, const Matrix4x4& )


    //=========================================================================
    //! @function    operator + ( const Matrix&, const Matrix& )
    //! @brief       Return the result of adding two matrices
    //!              
	//! @param		 lhs [in] 
    //! @param       rhs [in] 
    //!              
    //! @return      Result of adding lhs and rhs
    //=========================================================================
	Matrix4x4 operator+ ( const Matrix4x4& lhs, const Matrix4x4& rhs )
	{
		return Matrix4x4( lhs ) += rhs;
	}
	//end Matrix4x4:::operator+ ( Matrix4x4 )



    //=========================================================================
    //! @function    operator * ( const Matrix&, const Matrix& )
    //! @brief       Return the result of multiplying two matrices
    //! 
	//! @param		 lhs [in] 
    //! @param       rhs [in]
    //!              
    //! @return      Result of adding lhs and rhs
    //=========================================================================
	Matrix4x4 operator *  ( const Matrix4x4& lhs, const Matrix4x4& rhs )
	{
		return Matrix4x4( lhs ) *= rhs;
	}
	//end Matrix4x4::operator*



    //=========================================================================
    //! @function    operator * ( const Matrix4x4&, Scalar )
    //! @brief       Return the result of multiplying a matrix by a scalar
    //!              
	//! @param		 lhs [in]
    //! @param       rhs [in]
    //!              
    //! @return      
    //=========================================================================
	Matrix4x4 operator *  ( const Matrix4x4& lhs, Scalar rhs )
	{
		return (Matrix4x4 ( lhs ) *= rhs);
	}
	//end operator * ( Scalar )


    //=========================================================================
    //! @function    operator *
    //! @brief       Return the result of multiplying a vector by a matrix
    //!              
    //! @param       lhs [in] Vector to multiply
    //! @param       rhs [in] Matrix to multiply vector by
    //!              
    //! @return      Result of multiplying lhs by rhs
    //=========================================================================
	Vector3D operator * ( const Vector3D& lhs, const Matrix4x4& rhs )
	{
		return Vector3D(lhs) *= rhs;
	}
	//end operator *


    //=========================================================================
    //! @function    operator *= ( Vector3D&, const Matrix4x4& )
    //! @brief       Multiply a vector by a matrix
    //!              
	//!				 Note that this treats the vector as a 4 component
	//!				 homogenous coordinate, meaning that the W value is taken into account
	//!				 This shouldn't be an issue, unless you explicitly set the W coordinate
	//!				 of the vector, as it is set to 1.0 by default.
	//!
    //! @param       lhs [in] Vector to multiply
    //! @param       rhs [in] Matrix to multiply vector by
    //!              
    //! @return      lhs after being multiplied by rhs
    //=========================================================================
	Vector3D& operator *= ( Vector3D& lhs, const Matrix4x4& rhs )
	{
		//This could be optimised if need be by passing these values
		//directly to the set method of lhs instead of using these three temporaries
		//It's just a bit easier to read this way
		Scalar x = lhs.X() * rhs(0,0) + lhs.Y() * rhs(1,0) + lhs.Z() * rhs(2,0) + lhs.W() * rhs(3,0);
		Scalar y = lhs.X() * rhs(0,1) + lhs.Y() * rhs(1,1) + lhs.Z() * rhs(2,1) + lhs.W() * rhs(3,1);
		Scalar z = lhs.X() * rhs(0,2) + lhs.Y() * rhs(1,2) + lhs.Z() * rhs(2,2) + lhs.W() * rhs(3,2);

		lhs.Set ( x,y,z );

		return lhs;
	}
	//end operator *= ( Vector3D, Matrix4x4 )


#ifdef MATH_IOSTREAM_SUPPORT
	//=========================================================================
	//! @function    operator <<
	//! @brief       Formatted output of a Matrix4x4 to a standard ostream
	//!              
	//! @param       out 
	//! @param       matrixToOutput 
	//!              
	//! @return      
	//! @throw       
	//=========================================================================
	std::ostream& Math::operator << ( std::ostream& out, const Matrix4x4& matrixToOutput )
	{
		out << std::endl;

		for ( UInt row = 0; row < 4; ++row )
		{
			out << "| ";

			for ( UInt col = 0; col < 4; ++col )
			{
				out << matrixToOutput( row, col ) << " ";
			}

			out << "|" << std::endl;
		}

		return out;
	}
	//operator << ( std::ostream, Matrix4x4 )

#endif 
//#ifdef MATH_IOSTREAM_SUPPORT

}; 
//end namespace Math

#endif
//#ifndef MATH_MATRIX4X4