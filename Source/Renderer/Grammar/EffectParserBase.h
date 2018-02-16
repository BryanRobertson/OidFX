#ifndef YY_EffectParserBase_h_included
#define YY_EffectParserBase_h_included

#line 1 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
/* before anything */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else
#endif

#include <stdio.h>

/* #line 15 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 22 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"
#define YY_EffectParserBase_LSP_NEEDED 
#define YY_EffectParserBase_ERROR_BODY  = 0
#define YY_EffectParserBase_LEX_BODY  = 0
#define YY_EffectParserBase_STYPE  std::string
#define YY_EffectParserBase_CONSTRUCTOR_PARAM  Core::SyntaxTree<Renderer::EEffectNodeType>& tree
#define YY_EffectParserBase_MEMBERS 			  Core::SyntaxTree<Renderer::EEffectNodeType>& m_tree;
#define YY_EffectParserBase_CONSTRUCTOR_INIT   : m_tree(tree)
#line 11 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"

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



#line 15 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
 /* %{ and %header{ and %union, during decl */
#ifndef YY_EffectParserBase_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_EffectParserBase_COMPATIBILITY 1
#else
#define  YY_EffectParserBase_COMPATIBILITY 0
#endif
#endif

#if YY_EffectParserBase_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_EffectParserBase_LTYPE
#define YY_EffectParserBase_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_EffectParserBase_STYPE 
#define YY_EffectParserBase_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_EffectParserBase_DEBUG
#define  YY_EffectParserBase_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
#endif
#endif
#ifdef YY_EffectParserBase_STYPE
#ifndef yystype
#define yystype YY_EffectParserBase_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_EffectParserBase_USE_GOTO
#define YY_EffectParserBase_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_EffectParserBase_USE_GOTO
#define YY_EffectParserBase_USE_GOTO 0
#endif

#ifndef YY_EffectParserBase_PURE

/* #line 64 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 99 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"

#line 64 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
/* YY_EffectParserBase_PURE */
#endif

/* #line 66 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 106 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"

#line 66 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
/* prefix */
#ifndef YY_EffectParserBase_DEBUG

/* #line 68 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 113 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"

#line 68 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
/* YY_EffectParserBase_DEBUG */
#endif
#ifndef YY_EffectParserBase_LSP_NEEDED

/* #line 71 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 121 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"

#line 71 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
 /* YY_EffectParserBase_LSP_NEEDED*/
#endif
/* DEFAULT LTYPE*/
#ifdef YY_EffectParserBase_LSP_NEEDED
#ifndef YY_EffectParserBase_LTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YY_EffectParserBase_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
#ifndef YY_EffectParserBase_STYPE
#define YY_EffectParserBase_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_EffectParserBase_PARSE
#define YY_EffectParserBase_PARSE yyparse
#endif
#ifndef YY_EffectParserBase_LEX
#define YY_EffectParserBase_LEX yylex
#endif
#ifndef YY_EffectParserBase_LVAL
#define YY_EffectParserBase_LVAL yylval
#endif
#ifndef YY_EffectParserBase_LLOC
#define YY_EffectParserBase_LLOC yylloc
#endif
#ifndef YY_EffectParserBase_CHAR
#define YY_EffectParserBase_CHAR yychar
#endif
#ifndef YY_EffectParserBase_NERRS
#define YY_EffectParserBase_NERRS yynerrs
#endif
#ifndef YY_EffectParserBase_DEBUG_FLAG
#define YY_EffectParserBase_DEBUG_FLAG yydebug
#endif
#ifndef YY_EffectParserBase_ERROR
#define YY_EffectParserBase_ERROR yyerror
#endif

#ifndef YY_EffectParserBase_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_EffectParserBase_PARSE_PARAM
#ifndef YY_EffectParserBase_PARSE_PARAM_DEF
#define YY_EffectParserBase_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_EffectParserBase_PARSE_PARAM
#define YY_EffectParserBase_PARSE_PARAM void
#endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

#ifndef YY_EffectParserBase_PURE
extern YY_EffectParserBase_STYPE YY_EffectParserBase_LVAL;
#endif


/* #line 144 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 199 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"
#define	ERROR_TOKEN	258
#define	TOKEN_UNKNOWN	259
#define	TOKEN_EFFECT	260
#define	TOKEN_TECHNIQUE	261
#define	TOKEN_LODLEVEL	262
#define	TOKEN_RECEIVESHADOWS	263
#define	TOKEN_CASTSHADOWS	264
#define	TOKEN_SORT	265
#define	TOKEN_SKYDOME	266
#define	TOKEN_NORMAL	267
#define	TOKEN_TRANSPARENT	268
#define	TOKEN_PASS	269
#define	TOKEN_AMBIENT	270
#define	TOKEN_DIFFUSE	271
#define	TOKEN_SPECULAR	272
#define	TOKEN_SHININESS	273
#define	TOKEN_EMISSIVE	274
#define	TOKEN_VERTEXCOLOUR	275
#define	TOKEN_SCENEBLEND	276
#define	TOKEN_BLENDOP	277
#define	TOKEN_ADD	278
#define	TOKEN_MODULATE	279
#define	TOKEN_COLOURBLEND	280
#define	TOKEN_ALPHABLEND	281
#define	TOKEN_ONE	282
#define	TOKEN_ZERO	283
#define	TOKEN_SRCCOLOUR	284
#define	TOKEN_INVSRCCOLOUR	285
#define	TOKEN_SRCALPHA	286
#define	TOKEN_INVSRCALPHA	287
#define	TOKEN_SRCALPHASAT	288
#define	TOKEN_DESTALPHA	289
#define	TOKEN_INVDESTALPHA	290
#define	TOKEN_DESTCOLOUR	291
#define	TOKEN_INVDESTCOLOUR	292
#define	TOKEN_BLENDFACTOR	293
#define	TOKEN_INVBLENDFACTOR	294
#define	TOKEN_BOTHINVSRCALPHA	295
#define	TOKEN_ALPHATEST	296
#define	TOKEN_CULLINGMODE	297
#define	TOKEN_COUNTERCLOCKWISE	298
#define	TOKEN_CLOCKWISE	299
#define	TOKEN_NORMALISENORMALS	300
#define	TOKEN_LIGHTING	301
#define	TOKEN_MAXLIGHTS	302
#define	TOKEN_ITERATION	303
#define	TOKEN_POINT	304
#define	TOKEN_DIRECTIONAL	305
#define	TOKEN_SPOT	306
#define	TOKEN_ONCEPERLIGHT	307
#define	TOKEN_ONCE	308
#define	TOKEN_FOGOVERRIDE	309
#define	TOKEN_FOGTYPE	310
#define	TOKEN_FOGDENSITY	311
#define	TOKEN_FOGCOLOUR	312
#define	TOKEN_FOGSTART	313
#define	TOKEN_FOGEND	314
#define	TOKEN_NONE	315
#define	TOKEN_EXP	316
#define	TOKEN_EXP2	317
#define	TOKEN_LINEAR	318
#define	TOKEN_TEXTUREUNIT	319
#define	TOKEN_TEXTURE	320
#define	TOKEN_AUTOGENERATED	321
#define	TOKEN_1D	322
#define	TOKEN_2D	323
#define	TOKEN_CUBEMAP	324
#define	TOKEN_TEXCOORDSET	325
#define	TOKEN_ADDRESSINGMODE	326
#define	TOKEN_WRAP	327
#define	TOKEN_CLAMP	328
#define	TOKEN_MIRROR	329
#define	TOKEN_MIRRORONCE	330
#define	TOKEN_BORDER	331
#define	TOKEN_ADDRESSMODE_U	332
#define	TOKEN_ADDRESSMODE_V	333
#define	TOKEN_ADDRESSMODE_W	334
#define	TOKEN_FILTERING	335
#define	TOKEN_BILINEAR	336
#define	TOKEN_TRILINEAR	337
#define	TOKEN_ANISOTROPIC	338
#define	TOKEN_MAXANISOTROPY	339
#define	TOKEN_COLOUROP	340
#define	TOKEN_ALPHAOP	341
#define	TOKEN_DISABLE	342
#define	TOKEN_SELECTARG1	343
#define	TOKEN_SELECTARG2	344
#define	TOKEN_MODULATE2X	345
#define	TOKEN_MODULATE4X	346
#define	TOKEN_ADDSIGNED	347
#define	TOKEN_SUBTRACT	348
#define	TOKEN_ADDSMOOTH	349
#define	TOKEN_BLENDDIFFUSEALPHA	350
#define	TOKEN_BLENDTEXTUREALPHA	351
#define	TOKEN_BLENDFACTORALPHA	352
#define	TOKEN_BLENDTEXTUREALPHAPM	353
#define	TOKEN_BLENDCURRENTALPHA	354
#define	TOKEN_PREMODULATE	355
#define	TOKEN_MODULATEALPHA_ADDCOLOUR	356
#define	TOKEN_MODULATECOLOUR_ADDALPHA	357
#define	TOKEN_DOTPRODUCT3	358
#define	TOKEN_MULTIPLYADD	359
#define	TOKEN_LERP	360
#define	TOKEN_CURRENT	361
#define	TOKEN_CONSTANT	362
#define	TOKEN_CONSTANTCOLOUR	363
#define	TOKEN_TEXCOORDGEN	364
#define	TOKEN_SPHEREMAP	365
#define	TOKEN_EYESPACE_REFLECTION	366
#define	TOKEN_EYESPACE_NORMAL	367
#define	TOKEN_SCROLL	368
#define	TOKEN_ROTATE	369
#define	TOKEN_SCALE	370
#define	TOKEN_SCROLLANIM	371
#define	TOKEN_ROTATEANIM	372
#define	TOKEN_SCALEANIM	373
#define	TOKEN_WAVEXFORM	374
#define	TOKEN_WAVETYPE	375
#define	TOKEN_XFORMTYPE	376
#define	TOKEN_PHASE	377
#define	TOKEN_BASE	378
#define	TOKEN_FREQUENCY	379
#define	TOKEN_AMPLITUDE	380
#define	TOKEN_SCROLL_X	381
#define	TOKEN_SCROLL_Y	382
#define	TOKEN_SCALE_X	383
#define	TOKEN_SCALE_Y	384
#define	TOKEN_SINE	385
#define	TOKEN_SQUARE	386
#define	TOKEN_SAWTOOTH	387
#define	TOKEN_INVERSE_SAWTOOTH	388
#define	TOKEN_TRIANGLE	389
#define	TOKEN_COLOURWRITE	390
#define	TOKEN_DEPTHTEST	391
#define	TOKEN_DEPTHWRITE	392
#define	TOKEN_DEPTHFUNC	393
#define	TOKEN_DEPTHBIAS	394
#define	TOKEN_STENCILTEST	395
#define	TOKEN_STENCILWRITEMASK	396
#define	TOKEN_STENCILMASK	397
#define	TOKEN_STENCILPASS	398
#define	TOKEN_STENCILFAIL	399
#define	TOKEN_STENCILZFAIL	400
#define	TOKEN_KEEP	401
#define	TOKEN_REPLACE	402
#define	TOKEN_INCRSAT	403
#define	TOKEN_DECRSAT	404
#define	TOKEN_INVERT	405
#define	TOKEN_INCR	406
#define	TOKEN_DECR	407
#define	TOKEN_SHADING	408
#define	TOKEN_FLAT	409
#define	TOKEN_GOURAUD	410
#define	TOKEN_ALWAYS	411
#define	TOKEN_NEVER	412
#define	TOKEN_LESS	413
#define	TOKEN_LEQUAL	414
#define	TOKEN_EQUAL	415
#define	TOKEN_NOTEQUAL	416
#define	TOKEN_GEQUAL	417
#define	TOKEN_GREATER	418
#define	TOKEN_ENABLED	419
#define	TOKEN_DISABLED	420
#define	TOKEN_STRING	421
#define	TOKEN_FLOAT	422
#define	TOKEN_UINT	423
#define	TOKEN_INT	424
#define	TOKEN_COMMA	425
#define	TOKEN_LEFTCURLYBRACKET	426
#define	TOKEN_RIGHTCURLYBRACKET	427


#line 144 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
#ifndef YY_EffectParserBase_CLASS
#define YY_EffectParserBase_CLASS EffectParserBase
#endif

#ifndef YY_EffectParserBase_INHERIT
#define YY_EffectParserBase_INHERIT
#endif
#ifndef YY_EffectParserBase_MEMBERS
#define YY_EffectParserBase_MEMBERS 
#endif
#ifndef YY_EffectParserBase_LEX_BODY
#define YY_EffectParserBase_LEX_BODY  
#endif
#ifndef YY_EffectParserBase_ERROR_BODY
#define YY_EffectParserBase_ERROR_BODY  
#endif
#ifndef YY_EffectParserBase_CONSTRUCTOR_PARAM
#define YY_EffectParserBase_CONSTRUCTOR_PARAM
#endif
/* choose between enum and const */
#ifndef YY_EffectParserBase_USE_CONST_TOKEN
#define YY_EffectParserBase_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_EffectParserBase_USE_CONST_TOKEN != 0
#ifndef YY_EffectParserBase_ENUM_TOKEN
#define YY_EffectParserBase_ENUM_TOKEN yy_EffectParserBase_enum_token
#endif
#endif

class YY_EffectParserBase_CLASS YY_EffectParserBase_INHERIT
{
public: 
#if YY_EffectParserBase_USE_CONST_TOKEN != 0
/* static const int token ... */

/* #line 183 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 414 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"
static const int ERROR_TOKEN;
static const int TOKEN_UNKNOWN;
static const int TOKEN_EFFECT;
static const int TOKEN_TECHNIQUE;
static const int TOKEN_LODLEVEL;
static const int TOKEN_RECEIVESHADOWS;
static const int TOKEN_CASTSHADOWS;
static const int TOKEN_SORT;
static const int TOKEN_SKYDOME;
static const int TOKEN_NORMAL;
static const int TOKEN_TRANSPARENT;
static const int TOKEN_PASS;
static const int TOKEN_AMBIENT;
static const int TOKEN_DIFFUSE;
static const int TOKEN_SPECULAR;
static const int TOKEN_SHININESS;
static const int TOKEN_EMISSIVE;
static const int TOKEN_VERTEXCOLOUR;
static const int TOKEN_SCENEBLEND;
static const int TOKEN_BLENDOP;
static const int TOKEN_ADD;
static const int TOKEN_MODULATE;
static const int TOKEN_COLOURBLEND;
static const int TOKEN_ALPHABLEND;
static const int TOKEN_ONE;
static const int TOKEN_ZERO;
static const int TOKEN_SRCCOLOUR;
static const int TOKEN_INVSRCCOLOUR;
static const int TOKEN_SRCALPHA;
static const int TOKEN_INVSRCALPHA;
static const int TOKEN_SRCALPHASAT;
static const int TOKEN_DESTALPHA;
static const int TOKEN_INVDESTALPHA;
static const int TOKEN_DESTCOLOUR;
static const int TOKEN_INVDESTCOLOUR;
static const int TOKEN_BLENDFACTOR;
static const int TOKEN_INVBLENDFACTOR;
static const int TOKEN_BOTHINVSRCALPHA;
static const int TOKEN_ALPHATEST;
static const int TOKEN_CULLINGMODE;
static const int TOKEN_COUNTERCLOCKWISE;
static const int TOKEN_CLOCKWISE;
static const int TOKEN_NORMALISENORMALS;
static const int TOKEN_LIGHTING;
static const int TOKEN_MAXLIGHTS;
static const int TOKEN_ITERATION;
static const int TOKEN_POINT;
static const int TOKEN_DIRECTIONAL;
static const int TOKEN_SPOT;
static const int TOKEN_ONCEPERLIGHT;
static const int TOKEN_ONCE;
static const int TOKEN_FOGOVERRIDE;
static const int TOKEN_FOGTYPE;
static const int TOKEN_FOGDENSITY;
static const int TOKEN_FOGCOLOUR;
static const int TOKEN_FOGSTART;
static const int TOKEN_FOGEND;
static const int TOKEN_NONE;
static const int TOKEN_EXP;
static const int TOKEN_EXP2;
static const int TOKEN_LINEAR;
static const int TOKEN_TEXTUREUNIT;
static const int TOKEN_TEXTURE;
static const int TOKEN_AUTOGENERATED;
static const int TOKEN_1D;
static const int TOKEN_2D;
static const int TOKEN_CUBEMAP;
static const int TOKEN_TEXCOORDSET;
static const int TOKEN_ADDRESSINGMODE;
static const int TOKEN_WRAP;
static const int TOKEN_CLAMP;
static const int TOKEN_MIRROR;
static const int TOKEN_MIRRORONCE;
static const int TOKEN_BORDER;
static const int TOKEN_ADDRESSMODE_U;
static const int TOKEN_ADDRESSMODE_V;
static const int TOKEN_ADDRESSMODE_W;
static const int TOKEN_FILTERING;
static const int TOKEN_BILINEAR;
static const int TOKEN_TRILINEAR;
static const int TOKEN_ANISOTROPIC;
static const int TOKEN_MAXANISOTROPY;
static const int TOKEN_COLOUROP;
static const int TOKEN_ALPHAOP;
static const int TOKEN_DISABLE;
static const int TOKEN_SELECTARG1;
static const int TOKEN_SELECTARG2;
static const int TOKEN_MODULATE2X;
static const int TOKEN_MODULATE4X;
static const int TOKEN_ADDSIGNED;
static const int TOKEN_SUBTRACT;
static const int TOKEN_ADDSMOOTH;
static const int TOKEN_BLENDDIFFUSEALPHA;
static const int TOKEN_BLENDTEXTUREALPHA;
static const int TOKEN_BLENDFACTORALPHA;
static const int TOKEN_BLENDTEXTUREALPHAPM;
static const int TOKEN_BLENDCURRENTALPHA;
static const int TOKEN_PREMODULATE;
static const int TOKEN_MODULATEALPHA_ADDCOLOUR;
static const int TOKEN_MODULATECOLOUR_ADDALPHA;
static const int TOKEN_DOTPRODUCT3;
static const int TOKEN_MULTIPLYADD;
static const int TOKEN_LERP;
static const int TOKEN_CURRENT;
static const int TOKEN_CONSTANT;
static const int TOKEN_CONSTANTCOLOUR;
static const int TOKEN_TEXCOORDGEN;
static const int TOKEN_SPHEREMAP;
static const int TOKEN_EYESPACE_REFLECTION;
static const int TOKEN_EYESPACE_NORMAL;
static const int TOKEN_SCROLL;
static const int TOKEN_ROTATE;
static const int TOKEN_SCALE;
static const int TOKEN_SCROLLANIM;
static const int TOKEN_ROTATEANIM;
static const int TOKEN_SCALEANIM;
static const int TOKEN_WAVEXFORM;
static const int TOKEN_WAVETYPE;
static const int TOKEN_XFORMTYPE;
static const int TOKEN_PHASE;
static const int TOKEN_BASE;
static const int TOKEN_FREQUENCY;
static const int TOKEN_AMPLITUDE;
static const int TOKEN_SCROLL_X;
static const int TOKEN_SCROLL_Y;
static const int TOKEN_SCALE_X;
static const int TOKEN_SCALE_Y;
static const int TOKEN_SINE;
static const int TOKEN_SQUARE;
static const int TOKEN_SAWTOOTH;
static const int TOKEN_INVERSE_SAWTOOTH;
static const int TOKEN_TRIANGLE;
static const int TOKEN_COLOURWRITE;
static const int TOKEN_DEPTHTEST;
static const int TOKEN_DEPTHWRITE;
static const int TOKEN_DEPTHFUNC;
static const int TOKEN_DEPTHBIAS;
static const int TOKEN_STENCILTEST;
static const int TOKEN_STENCILWRITEMASK;
static const int TOKEN_STENCILMASK;
static const int TOKEN_STENCILPASS;
static const int TOKEN_STENCILFAIL;
static const int TOKEN_STENCILZFAIL;
static const int TOKEN_KEEP;
static const int TOKEN_REPLACE;
static const int TOKEN_INCRSAT;
static const int TOKEN_DECRSAT;
static const int TOKEN_INVERT;
static const int TOKEN_INCR;
static const int TOKEN_DECR;
static const int TOKEN_SHADING;
static const int TOKEN_FLAT;
static const int TOKEN_GOURAUD;
static const int TOKEN_ALWAYS;
static const int TOKEN_NEVER;
static const int TOKEN_LESS;
static const int TOKEN_LEQUAL;
static const int TOKEN_EQUAL;
static const int TOKEN_NOTEQUAL;
static const int TOKEN_GEQUAL;
static const int TOKEN_GREATER;
static const int TOKEN_ENABLED;
static const int TOKEN_DISABLED;
static const int TOKEN_STRING;
static const int TOKEN_FLOAT;
static const int TOKEN_UINT;
static const int TOKEN_INT;
static const int TOKEN_COMMA;
static const int TOKEN_LEFTCURLYBRACKET;
static const int TOKEN_RIGHTCURLYBRACKET;


#line 183 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
 /* decl const */
#else
enum YY_EffectParserBase_ENUM_TOKEN { YY_EffectParserBase_NULL_TOKEN=0

/* #line 186 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 593 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"
	,ERROR_TOKEN=258
	,TOKEN_UNKNOWN=259
	,TOKEN_EFFECT=260
	,TOKEN_TECHNIQUE=261
	,TOKEN_LODLEVEL=262
	,TOKEN_RECEIVESHADOWS=263
	,TOKEN_CASTSHADOWS=264
	,TOKEN_SORT=265
	,TOKEN_SKYDOME=266
	,TOKEN_NORMAL=267
	,TOKEN_TRANSPARENT=268
	,TOKEN_PASS=269
	,TOKEN_AMBIENT=270
	,TOKEN_DIFFUSE=271
	,TOKEN_SPECULAR=272
	,TOKEN_SHININESS=273
	,TOKEN_EMISSIVE=274
	,TOKEN_VERTEXCOLOUR=275
	,TOKEN_SCENEBLEND=276
	,TOKEN_BLENDOP=277
	,TOKEN_ADD=278
	,TOKEN_MODULATE=279
	,TOKEN_COLOURBLEND=280
	,TOKEN_ALPHABLEND=281
	,TOKEN_ONE=282
	,TOKEN_ZERO=283
	,TOKEN_SRCCOLOUR=284
	,TOKEN_INVSRCCOLOUR=285
	,TOKEN_SRCALPHA=286
	,TOKEN_INVSRCALPHA=287
	,TOKEN_SRCALPHASAT=288
	,TOKEN_DESTALPHA=289
	,TOKEN_INVDESTALPHA=290
	,TOKEN_DESTCOLOUR=291
	,TOKEN_INVDESTCOLOUR=292
	,TOKEN_BLENDFACTOR=293
	,TOKEN_INVBLENDFACTOR=294
	,TOKEN_BOTHINVSRCALPHA=295
	,TOKEN_ALPHATEST=296
	,TOKEN_CULLINGMODE=297
	,TOKEN_COUNTERCLOCKWISE=298
	,TOKEN_CLOCKWISE=299
	,TOKEN_NORMALISENORMALS=300
	,TOKEN_LIGHTING=301
	,TOKEN_MAXLIGHTS=302
	,TOKEN_ITERATION=303
	,TOKEN_POINT=304
	,TOKEN_DIRECTIONAL=305
	,TOKEN_SPOT=306
	,TOKEN_ONCEPERLIGHT=307
	,TOKEN_ONCE=308
	,TOKEN_FOGOVERRIDE=309
	,TOKEN_FOGTYPE=310
	,TOKEN_FOGDENSITY=311
	,TOKEN_FOGCOLOUR=312
	,TOKEN_FOGSTART=313
	,TOKEN_FOGEND=314
	,TOKEN_NONE=315
	,TOKEN_EXP=316
	,TOKEN_EXP2=317
	,TOKEN_LINEAR=318
	,TOKEN_TEXTUREUNIT=319
	,TOKEN_TEXTURE=320
	,TOKEN_AUTOGENERATED=321
	,TOKEN_1D=322
	,TOKEN_2D=323
	,TOKEN_CUBEMAP=324
	,TOKEN_TEXCOORDSET=325
	,TOKEN_ADDRESSINGMODE=326
	,TOKEN_WRAP=327
	,TOKEN_CLAMP=328
	,TOKEN_MIRROR=329
	,TOKEN_MIRRORONCE=330
	,TOKEN_BORDER=331
	,TOKEN_ADDRESSMODE_U=332
	,TOKEN_ADDRESSMODE_V=333
	,TOKEN_ADDRESSMODE_W=334
	,TOKEN_FILTERING=335
	,TOKEN_BILINEAR=336
	,TOKEN_TRILINEAR=337
	,TOKEN_ANISOTROPIC=338
	,TOKEN_MAXANISOTROPY=339
	,TOKEN_COLOUROP=340
	,TOKEN_ALPHAOP=341
	,TOKEN_DISABLE=342
	,TOKEN_SELECTARG1=343
	,TOKEN_SELECTARG2=344
	,TOKEN_MODULATE2X=345
	,TOKEN_MODULATE4X=346
	,TOKEN_ADDSIGNED=347
	,TOKEN_SUBTRACT=348
	,TOKEN_ADDSMOOTH=349
	,TOKEN_BLENDDIFFUSEALPHA=350
	,TOKEN_BLENDTEXTUREALPHA=351
	,TOKEN_BLENDFACTORALPHA=352
	,TOKEN_BLENDTEXTUREALPHAPM=353
	,TOKEN_BLENDCURRENTALPHA=354
	,TOKEN_PREMODULATE=355
	,TOKEN_MODULATEALPHA_ADDCOLOUR=356
	,TOKEN_MODULATECOLOUR_ADDALPHA=357
	,TOKEN_DOTPRODUCT3=358
	,TOKEN_MULTIPLYADD=359
	,TOKEN_LERP=360
	,TOKEN_CURRENT=361
	,TOKEN_CONSTANT=362
	,TOKEN_CONSTANTCOLOUR=363
	,TOKEN_TEXCOORDGEN=364
	,TOKEN_SPHEREMAP=365
	,TOKEN_EYESPACE_REFLECTION=366
	,TOKEN_EYESPACE_NORMAL=367
	,TOKEN_SCROLL=368
	,TOKEN_ROTATE=369
	,TOKEN_SCALE=370
	,TOKEN_SCROLLANIM=371
	,TOKEN_ROTATEANIM=372
	,TOKEN_SCALEANIM=373
	,TOKEN_WAVEXFORM=374
	,TOKEN_WAVETYPE=375
	,TOKEN_XFORMTYPE=376
	,TOKEN_PHASE=377
	,TOKEN_BASE=378
	,TOKEN_FREQUENCY=379
	,TOKEN_AMPLITUDE=380
	,TOKEN_SCROLL_X=381
	,TOKEN_SCROLL_Y=382
	,TOKEN_SCALE_X=383
	,TOKEN_SCALE_Y=384
	,TOKEN_SINE=385
	,TOKEN_SQUARE=386
	,TOKEN_SAWTOOTH=387
	,TOKEN_INVERSE_SAWTOOTH=388
	,TOKEN_TRIANGLE=389
	,TOKEN_COLOURWRITE=390
	,TOKEN_DEPTHTEST=391
	,TOKEN_DEPTHWRITE=392
	,TOKEN_DEPTHFUNC=393
	,TOKEN_DEPTHBIAS=394
	,TOKEN_STENCILTEST=395
	,TOKEN_STENCILWRITEMASK=396
	,TOKEN_STENCILMASK=397
	,TOKEN_STENCILPASS=398
	,TOKEN_STENCILFAIL=399
	,TOKEN_STENCILZFAIL=400
	,TOKEN_KEEP=401
	,TOKEN_REPLACE=402
	,TOKEN_INCRSAT=403
	,TOKEN_DECRSAT=404
	,TOKEN_INVERT=405
	,TOKEN_INCR=406
	,TOKEN_DECR=407
	,TOKEN_SHADING=408
	,TOKEN_FLAT=409
	,TOKEN_GOURAUD=410
	,TOKEN_ALWAYS=411
	,TOKEN_NEVER=412
	,TOKEN_LESS=413
	,TOKEN_LEQUAL=414
	,TOKEN_EQUAL=415
	,TOKEN_NOTEQUAL=416
	,TOKEN_GEQUAL=417
	,TOKEN_GREATER=418
	,TOKEN_ENABLED=419
	,TOKEN_DISABLED=420
	,TOKEN_STRING=421
	,TOKEN_FLOAT=422
	,TOKEN_UINT=423
	,TOKEN_INT=424
	,TOKEN_COMMA=425
	,TOKEN_LEFTCURLYBRACKET=426
	,TOKEN_RIGHTCURLYBRACKET=427


#line 186 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_EffectParserBase_PARSE(YY_EffectParserBase_PARSE_PARAM);
 virtual void YY_EffectParserBase_ERROR(char *msg) YY_EffectParserBase_ERROR_BODY;
#ifdef YY_EffectParserBase_PURE
#ifdef YY_EffectParserBase_LSP_NEEDED
 virtual int  YY_EffectParserBase_LEX(YY_EffectParserBase_STYPE *YY_EffectParserBase_LVAL,YY_EffectParserBase_LTYPE *YY_EffectParserBase_LLOC) YY_EffectParserBase_LEX_BODY;
#else
 virtual int  YY_EffectParserBase_LEX(YY_EffectParserBase_STYPE *YY_EffectParserBase_LVAL) YY_EffectParserBase_LEX_BODY;
#endif
#else
 virtual int YY_EffectParserBase_LEX() YY_EffectParserBase_LEX_BODY;
 YY_EffectParserBase_STYPE YY_EffectParserBase_LVAL;
#ifdef YY_EffectParserBase_LSP_NEEDED
 YY_EffectParserBase_LTYPE YY_EffectParserBase_LLOC;
#endif
 int YY_EffectParserBase_NERRS;
 int YY_EffectParserBase_CHAR;
#endif
#if YY_EffectParserBase_DEBUG != 0
public:
 int YY_EffectParserBase_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_EffectParserBase_CLASS(YY_EffectParserBase_CONSTRUCTOR_PARAM);
public:
 YY_EffectParserBase_MEMBERS 
};
/* other declare folow */
#endif


#if YY_EffectParserBase_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_EffectParserBase_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_EffectParserBase_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_EffectParserBase_DEBUG 
#define YYDEBUG YY_EffectParserBase_DEBUG
#endif
#endif

#endif
/* END */

/* #line 237 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.h" */
#line 820 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.h"
#endif
