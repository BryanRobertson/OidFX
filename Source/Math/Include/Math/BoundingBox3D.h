//======================================================================================
//! @file         BoundingBox3D.h
//! @brief        Classes representing 3D bounding boxes 
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 21 July 2005
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


#ifndef MATH_BOUNDINGBOX_H
#define MATH_BOUNDINGBOX_H


#include "Math/Math.h"
#include "Math/Vector3D.h"


//namespace Math
namespace Math
{



	//!@class	AxisAlignedBoundingBox
	//!@brief	Class representing an axis aligned bounding box
	class AxisAlignedBoundingBox
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			AxisAlignedBoundingBox ( ) {}; //Construct a zero size bounding box
			inline AxisAlignedBoundingBox ( const Vector3D& min, const Vector3D& max ) throw();


            //=========================================================================
            // Public types
            //=========================================================================
			enum ECorner
			{
				MIN_X_MIN_Y_MIN_Z,
				MIN_X_MIN_Y_MAX_Z,
				MIN_X_MAX_Y_MIN_Z,
				MIN_X_MAX_Y_MAX_Z,
				MAX_X_MIN_Y_MIN_Z,
				MAX_X_MIN_Y_MAX_Z,
				MAX_X_MAX_Y_MIN_Z,
				MAX_X_MAX_Y_MAX_Z
			};

            //=========================================================================
            // Public methods
            //=========================================================================
			inline void SetPosition ( const Vector3D& newPosition );
			inline const Vector3D& Position () const		{ return m_position;	}

			inline Float ExtentX() const throw();
			inline Float ExtentY() const throw();
			inline Float ExtentZ() const throw();

			inline Vector3D GetCorner ( ECorner index ) const throw();
			inline Vector3D GetCentre () const throw();

			inline const Math::Vector3D& Min() const throw();
			inline const Math::Vector3D& Max() const throw();
            
		private:

			Vector3D	m_position;
			Vector3D	m_min;
			Vector3D	m_max;

	};
	//End class AxisAlignedBoundingBox


	
    //=========================================================================
    // Definitions of non-member functions
    //=========================================================================
	inline std::ostream& operator << ( std::ostream& os, const AxisAlignedBoundingBox& box );



    //=========================================================================
    //! @function    operator << ( std::ostream&, const AxisAlignedBoundingBox& )
    //! @brief       Formatted output of a bounding box to an output stream
    //!              
    //! @param       os  [in/out]
    //! @param       box [in]
    //!              
    //! @return      os
    //=========================================================================
	std::ostream& operator << ( std::ostream& os, const AxisAlignedBoundingBox& box )
	{
		return os << box.GetCorner(AxisAlignedBoundingBox::MIN_X_MIN_Y_MIN_Z) 
				  << ";"
				  << box.GetCorner(AxisAlignedBoundingBox::MAX_X_MAX_Y_MAX_Z);
	}
	//End operator << ( std::ostream&, const AxisAlignedBoundingBox& )



    //=========================================================================
    //! @function    AxisAlignedBoundingBox::AxisAlignedBoundingBox
    //! @brief       AxisAlignedBoundingBox constructor
    //!                
    //! @param       min [in] Minimum point of the bounding box
    //! @param       max [in] Maximum point of the bounding box
    //!              
    //=========================================================================
	AxisAlignedBoundingBox::AxisAlignedBoundingBox( const Vector3D& min, const Vector3D& max )
		: m_min(min), m_max(max)
	{
	}
	//End AxisAlignedBoundingBox::AxisAlignedBoundingBox


    //=========================================================================
    //! @function    AxisAlignedBoundingBox::SetPosition
    //! @brief       Set the position of the bounding box
    //!              
    //! @param       newPosition [in]
    //!              
    //=========================================================================
	void AxisAlignedBoundingBox::SetPosition ( const Vector3D& newPosition )
	{
		m_position = newPosition;
	}
	//End AxisAlignedBoundingBox::SetPosition


    //=========================================================================
    //! @function    AxisAlignedBoundingBox::ExtentX
    //! @brief       Return the extent of the bounding box in the X dimension
	//!
    //! @return      The extent of the bounding box in the X dimension
    //=========================================================================
	Float AxisAlignedBoundingBox::ExtentX() const
	{
		return m_max.X() - m_min.X();
	}
	//End AxisAlignedBoundingBox::ExtentX


	//=========================================================================
    //! @function    AxisAlignedBoundingBox::ExtentY
    //! @brief       Return the extent of the bounding box in the Y dimension
	//!
    //! @return      The extent of the bounding box in the Y dimension
    //=========================================================================
	Float AxisAlignedBoundingBox::ExtentY() const
	{
		return m_max.Y() - m_min.Y();
	}
	//End AxisAlignedBoundingBox::ExtentY


    //=========================================================================
    //! @function    AxisAlignedBoundingBox::ExtentZ
    //! @brief       Return the extent of the bounding box in the Z dimension
	//!
    //! @return      The extent of the bounding box in the Z dimension
    //=========================================================================
	Float AxisAlignedBoundingBox::ExtentZ() const
	{
		return m_max.Z() - m_min.Z();
	}
	//End AxisAlignedBoundingBox::ExtentZ


    //=========================================================================
    //! @function    AxisAlignedBoundingBox::GetCorner
    //! @brief       Get one of the corners of the bounding box
    //!              
    //! @param       index [in] 
    //!              
    //! @return      A vector representing the point at the specified corner
    //=========================================================================
	Vector3D AxisAlignedBoundingBox::GetCorner ( AxisAlignedBoundingBox::ECorner index ) const
	{
		switch ( index )
		{
			case MIN_X_MIN_Y_MIN_Z:
				return Vector3D( m_min.X() + m_position.X(),   
								 m_min.Y() + m_position.Y(),   
								 m_min.Z() + m_position.Z()  );

			case MIN_X_MIN_Y_MAX_Z:
				return Vector3D( m_min.X() + m_position.X(),   
								 m_min.Y() + m_position.Y(),   
								 m_max.Z() + m_position.Z() );

			case MIN_X_MAX_Y_MIN_Z:
				return Vector3D( m_min.X() + m_position.X(),   
								 m_max.Y() + m_position.Y(),   
								 m_min.Z() + m_position.Z() );

			case MIN_X_MAX_Y_MAX_Z:
				return Vector3D( m_min.X() + m_position.X(),   
								 m_max.Y() + m_position.Y(),   
								 m_max.Z() + m_position.Z() );

			case MAX_X_MIN_Y_MIN_Z:
				return Vector3D( m_max.X() + m_position.X(),   
								 m_min.Y() + m_position.Y(),   
								 m_min.Z() + m_position.Z() );

			case MAX_X_MIN_Y_MAX_Z:
				return Vector3D( m_max.X() + m_position.X(),   
								 m_min.Y() + m_position.Y(),   
								 m_max.Z() + m_position.Z() );

			case MAX_X_MAX_Y_MIN_Z:
				return Vector3D( m_max.X() + m_position.X(),   
								 m_max.Y() + m_position.Y(),   
								 m_min.Z() + m_position.Z() );

			case MAX_X_MAX_Y_MAX_Z:
				return Vector3D( m_max.X() + m_position.X(),   
								 m_max.Y() + m_position.Y(),   
								 m_max.Z() + m_position.Z());

			default:
				debug_error ( "Invalid corner type!" );
		}
	}
	//End AxisAlignedBoundingBox::Corner


    //=========================================================================
    //! @function    AxisAlignedBoundingBox::GetCentre
    //! @brief       Get the centre point of the bounding box
    //!              
    //! @return		 The centre point of the bounding box             
    //=========================================================================
	Vector3D AxisAlignedBoundingBox::GetCentre() const
	{
		return ((GetCorner(MAX_X_MAX_Y_MAX_Z) + GetCorner(MIN_X_MIN_Y_MIN_Z)) / 2.0f);
	}
	//End AxisAlignedBoundingBox::GetCentre


    //=========================================================================
    //! @function    AxisAlignedBoundingBox::Min
    //! @brief       Return the minimum point of the bounding box
    //!				 in the box's object space (not affected by the position of the box)
    //!              
    //! @return      The minimum point of the bounding box in the box's object space
    //=========================================================================
	const Math::Vector3D& AxisAlignedBoundingBox::Min() const
	{
		return m_min;
	}
	//End AxisAlignedBoundingBox::Min


    //=========================================================================
    //! @function    AxisAlignedBoundingBox::Max
    //! @brief       Return the maximum point of the bounding box
    //!              in the box's object space ( not affected by the position of the box )
	//!
    //! @return      The maximum point of the bounding box in the box's object space
    //=========================================================================
	const Math::Vector3D& AxisAlignedBoundingBox::Max() const
	{
		return m_max;
	}
	//End AxisAlignedBoundingBox::Max

}
//end namespace Math


#endif
//#ifndef MATH_BOUNDINGBOX_H
