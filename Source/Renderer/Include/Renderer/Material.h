//======================================================================================
//! @file         Material.h
//! @brief        Class representing material properties
//!               
//!				  A material specifies the diffuse, ambient, specular, and emissive colours
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 29 June 2005
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

#ifndef RENDERER_MATERIAL_H
#define RENDERER_MATERIAL_H


#include "Renderer/Colour4f.h"


//namespace Renderer
namespace Renderer
{

	//!@class	Material
	//!@brief	Class representing material properties
	//!
	//!			A material specifies the diffuse, ambient, specular, and emmisive colours
	class Material
	{
		public:


            //=========================================================================
            // Constructors
            //=========================================================================
			Material ( Colour4f diffuse = Colour4f(1.0f, 1.0f, 1.0f), Colour4f ambient = Colour4f(0.0f, 0.0f, 0.0f),
					   Colour4f specular = Colour4f(1.0f, 1.0f, 1.0f), Float shininess = 1.0f, Colour4f emissive = Colour4f(0.0f, 0.0f, 0.0f) )
					   : m_diffuse(diffuse), m_ambient(ambient), m_specular(specular), m_emissive(emissive), m_shininess(shininess)
			{
				RecomputeChecksums();
			}


            //=========================================================================
            // Public methods
            //=========================================================================
			inline const Colour4f& GetAmbient() const		{ return m_ambient;     }
			inline const Colour4f& GetDiffuse() const		{ return m_diffuse;		}
			inline const Colour4f& GetSpecular() const		{ return m_specular;	}
			inline const Colour4f& GetEmissive() const		{ return m_emissive;	}
			inline const Float     GetShininess() const     { return m_shininess;   }

			inline void SetAmbient( const Colour4f& ambient )		{ m_ambient = ambient;   RecomputeAmbientChecksum(); 	}
			inline void SetDiffuse( const Colour4f& diffuse )		{ m_diffuse = diffuse;   RecomputeDiffuseChecksum();  	}
			inline void SetSpecular( const Colour4f& specular )		{ m_specular = specular; RecomputeSpecularChecksum(); 	}
			inline void SetEmissive( const Colour4f& emissive ) 	{ m_emissive = emissive; RecomputeEmissiveChecksum(); 	}
			inline void SetShininess( Float shininess ) 			{ m_shininess = shininess;  }

			inline friend bool operator < ( const Material& lhs, const Material& rhs );
			inline friend bool operator == ( const Material& lhs, const Material& rhs );
			inline friend bool operator != ( const Material& lhs, const Material& rhs );

		private:


            //=========================================================================
            // Private methods
            //=========================================================================
			void RecomputeChecksums()
			{
				RecomputeAmbientChecksum(); 
				RecomputeDiffuseChecksum(); 
				RecomputeSpecularChecksum();
				RecomputeEmissiveChecksum();
			}

			void RecomputeAmbientChecksum()  { m_ambientChecksum = Core::GenerateHash ( m_ambient );   }
			void RecomputeDiffuseChecksum()  { m_diffuseChecksum = Core::GenerateHash ( m_diffuse );   }
			void RecomputeSpecularChecksum() { m_specularChecksum = Core::GenerateHash ( m_specular ); }
			void RecomputeEmissiveChecksum() { m_emissiveChecksum = Core::GenerateHash ( m_emissive ); }

            //=========================================================================
            // Private data
            //=========================================================================

			Colour4f	m_ambient;
			Colour4f	m_diffuse;
			Colour4f	m_specular;
			Colour4f	m_emissive;
			Float		m_shininess;

			UInt m_ambientChecksum;
			UInt m_diffuseChecksum;
			UInt m_specularChecksum;
			UInt m_emissiveChecksum;

	};
	//End class Material



    //=========================================================================
    //! @function    operator < ( const Material& , const Material & )
    //! @brief       Used for render state sorting.
	//!				 Compares two materials, by comparing their checksums
	//!
    //! @param       lhs [in] 
    //! @param       rhs [in] 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	bool operator < ( const Material& lhs, const Material& rhs )
	{
		if ( lhs.m_ambientChecksum < rhs.m_ambientChecksum )
		{
			return true;
		}

		if ( lhs.m_diffuseChecksum < rhs.m_diffuseChecksum )
		{
			return true;
		}

		if ( lhs.m_specularChecksum < rhs.m_specularChecksum )
		{
			return true;
		}

		if ( lhs.m_emissiveChecksum < rhs.m_emissiveChecksum )
		{
			return true;
		}

		if ( lhs.GetShininess() < rhs.GetShininess() )
		{
			return true;
		}

		return false;
	}
	//End operator < ( const Material& , const Material & )



	//=========================================================================
    //! @function    operator == ( const Material&, const Material & )
    //! @brief       Used for render state sorting.
	//!				 Compares two materials, by comparing their checksums
    //!              
    //! @param       lhs [in] 
    //! @param       rhs [in] 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	bool operator == ( const Material& lhs, const Material& rhs )
	{

		if ( lhs.m_ambientChecksum != rhs.m_ambientChecksum )
		{
			return false;
		}

		if ( lhs.m_diffuseChecksum != rhs.m_diffuseChecksum )
		{
			return false;
		}

		if ( lhs.m_specularChecksum != rhs.m_specularChecksum )
		{
			return false;
		}

		if ( lhs.m_emissiveChecksum != rhs.m_emissiveChecksum )
		{
			return false;
		}

		if ( lhs.GetShininess() != rhs.GetShininess() )
		{
			return false;
		}

		return true;
	}
	//End operator == ( const Material& , const Material & )



	//=========================================================================
    //! @function    operator != ( const Matrial& , const Material & )
    //! @brief       Compare two materials ( for render state sorting purposes )
    //!              
    //! @param       lhs [in] 
    //! @param       rhs [in] 
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	bool operator != ( const Material& lhs, const Material& rhs )
	{
		return !(lhs == rhs);
	}
	//End operator < ( const Material& , const Material & )

};
//end namespace Renderer


#endif
//#ifndef MATERIAL_H