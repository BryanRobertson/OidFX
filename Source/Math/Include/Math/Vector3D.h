//======================================================================================
//! @file         Vector3D.h
//! @brief        3D Vector class
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


#ifndef MATH_VECTOR3D_H
#define MATH_VECTOR3D_H

#include "Math/Math.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace Math { class Quaternion;		}


//namespace Math
namespace Math
{

	//!@class	Vector3D
	//!@brief	3D vector class
	//!
	//!			Class representing a 3D vector in 4D homogenous coordinates.
	class Vector3D
	{
		public:

			//Constructors
			explicit inline Vector3D ( Scalar x = 0.0f, Scalar y = 0.0f, Scalar z = 0.0f, Scalar w = 1.0f ) throw();
			inline Vector3D ( const Vector3D& begin, const Vector3D& end ) throw();

			//Dot and Cross product
			inline static void   CrossProduct ( const Vector3D& v1, const Vector3D& v2, Vector3D& result ) throw();
			inline static Scalar DotProduct ( const Vector3D& v1, const Vector3D& v2 ) throw();

			//Invert/Length/Normalise
			inline void	  Invert ( ) throw();					
			inline Scalar Length ( ) const throw();			 
			inline Scalar LengthSquared ( ) const throw();	
			inline Vector3D& Normalise ( ) throw();

			//Compute the cos of the angle between two vectors
			inline static Scalar CosTheta ( const Vector3D& vec1, const Vector3D& vec2 ) throw();
			inline static Scalar AngleBetween ( const Vector3D& vec1, const Vector3D& vec2 ) throw();

			//Accessors
			inline Scalar X ( ) const throw(); 
			inline Scalar Y ( ) const throw();
			inline Scalar Z ( ) const throw(); 
			inline Scalar W ( ) const throw(); 
			
			//Mutators
			inline void Set ( Scalar x, Scalar y, Scalar z , Scalar w = 1.0f ) throw();
			inline void Zero ( ) throw();
			inline void X ( Scalar x )  throw(); 
			inline void Y ( Scalar y )  throw(); 
			inline void Z ( Scalar z )  throw(); 
			inline void W ( Scalar w )  throw(); 

			//Operator overloads
			inline Vector3D& operator += ( const Vector3D& rhs )  throw();
			inline Vector3D& operator -= ( const Vector3D& rhs ) throw();			
			inline Vector3D& operator *= ( Scalar rhs ) throw();
			inline Vector3D& operator /= ( Scalar rhs ) throw();
			inline Vector3D  operator - ( ) const throw();

			Vector3D& operator *= ( const Quaternion& rhs ) throw();
			
		
			#ifdef MATH_IOSTREAM_SUPPORT
				inline friend std::ostream& operator << ( std::ostream& outStream, const Vector3D& vec );
			#endif

			//=========================================================================
			// Constants for the three axis vectors
			//=========================================================================
			static const Vector3D XAxis;
			static const Vector3D YAxis;
			static const Vector3D ZAxis;

		private:

			//Vector members
			Scalar m_x, m_y, m_z, m_w;

	};

	
    //=========================================================================
    // Typedefs
    //=========================================================================
	typedef Vector3D Point3D;

    //=========================================================================
    // Function prototypes for non-member functions
    //=========================================================================
	inline bool		 operator == ( const Vector3D& lhs, const Vector3D& rhs ) throw();
	inline bool		 operator != ( const Vector3D& lhs, const Vector3D& rhs ) throw();
	inline bool		 operator <  ( const Vector3D& lhs, const Vector3D& rhs ) throw();
	inline bool		 operator >  ( const Vector3D& lhs, const Vector3D& rhs ) throw();

	inline Vector3D  operator +  ( const Vector3D& lhs, const Vector3D& rhs ) throw();
	inline Vector3D  operator -  ( const Vector3D& lhs, const Vector3D& rhs ) throw();
	inline Vector3D  operator *  ( const Vector3D& lhs, Scalar rhs ) throw();
	inline Vector3D	 operator /	 ( const Vector3D& lhs, Scalar rhs ) throw();

	Vector3D operator * ( const Vector3D& lhs, const Quaternion& rhs ) throw();



	//=========================================================================
	//! @function    Vector3D::Vector3D
	//! @brief       Vector3D Constructor
	//!              
	//! @param       x [in]
	//! @param       y [in]
	//! @param       z [in]
	//! @param       w [in]
	//!              
	//=========================================================================
	Vector3D::Vector3D ( Scalar x, Scalar y, Scalar z, Scalar w )
	: m_x (x), m_y (y), m_z (z), m_w (w)
	{	
	}
	//end Vector3D::Constructor



    //=========================================================================
    //! @function    Vector3D::Vector3D
    //! @brief       Construct a vector between points begin, and end
    //!              
    //! @param       begin  [in] Starting point
    //! @param       end	[in] Ending point
    //!             
    //=========================================================================
	Vector3D::Vector3D ( const Vector3D& begin, const Vector3D& end )
	{
		Set ( end.X(), end.Y(), end.Z(), 1.0f );
		(*this) -= begin;
	}
	//end Vector3D::Constructor ( begin, end )


    //=========================================================================
    //! @function    Vector3D::CrossProduct
    //! @brief       Compute the cross product of two vectors
    //!              
    //! @param       v1		[in]	First vector
    //! @param       v2		[in]	Second vector
    //! @param       result [out]	Result of the calculation
    //!              
    //=========================================================================
	void Vector3D::CrossProduct ( const Vector3D& v1, const Vector3D& v2, Vector3D& result )
	{
        result.Set ( (v1.Y() * v2.Z()) - (v1.Z() * v2.Y()),
					 (v1.Z() * v2.X()) - (v1.X() * v2.Z()),
					 (v1.X() * v2.Y()) - (v1.Y() * v2.X()) );
	}
	//end Vector3D::CrossProduct



    //=========================================================================
    //! @function    Vector3D::DotProduct
    //! @brief       Compute the dot product of the two vectors
    //!              
    //! @param       v1 [in]	First vector
    //! @param       v2 [in]	Second vector
    //!              
    //! @return      v1 . v2
    //=========================================================================
	Scalar Vector3D::DotProduct ( const Vector3D& v1, const Vector3D& v2 )
	{
		return (v1.X() * v2.X()) + (v1.Y () * v2.Y()) + (v1.Z() * v2.Z());
	}
	//end Vector3D::DotProduct



    //=========================================================================
    //! @function    Vector3D::Invert
    //! @brief       Make this vector point in the opposite direction
    //!              
    //!              
    //=========================================================================
	void Vector3D::Invert ()
	{
		X(-X()); 
		Y(-Y()); 
		Z(-Z());								
	}
	//End Vector3D::Invert



    //=========================================================================
    //! @function    Vector3D::Length
    //! @brief       Return the length of the vector
    //!              
    //!              
    //! @return      The length of the vector
    //=========================================================================
	Scalar Vector3D::Length ( ) const
	{ 
		return Sqrt( X()*X() + Y()*Y() + Z()*Z() );
	}
	//End Vector3D::Length



    //=========================================================================
    //! @function    Vector3D::LengthSquared
    //! @brief       Return the length of the vector squared
    //!              
    //!				 This method is intended to make it possible to tell
	//!				 if the magnitude of one vector is greater than another,
	//!				 without having to perform a costly square root operation.
	//!
    //! @return      The length of the vector
    //=========================================================================
	Scalar Vector3D::LengthSquared ( ) const throw()	
	{ 
		return ( X()*X() + Y()*Y() + Z()*Z() );
	}
	//End Vector3D::LengthSquared



    //=========================================================================
    //! @function    Vector3D::Normalise
    //! @brief       Normalise the vector
    //!              
	//!				 Normalising the vector preserves its direction, but
	//!				 gives it a length of one.
    //!              
	//!
	//! @return		 A reference to *this
    //=========================================================================
	Vector3D& Vector3D::Normalise ( )
	{
		Scalar length = Length();

		if ( length == 0.0f )
		{
			//If length is zero then exit to avoid a divide by zero
			return *this;
		}

		X ( X() / length );
		Y ( Y() / length );
		Z ( Z() / length );

		return *this;
	}
	//end Vector3D::Normalise



    //=========================================================================
    //! @function    Vector3D::CosTheta
    //! @brief       Return the cos of the angle between the two vectors
    //!              
    //! @param       vec1 [in] 
    //! @param       vec2 [in] 
    //!              
    //=========================================================================
	Scalar Vector3D::CosTheta ( const Vector3D& vec1, const Vector3D& vec2 )
	{
		if ( (vec1.Length ( ) == 0.0f) || (vec2.Length ( ) == 0.0f) )
		{
			//Return angle of 0 if either vector is 0 length
			//(remember that cos¯¹ ( 1.0 ) == 0
			return 1.0f;
		}

		return ( (vec1.X() * vec2.X( ) + vec1.Y() * vec2.Y() + vec1.Z() * vec2.Z() )
			      /  ( vec1.Length( ) * vec2.Length ( ) ) );
	}
	//end Vector3D::CosTheta



	//=========================================================================
    //! @function    Math::Vector3D::AngleBetween
    //! @brief       Return the angle between two vectors, in radians
    //!              
    //! @param       vec1 [in] 
    //! @param       vec2 [in]
    //!              
    //! @return      The angle between vec1 and vec2, in radians
    //=========================================================================
	Scalar Vector3D::AngleBetween ( const Vector3D& vec1, const Vector3D& vec2 )
	{
		return ACos( CosTheta(vec1,vec2) );
	}
	//end Vector2D::AngleBetween



    //=========================================================================
    //! @function    Vector3D::X
    //! @brief       Return the vector's x component
    //!              
    //! @return      The value of the vector's x component
    //=========================================================================
	Scalar Vector3D::X() const
	{
		return m_x;
	}
	//End Vector3D::X



	//=========================================================================
    //! @function    Vector3D::Y
    //! @brief       Return the vector's y component
    //!              
    //! @return      The value of the vector's y component
    //=========================================================================
	Scalar Vector3D::Y() const
	{
		return m_y;
	}
	//End Vector3D::Y



	//=========================================================================
    //! @function    Vector3D::Z
    //! @brief       Return the vector's z component
    //!              
    //! @return      The value of the vector's z component
    //=========================================================================
	Scalar Vector3D::Z() const
	{
		return m_z;
	}
	//End Vector3D::Z



    //=========================================================================
    //! @function    Vector3D::W
    //! @brief       Return the vector's w component
    //!              
    //! @return      The value of the vector's w component
    //=========================================================================
	Scalar Vector3D::W() const
	{
		return m_w;
	}
	//End Vector3D::W



    //=========================================================================
    //! @function    Vector3D::Set
    //! @brief       Set the contents of the vector
    //!              
    //! @param       x [in] Value for the x component
    //! @param       y [in] Value for the y component
    //! @param       z [in] Value for the z component
    //! @param       w [in] (optional) Value for the w component
    //!              
    //=========================================================================
	void Vector3D::Set ( Scalar x, Scalar y, Scalar z, Scalar w )
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}
	//End Vector3D::Set


    //=========================================================================
    //! @function	Vector3D::Zero
    //! @brief      Set the vector contents to zero 
    //!              
    //=========================================================================
	void Vector3D::Zero ()
	{
		m_x = m_y = m_z = 0.0f;
		m_w = 1.0f;
	}
	//End Vector3D::Zero



    //=========================================================================
    //! @function    Vector3D::X
    //! @brief       Set the x component of the vector
    //!              
    //! @param       x [in] New value for the x component
    //!              
    //=========================================================================
	void Vector3D::X( Scalar x )
	{
		m_x = x;
	}
	//End Vector3D::X



    //=========================================================================
    //! @function    Vector3D::Y
    //! @brief       Set the y component of the vector
    //!              
    //! @param       y [in] New value for the y component
	//!
    //=========================================================================
	void Vector3D::Y( Scalar y )
	{
		m_y = y;
	}
	//End Vector3D::Y



    //=========================================================================
    //! @function    Vector3D::Z
    //! @brief       Set the z component of the vector
    //!              
    //! @param       z [in] New value for the z component
    //!              
    //=========================================================================
	void Vector3D::Z( Scalar z )
	{
		m_z = z;
	}
	//End Vector3D::Z



    //=========================================================================
    //! @function    Vector3D::W
    //! @brief       Set the w component of the vector
    //!              
    //! @param       w  [in] New value for the w component
    //!              
    //=========================================================================
	void Vector3D::W( Scalar w )
	{
		m_w = w;
	}
	//End Vector3D::W




    //=========================================================================
    //! @function    Vector3D::operator +=
    //! @brief       Add a vector to this one
    //!              
    //! @param       rhs [in] Vector to add to this one
    //!              
    //! @return      (*this)
    //=========================================================================
	Vector3D& Vector3D::operator+= ( const Vector3D& rhs )
	{
		X ( X () + rhs.X () );
		Y ( Y () + rhs.Y () );
		Z ( Z () + rhs.Z () );

		return (*this);
	}
	//end Vector3D::operator +=



	//=========================================================================
	//! @function    Vector3D::operator -=
	//! @brief       Subtract a vector from this one
	//!              
	//! @param       rhs [in] Vector to subtract from this one
	//!              
	//! @return      (*this)
	//=========================================================================
	Vector3D& Vector3D::operator-= ( const Vector3D& rhs )
	{
		X ( X ( ) - rhs.X ( ) );
		Y ( Y ( ) - rhs.Y ( ) );
		Z ( Z ( ) - rhs.Z ( ) );

		return ( *this );
	}
	//end Vector3D::operator -=

	

	//=========================================================================
	//! @function    Vector3D::operator *= (Scalar)
	//! @brief       
	//!              
	//! @param       rhs [in] Scalar to multiply by this one
	//!              
	//! @return      (*this)
	//=========================================================================
	Vector3D& Vector3D::operator *= ( Scalar rhs )
	{
		X ( X( ) * rhs );
		Y ( Y( ) * rhs );
		Z ( Z( ) * rhs );

		return ( *this );
	}
	//end Vector3D::operator *=



    //=========================================================================
    //! @function    Vector3D::operator /=
    //! @brief       Divide this vector by a scalar
    //!              
    //! @param       rhs [in] Scalar value to divide this vector by
    //!              
    //! @return      (*this)
    //=========================================================================
	Vector3D& Vector3D::operator /= ( Scalar rhs )
	{
		X ( X( ) / rhs );
		Y ( Y( ) / rhs );
		Z ( Z( ) / rhs );

		return ( *this );
	}
	//end Vector3D::operator /=

	

    //=========================================================================
    //! @function    Vector3D::operator -
    //! @brief       Return a vector equal to the inverse of this vector
    //!              
    //!              
    //! @return      A vector equal to the inverse of this vector
    //=========================================================================
	Vector3D Vector3D::operator - ( ) const
	{
		return Vector3D ( -X(), -Y(), -Z() );
	}
	//end Vector3D::operator -



    //=========================================================================
    // Non-member functions
    //=========================================================================



    //=========================================================================
    //! @function    operator == ( const Vector3D&, const Vector3D& )
    //! @brief       Checks two vectors for equality
	//!
	//!				 Checks the difference between the two vectors components
	//!				 against an epsilon value, to protect against floating point inaccuracy
    //!              
    //! @param       lhs [in] First vector
    //! @param       rhs [in] Second vector
    //!              
    //! @return      true if the vectors are equal
	//!				 false otherwise
    //=========================================================================
	bool operator == ( const Vector3D& lhs, const Vector3D& rhs )
	{
		if ( !Equal(lhs.X(), rhs.X()) )
		{
			return false;
		}

		if (!Equal(lhs.Y(), rhs.Y()) )
		{
			return false;
		}

		if (!Equal(lhs.Z(), rhs.Z()) )
		{
			return false;
		}

		return true;
	}
	//end operator == ( const Vector3D&, const Vector3D& )



	//=========================================================================
    //! @function    operator != ( const Vector3D&, const Vector3D& )
    //! @brief       Checks two vectors for inequality
	//!
	//!				 
    //! @param       lhs [in] First vector
    //! @param       rhs [in] Second vector
    //!              
    //! @return      true if the vectors are equal
	//!				 false otherwise
    //=========================================================================
	bool operator != ( const Vector3D& lhs, const Vector3D& rhs )
	{
		return !( lhs == rhs );
	}
	//end operator != ( const Vector3D&, const Vector3D& )



    //=========================================================================
    //! @function    operator < ( const Vector3D&, const Vector3D& )
    //! @brief       return true if all the components of lhs, are 
	//!				 less than all the components of rhs
    //!              
    //! @param       lhs [in]
    //! @param       rhs [in]
    //!              
    //! @return      true if all components of lhs are less than all components of rhs
    //=========================================================================
	bool operator < ( const Vector3D& lhs, const Vector3D& rhs )
	{

		if (   (lhs.X() < rhs.X())
			&& (lhs.Y() < rhs.Y())
			&& (lhs.Z() < rhs.Z()) )
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	//End operator < ( const Vector3D&, const Vector3D& )


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
	bool operator > ( const Vector3D& lhs, const Vector3D& rhs )
	{
		if (   (lhs.X() > rhs.X())
			&& (lhs.Y() > rhs.Y())
			&& (lhs.Z() > rhs.Z()) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//End operator > ( const Vector3D&, const Vector3D& )



	//=========================================================================
	//! @function    operator + ( const Vector3D&, const Vector3D& )
	//! @brief       Return the result of adding one vector to another
	//!              
	//! @param		 lhs [in] First vector
	//! @param       rhs [in] Second vector
	//!              
	//! @return      A vector equal to lhs + rhs
	//! @throw       
	//=========================================================================
	Vector3D operator + ( const Vector3D& lhs, const Vector3D& rhs )
	{
		return Vector3D (lhs) += rhs;
	}
	//end operator + ( const Vector3D&, const Vector3D& )



	//=========================================================================
	//! @function    operator - ( const Vector3D&, const Vector3D& )
	//! @brief       Return the result of subtracting one vector from another
	//!              
	//! @param		 lhs [in] First vector
	//! @param       rhs [in] Second vector
	//!              
	//! @return      A vector equal to lhs - rhs
	//! @throw       
	//=========================================================================
	Vector3D operator - ( const Vector3D& lhs, const Vector3D& rhs )
	{
		return Vector3D (lhs) -= rhs;
	}
	//end operator - ( const Vector3D&, const Vector3D& )




    //=========================================================================
    //! @function    operator * ( const Vector3D&, Scalar )
    //! @brief       Return the result of multiplying a vector by a scalar
    //!             
	//! @param		 lhs [in] Vector to be multiplied
    //! @param       rhs [in] Scalar multiplier
    //!              
    //! @return      A vector equal to lhs * rhs
    //=========================================================================
	Vector3D operator * ( const Vector3D& lhs, Scalar rhs )
	{
		return Vector3D(lhs) *= rhs;
	}
	//end operator* ( const Vector3D&, Scalar )



    //=========================================================================
    //! @function    operator / ( const Vector3D&, Scalar )
    //! @brief       Return the result of dividing a vector by a scalar
    //!             
	//! @param		 lhs [in] Vector to be divided
    //! @param       rhs [in] Scalar divisor
    //!              
    //! @return      A vector equal to lhs / rhs
    //=========================================================================
	Vector3D operator / ( const Vector3D& lhs, Scalar rhs )
	{
		return Vector3D(lhs) /= rhs;
	}
	//end operator* ( const Vector3D&, Scalar )



	#ifdef MATH_IOSTREAM_SUPPORT

		//=========================================================================
		//! @function    operator << ( std::ostream&, const Vector3D&  )
		//! @brief       Write formatted output, about a Vector3D to an ostream
		//!              
		//! @param       outStream [in] output stream
		//! @param       vec	   [in] vector to be written
		//!              
		//! @return      outStream
		//=========================================================================
		std::ostream& operator << ( std::ostream& outStream, const Vector3D& vec )
		{
			return outStream << "( " << vec.X() << ", " << vec.Y() << ", " << vec.Z() << ", " << vec.W() << " )";
		}
		//end operator << ( std::ostream&, const Vector3D&  )

	#endif
	//#ifndef MATH_IOSTREAM_SUPPORT

}
//end namespace Math


#endif 
//#ifndef MATH_VECTOR3D_H
