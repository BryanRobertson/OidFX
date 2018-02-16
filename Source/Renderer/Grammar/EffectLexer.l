%name EffectLexer
%define IOSTREAM
%define LEX_PARAM YY_EffectParserBase_STYPE *val, YY_EffectParserBase_LTYPE *loc

%define MEMBERS public: UInt m_line; UInt m_column; private: std::ifstream& m_file;

%define CONSTRUCTOR_PARAM std::ifstream& file
	 
%define CONSTRUCTOR_INIT : m_line(1), m_column(1), m_file(file)

%define	IFILE_DEFAULT &m_file

%header{

//Code copied to the header file
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Renderer/EffectSyntaxTreeNodeTypes.h"
#include "EffectParserBase.h"
#include <malloc.h>
#define alloca _alloca

%}

%{

/* ------------------------------------------------------------------
   Initial code (copied verbatim to the output file)
   ------------------------------------------------------------------ */
  using namespace std;   
 
  
%}

DIGIT			[0-9]
WSPACE			[ \t]+
LINEBREAK		\n|\r\n
IDENTIFIER		[a-zA-Z_][a-zA-Z0-9_]*
COMMENT			"\/\/"[^\n]*\n
STRING			\"[^\"]*\"
FLOAT			"-"?{DIGIT}+("."{DIGIT}+)?

%%

"Effect"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_EFFECT;				}
"Technique"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TECHNIQUE;			}
"LODLevel"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_LODLEVEL;			}
"ReceiveShadows"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_RECEIVESHADOWS;		}
"CastShadows"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CASTSHADOWS;			}
"Sort"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SORT;				}
"SKYDOME"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SKYDOME;				}
"NORMAL"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_NORMAL;				}
"TRANSPARENT"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TRANSPARENT;			}
"Pass"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_PASS;				}

"Ambient"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_AMBIENT;				}
"Diffuse"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DIFFUSE;				}
"Specular"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SPECULAR;			}
"Shininess"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SHININESS;			}
"Emissive"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_EMISSIVE;			}
"VERTEXCOLOUR"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_VERTEXCOLOUR;		}

"SceneBlend"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCENEBLEND;			}
"BlendOp"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BLENDOP;				}

"DepthTest"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DEPTHTEST;					}
"DepthWrite"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DEPTHWRITE;					}
"DepthFunc"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DEPTHFUNC;					}
"DepthBias"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DEPTHBIAS;					}

"StencilTest"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_STENCILTEST;					}
"StencilWriteMask"  { m_column += strlen(yytext);	return EffectParserBase::TOKEN_STENCILWRITEMASK;			}
"StencilMask"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_STENCILMASK;					}
"StencilPass"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_STENCILPASS;					}
"StencilFail"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_STENCILFAIL;					}
"StencilZFail"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_STENCILZFAIL;				}

"KEEP"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_KEEP;						}
"REPLACE"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_REPLACE;						}
"INCRSAT"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INCRSAT;						}
"DECRSAT"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DECRSAT;						}
"INVERT"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INVERT;						}
"INCR"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INCR;						}
"DECR"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DECR;						}

"AlphaTest"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ALPHATEST;					}

"CullingMode"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CULLINGMODE;					}
"COUNTERCLOCKWISE"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_COUNTERCLOCKWISE;			}
"CLOCKWISE"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CLOCKWISE;					}

"Lighting"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_LIGHTING;					}

"Shading"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SHADING;						}
"FLAT"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FLAT;						}
"GOURAUD"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_GOURAUD;						}

"ColourWrite"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_COLOURWRITE;					}

"NormaliseNormals"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_NORMALISENORMALS;			}

"MaxLights"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MAXLIGHTS;					}
"Iteration"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ITERATION;					}
"POINT"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_POINT;						}
"DIRECTIONAL"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DIRECTIONAL;					}
"SPOT"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SPOT;						}
"ONCEPERLIGHT"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ONCEPERLIGHT;				}
"ONCE"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ONCE;						}

"FogOverride"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FOGOVERRIDE;				}
"FogType"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FOGTYPE;					}
"FogDensity"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FOGDENSITY;				}
"FogColour"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FOGCOLOUR;				}
"FogStart"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FOGSTART;				}
"FogEnd"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FOGEND;					}

"NONE"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_NONE;					}
"EXP"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_EXP;						}
"EXP2"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_EXP2;					}
"LINEAR"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_LINEAR;					}

"TextureUnit"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TEXTUREUNIT;				}
"Texture"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TEXTURE;					}
"AutoGenerated"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_AUTOGENERATED;			}
"1D"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_1D;						}
"2D"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_2D;						}
"CUBEMAP"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CUBEMAP;					}
"TexCoordSet"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TEXCOORDSET;				}
"AddressingMode"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADDRESSINGMODE;			}
"WRAP"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_WRAP;					}
"CLAMP"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CLAMP;					}
"MIRROR"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MIRROR;					}
"MIRRORONCE"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MIRRORONCE;				}
"BORDER"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BORDER;					}
"ADDRESSMODE_U"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADDRESSMODE_U;			}
"ADDRESSMODE_V"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADDRESSMODE_V;			}
"ADDRESSMODE_W"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADDRESSMODE_W;			}
"Filtering"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FILTERING;				}
"BILINEAR"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BILINEAR;				}
"TRILINEAR"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TRILINEAR;				}
"ANISOTROPIC"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ANISOTROPIC;				}
"MaxAnisotropy"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MAXANISOTROPY;			}
"ColourOp"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_COLOUROP;				}
"AlphaOp"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ALPHAOP;					}
"DISABLE"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DISABLE;					}
"SELECTARG1"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SELECTARG1;				}
"SELECTARG2"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SELECTARG2;				}
"MODULATE"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MODULATE;				}
"MODULATE2X"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MODULATE2X;				}
"MODULATE4X"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MODULATE4X;				}
"ADD"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADD;						}
"ADDSIGNED"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADDSIGNED;				}
"SUBTRACT"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SUBTRACT;				}
"ADDSMOOTH"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADDSMOOTH;				}
"BLENDDIFFUSEALPHA"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BLENDDIFFUSEALPHA;		}
"BLENDTEXTUREALPHA"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BLENDTEXTUREALPHA;		}
"BLENDFACTORALPHA"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BLENDFACTORALPHA;		}
"BLENDTEXTUREALPHAPM"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BLENDTEXTUREALPHAPM;					}
"BLENDCURRENTALPHA"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BLENDCURRENTALPHA;					}
"PREMODULATE"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_PREMODULATE;							}
"MODULATEALPHA_ADDCOLOUR"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MODULATEALPHA_ADDCOLOUR;			}
"MODULATECOLOUR_ADDALPHA"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MODULATECOLOUR_ADDALPHA;			}
"DOTPRODUCT3"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DOTPRODUCT3;						}
"MULTIPLYADD"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MULTIPLYADD;						}
"LERP"						{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_LERP;							}
"CURRENT"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CURRENT;							}
"TEXTURE"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TEXTURE;							}
"DIFFUSE"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DIFFUSE;							}
"SPECULAR"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SPECULAR;						}
"CONSTANT"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CONSTANT;						}
"ConstantColour"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_CONSTANTCOLOUR;					}
"TexCoordGen"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TEXCOORDGEN;						}
"SPHEREMAP"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SPHEREMAP;						}
"EYESPACE_REFLECTION"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_EYESPACE_REFLECTION;				}
"EYESPACE_NORMAL"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_EYESPACE_NORMAL;					}
"Scroll"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCROLL;							}
"Rotate"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ROTATE;							}
"Scale"						{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCALE;							}
"ScrollAnim"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCROLLANIM;						}
"RotateAnim"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ROTATEANIM;						}
"ScaleAnim"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCALEANIM;						}

"WaveXForm"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_WAVEXFORM;						}
"SCROLL_X"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCROLL_X;						}
"SCROLL_Y"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCROLL_Y;						} 
"ROTATE"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ROTATE;							}
"SCALE_X"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCALE_X;							}
"SCALE_Y"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SCALE_Y;							}
"SINE"						{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SINE;							}
"SQUARE"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SQUARE;							}
"SAWTOOTH"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SAWTOOTH;						}
"INVERSE_SAWTOOTH"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INVERSE_SAWTOOTH;				}
"TRIANGLE"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_TRIANGLE;						}
"WaveType"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_WAVETYPE;						}
"XFormType"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_XFORMTYPE;						}
"Phase"						{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_PHASE;							}
"Base"						{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BASE;							}
"Frequency"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_FREQUENCY;						}
"Amplitude"					{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_AMPLITUDE;						}


"ADD"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ADD;					}			
"MODULATE"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_MODULATE;			}
"COLOURBLEND"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_COLOURBLEND;			}	
"ALPHABLEND"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ALPHABLEND;			}
"ONE"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ONE;					}				
"ZERO"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ZERO;				}			
"SRCCOLOUR"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SRCCOLOUR;			}		
"INVSRCCOLOUR"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INVSRCCOLOUR;		}
"SRCALPHA"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SRCALPHA;			}
"INVSRCALPHA"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INVSRCALPHA;			}	
"SRCALPHASAT"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_SRCALPHASAT;				}	
"DESTALPHA"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DESTALPHA;					}
"INVDESTALPHA"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INVDESTALPHA;				}
"DESTCOLOUR"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_DESTCOLOUR;					}
"INVDESTCOLOUR"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INVDESTCOLOUR;				}
"BLENDFACTOR"		{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BLENDFACTOR;				}
"INVBLENDFACTOR"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_INVBLENDFACTOR;				}
"BOTHINVSRCALPHA"	{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_BOTHINVSRCALPHA;			}

"ALWAYS"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_ALWAYS;						}
"NEVER"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_NEVER;						}
"LESS"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_LESS;						}
"LEQUAL"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_LEQUAL;						}
"EQUAL"				{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_EQUAL;						}
"NOTEQUAL"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_NOTEQUAL;					}
"GEQUAL"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_GEQUAL;						}
"GREATER"			{ m_column += strlen(yytext);	return EffectParserBase::TOKEN_GREATER;					}

"{"					{ return EffectParserBase::TOKEN_LEFTCURLYBRACKET;		}
"}"					{ return EffectParserBase::TOKEN_RIGHTCURLYBRACKET;		}
","					{ return EffectParserBase::TOKEN_COMMA;					}
"ENABLED"			{ return EffectParserBase::TOKEN_ENABLED;				}
"DISABLED"			{ return EffectParserBase::TOKEN_DISABLED;				}			

{STRING}			{	
						 //Copy the string without quotes to yytext
						 val->assign ( &yytext[1], strlen(yytext)-2 );
						 
						 return EffectParserBase::TOKEN_STRING;
					}
		
{FLOAT}				{	
						 //Copy the number as a string, we'll convert it in the parser
						 val->assign ( &yytext[0], strlen(yytext));
						 
						 return EffectParserBase::TOKEN_FLOAT;	 
					}		
					
			
{COMMENT}			{ m_column += strlen(yytext); ++m_line;		}
{WSPACE}			{ m_column += strlen(yytext);				}
{LINEBREAK}			{ ++m_line;	m_column = 0;					}




.					{ return EffectParserBase::ERROR_TOKEN;		} /*Other character, error, illegal token*/
<<EOF>>				{ yyterminate();							} /*End of file							 */

%%

