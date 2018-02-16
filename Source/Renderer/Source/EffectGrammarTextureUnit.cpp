//======================================================================================
//! @file         EffectGrammarTextureUnit.cpp
//! @brief        Defines the part of the effect grammar relating to texture units
//!               
//!				  This is in a seperate file, because compiling the effect grammar all in one
//!				  go was too much for the compiler.
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 05 July 2005
//! @copyright    Bryan Robertson
//======================================================================================

#include <iostream>
#include "Renderer/EffectGrammar.h"
#include "Renderer/EffectParserSemanticActions.h"


using namespace boost::spirit;
using namespace Renderer;


//=========================================================================
// The following code relates to the boost spirit parser
//=========================================================================
template <class ScannerT>
void EffectGrammar::definition<ScannerT>::texunitdef( EffectGrammar const& self )
{
	/*
	//Textures
	TextureUnit = (lexeme_d[str_p("TextureUnit")][AddRootNode(self.Tree(), NODETYPE_TEXTUREUNIT)] >> ch_p('{') >> *TextureStatement >> ch_p('}'))
						[EndRootNode(self.Tree())];

	TextureStatement = Texture 
						| TexCoordSet 
						| TexCoordGen
						| AddressingMode 
						| Filtering 
						| MaxAnisotropy
						| ColourOp  
						| AlphaOp 
						| Scroll 
						| ScrollAnim
						| Rotate 
						| RotateAnim 
						| Scale 
						| WaveXForm;

	Texture = (lexeme_d[str_p("Texture")[AddRootNode(self.Tree(), NODETYPE_TEXTURE)]] 
										>> StringLiteral >> lexeme_d[str_p("1D")[AddNode(self.Tree(), NODETYPE_TEX1D)] 
															| str_p("2D")[AddNode(self.Tree(), NODETYPE_TEX2D)] 
															| str_p("CUBEMAP")[AddNode(self.Tree(), NODETYPE_TEXCUBEMAP)] ])
				[EndRootNode(self.Tree())];

	TexCoordSet = (lexeme_d[str_p("TexCoordSet")][AddRootNode(self.Tree(), NODETYPE_TEXCOORDSET)] 
									>> UnsignedInt)
				[EndRootNode(self.Tree())];

	AddressingMode = (lexeme_d[str_p("AddressingMode")][AddRootNode(self.Tree(), NODETYPE_ADDRESSINGMODE)] 
												>> lexeme_d[str_p("WRAP")[AddNode(self.Tree(), NODETYPE_WRAP)] 
															| str_p("CLAMP")[AddNode(self.Tree(), NODETYPE_CLAMP)] 
															| str_p("MIRROR")[AddNode(self.Tree(), NODETYPE_MIRROR)] ])
						[EndRootNode(self.Tree())];

	Filtering = (lexeme_d[str_p("Filtering")[AddRootNode(self.Tree(), NODETYPE_FILTERING)]] >>	(FilterComplex | FilterSimple))
						[EndRootNode(self.Tree())];

	FilterComplex = (FilterType >> FilterType >> (lexeme_d[str_p("NONE")[AddNode(self.Tree(), NODETYPE_NONE)]] | FilterType));

	FilterSimple  = (lexeme_d[str_p("NONE")[AddNode(self.Tree(), NODETYPE_NONE)]
								| str_p("BILINEAR")[AddNode(self.Tree(), NODETYPE_BILINEAR)] 
								| str_p("TRILINEAR")[AddNode(self.Tree(), NODETYPE_TRILINEAR)] 
								| str_p("ANISOTROPIC")[AddNode(self.Tree(), NODETYPE_ANISOTROPIC)] ]);


	FilterType = lexeme_d[str_p("POINT")[AddNode(self.Tree(), NODETYPE_POINT)] 
							| str_p("LINEAR")[AddNode(self.Tree(), NODETYPE_LINEAR)] 
							| str_p("ANISOTROPIC")[AddNode(self.Tree(), NODETYPE_ANISOTROPIC)]];

	MaxAnisotropy = (lexeme_d[str_p("MaxAnisotropy")[AddRootNode(self.Tree(), NODETYPE_MAXANISOTROPY)]] >> UnsignedInt)
							[EndRootNode(self.Tree())];

	ColourOp = (lexeme_d[str_p("ColourOp")[AddRootNode(self.Tree(), NODETYPE_COLOUROP)]] 
										>> ColourOperand >> ColourOperand >> ColourOperation)
							[EndRootNode(self.Tree())];

	ColourOperation =	lexeme_d[ str_p("SELECTARG1")[AddNode(self.Tree(), NODETYPE_SELECTARG1)] 
									| str_p("SELECTARG2")[AddNode(self.Tree(), NODETYPE_SELECTARG2)]
									| str_p("MODULATE2X")[AddNode(self.Tree(), NODETYPE_MODULATE2X)]
									| str_p("MODULATE4X")[AddNode(self.Tree(), NODETYPE_MODULATE4X)]
									| str_p("MODULATE")[AddNode(self.Tree(), NODETYPE_MODULATE)]  
									| str_p("DISABLE") [AddNode(self.Tree(), NODETYPE_DISABLE)]
									| str_p("ADDSIGNED")[AddNode(self.Tree(), NODETYPE_ADDSIGNED)] 
									| str_p("ADDSMOOTH")[AddNode(self.Tree(), NODETYPE_ADDSMOOTH)]
									| str_p("ADD")[AddNode(self.Tree(), NODETYPE_ADD)]
									| str_p("SUBTRACT")[AddNode(self.Tree(), NODETYPE_SUBTRACT)]
									| str_p("PREMODULATE")[AddNode(self.Tree(), NODETYPE_PREMODULATE)]
									| str_p("MODULATEALPHA_ADDCOLOUR")[AddNode(self.Tree(), NODETYPE_MODULATEALPHA_ADDCOLOUR)]
									| str_p("MODULATEALPHA_ADDALPHA")[AddNode(self.Tree(), NODETYPE_MODULATEALPHA_ADDALPHA)]
									| str_p("DOTPRODUCT3")[AddNode(self.Tree(), NODETYPE_DOTPRODUCT3)]
									| str_p("MULTIPLYADD")[AddNode(self.Tree(), NODETYPE_MULTIPLYADD)]
									| str_p("LERP")[AddNode(self.Tree(), NODETYPE_LERP)]
									| str_p("BLENDDIFFUSEALPHA")[AddNode(self.Tree(), NODETYPE_BLENDDIFFUSEALPHA)]
									| str_p("BLENDTEXTUREALPHA")[AddNode(self.Tree(), NODETYPE_BLENDTEXTUREALPHA)]
									| str_p("BLENDCURRENTALPHA")[AddNode(self.Tree(), NODETYPE_BLENDCURRENTALPHA)]
									| str_p("BLENDFACTORALPHA")[AddNode(self.Tree(), NODETYPE_BLENDFACTORALPHA)]
									| str_p("BLENDTEXTUREALPHAPM")[AddNode(self.Tree(), NODETYPE_BLENDTEXTUREALPHAPM)]];

	ColourOperand =		lexeme_d[str_p("CURRENT")[AddNode(self.Tree(), NODETYPE_CURRENT)] 
						| str_p("CONSTANT")[AddNode(self.Tree(), NODETYPE_CONSTANT)] 
						| str_p("DIFFUSE")[AddNode(self.Tree(), NODETYPE_DIFFUSE)] 
						| str_p("SPECULAR")[AddNode(self.Tree(), NODETYPE_SPECULAR)] 
						| str_p("TEMP")[AddNode(self.Tree(), NODETYPE_TEMP)]
						| str_p("TEXTURE")[AddNode(self.Tree(), NODETYPE_TEXTURE)]
						| str_p("TEXTUREFACTOR")[AddNode(self.Tree(), NODETYPE_TEXTUREFACTOR)]];

	AlphaOp = (lexeme_d[str_p("AlphaOp")[AddRootNode(self.Tree(), NODETYPE_ALPHAOP)]] >> ColourOperand >> ColourOperand >> ColourOperation)
						[EndRootNode(self.Tree())];

	Scroll = (lexeme_d[str_p("Scroll")[AddRootNode(self.Tree(), NODETYPE_SCROLL)]] >> FloatingPoint >> FloatingPoint)
						[EndRootNode(self.Tree())];
	
	ScrollAnim =  (lexeme_d[str_p("ScrollAnim")[AddRootNode(self.Tree(), NODETYPE_SCROLLANIM)]] >> FloatingPoint >> FloatingPoint)
						[EndRootNode(self.Tree())];
	
	Rotate =  (lexeme_d[str_p("Rotate")[AddRootNode(self.Tree(), NODETYPE_ROTATE)]] >> FloatingPoint)
						[EndRootNode(self.Tree())];
	
	RotateAnim =  (lexeme_d[str_p("RotateAnim")[AddRootNode(self.Tree(), NODETYPE_ROTATEANIM)]] >> FloatingPoint)
						[EndRootNode(self.Tree())];
	
	Scale =  (lexeme_d[str_p("Scale")[AddRootNode(self.Tree(), NODETYPE_SCALE)]] >> FloatingPoint >> FloatingPoint)
						[EndRootNode(self.Tree())];

	WaveXForm = (lexeme_d[str_p("WaveXForm")[AddRootNode(self.Tree(), NODETYPE_WAVEXFORM)]] 
													>> XFormType >> WaveType 
													>> FloatingPoint >> FloatingPoint 
													>> FloatingPoint >> FloatingPoint)
						[EndRootNode(self.Tree())];

	XFormType = lexeme_d[str_p("SCROLLX")[AddNode(self.Tree(), NODETYPE_SCROLLX)]
							| str_p("SCROLLY")[AddNode(self.Tree(), NODETYPE_SCROLLY)]
							| str_p("ROTATE")[AddNode(self.Tree(), NODETYPE_ROTATE)]
							| str_p("SCALEX")[AddNode(self.Tree(), NODETYPE_SCALEX)]
							| str_p("SCALEY")[AddNode(self.Tree(), NODETYPE_SCALEY)] ];

	WaveType = lexeme_d[str_p("SINE")		[AddNode(self.Tree(), NODETYPE_SINE)]
						| str_p("SQUARE")	[AddNode(self.Tree(), NODETYPE_SQUARE)]
						| str_p("SAWTOOTH") [AddNode(self.Tree(), NODETYPE_SAWTOOTH)]
						| str_p("TRIANGLE") [AddNode(self.Tree(), NODETYPE_TRIANGLE)]
						| str_p("INVERSESAWTOOTH") [AddNode(self.Tree(), NODETYPE_INVERSESAWTOOTH)] ];
*/
}
