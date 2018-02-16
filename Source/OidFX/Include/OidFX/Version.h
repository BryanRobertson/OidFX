//======================================================================================
//! @file         Version.h
//! @brief        Declares a global instance of the Versioning::Version class, g_version
//!				  used to determine the version of the application.
//!
//!				  The instance is defined in Version.cpp, which is maintained by the build script
//!               
//! @author       Bryan Robertson
//! @date         Friday, 11 February 2005
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


#ifndef OIDFX_VERSION_H
#define OIDFX_VERSION_H


namespace Versioning
{

	enum BuildType
	{
		PA,A,B,R
	};

	struct Version
	{

		Version ( UInt revision, UInt major, UInt minor, 
					UInt build, BuildType type, const Char* versionString )
		: m_revision(revision), m_major(major), m_minor(minor),m_build(build),
			m_versionString(versionString)
		{
		}

		UInt m_revision;
		UInt m_major;
		UInt m_minor;
		UInt m_build;
		const Char* m_versionString;

	};

	extern Version g_version;

};

#endif
//#ifndef OIDFX_VERSION_H