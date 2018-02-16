//======================================================================================
//! @file         MissileLauncher.h
//! @brief        Class for an Entity which can launch projectiles.
//!				  
//!               
//! @author       Bryan Robertson
//! @date         Monday, 05 September 2005
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


#ifndef OIDFX_MISSILELAUNCHER_H
#define OIDFX_MISSILELAUNCHER_H




//=========================================================================
// Forward declarations
//=========================================================================
namespace OidFX		{ class TargetingComputer;	}


//namespace OidFX
namespace OidFX
{


	//Flags governing the behaviour of a missile launcher
	enum EMissileLauncherFlags
	{
		MF_INFINITEAMMO,		//!< Missile launcher never runs out of ammunition
	
		MF_COUNT
	};
	//End EMissileLauncherFlags


	//!@class	MissileLauncher
	//!@brief	Class for an entity which launches missiles
	class MissileLauncher : public EntityNode
	{

		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			MissileLauncher ( Scene& scene,
							  TargetingComputer& targetingComputer,
							  const Char* meshFileName );

            //=========================================================================
            // Public types
            //=========================================================================
			enum ELauncherState
			{
				LS_READY,
				LS_RELOADING
				
			};

            //=========================================================================
            // Public methods
            //=========================================================================
			void Update( Math::MatrixStack& toWorldStack, 
						 Math::MatrixStack& fromWorldStack, 
						 Float timeElapsedInSeconds );

			bool LaunchMissile ( );

			inline void  SetAmmunition ( UInt count );
			inline void  DeductAmmunition ( UInt count );
			inline void  IncreaseAmmunition ( UInt count );
			inline void  SetReloadTime ( Float time );
			inline Float GetReloadTime ( ) const;
			inline UInt  GetAmmunition ( ) const;
			inline bool  IsEmpty () const;

			//=========================================================================
            // Flags 
            //=========================================================================

			//Import the parent methods, so that our new flag methods don't hide them
			using EntityNode::SetFlag;
			using EntityNode::ClearFlag;
			using EntityNode::IsFlagSet;

			inline void SetFlag ( EMissileLauncherFlags flag );
			inline void ClearFlag ( EMissileLauncherFlags flag );
			inline bool IsFlagSet ( EMissileLauncherFlags flag ) const;

		private:

            //=========================================================================
            // Private methods
            //=========================================================================

            //=========================================================================
            // Private data
            //=========================================================================
			ELauncherState		m_launcherState;
			TargetingComputer&	m_targetingComputer;
			UInt				m_ammunition;
			Float				m_reloadTime;
			Float				m_timeElapsedSinceLastFired;

			std::bitset<MF_COUNT> m_launcherFlags;
	};
	//End class MissileLauncher



    //=========================================================================
    //! @function    MissileLauncher::SetAmmunition
    //! @brief       Set the number of ammunition in the missile launcher
    //!              
    //! @param       count [in] Number of missiles in the launcher 
    //!              
    //=========================================================================
	void MissileLauncher::SetAmmunition ( UInt count )
	{
		m_ammunition = count;
	}
	//End MissileLauncher::SetAmmunitionCount


    //=========================================================================
    //! @function    MissileLauncher::DeductAmmunition
    //! @brief       Deduct count missiles from the ammunition store
    //!              
    //! @param       count [in] Number of missiles to deduct
    //!              
    //=========================================================================
	void MissileLauncher::DeductAmmunition ( UInt count )
	{
		if ( count > m_ammunition )
		{
			m_ammunition = 0;
		}
		else
		{
			m_ammunition -= count;
		}
	}
	//End MissileLauncher::DeductAmmunition


    //=========================================================================
    //! @function    MissileLauncher::IncreaseAmmunition
    //! @brief       Add count missiles to the ammunition store
	//!
    //! @param       count [in] Number of missiles to add
    //!              
    //=========================================================================
	void MissileLauncher::IncreaseAmmunition ( UInt count )
	{	
		m_ammunition += count;
	}
	//End MissileLauncher::IncreaseAmmunition



    //=========================================================================
    //! @function    MissileLauncher::SetReloadTime
    //! @brief       Set the length of time between reloads in seconds
    //!              During the reload period, the missile launcher will be unable to fire
    //!              
    //! @param       time [in] Length of time between reloads in seconds
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	void MissileLauncher::SetReloadTime ( Float time )
	{
		m_reloadTime = time;
	}
	//End MissileLauncher::SetReloadTime



    //=========================================================================
    //! @function    MissileLauncher::GetReloadTime
    //! @brief       Return the reload period of the missile
    //!              
    //! @return      The amount of time the missile has to wait before firing again
    //=========================================================================
	Float MissileLauncher::GetReloadTime ( ) const
	{
		return m_reloadTime;
	}
	//End MissileLauncher::GetReloadTime


    //=========================================================================
    //! @function    MissileLauncher::GetAmmunition
    //! @brief       Get the number of missiles in the launcher
    //!              
    //! @return      The number of missiles in the launcher
    //=========================================================================
	UInt MissileLauncher::GetAmmunition ( ) const
	{
		return m_ammunition;
	}
	//End MissileLauncher::GetAmmunitionCount


    //=========================================================================
    //! @function    MissileLauncher::IsEmpty
    //! @brief       Are there any missiles left?
    //!              
    //! @return      True if there are missiles in the launcher, false otherwise
    //=========================================================================
	bool MissileLauncher::IsEmpty () const
	{
		if ( GetAmmunition() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//End MissileLauncher::IsEmpty


    //=========================================================================
    //! @function    MissileLauncher::SetFlag
    //! @brief       Set one of the missile launcher flags
    //!              
    //! @param       flag [in] Flag to set
    //!              
    //=========================================================================
	void MissileLauncher::SetFlag ( EMissileLauncherFlags flag )
	{
		m_launcherFlags[flag] = true;
	}
	//End MissileLauncher::SetFlag


    //=========================================================================
    //! @function    MissileLauncher::ClearFlag
    //! @brief       Clear one of the missile launcher flags
    //!              
    //! @param       flag 
    //!             
    //=========================================================================
	void MissileLauncher::ClearFlag ( EMissileLauncherFlags flag )
	{
		m_launcherFlags[flag] = false;
	}
	//End MissileLauncher::ClearFlag



    //=========================================================================
    //! @function    MissileLauncher::IsFlagSet
    //! @brief       Indicates whether or not a flag is set
    //!              
    //! @param       flag 
    //!              
    //=========================================================================
	bool MissileLauncher::IsFlagSet ( EMissileLauncherFlags flag ) const
	{
		return m_launcherFlags[flag];
	}
	//End MissileLauncher::IsFlagSet


}
//end namespace OidFX


#endif
//#ifndef OIDFX_MISSILELAUNCHER_H

