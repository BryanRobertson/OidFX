//======================================================================================
//! @file         Matrix1x2.h
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

#include <iostream>
#include "Math/Matrix1x2.h"


using namespace Math;


#ifdef MATH_IOSTREAM_SUPPORT
	//=========================================================================
	//! @function    operator << ( ostream, const Matrix1x2& )
	//! @brief       Formatted output of a Matrix1x2 to an ostream
	//!              
	//! @param       os	 [in] 
	//! @param       rhs [in] 
	//!              
	//! @return      
	//! @throw       
	//=========================================================================
	std::ostream& operator << ( std::ostream& os, const Matrix1x2& rhs ) 
	{
		os << "|" << rhs(0) << " " << rhs(1) << "|";
		return os;
	}
	//end operator <<
#endif
//#ifdef MATH_IOSTREAM_SUPPORT