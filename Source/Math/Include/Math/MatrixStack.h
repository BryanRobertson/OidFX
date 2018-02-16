//======================================================================================
//! @file         MatrixStack.h
//! @brief        Matrix stack. Class that stores a stack of 4x4 matrices, allowing
//!               transforms to be pushed and popped to and from the stack
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 04 June 2005
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

#ifndef MATH_MATRIXSTACK_H
#define MATH_MATRIXSTACK_H


#include <stack>
#include "Math/Matrix4x4.h"


//namespace Math
namespace Math
{

	//!@class	MatrixStack
	//!@brief	Class that stores a stack of 4x4 matrices, allowing
	//!         transforms to be pushed and popped to and from the stack
	class MatrixStack
	{
		public:

			inline MatrixStack();

			inline void Push( const Matrix4x4& mat );
			inline void Push();
			inline void Pop();

			inline Matrix4x4& Top();

		private:

			std::stack<Matrix4x4> m_stack;
	};
	//End class MatrixStack



    //=========================================================================
    //! @function    MatrixStack::MatrixStack
    //! @brief       Construct a matrix stack
    //!              
    //!              Adds an identity matrix as the top of the stack
    //=========================================================================
	MatrixStack::MatrixStack( )
	{
		m_stack.push( Matrix4x4() );
		Top().Identity();
	}
	//End MatrixStack::MatrixStack



    //=========================================================================
    //! @function    MatrixStack::Push
    //! @brief       Pushes the contents of the current matrix onto the stack
    //!              
	//!				 After this call completes, the top of the stack will be a
	//!				 matrix equal to that matrix that was previously the top of the stack 
    //!              
    //=========================================================================
	void MatrixStack::Push( )
	{
		m_stack.push( m_stack.top() );
	}
	//End MatrixStack::Push


	//=========================================================================
    //! @function    MatrixStack::Push
    //! @brief       Pushes a matrix onto the stack
    //!              
	//!	@param		 mat [in] Matrix to push onto the stack			 
    //!              
    //=========================================================================
	void MatrixStack::Push( const Matrix4x4& mat )
	{
		m_stack.push( mat );
	}
	//End MatrixStack::Push



    //=========================================================================
    //! @function    MatrixStack::Pop
    //! @brief       Pops the top off the matrix stack
    //!              
    //!              Care must be taken not to pop the last item off the stack
	//!				 as subsequent calls to Top will be undefined
    //=========================================================================
	void MatrixStack::Pop()
	{
		debug_assert ( m_stack.size() > 1, "Tried to pop the last element of a matrix stack, this is not allowed!" );

		m_stack.pop();
	}
	//End MatrixStack::Pop


    //=========================================================================
    //! @function    MatrixStack::Top
    //! @brief       Returns a reference to the item at the top of the stack
    //!              
    //!              
    //=========================================================================
	Matrix4x4& MatrixStack::Top()
	{
		debug_assert ( !m_stack.empty(), "Tried to get the top of an empty matrix stack!" );

		return m_stack.top();
	}
	//End MatrixStack::Top


};
//end namespace Math



#endif
//#ifndef MATH_MATRIXSTACK_H