//======================================================================================
//! @file         Effect.h
//! @brief        Effect class
//!               
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


#ifndef RENDERER_RENDEREREFFECT_H
#define RENDERER_RENDEREREFFECT_H


#include <limits>
#include <vector>
#include "Core/Resource.h"
#include "Core/Handle.h"
#include "Renderer/Technique.h"


//namespace Renderer
namespace Renderer
{

    //=========================================================================
    // Forward declarations
    //=========================================================================
	class Technique;
	class IRenderer;
	class TexturePrecacheList;


	//!@class	Effect
	//!@brief	Effect class
	//!
	//!			Represents a series of techniques for rendering an object
	//!			Each technique contains a series of passes, containing render states
	//!			Effects are parsed from .ofx text files
	class Effect : public Core::Resource 
	{
		public:

            //=========================================================================
            // Constructor
            //=========================================================================
			Effect ( const Char* fileName );


			//=========================================================================
            // Public types
            //=========================================================================
			typedef std::vector<Technique>				TechniqueStore;
			typedef TechniqueStore::iterator			iterator;
			typedef TechniqueStore::const_iterator		const_iterator;


            //=========================================================================
            // Public methods
            //=========================================================================

			//Add Technique
			inline UInt AddTechnique ( const Technique& technique );
			
			//Get Technique
			inline const Technique& Techniques ( UInt index ) const;

			//Precache
			void Precache ( TexturePrecacheList& precacheList );

			//Update
			void Update( Float timeElapsedInSeconds );

			//Get the best technique index for a specific LOD level
			inline UInt GetBestTechniqueForLOD ( UInt lod );

			//Technique Count		
			inline UInt TechniqueCount() const	{ return m_techniques.size(); }
			
			//Iterators
			inline iterator			TechniquesBegin()		  { return m_techniques.begin(); }
			inline iterator			TechniquesEnd()			  { return m_techniques.end();	 }
			inline const_iterator	TechniquesBegin() const	  { return m_techniques.begin(); }
			inline const_iterator	TechnquesEnd() const	  { return m_techniques.end();	 }

			//Core::Resource
			void Unload() {}

		private:


            //=========================================================================
            // Private data
            //=========================================================================
			TechniqueStore	m_techniques;
	

	};
	//End class Effect


    //=========================================================================
    // Typedefs
    //=========================================================================
	typedef Core::Handle<Effect>	HEffect;


    //=========================================================================
    //! @function    Effect::AddTechnique
    //! @brief       Add a technique to the effect's list of techniques
    //!              
    //! @param       technique [in]	Technique to add
    //!              
    //! @return      The index of the technique that was just added
    //=========================================================================
	UInt Effect::AddTechnique ( const Technique& technique )
	{
		m_techniques.push_back(technique);

		return TechniqueCount() - 1;
	}
	//End Effect::AddTechnique



    //=========================================================================
    //! @function    Effect::Techniques
    //! @brief       Get the technique at index
	//!				 index must be a valid index into the techniques array
    //!              
    //! @param       index [in] Index into the techniques
    //!              
    //! @return      The technique at index
    //=========================================================================
	const Technique& Effect::Techniques( UInt index ) const
	{
		debug_assert ( index < TechniqueCount(), "Error, index out of range!" );

		return m_techniques[index];
	}
	//End Effect::Techniques



    //=========================================================================
    //! @function    Effect::GetBestTechniqueForLOD
    //! @brief       Get the technique with the closest LOD level
    //!              
    //!              
    //! @param       lod [in] Level of detail to get technique for
    //!              
    //! @return      The index of the technique that is the best match for the LOD level
	//!				 passed in
    //! @throw       
    //=========================================================================
	UInt Effect::GetBestTechniqueForLOD ( UInt lod )
	{
		//If there is only one technique, then there can only be one effect index
		if ( TechniqueCount() < 2 )
		{
			return 0;
		}

		//Undefine any max macro that might stop max from working :rolleyes:
		#ifdef max
		#undef max
		#endif

		//Keep track of which LOD has the smallest difference from lod
		UInt minDifference = std::numeric_limits<UInt>::max();
		UInt index = 0;
		UInt currentIndex = 0;

		for ( const_iterator itr = TechniquesBegin(); itr != TechniquesEnd(); ++itr, ++currentIndex )
		{
			UInt currentDifference = lod - itr->LODLevel();

			//If the difference is zero, just return, we've found a perfect match
			if ( itr->LODLevel() == lod )
			{
				return currentIndex;
			}
			
			//Otherwise, get the closest match, by storing the LOD with the smallest difference
			if ( currentDifference < minDifference )
			{
				minDifference = currentDifference;
				index = currentIndex;
			}
		}

		return index;

	}
	//End Effect::GetBestTechniqueForLOD


};
//end namespace Renderer


#endif
//#ifndef RENDEREREFFECT_H