//======================================================================================
//! @file         EffectSyntaxTreeParser.h
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


#ifndef RENDERER_EFFECTSYNTAXTREEPARSER_H
#define RENDERER_EFFECTSYNTAXTREEPARSER_H



#include <boost/shared_ptr.hpp>
#include "Core/SyntaxTree.h"
#include "Renderer/EffectSyntaxTreeNodeTypes.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer { class Effect; class Colour4f; }
namespace Math	   { class Vector3D;			   }



//namespace Renderer
namespace Renderer
{


	//!@class	EffectSyntaxTreeParser
	//!@brief	Class that transforms a syntax tree from a parsed effect, into an effect 
	class EffectSyntaxTreeParser
	{
		public:


			//=========================================================================
            // Public types
            //=========================================================================
			typedef Core::SyntaxTree<EEffectNodeType> Tree;

            //=========================================================================
            // Constructors
            //=========================================================================
			EffectSyntaxTreeParser ( const Tree& tree, const Char* fileName, Renderer::IRenderer& renderer  );
			

            //=========================================================================
            // Public methods
            //=========================================================================
			boost::shared_ptr<Effect> ParseTree ( );


		private:

            //=========================================================================
            // Private types
            //=========================================================================
			typedef Tree::Node	Node;
			typedef Node::const_iterator const_tree_iterator;

            //=========================================================================
            // Private methods
            //=========================================================================
			void ParseTechnique		( const Node& node );
			void ParsePass			( Technique& technique, const Node& node );
			void ParseTextureUnit	( RenderState& state, const Node& node );

			void ParseWaveXForm		   ( TextureUnit& textureUnit, const Node& node );
			void ParseTextureTransform ( TextureUnit& textureUnit, const Node& node );
			void ParseTextureFilter	 ( TextureUnit& textureUnit, const Node& node );
			void ParseFogSettings	 ( RenderState& state, const Node& node );
			void ParseStencilTest	 ( RenderState& state, const Node& node );
			void ParseAlphaTest		 ( RenderState& state, const Node& node );
			void ParseDepthTest		 ( RenderState& state, const Node& node );
			void ParseSceneBlend	 ( RenderState& state, const Node& node );
			void ParseMaterialColour ( RenderState& state, const Node& node );
			void ParseColour		 ( Colour4f& colour, const Node& node );
			void ParseVector		 ( Math::Vector3D& vec, const Node& node );

            //=========================================================================
            // Private types
            //=========================================================================
			const Tree&							m_tree;
			boost::shared_ptr<Effect>		    m_effect;
			Renderer::IRenderer&			    m_renderer;
	};


};
//end namespace Renderer


#endif
//#ifndef EFFECTSYNTAXTREEPARSER_H
