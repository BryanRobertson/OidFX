//======================================================================================
//! @file         Restorable.h
//! @brief        IRestorable interface. Interface for objects that can be lost and restored
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 04 June 2005
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

#ifndef CORE_RESTORABLE_H
#define CORE_RESTORABLE_H


//namespace Core
namespace Core
{

	//!@class	IRestorable
	//!@brief	IRestorable interface. Interface for objects that can be lost and restored
	class IRestorable
	{
		public:

			//!@brief	Determines whether or not the object has been lost
			virtual bool RequiresRestore() const = 0;

			//!@brief	Prepare for a restore operation.
			//!			
			//!			In the case that an instance of an object doesn't require
			//!			restoration, implementations are free to ignore
			//!			this request, unless forceRestore is true.
			//!
			//!@param	forceRestore [in] Implementations of this method are free to ignore
			//!							  the PrepareForRestore request if forceRestore is false. However, if 
			//!							  forceRestore is true, then they must carry out this request
			virtual void PrepareForRestore( bool forceRestore ) = 0;
			

			//!@brief	Perform a Restore operation
			//!
			//!			In a case that an instance of an object doesn't require restoration
			//!			the object is free to ignore this request. However, if 
			//!			forceRestore is true, then the implementation must restore the object
			//!
			//!@param	forceRestore [in] Implementations of this method are free to ignore the
			//!							  Restore request if forceRestore is false. However, if 
			//!							  forceRestore is true, then the implementation MUST restore the object
			virtual void Restore( bool forceRestore ) = 0;
	};
	//end class IRestorable

};
//end namespace Core


#endif
//#ifndef CORE_RESTORABLE_H