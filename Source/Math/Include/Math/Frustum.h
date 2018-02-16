//======================================================================================
//! @file         Frustum.h
//! @brief        Class representing a view frustum
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


#ifndef MATH_FRUSTUM_H
#define MATH_FRUSTUM_H


#include "Math/Math.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3D.h"
#include "Math/Plane3D.h"


//namespace Math
namespace Math
{

	
	//!@class	Frustum
	//!@brief	Class representing a view frustum
	class Frustum
	{
		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			inline Frustum ();

			inline Frustum ( const Plane3D& nearPlane, 
							 const Plane3D& farPlane,
							 const Plane3D& leftPlane,
							 const Plane3D& rightPlane,
							 const Plane3D& topPlane,
							 const Plane3D& bottomPlane );

			inline Frustum ( const Matrix4x4& matrix, bool normalise );

            //=========================================================================
            // Public methods
            //=========================================================================
			const Plane3D& Near()	const		{ return m_nearPlane;	}
			const Plane3D& Far()	const		{ return m_farPlane;	}
			const Plane3D& Left()	const		{ return m_leftPlane;	}
			const Plane3D& Right()	const		{ return m_rightPlane;	}
			const Plane3D& Bottom() const		{ return m_bottomPlane;	}
			const Plane3D& Top()	const		{ return m_topPlane;	}
			
			void Near( const Plane3D& nearPlane )		{ m_nearPlane = nearPlane;		}
			void Far( const Plane3D& farPlane )			{ m_farPlane = farPlane;		}
			void Left( const Plane3D& leftPlane )		{ m_leftPlane = leftPlane;		}
			void Right( const Plane3D& rightPlane )		{ m_rightPlane = rightPlane;	}
			void Bottom( const Plane3D& bottomPlane )	{ m_bottomPlane = bottomPlane;	}
			void Top( const Plane3D& topPlane)			{ m_topPlane = topPlane;		}

		private:

            //=========================================================================
            // Private data
            //=========================================================================
			Plane3D m_bottomPlane;
			Plane3D m_topPlane;
			Plane3D m_leftPlane;
			Plane3D m_rightPlane;
			Plane3D m_nearPlane;
			Plane3D m_farPlane;

	};
	//End class Frustum



    //=========================================================================
    // Declaration of non-member functions
    //=========================================================================
	inline std::ostream& operator << ( std::ostream& os, const Frustum& frustum );



    //=========================================================================
    //! @function    Frustum::Frustum
    //! @brief       Frustum default constructor
    //!              
    //=========================================================================
	Frustum::Frustum ()
	{

	}
	//End Frustum::Frustum


    //=========================================================================
    //! @function    Frustum::Frustum
    //! @brief       Frustum constructor
    //!              
    //!              
    //! @param		 nearPlane		[in]
	//!				 farPlane		[in]
	//!				 leftPlane		[in]
	//!				 rightPlane		[in]
	//!				 topPlane		[in]
    //!				 bottomPlane    [in]
    //=========================================================================
	Frustum::Frustum ( const Plane3D& nearPlane, 
						const Plane3D& farPlane,
						const Plane3D& leftPlane,
						const Plane3D& rightPlane,
						const Plane3D& topPlane,
						const Plane3D& bottomPlane )

	:  m_nearPlane(nearPlane), m_farPlane(farPlane), m_leftPlane(leftPlane),
	   m_rightPlane(rightPlane), m_topPlane(topPlane), m_bottomPlane(bottomPlane)
					
	{
	}
	//End Frustum::Frustum



    //=========================================================================
    //! @function    Frustum::Frustum
    //! @brief       Construct a frustum from a matrix
	//!
	//!				 If the matrix is a projection matrix, then the 
	//!				 frustum will be in view space
	//!
	//!				 If the matrix is a combined view projection matrix, then
	//!				 the frustum will be in world space
	//!
	//!				 If the matrix is a combined world, view, projection matrix,
	//!				 then the frustum will be in object space
	//!
	//!				 Algorithm taken from the paper
	//!				 "Fast Extraction of Viewing Frustum Planes from the World-
	//!				 View-Projection Matrix" by Gil Gribb and Klaus Hartmann
    //!              
    //! @param       matrix	   [in]
	//! @param		 normalise [in] Indicates whether or not the planes will be normalised
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	Frustum::Frustum ( const Matrix4x4& matrix, bool normalise  )
	{

		// Near clipping plane
		m_nearPlane = Plane3D ( matrix(0,2),
								matrix(1,2),
								matrix(2,2),
								matrix(3,2), normalise );

		// Far clipping plane
		m_farPlane = Plane3D ( matrix(0,3) - matrix(0,2),
							   matrix(1,3) - matrix(1,2),
							   matrix(2,3) - matrix(2,2),
							   matrix(3,3) - matrix(3,2), normalise );

		// Left clipping plane
		m_leftPlane = Plane3D( matrix(0,3) + matrix(0,0),
							   matrix(1,3) + matrix(1,0),
							   matrix(2,3) + matrix(2,0),
							   matrix(3,3) + matrix(3,0), normalise );

		// Right clipping plane
		m_rightPlane = Plane3D ( matrix(0,3) - matrix(0,0),
							matrix(1,3) - matrix(1,0),
							matrix(2,3) - matrix(2,0),
							matrix(3,3) - matrix(3,0), normalise );

		// Bottom clipping plane
		m_bottomPlane = Plane3D ( matrix(0,3) + matrix(0,1),
							 matrix(1,3) + matrix(1,1),
							 matrix(2,3) + matrix(2,1),
							 matrix(3,3) + matrix(3,1), normalise );
		
		// Top clipping plane
		m_topPlane = Plane3D ( matrix(0,3) - matrix(0,1),
						  matrix(1,3) - matrix(1,1),
						  matrix(2,3) - matrix(2,1),
						  matrix(3,3) - matrix(3,1), normalise );

	}
	//End Frustum::Frustum



    //=========================================================================
    //! @function    operator << ( std::ostream& , const Frustum& )
    //! @brief       Formatted output of a frustum to an output stream
    //!              
    //! @param       os		 [in/out] 
    //! @param       frustum [in]
    //!              
    //! @return      os
    //=========================================================================
	std::ostream& operator << ( std::ostream& os, const Frustum& frustum )
	{
		os << "Near plane: "   << frustum.Near()	<< std::endl;
		os << "Far plane : "   << frustum.Far()		<< std::endl;
		os << "Left plane: "   << frustum.Left()	<< std::endl;
		os << "Right plane: "  << frustum.Right()	<< std::endl;
		os << "Bottom plane: " << frustum.Bottom()	<< std::endl;
		os << "Top plane: "	   << frustum.Top()		<< std::endl;

		return os;
	}
	//End operator << ( std::ostream& , const Frustum& )



}
//End namespace Math


#endif
//#ifndef MATH_FRUSTUM_H

