//======================================================================================
//! @file         ConsoleCursor.h
//! @brief        Class representing the cursor on the console command line
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 21 May 2005
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

#ifndef CORE_CONSOLECURSOR_H
#define CORE_CONSOLECURSOR_H


#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/StandardExceptions.h"



//Forward declarations
namespace Core { class ConsoleCommandLine; }


//namespace Core
namespace Core
{

	//!@class	ConsoleCursor
	//!@brief	Class representing the cursor on the console command line
	class ConsoleCursor
	{
		public:

			//Constructor
			inline ConsoleCursor( const ConsoleCommandLine& commandLine );

			//Public types
			enum ECursorPosition 
			{ 
				BEGIN, 
				END 
			};

			//Accessors
			inline UInt GetPosition() const throw();
			bool IsAtEnd() const throw();

			//Mutators
			void SetPosition ( ECursorPosition pos ) throw();
			UInt SetPosition ( UInt pos ) throw(OutOfRange);
			UInt IncrementPosition( UInt increment ) throw(OutOfRange);
			UInt DecrementPosition( UInt decrement ) throw(OutOfRange);

		private:

			UInt						m_position;	//!< Index of current command line position
			const ConsoleCommandLine&   m_commandLine; //!< Reference to CommandLine object that owns this cursor

	};
	//end ConsoleCursor


	//=========================================================================
	//! @function    ConsoleCursor::ConsoleCursor
	//! @brief       ConsoleCursor constructor
	//!
	//! @param       commandLine [in] const reference to the CommandLine object
	//!								  that owns this cursor
	//!              
	//=========================================================================
	ConsoleCursor::ConsoleCursor ( const ConsoleCommandLine& commandLine )
	: m_commandLine( commandLine ), m_position(0)
	{
	}
	//end ConsoleCursor::ConsoleCursor



    //=========================================================================
    //! @function    ConsoleCursor::GetPosition
    //! @brief       Get the current position of the cursor
    //!          
    //! @return      The current position of the cursor
    //=========================================================================
	UInt ConsoleCursor::GetPosition() const
	{
		return m_position;
	}
	//end ConsoleCursor::GetPosition


};
//end namespace Core


#endif
//#ifndef CONSOLECURSOR_H
