//======================================================================================
//! @file         TargetingComputer.h
//! @brief        Class representing the targeting computer in an entity which
//!               can fire projectiles.
//!
//!				  The targeting computer searches the immediate area for targetable entities
//!				  and assigns a target.
//!
//!				  In future versions, this will be used to draw a target billboard over
//!               the target
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 06 September 2005
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

#ifndef OIDFX_TARGETINGCOMPUTER_H
#define OIDFX_TARGETINGCOMPUTER_H

#include "OidFX/Billboard.h"
#include "OidFX/EntityNode.h"




//namespace OidFX
namespace OidFX
{

	//! Flags that govern the behaviour of the targeting computer
	enum ETargetingComputerFlags
	{
		TCF_TARGETPLAYERS,		//!< Targeting computer will flag players as targetable
		TCF_TARGETENEMIES,		//!< Targeting computer will flag enemies as targetable
		TCF_TARGETALLIES,		//!< Targeting computer will flag allies as targetable
		TCF_IGNOREANGLE,		//!< Targeting computer can target objects behind it
		TCF_DRAWTARGET,			//!< Targeting computer will draw a target over its target
		TCF_COUNT
	};
	//End ETargetingComputerFlags


	//!@class	TargetingComputer
	//!@brief	 Class representing the targeting computer in an entity which
	//!          can fire projectiles.
	//!
	//!			The targeting computer searches the immediate area for targetable entities
	//!			and assigns a target.
	//!
	//!			In future versions, this will be used to draw a target billboard over the target
	class TargetingComputer : public EntityNode
	{

		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			TargetingComputer ( Scene& scene );

            //=========================================================================
            // Public methods
            //=========================================================================	
			void Update( Math::MatrixStack& toWorldStack, 
						 Math::MatrixStack& fromWorldStack, 
						 Float timeElapsedInSeconds );

			//Get the closest target
			void AcquireTarget ();
			inline EntityNode* GetCurrentTarget ();

			//Maximum search radius
			inline Float GetMaxRange () const;
			inline void  SetMaxRange ( Float maxRange );

			//=========================================================================
            // Flags 
            //=========================================================================

			//Import the parent methods, so that our new flag methods don't hide them
			using EntityNode::SetFlag;
			using EntityNode::ClearFlag;
			using EntityNode::IsFlagSet;

			inline void SetFlag	 ( ETargetingComputerFlags flag );
			inline void ClearFlag ( ETargetingComputerFlags flag );
			inline bool IsFlagSet ( ETargetingComputerFlags flag ) const;

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			typedef std::bitset<TCF_COUNT>	TargetComputerFlagSet;


            //=========================================================================
            // Private methods
            //=========================================================================
			bool CanTarget ( const EntityNode* entity ) const;
		
            //=========================================================================
            // Private data
            //=========================================================================
			EntityNode*			  m_currentTarget;
			TargetComputerFlagSet m_targetComputerFlags;

			Float				  m_maxRange;
			Float				  m_timeSinceLastUpdate;

			Billboard			  m_targetDisplay;
			Math::Vector3D		  m_targetDisplayOffset;

	};
	//End class TargetingComputer



    //=========================================================================
    //! @function    TargetingComputer::SetFlag
    //! @brief       Set one of the internal flags
    //!              
    //! @param       flag [in]	
    //!              
    //=========================================================================
	void TargetingComputer::SetFlag	( ETargetingComputerFlags flag)
	{
		m_targetComputerFlags[flag] = true;
	}
	//End TargetingComputer::SetFlag



    //=========================================================================
    //! @function    TargetingComputer::ClearFlag
    //! @brief       Clear one of the internal flags
    //!              
    //! @param       flag [in]	
    //!              
    //=========================================================================
	void TargetingComputer::ClearFlag ( ETargetingComputerFlags flag )
	{
		m_targetComputerFlags[flag] = false;
	}
	//End TargetingComputer::ClearFlag



    //=========================================================================
    //! @function    TargetingComputer::IsFlagSet
    //! @brief       Indicate whether or not a flag is set
    //!              
	//! @param		 flag [in]
	//!
    //! @return      true if the flag is set, false otherwise
    //=========================================================================
	bool TargetingComputer::IsFlagSet ( ETargetingComputerFlags flag ) const
	{
		return m_targetComputerFlags[flag];
	}
	//End TargetingComputer::IsFlagSet 



    //=========================================================================
    //! @function    TargetingComputer::GetCurrentTarget
    //! @brief       Return a pointer to the entity that this targeting computer 
    //!              is currently targeting, this will be null if there is no target
    //!              
    //! @return      The entity that is being targeted, or null if no entity is being targeted
    //=========================================================================
	EntityNode* TargetingComputer::GetCurrentTarget ()
	{
		return m_currentTarget;
	}
	//End TargetingComputer::GetCurrentTarget



    //=========================================================================
    //! @function    TargetingComputer::SetMaxRange
    //! @brief       Set the maximum radius of the targeting computer
    //!              
    //! @param       maxRange [in] Maximum radius at which targets can be found
    //!              
    //=========================================================================
	void TargetingComputer::SetMaxRange ( Float maxRange )
	{
		m_maxRange = maxRange;
	}
	//End TargetingComputer::SetMaxRange


    //=========================================================================
    //! @function    TargetingComputer::GetMaxRange
    //! @brief       Get the maximum radius at which the computer will detect targets
	//!
    //! @return      The maximum detection range
    //=========================================================================
	Float TargetingComputer::GetMaxRange ( ) const
	{
		return m_maxRange;
	}
	//End TargetingComputer::GetMaxRange

}
//end namespace OidFX

#endif
//#ifndef OIDFX_TARGETINGCOMPUTER_H
