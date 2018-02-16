//======================================================================================
//! @file         Vector2D.h
//! @brief        2D Vector class
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


#ifndef MATH_VECTOR2D_H
#define MATH_VECTOR2D_H

#include "Math/Math.h"

#ifdef MATH_IOSTREAM_SUPPORT
	#include <iostream>
#endif


namespace Math
{

	//! @class Vector2D
	//! @brief 2D Vector class
	class Vector2D
	{
		public:

			//Constructors
			explicit inline Vector2D ( Scalar x = 0.0f, Scalar y = 0.0f ) throw();
			inline Vector2D ( const Vector2D& begin, const Vector2D& end ) throw();

			//Invert/Length/Normalise
			inline void	  Invert ( ) throw(); 			
			inline Scalar Length ( ) const throw();			
			inline Scalar LengthSquared ( ) const throw(); 	
			inline Vector2D& Normalise ( )	throw();

			//Compute the Cos of the angle between two vectors
			inline static Scalar CosTheta ( const Vector2D& vec1, const Vector2D& vec2 ) throw();
			//Get the angle between two vectors
			inline static Scalar AngleBetween ( const Vector2D& vec1, const Vector2D& vec2 ) throw();
			//Dot product
			inline static Scalar DotProduct ( const Vector2D& v1, const Vector2D& v2 ) throw();

			//Dot product for instances of Vector2D
			inline Scalar Dot ( const Vector2D& vec ) const;

			//Accessors
			inline Scalar X ( ) const throw() { return m_x; }
			inline Scalar Y ( ) const throw() { return m_y; }
			
			//Mutators
			inline void Set  ( Scalar x, Scalar y ) throw()	{ X(x); Y(y);		}
			inline void Zero ( ) throw() 						{ X(0.0f); Y(0.0f);	} 
			inline void X ( Scalar x )  throw()				{ m_x = x;			}
			inline void Y ( Scalar y )  throw()				{ m_y = y;			}

			//Operator overloads
			inline Vector2D& operator += ( const Vector2D& rhs )  throw();
			inline Vector2D& operator -= ( const Vector2D& rhs )  throw();			
			inline Vector2D& operator *= ( Scalar rhs ) throw();
			inline Vector2D& operator /= ( Scalar rhs ) throw();
			inline Vector2D  operator - ( ) const throw();


			#ifdef MATH_IOSTREAM_SUPPORT
				inline friend std::ostream& operator << ( std::ostream& outStream, const Vector2D& vec );
			#endif

		private:

			//Vector members
			Scalar m_x, m_y;

	};
	//end class Vector2D


    //=========================================================================
    // Typedefs
   //=========================================================================
	typedef Vector2D Point2D;


    //=========================================================================
    // Prototypes for non-member functions
    //=========================================================================
	inline bool		 operator == ( const Vector2D& lhs, const Vector2D& rhs ) throw();
	inline bool		 operator != ( const Vector2D& lhs, const Vector2D& rhs ) throw();
	inline bool		 operator <  ( const Vector2D& lhs, const Vector2D& rhs ) throw();
	inline bool		 operator >  ( const Vector2D& lhs, const Vector2D& rhs ) throw();


	inline Vector2D  operator +  ( const Vector2D& lhs, const Vector2D& rhs ) throw();
	inline Vector2D  operator -  ( const Vector2D& lhs, const Vector2D& rhs ) throw();
	inline Vector2D  operator *  ( const Vector2D& lhs, Scalar rhs ) throw();
	inline Vector2D  operator /  ( const Vector2D& lhs, Scalar rhs ) throw();


	//=========================================================================
	//! @function    Vector2D::Constructor
	//! @brief       Initialize the vector to the values provided
	//!              
	//! @param		 x	[in]	X value to set
	//! @param		 y	[in]	Y value to set
	//=========================================================================
	Vector2D::Vector2D ( Scalar x, Scalar y )
	: m_x(x), m_y(y)
	{
	}
	//end Vector2D::Constructor



	//=========================================================================
	//! @function    Vector2D::Constructor
	//! @brief       Construct a vector between two points
	//!              
	//! @param		 begin	[in]	Start point of the vector
	//! @param		 end	[in]	End point of the vector
	//=========================================================================
	Vector2D::Vector2D ( const Vector2D& begin, const Vector2D& end )
	{
		Set (end.X(), end.Y());
		(*this) -= begin;
	}
	//end Vector2D::Constructor


    //=========================================================================
    //! @function    Vector2D::Invert
    //! @brief       Make this vector point in the opposite direction
    //!              
    //!           
    //=========================================================================
	void Vector2D::Invert()
	{
		X(-X());
		Y(-Y());
	}
	//End Vector2D::Invert



	//=========================================================================
	//! @function    Vector2D::Normalise
	//! @brief       Normalise the vector
	//!
	//!				 After this call, the magnitude of the vector will be 1
	//!              
	//! @return		 A reference to *this
	//=========================================================================
	Vector2D& Vector2D::Normalise ( )
	{
		Scalar length = Length();
		
		if ( length == 0.0f )
		{
			return *this;
		}

		X( X() / length );
		Y( Y() / length );

		return *this;
	}
	//end Vector2D::Normalise



    //=========================================================================
    //! @function    Vector2D::LengthSquared
    //! @brief       Return the length of the vector squared
    //!              
    //!              Allows the lengths of vectors to be compared, where
	//!				 the actual length is not required. Thus avoiding a square root 
    //!
	//! @return		 The length of the vector squared
    //=========================================================================
	Scalar Vector2D::LengthSquared() const
	{
		return (X()*X()) + (Y()*Y());
	}
	//End Vector2D::LengthSquared



    //=========================================================================
    //! @function    Vector2D::Length
    //! @brief       Return the length of the vector
    //!              
    //!              
    //! @return      The length of the vector
    //=========================================================================
	Scalar Vector2D::Length() const
	{
		return Sqrt(LengthSquared());
	}
	//End Vector2D::Length



	//=========================================================================
	//! @function    Vector2D::DotProduct
	//! @return		 The dot product of v1 and v2
	//=========================================================================
	Scalar Vector2D::DotProduct ( const Vector2D& v1, const Vector2D& v2 )
	{
		return ( v1.X() * v2.X() + v1.Y() * v2.Y() );
	}
	//end Vector2D::DotProduct



	//=========================================================================
	//! @function    Vector2D::CosTheta
	//! @return		 The Cos of the angle between two vectors
	//!              
	//! @param		 vec1	[in]
	//! @param		 vec2	[in]
	//=========================================================================
	Scalar Vector2D::CosTheta ( const Vector2D &vec1, const Vector2D& vec2 )
	{
		if ( (vec1.Length() == 0.0f) || (vec2.Length() == 0.0f) )
		{
			 
			//If the length of either vector is zero, then so must the angle
			//cos¯¹ ( 1.0 ) = 0
			//therefore cos ( 0 ) = 1.0
			return 1.0f;
		}

		//cos(theta) = x1*x2 + y1*y2
		//			  ---------------
		//				|v1| * |v2|

		return ( (vec1.X() * vec2.X() + vec1.Y() * vec2.Y() )
					/ (vec1.Length() * vec2.Length()) ); 
	}
	//end Vector2D::CosTheta



    //=========================================================================
    //! @function    Math::Vector2D::AngleBetween
    //! @brief       Return the angle between two vectors, in radians
    //!              
    //! @param       vec1 [in] 
    //! @param       vec2 [in]
    //!              
    //! @return      The angle between vec1 and vec2, in radians
    //=========================================================================
	Scalar Vector2D::AngleBetween ( const Vector2D& vec1, const Vector2D& vec2 )
	{
		return ACos( CosTheta(vec1,vec2) );
	}
	//end Vector2D::AngleBetween



    //=========================================================================
    //! @function    Vector2D::Dot
    //! @brief       Get the dot product of *this, and another vector
    //!              
    //! @param       vec [in] Vector to dot product *this with 
    //!              
    //! @return      Dot product of *this and vec
    //=========================================================================
	Scalar Vector2D::Dot ( const Vector2D& vec ) const
	{
		return ( X() * vec.X() + Y() * vec.Y() );
	}
	//end Vector2D::Dot
	
	
	//Operator overloads
	

	//=========================================================================
	//! @function    Vector2D::operator +=
	//=========================================================================
	Vector2D& Vector2D::operator += ( const Vector2D& rhs )
	{
		X (X() + rhs.X());
		Y (Y() + rhs.Y());

		return ( *this );
	}
	//end Vector2D::operator +=


	//=========================================================================
	//! @function    Vector2D::operator -=
	//=========================================================================
	Vector2D& Vector2D::operator -= ( const Vector2D& rhs )
	{
		X (X() - rhs.X());
		Y (Y() - rhs.Y());

		return ( *this );
	}
	//end Vector2D::operator -=


	//=========================================================================
	//! @function    Vector2D::operator *= (Scalar)
	//! @brief       Multiplication by scalar
	//=========================================================================
	Vector2D& Vector2D::operator *= ( Scalar rhs )
	{
		X (X() * rhs);
		Y (Y() * rhs);

		return (*this);
	}
	//end Vector2D::operator *=


	//=========================================================================
	//! @function    Vector2D::operator /=
	//! @brief		 Scalar division
	//=========================================================================
	Vector2D& Vector2D::operator /= ( Scalar rhs )
	{
		X (X() / rhs);
		Y (Y() / rhs);

		return ( *this );
	}
	//end Vector2D::operator /=


	//=========================================================================
	//! @function    Vector2D::operator -
	//! @brief		 Negation operator
	//!
	//! @return		 -V
	//=========================================================================
	Vector2D Vector2D::operator - ( ) const
	{
		return Vector2D (-X(), -Y());
	}
	//Vector2D::operator -



	//=========================================================================
	//! @function    operator == ( const Vector2D&, const Vector2D& )
	//! @brief		 Compare two vectors for equality
	//!
	//!				 Takes the dot product between two vectors.
	//!				 If the result if close enough to 1.0, then the two vectors
	//!				 are considered to be equal.
	//!				 Because the members of the vector are stored in floating point
	//!				 there'd be pretty much no chance of this returning true if we
	//!				 just compared the members for equality
	//=========================================================================
	bool operator == ( const Vector2D& lhs, const Vector2D& rhs )
	{
		//Check whether the dot product between the two vectors is 1.0f
		//rather than comparing the contents of the vectors
		return Equal( 1.0, Vector2D::DotProduct(lhs, rhs));		
	}
	//end Vector2D::operator ==


	//=========================================================================
	//! @function    operator != ( const Vector2D&, const Vector2D& )
	//=========================================================================
	bool operator != ( const Vector2D& lhs, const Vector2D& rhs )
	{
		return !(lhs == rhs);
	}
	//end Vector2D::operator !=


	//=========================================================================
    //! @function    operator < ( const Vector2D&, const Vector2D& )
    //! @brief       return true if all the components of lhs, are 
	//!				 less than all the components of rhs
    //!              
    //! @param       lhs [in]
    //! @param       rhs [in]
    //!              
    //! @return      true if all components of lhs are less than all components of rhs
    //=========================================================================
	bool operator < ( const Vector2D& lhs, const Vector2D& rhs )
	{

		if (   (lhs.X() < rhs.X())
			&& (lhs.Y() < rhs.Y()))
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	//End operator < ( const Vector2D&, const Vector2D& )


    //=========================================================================
    //! @function    operator >
    //! @brief       return true if all the components of lhs, are 
	//!				 greater than all the components of rhs
    //!              
    //! @param       lhs [in]
    //! @param       rhs [in]
    //!              
    //! @return      true if all components of lhs are greater than all components of rhs
    //=========================================================================
	bool operator > ( const Vector2D& lhs, const Vector2D& rhs )
	{
		if (   (lhs.X() > rhs.X())
			&& (lhs.Y() > rhs.Y()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//End operator > ( const Vector2D&, const Vector2D& )

	

	//=========================================================================
	//! @function    operator / ( const Vector2D&, Scalar rhs )
	//! @brief		 Scalar division
	//=========================================================================
	Vector2D operator / ( const Vector2D& lhs, Scalar rhs )
	{
		return (Vector2D(lhs) /= rhs);
	}
	//end Vector2D::operator/

		

	//=========================================================================
	//! @function     operator * ( const Vector2D&, Scalar rhs )
	//=========================================================================
	Vector2D operator * ( const Vector2D& lhs, Scalar rhs )
	{
		return (Vector2D(lhs) *= rhs);
	}
	//end Vector2D::operator *



	//=========================================================================
	//! @function    operator+ (const Vector2D&, const Vector2D&)
	//=========================================================================
	Vector2D operator + ( const Vector2D & lhs, const Vector2D & rhs )
	{
		return Vector2D(lhs) += rhs;
	}
	//end Vector2D::operator+


	//=========================================================================
	//! @function    operator - (const Vector2D&, const Vector2D&)
	//=========================================================================
	Vector2D operator - ( const Vector2D& lhs, const Vector2D& rhs )
	{
		return Vector2D(lhs) -= rhs;
	}
	//end Vector2D::operator -


	#ifdef MATH_IOSTREAM_SUPPORT //some platforms, such as dreamcast, don't really have decent STL support yet
	
		//operator <<
		//Write formatted output from a Vector2D to an output stream
		std::ostream& operator << ( std::ostream& outStream, const Vector2D& vec )
		{
			return outStream << "( " << vec.X() << ", " << vec.Y () << " )";
		}
		//end operator <<
	
	#endif

}; 
//end namespace Math


#endif //#ifndef MATH_VECTOR2D_H