//======================================================================================
//! @file         Quaternion.h
//! @brief        Class representing a quaternion
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


#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H


#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Math/Math.h"


//namespace Math
namespace Math
{

    //=========================================================================
    // Forward declarations
    //=========================================================================
	class Matrix4x4;
	class Matrix3x3;


	//!@class	Quaternion
	//!@brief	Class representing a quaternion
	class Quaternion
	{
		public:

			//Constructors
			inline Quaternion ( ) throw() {};
			inline explicit Quaternion ( Scalar w, Scalar x, Scalar y, Scalar z) throw();
			inline Quaternion ( const Vector3D& v, Scalar theta ) throw();
			inline Quaternion ( Scalar thetaZ, Scalar thetaY, Scalar thetaX ) throw();
			explicit Quaternion ( const Matrix4x4& mat );
			explicit Quaternion ( const Matrix3x3& mat );

			//Triple Product
			static inline Quaternion TripleProduct ( const Quaternion& q1, const Quaternion& q2, const Quaternion& q3 ) throw();
			Quaternion Lerp  ( Scalar t, const Quaternion& q1, const Quaternion& q2 ) throw();
			Quaternion Slerp ( Scalar t, const Quaternion& q1, const Quaternion& q2 ) throw();	

			//Set all the members to zero
			void Zero ( ) throw() { W(0.0f); m_xyzw.Zero ( );  }

			//Conversion methods
			inline void ToVector3DTheta ( Vector3D& vec, Scalar& theta ) const throw();
			
			//Operator overloads
			inline Quaternion&	operator+=( const Quaternion& rhs ) throw();
			inline Quaternion&	operator-=( const Quaternion& rhs ) throw();
			inline Quaternion&	operator*=( const Quaternion& rhs ) throw();
			inline Quaternion&	operator*=( Scalar rhs			  )	throw();
			inline Quaternion	operator- () const throw();

			//Quaternion operations
			inline Quaternion Conjugate	( )	const throw();
			inline Quaternion Inverse		( )	const throw();
			inline Quaternion UnitInverse	( )	const throw();
			inline Scalar	  Norm			( )	const throw();

			inline Quaternion& SetToConjugate	( ) throw();
			inline Quaternion& Normalise		( )	throw();
			inline Quaternion& Invert			( )	throw();
			inline Quaternion& UnitInvert		( )	throw();

			//Accessors
			Scalar W() const throw()				{ return m_xyzw.W(); }
			Scalar X() const throw()				{ return m_xyzw.X(); }
			Scalar Y() const throw()				{ return m_xyzw.Y(); }
			Scalar Z() const throw()				{ return m_xyzw.Z(); }
			const Vector3D& Vector() const throw()    { return m_xyzw; }

			//Mutators
			void W ( Scalar w ) throw()			{ m_xyzw.W ( w ); }
			void X ( Scalar x ) throw()			{ m_xyzw.X ( x ); }
			void Y ( Scalar y ) throw()			{ m_xyzw.Y ( y ); }
			void Z ( Scalar z ) throw()			{ m_xyzw.Z ( z ); }

			//Friend Functions
			#ifdef MATH_IOSTREAM_SUPPORT
				inline friend std::ostream& operator << ( std::ostream& outStream, const Quaternion& vec );
			#endif

		private:

			Vector3D	m_xyzw;

	};
	//end class Quaternion


    //=========================================================================
    // Prototypes for non-member functions
    //=========================================================================
	inline Quaternion operator+ ( const Quaternion& lhs, const Quaternion& rhs ) throw();
	inline Quaternion operator- ( const Quaternion& lhs, const Quaternion& rhs ) throw();
	inline Quaternion operator* ( const Quaternion& lhs, const Quaternion& rhs ) throw();
	inline Quaternion operator* ( const Quaternion& lhs, Scalar rhs            ) throw();

	
	//=========================================================================
	//! @function    Quaternion::Quaternion
	//! @brief       Construct a quaternion from the scalar values w,x,y,z
	//!              
	//! @param       begin [in] Beginning of the line
	//! @param       end   [in] End of the line
	//=========================================================================
	Quaternion::Quaternion  ( Scalar w, Scalar x, Scalar y, Scalar z )
	: m_xyzw(x,y,z,w)
	{
	}
	//end Quaternion::Constructor (w,x,y,z)

 

    //=========================================================================
    //! @function    Quaternion::Quaternion
    //! @brief       Construct a quaternion from an axis, and a rotation around that axis
    //!              
	//!
    //! @param       v		[in] Axis around which to rotate. Must be a unit vector!
    //! @param       theta	[in] Rotation around that axis
    //!              
    //=========================================================================
	Quaternion::Quaternion ( const Vector3D& v, Scalar theta )
	{
		debug_assert ( Equal( v.Length(), 1.0f ), "v must be a unit vector!" );

		const Scalar halfTheta = 0.5f * theta;
		
		//precompute sin (halfTheta)
		//because it will be used more than once
		const Scalar sinHalfTheta = Sin(halfTheta);

		//                           
		//Q = cos(theta/2) + (sin(theta/2) . Vq )

		m_xyzw = Vector3D( (v.X()*sinHalfTheta), 
						   (v.Y()*sinHalfTheta), 
						   (v.Z()*sinHalfTheta), 
						   Cos(halfTheta));

	}
	//end Quaternion (const Vector3D& v, Scalar theta)



    //=========================================================================
    //! @function    Quaternion::Quaternion
    //! @brief       Construct a quaternion from euler angles
    //!              
	//!				 Rotates in z,y,x order
	//!
    //! @param       thetaZ [in] Rotation around z axis
    //! @param       thetaY [in] Rotation around y axis
    //! @param       thetaX [in] Rotation around x axis
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	Quaternion::Quaternion ( Scalar thetaZ, Scalar thetaY, Scalar thetaX )
	{

		//NOTE: This is probably the least efficient way to do this
		//It'd be quite easy to optimise if necessary.

		//Quaternion for rotation around Z axis
		Quaternion qz = Quaternion ( Vector3D::ZAxis, thetaZ );
		//Quaternion for rotation around Y axis
		Quaternion qy = Quaternion ( Vector3D::YAxis, thetaY ); 
		//Quaternion for rotation around X axis
		Quaternion qx = Quaternion ( Vector3D::XAxis, thetaX );

		//Set this quaternion to be qz * qy * qx
		*(this) = TripleProduct ( qz, qy, qx );
	}
	//end Quaternion::Constructor ( Scalar thetaZ, Scalar thetaY, Scalar thetaX )



	//=========================================================================
	//! @function    Quaternion::TripleProduct
	//! @brief       Return the result of q1 * q2 * q3
	//!              
	//! @param       q1 [in]
	//! @param       q2 [in]
	//! @param       q3 [in]
	//!              
	//! @return      A quaternion equal to q1 * q2 * q3
	//=========================================================================
	Quaternion Quaternion::TripleProduct ( const Quaternion& q1, const Quaternion& q2, const Quaternion& q3 )
	{

		Quaternion result(q1); 
		result *= q2;
		result *= q3;

		return ( result );
	}
	//end Quaternion::TripleProduct



	//=========================================================================
	//! @function    Quaternion::ToVector3DTheta
	//! @brief       Convert to a 3D vector (axis of rotation)
	//!				 and a rotation around that axis
	//!              
	//! @param       vec	[out]	Axis of rotation
	//! @param       theta	[out]	Rotation around that axis
	//=========================================================================
	void Quaternion::ToVector3DTheta ( Vector3D& vec, Scalar& theta ) const
	{
		theta = 2 * ACos ( W() );
		
		//precompute sin ( halfTheta )
		//because it will be used more than once
		const Scalar sinHalfTheta = Sin ( theta * 0.5f );
		vec = Vector3D ( (X() / sinHalfTheta), (Y() / sinHalfTheta), (Z() / sinHalfTheta) );
	
	}
	//end Quaternion::ToVector3DTheta



    //=========================================================================
    //! @function    Quaternion::operator +=
    //! @brief       Add a quaternion to *this
    //!              
    //! @param       rhs [in] Quaternion to add
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::operator+= ( const Quaternion& rhs )
	{
		W ( W() + rhs.W() );
		X ( X() + rhs.X() );
		Y ( Y() + rhs.Y() );
		Z ( Z() + rhs.Z() );

		return (*this);
	}
	//end Quaternion::operator +=

	

	//=========================================================================
    //! @function    Quaternion::operator -=
    //! @brief       Subtract a quaternion from *this
    //!              
    //! @param       rhs [in] Quaternion to subtract
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::operator-= ( const Quaternion& rhs )
	{
		W ( W() - rhs.W() );
		X ( X() - rhs.X() );
		Y ( Y() - rhs.Y() );
		Z ( Z() - rhs.Z() );

		return (*this);
	}
	//end Quaternion::operator -=



	//=========================================================================
    //! @function    Quaternion::operator *=
    //! @brief       Multiply *this by a quaternion
    //!              
    //! @param       rhs [in] Quaternion to multiply
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::operator*= ( const Quaternion& rhs )
	{
		
		Scalar tempW = W()*rhs.W() - X()*rhs.X() - Y()*rhs.Y() - Z()*rhs.Z();
		Scalar tempX = W()*rhs.X() + X()*rhs.W() + Y()*rhs.Z() - Z()*rhs.Y();
		Scalar tempY = W()*rhs.Y() - X()*rhs.Z() + Y()*rhs.W() + Z()*rhs.X();
		Scalar tempZ = W()*rhs.Z() + X()*rhs.Y() - Y()*rhs.X() + Z()*rhs.W();

		W ( tempW );
		X ( tempX );
		Y ( tempY );
		Z ( tempZ );

		return *this;
	}
	//end Quaternion::operator *=



	 //=========================================================================
    //! @function    Quaternion::operator *=
    //! @brief       Multiply *this by a scalar
    //!              
    //! @param       rhs [in] Scalar to multiply *this by
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::operator*= ( Scalar rhs )
	{
		W ( W() * rhs );
		X ( X() * rhs );
		Y ( Y() * rhs );
		Z ( Z() * rhs );

		return (*this);
	}
	//end Quaternion::operator *=



    //=========================================================================
    //! @function    Quaternion::operator -
    //! @brief       Return the inverse of a quaternion
    //!              
    //!              
    //! @return      The inverse of a quaternion
    //! @throw       
    //=========================================================================
	Quaternion Quaternion::operator- () const
	{
		return Inverse();
	}
	//End  Quaternion::operator -



    //=========================================================================
    //! @function    Quaternion::Conjugate
    //! @brief       Return the quaternion conjugate
    //!              
    //!              
    //! @return      A quaternion equal to this quaternions conjugate 
    //=========================================================================
	Quaternion Quaternion::Conjugate ( ) const
	{
		return Quaternion ( W(), -X(), -Y(), -Z() );
	}
	//end Quaternion::Conjugate



    //=========================================================================
    //! @function    Quaternion::Norm
    //! @brief       Return the "norm",(length) of the quaternion
    //!              
    //!              
    //! @return      The length of the quaternion
    //=========================================================================
	Scalar Quaternion::Norm ( ) const
	{
		return Sqrt ( W()*W() + X()*X() + Y()*Y() + Z()*Z() );
	}
	//end Quaternion::Norm



    //=========================================================================
    //! @function    Quaternion::Inverse
    //! @brief       Return the inverse of the quaternion
    //!              
    //! @return      A quaternion equal to the inverse of this one
    //! @throw       
    //=========================================================================
	Quaternion Quaternion::Inverse ( ) const
	{
		return Quaternion( *this ).Invert();
	}
	//end Quaternion::Inverse



    //=========================================================================
    //! @function    Quaternion::UnitInverse
    //! @brief       Return the inverse of the quaternion, assuming the
    //!              quaternion is a unit quaternion
    //!              
	//!				 Returns the conjugate, since for a unit quaternion, the
	//!				 inverse is equal to the conjugate
	//!
    //! @return      The conjugate of the quaternion
	//=========================================================================
	Quaternion Quaternion::UnitInverse ( ) const
	{
		debug_assert (Equal(Norm(), 1.0f), "UnitInverse requires a unit quaternion!" );
		return ( Conjugate() );
	}
	//end Quaternion::UnitInverse



    //=========================================================================
    //! @function    Quaternion::SetToConjugate
    //! @brief       Set the quaternion to its conjugate
    //!              
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::SetToConjugate ( )
	{
		X( -X() );
		Y( -Y() );
		Z( -Z() );

		return *this;
	}
	//end Quaternion::SetToConjugate



    //=========================================================================
    //! @function    Quaternion::Normalise
    //! @brief       Normalise the quaternion
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::Normalise ( )
	{
		Scalar norm = Norm();

		X( X() / norm );
		Y( Y() / norm );
		Z( Z() / norm );
		W( W() / norm );

		return *this;
	}
	//end Quaternion::Normalise



    //=========================================================================
    //! @function    Quaternion::Invert
    //! @brief       Invert the quaternion
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::Invert ( )
	{
		SetToConjugate ();
		Scalar lengthSquared = ( W()*W() + X()*X() + Y()*Y() + Z()*Z() );

		X ( X() / lengthSquared );
		Y ( Y() / lengthSquared );
		Z ( Z() / lengthSquared );
		W ( W() / lengthSquared );

		return *this;
	}
	//end Quaternion::Invert ( )



    //=========================================================================
    //! @function    Quaternion::UnitInvert
    //! @brief       Invert the quaterion, assuming it is a unit quaternion
    //!              
    //!              
    //! @return      *this
    //=========================================================================
	Quaternion& Quaternion::UnitInvert ( )
	{
		debug_assert (Equal(Norm(), 1.0f), "UnitInvert requires a unit quaternion!" );
		SetToConjugate ();
		return *this;
	}
	//end Quaternion::UnitInvert ( )



    //=========================================================================
    //Non-member functions
    //=========================================================================



    //=========================================================================
    //! @function    operator + ( const Quaternion&, const Quaternion& )
    //! @brief       Return the sum of two quaternions
    //!              
    //! @param       lhs [in] 
    //! @param       rhs [in] 
    //!              
    //! @return      The sum of the two quaternions
    //=========================================================================
	Quaternion operator + ( const Quaternion& lhs, const Quaternion& rhs )
	{
		return Quaternion ( lhs ) += rhs;
	}
	//end Quaternion::operator +



    //=========================================================================
    //! @function    operator -
    //! @brief       Return the difference of two quaternions
    //!              
    //! @param       lhs 
    //! @param       rhs 
    //!              
    //! @return      The difference of the two quaternions
    //=========================================================================
	Quaternion operator- ( const Quaternion& lhs, const Quaternion& rhs )
	{
		return Quaternion ( lhs ) -= rhs;
	}
	//end Quaternion::operator -



    //=========================================================================
    //! @function    operator *
    //! @brief       Return the product of two quaternions
    //!              
    //! @param       lhs 
    //! @param       rhs 
    //!              
    //! @return      The product of two quaternions
    //=========================================================================
	Quaternion operator * ( const Quaternion& lhs, const Quaternion& rhs )
	{
		return Quaternion ( lhs ) *= rhs;
	}
	//end Quaternion::operator * (Quaternion)



    //=========================================================================
    //! @function    operator *
    //! @brief       Return the product of a quaternion and a scalar
    //!              
    //! @param       lhs 
    //! @param       rhs 
    //!              
    //! @return      The product of the quaternion and scalar
    //=========================================================================
	Quaternion operator* ( const Quaternion& lhs, Scalar rhs  )
	{
		return Quaternion ( lhs ) *= rhs;
	}
	//end Quaternion::operator * (Quaternion)


	//=========================================================================
	//! @function    operator << ( std::ostream&, const Quaternion&  )
	//! @brief       Write formatted output, about a Quaternion to an ostream
	//!              
	//! @param       outStream [in] output stream
	//! @param       quat	   [in] quaternion to be written
	//!              
	//! @return      outStream
	//=========================================================================
	std::ostream& operator << ( std::ostream& outStream, const Quaternion& quat )
	{
		return outStream << "( " << quat.W() << " + <" << quat.X() << ", " << quat.Y() << ", " << quat.Z() << "> )";
	}
	//end operator << ( std::ostream&, const Vector3D&  )



};
//end namespace Math

#endif //#ifndef MATH_QUATERNION_H