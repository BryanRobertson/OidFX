//======================================================================================
//! @file         EffectGrammar.cpp
//! @brief        Class the does all the work of parsing an effect file into an effect syntax tree
//!               
//!				  Contains the first part of the boost::spirit effect grammar.
//!				  The grammar had to be split up to avoid overflowing internal compiler limits
//!				  under MS Visual C++ 2002
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 04 July 2005
//! @copyright    Bryan Robertson
//======================================================================================

#include <iostream>
#include "Renderer/EffectGrammar.h"
#include "Renderer/EffectParserSemanticActions.h"


using namespace boost::spirit;
using namespace Renderer;


//=========================================================================
//! @function    ParseEffectFromFile
//! @brief       
//!              
//! @param       fileName [in] 
//! @param       tree	  [in] 
//! 
//! @return
//! @throw       
//=========================================================================
bool Renderer::ParseEffectFromFile ( const Char* fileName, Core::SyntaxTree<UInt>& tree )
{
	FileIterator first ( fileName );

	if (!first)
	{
		std::cerr << "Couldn't load effect file" << fileName << std::endl;

		return false;
	}

	FileIterator last = first.make_end();

	EffectGrammar g(tree);	SkipGrammar skip;
	
    boost::spirit::parse_info<FileIterator> info = parse(first, last, g, skip);
	
	if (info.full)
	{
		return true;
	}
	else
    {
		std::string errorInfo;
		std::copy ( info.stop, last, errorInfo.begin() );

		std::cerr << "Error, parsing of effect " << fileName << " failed. Stopped at: " << errorInfo;
		return false;
    }

}
//End Renderer::ParseEffectFromFile



//=========================================================================
// The following code relates to the boost spirit parser
//=========================================================================
template <class ScannerT>
EffectGrammar::definition<ScannerT>::definition( EffectGrammar const& self )
{
	
	EffectFile		= (lexeme_d[str_p("Effect")[AddRootNode(self.Tree(), NODETYPE_EFFECT)]] 
								>> StringLiteral >> ch_p('{') >> !RecieveShadows >> !CastShadows >> Technique >> ch_p('}'))
								[EndRootNode(self.Tree())];

	RecieveShadows = (lexeme_d[str_p("RecieveShadows")[AddRootNode(self.Tree(), NODETYPE_RECIEVESHADOWS)]] >> Boolean)
						[EndRootNode(self.Tree())];

	CastShadows = (lexeme_d[str_p("CastShadows")[AddRootNode(self.Tree(), NODETYPE_CASTSHADOWS)]] >> Boolean)
						[EndRootNode(self.Tree())];

	Technique = (lexeme_d[str_p("Technique")[AddRootNode(self.Tree(), NODETYPE_TECHNIQUE)]] >> ch_p('{') >> *Pass >> ch_p('}'))
						[EndRootNode(self.Tree())];

	Pass = (lexeme_d[str_p("Pass")[AddRootNode(self.Tree(), NODETYPE_PASS)]] >> ch_p('{') >> PassBlock >>  ch_p('}'))
						[EndRootNode(self.Tree())];

	PassBlock = MaterialProperties;		
	//			| SceneBlend;
/*
	MaterialProperties = AmbientColour 
						| DiffuseColour
						| SpecularColour
						| EmissiveColour;*/
/*
	VertexColour = lexeme_d[str_p("VERTEXCOLOUR")[AddNode(self.Tree(), NODETYPE_VERTEXCOLOUR)]];
	
	AmbientColour = (lexeme_d[str_p("Ambient")[AddRootNode(self.Tree(), NODETYPE_AMBIENT)]] 
											>>  VertexColour
												| Colour3 )
					[EndRootNode(self.Tree())];

	DiffuseColour = (lexeme_d[str_p("Diffuse")[AddRootNode(self.Tree(), NODETYPE_DIFFUSE)]] 
											>>  VertexColour
												| Colour )
					[EndRootNode(self.Tree())];

	SpecularColour = ((lexeme_d[str_p("Specular")[AddRootNode(self.Tree(), NODETYPE_SPECULAR)]] 
											>>   VertexColour 
												| Colour )
											>>  !FloatingPoint)
					[EndRootNode(self.Tree())];

	EmissiveColour = (lexeme_d[str_p("Emissive")[AddRootNode(self.Tree(), NODETYPE_EMISSIVE)]] 
											>> VertexColour
												| Colour )
					[EndRootNode(self.Tree())];

	SceneBlend = (lexeme_d[str_p("SceneBlend")[AddRootNode(self.Tree(), NODETYPE_SCENEBLEND)]])
											//>>	BlendMode >> BlendMode)
					[EndRootNode(self.Tree())];*/

/*
	BlendMode = lexeme_d[ str_p("ONE")[AddNode(self.Tree(), NODETYPE_ONE)]
						| str_p("ZERO")[AddNode(self.Tree(), NODETYPE_ZERO)]
						| str_p("SRCCOLOUR")[AddNode(self.Tree(), NODETYPE_SRCCOLOUR)]
						| str_p("INVSRCCOLOUR")[AddNode(self.Tree(), NODETYPE_INVSRCCOLOUR)]
						| str_p("SRCALPHA")[AddNode(self.Tree(), NODETYPE_SRCALPHA)]
						| str_p("INVSRCALPHA")[AddNode(self.Tree(), NODETYPE_INVSRCALPHA)]
						| str_p("SRCALPHASAT")[AddNode(self.Tree(), NODETYPE_SRCALPHASAT)]
						| str_p("DESTALPHA")[AddNode(self.Tree(), NODETYPE_DESTALPHA)]
						| str_p("INVDESTALPHA")[AddNode(self.Tree(), NODETYPE_INVDESTALPHA)]
						| str_p("DESTCOLOUR")[AddNode(self.Tree(), NODETYPE_DESTCOLOUR)]
						| str_p("INVDESTCOLOUR")[AddNode(self.Tree(), NODETYPE_INVDESTCOLOUR)]
						| str_p("BLENDFACTOR")[AddNode(self.Tree(), NODETYPE_BLENDFACTOR)]
						| str_p("INVBLENDFACTOR")[AddNode(self.Tree(), NODETYPE_INVBLENDFACTOR)]
						| str_p("BOTHINVSRCALPHA")[AddNode(self.Tree(), NODETYPE_BOTHINVSRCALPHA)] ];*/
	/*
	DepthBuffer = (lexeme_d[str_p("DepthBuffer")[AddRootNode(self.Tree(), NODETYPE_DEPTHTEST)]] >> Boolean)
					[EndRootNode(self.Tree())];

	DepthWrite = (lexeme_d[str_p("DepthWrite")[AddRootNode(self.Tree(), NODETYPE_DEPTHWRITE)]] >> Boolean)
					[EndRootNode(self.Tree())];

	DepthFunc = (lexeme_d[str_p("DepthFunc")[AddRootNode(self.Tree(), NODETYPE_DEPTHFUNC)]] >> TestFunc)
					[EndRootNode(self.Tree())];

	DepthBias = (lexeme_d[str_p("DepthBias")[AddRootNode(self.Tree(), NODETYPE_DEPTHBIAS)]] >> FloatingPoint)
					[EndRootNode(self.Tree())];

	AlphaTest = (lexeme_d[str_p("AlphaTest")[AddRootNode(self.Tree(), NODETYPE_ALPHATEST)]] >> TestFunc >> FloatingPoint)
					[EndRootNode(self.Tree())];

	StencilTest = (lexeme_d[str_p("StencilTest")[AddRootNode(self.Tree(), NODETYPE_STENCILTEST)]] >> TestFunc >> UnsignedInt)
					[EndRootNode(self.Tree())];

	StencilOp	= lexeme_d[ str_p("KEEP")[AddNode(self.Tree(), NODETYPE_KEEP)] 
							| str_p("KEEP")[AddNode(self.Tree(), NODETYPE_ZERO)]
							| str_p("REPLACE")[AddNode(self.Tree(), NODETYPE_REPLACE)]
							| str_p("INCRSAT")[AddNode(self.Tree(), NODETYPE_INCRSAT)]
							| str_p("DECRSAT")[AddNode(self.Tree(), NODETYPE_DECRSAT)]
							| str_p("INVERT")[AddNode(self.Tree(), NODETYPE_INVERT)]
							| str_p("INCR")[AddNode(self.Tree(), NODETYPE_INCR)]
							| str_p("DECR")[AddNode(self.Tree(), NODETYPE_DECR)] ];

	StencilPass = (lexeme_d[str_p("StencilPass")[AddRootNode(self.Tree(), NODETYPE_STENCILPASS)]] >> StencilOp)
					[EndRootNode(self.Tree())];
	
	StencilFail = (lexeme_d[str_p("StencilFail")[AddRootNode(self.Tree(), NODETYPE_STENCILFAIL)]] >> StencilOp)
					[EndRootNode(self.Tree())];

	StencilZFail = (lexeme_d[str_p("StencilZFail")[AddRootNode(self.Tree(), NODETYPE_STENCILZFAIL)]] >> StencilOp)
					[EndRootNode(self.Tree())];

	StencilMask = (lexeme_d[str_p("StencilMask")[AddRootNode(self.Tree(), NODETYPE_STENCILMASK)]] >> UnsignedInt)
					[EndRootNode(self.Tree())];

	StencilWriteMask = (lexeme_d[str_p("StencilWriteMask")[AddRootNode(self.Tree(), NODETYPE_STENCILWRITEMASK)]] >> UnsignedInt)
					[EndRootNode(self.Tree())];

	TestFunc = (lexeme_d[str_p("ALWAYS")[AddNode(self.Tree(), NODETYPE_ALWAYS)] 
					| str_p("NEVER")[AddNode(self.Tree(), NODETYPE_NEVER)]
					| str_p("LESS")[AddNode(self.Tree(), NODETYPE_LESS)]
					| str_p("LEQUAL")[AddNode(self.Tree(), NODETYPE_LEQUAL)]
					| str_p("EQUAL")[AddNode(self.Tree(), NODETYPE_EQUAL)]
					| str_p("NOTEQUAL")[AddNode(self.Tree(), NODETYPE_NOTEQUAL)]
					| str_p("GEQUAL")[AddNode(self.Tree(), NODETYPE_GEQUAL)]
					| str_p("GREATER")[AddNode(self.Tree(), NODETYPE_GREATER)]] );

	CullingMode = (lexeme_d[str_p("CullingMode")[AddRootNode(self.Tree(), NODETYPE_CULLINGMODE)]] 
										>> ( lexeme_d[str_p("CLOCKWISE")[AddNode(self.Tree(), NODETYPE_CLOCKWISE)]] 
											| lexeme_d[str_p("ANTICLOCKWISE")[AddRootNode(self.Tree(), NODETYPE_ANTICLOCKWISE)]] ))
						[EndRootNode(self.Tree())];

	Lighting = (lexeme_d[str_p("Lighting")[AddRootNode(self.Tree(), NODETYPE_LIGHTING)]] >> Boolean)
						[EndRootNode(self.Tree())];

	Shading = (lexeme_d[str_p("Shading")][AddRootNode(self.Tree(), NODETYPE_SHADING)] 
							>> (  lexeme_d[str_p("FLAT")[AddNode(self.Tree(), NODETYPE_FLAT)] 
											| str_p("GOURAUD")[AddNode(self.Tree(), NODETYPE_GOURAUD)]]))
						[EndRootNode(self.Tree())];

	FogSetting  = FogOverride 
				| FogType 
				| FogColour 
				| FogDensity 
				| FogStart 
				| FogEnd;
	
	FogOverride = (lexeme_d[str_p("FogOverride")[AddRootNode(self.Tree(), NODETYPE_FOGOVERRIDE)]] >> Boolean)
						[EndRootNode(self.Tree())];

	FogType = (lexeme_d[str_p("FogType")[AddRootNode(self.Tree(), NODETYPE_FOGTYPE)]] 
							>>  ( lexeme_d[str_p("NONE")[AddNode(self.Tree(), NODETYPE_NONE)]
												| str_p("LINEAR")[AddNode(self.Tree(), NODETYPE_LINEAR)]
												| str_p("EXP2")[AddNode(self.Tree(), NODETYPE_EXP2)]
												| str_p("EXP")[AddNode(self.Tree(), NODETYPE_EXP)]]) )
						[EndRootNode(self.Tree())];

	FogColour = (lexeme_d[str_p("FogColour")[AddRootNode(self.Tree(), NODETYPE_FOGCOLOUR)]] >> Colour3)
						[EndRootNode(self.Tree())];
	
	FogDensity  = (lexeme_d[str_p("FogDensity")[AddRootNode(self.Tree(), NODETYPE_FOGDENSITY)]] >> FloatingPoint)
						[EndRootNode(self.Tree())];
	
	FogStart  = (lexeme_d[str_p("FogStart")[AddRootNode(self.Tree(), NODETYPE_FOGSTART)]] >> FloatingPoint)
						[EndRootNode(self.Tree())];
	
	FogEnd	  = (lexeme_d[str_p("FogEnd")[AddRootNode(self.Tree(), NODETYPE_FOGEND)]] >> FloatingPoint)
						[EndRootNode(self.Tree())];


	ColourWrite = (lexeme_d[str_p("ColourWrite")[AddRootNode(self.Tree(), NODETYPE_COLOURWRITE)]] >> Boolean)
						[EndRootNode(self.Tree())];x

	MaxLights = (lexeme_d[str_p("MaxLights")[AddRootNode(self.Tree(), NODETYPE_MAXLIGHTS)]] >> UnsignedInt)
						[EndRootNode(self.Tree())];

*/

	Boolean = lexeme_d[str_p("Enabled")[AddNode(self.Tree(), NODETYPE_ENABLED)] 
								|  str_p("Disabled")[AddNode(self.Tree(), NODETYPE_DISABLED)]];

	StringLiteral = lexeme_d[(ch_p('\"') >> (*(~ch_p('\"')))[AddNode(self.Tree(), NODETYPE_STRINGLITERAL)] >> ch_p('\"'))];

	FloatingPoint = real_p[AddFloatNode(self.Tree(), NODETYPE_FLOATVALUE)];

	UnsignedInt = uint_p[AddUIntNode(self.Tree(), NODETYPE_UINTVALUE)];

	//Used where only a colour with 4 elements is valid
	Colour4 = FloatingPoint >> FloatingPoint >> FloatingPoint >> FloatingPoint;
	//Used where only a colour with 3 elements is valid
	Colour3 = FloatingPoint >> FloatingPoint >> FloatingPoint;
	//Used where a colour with 3 or 4 elements is valid
	Colour  = FloatingPoint >> FloatingPoint >> FloatingPoint >> !FloatingPoint;


	//Call the rest of the parser definition.
	texunitdef(self);
}
