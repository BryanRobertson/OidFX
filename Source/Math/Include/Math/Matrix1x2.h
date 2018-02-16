//======================================================================================
//! @file         Matrix1x2.h
//! @brief        1x2 Matrix class
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


#ifndef MATH_MATRIX1X2_H
#define MATH_MATRIX1X2_H

#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Math/Math.h"


//namespace Math
namespace Math
{


    //=========================================================================
    // Forward declarations
    //=========================================================================


	//!@class	Matrix1x2
	//!@brief	1x2 Matrix class
	class Matrix1x2
	{
		public:
			
			//Constructors
			Matrix1x2 ( ) throw() { /*default constructor has no implementation*/ }
			Matrix1x2 ( Scalar m00, Scalar m01 ) throw () : m_00 (m00), m_01 (m01) {  }

			inline void Set (  Scalar m00, Scalar m01 ) throw () { m_00 = m00; m_01 = m01; }

			//operator overloads

			inline Scalar operator () ( UInt col ) const throw ()   { return m[col]; }
			inline Scalar& operator () ( UInt col ) throw ()		{ return m[col]; }

			//friend functions
			#ifdef MATH_IOSTREAM_SUPPORT
				friend std::ostream& operator << ( std::ostream& os, const Matrix1x2& rhs ); 
			#endif

			static const UInt ms_numRows = 1;
			static const UInt ms_numCols = 2;

		private:

			union 
			{
				Scalar m[2];

				struct
				{
					Scalar m_00, m_01;
				};
			};

	};
	//end class Matrix1x2



};//end namespace Math3D

#endif //#ifndef MATH_MATRIX1x2_H