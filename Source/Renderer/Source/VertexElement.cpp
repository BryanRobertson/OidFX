//======================================================================================
//! @file         VertexElement.cpp
//! @brief        Class describing an element in a VertexDeclaration
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 29 June 2005
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


#include "Core/Core.h"
#include "Renderer/VertexElement.h"



using namespace Renderer;



//=========================================================================
//! @function    VertexElement::operator <
//! @brief       Used when sorting render states.
//!				 Simply compares each element
//!              
//! @param       rhs [in] VertexElement to compare against
//!              
//! @return      true if *this is less than rhs, false otherwise
//=========================================================================
bool VertexElement::operator < ( const VertexElement& element ) const
{
	if ( StreamIndex() < element.StreamIndex() )
	{
		return true;
	}
	
	if ( Offset() < element.Offset() )
	{
		return true;
	}

	if ( Type() < element.Type() )
	{
		return true;
	}

	if ( Usage() < element.Usage() )
	{	
		return true;
	}

	if ( UsageIndex() < element.UsageIndex() )
	{
		return true;
	}

	if ( Method() < element.Method() )
	{
		return true;
	}

	return false;
}
//End VertexElement::operator <

