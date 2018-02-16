//======================================================================================
//! @file         Debug.h
//! @brief        Core library debug services
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 20 May 2005
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

#ifndef CORE_DEBUGSERVICES_H
#define CORE_DEBUGSERVICES_H


namespace Core
{

//Undefine the assert commands we will be replacing
#ifdef assert
#undef assert
#endif

#ifdef verify
#undef verify
#endif

//Result for the DisplayAssertError function
enum ERROR_RESULT
{
	_ERROR_IGNORE,
	_ERROR_ABORT,
	_ERROR_RETRY
};


//DisplayUnimplementedMessage
void DisplayUnimplementedMessage ( const Char* function, const Char* sourceFile, UInt line );

//DisplayErrorMessage
void DisplayError ( const Char* message, const Char* title );

//DisplayAssertError
ERROR_RESULT DisplayAssertError ( const Char* condition, const Char* outputMessage,
								  const Char* function, const Char* sourceFile, UInt line); 



//Make it less of a pain to throw our exception types
/*
#define throw_exception( ExceptionType, errorMessage, errorCode ) \
		throw ExceptionType ( errorMessage, errorCode, __FILE__, __FUNCTION__, __LINE__ )
*/

//Allows asserts in non debug builds if this is defined
#ifdef CORE_ASSERTS

//debug_assert
#define debug_assert( condition, outputMessage ) \
		{\
		static bool _ignoreAlways = false;\
		if ( !_ignoreAlways )\
		{\
			if ( !(condition) )\
			{\
				Core::ERROR_RESULT _result = Core::DisplayAssertError ( #condition, outputMessage, __FUNCTION__, __FILE__, __LINE__ );\
				if ( _result == Core::_ERROR_IGNORE)\
				{\
					_ignoreAlways = true;\
				}\
				else if( _result == Core::_ERROR_RETRY)\
				{\
					__asm{int 3};\
				}\
				else if ( _result == Core::_ERROR_ABORT)\
				{\
					abort();\
				}\
			}\
		}\
		}\

//Debug error, an assert that always appears
#define debug_error( outputMessage ) \
	{\
		static bool _ignoreAlways = false;\
		if ( !_ignoreAlways )\
		{\
			{\
				Core::ERROR_RESULT _result = Core::DisplayAssertError ( "", outputMessage, __FUNCTION__, __FILE__, __LINE__ );\
				if ( _result == Core::_ERROR_IGNORE)\
				{\
					_ignoreAlways = true;\
				}\
				else if( _result == Core::_ERROR_RETRY)\
				{\
					__asm{int 3};\
				}\
				else if ( _result == Core::_ERROR_ABORT)\
				{\
					abort();\
				}\
			}\
		}\
		}\


#define assert( condition ) debug_assert(condition, 0)
#define verify( condition ) debug_assert(condition, 0)

//Define a macro that allows us to flag stubbed functions that haven't been implemented yet
#define not_implemented_yet \
	Core::DisplayUnimplementedMessage( __FUNCTION__, __FILE__, __LINE__ );\
	__asm{ int 3 }\

#else

//Define a macro that allows us to flag stubbed functions that haven't been implemented yet
#define not_implemented_yet		Core::DisplayUnimplementedMessage( __FUNCTION__, __FILE__, __LINE__ )

#define debug_error( outputMessage )
#define debug_assert( condition, outputMessage )
#define assert( condition )
#define verify( condition ) condition

#endif
//#ifdef CORE_ASSERTS

};
//end namespace Core

#endif
//#ifndef CORE_DEBUGSERVICES_H
