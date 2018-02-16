//======================================================================================
//! @file         Control.h
//! @brief        Template class representing a control on a controller
//!				  which can have a controlled value bound to it               
//!
//!               
//! @author       Bryan Robertson
//! @date         Monday, 18 July 2005
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

#ifndef INPUT_CONTROL_H
#define INPUT_CONTROL_H


#include <vector>
#include "Input/ControlledValue.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Input { class InputSystem;	}



//namespace Input
namespace Input
{


	//!@class	Control
	//!@brief	Template class representing a control on a controller
	//!			which can have a controlled value bound to it    
	template <class ValueType, class IDType >
	class Control
	{
		public:

			//Friends
			friend class InputSystem;

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			Control ( IDType ID );
			~Control ();


            //=========================================================================
            // Public types
            //=========================================================================
			typedef Control<ValueType, IDType>					ControlType;
			typedef ControlledValue<ValueType, ControlType>		ControlledValueType;
			typedef std::vector<ControlledValueType*>			ControlledValueStore;


            //=========================================================================
            // Public methods
            //=========================================================================
			void RegisterControlledValue	( ControlledValueType& value );
			void UnregisterControlledValue	( ControlledValueType& value );

			IDType	  ID() const					{ return m_ID;			}
			ValueType Value() const					{ return m_value;		}

		private:

            //=========================================================================
            // Private types
            //=========================================================================
			ControlledValueStore	m_controlledValues;

            //=========================================================================
            // Private methods
            //=========================================================================
			void SetValue ( ValueType value )		{ m_value = value;	UpdateControlledValues();	}
			void UpdateControlledValues ();

            //=========================================================================
            // Private data
            //=========================================================================
			IDType		m_ID;
			ValueType	m_value;

	};
	//End class Control



	//=========================================================================
	//! @function    Control<ValueType,IDType>::Control
	//! @brief       Control constructor
	//!              
	//! @param       ID [in] ID of control
	//!              
	//=========================================================================
	template <class ValueType, class IDType >
		Control<ValueType, IDType>::Control ( IDType ID )
		: m_id(ID), m_value(ValueType())
	{
	}
	//End Control<ValueType,IDType>::Control



	//=========================================================================
	//! @function    Control<ValueType,IDType>::Control
	//! @brief       Control destructor
	//!          
	//=========================================================================
	template <class ValueType, class IDType >
		Control<ValueType, IDType>::~Control ( )
	{
		ControlledValueStore::iterator itr = m_controlledValues.begin();
		ControlledValueStore::iterator end = m_controlledValues.end();

		for ( ; itr != end; ++itr )
		{
			itr->Unbind();
		}
	}
	//End Control<ValueType,IDType>::Control



    //=========================================================================
    //! @function    Control<ValueType,IDType>::RegisterControlledValue
    //! @brief       Register a controlled value with the control.
    //!              
    //!              Once a controlled value has been registered with the control
	//!				 its value will be updated whenever the control's value changes
    //!              
    //! @param       value [in] Controlled value to register with the control
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	template <class ValueType, class IDType >
		void Control<ValueType, IDType>::RegisterControlledValue 
								( Control<ValueType, IDType>::ControlledValueType& value )
	{
		m_controlledValues.push_back(&value);
	}
	//End Control<ValueType,IDType>::RegisterControlledValue



    //=========================================================================
    //! @function    Control<ValueType,IDType>::UnregisterControlledValue
    //! @brief       Remove a controlled value from the list of values
    //!              
    //!              
    //! @param       value [in] Value to remove
    //!              
    //=========================================================================
	template <class ValueType, class IDType >
		void Control<ValueType, IDType>::UnregisterControlledValue 
								( Control<ValueType, IDType>::ControlledValueType& value )
	{
		ControlledValueStore::iterator itr = m_controlledValues.begin();
		bool found = false;

		while ( (!found) && (*itr != m_controlledValues.end()) )
		{
			if ( m_controlledValues[index] == &value )
			{
				found = true;
			}

			++itr;
		}

		debug_assert ( found, "Couldn't find controlled value!" );
		m_controlledValues.erase(itr);
		
	}
	//End Control<ValueType,IDType>::UnregisterControlledValue


    //=========================================================================
    //! @function    Control<ValueType,IDType>::UpdateControlledValues
    //! @brief       Update all controlled values with the value of this control
    //!              
    //=========================================================================
	template <class ValueType, class IDType >
		void Control<ValueType, IDType>::UpdateControlledValues ( )
	{
		ControlledValueStore::iterator itr = m_controlledValues.begin();
		ControlledValueStore::iterator end = m_controlledValues.end();

		for ( ; itr != end; ++itr )
		{
			itr->UpdateValue(m_value);
		}
	}
	//End Control<ValueType,IDType>::UpdateControlledValues

};
//end namespace Input


#endif
//#ifndef INPUT_CONTROL_H

