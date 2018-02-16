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



#include <iostream>
#include <iomanip>
#include "Core/Core.h"
#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/Matrix4x4.h"
#include "TestMath.h"


void TestMatrix()
{

	using namespace Math;

	Matrix4x4 mat1 ( 1, 2, 3, 4, 
						   5, 6, 7, 8, 
						   9, 10, 11, 12, 
						   13, 14, 15, 16 );

	Matrix4x4 mat2 ( 1, 2, 3, 4, 
						   5, 6, 7, 8, 
						   9, 10, 11, 12, 
						   13, 14, 15, 16 );

	std::cout << "mat1 = " << mat1 << std::endl;
	std::cout << "mat2 = " << mat2 << std::endl;
	std::cout << "mat1 + mat2 = " << (mat1+mat2) << std::endl;
	std::cout << "mat1 * mat2 = " << (mat1*mat2) << std::endl;
	std::cout << "mat2 * mat1 = " << (mat2*mat1) << std::endl;
	
	mat1.Transpose();
	std::cout << "mat1 T = " << mat1 << std::endl;

	Matrix4x4::CreateTranslationMatrix( mat1, Vector3D(1.0, 2.0, 3.0) );
	std::cout << "translation matrix: mat1" << mat1 << std::endl;

	Vector3D vec;
	std::cout << "vec = " << vec << std::endl;
	std::cout << "vec * mat1 = " << vec * mat1 << std::endl;

	Matrix4x4 A (  2.0,  3.0,  8.0,  0.0,
						   6.0,  0.0, -3.0,  0.0,
						  -1.0,  3.0,  2.0,  0.0,
						   0.0,  0.0,  0.0,  1.0);


	std::cout << "YAxis rotation test" << std::endl;
	std::cout << "=================================================" << std::endl;
	Matrix4x4::CreateRotationMatrix ( mat1, Vector3D(0.0f, 1.0f, 0.0f), Math::DegreesToRadians(180.0f) );
	std::cout << "rotation matrix: mat1" << mat1 << std::endl;
	
	std::cout << "rotation matrix * inverse transpose = " << std::endl;
	Matrix4x4 mat1Inv;
	mat1.FastInvert ( mat1Inv );
	std::cout << mat1 * mat1Inv << std::endl;
	debug_assert ( (mat1 * mat1Inv) == Matrix4x4(), "Test failed! mat1 isn't equal to identity!" );

	Matrix4x4::CreateRotationMatrixYAxis ( mat1, Math::DegreesToRadians(180.0f) );
	std::cout << "rotation matrix y axis: mat1" << mat1 << std::endl;
	std::cout << "rotation matrix * inverse transpose = " << std::endl;
	mat1.FastInvert ( mat1Inv );
	std::cout << mat1 * mat1Inv << std::endl;
	debug_assert ( (mat1 * mat1Inv) == Matrix4x4(), "Test failed! mat1 isn't equal to identity!" );

	std::cout << "XAxis rotation test" << std::endl;
	std::cout << "=================================================" << std::endl;
	Matrix4x4::CreateRotationMatrix ( mat1, Vector3D(1.0f, 0.0f, 0.0f), Math::DegreesToRadians(180.0f) );
	std::cout << "rotation matrix: mat1" << mat1 << std::endl;
	
	std::cout << "rotation matrix * inverse transpose = " << std::endl;
	mat1.FastInvert ( mat1Inv );
	std::cout << mat1 * mat1Inv << std::endl;
	debug_assert ( (mat1 * mat1Inv) == Matrix4x4(), "Test failed! mat1 isn't equal to identity!" );

	Matrix4x4::CreateRotationMatrixXAxis ( mat1, Math::DegreesToRadians(180.0f) );
	std::cout << "rotation matrix x axis: mat1" << mat1 << std::endl;
	std::cout << "rotation matrix * inverse transpose = " << std::endl;
	mat1.FastInvert ( mat1Inv );
	std::cout << mat1 * mat1Inv << std::endl;
	debug_assert ( (mat1 * mat1Inv) == Matrix4x4(), "Test failed! mat1 isn't equal to identity!" );

	std::cout << "ZAxis rotation test" << std::endl;
	std::cout << "=================================================" << std::endl;
	Matrix4x4::CreateRotationMatrix ( mat1, Vector3D(0.0f, 0.0f, 1.0f), Math::DegreesToRadians(180.0f) );
	std::cout << "rotation matrix: mat1" << mat1 << std::endl;
	
	std::cout << "rotation matrix * inverse transpose = " << std::endl;
	mat1.FastInvert ( mat1Inv );
	std::cout << mat1 * mat1Inv << std::endl;
	debug_assert ( (mat1 * mat1Inv) == Matrix4x4(), "Test failed! mat1 isn't equal to identity!" );

	Matrix4x4::CreateRotationMatrixZAxis ( mat1, Math::DegreesToRadians(180.0f) );
	std::cout << "rotation matrix z axis: mat1" << mat1 << std::endl;
	std::cout << "rotation matrix * inverse transpose = " << std::endl;
	mat1.FastInvert ( mat1Inv );
	std::cout << mat1 * mat1Inv << std::endl;
	debug_assert ( (mat1 * mat1Inv) == Matrix4x4(), "Test failed! mat1 isn't equal to identity!" );

	Matrix4x4::CreateScalingMatrix( mat1, Vector3D(10.0f, 20.0f, 30.0f) );
	std::cout << "Scaling matrix: mat1" << mat1 << std::endl;

	Matrix4x4::CreateUVNCameraMatrixRH ( mat1, Vector3D(0.0f, 0.0f, 0.0f), Vector3D::YAxis, Vector3D(0.0f, 0.0f, 20.0f ) );
	std::cout << "UVN camera matrix at the origin looking down the Z axis" << mat1 << std::endl;

	Matrix4x4::CreateUVNCameraMatrixLH ( mat1, Vector3D(0.0f, 0.0f, 0.0f), Vector3D::YAxis, Vector3D(0.0f, 0.0f, 20.0f ) );
	std::cout << "LH UVN camera matrix at the origin looking down the Z axis" << mat1 << std::endl;

	Matrix4x4::CreateUVNCameraMatrixRH ( mat1, Vector3D(10.0f, 20.0f, 90.0f), Vector3D::YAxis, Vector3D(1.0f, 4.0f, 20.0f ) );
	std::cout << "UVN camera matrix" << mat1 << std::endl;

	Matrix4x4::CreateUVNCameraMatrixLH ( mat1, Vector3D(10.0f, 20.0f, 90.0f), Vector3D::YAxis, Vector3D(1.0f, 4.0f, 20.0f ) );
	std::cout << "LH UVN camera matrix " << mat1 << std::endl;

	Matrix4x4::CreatePerspectiveProjectionRH ( mat1, 90, 0.7, -1, 400 );
	std::cout << "Perspective projection matrix" << mat1 << std::endl;

	Matrix4x4::CreatePerspectiveProjectionLH ( mat1, 90, 0.7, -1, 400 );
	std::cout << "LH Perspective projection matrix" << mat1 << std::endl;

	Matrix4x4::CreateOrthographicProjectionRH ( mat1, 0, 640, 480, 0, -1, 100 );
	std::cout << "Orthographic projection matrix" << mat1 << std::endl;

	Matrix4x4::CreateOrthographicProjectionLH ( mat1, 0, 640, 480, 0, -1, 100 );
	std::cout << "LH Orthographic projection matrix" << mat1 << std::endl;


	std::cout << "Matrix inversion test:\nA =";
	std::cout << A << std::endl;

	std::cout << "A After inversion =";
	A.Invert();

	std::cout << A << std::endl;

	std::cout << "Now we're going to multiply the original value of A with its inverse\n"
			  << "to see if we get the identity matrix\n";

	Matrix4x4 B (  2.0,  3.0,  8.0,  0.0,
						   6.0,  0.0, -3.0,  0.0,
						  -1.0,  3.0,  2.0,  0.0,
						   0.0,  0.0,  0.0,  1.0);

	B *= A;

	Matrix4x4 singular (  0.0f, 0.0f, 0.0f, 0.0f,
								1.0f, 2.0f, 2.0f, 1.0f,
								0.0f, 0.0f, 0.0f, 0.0f,
								30.0f, 32.0f, 104.f, 20.0f );

	if ( singular.Invert() )
	{
		std::cerr << "Error, Matrix4x4::Invert() claims to have inverted a singular matrix!" << std::endl;
	}

	std::cout << "result = " << std::endl;
	std::cout << B << std::endl;

	debug_assert ( B == Matrix4x4(), "Test failed! B isn't equal to identity!" );
}


void TestVector()
{
	using namespace Math;

	Vector3D vector1, vector2, result;

	std::cout << "Vector3D tests\n"
				 "First, check the dot product operation\n";

	std::cout << "XAxis . YAxis = " << Vector3D::DotProduct(Vector3D::XAxis, Vector3D::YAxis) << std::endl;;

	debug_assert ( Equal(Vector3D::DotProduct(Vector3D::XAxis, Vector3D::YAxis), 0.0f),
					"Test failed!: Dot product of x axis and y axis should be 0.0!");


	Vector3D::CrossProduct(Vector3D::XAxis, Vector3D::YAxis, result);
	std::cout << "XAxis x YAxis = " << result << std::endl;

	Vector3D::CrossProduct(Vector3D::YAxis, Vector3D::XAxis, result);
	std::cout << "YAxis x XAxis = " << result << std::endl;

	vector1 = Vector3D( 6.0, 2.0, 30.0 ); 
	vector2 = -vector1;

	std::cout << vector1 << " "<< vector2 << " " << -vector2 << std::endl;
	debug_assert ( vector1 == (-vector2), "Problem with vector operator -" );
	
	std::cout << "vector1.Length() = " << vector1.Length() << std::endl;
	vector1.Normalise();
	std::cout << "vector1.Length() after normalise = " << vector1.Length() << std::endl;
	debug_assert ( Equal(vector1.Length(), 1.0f), "Vector length != 1 after normalise!" );

	std::cout << "vector1 *= 2 /= 2" << (vector1 * 2) / 2 << std::endl;

	debug_assert ( vector1 == ((vector1 * 2) / 2) , "vector1 * 2 / 2 should be equal to vector1" );

	vector1 = Vector3D ( 1,2,3);
	vector2 = Vector3D ( 1,2,3);

	std::cout << "vector1 + vector2" << vector1 + vector2 << std::endl;
	std::cout << "vector1 - vector2" << vector1 - vector2 << std::endl;

}