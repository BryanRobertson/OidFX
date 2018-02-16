//======================================================================================
//! @file         Main.cpp
//! @brief        Main application for terrain demo
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 30 May 2005
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


#include "Core/Core.h"
#include "TerrainDemo/TerrainDemoApplication.h"


//=========================================================================
//! @function    GameMain
//! @brief       Main game program
//!				 This is the main game function, which is run regardless
//!				 of whether the program is compiled as a console application
//!				 or as a windows application
//!
//! @param       commandLineStrings		array of string tokens from the 
//!										command line
//!              
//! @return      
//=========================================================================
int GameMain ( std::vector<std::string>& commandLineStrings )
{
	boost::shared_ptr<OidFX::GameApplication> game(new TerrainDemo::TerrainDemoApplication());

	return game->Run ( commandLineStrings, "Terrain Demo", "TerrainDemo log.txt" );	
}
//end GameMain


//=========================================================================
//! @function    main
//! @brief       Main program for console application, simply calls
//!				 GameMain
//!
//! @return      result of GameMain       
//=========================================================================
int main ( int argc, char* argv[] )
{
	int result = 0;
	std::vector<std::string> commandLineStrings;

	for ( int i=0; i<argc; ++i )
	{
		commandLineStrings.push_back ( argv[i] );
	}

	result = GameMain ( commandLineStrings );
	//system ( "pause" );

	return result;
}
//end main


//=========================================================================
//! @function    WinMain
//! @brief       Main program for windows application, simply calls 
//!				 GameMain
//!
//! @return      return value of GameMain       
//=========================================================================
INT WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nShowCmd )
{
	std::vector<std::string> commandLineStrings;
	Core::TokeniseCommandLine ( lpCmdLine, commandLineStrings );

	return GameMain ( commandLineStrings );
}
//end WinMain