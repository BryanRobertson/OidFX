//======================================================================================
//! @file         RendererStateConstants.h
//! @brief        Constant identifiers for render states, used to identify render
//!				  states when getting/setting them
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 06 June 2005
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

#ifndef RENDERER_RENDERERSTATECONSTANTS_H
#define RENDERER_RENDERERSTATECONSTANTS_H


//namespace Renderer
namespace Renderer
{

    //! IDs for render states with boolean values
	enum EBoolStateID
	{
		STATE_COLOURWRITE,			//!< Specifies whether or not writing to the colour buffer is enabled
		STATE_DEPTHTEST,			//!< Specifies whether or not depth testing is enabled
		STATE_DEPTHWRITE,			//!< Specifies whether or not depth writing is enabled
		STATE_ALPHATEST,			//!< Specifies whether or not alpha testing is enabled
		STATE_BLENDING,				//!< Specifies whether or not alpha blending is enabled
		STATE_FOGBLENDING,			//!< Specifies whether or not fog blending is enabled
		STATE_SPECULAR,				//!< Specifies whether or not specular lighting is enabled
		STATE_STENCIL,				//!< Specifies whether or not use of the stencil buffer is enabled
		STATE_RANGEFOG,				//!< Specifies whether or not range fog is enabled
									//!< that is, whether the distance of the object from the viewer is taken into account
									//!< rather than the Z value of the object

		STATE_CLIPPING,				//!< Specifies whether or not clipping is enabled
		STATE_LIGHTING,				//!< Specifies whether or not vertex lighting is enabled
		STATE_VERTEXCOLOURS,		//!< Specifies whether or not vertex colours are enabled
		STATE_NORMALISENORMALS,		//!< Specifies whether or not normals are automatically renormalised.
									//!< Scaling operations can cause vertex normals to become denormalised 

		STATE_POINTSPRITE,			//!< Specifies whether or not point sprites are enabled
		STATE_POINTSCALE,			//!< Specifies whether or not point scaling is enabled
		STATE_SCISSORTEST,			//!< Specifies whether or not scissor testing is enabled
		STATE_TWOSIDEDSTENCIL,		//!< Specifies whether stencil buffering is two sided or not
		STATE_SEPERATE_ALPHABLEND,	//!< Specifies whether blending for alpha can be different from the blending of the colour
		STATE_INDEXED_VERTEX_BLEND	//!< Specifies whether indexed vertex blending is available. If this is set to true, then
									//!< a set of matrix indices must be supplied per-vertex
	};


    //=========================================================================
    // States that are refrenced by SetFloat style functions
    //=========================================================================
	enum EFloatStateID
	{
		STATE_ALPHAREFERENCE,				//!< Alpha reference value used for alpha testing
		STATE_FOGSTART,						//!< Distance from the camera, at which the fog blending starts
		STATE_FOGEND,						//!< Distance from the cmarea, at which the fog blending ends
		STATE_FOGDENSITY,					//!< Density of the fog used in exponential fog modes
		STATE_DEPTHBIASVALUE,				//!< Depth bias used in depth comparisons
		STATE_SLOPESCALEDEPTHBIASVALUE,		//!< More advanced form of depth bias
		STATE_POINTSIZE,					//!< Size to use for point size in the case that it is not set per vertex
		STATE_POINTSIZEMIN,					//!< Minimum size of point primitives
		STATE_POINTSIZEMAX,					//!< Maximum size of point primitives
		STATE_POINTSCALE_A,					//!< 
		STATE_POINTSCALE_B,					//!<
		STATE_POINTSCALE_C					//!<
	};										
											
	enum EUIntStateID						
	{										
		STATE_STENCILREFERENCE,				//!< Stencil reference value used for stencil testing
		STATE_STENCILMASK,					//!< Mask applied to the reference value, and the stencil values when comparing
		STATE_STENCILWRITEMASK,				//!< Mask applied to the stencil values as they are written
		//STATE_VERTEXBLENDMATRIXCOUNT		 
	};

	enum EAlphaBlendStateID
	{
		STATE_SRCBLENDALPHA,				//!< Source blending mode for alpha if STATE_SEPERATE_ALPHABLEND is true
		STATE_DESTBLENDALPHA,				//!< Destination blending mode for alpha if STATE_SEPERATE_ALPHABLEND is true
		STATE_BLENDOPALPHA					//!< Blend op for alpha if STATE_SEPERATE_ALPHABLEND is true
	};

	enum EColourStateID
	{
		STATE_FOGCOLOUR,					//!< Colour used for fog blending
		STATE_TEXTUREFACTORCOLOUR,			//!< Texture factor colour used in multitexturing
		STATE_AMBIENTLIGHTCOLOUR,			//!< Colour of ambient lighting
		STATE_BLENDFACTORCOLOUR				//!< Blend factor colour
	};

    //=========================================================================
    // Constants for modes that aren't set through SetState style functions
    //=========================================================================		
	enum EMaterialSourceType
	{
		STATE_DIFFUSE_MATERIAL_SOURCE,
		STATE_AMBIENT_MATERIAL_SOURCE,
		STATE_SPECULAR_MATERIAL_SOURCE,
		STATE_EMISSIVE_MATERIAL_SOURCE
	};
	
	enum EMaterialSource
	{
		MATERIALSOURCE_MATERIALCOLOUR,
		MATERIALSOURCE_DIFFUSECOLOUR
		//MATERIALSOURCE_SPECULARCOLOUR
	};
	
	
	enum EBlendOp
	{
		BLEND_ADD,							//!< Add the source and destination operands
		BLEND_SUBTRACT,						//!< Subtract the destination from the source
		BLEND_REVERSE_SUBTRACT,				//!< Subtract the source from the destination
		BLEND_MIN,							//!< Gets the minimum of the source and destination operands
		BLEND_MAX							//!< Gets the maximum of the source and destination operands
	};

	
	enum EFillMode
	{
		FILL_POINT,							//!<
		FILL_WIREFRAME,						//!<
		FILL_SOLID							//!<
	};

	enum EShadeMode
	{
		SHADE_FLAT,							//!<
		SHADE_GOURAUD						//!<
	};										

	enum EBlendMode
	{
		BLEND_ZERO,							//!< Use zero as the factor
		BLEND_ONE,							//!< Use one as the factor
		BLEND_SRCCOLOUR,					//!< Use the source colour 
		BLEND_INVSRCCOLOUR,					//!< Use 1 - source colour
		BLEND_SRCALPHA,						//!< Use source alpha
		BLEND_INVSRCALPHA,					//!< Use 1 - source alpha
		BLEND_SRCALPHASAT,					//!< 
		BLEND_DESTALPHA,					//!< Use destination alpha
		BLEND_INVDESTALPHA,					//!< Use 1 - destination alpha
		BLEND_DESTCOLOUR,					//!< Use destination colour
		BLEND_INVDESTCOLOUR,				//!< Use 1 - destination color
		BLEND_BLENDFACTOR,					//!< Use blend factor colour
		BLEND_INVBLENDFACTOR,				//!< Use 1 - blend factor colour
		BLEND_BOTHINVSRCALPHA				//!< 
	};

	enum ECullMode
	{
		CULL_NONE,
		CULL_CLOCKWISE,							//!<
		CULL_COUNTERCLOCKWISE					//!<
	};										

	//For use with SetStencilFunc, SetDepthFunc, SetAlphaFunc
	enum ECmpFunc
	{
		CMP_NEVER,							//!< Test never passes
		CMP_LESS,							//!< Test passes if the value is less than the value being compared with
		CMP_LEQUAL,							//!< Test passes if the value is less than or equal to the value being compared with
		CMP_GREATER,						//!< Test passes if the value is greater than the value being compared with
		CMP_GEQUAL,							//!< Test passes if the value is greater or equal to the value being compared with
		CMP_ALWAYS,							//!< Test always passes
		CMP_EQUAL,							//!< Test passes if the values are equal
		CMP_NOTEQUAL						//!< Test passes if the values are not equal
	};

	enum EFogMode
	{
		FOGMODE_NONE,						//!<
		FOGMODE_EXP,						//!<
		FOGMODE_EXP2,						//!<
		FOGMODE_LINEAR						//!<
	};

	enum EFogType
	{
		FOGTYPE_TABLE,
		FOGTYPE_VERTEX
	};

	enum EStencilOpType
	{
		STENCILOP_FAIL,						//
		STENCILOP_ZFAIL,					//
		STENCILOP_PASS						//
	};

	enum EStencilOp
	{
		STENCILOP_KEEP,					//!<
		STENCILOP_ZERO,					//!<
		STENCILOP_REPLACE,				//!<
		STENCILOP_INCRSAT,				//!<
		STENCILOP_DECRSAT,				//!<
		STENCILOP_INVERT,					//!<
		STENCILOP_INCR,					//!<
		STENCILOP_DECR					//!<
	};										

	enum EWrap
	{
		WRAP_U,								//!<
		WRAP_V,								//!<
		WRAP_W								//!<
	};

    //=========================================================================
    // Texture stage state
    //=========================================================================
	enum ETextureStageStateID
	{
		TEXSTAGE_COLOUROP,
		TEXSTAGE_COLOURARG1,
		TEXSTAGE_COLOURARG2,
		TEXSTAGE_ALPHAOP,
		TEXSTAGE_ALPHAARG1,
		TEXSTAGE_ALPHAARG2,
		TEXSTAGE_TEXCOORDINDEX,
		TEXSTAGE_COLOURARG0,
		TEXSTAGE_ALPHAARG0,
		TEXSTAGE_RESULTARG
	};

	enum ETextureStageID
	{
		STAGE_0,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		STAGE_5,
		STAGE_6,
		STAGE_7,

		TEXTURE_STAGE_COUNT
	};

	enum ETextureCoordSetID
	{
		TEXCOORDSET_0,
		TEXCOORDSET_1,
		TEXCOORDSET_2,
		TEXCOORDSET_3,
		TEXCOORDSET_4,
		TEXCOORDSET_5,
		TEXCOORDSET_6,
		TEXCOORDSET_7,

		TEXCOORDSET_COUNT
	};

	enum ETextureOp
	{
		TEXOP_DISABLE,
		TEXOP_SELECTARG1,
		TEXOP_SELECTARG2,
		TEXOP_MODULATE,
		TEXOP_MODULATE2X,
		TEXOP_MODULATE4X,
		TEXOP_ADD,
		TEXOP_ADDSIGNED,
		TEXOP_SUBTRACT,
		TEXOP_ADDSMOOTH,
		TEXOP_BLENDDIFFUSEALPHA,
		TEXOP_BLENDTEXTUREALPHA,
		TEXOP_BLENDFACTORALPHA,
		TEXOP_BLENDTEXTUREALPHAPM,
		TEXOP_BLENDCURRENTALPHA,
		TEXOP_PREMODULATE,
		TEXOP_MODULATEALPHA_ADDCOLOUR,
		TEXOP_MODULATECOLOUR_ADDALPHA,
		TEXOP_DOTPRODUCT3,
		TEXOP_MULTIPLYADD,
		TEXOP_LERP
	};

	enum ETextureArgument
	{
		TEXARG_CONSTANT,	//!< Select a constant from a texure stage
		TEXARG_CURRENT,		//!< The texture argument is the result of the previous blending stage
							//!< in the first blending stage, this is equivilent to TEXARG_DIFFUSE
		TEXARG_DIFFUSE,		//!< Diffuse colour interpolated during gouraud shading
		TEXARG_SPECULAR,	//!< Specular colour interpolated during gouraud shading
		TEXARG_TEMP,		//!< Temporary register
		TEXARG_TEXTURE,		//!< The texture for this stage
		TEXARG_TEXTUREFACTOR //!< The texture factor colour
	};

	enum ETextureAddressModeType
	{
		TEX_ADDRESS_U,
		TEX_ADDRESS_V,
		TEX_ADDRESS_W
	};

	enum ETextureAddressingMode
	{
		TEXADDRESS_WRAP, 
		TEXADDRESS_CLAMP, 
		TEXADDRESS_BORDER,
		TEXADDRESS_MIRROR, 
		TEXADDRESS_MIRRORONCE
	};

	enum ETextureCoordGen
	{
		TEXGEN_NONE,
		TEXGEN_SPHEREMAP,
		TEXGEN_EYESPACE_REFLECTION,
		TEXGEN_EYESPACE_NORMAL
	};

	enum ETextureFilterType
	{
		TEXFILTER_MIN,
		TEXFILTER_MAG,
		TEXFILTER_MIP
	};

	enum ETextureFilter
	{
		TEXFILTER_POINT,
		TEXFILTER_LINEAR,
		TEXFILTER_ANISOTROPIC
	};

	enum ETextureParamType
	{
		TEXPARAM_MIPMAP_LOD_BIAS,
		TEXPARAM_MAX_ANISOTROPY
	};


    //=========================================================================
    // Lighting
    //=========================================================================
	enum ELightType
	{
		LIGHT_DIRECTIONAL,
		LIGHT_POINT,
		LIGHT_SPOT
	};


    //=========================================================================
    // Matrix type
    //=========================================================================
	enum EMatrixType
	{
		MAT_WORLD,
		MAT_VIEW,
		MAT_PROJECTION,
		MAT_TEXTURE0,
		MAT_TEXTURE1,
		MAT_TEXTURE2,
		MAT_TEXTURE3,
		MAT_TEXTURE4,
		MAT_TEXTURE5,
		MAT_TEXTURE6,
		MAT_TEXTURE7
	};

	enum EReadOnlyMatrixType
	{
		MAT_WORLDVIEW,
		MAT_VIEWPROJECTION
	};


    //=========================================================================
    // Sorting
    //=========================================================================
	enum ESortValue
	{
		SORT_SKYDOME,
		SORT_NORMAL,
		SORT_TRANSPARENT,
		SORT_REFRACTIVE
	};
};
//end namespace Renderer



#endif
//#ifndef RENDERER_RENDERERSTATECONSTANTS_H
