//======================================================================================
//! @file         NewtonCollision.h
//! @brief        Class wrapper for Newton Collision objects
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 21 September 2005
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

#ifndef OIDFX_NEWTONCOLLISION_H
#define OIDFX_NEWTONCOLLISION_H


#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include "OidFX/NewtonWrapper.h"
#include "OidFX/NewtonWorld.h"


//namespace OidFX
namespace OidFX
{

	//namespace Newton
	namespace Newton
	{


		//!@class	Collision
		//!@brief	Class wrapper for Newton Collision objects
		class Collision
		{
			
			public:

                //=========================================================================
                // Public Constructors
                //=========================================================================
				inline Collision();
				inline ~Collision();

                //=========================================================================
                // Public methods
                //=========================================================================
				inline bool IsNull() const;

				inline void Release( Impl::NewtonCollision* collision );


                //=========================================================================
                // Friends
                //=========================================================================
				//Allow World access to our private constructor
				friend class World;


			private:

				//=========================================================================
                // Private Constructors
                //=========================================================================
				inline Collision ( World* world, Impl::NewtonCollision* collision );


                //=========================================================================
                // Private methods
                //=========================================================================
				inline const Impl::NewtonCollision* GetCollision() const;

                //=========================================================================
                // Private methods
                //=========================================================================
				boost::shared_ptr<Impl::NewtonCollision>	m_collision;
				World*										m_world;

		};
		//End class Collision



        //=========================================================================
        //! @function    Collision::Collision
        //! @brief       Collision default constructor
        //!              
        //=========================================================================
		Collision::Collision()
			: m_world(0)
		{
			//Does nothing
		}
		//End Collision::Collision


		//=========================================================================
        //! @function    Collision::~Collision
        //! @brief       Collision destructor
        //!              
        //=========================================================================
		Collision::~Collision()
		{
		}
		//End Collision::~Collision



        //=========================================================================
        //! @function    Collision::IsNull
        //! @brief       Indicates whether or not this object refers to a valid
        //!              Newton collision object
		//!
        //! @return      true if this is a valid collision object, false if this is a null collision object
        //=========================================================================
		bool Collision::IsNull() const
		{
			return !(m_collision);
		}
		//End Collision::IsNull


		//=========================================================================
        //! @function    Collision::Release
        //! @brief       Releases a collision object. After this call completes,
		//!				 the collision object will be null
        //=========================================================================
		void Collision::Release ( Impl::NewtonCollision* collision )
		{
			debug_assert ( m_world, "World is NULL!" );

			Impl::NewtonReleaseCollision ( m_world->GetWorld(), collision );
			m_world = 0;

		}
		//End Collision::Release


        //=========================================================================
        //! @function    Collision::Collision
        //! @brief       Collision constructor
        //!              
		//!				 Called by the World class, when creating a new Collision object
        //=========================================================================
		Collision::Collision ( World* world, Impl::NewtonCollision* collision )
		{

			debug_assert ( collision, "Collision is null!" );

			m_world = world;

			//Note that we create the shared pointer with a custom deleter, that calls Release
			m_collision = boost::shared_ptr<Impl::NewtonCollision> ( collision, boost::bind(&Collision::Release, *this, _1) );
			
		}
		//End Collision::Collision



		//=========================================================================
        //! @function    Collision::GetCollision
        //! @brief       Return a pointer to the underlying NewtonCollision object
		//!
		//!				 This is private, and therefore can only be used by 
		//!				 the World class, which is a friend
        //=========================================================================
		const Impl::NewtonCollision* Collision::GetCollision() const
		{
			debug_assert(!IsNull(), "Collision object is null!" );

			return m_collision.get();
		}
		//End  Collision::GetCollision


	}
	//end namespace Newton

}
//end namespace OidFX


#endif
//#ifndef OIDFX_NEWTONCOLLISION_H

