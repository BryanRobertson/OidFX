//======================================================================================
//! @file         Vector3D.cpp
//! @brief        3D Vector class
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
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Math/Vector3D.h"
#include "Math/Quaternion.h"


using namespace Math;


//=========================================================================
// Static initialisation
//=========================================================================
const Vector3D Vector3D::XAxis ( 1.0f, 0.0f, 0.0f );
const Vector3D Vector3D::YAxis ( 0.0f, 1.0f, 0.0f );
const Vector3D Vector3D::ZAxis ( 0.0f, 0.0f, 1.0f );



//=========================================================================
//! @function    operator * ( const Vector3D&, const Quaternion& )
//! @brief       Rotate a Vector by a Quaternion
//!              
//! @param       lhs [in] Vector to rotate 
//! @param       rhs [in] Quaternion to rotate by
//!              
//! @return      The result of the Vector being rotated by the quaternion
//=========================================================================
Vector3D Math::operator * ( const Vector3D& lhs, const Quaternion& rhs )
{
	return Vector3D(lhs) *= rhs;
}
//End operator *


//=========================================================================
//! @function    Vector3D::operator *=
//! @brief       Rotate a Vector by a Quaternion
//!              
//! @param       rhs [in]
//!              
//! @return      *this
//=========================================================================
Vector3D& Math::Vector3D::operator *= ( const Quaternion& rhs )
{
	//First multiply the vector by the quaternion
	Scalar w = -rhs.X()*X() - rhs.Y()*Y() - rhs.Z()*Z();
	Scalar x =  rhs.W()*X() + rhs.Y()*Z() - rhs.Z()*Y(); 
	Scalar y =  rhs.W()*Y() - rhs.X()*Z() + rhs.Z()*X();
	Scalar z =  rhs.W()*Z() + rhs.X()*Y() - rhs.Y()*X();

	//Make temp copies of x, y, and z
	Set(x,y,z);

	//Now multiply the product of the Vector and Quaternion by the conjugate of the Quaternion
	x = w*-rhs.X()	+ X()*rhs.W()	+ Y()*-rhs.Z()	- Z()*-rhs.Y();
	y = w*-rhs.Y()	- X()*-rhs.Z()	+ Y()*rhs.W()	+ Z()*-rhs.X();
	z = w*-rhs.Z()	+ X()*-rhs.Y()	- Y()*-rhs.X()	+ Z()*rhs.W();

	//Set the vector to the final contents of x,y,z
	Set(x,y,z);

	return *this;
}
//End Vector3D::operator *=