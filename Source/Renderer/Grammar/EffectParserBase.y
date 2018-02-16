%name EffectParserBase
%define LSP_NEEDED
%define ERROR_BODY = 0
%define LEX_BODY = 0
%define STYPE std::string
%define CONSTRUCTOR_PARAM Core::SyntaxTree<Renderer::EEffectNodeType>& tree
%define MEMBERS			  Core::SyntaxTree<Renderer::EEffectNodeType>& m_tree;
%define CONSTRUCTOR_INIT  : m_tree(tree)


%header{
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <malloc.h>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/SyntaxTree.h"
#include "Renderer/EffectSyntaxTreeNodeTypes.h"
#include "Renderer/RendererStateConstants.h"
#include "Renderer/RendererTypes.h"
#include "Renderer/TextureUnit.h"


%}

%{

/* ------------------------------------------------------------------
   Initial code (copied verbatim to the output file)
   ------------------------------------------------------------------ */
  using namespace Renderer;   
 
  
%}

%token ERROR_TOKEN
%token TOKEN_UNKNOWN
%token TOKEN_EFFECT			
%token TOKEN_TECHNIQUE	
%token TOKEN_LODLEVEL	
%token TOKEN_RECEIVESHADOWS	
%token TOKEN_CASTSHADOWS	
%token TOKEN_SORT	
%token TOKEN_SKYDOME
%token TOKEN_NORMAL
%token TOKEN_TRANSPARENT	
%token TOKEN_PASS	
%token TOKEN_AMBIENT
%token TOKEN_DIFFUSE
%token TOKEN_SPECULAR
%token TOKEN_SHININESS
%token TOKEN_EMISSIVE	
%token TOKEN_VERTEXCOLOUR

%token TOKEN_SCENEBLEND
%token TOKEN_BLENDOP
%token TOKEN_ADD			
%token TOKEN_MODULATE	
%token TOKEN_COLOURBLEND	
%token TOKEN_ALPHABLEND
%token TOKEN_ONE				
%token TOKEN_ZERO			
%token TOKEN_SRCCOLOUR		
%token TOKEN_INVSRCCOLOUR	
%token TOKEN_SRCALPHA		
%token TOKEN_INVSRCALPHA		
%token TOKEN_SRCALPHASAT		
%token TOKEN_DESTALPHA		
%token TOKEN_INVDESTALPHA	
%token TOKEN_DESTCOLOUR		
%token TOKEN_INVDESTCOLOUR	
%token TOKEN_BLENDFACTOR		
%token TOKEN_INVBLENDFACTOR	
%token TOKEN_BOTHINVSRCALPHA

%token TOKEN_ALPHATEST

%token TOKEN_CULLINGMODE
%token TOKEN_COUNTERCLOCKWISE
%token TOKEN_CLOCKWISE

%token TOKEN_NORMALISENORMALS
%token TOKEN_LIGHTING
%token TOKEN_MAXLIGHTS

%token TOKEN_ITERATION	
%token TOKEN_POINT		
%token TOKEN_DIRECTIONAL	
%token TOKEN_SPOT	
%token TOKEN_ONCEPERLIGHT
%token TOKEN_ONCE		
	
%token TOKEN_FOGOVERRIDE	
%token TOKEN_FOGTYPE		
%token TOKEN_FOGDENSITY	
%token TOKEN_FOGCOLOUR	
%token TOKEN_FOGSTART	
%token TOKEN_FOGEND		

%token TOKEN_NONE		
%token TOKEN_EXP			
%token TOKEN_EXP2		
%token TOKEN_LINEAR		

%token TOKEN_TEXTUREUNIT			
%token TOKEN_TEXTURE	
%token TOKEN_AUTOGENERATED			
%token TOKEN_1D					
%token TOKEN_2D					
%token TOKEN_CUBEMAP				
%token TOKEN_TEXCOORDSET			
%token TOKEN_ADDRESSINGMODE		
%token TOKEN_WRAP				
%token TOKEN_CLAMP				
%token TOKEN_MIRROR				
%token TOKEN_MIRRORONCE	
%token TOKEN_BORDER		
%token TOKEN_ADDRESSMODE_U		
%token TOKEN_ADDRESSMODE_V		
%token TOKEN_ADDRESSMODE_W		
%token TOKEN_FILTERING			
%token TOKEN_BILINEAR			
%token TOKEN_TRILINEAR			
%token TOKEN_ANISOTROPIC			
%token TOKEN_MAXANISOTROPY		
%token TOKEN_COLOUROP			
%token TOKEN_ALPHAOP				
%token TOKEN_DISABLE				
%token TOKEN_SELECTARG1			
%token TOKEN_SELECTARG2			
%token TOKEN_MODULATE			
%token TOKEN_MODULATE2X			
%token TOKEN_MODULATE4X			
%token TOKEN_ADD					
%token TOKEN_ADDSIGNED			
%token TOKEN_SUBTRACT			
%token TOKEN_ADDSMOOTH			
%token TOKEN_BLENDDIFFUSEALPHA	
%token TOKEN_BLENDTEXTUREALPHA	
%token TOKEN_BLENDFACTORALPHA	
%token TOKEN_BLENDTEXTUREALPHAPM		
%token TOKEN_BLENDCURRENTALPHA		
%token TOKEN_PREMODULATE				
%token TOKEN_MODULATEALPHA_ADDCOLOUR	
%token TOKEN_MODULATECOLOUR_ADDALPHA	
%token TOKEN_DOTPRODUCT3				
%token TOKEN_MULTIPLYADD				
%token TOKEN_LERP	
				
%token TOKEN_CURRENT					
%token TOKEN_TEXTURE					
%token TOKEN_DIFFUSE					
%token TOKEN_SPECULAR				
%token TOKEN_CONSTANT				
%token TOKEN_CONSTANTCOLOUR	

%token TOKEN_TEXCOORDGEN		
%token TOKEN_SPHEREMAP			
%token TOKEN_EYESPACE_REFLECTION
%token TOKEN_EYESPACE_NORMAL	

%token TOKEN_SCROLL					
%token TOKEN_ROTATE					
%token TOKEN_SCALE					
%token TOKEN_SCROLLANIM				
%token TOKEN_ROTATEANIM				
%token TOKEN_SCALEANIM				

%token TOKEN_WAVEXFORM				
%token TOKEN_WAVETYPE
%token TOKEN_XFORMTYPE
%token TOKEN_PHASE
%token TOKEN_BASE	
%token TOKEN_FREQUENCY
%token TOKEN_AMPLITUDE
%token TOKEN_SCROLL_X				
%token TOKEN_SCROLL_Y				
%token TOKEN_ROTATE					
%token TOKEN_SCALE_X					
%token TOKEN_SCALE_Y					
%token TOKEN_SINE					
%token TOKEN_SQUARE					
%token TOKEN_SAWTOOTH				
%token TOKEN_INVERSE_SAWTOOTH		
%token TOKEN_TRIANGLE				

%token TOKEN_COLOURWRITE

%token TOKEN_DEPTHTEST
%token TOKEN_DEPTHWRITE
%token TOKEN_DEPTHFUNC
%token TOKEN_DEPTHBIAS

%token TOKEN_STENCILTEST
%token TOKEN_STENCILWRITEMASK
%token TOKEN_STENCILMASK
%token TOKEN_STENCILPASS
%token TOKEN_STENCILFAIL
%token TOKEN_STENCILZFAIL
%token TOKEN_KEEP		
%token TOKEN_REPLACE		
%token TOKEN_INCRSAT		
%token TOKEN_DECRSAT		
%token TOKEN_INVERT		
%token TOKEN_INCR		
%token TOKEN_DECR	

%token TOKEN_SHADING
%token TOKEN_FLAT
%token TOKEN_GOURAUD	

%token TOKEN_ALWAYS
%token TOKEN_NEVER
%token TOKEN_LESS
%token TOKEN_LEQUAL
%token TOKEN_EQUAL
%token TOKEN_NOTEQUAL
%token TOKEN_GEQUAL
%token TOKEN_GREATER

%token TOKEN_ENABLED
%token TOKEN_DISABLED
%token TOKEN_STRING
%token TOKEN_FLOAT
%token TOKEN_UINT
%token TOKEN_INT
%token TOKEN_COMMA
%token TOKEN_LEFTCURLYBRACKET
%token TOKEN_RIGHTCURLYBRACKET
	

%start effectfile

%%

effectfile
: TOKEN_EFFECT TOKEN_STRING										{	m_tree.AddRootNode( NODETYPE_EFFECT ); 
																	m_tree.AddNode( NODETYPE_STRINGLITERAL, $2 ); }
  TOKEN_LEFTCURLYBRACKET effectblock TOKEN_RIGHTCURLYBRACKET	{   m_tree.EndRootNode(); }
;

effectblock
:	 receiveshadows castshadows techniquelist
;

receiveshadows
: TOKEN_RECEIVESHADOWS						{	m_tree.AddRootNode( NODETYPE_RECEIVESHADOWS ); }
  boolean									{   m_tree.EndRootNode(); }
| /* empty */
;

castshadows
: TOKEN_CASTSHADOWS							{	m_tree.AddRootNode( NODETYPE_CASTSHADOWS ); }
  boolean									{   m_tree.EndRootNode(); }
| /* empty */
;

techniquelist
: techniquelist technique
| technique
;

technique
: TOKEN_TECHNIQUE															{	 m_tree.AddRootNode(NODETYPE_TECHNIQUE); }
  TOKEN_LEFTCURLYBRACKET techniquestatementlist TOKEN_RIGHTCURLYBRACKET		{	 m_tree.EndRootNode(); }
;

techniquestatementlist
: techniquestatementlist techniquestatement
| /* empty */
;

techniquestatement
: sort
| lodlevel
| passlist
;

lodlevel
: TOKEN_LODLEVEL							{	m_tree.AddRootNode( NODETYPE_LODLEVEL );	}
  uintvalue									{   m_tree.EndRootNode( );						}
| /* empty */
;  

sort
: TOKEN_SORT								{	m_tree.AddRootNode( NODETYPE_SORT );		}
  sortmode									{	m_tree.EndRootNode( );						}
| /* empty */
;

sortmode
: TOKEN_SKYDOME								{	m_tree.AddNode( NODETYPE_SKYDOME, SORT_SKYDOME);		}
| TOKEN_NORMAL								{	m_tree.AddNode( NODETYPE_NORMAL,  SORT_NORMAL );		}
| TOKEN_TRANSPARENT							{	m_tree.AddNode( NODETYPE_TRANSPARENT, SORT_TRANSPARENT ); }
;

passlist
: passlist pass
| pass

pass
: TOKEN_PASS														{	m_tree.AddRootNode(NODETYPE_PASS);	}
  TOKEN_LEFTCURLYBRACKET passstatementlist TOKEN_RIGHTCURLYBRACKET	{	m_tree.EndRootNode();				}
;

passstatementlist
: passstatementlist passstatement
| /*empty*/
;

passstatement
: materialsettings
| sort
| sceneblend 
| alphatest
| depthbufferstatement
| stencilstatement
| cullingmode
| shading
| colourwrite
| normalisenormals
| fogstatement
| lighting
| maxlights
| iteration 
| textureunit
;	
	
materialsettings
:	ambient
|	diffuse
|	specular
|	shininess
|	emissive
;

ambient
: TOKEN_AMBIENT					{ m_tree.AddRootNode(NODETYPE_AMBIENT);	}
  materialcolour				{ m_tree.EndRootNode();					}
;

diffuse
: TOKEN_DIFFUSE					{ m_tree.AddRootNode(NODETYPE_DIFFUSE);	}
  materialcolour				{ m_tree.EndRootNode();					}
;

specular
: TOKEN_SPECULAR				{ m_tree.AddRootNode(NODETYPE_SPECULAR); }
  materialcolour				{ m_tree.EndRootNode();					 }
;

shininess
: TOKEN_SHININESS				{ m_tree.AddRootNode(NODETYPE_SHININESS);}
  floatvalue					{ m_tree.EndRootNode();					 }
;

emissive
: TOKEN_EMISSIVE				{ m_tree.AddRootNode(NODETYPE_EMISSIVE); } 
  materialcolour				{ m_tree.EndRootNode();					 }
;

materialcolour
: colour
| TOKEN_VERTEXCOLOUR			{ m_tree.AddNode(NODETYPE_VERTEXCOLOUR); }
;

sceneblend
: TOKEN_SCENEBLEND				{ m_tree.AddRootNode(NODETYPE_SCENEBLEND);	}
	sceneBlendOption			{ m_tree.EndRootNode();						}
;
	
sceneBlendOption
: TOKEN_ADD						{ m_tree.AddNode(NODETYPE_ADD);				}
| TOKEN_MODULATE				{ m_tree.AddNode(NODETYPE_MODULATE);			}
| TOKEN_COLOURBLEND				{ m_tree.AddNode(NODETYPE_COLOURBLEND);		}
| TOKEN_ALPHABLEND				{ m_tree.AddNode(NODETYPE_ALPHABLEND);		}
| blendOp TOKEN_COMMA blendOp
;

blendOp
: TOKEN_ONE						{ m_tree.AddNode(NODETYPE_ONE, BLEND_ONE);							}
| TOKEN_ZERO					{ m_tree.AddNode(NODETYPE_ZERO, BLEND_ZERO);						}
| TOKEN_SRCCOLOUR				{ m_tree.AddNode(NODETYPE_SRCCOLOUR, BLEND_SRCCOLOUR);				}
| TOKEN_INVSRCCOLOUR			{ m_tree.AddNode(NODETYPE_INVSRCCOLOUR, BLEND_INVSRCCOLOUR);		}
| TOKEN_SRCALPHA				{ m_tree.AddNode(NODETYPE_SRCALPHA, BLEND_SRCALPHA);				}
| TOKEN_INVSRCALPHA				{ m_tree.AddNode(NODETYPE_INVSRCALPHA, BLEND_INVSRCALPHA);			}
| TOKEN_SRCALPHASAT				{ m_tree.AddNode(NODETYPE_SRCALPHASAT, BLEND_SRCALPHASAT);			}
| TOKEN_DESTALPHA				{ m_tree.AddNode(NODETYPE_DESTALPHA, BLEND_DESTALPHA);				}
| TOKEN_INVDESTALPHA			{ m_tree.AddNode(NODETYPE_INVDESTALPHA, BLEND_INVDESTALPHA);		}
| TOKEN_DESTCOLOUR				{ m_tree.AddNode(NODETYPE_DESTCOLOUR, BLEND_DESTCOLOUR);			}
| TOKEN_INVDESTCOLOUR			{ m_tree.AddNode(NODETYPE_INVDESTCOLOUR, BLEND_INVDESTCOLOUR);		}
| TOKEN_BLENDFACTOR				{ m_tree.AddNode(NODETYPE_BLENDFACTOR, BLEND_BLENDFACTOR);			}
| TOKEN_INVBLENDFACTOR			{ m_tree.AddNode(NODETYPE_INVBLENDFACTOR, BLEND_INVBLENDFACTOR);	}
| TOKEN_BOTHINVSRCALPHA			{ m_tree.AddNode(NODETYPE_BOTHINVSRCALPHA, BLEND_BOTHINVSRCALPHA);	}
;

alphatest
: TOKEN_ALPHATEST					{ m_tree.AddRootNode(NODETYPE_ALPHATEST);	}
  alphatestvalue					{ m_tree.EndRootNode();						}
;

alphatestvalue
:  disabled
|  cmpfunc TOKEN_COMMA floatvalue
;

depthbufferstatement
: depthtest
| depthfunc
| depthbias
| depthwrite
;

depthtest
: TOKEN_DEPTHTEST				{ m_tree.AddRootNode(NODETYPE_DEPTHTEST);	}
  boolean						{ m_tree.EndRootNode();						}
;

depthfunc
: TOKEN_DEPTHFUNC				{ m_tree.AddRootNode(NODETYPE_DEPTHFUNC);	}
  cmpfunc						{ m_tree.EndRootNode();						}
;

depthbias
: TOKEN_DEPTHBIAS				{ m_tree.AddRootNode(NODETYPE_DEPTHBIAS);	}
  floatvalue					{ m_tree.EndRootNode();						}
;

depthwrite
: TOKEN_DEPTHWRITE				{ m_tree.AddRootNode(NODETYPE_DEPTHWRITE);	}
  boolean						{ m_tree.EndRootNode();						}
;

stencilstatement
: stenciltest
| stencilmask
| stencilwritemask
| stencilpass
| stencilfail
| stencilzfail


stenciltest
:	TOKEN_STENCILTEST			{ m_tree.AddRootNode(NODETYPE_STENCILTEST);		}	
	stenciltestvalue 			{ m_tree.EndRootNode();							}
;

stenciltestvalue
:	disabled
|	cmpfunc TOKEN_COMMA uintvalue
;

stencilmask
: TOKEN_STENCILMASK				{ m_tree.AddRootNode(NODETYPE_STENCILMASK);		}
  uintvalue						{ m_tree.EndRootNode();							}
;

stencilwritemask
: TOKEN_STENCILWRITEMASK		{ m_tree.AddRootNode(NODETYPE_STENCILWRITEMASK);}
  uintvalue						{ m_tree.EndRootNode();							}
;				

stencilpass
: TOKEN_STENCILPASS				{ m_tree.AddRootNode(NODETYPE_STENCILPASS);		}
  stencilop						{ m_tree.EndRootNode();							}
;

stencilfail
: TOKEN_STENCILFAIL				{ m_tree.AddRootNode(NODETYPE_STENCILFAIL);		}
  stencilop						{ m_tree.EndRootNode();							}
;

stencilzfail
: TOKEN_STENCILZFAIL			{ m_tree.AddRootNode(NODETYPE_STENCILZFAIL);	}
  stencilop						{ m_tree.EndRootNode();							}
;

stencilop
: TOKEN_KEEP					{ m_tree.AddNode(NODETYPE_KEEP, STENCILOP_KEEP);		}	
| TOKEN_REPLACE					{ m_tree.AddNode(NODETYPE_REPLACE, STENCILOP_REPLACE);	}	
| TOKEN_INCRSAT					{ m_tree.AddNode(NODETYPE_INCRSAT, STENCILOP_INCRSAT);	}	
| TOKEN_DECRSAT					{ m_tree.AddNode(NODETYPE_DECRSAT, STENCILOP_DECRSAT);	}	
| TOKEN_INVERT					{ m_tree.AddNode(NODETYPE_INVERT, STENCILOP_INVERT);	}	
| TOKEN_INCR					{ m_tree.AddNode(NODETYPE_INCR, STENCILOP_INCR);		}	
| TOKEN_DECR					{ m_tree.AddNode(NODETYPE_DECR, STENCILOP_DECR);		}	
;

cullingmode
: TOKEN_CULLINGMODE				{ m_tree.AddRootNode(NODETYPE_CULLINGMODE);			}
  cullingmodetype				{ m_tree.EndRootNode();								}
;

cullingmodetype
: TOKEN_NONE					{ m_tree.AddNode(NODETYPE_NONE, CULL_NONE);							}
| TOKEN_COUNTERCLOCKWISE		{ m_tree.AddNode(NODETYPE_COUNTERCLOCKWISE, CULL_COUNTERCLOCKWISE);	}
| TOKEN_CLOCKWISE				{ m_tree.AddNode(NODETYPE_CLOCKWISE, CULL_CLOCKWISE);				}
;

normalisenormals
: TOKEN_NORMALISENORMALS		{ m_tree.AddRootNode(NODETYPE_NORMALISENORMALS);	}
  boolean						{ m_tree.EndRootNode();								}
;

lighting
: TOKEN_LIGHTING				{ m_tree.AddRootNode(NODETYPE_LIGHTING);			}
  boolean						{ m_tree.EndRootNode();								}
;

shading
: TOKEN_SHADING					{ m_tree.AddRootNode(NODETYPE_SHADING);				}
  shademode						{ m_tree.EndRootNode();								}
;

shademode
: TOKEN_FLAT					{ m_tree.AddNode(NODETYPE_FLAT, SHADE_FLAT);		}
| TOKEN_GOURAUD					{ m_tree.AddNode(NODETYPE_GOURAUD, SHADE_GOURAUD);	}
;

colourwrite
: TOKEN_COLOURWRITE				{ m_tree.AddRootNode(NODETYPE_COLOURWRITE);			}
  boolean						{ m_tree.EndRootNode();								}
;  
  
maxlights
: TOKEN_MAXLIGHTS				{ m_tree.AddRootNode(NODETYPE_MAXLIGHTS);			}
  uintvalue						{ m_tree.EndRootNode();								}
;

iteration
: TOKEN_ITERATION							{ m_tree.AddRootNode(NODETYPE_ITERATION);			}
  iterationtype TOKEN_COMMA lighttype		{ m_tree.EndRootNode();								}
;
  
iterationtype
: TOKEN_ONCE					{ m_tree.AddNode(NODETYPE_ONCE);					}
|  TOKEN_ONCEPERLIGHT			{ m_tree.AddNode(NODETYPE_ONCEPERLIGHT);			}
  
lighttype
: TOKEN_POINT					{ m_tree.AddNode(NODETYPE_POINT, LIGHT_POINT);					}
| TOKEN_SPOT					{ m_tree.AddNode(NODETYPE_SPOT, LIGHT_SPOT);					}
| TOKEN_DIRECTIONAL				{ m_tree.AddNode(NODETYPE_DIRECTIONAL, LIGHT_DIRECTIONAL);		}
;

fogstatement
: fogoverride
| fogtype
| fogdensity
| fogcolour
| fogstart
| fogend
;

fogoverride
: TOKEN_FOGOVERRIDE				{ m_tree.AddRootNode(NODETYPE_FOGOVERRIDE);			}
  boolean						{ m_tree.EndRootNode();								}
;

fogtype
: TOKEN_FOGTYPE					{ m_tree.AddRootNode(NODETYPE_FOGTYPE);				}
  fogtypesetting				{ m_tree.EndRootNode();								}
;

fogtypesetting
: TOKEN_NONE					{ m_tree.AddNode(NODETYPE_NONE, FOGMODE_NONE);				}
| TOKEN_LINEAR					{ m_tree.AddNode(NODETYPE_LINEAR, FOGMODE_LINEAR);			}
| TOKEN_EXP						{ m_tree.AddNode(NODETYPE_EXP, FOGMODE_EXP);				}
| TOKEN_EXP2					{ m_tree.AddNode(NODETYPE_EXP2, FOGMODE_EXP2);				}
;	
	
fogdensity
: TOKEN_FOGDENSITY				{ m_tree.AddRootNode(NODETYPE_FOGDENSITY);		}
  floatvalue					{ m_tree.EndRootNode();							}
;

fogcolour
: TOKEN_FOGCOLOUR				{ m_tree.AddRootNode(NODETYPE_FOGCOLOUR);		}
  colour						{ m_tree.EndRootNode();							}
;

fogstart
: TOKEN_FOGSTART				{ m_tree.AddRootNode(NODETYPE_FOGSTART);		}
  floatvalue					{ m_tree.EndRootNode();							}
;

fogend
: TOKEN_FOGEND					{ m_tree.AddRootNode(NODETYPE_FOGEND);			}
  floatvalue					{ m_tree.EndRootNode();							}
;	

textureunit
: TOKEN_TEXTUREUNIT				{ m_tree.AddRootNode(NODETYPE_TEXTUREUNIT);			}
  TOKEN_LEFTCURLYBRACKET
  textureunitstatementlist		
  TOKEN_RIGHTCURLYBRACKET		{ m_tree.EndRootNode();								}

textureunitstatementlist
: textureunitstatementlist textureunitstatement
| /* empty */
  
textureunitstatement
: texture optionaltextureunitstatementlist
;

optionaltextureunitstatementlist
: optionaltextureunitstatementlist optionaltextureunitstatement
| /* Empty */
;

optionaltextureunitstatement
: autogenerated
| texcoordset 
| addressingmode 
| filtering 
| maxanisotropy
| colourop  
| alphaop
| constantcolour
| texcoordgen 
| scroll 
| scrollanim
| rotate 
| rotateanim 
| scale
| scaleanim 
| wavexform
;

texture
: TOKEN_TEXTURE						{ m_tree.AddRootNode(NODETYPE_TEXTURE);			}
  texturetype TOKEN_COMMA string	{ m_tree.EndRootNode();							}
;

autogenerated
: TOKEN_AUTOGENERATED				{ m_tree.AddRootNode(NODETYPE_AUTOGENERATED);	}
  boolean							{ m_tree.EndRootNode();							}
;

texturetype
: TOKEN_1D				{ m_tree.AddNode(NODETYPE_TEX1D, TEXTURE_1D);						}
| TOKEN_2D				{ m_tree.AddNode(NODETYPE_TEX2D, TEXTURE_2D );						}
| TOKEN_CUBEMAP			{ m_tree.AddNode(NODETYPE_TEXCUBEMAP, TEXTURE_CUBEMAP);				}
  
texcoordset
: TOKEN_TEXCOORDSET		{ m_tree.AddRootNode(NODETYPE_TEXCOORDSET);		}
  uintvalue				{ m_tree.EndRootNode();							}
;
  
addressingmode
: TOKEN_ADDRESSINGMODE									{ m_tree.AddRootNode(NODETYPE_ADDRESSINGMODE);	}
  addressingmodetype TOKEN_COMMA addressingmodesetting	{ m_tree.EndRootNode();		}
;

addressingmodetype
: TOKEN_ADDRESSMODE_U	{ m_tree.AddNode(NODETYPE_ADDRESSMODE_U, TEX_ADDRESS_U);		}
| TOKEN_ADDRESSMODE_V	{ m_tree.AddNode(NODETYPE_ADDRESSMODE_V, TEX_ADDRESS_V);		}	
| TOKEN_ADDRESSMODE_W	{ m_tree.AddNode(NODETYPE_ADDRESSMODE_W, TEX_ADDRESS_W);		}	
;

addressingmodesetting
: TOKEN_WRAP			{ m_tree.AddNode(NODETYPE_WRAP, TEXADDRESS_WRAP);				}
| TOKEN_CLAMP			{ m_tree.AddNode(NODETYPE_CLAMP, TEXADDRESS_CLAMP);				}
| TOKEN_MIRROR			{ m_tree.AddNode(NODETYPE_MIRROR, TEXADDRESS_MIRROR);			}
| TOKEN_MIRRORONCE		{ m_tree.AddNode(NODETYPE_MIRRORONCE, TEXADDRESS_MIRRORONCE);	}
| TOKEN_BORDER			{ m_tree.AddNode(NODETYPE_BORDER, TEXADDRESS_BORDER);			}
;

filtering
: TOKEN_FILTERING		{ m_tree.AddRootNode(NODETYPE_FILTERING);		}
  filtersetting			{ m_tree.EndRootNode();							}
;

filtersetting
: filtersettingsimple
| filtertype TOKEN_COMMA filtertype TOKEN_COMMA filtertype
;

filtersettingsimple
: TOKEN_NONE			{ m_tree.AddNode(NODETYPE_NONE);		}
| TOKEN_BILINEAR		{ m_tree.AddNode(NODETYPE_BILINEAR);	}
| TOKEN_TRILINEAR		{ m_tree.AddNode(NODETYPE_TRILINEAR);	}
| TOKEN_ANISOTROPIC		{ m_tree.AddNode(NODETYPE_ANISOTROPIC);	}

filtertype
: TOKEN_POINT			{ m_tree.AddNode(NODETYPE_POINT, TEXFILTER_POINT);		}
| TOKEN_LINEAR			{ m_tree.AddNode(NODETYPE_LINEAR, TEXFILTER_LINEAR);		}
| TOKEN_ANISOTROPIC		{ m_tree.AddNode(NODETYPE_ANISOTROPIC, TEXFILTER_ANISOTROPIC);	}

maxanisotropy
: TOKEN_MAXANISOTROPY	{ m_tree.AddRootNode(NODETYPE_MAXANISOTROPY);	}
  uintvalue				{ m_tree.EndRootNode();							}
;

colourop
: TOKEN_COLOUROP												{ m_tree.AddRootNode(NODETYPE_COLOUROP);		}
  colouroperation TOKEN_COMMA colourarg TOKEN_COMMA colourarg	{ m_tree.EndRootNode();							}
;

alphaop
: TOKEN_ALPHAOP													{ m_tree.AddRootNode(NODETYPE_ALPHAOP);			}
  colouroperation TOKEN_COMMA colourarg TOKEN_COMMA colourarg	{ m_tree.EndRootNode();							}
;

constantcolour
: TOKEN_CONSTANTCOLOUR			{ m_tree.AddRootNode(NODETYPE_CONSTANTCOLOUR);			}
  colour						{ m_tree.EndRootNode();									}
;

colouroperation
: TOKEN_DISABLE					{ m_tree.AddNode(NODETYPE_DISABLE, TEXOP_DISABLE);										}	
| TOKEN_SELECTARG1				{ m_tree.AddNode(NODETYPE_SELECTARG1, TEXOP_SELECTARG1);									}	
| TOKEN_SELECTARG2				{ m_tree.AddNode(NODETYPE_SELECTARG2, TEXOP_SELECTARG2);									}	
| TOKEN_MODULATE				{ m_tree.AddNode(NODETYPE_MODULATE, TEXOP_MODULATE);										}	
| TOKEN_MODULATE2X				{ m_tree.AddNode(NODETYPE_MODULATE2X, TEXOP_MODULATE2X);									}	
| TOKEN_MODULATE4X				{ m_tree.AddNode(NODETYPE_MODULATE4X, TEXOP_MODULATE4X);									}	
| TOKEN_ADD						{ m_tree.AddNode(NODETYPE_ADD, TEXOP_ADD);												}	
| TOKEN_ADDSIGNED				{ m_tree.AddNode(NODETYPE_ADDSIGNED, TEXOP_ADDSIGNED);									}	
| TOKEN_SUBTRACT				{ m_tree.AddNode(NODETYPE_SUBTRACT, TEXOP_SUBTRACT);										}	
| TOKEN_ADDSMOOTH				{ m_tree.AddNode(NODETYPE_ADDSMOOTH, TEXOP_ADDSMOOTH);									}	
| TOKEN_BLENDDIFFUSEALPHA		{ m_tree.AddNode(NODETYPE_BLENDDIFFUSEALPHA, TEXOP_BLENDDIFFUSEALPHA	);					}			
| TOKEN_BLENDTEXTUREALPHA		{ m_tree.AddNode(NODETYPE_BLENDTEXTUREALPHA, TEXOP_BLENDTEXTUREALPHA	);					}	
| TOKEN_BLENDFACTORALPHA		{ m_tree.AddNode(NODETYPE_BLENDFACTORALPHA, TEXOP_BLENDFACTORALPHA	);					}
| TOKEN_BLENDTEXTUREALPHAPM		{ m_tree.AddNode(NODETYPE_BLENDTEXTUREALPHAPM, TEXOP_BLENDTEXTUREALPHAPM);				}			
| TOKEN_BLENDCURRENTALPHA		{ m_tree.AddNode(NODETYPE_BLENDCURRENTALPHA, TEXOP_BLENDCURRENTALPHA);					}			
| TOKEN_PREMODULATE				{ m_tree.AddNode(NODETYPE_PREMODULATE, TEXOP_PREMODULATE);								}					
| TOKEN_MODULATEALPHA_ADDCOLOUR	{ m_tree.AddNode(NODETYPE_MODULATEALPHA_ADDCOLOUR, TEXOP_MODULATEALPHA_ADDCOLOUR);		}		
| TOKEN_MODULATECOLOUR_ADDALPHA	{ m_tree.AddNode(NODETYPE_MODULATECOLOUR_ADDALPHA, TEXOP_MODULATECOLOUR_ADDALPHA);		}		
| TOKEN_DOTPRODUCT3				{ m_tree.AddNode(NODETYPE_DOTPRODUCT3, TEXOP_DOTPRODUCT3);								}					
| TOKEN_MULTIPLYADD				{ m_tree.AddNode(NODETYPE_MULTIPLYADD, TEXOP_MULTIPLYADD);								}					
| TOKEN_LERP					{ m_tree.AddNode(NODETYPE_LERP, TEXOP_LERP);												}						
;

colourarg
: TOKEN_CURRENT			{ m_tree.AddNode(NODETYPE_CURRENT, TEXARG_CURRENT);		}			
| TOKEN_TEXTURE			{ m_tree.AddNode(NODETYPE_TEXTURE, TEXARG_TEXTURE);		}			
| TOKEN_DIFFUSE			{ m_tree.AddNode(NODETYPE_DIFFUSE, TEXARG_DIFFUSE);		}			
| TOKEN_SPECULAR		{ m_tree.AddNode(NODETYPE_SPECULAR, TEXARG_SPECULAR);	}		
| TOKEN_CONSTANT		{ m_tree.AddNode(NODETYPE_CONSTANT, TEXARG_CONSTANT);	}		
;

texcoordgen
: TOKEN_TEXCOORDGEN			 { m_tree.AddRootNode(NODETYPE_TEXCOORDGEN);	}
  texcoordgentype			 { m_tree.EndRootNode();						}
;

texcoordgentype
: TOKEN_NONE				 { m_tree.AddNode(NODETYPE_NONE, TEXGEN_NONE);								}
| TOKEN_SPHEREMAP			 { m_tree.AddNode(NODETYPE_SPHEREMAP, TEXGEN_SPHEREMAP);						}
| TOKEN_EYESPACE_REFLECTION	 { m_tree.AddNode(NODETYPE_EYESPACE_REFLECTION, TEXGEN_EYESPACE_REFLECTION);	}
| TOKEN_EYESPACE_NORMAL		 { m_tree.AddNode(NODETYPE_EYESPACE_NORMAL, TEXGEN_EYESPACE_NORMAL);			}
;

scroll
: TOKEN_SCROLL				{ m_tree.AddRootNode(NODETYPE_SCROLL);					}
  vector					{ m_tree.EndRootNode();									}
;
  
rotate
: TOKEN_ROTATE				{ m_tree.AddRootNode(NODETYPE_ROTATE);					}
  floatvalue				{ m_tree.EndRootNode();									}
;
  
scale
: TOKEN_SCALE				{ m_tree.AddRootNode(NODETYPE_SCALE);					}
  vector					{ m_tree.EndRootNode();									}
;
  
scrollanim
: TOKEN_SCROLLANIM			{ m_tree.AddRootNode(NODETYPE_SCROLLANIM);				}
  vector					{ m_tree.EndRootNode();									}
;
  
rotateanim
: TOKEN_ROTATEANIM			{ m_tree.AddRootNode(NODETYPE_ROTATEANIM);				}
  floatvalue				{ m_tree.EndRootNode();									}
;
  
scaleanim
: TOKEN_SCALEANIM			{ m_tree.AddRootNode(NODETYPE_SCALEANIM);				}
  vector					{ m_tree.EndRootNode();									}
;

wavexform
: TOKEN_WAVEXFORM			{ m_tree.AddRootNode(NODETYPE_WAVEXFORM);				}
  TOKEN_LEFTCURLYBRACKET
  wavexformsettinglist
  TOKEN_RIGHTCURLYBRACKET	{ m_tree.EndRootNode();									}
;

wavexformsettinglist
: wavexformsettinglist wavexformsetting
| /* Empty */

wavexformsetting
: wavexformtype 
| wavetype 
| wavephase 
| wavebase 
| waveamplitude 
| wavefrequency
;

wavexformtype
: TOKEN_XFORMTYPE			{ m_tree.AddRootNode(NODETYPE_XFORMTYPE);				}
  wavexformtypesetting			{ m_tree.EndRootNode();									}
;

wavexformtypesetting
: TOKEN_SCROLL_X			{ m_tree.AddNode(NODETYPE_SCROLL_X, XFORM_SCROLL_X);					}
| TOKEN_SCROLL_Y			{ m_tree.AddNode(NODETYPE_SCROLL_Y, XFORM_SCROLL_Y);					}
| TOKEN_ROTATE				{ m_tree.AddNode(NODETYPE_ROTATE, XFORM_ROTATE);						}
| TOKEN_SCALE_X				{ m_tree.AddNode(NODETYPE_SCALE_X, XFORM_SCALE_X);					}
| TOKEN_SCALE_Y				{ m_tree.AddNode(NODETYPE_SCALE_Y, XFORM_SCALE_Y);					}
;

wavetype
: TOKEN_WAVETYPE			{ m_tree.AddRootNode(NODETYPE_WAVETYPE);				}
  wavetypesetting			{ m_tree.EndRootNode();									}
;

wavetypesetting
: TOKEN_SINE				{ m_tree.AddNode(NODETYPE_SINE, WAVE_SINE);							}			
| TOKEN_SQUARE				{ m_tree.AddNode(NODETYPE_SQUARE, WAVE_SQUARE);						}
| TOKEN_SAWTOOTH			{ m_tree.AddNode(NODETYPE_SAWTOOTH, WAVE_SAWTOOTH);					}
| TOKEN_INVERSE_SAWTOOTH	{ m_tree.AddNode(NODETYPE_INVERSE_SAWTOOTH, WAVE_INVERSE_SAWTOOTH);	}
| TOKEN_TRIANGLE			{ m_tree.AddNode(NODETYPE_TRIANGLE, WAVE_TRIANGLE);					}
;

wavebase
: TOKEN_BASE				{ m_tree.AddRootNode(NODETYPE_BASE);					}
  floatvalue				{ m_tree.EndRootNode();									}
;

wavephase
: TOKEN_PHASE				{ m_tree.AddRootNode(NODETYPE_PHASE);					}
  floatvalue				{ m_tree.EndRootNode();									}
;

waveamplitude
: TOKEN_AMPLITUDE			{ m_tree.AddRootNode(NODETYPE_AMPLITUDE);				}
  floatvalue				{ m_tree.EndRootNode();									}
;

wavefrequency				
: TOKEN_FREQUENCY			{ m_tree.AddRootNode(NODETYPE_FREQUENCY);				}								
  floatvalue				{ m_tree.EndRootNode();									}	
;							
							
cmpfunc
: TOKEN_ALWAYS					{ m_tree.AddNode(NODETYPE_ALWAYS, CMP_ALWAYS);				}
| TOKEN_NEVER					{ m_tree.AddNode(NODETYPE_NEVER, CMP_NEVER);				}
| TOKEN_LESS					{ m_tree.AddNode(NODETYPE_LESS, CMP_LESS);					}
| TOKEN_LEQUAL					{ m_tree.AddNode(NODETYPE_LEQUAL, CMP_LEQUAL);				}
| TOKEN_EQUAL					{ m_tree.AddNode(NODETYPE_EQUAL, CMP_EQUAL);				}
| TOKEN_NOTEQUAL				{ m_tree.AddNode(NODETYPE_NOTEQUAL, CMP_NOTEQUAL);			}
| TOKEN_GEQUAL					{ m_tree.AddNode(NODETYPE_GEQUAL, CMP_GEQUAL);				}
| TOKEN_GREATER					{ m_tree.AddNode(NODETYPE_GREATER, CMP_GREATER);			}
;

colour
: floatvalue TOKEN_COMMA floatvalue TOKEN_COMMA floatvalue
| floatvalue TOKEN_COMMA floatvalue TOKEN_COMMA floatvalue TOKEN_COMMA floatvalue
;

vector
: floatvalue TOKEN_COMMA floatvalue TOKEN_COMMA floatvalue
| floatvalue TOKEN_COMMA floatvalue
;

string
: TOKEN_STRING			{ m_tree.AddNode( NODETYPE_STRINGLITERAL, $1 ); }

floatvalue
: TOKEN_FLOAT			{   
							Float value = 0.0f;
						    std::stringstream str($1);
						    str >> value;
						   
						    //std::cout << "Value = " << $1 << std::endl;
						   
							m_tree.AddNode(NODETYPE_FLOATVALUE, boost::any(value) );
						 }
						 
uintvalue
: TOKEN_FLOAT
						{   
							UInt value = 0.0f;
						    std::stringstream str($1);
						    str >> value;
						   
						    //std::cout << "Value = " << $1 << std::endl;
						   
							m_tree.AddNode(NODETYPE_FLOATVALUE, boost::any(value) );
						 }
						 
intvalue
: TOKEN_FLOAT
						{   
							Int value = 0.0f;
						    std::stringstream str($1);
						    str >> value;
						   
						    //std::cout << "Value = " << $1 << std::endl;
						   
							m_tree.AddNode(NODETYPE_UINTVALUE, boost::any(value) );
						 }

boolean
: enabled | disabled
;

enabled
: TOKEN_ENABLED												{ m_tree.AddNode(NODETYPE_BOOLEAN, boost::any(true));	 }
;

disabled
: TOKEN_DISABLED											{ m_tree.AddNode(NODETYPE_BOOLEAN, boost::any(false));	 }
;

%%
