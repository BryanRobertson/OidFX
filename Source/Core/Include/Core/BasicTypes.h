//======================================================================================
//! @file         BasicTypes.h
//! @brief        Definitions for the basic types used in applications.
//!               
//!
//! @author       Bryan Robertson
//! @date         Saturday, 16 October 2004
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
 

#ifndef CORE_BASICTYPES_H
#define CORE_BASICTYPES_H

  #ifdef _MSC_VER

      typedef char Char;
      typedef unsigned char UChar;

      typedef short WChar;
      typedef unsigned short UWChar;

      typedef short Short;
      typedef unsigned short UShort;

      typedef int Int;
      typedef unsigned int UInt;

      typedef long Long;
      typedef unsigned long ULong;

      typedef __int8 Int8;
      typedef unsigned __int8 UInt8;

	  typedef UChar	 Byte;
	  typedef UShort Word;
	  typedef UInt	 DWord;

      typedef __int16	Int16;
      typedef unsigned __int16 UInt16;

      typedef __int32	Int32;
      typedef unsigned __int32 UInt32;

      typedef __int64 Int64;
      typedef unsigned __int64 UInt64;

	  typedef float	 Float;
	  typedef double Double;

  #endif //#ifdef MSC_VER


  #ifdef _arch_dreamcast

	  typedef unsigned char Byte;

      typedef char Char;
      typedef unsigned char UChar;

      typedef short WChar;
      typedef unsigned short UWChar;

      typedef short Short;
      typedef unsigned short UShort;

      typedef int Int;
      typedef unsigned int UInt;

      typedef long Long;
      typedef unsigned long ULong;

      typedef int8 Int8;
      typedef uint8 UInt8;

	  typedef UChar	 Byte;
	  typedef UShort Word;
	  typedef UInt	 DWord;

      typedef int16   Int16;
      typedef uint16 UInt16;

      typedef int32   Int32;
      typedef uint32 UInt32;

      typedef int64   Int64;
      typedef uint64 UInt64;

	  typedef float	 Float;
	  typedef double Double;

  #endif //#ifdef arch_dreamcast


#endif //CORE_BASICTYPES_H

 