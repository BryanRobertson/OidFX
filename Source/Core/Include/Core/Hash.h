//======================================================================================
//! @file         Hash.h
//! @brief        Classes and functions for hashing up objects
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 28 September 2004
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

#ifndef CORE_HASH_H
#define CORE_HASH_H


#include <boost/cstdint.hpp>  // for boost::uint16_t
#include <boost/crc.hpp>      // for boost::crc_basic, boost::crc_optimal
#include <cstring>
#include "Core/StandardExceptions.h"
#include "Core/BasicTypes.h"
#include "Core/Debug.h"


//namespace Core
namespace Core
{
	
	//! Generates a hash code for an object
	template<class T>
		inline UInt GenerateHash ( const T& objectToHash )
		{
			boost::crc_32_type crcCheck;
			crcCheck.process_bytes ( reinterpret_cast<void const*> ( &objectToHash ),
										sizeof ( objectToHash ) );


			return crcCheck.checksum ();				
		}

	//! Generates a hash code for an array of objects
	template<class T>
		inline UInt GenerateHash ( const T& objectToHash, UInt count )
		{
			boost::crc_32_type crcCheck;
			crcCheck.process_bytes ( reinterpret_cast<void const*> ( &objectToHash ),
										sizeof(objectToHash) * count );

			return crcCheck.checksum ();
		}

	//! Generates a hash code for a string
	template<>
		inline UInt GenerateHash <std::string> ( const std::string& stringToHash )
		{
			boost::crc_32_type crcCheck;

			if ( stringToHash.length() == 0 )
			{
				throw InvalidArgument ( "objectToHash.length() == 0", 0,__FILE__, __FUNCTION__, __LINE__  );
			}

			crcCheck.process_bytes ( reinterpret_cast<void const*> ( stringToHash.c_str() ),
										stringToHash.length() );

			return crcCheck.checksum ();
		}


	//! Generate a hash code from a string
	inline UInt GenerateHashFromString ( const Char* stringToHash )
	{
		boost::crc_32_type crcCheck;
		crcCheck.process_bytes ( reinterpret_cast<void const*> ( stringToHash ),
										strlen( stringToHash )  );

		return crcCheck.checksum ();				
	}

};
//end namespace Core

#endif //#ifndef CORE_HASH_H