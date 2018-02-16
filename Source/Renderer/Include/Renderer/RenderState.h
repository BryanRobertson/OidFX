//======================================================================================
//! @file         RenderState.h
//! @brief        RenderState and TextureUnit classes
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


#ifndef RENDERER_RENDERSTATE_H
#define RENDERER_RENDERSTATE_H


#include <iostream>
#include <deque>
#include "Renderer/Material.h"
#include "Renderer/Colour4f.h"
#include "Renderer/RendererStateConstants.h"
#include "Renderer/TextureUnit.h"



//=========================================================================
// Forward declaration
//=========================================================================
namespace Renderer { class IRenderer; class RenderState; class TexturePrecacheList; }



//namespace Renderer
namespace Renderer
{

	//!@class	RenderState
	//!@brief	Class encapsulating the render state
	class RenderState
	{
		public:

            //=========================================================================
            // Constructors
            //=========================================================================
			RenderState();


            //=========================================================================
            // Public types
            //=========================================================================
			//Scene blend
			struct SceneBlend
			{
				EBlendMode srcBlend;
				EBlendMode destBlend;
			};

			//Fog
			struct Fog
			{
				bool		override;
				EFogMode	mode;
				Colour4f	colour;
				Float		density;
				Float		begin;
				Float		end;
			};

			typedef std::deque<TextureUnit>				TextureUnitStore;
			typedef TextureUnitStore::iterator			TextureUnitIterator;
			typedef TextureUnitStore::const_iterator	TextureUnitConstIterator;


			//=========================================================================
			// Friends
			//=========================================================================
			friend std::ostream& operator << ( std::ostream& out, const Renderer::RenderState& renderState );


            //=========================================================================
            // Public methods
            //=========================================================================
			
			void Precache ( TexturePrecacheList& precacheList );
			void UpdateTextureAnimations( Float timeElapsedInSeconds ) throw();
			
	
            //=========================================================================
            // Public mutator methods
            //=========================================================================
			
			//Material
			inline void SetMaterialSource ( EMaterialSourceType type, EMaterialSource source ) throw();
			void SetMaterial	  ( const Material& material ) throw()		{ m_material = material;				}
			void SetAmbientColour ( const Colour4f& ambient )  throw()		{ m_material.SetAmbient( ambient );		}
			void SetDiffuseColour ( const Colour4f& diffuse )  throw()		{ m_material.SetDiffuse( diffuse );		}
			void SetSpecularColour ( const Colour4f& specular )  throw()	{ m_material.SetSpecular( specular );	}
			void SetEmissiveColour ( const Colour4f& emissive )  throw()	{ m_material.SetEmissive( emissive );	}
			void SetShininess ( Float shininess )  throw()					{ m_material.SetShininess( shininess );	}

			//Blending
			inline void SetBlending   ( bool blending ) throw()					{ m_blendEnable = true;		}
			inline void SetBlendOp	  ( EBlendOp op   ) throw()					{ m_blendOp = op;			}
			inline void SetSceneBlend ( EBlendMode srcBlend, EBlendMode dstBlend ) throw(); 

			//Depth testing
			void SetDepthTest  ( bool depthTest )	 throw() { m_depthTest = depthTest;	 }
			void SetDepthWrite ( bool depthWrite )  throw() { m_depthWrite = depthWrite; }
			void SetDepthFunc  ( ECmpFunc func )	 throw() { m_depthFunc = func;	 }
			void SetDepthBias	( Float depthBias )  throw() { m_depthBias = depthBias;	 }

			//Alpha testing
			void SetAlphaTest ( bool alphaTest )  throw()	{ m_alphaTest = alphaTest;	 }
			void SetAlphaFunc ( ECmpFunc func )  throw()	{ m_alphaFunc = func;		 }
			void SetAlphaReference ( Float ref ) throw()	{ m_alphaRef = ref;			 }

			//Stencil testing
			void SetStencilTest ( bool stencilTest ) throw()		{ m_stencilTest = stencilTest; }
			void SetStencilRef  ( UInt stencilRef ) throw()			{ m_stencilRef = stencilRef;   }
			void SetStencilMask ( UInt stencilMask ) throw()		{ m_stencilMask = stencilMask; }
			void SetStencilWriteMask ( UInt writeMask ) throw()		{ m_stencilWriteMask = writeMask; }
			void SetStencilFunc ( ECmpFunc stencilFunc ) throw()	{ m_stencilFunc = stencilFunc; }
			void SetStencilPass ( EStencilOp stencilPass ) throw()	{ m_stencilPass = stencilPass; }
			void SetStencilFail ( EStencilOp stencilFail ) throw()	{ m_stencilFail = stencilFail; }
			void SetStencilZFail ( EStencilOp stencilZFail ) throw() { m_stencilZFail = stencilZFail; }

			//Culling mode
			void SetCullMode  ( ECullMode mode )  throw()	{ m_culling = mode;		 }

			//Lighting
			void SetLighting  ( bool lighting )  throw()	{ m_lighting = lighting;		}
			void SetMaxLights ( UInt maxLights )  throw()	{ m_maxLights = maxLights;		}

			//Shading
			void SetShadeMode ( EShadeMode shadingMode )  throw()	{ m_shadingMode = shadingMode;	 }

			//Fog
			inline void SetFog ( bool fogOverride, EFogMode mode, const Colour4f& colour, Float density, Float begin, Float end )  throw();

			void SetFogOverride ( bool fogOverride )			{ m_fog.override = fogOverride;		}
			void SetFogMode		( EFogMode mode    )			{ m_fog.mode = mode;				}
			void SetFogColour	( const Colour4f& colour  )		{ m_fog.colour = colour;			}
			void SetFogDensity  ( Float density )				{ m_fog.density = density;			}
			void SetFogBegin	( Float begin   )				{ m_fog.begin = begin;				}
			void SetFogEnd		( Float end		)				{ m_fog.end = end;					}

			//Colour write
			void SetColourWrite ( bool colourWrite ) throw()		{ m_colourWrite = colourWrite; } 

			//Misc
			void SetNormaliseNormals    ( bool normaliseNormals ) throw() { m_normaliseNormals = normaliseNormals; }
			void SetSpecularHighlights	( bool specular ) throw()		   { m_specular = specular; }


			//Texture units
			inline void AddTextureUnit ( const TextureUnit& textureUnit )  throw();


            //=========================================================================
            // Public accessors methods
            //=========================================================================

			//Material
			inline EMaterialSource	GetMaterialSource ( EMaterialSourceType type ) const throw();
			
			const Material&	GetMaterial () const throw()		{ return m_material;				}
			const Colour4f& AmbientColour () const throw()		{ return m_material.GetAmbient();   }
			const Colour4f& DiffuseColour () const throw()		{ return m_material.GetDiffuse();   }
			const Colour4f& SpecularColour () const throw()		{ return m_material.GetSpecular();	}
			const Colour4f& EmissiveColour () const throw()		{ return m_material.GetEmissive();	}
			Float Shininess ( ) const throw()					{ return m_material.GetShininess();	}

			//Blending
			bool	   Blending () const throw()		{ return m_blendEnable;			 }
			EBlendOp   BlendOp()   const throw()		{ return m_blendOp;				 }
			EBlendMode SourceBlend () const throw()		{ return m_sceneBlend.srcBlend;  }
			EBlendMode DestBlend () const throw()		{ return m_sceneBlend.destBlend; }

			//Depth testing
			bool	 DepthTest  () const throw()			{ return m_depthTest;	 }
			bool	 DepthWrite () const throw()			{ return m_depthWrite;	 }
			ECmpFunc DepthFunc  () const throw()			{ return m_depthFunc;	 }
			Float	 DepthBias	() const throw()			{ return m_depthBias;	 }

			//Alpha testing
			bool	 AlphaTest () const throw()				{ return m_alphaTest;	 }
			ECmpFunc AlphaFunc  () const throw()			{ return m_alphaFunc;	 }
			Float	 AlphaReference() const throw()			{ return m_alphaRef;	 }

			//Stencil testing
			bool		StencilTest() const throw()			{ return m_stencilTest;	 }
			UInt		StencilRef() const throw()			{ return m_stencilRef;	 }
			UInt		StencilMask() const throw()			{ return m_stencilMask;	 }
			UInt		StencilWriteMask() const throw()	{ return m_stencilWriteMask; }
			ECmpFunc	StencilFunc() const throw()			{ return m_stencilFunc;	 }
			EStencilOp	StencilPass() const throw()			{ return m_stencilPass;	 }
			EStencilOp	StencilFail() const throw()			{ return m_stencilFail;	 }
			EStencilOp	StencilZFail() const throw()		{ return m_stencilZFail; }	

			//Culling mode
			ECullMode CullMode () const throw()				{ return m_culling;	 }

			//Lighting
			bool Lighting  () const throw()					{ return m_lighting;	 }
			UInt MaxLights () const throw()					{ return m_maxLights;	 }

			//Shading
			EShadeMode ShadeMode () const throw()			{ return m_shadingMode; }

			//Fog
			bool			 FogOverride() const throw()		{ return m_fog.override; }
			EFogMode		 FogMode() const throw()			{ return m_fog.mode;	 }
			const Colour4f&  FogColour() const throw()			{ return m_fog.colour;	 }
			Float			 FogDensity() const throw()			{ return m_fog.density;	 }
			Float			 FogBegin() const throw()			{ return m_fog.begin;	 }
			Float			 FogEnd() const throw()				{ return m_fog.end;		 }
				
			//Colour write
			bool ColourWrite ( ) const throw()						{ return m_colourWrite; } 

			//Misc
			bool NormaliseNormals() const throw()					{ return m_normaliseNormals; }
			bool SpecularHighlights() const throw()					{ return m_specular;		 }

			//Texture units
			inline const TextureUnit& TextureUnits ( UInt index ) const throw();
			
			//Texture unit iteration
			inline UInt TextureUnitCount () const throw()	{ return m_textureUnits.size(); }
			
			inline TextureUnitIterator TextureUnitsBegin()				{ return m_textureUnits.begin(); }
			inline TextureUnitIterator TextureUnitsEnd()				{ return m_textureUnits.end();	 }
			inline TextureUnitConstIterator TextureUnitsBegin() const	{ return m_textureUnits.begin(); }
			inline TextureUnitConstIterator TextureUnitsEnd() const		{ return m_textureUnits.end();   }

		private:

			
            //=========================================================================
            // Private data
            //=========================================================================
			
			//Material colours
			Material			m_material;
			EMaterialSource		m_ambientMaterialSource;
			EMaterialSource		m_diffuseMaterialSource;
			EMaterialSource		m_specularMaterialSource;
			EMaterialSource		m_emissiveMaterialSource;

			//Blending
			bool		m_blendEnable;
			EBlendOp	m_blendOp;
			SceneBlend	m_sceneBlend;

			//Depth test
			bool		m_depthTest;
			bool		m_depthWrite;
			ECmpFunc	m_depthFunc;
			Float		m_depthBias;

			//Alpha test
			bool		m_alphaTest;
			ECmpFunc	m_alphaFunc;
			Float		m_alphaRef;

			//Stencil test
			bool		m_stencilTest;
			ECmpFunc	m_stencilFunc;
			EStencilOp	m_stencilPass;
			EStencilOp	m_stencilFail;
			EStencilOp  m_stencilZFail;
			UInt		m_stencilRef;
			UInt		m_stencilMask;
			UInt		m_stencilWriteMask;

			//Culling
			ECullMode	m_culling;

			//Lighting
			bool		m_lighting;

			//Shading
			EShadeMode	m_shadingMode;

			//Fog
			Fog			m_fog;

			//Colour write
			bool		m_colourWrite;

			//Max lights
			UInt		m_maxLights;

			//Misc
			bool		m_normaliseNormals;
			bool		m_specular;
						
			//Texture units
			TextureUnitStore	 m_textureUnits;

	};
	//End class RenderState



    //=========================================================================
    //! @function    RenderState::GetMaterialSource
    //! @brief       Get one of the material sources
	//!
	//!				 The material source specifies where the colours come from for
	//!				 the different colour types.
	//!				 For each colour type, ambient, diffuse, specular, or emissive,
	//!				 it sets whether the colour is sourced from the relevant material colour
	//!				 or from the vertex diffuse colour
    //!              
    //! @param       type [in] Type of material source
    //!              
    //! @return      THe material source for the material source type
    //! @throw       
    //=========================================================================
	EMaterialSource RenderState::GetMaterialSource ( EMaterialSourceType type ) const
	{

		switch ( type )
		{
			case STATE_AMBIENT_MATERIAL_SOURCE:
				return m_ambientMaterialSource; 

			case STATE_DIFFUSE_MATERIAL_SOURCE:
				return m_diffuseMaterialSource;

			case STATE_SPECULAR_MATERIAL_SOURCE:
				return m_specularMaterialSource;

			case STATE_EMISSIVE_MATERIAL_SOURCE:
				return m_emissiveMaterialSource;

			default:
				debug_assert(false, "Invalid material source type!" );
		}

	}
	//End RenderState::GetMaterialSource



    //=========================================================================
    //! @function    RenderState::SetMaterialSource
    //! @brief		 Set one of the material sources      
    //!
	//!				 The material source specifies where the colours come from for
	//!				 the different colour types.
	//!				 For each colour type, ambient, diffuse, specular, or emissive,
	//!				 it sets whether the colour is sourced from the relevant material colour
	//!				 or from the vertex diffuse colour
    //!              
	//!              
    //! @param       type	[in] STATE_AMBIENT_MATERIAL_SOURCE	
	//!							 STATE_DIFFUSE_MATERIAL_SOURCE
	//!							 STATE_SPECULAR_MATERIAL_SOURCE
	//!							 STATE_EMISSIVE_MATERIAL_SOURCE
	//!
    //! @param       source [in] MATERIALSOURCE_MATERIALCOLOUR - Source from the relevant material colour
	//!							 MATERIALSOURCE_COLOUR1		   - Source from the vertex diffuse colour
    //!              
    //=========================================================================
	void RenderState::SetMaterialSource ( EMaterialSourceType type, EMaterialSource source )
	{

		switch ( type )
		{
			case STATE_AMBIENT_MATERIAL_SOURCE:
				m_ambientMaterialSource = source;
				break;

			case STATE_DIFFUSE_MATERIAL_SOURCE:
				m_diffuseMaterialSource = source;
				break;

			case STATE_SPECULAR_MATERIAL_SOURCE:
				m_specularMaterialSource = source;
				break;

			case STATE_EMISSIVE_MATERIAL_SOURCE:
				m_emissiveMaterialSource = source;
				break;
		}

	}
	//End RenderState::SetMaterialSource




    //=========================================================================
    //! @function    RenderState::SetSceneBlend
    //! @brief       Set the scene blend
    //!              
    //! @param       srcBlend [in] Source blend mode
    //! @param       dstBlend [in] Destination blend mode
    //!              
    //=========================================================================
	void RenderState::SetSceneBlend ( EBlendMode srcBlend, EBlendMode dstBlend )
	{
		m_sceneBlend.srcBlend = srcBlend;
		m_sceneBlend.destBlend = dstBlend;
	}
	//End RenderState::SceneBlend



    //=========================================================================
    //! @function    RenderState::SetFog
    //! @brief       Set the fog mode
    //!              
    //! @param       fogOverride [in] Should the global fog mode be overriden?
    //! @param       mode		 [in] Mode of fog
    //! @param       colour		 [in] Colour of fog
    //! @param       density	 [in] Density of fog
    //! @param       begin		 [in] Start distance
    //! @param       end		 [in] End distance
    //!              
    //=========================================================================
	void RenderState::SetFog ( bool fogOverride, EFogMode mode, const Colour4f& colour, Float density, Float begin, Float end )
	{
		m_fog.override = fogOverride;
		m_fog.mode = mode;
		m_fog.colour = colour;
		m_fog.density = density;
		m_fog.begin = begin;
		m_fog.end = end;
	}
	//End RenderState::Fog


    //=========================================================================
    //! @function    RenderState::AddTextureUnit
    //! @brief       Add a texture unit to the list of texture units
    //!              
    //! @param       textureUnit [in] Texture unit to add
    //!              
    //=========================================================================
	void RenderState::AddTextureUnit ( const Renderer::TextureUnit& textureUnit )
	{
		m_textureUnits.push_back( textureUnit );
	}
	//End RenderState::AddTextureUnit



    //=========================================================================
    //! @function    RenderState::TextureUnits
    //! @brief       Return the texture unit at index
    //!              
    //! @param       index [in] Index into the texture units
    //!              
    //! @return      The texture unit at index
    //=========================================================================
	const TextureUnit& RenderState::TextureUnits ( UInt index ) const
	{
		debug_assert(index < TextureUnitCount(), "index out of range!" );

		return m_textureUnits[index];
	}
	//End RenderState::GetTextureUnit


};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERSTATE_H
