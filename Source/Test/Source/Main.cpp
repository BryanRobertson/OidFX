//======================================================================================
//! @file         Main.cpp
//! @brief        Main program for Core engine test application
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 21 May 2005
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
#include <iomanip>
#include <fstream>
#include "Core/Core.h"
#include "Math/Math.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "TestMath.h"

int main ( int argc, char* argv[])
{
	
	using namespace Math;

	Quaternion q0 ( Vector3D::XAxis, 20.0f );
	Quaternion q1 ( 0.0f, 20.0f, 10.0f, 56.0f );

	q0.Normalise();

	Quaternion result = Quaternion::TripleProduct ( q0, q1, q0.Conjugate() );
	Vector3D vecResult ( result.X(), result.Y(), result.Z() );

	Vector3D temp ( 20.0f, 10.0f, 56.0f );
	temp *= q0;

	std::clog << vecResult << "     " << temp << std::endl;
	
	return 0;
}