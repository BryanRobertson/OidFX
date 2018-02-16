//======================================================================================
//! @file         Quaternion.cpp
//! @brief        Class representing a quaternion
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 25 May 2005
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
#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "Math/Matrix3x3.h"
#include "Math/Matrix4x4.h"


using namespace Math;



//=========================================================================
//! @function    Quaternion::Quaternion ( const Matrix3x3& )
//! @brief       Construct a quaternion from a 3x3 matrix
//!
//! @param       mat [in] Matrix to construct quaternion from
//!
//=========================================================================
Quaternion::Quaternion ( const Matrix3x3& mat )
{
	//Calculate the trace of the matrix
	//(the sum of the diagonal elements)
	Scalar trace = mat(0,0) + mat(1,1) + mat(2,2);
	
	if ( trace > 0.0f )
	{
		//If the trace of the matrix is greater than zero
		//then |w| > 0.5

		W( Sqrt(trace + 0.5f) );

		Scalar oneOver4W = 1.0f / (4*W());

		X( (mat(2,1)-mat(1,2)) * oneOver4W );
		Y( (mat(0,2)-mat(2,0)) * oneOver4W );
		Z( (mat(1,0)-mat(0,1)) * oneOver4W );
	}
	else
	{
		if ( (mat(0,0) > mat(1,1)) && (mat(0,0) > mat(2,2) ) )
		{
			//mat(0,0) is the largest out of the trace terms
			//so x is larger in magnitude than y or z
			X( Sqrt(mat(0,0) - mat(1,1) - mat(2,2) + 0.5f) );

			Scalar oneOver4X = 1.0f / (4*X());

			W( (mat(2,1) - mat(1,2)) * oneOver4X );
			Y( (mat(1,0) + mat(0,1)) * oneOver4X );
			Z( (mat(2,0) + mat(0,2)) * oneOver4X );

		}
		else if ( (mat(1,1) > mat(0,0)) && (mat(1,1) > mat(2,2)) )
		{
			//mat(1,1) is the largest out of the trace terms
			Y( Sqrt(mat(1,1) - mat(0,0) - mat(2,2) + 0.5f) );

			Scalar oneOver4Y = 1.0f / (4*Y());

			W(mat(0,2) - mat(2,0) * oneOver4Y);
			X(mat(1,0) + mat(0,1) * oneOver4Y);
			Z(mat(2,1) + mat(1,2) * oneOver4Y);
		}
		else
		{
			Z( Sqrt(mat(2,2) - mat(0,0) - mat(1,1) + 0.5f) );

			Scalar oneOver4Z = 1.0f / (4*Z());

			W(mat(1,0) - mat(0,1) * oneOver4Z );
			X(mat(2,0) - mat(0,2) * oneOver4Z );
			Y(mat(2,1) - mat(1,2) * oneOver4Z );
		}
	}

}
//End Quaternion::Quaternion ( const Matrix3x3& )



//=========================================================================
//! @function    Quaternion::Quaternion ( const Matrix4x4& )
//! @brief		 Construct a quaternion from a 4x4 matrix
//!
//!				 Obviously, the translation component of the matrix is ignored
//!				 and only the 3x3 rotation component is relevant
//!
//!	@param		 mat [in] Matrix to construct quaternion from
//!
//=========================================================================
Quaternion::Quaternion ( const Matrix4x4& mat )
{
	//Calculate the trace of the matrix
	//(the sum of the diagonal elements)
	Scalar trace = mat(0,0) + mat(1,1) + mat(2,2);
	
	if ( trace > 0.0f )
	{
		//If the trace of the matrix is greater than zero
		//then |w| > 0.5

		W( Sqrt(trace + 0.5f) );

		Scalar oneOver4W = 1.0f / (4*W());

		X( (mat(2,1)-mat(1,2)) * oneOver4W );
		Y( (mat(0,2)-mat(2,0)) * oneOver4W );
		Z( (mat(1,0)-mat(0,1)) * oneOver4W );
	}
	else
	{
		if ( (mat(0,0) > mat(1,1)) && (mat(0,0) > mat(2,2) ) )
		{
			//mat(0,0) is the largest out of the trace terms
			//so x is larger in magnitude than y or z
			X( Sqrt(mat(0,0) - mat(1,1) - mat(2,2) + 0.5f) );

			Scalar oneOver4X = 1.0f / (4*X());

			W( (mat(2,1) - mat(1,2)) * oneOver4X );
			Y( (mat(1,0) + mat(0,1)) * oneOver4X );
			Z( (mat(2,0) + mat(0,2)) * oneOver4X );

		}
		else if ( (mat(1,1) > mat(0,0)) && (mat(1,1) > mat(2,2)) )
		{
			//mat(1,1) is the largest out of the trace terms
			Y( Sqrt(mat(1,1) - mat(0,0) - mat(2,2) + 0.5f) );

			Scalar oneOver4Y = 1.0f / (4*Y());

			W(mat(0,2) - mat(2,0) * oneOver4Y);
			X(mat(1,0) + mat(0,1) * oneOver4Y);
			Z(mat(2,1) + mat(1,2) * oneOver4Y);
		}
		else
		{
			Z( Sqrt(mat(2,2) - mat(0,0) - mat(1,1) + 0.5f) );

			Scalar oneOver4Z = 1.0f / (4*Z());

			W(mat(1,0) - mat(0,1) * oneOver4Z );
			X(mat(2,0) - mat(0,2) * oneOver4Z );
			Y(mat(2,1) - mat(1,2) * oneOver4Z );
		}
	}
}
//end Quaternion::Quaternion ( const Matrix4x4& )



//=========================================================================
//! @function    Quaternion::Lerp
//! @brief       Perform linear interpolation between two quaternions
//!              
//! @param       t	[in] Amount to interpolate between q1 and q2. Where
//!						 0 <= t <= 1
//! @param       q1	[in] First quaternion
//! @param       q2 [in] Second quaternion
//!              
//! @return      Result of the lerp between q1 and q2
//=========================================================================
Quaternion Quaternion::Lerp ( Scalar t, const Quaternion& q1, const Quaternion& q2 )
{
	debug_assert ( Abs(1.0f - q1.Norm()) < EpsilonE4, "q1 must be a unit quaternion!");
	debug_assert ( Abs(1.0f - q2.Norm()) < EpsilonE4, "q2 must be a unit quaternion!");
	
	Quaternion result( (q1 - q2) * t );
	result += q2;

	return result;
}
//End Quaternion::Slerp



//=========================================================================
//! @function    Quaternion::Slerp
//! @brief       Perform spherical linear interpolation between two quaternions
//!              
//! @param       t	[in] Amount to interpolate between q1 and q2. Where
//!						 0 <= t <= 1
//! @param       q1	[in] First quaternion. Must be a unit quaternion
//! @param       q2 [in] Second quaternion. Must be a unit quaternion
//!              
//! @return      Result of the slerp between q1 and q2
//=========================================================================
Quaternion Quaternion::Slerp ( Scalar t, const Quaternion& q1, const Quaternion& q2 )
{
	debug_assert ( Abs(1.0f - q1.Norm()) < EpsilonE4, "q1 must be a unit quaternion!");
	debug_assert ( Abs(1.0f - q2.Norm()) < EpsilonE4, "q2 must be a unit quaternion!");

	/*
		slerp ( t; q1, q2) = [q1 sin(theta*(1-t)) + q2 sin(theta*t)] / sin(theta)
	*/

	//Treat the two quaternions as four dimensional vectors, and get their dot product
	//so that we can find the angle between them
	Scalar q1Dotq2 = Vector3D::DotProduct ( q1.Vector(), q2.Vector() );

	//If q1Dotq2 is close to one, then fall back to the lerp operation, since
	//sin(theta) approaches zero, as the dot product reaches one
	if ( Abs(1.0f-q1Dotq2) < EpsilonE4 )
	{
		return Lerp(t, q1, q2);
	}

	//OK, we've established that we can't get away with doing a lerp, so now we have
	//to calculate the angle between the two quaternions, using the result of the dot product
	Scalar theta = ACos( q1Dotq2 );

	//Quaternion to hold the result
	Quaternion result(q1);
	
	//If the q1 . q2 < 0, then theta > PI/2. Since q and -q represent the same rotation,
	//it is best to invert q0 or q1, minimising the distance the interpolation has to follow
	if ( q1Dotq2 < 0 )
	{
		//Result only holds q1 at the moment, so this will invert q1
		result.Invert();
	}

	result *= Sin(theta * (1.0f - t));
	result += q2 * Sin(theta * t);

	//Divide the result by sin(theta)
	result *= 1/Sin(theta);
	
	return result;
}
//End Quaternion::Slerp