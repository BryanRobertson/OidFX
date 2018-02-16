//======================================================================================
//! @file         VertexDeclarationDescriptor.h
//! @brief        Class describing the elements making up a VertexDeclaration
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 28 July 2005
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

#ifndef RENDERER_VERTEXDECLARATIONDESCRIPTOR_H
#define RENDERER_VERTEXDECLARATIONDESCRIPTOR_H


#include "Renderer/VertexElement.h"


//namespace Renderer
namespace Renderer
{



	//!@class	VertexDeclarationDescriptor
	//!@brief	Class describing the elements making up a VertexDeclaration
	//!
	//!			Used in the construction off a VertexDeclaration
	class VertexDeclarationDescriptor
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			inline VertexDeclarationDescriptor();


			//=========================================================================
            // Public types
            //=========================================================================
			//! Warning, ComputeChecksum will break if you change this to a container that does not
			//! store its elements contiguously in memory
			typedef std::vector<VertexElement> ElementStore; 

			typedef ElementStore::iterator			iterator;
			typedef ElementStore::const_iterator	const_iterator;

	
            //=========================================================================
            // Public methods
            //=========================================================================

			//! Add an element
			inline void AddElement ( UInt streamIndex, size_t offset, EElementType type, EElementUsage usage, 
							  UInt usageIndex, UInt method = 0 );

			//Get the checksum
			inline UInt Checksum();

			//Iterator methods
			iterator		Begin()			{ return m_elements.begin();	}
			iterator		End()			{ return m_elements.end();		}
			const_iterator	Begin() const	{ return m_elements.begin();	}
			const_iterator	End() const		{ return m_elements.end();		}


		protected:

            //=========================================================================
            // Private methods
            //=========================================================================
			inline void ComputeChecksum();

            //=========================================================================
            // Private data
            //=========================================================================
			UInt		  m_checksum;			//!< Provides a fast method of comparing two VertexDeclarations
			bool		  m_checksumOutOfDate;	//!< Indicates whether or not the check sum needs to be recalculated

			ElementStore  m_elements;		   //!< Array of elements
			bool		  m_compileRequired; //!< Indicates whether the declaration needs to be compiled

	};
	//end class VertexDeclaration



    //=========================================================================
    //! @function    VertexDeclarationDescriptor::VertexDeclarationDescriptor
    //! @brief       VertexDeclaration constructor
    //!              
    //=========================================================================
	VertexDeclarationDescriptor::VertexDeclarationDescriptor()
		: m_checksum(0), m_checksumOutOfDate(true)
	{
	}
	//End VertexDeclaration::VertexDeclaration



    //=========================================================================
    //! @function    VertexDeclarationDescriptor::AddElement
    //! @brief       Add an element to the vertex declaration
    //!              
    //! @param       streamIndex [in] 
    //! @param       offset		 [in] 
    //! @param       type		 [in] 
    //! @param       usage		 [in] 
    //! @param       usageIndex	 [in] 
    //! @param       method		 [in] 
    //!     
    //=========================================================================
	void VertexDeclarationDescriptor::AddElement ( UInt streamIndex, 
										 size_t offset, 
										 EElementType type, 
										 EElementUsage usage, 
										 UInt usageIndex, 
										 UInt method )
	{
		m_elements.push_back ( VertexElement(streamIndex, offset, type, usage, usageIndex, method) );
		m_checksumOutOfDate = true;
	}
	//End VertexDeclaration::AddElement


    //=========================================================================
    //! @function    VertexDeclarationDescriptor::Checksum
    //! @brief       Return the checksum
    //!              
    //=========================================================================
	UInt VertexDeclarationDescriptor::Checksum ( )
	{
		if ( m_checksumOutOfDate )
		{
			ComputeChecksum();
		}

		return m_checksum;
	}
	//End VertexDeclarationDescriptor::Checksum



    //=========================================================================
    //! @function    VertexDeclarationDescriptor::ComputeChecksum
    //! @brief       Computes a checksum for the vertex declaration, from its elements
    //!              
    //!              
    //=========================================================================
	void VertexDeclarationDescriptor::ComputeChecksum()
	{
		m_checksum = Core::GenerateHash<VertexElement>( m_elements[0], m_elements.size() );
		m_checksumOutOfDate = false;
	}
	//End VertexDeclarationDescriptor::ComputeChecksum

}
//end namespace Renderer



#endif
//#ifndef RENDERER_VERTEXDECLARATIONDESCRIPTOR