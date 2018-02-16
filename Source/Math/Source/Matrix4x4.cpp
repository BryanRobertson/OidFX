//======================================================================================
//! @file         Matrix4x4.cpp
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


#include <iostream>
#include <algorithm>
#include "Math/Vector3D.h"
#include "Math/Matrix4x4.h"
#include "Math/MatrixNxN.h"
#include "Math/Quaternion.h"


using namespace Math;



//=========================================================================
// Static initialisation
//=========================================================================
Matrix4x4 Matrix4x4::IdentityMatrix( 1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0f );


//=========================================================================
//! @function    Matrix4x4::Constructor
//! @brief       Construct a 4x4 matrix from a quaternion
//!              
//! @param       q [in] Quaternion from which to create the matrix     
//=========================================================================
Matrix4x4::Matrix4x4 ( const Quaternion& q )
{
	debug_assert ( Equal( q.Norm(), 1.0f ), "quaternion must be a unit quaternion!" );

	Float xx = q.X() * q.X();
	Float yy = q.Y() * q.Y();
	Float zz = q.Z() * q.Z();
	Float xy = q.X() * q.Y();
	Float xz = q.X() * q.Z();
	Float yz = q.Y() * q.Z();
	Float wx = q.W() * q.X();
	Float wy = q.W() * q.Y();
	Float wz = q.W() * q.Z();

	m_00 = 1.0f - (2.0f * (yy + zz));	
	m_01 = 2.0f * (xy + wz);
	m_02 = 2.0f * (xz - wy);
	m_03 = 0.0f;

	m_10 = 2.0f * (xy - wz);
	m_11 = 1.0f - (2.0f * (xx + zz));
	m_12 = 2.0f * (yz + wx);
	m_13 = 0.0f;

	m_20 = 2.0f * (xz + wy);
	m_21 = 2.0f * (yz - wx);
	m_22 = 1.0f - (2.0f * (xx + yy));
	m_23 = 0.0f;

	m_30 = 0.0f;
	m_31 = 0.0f;
	m_32 = 0.0f;
	m_33 = 1.0f;
}
//End Matrix4x4::Constructor



//=========================================================================
//! @function    Matrix4x4::CreateTranslationMatrix
//! @brief       Create a translation matrix
//!              
//! @param		 mat		 [in]	Matrix to set 
//! @param		 translation [in]	Translation vector
//!
//=========================================================================
void Matrix4x4::CreateTranslationMatrix ( Matrix4x4& mat, const Vector3D& translation )
{
	mat(0,0) = 1.0f;
	mat(0,1) = 0.0f;
	mat(0,2) = 0.0f;
	mat(0,3) = 0.0f;

	mat(1,0) = 0.0f;
	mat(1,1) = 1.0f;
	mat(1,2) = 0.0f;
	mat(1,3) = 0.0f;

	mat(2,0) = 0.0f;
	mat(2,1) = 0.0f;
	mat(2,2) = 1.0f;
	mat(2,3) = 0.0f;
	
	mat(3,0) = translation.X();
	mat(3,1) = translation.Y();
	mat(3,2) = translation.Z();
	mat(3,3) = 1.0f;
}
//End Matrix4x4::CreateTranslationMatrix


//=========================================================================
//! @function    Matrix4x4::CreateRotationMatrixXAxis
//! @brief       Create a matrix consisting of a rotation around the x axis
//!
//!				 In a right-handed system, positive theta values will be counterclockwise
//!				 In a left-handed system, positive theta values will be clockwise
//!
//! @param		 mat   [in]	Matrix to set 
//! @param		 angle [in]	Angle to rotate around the x axis, in radians
//!
//!
//=========================================================================
void Matrix4x4::CreateRotationMatrixXAxis ( Matrix4x4& mat, Scalar angle )
{
	Scalar cosTheta = Cos(angle);
	Scalar sinTheta = Sin(angle);

	mat(0,0) = 1.0f;
	mat(0,1) = 0.0f;
	mat(0,2) = 0.0f;
	mat(0,3) = 0.0f;

	mat(1,0) = 0.0f;
	mat(1,1) = cosTheta;
	mat(1,2) = sinTheta;
	mat(1,3) = 0.0f;

	mat(2,0) = 0.0f;
	mat(2,1) = -sinTheta;
	mat(2,2) = cosTheta;
	mat(2,3) = 0.0f;

	mat(3,0) = 0.0f;
	mat(3,1) = 0.0f;
	mat(3,2) = 0.0f;
	mat(3,3) = 1.0f;
}
//End Matrix4x4::CreateRotationMatrixXAxis



//=========================================================================
//! @function    Matrix4x4::CreateRotationMatrixYAxis
//! @brief       Create a matrix consisting of a rotation around the y-axis
//!
//!				 In a right-handed system, positive theta values will be counterclockwise
//!				 In a left-handed system, positive theta values will be clockwise
//!
//! @param		 mat   [in]	Matrix to set 
//! @param		 angle [in]	Angle to rotate around the y axis, in radians
//!
//!
//=========================================================================
void Matrix4x4::CreateRotationMatrixYAxis ( Matrix4x4& mat, Scalar angle )
{
	Scalar cosTheta = Cos(angle);
	Scalar sinTheta = Sin(angle);

	mat(0,0) = cosTheta;
	mat(0,1) = 0.0f;
	mat(0,2) = -sinTheta;
	mat(0,3) = 0.0f;

	mat(1,0) = 0.0f;
	mat(1,1) = 1.0f;
	mat(1,2) = 0.0f;
	mat(1,3) = 0.0f;

	mat(2,0) = sinTheta;
	mat(2,1) = 0.0f;
	mat(2,2) = cosTheta;
	mat(2,3) = 0.0f;

	mat(3,0) = 0.0f;
	mat(3,1) = 0.0f;
	mat(3,2) = 0.0f;
	mat(3,3) = 1.0f;
}
//End Matrix4x4::CreateRotationMatrixYAxis



//=========================================================================
//! @function    Matrix4x4::CreateRotationMatrixZAxis
//! @brief       Create a matrix consisting of a rotation around the z-axis
//!
//!				 In a right-handed system, positive theta values will be counterclockwise
//!				 In a left-handed system, positive theta values will be clockwise
//!
//! @param		 mat   [in]	Matrix to set 
//! @param		 angle [in]	Angle to rotate around the z axis, in radians
//!
//!
//=========================================================================
void Matrix4x4::CreateRotationMatrixZAxis ( Matrix4x4& mat, Scalar angle )
{
	Scalar cosTheta = Cos(angle);
	Scalar sinTheta = Sin(angle);

	mat(0,0) = cosTheta;
	mat(0,1) = sinTheta;
	mat(0,2) = 0.0f;
	mat(0,3) = 0.0f;

	mat(1,0) = -sinTheta;
	mat(1,1) = cosTheta;
	mat(1,2) = 0.0f;
	mat(1,3) = 0.0f;

	mat(2,0) = 0.0f;
	mat(2,1) = 0.0f;
	mat(2,2) = 1.0f;
	mat(2,3) = 0.0f;

	mat(3,0) = 0.0f;
	mat(3,1) = 0.0f;
	mat(3,2) = 0.0f;
	mat(3,3) = 1.0f;
}
//End Matrix4x4::CreateRotationMatrixZAxis



//=========================================================================
//! @function    Matrix4x4::CreateRotationMatrix
//! @brief       Create a matrix consisting of a rotation around an arbitrary axis
//!
//!				 In a right-handed system, positive theta values will be counterclockwise
//!				 In a left-handed system, positive theta values will be clockwise
//!
//! @param		 mat   [in]	Matrix to set 
//! @param		 axis  [in] Axis around which to rotate
//! @param		 angle [in]	Angle to rotate around the axis, in radians
//!
//!
//=========================================================================
void Matrix4x4::CreateRotationMatrix ( Matrix4x4& mat, const Vector3D& axis, Scalar angle )
{
	//Precalculate cos(theta) and sin(theta), as they will be used more than once
	Scalar cosTheta = Cos(angle);
	Scalar sinTheta = Sin(angle);

	//Create rotation matrix
	mat(0,0) = cosTheta + (axis.X()*axis.X()) * (1.0f-cosTheta);
	mat(0,1) = (axis.X() * axis.Y()) * (1.0f-cosTheta) + (axis.Z() * sinTheta);
	mat(0,2) = (axis.X() * axis.Z()) * (1.0f-cosTheta) - (axis.Y() * sinTheta);
	mat(0,3) = 0.0f;

	mat(1,0) = (axis.X() * axis.Y()) * (1.0f-cosTheta) - (axis.Z() * sinTheta);
	mat(1,1) = cosTheta + (axis.Y()*axis.Y()) * (1.0f-cosTheta);
	mat(1,2) = (axis.X() * axis.Z()) * (1.0f-cosTheta) - (axis.X() * sinTheta);
	mat(1,3) = 0.0f;

	mat(2,0) = (axis.X() * axis.Z()) * (1.0f-cosTheta) + (axis.Y() * sinTheta);
	mat(2,1) = (axis.Y() * axis.Z()) * (1.0f-cosTheta) - (axis.X() * sinTheta);
	mat(2,2) = cosTheta + (axis.Z()*axis.Z()) * (1.0f-cosTheta);
	mat(2,3) = 0.0f;

	mat(3,0) = 0.0f;
	mat(3,1) = 0.0f;
	mat(3,2) = 0.0f;
	mat(3,3) = 1.0f;
}
//End Matrix4x4::CreateRotationMatrix



//=========================================================================
//! @function    Matrix4x4::CreateScalingMatrix
//! @brief       Create a matrix to perform a scaling operation
//!
//!				 
//!
//! @param		 mat		 [in] Matrix to set 
//! @param		 scaleFactor [in] 3D Vector containing scale factor for each dimension
//!
//=========================================================================
void Matrix4x4::CreateScalingMatrix ( Matrix4x4& mat, const Vector3D& scaleFactor )
{
	//Create rotation matrix
	mat(0,0) = scaleFactor.X();
	mat(0,1) = 0.0f;
	mat(0,2) = 0.0f;
	mat(0,3) = 0.0f;

	mat(1,0) = 0.0f;
	mat(1,1) = scaleFactor.Y();
	mat(1,2) = 0.0f;
	mat(1,3) = 0.0f;

	mat(2,0) = 0.0f;
	mat(2,1) = 0.0f;
	mat(2,2) = scaleFactor.Z();
	mat(2,3) = 0.0f;

	mat(3,0) = 0.0f;
	mat(3,1) = 0.0f;
	mat(3,2) = 0.0f;
	mat(3,3) = 1.0f;
}
//End Matrix4x4::CreateScalingMatrix


//=========================================================================
//! @function    Matrix4x4::CreateUVNCameraMatrixLH
//! @brief       Create a UVN camera matrix for a left coordinate handed system
//!
//!				 This math API assumes a right handed system. 
//!				 If you're using a left handed rendering API, such as DirectX
//!				 use can use this function to generate a left handed
//!				 look at matrix.
//!
//!				 To use a left handed renderer with a right handed coordinate system,
//!				 we need to flip the view vector. That's what this method does
//!
//!
//! @param		 mat	[in]	Matrix to set 
//! @param		 eye	[in]	Eye point for the camera
//! @param		 up		[in]	Up vector for the camera
//! @param		 lookAt	[in]	Point the camera is looking at
//!
//!
//=========================================================================
void Matrix4x4::CreateUVNCameraMatrixLH ( Matrix4x4& mat, const Vector3D& eye, const Vector3D& up, const Vector3D& lookAt )
{
	//First we need to get the vector from the eye to the lookAt position
	//This will be our N vector
	//
	//Note that because we're generating a left handed view vector in a right
	//handed system, the vector is actually generated by calculating eye - lookAt
	//so that we get a vector in the opposite direction from what you would expect
	Vector3D N(eye);
	N -= lookAt;
	N.Normalise();

	//Now, to get the right, or "U" vector, we need to get the cross product
	//of the N vector and the up vector
	Vector3D U;
	Vector3D::CrossProduct ( up, N, U );
	U.Normalise();

	//Finally, to get our final up, or "V" vector, we get the cross product between
	//the U and N vector
	Vector3D V;
	Vector3D::CrossProduct ( N, U, V );
	V.Normalise();

	//Set the output matrix to the inverse camera position.
	//Remember, when the camera moves forward, we want the world to move backwards
	mat(0,0) = 1.0f;		mat(0,1) = 0.0f;		mat(0,2) = 0.0f;		mat(0,3) = 0.0f;
	mat(1,0) = 0.0f;		mat(1,1) = 1.0f;		mat(1,2) = 0.0f;		mat(1,3) = 0.0f;
	mat(2,0) = 0.0f;		mat(2,1) = 0.0f;		mat(2,2) = 1.0f;		mat(2,3) = 0.0f;
	mat(3,0) = -eye.X();	mat(3,1) = -eye.Y();	mat(3,2) = -eye.Z();	mat(3,3) = 1.0f;

	//Create a matrix for our UVN translation
	//Note that the vectors form the columns of the matrix, not the rows.
	//
	//Our matrix is row major format, meaning that the basis vectors form the rows, not the columns.
	//Why then is it that the basis vectors form the columns of the matrix?
	//
	//The reason, is because the inverse of an orthonormal matrix (like our UVN matrix), is its transpose
	//Again, remember we want the world to move in the opposite direction from our camera!
	//
	//Optimisation notes: We could avoid creating this temporary, by doing the matrix multiplcation
	//					  of the inverse camera position by the UVN matrix ourselves, but
	//					  there's no point in doing that, unless this turns up as a bottleneck in profiling.
	//					  It's more readable this way.
	Matrix4x4 UVN ( U.X(),   V.X(),   N.X(),	0.0f,
					U.Y(),   V.Y(),   N.Y(),	0.0f,
					U.Z(),   V.Z(),   N.Z(),	0.0f,
					0.0f ,   0.0f ,	  0.0f,		1.0f );

	//Multiply our inverse camera matrix by our UVN matrix to get the final result
	mat *= UVN;

}
//End CreateUVNCameraMatrixLH



//=========================================================================
//! @function    Matrix4x4::CreateUVNCameraMatrixRH
//! @brief       Create a UVN camera matrix for a right handed system
//!
//!				 This math API assumes a right handed coordinate system. 
//!				 If you're using a right handed rendering API, such as OpenGL
//!				 then this is the right function to use when generating
//!				 a view matrix
//!
//!				 This version doesn't do any flipping of the view vector,
//!				 because we don't want that.
//!
//! @param		 mat	[in]	Matrix to set 
//! @param		 eye	[in]	Eye point for the camera
//! @param		 up		[in]	Up vector for the camera
//! @param		 lookAt	[in]	Point the camera is looking at
//!
//!
//=========================================================================
void Matrix4x4::CreateUVNCameraMatrixRH ( Matrix4x4& mat, const Vector3D& eye, const Vector3D& up, const Vector3D& lookAt )
{
	//First we need to get the  vector from the eye to the lookAt position
	//This will be our N vector
	Vector3D N(lookAt);
	N -= eye;
	N.Normalise();

	//Now, to get the right, or "U" vector, we need to get the cross product
	//of the N vector and the up vector
	Vector3D U;
	Vector3D::CrossProduct ( up, N, U );
	U.Normalise();

	//Finally, to get our final up, or "V" vector, we get the cross product between
	//the U and N vector
	Vector3D V;
	Vector3D::CrossProduct ( N, U, V );
	V.Normalise();

	//Set the output matrix to the inverse camera position.
	//Remember, when the camera moves forward, we want the world to move backwards
	mat(0,0) = 1.0f;		mat(0,1) = 0.0f;		mat(0,2) = 0.0f;		mat(0,3) = 0.0f;
	mat(1,0) = 0.0f;		mat(1,1) = 1.0f;		mat(1,2) = 0.0f;		mat(1,3) = 0.0f;
	mat(2,0) = 0.0f;		mat(2,1) = 0.0f;		mat(2,2) = 1.0f;		mat(2,3) = 0.0f;
	mat(3,0) = -eye.X();	mat(3,1) = -eye.Y();	mat(3,2) = -eye.Z();	mat(3,3) = 1.0f;

	//Create a matrix for our UVN translation
	//Note that the vectors form the columns of the matrix, not the rows.
	//
	//Our matrix is row major format, meaning that the basis vectors form the rows, not the columns.
	//Why then is it that the basis vectors form the columns of the matrix?
	//
	//The reason, is because the inverse of an orthonormal matrix (like our UVN matrix), is its transpose
	//Again, remember we want the world to move in the opposite direction from our camera!
	//
	//Optimisation notes: We could avoid creating this temporary, by doing the matrix multiplcation
	//					  of the inverse camera position by the UVN matrix ourselves, but
	//					  there's no point in doing that, unless this turns up as a bottleneck in profiling.
	//					  It's more readable this way.
	Matrix4x4 UVN ( U.X(),   V.X(),   N.X(),	0.0f,
					U.Y(),   V.Y(),   N.Y(),	0.0f,
					U.Z(),   V.Z(),   N.Z(),	0.0f,
					0.0f ,   0.0f ,	  0.0f,		1.0f );

	//Multiply our inverse camera matrix by our UVN matrix to get the final result
	mat *= UVN;

}
//End CreateUVNCameraMatrix



//=========================================================================
//! @function    Matrix4x4::CreateUVNCameraFromViewVectorLH
//! @brief       Create a UVN camera matrix for a left coordinate handed system
//!				 from a position, a view vector and an up vector
//!
//! @param		 mat	[in]	Matrix to set 
//! @param		 eye	[in]	Position of camera
//! @param		 view	[in]	View vector for the camera, must be normalised
//! @param		 up		[in]	Up vector for the camera
//!
//=========================================================================
void Matrix4x4::CreateUVNCameraFromViewVectorLH ( Matrix4x4& mat, const Vector3D& eye, const Vector3D& view, const Vector3D& up )
{
	debug_assert ( Equal(view.Length(), 1.0f), "view vector must be normalised!" );

	//Reverse the view vector, to compensate for the left handed coordinate system
	Vector3D N = -view;

	//To get the right, or "U" vector, we need to get the cross product
	//of the N vector and the up vector
	Vector3D U;
	Vector3D::CrossProduct ( up, view, U );
	U.Normalise();

	//Finally, to get our final up, or "V" vector, we get the cross product between
	//the U and N vector
	Vector3D V;
	Vector3D::CrossProduct ( view, U, V );
	V.Normalise();

	//Set the output matrix to the inverse camera position.
	//Remember, when the camera moves forward, we want the world to move backwards
	mat(0,0) = 1.0f;		mat(0,1) = 0.0f;		mat(0,2) = 0.0f;		mat(0,3) = 0.0f;
	mat(1,0) = 0.0f;		mat(1,1) = 1.0f;		mat(1,2) = 0.0f;		mat(1,3) = 0.0f;
	mat(2,0) = 0.0f;		mat(2,1) = 0.0f;		mat(2,2) = 1.0f;		mat(2,3) = 0.0f;
	mat(3,0) = -eye.X();	mat(3,1) = -eye.Y();	mat(3,2) = -eye.Z();	mat(3,3) = 1.0f;

	//Create a matrix for our UVN translation
	//Note that the vectors form the columns of the matrix, not the rows.
	//
	//Our matrix is row major format, meaning that the basis vectors form the rows, not the columns.
	//Why then is it that the basis vectors form the columns of the matrix?
	//
	//The reason, is because the inverse of an orthonormal matrix (like our UVN matrix), is its transpose
	//Again, remember we want the world to move in the opposite direction from our camera!
	//
	//Optimisation notes: We could avoid creating this temporary, by doing the matrix multiplcation
	//					  of the inverse camera position by the UVN matrix ourselves, but
	//					  there's no point in doing that, unless this turns up as a bottleneck in profiling.
	//					  It's more readable this way.
	Matrix4x4 UVN ( U.X(),   V.X(),   N.X(),	0.0f,
					U.Y(),   V.Y(),   N.Y(),	0.0f,
					U.Z(),   V.Z(),   N.Z(),	0.0f,
					0.0f ,   0.0f ,	  0.0f,		1.0f );

	//Multiply our inverse camera matrix by our UVN matrix to get the final result
	mat *= UVN;

}
//End CreateUVNCameraMatrixLH



//=========================================================================
//! @function    Matrix4x4::CreateUVNCameraFromViewVectorLH
//! @brief       Create a UVN camera matrix for a left coordinate handed system
//!				 from a position, a view vector and an up vector
//!
//! @param		 mat	[in]	Matrix to set 
//! @param		 eye	[in]	Position of camera
//! @param		 view	[in]	View vector for the camera, must be normalised
//! @param		 up		[in]	Up vector for the camera
//!
//=========================================================================
void Matrix4x4::CreateUVNCameraFromViewVectorRH ( Matrix4x4& mat, const Vector3D& eye, const Vector3D& view, const Vector3D& up )
{
	debug_assert ( Equal(view.Length(), 1.0f), "view vector must be normalised!" );

	//To get the right, or "U" vector, we need to get the cross product
	//of the N vector and the up vector
	Vector3D U;
	Vector3D::CrossProduct ( up, view, U );
	U.Normalise();

	//Finally, to get our final up, or "V" vector, we get the cross product between
	//the U and N vector
	Vector3D V;
	Vector3D::CrossProduct ( view, U, V );
	V.Normalise();

	//Set the output matrix to the inverse camera position.
	//Remember, when the camera moves forward, we want the world to move backwards
	mat(0,0) = 1.0f;		mat(0,1) = 0.0f;		mat(0,2) = 0.0f;		mat(0,3) = 0.0f;
	mat(1,0) = 0.0f;		mat(1,1) = 1.0f;		mat(1,2) = 0.0f;		mat(1,3) = 0.0f;
	mat(2,0) = 0.0f;		mat(2,1) = 0.0f;		mat(2,2) = 1.0f;		mat(2,3) = 0.0f;
	mat(3,0) = -eye.X();	mat(3,1) = -eye.Y();	mat(3,2) = -eye.Z();	mat(3,3) = 1.0f;

	//Create a matrix for our UVN translation
	//Note that the vectors form the columns of the matrix, not the rows.
	//
	//Our matrix is row major format, meaning that the basis vectors form the rows, not the columns.
	//Why then is it that the basis vectors form the columns of the matrix?
	//
	//The reason, is because the inverse of an orthonormal matrix (like our UVN matrix), is its transpose
	//Again, remember we want the world to move in the opposite direction from our camera!
	//
	//Optimisation notes: We could avoid creating this temporary, by doing the matrix multiplcation
	//					  of the inverse camera position by the UVN matrix ourselves, but
	//					  there's no point in doing that, unless this turns up as a bottleneck in profiling.
	//					  It's more readable this way.
	Matrix4x4 UVN ( U.X(),   V.X(),   view.X(),	0.0f,
					U.Y(),   V.Y(),   view.Y(),	0.0f,
					U.Z(),   V.Z(),   view.Z(),	0.0f,
					0.0f ,   0.0f ,	  0.0f,		1.0f );

	//Multiply our inverse camera matrix by our UVN matrix to get the final result
	mat *= UVN;

}
//End CreateUVNCameraFromViewVectorRH



//=========================================================================
//! @function    Matrix4x4::CreatePerspectiveProjectionLH
//! @brief       Create a projection transformm matrix for a left handed renderer
//!
//!				 This math API assumes a right handed system. 
//!				 If you're using a left handed rendering API, such as DirectX
//!				 use can use this function to generate a left handed
//!				 projection matrix.
//!
//!
//! @param		 mat		 [in]	Matrix to set 
//! @param		 fovY		 [in]	Field of view in y direction
//! @param		 aspectRatio [in]	Ratio of width to height
//! @param		 zNear		 [in]	Value of z at near clipping plane
//! @param		 zFar		 [in]	Value of z at far clipping plane
//!
//!
//=========================================================================
void Matrix4x4::CreatePerspectiveProjectionLH ( Matrix4x4& mat, Scalar fovY, Scalar aspectRatio, Scalar zNear, Scalar zFar )
{
	Scalar yScale = Cot(fovY/2);
	Scalar xScale = aspectRatio * yScale;

	mat(0,0) = xScale;		
	mat(0,1) = 0.0f;		
	mat(0,2) = 0.0f;					
	mat(0,3) = 0.0f;
	mat(1,0) = 0.0f;		
	mat(1,1) = yScale;		
	mat(1,2) = 0.0f;					
	mat(1,3) = 0.0f;
	mat(2,0) = 0.0f;		
	mat(2,1) = 0.0f;		
	mat(2,2) = zFar/(zNear-zFar);		
	mat(2,3) = -1.0f;
	mat(3,0) = 0.0f;		
	mat(3,1) = 0.0f;		
	mat(3,2) = zNear*zFar/(zNear-zFar);
	mat(3,3) = 0.0f;

}
//End Matrix4x4::CreatePerspectiveProjectionLH 


//=========================================================================
//! @function    Matrix4x4::CreatePerspectiveProjectionRH
//! @brief       Create a projection transformm matrix for a right handed renderer
//!
//!				 This math API assumes a right handed system. 
//!				 If you're using a right handed rendering API, such as OpenGL
//!				 then this is the right function to use when generating a perspective
//!				 projection matrix
//!
//!
//! @param		 mat		 [in]	Matrix to set 
//! @param		 fovY		 [in]	Field of view in y direction
//! @param		 aspectRatio [in]	Ratio of width to height
//! @param		 zNear		 [in]	Value of z at near clipping plane
//! @param		 zFar		 [in]	Value of z at far clipping plane
//!
//!
//=========================================================================
void Matrix4x4::CreatePerspectiveProjectionRH ( Matrix4x4& mat, Scalar fovY, Scalar aspectRatio, Scalar zNear, Scalar zFar )
{
		Scalar yScale = Cot(fovY/2);
		Scalar xScale = aspectRatio * yScale;

		mat(0,0) = xScale;		
		mat(0,1) = 0.0f;		
		mat(0,2) = 0.0f;					
		mat(0,3) = 0.0f;
		mat(1,0) = 0.0f;		
		mat(1,1) = yScale;		
		mat(1,2) = 0.0f;					
		mat(1,3) = 0.0f;
		mat(2,0) = 0.0f;		
		mat(2,1) = 0.0f;		
		mat(2,2) = zFar/(zFar-zNear);		
		mat(2,3) = 1.0f;
		mat(3,0) = 0.0f;		
		mat(3,1) = 0.0f;		
		mat(3,2) = -zNear*zFar/(zFar-zNear);
		mat(3,3) = 0.0f;
	
}
//End Matrix4x4::CreatePerspectiveProjectionRH



//=========================================================================
//! @function    Matrix4x4::CreateOrthographicProjectionLH
//! @brief       Create an orthographic projection transformm matrix for a left handed renderer
//!
//!				 This math API assumes a right handed system. 
//!				 If you're using a left handed rendering API, such as DirectX
//!				 use can use this function to generate a left handed
//!				 projection matrix.
//!
//!
//! @param		 mat		 [in]	Matrix to set 
//! @param		 left		 [in]	Coordinate for the left clipping plane
//! @param		 right		 [in]	Coordinate for the right clipping plane
//! @param		 top		 [in]	Coordinate for the top clipping plane
//! @param		 bottom		 [in]   Coordinate for the bottom clipping plane
//! @param		 zNear		 [in]	Value of z at near clipping plane
//! @param		 zFar		 [in]	Value of z at far clipping plane
//!
//!
//=========================================================================
void Matrix4x4::CreateOrthographicProjectionLH ( Matrix4x4& mat, 
											   Scalar left, Scalar right, 
											   Scalar bottom, Scalar top, 
											   Scalar zNear, Scalar zFar )
{
	mat(0,0) = 2/(right-left);		
	mat(0,1) = 0.0f;		
	mat(0,2) = 0.0f;					
	mat(0,3) = 0.0f;
	mat(1,0) = 0.0f;		
	mat(1,1) = 2/(top-bottom);		
	mat(1,2) = 0.0f;					
	mat(1,3) = 0.0f;
	mat(2,0) = 0.0f;		
	mat(2,1) = 0.0f;		
	mat(2,2) = -2.0f/(zFar-zNear);		
	mat(2,3) = 0.0f;
	mat(3,0) = (right+left)/(left-right);		
	mat(3,1) = (top+bottom)/(bottom-top);		
	mat(3,2) = (zNear)/(zNear-zFar);
	mat(3,3) = 1.0f;

}
//End Matrix4x4::CreateOrthographicProjection



//=========================================================================
//! @function    Matrix4x4::CreateOrthographicProjectionRH
//! @brief       Create an orthographic projection transformm matrix for a left handed renderer
//!
//!				 This math API assumes a right handed system. 
//!				 If you're using a right handed rendering API, such as OpenGL
//!				 This is the function to use to generate an orthographic projection
//!
//!
//! @param		 mat		 [in]	Matrix to set 
//! @param		 fovY		 [in]	Field of view in y direction
//! @param		 aspectRatio [in]	Ratio of width to height
//! @param		 zNear		 [in]	Value of z at near clipping plane
//! @param		 zFar		 [in]	Value of z at far clipping plane
//!
//!
//=========================================================================
void Matrix4x4::CreateOrthographicProjectionRH ( Matrix4x4& mat, 
											   Scalar left, Scalar right, 
											   Scalar bottom, Scalar top, 
											   Scalar zNear, Scalar zFar )
{
	mat(0,0) = 2/(right-left);		
	mat(0,1) = 0.0f;		
	mat(0,2) = 0.0f;					
	mat(0,3) = 0.0f;
	mat(1,0) = 0.0f;		
	mat(1,1) = 2/(top-bottom);		
	mat(1,2) = 0.0f;					
	mat(1,3) = 0.0f;
	mat(2,0) = 0.0f;		
	mat(2,1) = 0.0f;		
	mat(2,2) = -2.0f/(zNear-zFar);	
	mat(2,3) = 0.0f;
	mat(3,0) = (right+left)/(left-right);		
	mat(3,1) = (top+bottom)/(bottom-top);			
	mat(3,2) = zNear/(zNear-zFar);
	mat(3,3) = 1.0f;

}
//End Matrix4x4::CreateOrthographicProjection


//=========================================================================
//! @function    Matrix4x4::Invert
//! @brief       Invert a 4x4 Matrix, if possible
//!              
//!				 Uses guassian elimination to invert a 4x4 matrix
//!
//!              
//! @return      Returns true if the matrix was inverted successfully
//!				 Returns false if the matrix could not be inverted. Contents
//!				 of the matrix will then be undefined
//=========================================================================
bool Matrix4x4::Invert ( )
{
	//Create an augmented matrix with this matrix on the left, and 
	//the identity matrix on the right
	Matrix<ms_numCols*2, ms_numRows> aug;

	//Copy the matrices to the augmented matrix
	for ( UInt row=0; row < ms_numRows; ++row )
	{
		for ( UInt col=0; col < ms_numCols; ++col )
		{
			//Copy this matrix to the left hand side
			aug(row,col) = operator()(row,col);
			
			//and the identity matrix to the right
			aug(row,col+ms_numCols) = (row == col) ? 1.0f : 0.0f; 
		}
	}

	bool singular = true;

	//
	for ( UInt j=0; j < ms_numCols; ++j )
	{
		singular = true;

		for ( UInt i=j; i < aug.ms_numRows; ++i )
		{
			if (aug(i,j) != 0.0f)
			{
				singular = false;

				if ( i != j )
				{
					//Swap rows i, and j
					aug.SwapRows( i, j );
				}

				//Multiply row j by 1/aug(j,j)
				aug.MultiplyRow(j, 1.0f/aug(j,j));


				for ( UInt r=0; r < aug.ms_numRows; ++r )
				{
					if ( r != j )
					{
						aug.AddMultipleOfRowToRow(j, r, -aug(r,j)); 
					}
				}
				
			}
		}
	}

	if ( singular == true )
	{
		return false;
	}
	else
	{
		//Copy the matrix values into this matrix
		for ( UInt row=0; row < ms_numRows; ++row )
		{
			for ( UInt col=0; col < ms_numCols; ++col )
			{
				//Copy this matrix to the left hand side
				operator()(row,col) = aug(row,col+ms_numCols) ;
			}
		}

		return true;
	}
}
//end Matrix4x4::Invert ( )



//=========================================================================
//! @function    Matrix4x4::InvertByTranspose
//! @brief       Invert a matrix by setting it to its inverse transpose
//!              
//!				 Note that this will only work for orthonormal matrices
//!            
//=========================================================================
void Matrix4x4::InvertByTranspose ( )
{
	//Get the translation component, we'll need it later
	Scalar transX = m_30;
	Scalar transY = m_31;
	Scalar transZ = m_32;

	//Zero out the translation component, we don't want it to 
	//form part of the transpose
	m_30 = 0.0f;
	m_31 = 0.0f;
	m_32 = 0.0f;

	//Transpose the matrix
	Transpose();

	//Set the translation component of the matrix
	//by multiplying the old translation component, by
	//the rotation part of the newly transposed matrix
	m_30 = transX * m_00 + transY * m_10 + transZ * m_20;
	m_31 = transX * m_01 + transY * m_11 + transZ * m_21; 
	m_32 = transX * m_02 + transY * m_12 + transZ * m_22; 

}
//End Matrix4x4::InvertByTranspose



//=========================================================================
//! @function    Matrix4x4::SwapColumn
//! @brief       Swap the column indexed by firstIndex, with the column
//!				 indexed by secondIndex
//!              
//! @param       firstIndex  [in]
//! @param       secondIndex [in]
//!              
//=========================================================================
void Matrix4x4::SwapColumn ( UInt firstIndex, UInt secondIndex )
{
	//Make sure firstIndex and secondIndex are in range
	debug_assert ( (firstIndex < ms_numCols), "First column index out of range" )
	debug_assert ( (secondIndex < ms_numCols), "Second column index out of range" ); 

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
//end Matrix4x4::SwapColumn


//=========================================================================
//! @function    Matrix4x4::Determinate
//! @brief       Return the determinate of a 4x4 matrix
//!              
//!              
//! @return      The determinate of the matrix
//=========================================================================
Scalar Matrix4x4::Determinate ( ) const
{
	return ( m_00 * (m_11 * (m_22 * m_33 - m_23 * m_32) - m_21 * (m_12 * m_33 - m_13 * m_32)
				 + (m_12 * m_23 - m_13 * m_22) * m_31) - m_10 * (m_01 * (m_22 * m_33 - m_23 * m_32)
				 - m_21 * (m_02 * m_33 - m_03 * m_32) + (m_02 * m_23 - m_03 * m_22) * m_31)
				 + m_20 * (m_01 * (m_12 * m_33 - m_13 * m_32) - m_11 * (m_02 * m_33 - m_03 * m_32)
				 + (m_02 * m_13 - m_03 * m_12) * m_31) - (m_01 * (m_12 * m_23 - m_13 * m_22)
				 - m_11 * (m_02 * m_23 - m_03 * m_22) + (m_02 * m_13 - m_03 * m_12) * m_21) * m_30 ) ;
}
//end Matrix4x4::Determinate ( )


//=========================================================================
//! @function    Matrix4x4::Transpose
//! @brief       Swap the rows of the matrix with the columns, such that m[i,j] becomes m[j,i]
//!              
//=========================================================================
void Matrix4x4::Transpose ( )
{
	std::swap ( m_01 , m_10 );
	std::swap ( m_02 , m_20 );
	std::swap ( m_03 , m_30 );

	std::swap ( m_12 , m_21 );
	std::swap ( m_13,  m_31 );	
	std::swap ( m_23,  m_32 );

}
//Matrix4x4::Transpose ( )