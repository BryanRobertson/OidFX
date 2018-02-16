//======================================================================================
//! @file         Timer.cpp
//! @brief        Class to measure the passage of time
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 19 October 2004
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

#include "Core/StandardExceptions.h"
#include "Core/Timer.h"



using namespace Core;




//=========================================================================
//! @function    Timer::Timer
//! @brief		 Timer constructor       
//! 
//! @throw		 Core::RuntimeError, if no performance counter is available
//=========================================================================
Timer::Timer ( )
: m_oldTime(0.0f), m_currentTime(0.0f), m_clockFrequency(0.0f), m_cachedTimeDelta(0.0f)
{
	LARGE_INTEGER frequency;

	BOOL result = QueryPerformanceFrequency( &frequency );

	if ( result == 0 )
	{
		throw Core::RuntimeError (  "No performance counter available!", 0, __FILE__,
									  __FUNCTION__, __LINE__ );
	}
	else
	{
		m_clockFrequency = (TimerValue)frequency.QuadPart;
	}

	m_oldTime = m_currentTime = GetTime( );
}
//end Timer::Timer