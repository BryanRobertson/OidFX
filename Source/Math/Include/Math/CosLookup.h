//======================================================================================
//! @file         CosLookup.h
//! @brief        Declaration and implementation of CosLookup class.
//!               Provides an interface to cosine lookup tables that can
//!               be called like a regular cos function
//!			
//!				  Declares an instance of this class called FastCos
//!
//!				  Idea for interpolation code from "Tricks of the 3d game programming gurus"
//!               by Andre Lamothe
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

#ifndef MATH_COSLOOKUP_H
#define MATH_COSLOOKUP_H


#include "Math/Math.h"


namespace Math
{
	
	//! @class	CosLookup
	//! @brief	Cos lookup table class
	//!
	//!			Holds and initializes a lookup table for the cos function.
	//!			This class overrides operator(), so you can call it
	//!			like a function
	class CosLookup
	{
		public:
			
			//Constructor
			inline CosLookup ( ) throw();

			//! Access to lookup table without interpolation
			Scalar Table (UInt index) const throw()  { return m_lookupTable[ index ]; }

			//Operator overloads
			inline Scalar operator() ( Scalar theta ) const throw();

		private:

			//Private members
			Scalar m_lookupTable[361]; //store cosine for 0 to 360 inclusive

	};
	//end class CosLookup


	extern CosLookup FastCos;


	//=========================================================================
	//! @function    CosLookup::Constructor
	//! @brief		 Initialize the consine lookup table
	//=========================================================================
	CosLookup::CosLookup ( )
	{
		for( UInt i=0; i<361; ++i )
		{
			m_lookupTable[i] = Cos(static_cast<Scalar>(i));
		}
	}
	//end CosLookup::Constructor




	//=========================================================================
	//! @function    CosLookup::operator()
	//! @brief		
	//!		Return the consine for the passed Scalar
	//!		using an interpolated table lookup.
	//!
	//!		Value of theta is in degrees
	//!
	//!		Faster, but less accurate than the C library cos function
	//!		Slower, but more accurate than a direct table lookup		
	//!
	//=========================================================================
	Scalar CosLookup::operator() ( Scalar theta ) const
	{
		//Make sure theta is in the range 0-360 inclusive
		fmodf ( theta, 360 );

		//Make sure theta is positive
		if ( theta < 0 )
		{
			theta += 360.0f;
		}

		//Convert theta to an integer for the table lookup
		//note that if this method turns out to be a bottleneck, we could perhaps look into using the
		//fast float to int conversion mentioned in Game programming gems...
		UInt thetaAsInteger = static_cast<Int> ( theta );
		//Get the fractional part of theta to get a more accurate result
		Scalar thetaFractionalPart = theta - thetaAsInteger; 

		return ( m_lookupTable[thetaAsInteger] +  
					thetaFractionalPart * (m_lookupTable[thetaAsInteger+1] - m_lookupTable[thetaAsInteger]) );
	}
	//end CosLookup::operator()


}; 
//end namespace Math



#endif
//#ifndef MATH_COSLOOKUP_H
