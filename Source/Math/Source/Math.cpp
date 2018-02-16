//======================================================================================
//! @file         Math.cpp
//! @brief        Shared math constants and functions
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 18 January 2005
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


#include "Math/Math.h"

namespace Math
{

	//Pi constants
	const Scalar Pi			= 3.1415926535897932384626433832795;
	const Scalar TwoPi		= 6.283185307179586476925286766559;
	const Scalar HalfPi		= 1.5707963267948966192313216916398;
	const Scalar QuarterPi	= 0.78539816339744830961566084581988;
	const Scalar InvPi		= 0.31830988618379067153776752674503;

	//Constants for small floating point numbers
	const Scalar EpsilonE4 = 1E-4f;
	const Scalar EpsilonE5 = 1E-5f;
	const Scalar EpsilonE6 = 1E-6f;

};
//end namespace Math



