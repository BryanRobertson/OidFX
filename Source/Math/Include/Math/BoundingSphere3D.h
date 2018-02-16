//======================================================================================
//! @file         BoundingSphere3D.h
//! @brief        Class representing a 3D bounding sphere
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 07 September 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================


#ifndef MATH_BOUNDINGSPHERE3D_H
#define MATH_BOUNDINGSPHERE3D_H


#include "Math/Math.h"
#include "Math/Vector3D.h"
#include "Math/BoundingBox3D.h"


//namespace Math
namespace Math
{


	//!@class	BoundingSphere3D
	//!@brief	Class representing a 3D bounding sphere
	class BoundingSphere3D
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			inline BoundingSphere3D();
			explicit inline BoundingSphere3D ( Scalar radius, const Vector3D& position = Vector3D() ) throw();
			explicit inline BoundingSphere3D ( const AxisAlignedBoundingBox& box );


            //=========================================================================
            // Public methods
            //=========================================================================
			inline Scalar		   Radius() const throw();
			inline Scalar		   RadiusSquared() const throw();
			inline const Vector3D& GetPosition() const throw();

			inline void SetPosition ( const Vector3D& position ) throw();

		private:

            //=========================================================================
            // Private data
            //=========================================================================
			Scalar		m_radius;
			Scalar		m_radiusSquared;
			Vector3D	m_position;

	};
	//End class BoundingSphere3D



	//=========================================================================
    //! @function    BoundingSphere3D::BoundingSphere3D
    //! @brief       BoundingSphere3D 
    //!              
    //! @param       radius [in]
    //=========================================================================
	BoundingSphere3D::BoundingSphere3D ()
	: m_radius(0.0f), m_radiusSquared(0.0f), m_position(0.0f, 0.0f, 0.0f)
	{
	}
	//End BoundingSphere3D::BoundingSphere3D



    //=========================================================================
    //! @function    BoundingSphere3D::BoundingSphere3D
    //! @brief       Construct a bounding sphere from an axis aligned bounding box
    //!              
    //! @param       box [in]
    //!              
    //=========================================================================
	BoundingSphere3D::BoundingSphere3D ( const AxisAlignedBoundingBox& box )
	{
		
		Math::Vector3D maxToMin = (box.Max() - box.Min()) / 2.0f;

		m_position = box.Position();
		m_radiusSquared = maxToMin.LengthSquared();
		m_radius = maxToMin.Length();

	}
	//End BoundingSphere3D::BoundingSphere3D


    //=========================================================================
    //! @function    BoundingSphere3D::BoundingSphere3D
    //! @brief       BoundingSphere3D 
    //!              
    //! @param       radius [in]
    //=========================================================================
	BoundingSphere3D::BoundingSphere3D ( Scalar radius, const Vector3D& position )
		: m_radius(radius), m_position(position)
	{
		m_radiusSquared = m_radius * m_radius;
	}
	//End BoundingSphere3D::BoundingSphere3D



    //=========================================================================
    //! @function    BoundingSphere3D::Radius
    //! @brief       Get the radius of the bounding sphere
	//!
    //! @return      The radius of the bounding sphere
    //=========================================================================
	Scalar BoundingSphere3D::Radius ( ) const
	{
		return m_radius;
	}
	//End BoundingSphere3D::Radius


	//=========================================================================
    //! @function    BoundingSphere3D::RadiusSquared
    //! @brief       Get the radius of the bounding sphere squared
	//!
    //! @return      The radius of the bounding sphere squared
    //=========================================================================
	Scalar BoundingSphere3D::RadiusSquared ( ) const
	{
		return m_radiusSquared;
	}
	//End BoundingSphere3D::RadiusSquared


    //=========================================================================
    //! @function    BoundingSphere3D::GetPosition
    //! @brief       Get the position of the bounding sphere
    //!              
    //! @return      The position of the bounding sphere
    //=========================================================================
	const Vector3D& BoundingSphere3D::GetPosition () const
	{
		return m_position;
	}
	//End BoundingSphere3D::GetPosition


    //=========================================================================
    //! @function    BoundingSphere3D::SetPosition
    //! @brief       Set the position of the bounding sphere
    //!              
	//!	@param		 position [in] New position of the sphere
	//!
    //=========================================================================
	void BoundingSphere3D::SetPosition( const Math::Vector3D& position )
	{
		m_position = position;
	}
	//End BoundingSphere3D::SetPosition

}
//end namespace Math


#endif
//#ifndef MATH_BOUNDINGSPHERE_H