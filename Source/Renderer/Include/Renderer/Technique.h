//======================================================================================
//! @file         Technique.h
//! @brief        Class representing a single technique in an effect
//!               
//!               
//! @author       Bryan Robertson
//! @date         Friday, 24 June 2005
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


#ifndef RENDERER_TECHNIQUE_H
#define RENDERER_TECHNIQUE_H


#include <vector>
#include "Renderer/Pass.h"
#include "Renderer/RendererStateConstants.h"


//namespace Renderer
namespace Renderer
{

	//=========================================================================
    // Forward declaration
    //=========================================================================
	class IRenderer;
	class TexturePrecacheList;


	//!@class	Technique
	//!@brief	Class representing a single technique in an effect
	//!
	//!			A technique represents a method for rendering an object.
	//!			An effect file may contain many techniques, allowing a single effect file to support a wide range of hardware.
	//!
	//!			A technique consists of an arbitrary number of "passes" each with their own render state
	class Technique
	{
		public:
			

            //=========================================================================
            // Constructors/Destructors
            //=========================================================================
			Technique( UInt lodLevel = 0, bool receiveShadows = true, bool castShadows = true  );
			

			//=========================================================================
            // Public types
            //=========================================================================
			typedef std::vector<Pass>			PassStore;
			typedef PassStore::iterator			iterator;
			typedef PassStore::const_iterator	const_iterator;

            //=========================================================================
            // Public methods
            //=========================================================================

			//Precache
			void Precache ( TexturePrecacheList& precacheList );

			//Update
			void Update ( Float timeElapsedInSeconds );	

			//Get attributes
			UInt LODLevel () const				{ return m_lodLevel;		}
			bool ReceiveShadows () const		{ return m_receiveShadows;	}
			bool CastShadows () const			{ return m_castShadows;		}
			ESortValue SortValue() const		{ return m_sortValue;		}

			//Set attributes
			void LODLevel ( UInt lodLevel )				{ m_lodLevel = lodLevel;				}
			void ReceiveShadows ( bool receiveShadows ) { m_receiveShadows = receiveShadows;	}
			void CastShadows ( bool castShadows )		{ m_castShadows = castShadows;			}
			void SortValue ( ESortValue sortValue )		{ m_sortValue = sortValue;				}
			
			//Get pass
			inline const Pass& Passes ( UInt index ) const;

			//Add pass
			inline void AddPass ( const Pass& pass )	{ m_passes.push_back(pass);	}

			//Pass count
			inline UInt PassCount () const				{ return m_passes.size();	}

			//Iterators
			inline iterator			PassesBegin()		{ return m_passes.begin();	}
			inline iterator			PassesEnd()			{ return m_passes.end();	}
			inline const_iterator	PassesBegin() const { return m_passes.begin();	}
			inline const_iterator	PassesEnd()	  const	{ return m_passes.end();	}

		private:
			
			
            //=========================================================================
            // Private data
            //=========================================================================
			
			ESortValue	m_sortValue;
			UInt		m_lodLevel;
			bool		m_receiveShadows;
			bool		m_castShadows;
			
			PassStore m_passes;

	};
	//End class Technique




    //=========================================================================
    //! @function    Technique::Passes
    //! @brief       Returns the pass referenced by index
    //!              
    //! @param       index [in] Zero based pass index. Must be a valid pass index
    //!              
    //! @return      The pass referenced by index
    //=========================================================================
	const Pass& Technique::Passes ( UInt index ) const
	{
		debug_assert ( index < PassCount(), "Pass index invalid!" );

		return m_passes[index];
	}
	//End Technique::Passes


	

};
//end namespace Renderer


#endif
//#ifndef RENDERER_TECHNIQUE_H
