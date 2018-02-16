//======================================================================================
//! @file         FramerateCounter.h
//! @brief        Class that keeps track of the frame rate, updating it at set intervals
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 12 July 2005
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

#ifndef CORE_FRAMERATECOUNTER_H
#define CORE_FRAMERATECOUNTER_H


//namespace Core
namespace Core
{

	//!@class	FramerateCounter
	//!@brief	Class that keeps track of the frame rate, updating it at set intervals
	class FramerateCounter
	{
		public:

			FramerateCounter( Float updateInterval = 0.25 )
				: m_updateInterval(updateInterval), m_frameRate(0.0f), m_timeElapsed(0.0f),
				  m_updateCount(0)
			{
			}

			void  SetUpdateInterval( Float updateInterval ) throw() { m_updateInterval = updateInterval; }
			Float UpdateInterval () const throw()					{ return m_updateInterval;			 }

			Float FrameRate() const throw()							{ return m_frameRate;				 }

			inline void Update ( Float timeElapsedInSeconds );

		private:

			Float m_frameRate;
			Float m_timeElapsed;
			Float m_updateInterval;
			UInt  m_updateCount;
			
	};
	//End class FramerateCounter



    //=========================================================================
    //! @function    FramerateCounter::Update
    //! @brief       Update the frame rate counter.
	//!
	//!				 Only updates the frame rate if more
	//!				 than m_updateInterval seconds have passed.
    //!              
    //! @param       timeElapsedInSeconds [in]
    //!              
    //=========================================================================
	void FramerateCounter::Update( Float timeElapsedInSeconds )
	{
		m_timeElapsed += timeElapsedInSeconds;
		++m_updateCount;

		if ( m_timeElapsed >= m_updateInterval )
		{
			Float averageFrameTime = (m_timeElapsed / static_cast<Float>(m_updateCount));

			if ( averageFrameTime == 0.0f )
			{
				m_frameRate = 0.0;
			}
			else
			{
				//Update the frame rate
				m_frameRate = 1.0f / averageFrameTime;
				
			}

			m_timeElapsed = 0.0f;
			m_updateCount = 0;
		}


	}
	//End FramerateCounter::Update

};
//end namespace Core



#endif
//#ifndef CORE_FRAMERATECOUNTER_H
