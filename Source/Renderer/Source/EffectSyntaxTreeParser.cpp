//======================================================================================
//! @file         EffectSyntaxTreeParser.cpp
//! @brief        Class that transforms an syntax tree from a parsed effect, into an effect 
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 04 July 2005
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


#include "Core/Core.h"
#include "Math/Vector3D.h"
#include "Renderer/Renderer.h"
#include "Renderer/Colour4f.h"
#include "Renderer/Effect.h"
#include "Renderer/EffectSyntaxTreeParser.h"



using namespace Renderer;



//=========================================================================
//! @function    EffectSyntaxTreeParser::EffectSyntaxTreeParser
//! @brief       EffectSyntaxTreeParser constructor
//!              
//! @param       tree		[in] Reference to the syntax tree
//! @param		 fileName	[in] Name of the file that the effect is stored in
//! @param		 renderer	[in] Reference to the renderer. Used to check support for render states
//!              
//=========================================================================
EffectSyntaxTreeParser::EffectSyntaxTreeParser( const EffectSyntaxTreeParser::Tree& tree, 
												const Char* fileName, 
												Renderer::IRenderer& renderer  )
: m_tree(tree), m_renderer(renderer)
{
	m_effect = boost::shared_ptr<Effect> ( new Effect(fileName) );
}
//End EffectSyntaxTreeParser::EffectSyntaxTreeParser



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseTree
//! @brief       Parse the syntax tree, producing an effect as its output
//!              
//!              
//! @return      A pointer to the effect
//! @throw       Core::RuntimeError if the parse failed
//=========================================================================
boost::shared_ptr<Effect> EffectSyntaxTreeParser::ParseTree ( )
{	
	const_tree_iterator currentNode = m_tree.Root()->ChildrenBegin();
	const_tree_iterator end = m_tree.Root()->ChildrenEnd();

	for ( ; currentNode != end ; ++currentNode )
	{
		if ( currentNode->Description() == NODETYPE_EFFECT )
		{
			const_tree_iterator effectNode = currentNode->ChildrenBegin();
			const_tree_iterator effectNodeEnd = currentNode->ChildrenEnd();

			if ( effectNode->Description() == NODETYPE_STRINGLITERAL )
			{
				std::string effectName = boost::any_cast<std::string>( effectNode->Data() );
				std::clog << __FUNCTION__ ": Found effect " << effectName << std::endl;

				++effectNode;

				for ( ; effectNode != effectNodeEnd; ++effectNode )
				{
					if ( effectNode->Description() == NODETYPE_TECHNIQUE )
					{
						try
						{
							ParseTechnique( *effectNode );
						}
						catch ( Core::RuntimeError err )
						{
							std::cerr << __FUNCTION__  ": Error parsing technique " << m_effect->TechniqueCount()
										<< ": " << err.What() << std::endl;
						}
					}
				}
			}
			else
			{
				throw Core::RuntimeError ( "Effect name not found!", 0, __FILE__, __FUNCTION__, __LINE__ );
			}
		}
	}

	if ( m_effect->TechniqueCount() == 0 )
	{
		throw Core::RuntimeError ( "Effect does not contain any techniques!", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

	return m_effect;
}
//End EffectSyntaxTreeParser::ParseTree


//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseTechnique
//! @brief       Parse a technique in the syntax tree
//!             
//! @param       node		[in] Root node in the syntax tree for the technique
//!              
//! @throw       Core::RuntimeError if any error was encountered
//=========================================================================
void EffectSyntaxTreeParser::ParseTechnique	( const EffectSyntaxTreeParser::Node& node )
{
	std::clog << __FUNCTION__ ": Technique " << m_effect->TechniqueCount() << " found" << std::endl;

	const_tree_iterator current = node.ChildrenBegin();
	const_tree_iterator end = node.ChildrenEnd();
	Technique technique;

	for ( ; current != end; ++current )
	{
		if ( current->Description() == NODETYPE_CASTSHADOWS )
		{
			technique.CastShadows( boost::any_cast<bool>(current->Data()) );
		}

		if ( current->Description() == NODETYPE_RECEIVESHADOWS )
		{
			technique.ReceiveShadows( boost::any_cast<bool>(current->Data()) );
		}

		if ( current->Description() == NODETYPE_LODLEVEL )
		{
			technique.LODLevel ( boost::any_cast<UInt>(current->ChildrenBegin()->Data()) );

			std::clog << __FUNCTION__ ": lod level " << technique.LODLevel() << std::endl;
		}

		if ( current->Description() == NODETYPE_SORT )
		{
			technique.SortValue( boost::any_cast<ESortValue>(current->ChildrenBegin()->Data()) );
		}

		if ( current->Description() == NODETYPE_PASS )
		{
			ParsePass ( technique, *(current) );
		}
	}

	if ( technique.PassCount() == 0 )
	{
		std::cerr << __FUNCTION__ << ": Error, technique " << m_effect->TechniqueCount()
				  << " does not contain any passes! Adding a default pass!" << std::endl;

		technique.AddPass(RenderState());
	}
	
	m_effect->AddTechnique(technique);

}
//End EffectSyntaxTreeParser::ParseTechnique


//=========================================================================
//! @function    EffectSyntaxTreeParser::ParsePass
//! @brief		 Parse a pass from the syntax tree
//!              
//! @param		 technique [in] Parent techique that will own the pass
//! @param       node	   [in]	EffectSyntaxTreeParser::Tree node that serves as the root of the pass
//!              
//! @throw       Core::RuntimeError if any error was encountered
//=========================================================================
void EffectSyntaxTreeParser::ParsePass ( Technique& technique, const EffectSyntaxTreeParser::Node& node )
{
	std::clog << "Pass " << technique.PassCount() << " found" << std::endl;
	RenderState renderState;

	const_tree_iterator current = node.ChildrenBegin();
	const_tree_iterator end = node.ChildrenEnd();

	for ( ; current != end; ++current )
	{
		//EEffectNodeType type = current->Description();

		switch ( current->Description() )
		{
			case NODETYPE_AMBIENT:
			case NODETYPE_DIFFUSE:
			case NODETYPE_SPECULAR:
			case NODETYPE_EMISSIVE:
				ParseMaterialColour ( renderState, *current );
			break;

			case NODETYPE_SCENEBLEND:
				ParseSceneBlend ( renderState, *current );
			break;

			case NODETYPE_ALPHATEST:
				ParseAlphaTest ( renderState, *current );
			break;

			case NODETYPE_DEPTHTEST:
			case NODETYPE_DEPTHFUNC:
			case NODETYPE_DEPTHBIAS:
			case NODETYPE_DEPTHWRITE:
				ParseDepthTest( renderState, *current );
			break;

			case NODETYPE_STENCILWRITEMASK:
			case NODETYPE_STENCILMASK:
			case NODETYPE_STENCILPASS:
			case NODETYPE_STENCILFAIL:
			case NODETYPE_STENCILZFAIL:
			case NODETYPE_STENCILTEST:
				ParseStencilTest( renderState, *current );
			break;

			case NODETYPE_CULLINGMODE:
				renderState.SetCullMode ( boost::any_cast<ECullMode>( current->ChildrenBegin()->Data() ) );
			break;

			case NODETYPE_NORMALISENORMALS:
				renderState.SetNormaliseNormals ( boost::any_cast<bool>( current->ChildrenBegin()->Data() ) );
			break;

			case NODETYPE_LIGHTING:
				renderState.SetLighting ( boost::any_cast<bool>( current->ChildrenBegin()->Data() ) );
			break;

			case NODETYPE_SHADING:
				renderState.SetShadeMode ( boost::any_cast<EShadeMode>( current->ChildrenBegin()->Data() ) );
			break;

			case NODETYPE_COLOURWRITE:
				renderState.SetColourWrite ( boost::any_cast<bool>( current->ChildrenBegin()->Data() ) );
			break;

			case NODETYPE_MAXLIGHTS:
				renderState.SetMaxLights ( boost::any_cast<UInt>( current->ChildrenBegin()->Data() ) );
			break;

			case NODETYPE_FOGOVERRIDE:
			case NODETYPE_FOGTYPE:
			case NODETYPE_FOGDENSITY:
			case NODETYPE_FOGSTART:
			case NODETYPE_FOGEND:
			case NODETYPE_FOGCOLOUR:
				ParseFogSettings( renderState, *current );
			break;

			case NODETYPE_TEXTUREUNIT:
				
				if ( renderState.TextureUnitCount() >= m_renderer.GetDeviceProperty (CAP_TEXTURE_MAX_SIMULTANEOUS) )
				{
					std::ostringstream errorMessage;
					
					errorMessage << "Technique not supported by the hardware. Pass " << technique.PassCount()
								 << " has too many texture units.\n"
								 << "Renderer max simultaneous textures = " 
								 << m_renderer.GetDeviceProperty(CAP_TEXTURE_MAX_SIMULTANEOUS)
								 << std::endl;

					throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
				}
				else
				{
					ParseTextureUnit(renderState, *current);
				}

			break;
		}
		
	}

	technique.AddPass(renderState);
}
//End EffectSyntaxTreeParser::ParsePass


//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseTextureUnit
//! @brief       Parse a texture unit from the syntax tree
//!              
//! @param		 renderState [out]  Render state that will own the texture unit
//! @param       node		 [in]	Root node in the tree that represents the texture unit
//!              
//! @throw       Core::RuntimeError if an error occured
//=========================================================================
void EffectSyntaxTreeParser::ParseTextureUnit ( RenderState& state, const EffectSyntaxTreeParser::Node& node )
{
	std::clog << __FUNCTION__ ": Texture unit " << state.TextureUnitCount() << " found" << std::endl;

	TextureUnit textureUnit;
	const_tree_iterator current = node.ChildrenBegin();
	const_tree_iterator end = node.ChildrenEnd();

	for ( ; current != end; ++current )
	{
	
		switch ( current->Description() )
		{
			case NODETYPE_TEXTURE:
			{
				const_tree_iterator texture = current->ChildrenBegin();
		
				textureUnit.SetType ( boost::any_cast<ETextureType>((texture)->Data()) );
				textureUnit.SetName ( boost::any_cast<std::string>((++texture)->Data()).c_str() );

				std::clog << __FUNCTION__ ": Texture " << boost::any_cast<std::string>((texture)->Data()).c_str() << std::endl;
				
			}
			break;

			case NODETYPE_AUTOGENERATED:
				textureUnit.SetAutoGenerated ( boost::any_cast<bool>(current->ChildrenBegin()->Data()) );
			break;

			case NODETYPE_TEXCOORDSET:
			{
				UInt texCoordSet = boost::any_cast<UInt>(current->ChildrenBegin()->Data());

				if ( texCoordSet >= TEXCOORDSET_COUNT )
				{
					std::ostringstream errorMessage;
					errorMessage << "Error, texture coordinate set for texture unit " << state.TextureUnitCount()
								 << " is out of range. value is " << texCoordSet 
								 << ", the maximum is " << TEXCOORDSET_COUNT << std::endl;

					throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
				}

				textureUnit.SetCoordinateSet ( static_cast<ETextureCoordSetID>(texCoordSet) );
			}
			break;

			case NODETYPE_ADDRESSINGMODE:
			{
				const_tree_iterator addressMode = current->ChildrenBegin();

				ETextureAddressModeType type = boost::any_cast<ETextureAddressModeType>(addressMode->Data());
				ETextureAddressingMode mode  = boost::any_cast<ETextureAddressingMode>((++addressMode)->Data());

				textureUnit.SetAddressingMode ( type, mode);
			}
			break;

			case NODETYPE_FILTERING:
				ParseTextureFilter( textureUnit, *current );
			break;

			case NODETYPE_MAXANISOTROPY:
				textureUnit.SetMaxAnisotropy ( boost::any_cast<UInt>(current->ChildrenBegin()->Data()) );
			break;

			case NODETYPE_COLOUROP:
			{
				const_tree_iterator colourOp = current->ChildrenBegin();

				ETextureOp op =  boost::any_cast<ETextureOp>(colourOp->Data());
				ETextureArgument arg1 = boost::any_cast<ETextureArgument>((++colourOp)->Data());
				ETextureArgument arg2 = boost::any_cast<ETextureArgument>((++colourOp)->Data());

				textureUnit.SetColourOp ( op, arg1, arg2 );
			}
			break;

			case NODETYPE_ALPHAOP:
			{
				const_tree_iterator alphaOp = current->ChildrenBegin();

				ETextureOp op = boost::any_cast<ETextureOp>(alphaOp->Data());
				ETextureArgument arg1 = boost::any_cast<ETextureArgument>((++alphaOp)->Data());
				ETextureArgument arg2 = boost::any_cast<ETextureArgument>((++alphaOp)->Data());

				textureUnit.SetAlphaOp ( op, arg1, arg2 );
			}
			break;

			case NODETYPE_CONSTANTCOLOUR:
			{
				Colour4f colour;
				ParseColour(colour, *current);

				textureUnit.SetConstantColour ( colour );
			}
			break;

			case NODETYPE_TEXCOORDGEN:
				textureUnit.SetCoordinateGenMode ( boost::any_cast<ETextureCoordGen>(current->ChildrenBegin()->Data()) );
			break;

			case NODETYPE_SCROLL:
			case NODETYPE_SCALE:
			case NODETYPE_ROTATE:
			case NODETYPE_SCROLLANIM:
			case NODETYPE_SCALEANIM:
			case NODETYPE_ROTATEANIM:
			case NODETYPE_WAVEXFORM:
				ParseTextureTransform( textureUnit, *current );
			break;

		}
	}

	state.AddTextureUnit( textureUnit );
}
//EffectSyntaxTreeParser::ParseTextureUnit


//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseTextureTransform
//! @brief       Parse a texture transform entry from the syntax tree
//!              
//! @param       textureUnit [out]	Texture unit to change
//! @param       node		 [in]	Node in the syntax tree containing the filter settings
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void EffectSyntaxTreeParser::ParseTextureTransform ( TextureUnit& textureUnit, const EffectSyntaxTreeParser::Node& node )
{
	switch ( node.Description() )
	{
		case NODETYPE_SCROLL:
		{
			Math::Vector3D vec;
			ParseVector(vec, node);
			textureUnit.SetScroll( vec );
		}
		break;
		
		case NODETYPE_SCALE:
		{
			Math::Vector3D vec;
			ParseVector(vec, node);
			textureUnit.SetScale( vec );
		}
		break;

		case NODETYPE_ROTATE:
		{
			textureUnit.SetRotate( boost::any_cast<Float>(node.ChildrenBegin()->Data()) );
		}
		break;

		case NODETYPE_SCROLLANIM:
		{
			Math::Vector3D vec;
			ParseVector(vec, node);
			textureUnit.SetScrollAnim( vec );
		}
		break;
		
		case NODETYPE_SCALEANIM:
		{
			Math::Vector3D vec;
			ParseVector(vec, node);
			textureUnit.SetScaleAnim( vec );
		}
		break;

		case NODETYPE_ROTATEANIM:
		{
			textureUnit.SetRotateAnim( boost::any_cast<Float>(node.ChildrenBegin()->Data()) );
		}
		break;

		case NODETYPE_WAVEXFORM:
		{
			ParseWaveXForm( textureUnit, node );
		}
		break;
	}
}
//End EffectSyntaxTreeParser::ParseTextureTransform



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseWaveXForm
//! @brief       Parse a wave transform from the syntax tree
//!              
//! @param       textureUnit [out] Texture unit to add the wave transform to
//! @param       node		 [in]  Node in the syntax tree which contains the filter settings
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void EffectSyntaxTreeParser::ParseWaveXForm ( TextureUnit& textureUnit, const EffectSyntaxTreeParser::Node& node )
{
	const_tree_iterator current = node.ChildrenBegin();
	const_tree_iterator end = node.ChildrenEnd();

	EXFormType xformType = XFORM_SCROLL_X;
	EWaveType  waveType = WAVE_SINE;
	Float base = 0.0f;
	Float frequency = 1.0f;
	Float phase = 0.0f;
	Float amp = 1.0f;

	for ( ; current != end; ++current )
	{
	
		switch ( current->Description() )
		{
			case NODETYPE_XFORMTYPE:
				xformType = boost::any_cast<EXFormType>(current->ChildrenBegin()->Data());
			break;

			case NODETYPE_WAVETYPE:
				waveType = boost::any_cast<EWaveType>(current->ChildrenBegin()->Data());
			break;

			case NODETYPE_BASE:
				base = boost::any_cast<Float>(current->ChildrenBegin()->Data());
			break;

			case NODETYPE_FREQUENCY:
				frequency = boost::any_cast<Float>(current->ChildrenBegin()->Data());
			break;

			case NODETYPE_PHASE:
				phase = boost::any_cast<Float>(current->ChildrenBegin()->Data());
			break;

			case NODETYPE_AMPLITUDE:
				amp = boost::any_cast<Float>(current->ChildrenBegin()->Data());
			break;
		}
	}

	textureUnit.AddWaveTransform ( xformType, waveType, base, frequency, phase, amp );
}
//End EffectSyntaxTreeParser::ParseWaveXForm


//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseTextureFilter
//! @brief       Parse a texture filter entry from the syntax tree
//!              
//!              
//! @param       textureUnit [out] Texture unit to have its filter setting changed
//! @param       node		 [in]  Node in the syntax tree which contains the filter settings
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void EffectSyntaxTreeParser::ParseTextureFilter ( TextureUnit& textureUnit, const EffectSyntaxTreeParser::Node& node )
{
	if ( node.ChildrenCount() == 1 )
	{
		switch ( node.ChildrenBegin()->Description() )
		{
			case NODETYPE_NONE:
				textureUnit.SetMinFilter( TEXFILTER_POINT );
				textureUnit.SetMagFilter( TEXFILTER_POINT );
				textureUnit.SetMipFilter( TEXFILTER_POINT );
			break;

			case NODETYPE_BILINEAR:
				textureUnit.SetMinFilter( TEXFILTER_LINEAR );
				textureUnit.SetMagFilter( TEXFILTER_LINEAR );
				textureUnit.SetMipFilter( TEXFILTER_POINT );
			break;

			case NODETYPE_TRILINEAR:
				textureUnit.SetMinFilter( TEXFILTER_LINEAR );
				textureUnit.SetMagFilter( TEXFILTER_LINEAR );
				textureUnit.SetMipFilter( TEXFILTER_LINEAR );
			break;

			case NODETYPE_ANISOTROPIC:
				textureUnit.SetMinFilter( TEXFILTER_ANISOTROPIC );
				textureUnit.SetMagFilter( TEXFILTER_ANISOTROPIC );
				textureUnit.SetMipFilter( TEXFILTER_LINEAR );
			break;
		}
	}
	else
	{
		const_tree_iterator current = node.ChildrenBegin();

		ETextureFilter min = boost::any_cast<ETextureFilter>(current->Data());
		ETextureFilter mag = boost::any_cast<ETextureFilter>((++current)->Data());
		ETextureFilter mip = boost::any_cast<ETextureFilter>((++current)->Data());

		textureUnit.SetMinFilter( min );
		textureUnit.SetMagFilter( mag );
		textureUnit.SetMipFilter( mip );
   	}
}
//End EffectSyntaxTreeParser::ParseTextureFilter



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseFogSettings
//! @brief       Parse a fog entry from the syntax tree
//!              
//! @param       state [out] Render state which will have its fog settings changed
//! @param       node  [in]	 Node in the syntax tree which contains the fog settings
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void EffectSyntaxTreeParser::ParseFogSettings ( RenderState& state, const EffectSyntaxTreeParser::Node& node )
{
	switch ( node.Description() )
	{
		case NODETYPE_FOGOVERRIDE:
			state.SetFogOverride ( boost::any_cast<bool>( node.ChildrenBegin()->Data() ) );
		break;

		case NODETYPE_FOGTYPE:
			state.SetFogMode ( boost::any_cast<EFogMode>( node.ChildrenBegin()->Data() ) );
		break;

		case NODETYPE_FOGDENSITY:
			state.SetFogDensity ( boost::any_cast<Float>( node.ChildrenBegin()->Data() ) );
		break;

		case NODETYPE_FOGSTART:
			state.SetFogBegin ( boost::any_cast<Float>( node.ChildrenBegin()->Data() ) );
		break;

		case NODETYPE_FOGEND:
			state.SetFogEnd ( boost::any_cast<Float>( node.ChildrenBegin()->Data() ) );
		break;

		case NODETYPE_FOGCOLOUR:
		{
			Colour4f colour;
			ParseColour ( colour, node );
			state.SetFogColour ( colour );
		}
		break;

		default:
			debug_assert ( false, "Error, invalid fog syntax node!");
		break;
	}
}
//End EffectSyntaxTreeParser::ParseFogSettings




//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseStencilTest
//! @brief       Parse a stencil test entry from the syntax tree
//!              
//!              
//! @param       state [out] Render state which will have its stencil test changed
//! @param       node  [in] Node in the syntax tree which contains the stencil test setting
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void EffectSyntaxTreeParser::ParseStencilTest ( RenderState& state, const EffectSyntaxTreeParser::Node& node )
{
	switch ( node.Description() )
	{
		case NODETYPE_STENCILWRITEMASK:
			state.SetStencilWriteMask ( boost::any_cast<UInt>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_STENCILMASK:
			state.SetStencilMask ( boost::any_cast<UInt>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_STENCILPASS:
			state.SetStencilPass( boost::any_cast<EStencilOp>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_STENCILFAIL:
			state.SetStencilFail( boost::any_cast<EStencilOp>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_STENCILZFAIL:
			state.SetStencilZFail( boost::any_cast<EStencilOp>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_STENCILTEST:
			{
				const_tree_iterator current = node.ChildrenBegin();

				if ( node.Description() == NODETYPE_BOOLEAN )
				{
					//If the description is of type boolean, then it can only be false
					state.SetStencilTest(false);
				}
				else
				{
					state.SetStencilFunc ( boost::any_cast<ECmpFunc>(current->Data()) );
					state.SetStencilRef	 ( boost::any_cast<UInt>((++current)->Data()) );
				}
			}
			break;

		default:
			debug_assert ( false, "Error, invalid stencil state!" );
			break;
	}
}
//End EffectSyntaxTreeParser::ParseStencilTest



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseDepthTest
//! @brief       
//!              
//!              
//! @param       state 
//! @param       node 
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void EffectSyntaxTreeParser::ParseDepthTest ( RenderState& state, const Node& node )
{
	switch ( node.Description() )
	{
		case NODETYPE_DEPTHTEST:
			state.SetDepthTest( boost::any_cast<bool>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_DEPTHFUNC:
			state.SetDepthFunc( boost::any_cast<ECmpFunc>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_DEPTHBIAS:
			state.SetDepthBias( boost::any_cast<Float>(node.ChildrenBegin()->Data()) );
			break;

		case NODETYPE_DEPTHWRITE:
			state.SetDepthWrite( boost::any_cast<bool>(node.ChildrenBegin()->Data()) );
			break;

		default:
			debug_assert ( false, "Error, invalid depth state!" );
			break;
	}
}
//End EffectSyntaxTreeParser::ParseDepthTest



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseAlphaTest
//! @brief       Parse an alpha test entry from the syntax tree          
//!              
//! @param		 state [out] Render state which will have its alpha test changed
//! @param       node  [in]	 Node in the syntax tree which contains the alpha test setting
//!              
//! @throw       Core::RuntimeError
//=========================================================================
void EffectSyntaxTreeParser::ParseAlphaTest ( RenderState& state, const EffectSyntaxTreeParser::Node& node )
{
	const_tree_iterator current = node.ChildrenBegin();

	if ( current->Description() == NODETYPE_BOOLEAN )
	{
		//If the description is of type boolean, then it can only be false
		state.SetAlphaTest(false);
	}
	else
	{
		state.SetAlphaFunc		( boost::any_cast<ECmpFunc>(current->Data()) );
		state.SetAlphaReference ( boost::any_cast<Float>((++current)->Data()) );
	}

}
//End EffectSyntaxTreeParser::ParseAlphaTest



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseSceneBlend
//! @brief       Parse a scene blend entry from the syntax tree
//!              
//! @param       state [out] Render state which will have its scene blend changed
//! @param       node  [in]	 Node in the syntax tree which contains the scene blend setting
//!              
//! @throw       Core::RuntimeError if an error occurs
//=========================================================================
void EffectSyntaxTreeParser::ParseSceneBlend ( RenderState& state, const EffectSyntaxTreeParser::Node& node )
{
	debug_assert ( node.Description() == NODETYPE_SCENEBLEND, "Invalid scene blend node" );
	const_tree_iterator current = node.ChildrenBegin();

	switch ( current->Description() )
	{
		case NODETYPE_ADD:
			state.SetSceneBlend ( BLEND_ONE, BLEND_ONE );
			return;

		case NODETYPE_MODULATE:
			state.SetSceneBlend ( BLEND_DESTCOLOUR, BLEND_ZERO );
			return;

		case NODETYPE_COLOURBLEND:
			state.SetSceneBlend ( BLEND_SRCCOLOUR, BLEND_INVSRCCOLOUR );
			return;

		case NODETYPE_ALPHABLEND:
			state.SetSceneBlend ( BLEND_SRCALPHA, BLEND_INVSRCALPHA );
			return;
	}

	EBlendMode src = boost::any_cast<EBlendMode>(current->Data());
	EBlendMode dest = boost::any_cast<EBlendMode>((++current)->Data());

	state.SetSceneBlend ( src, dest);
	state.SetBlending ( true );

}
//End EffectSyntaxTreeParser::ParseSceneBlend



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseMaterialColour
//! @brief       Parse a material colour entry from the syntax tree
//!              
//! @param       state [out] Render state to set the material colour of
//! @param       node  [in]  Node in the syntax tree that represents the colour
//!              
//! @throw       Core::RuntimeError if an error occured
//=========================================================================
void EffectSyntaxTreeParser::ParseMaterialColour ( RenderState& state, const EffectSyntaxTreeParser::Node& node )
{
	if ( !m_renderer.Supports( CAP_MATERIAL_SOURCECOLOUR ) )
	{
		throw Core::RuntimeError ( "Graphics card does not support material source colour! Technique not supported", 0,
									__FILE__, __FUNCTION__, __LINE__ );
	}

	switch ( node.Description() )
	{
		case NODETYPE_AMBIENT:
		{
			if ( node.ChildrenBegin()->Description() == NODETYPE_VERTEXCOLOUR )
			{
				state.SetMaterialSource ( STATE_AMBIENT_MATERIAL_SOURCE, MATERIALSOURCE_DIFFUSECOLOUR );
			}
			else
			{
				state.SetMaterialSource ( STATE_AMBIENT_MATERIAL_SOURCE, MATERIALSOURCE_MATERIALCOLOUR );
				Colour4f colour;

				ParseColour( colour, node );
				state.SetAmbientColour ( colour );
			}
		}
		break;

		case NODETYPE_DIFFUSE:
		{
			if ( node.ChildrenBegin()->Description() == NODETYPE_VERTEXCOLOUR )
			{
				state.SetMaterialSource ( STATE_DIFFUSE_MATERIAL_SOURCE, MATERIALSOURCE_DIFFUSECOLOUR );
			}
			else
			{
				state.SetMaterialSource ( STATE_DIFFUSE_MATERIAL_SOURCE, MATERIALSOURCE_MATERIALCOLOUR );
				Colour4f colour;

				ParseColour( colour, node );
				state.SetDiffuseColour ( colour );
			}
		}
		break;

		case NODETYPE_SPECULAR:
		{
			if ( node.ChildrenBegin()->Description() == NODETYPE_VERTEXCOLOUR )
			{
				state.SetMaterialSource ( STATE_SPECULAR_MATERIAL_SOURCE, MATERIALSOURCE_DIFFUSECOLOUR );
			}
			else
			{
				state.SetMaterialSource ( STATE_SPECULAR_MATERIAL_SOURCE, MATERIALSOURCE_MATERIALCOLOUR );
				Colour4f colour;

				ParseColour( colour, node );
				state.SetSpecularColour ( colour );
			}
		}
		break;


		case NODETYPE_EMISSIVE:
		{
			if ( node.ChildrenBegin()->Description() == NODETYPE_VERTEXCOLOUR )
			{
				state.SetMaterialSource ( STATE_EMISSIVE_MATERIAL_SOURCE, MATERIALSOURCE_DIFFUSECOLOUR );
			}
			else
			{
				state.SetMaterialSource ( STATE_EMISSIVE_MATERIAL_SOURCE, MATERIALSOURCE_MATERIALCOLOUR );
				Colour4f colour;

				ParseColour( colour, node );
				state.SetEmissiveColour ( colour );
			}
		}
		break;

		case NODETYPE_SHININESS:
		{
			state.SetShininess( boost::any_cast<Float>(node.ChildrenBegin()->Data()) );
		}
		break;

		default:
			throw Core::RuntimeError ( "Invalid material colour block in syntax tree!", node.Description(),
										__FILE__, __FUNCTION__, __LINE__ );
	}
}
//End EffectSyntaxTreeParser::ParseMaterialColour



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseColour
//! @brief       Parse a colour from the syntax tree
//!              
//! @param       colour [out] Colour to hold the output of the parse
//! @param       node	[in]  Node in the tree where the colour is stored
//!              
//! @throw       Core::RuntimeError if an error occured
//=========================================================================
void EffectSyntaxTreeParser::ParseColour ( Colour4f& colour, const EffectSyntaxTreeParser::Node& node )
{
	debug_assert ( node.ChildrenCount() >= 3, "Invalid colour!" );

	const_tree_iterator current = node.ChildrenBegin();

	if ( current->Description() == NODETYPE_FLOATVALUE )
	{
		colour.Red( boost::any_cast<Float>(current->Data()) );
		++current;
	}

	if ( current->Description() == NODETYPE_FLOATVALUE )
	{
		colour.Green( boost::any_cast<Float>(current->Data()) );
		++current;
	}

	if ( current->Description() == NODETYPE_FLOATVALUE )
	{
		colour.Blue( boost::any_cast<Float>(current->Data()) );
		++current;
	}

	if ( current != node.ChildrenEnd() )
	{
		colour.Alpha( boost::any_cast<Float>(current->Data()) );
	}
}
//End EffectSyntaxTreeParser::ParseColour



//=========================================================================
//! @function    EffectSyntaxTreeParser::ParseVector
//! @brief       Parse a vector from the syntax tree
//!              
//! @param       vect [out] Vector to hold the output of the parse
//! @param       node [in]  Node in the tree where the colour is stored
//!              
//! @throw       Core::RuntimeError if an error occured
//=========================================================================
void EffectSyntaxTreeParser::ParseVector ( Math::Vector3D& vec, const EffectSyntaxTreeParser::Node& node )
{
	debug_assert ( node.ChildrenCount() >= 2, "Invalid vector!" );

	const_tree_iterator current = node.ChildrenBegin();

	if ( current->Description() == NODETYPE_FLOATVALUE )
	{
		vec.X( boost::any_cast<Float>(current->Data()) );
		++current;
	}

	if ( current->Description() == NODETYPE_FLOATVALUE )
	{
		vec.Y( boost::any_cast<Float>(current->Data()) );
		++current;
	}

	if ( current != node.ChildrenEnd()  )
	{
		vec.Z( boost::any_cast<Float>(current->Data()) );
		//++current;
	}
}
//End EffectSyntaxTreeParser::ParseVector