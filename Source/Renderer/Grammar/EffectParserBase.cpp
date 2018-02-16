#define YY_EffectParserBase_h_included

/*  A Bison++ parser, made from c:\Documents and Settings\Bryan\My Documents\PerforceWorkspace\OidFX\Source\Renderer\Grammar\EffectParserBase.y  */

 /* with Bison++ version bison++ Version 1.21-8, adapted from GNU bison by coetmeur@icdc.fr
  */


#line 1 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* HEADER SECTION */
#if defined( _MSDOS ) || defined(MSDOS) || defined(__MSDOS__) 
#define __MSDOS_AND_ALIKE
#endif
#if defined(WIN32) && defined(_MSC_VER)
#define __HAVE_NO_ALLOCA
#define __MSDOS_AND_ALIKE
#endif

#ifndef alloca
#if defined( __GNUC__)
#define alloca __builtin_alloca

#elif (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)  || defined (__sgi)
#include <alloca.h>

#elif defined (__MSDOS_AND_ALIKE)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif

#elif defined(_AIX)
#include <malloc.h>
#pragma alloca

#elif defined(__hpux)
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */

#endif /* not _AIX  not MSDOS, or __TURBOC__ or _AIX, not sparc.  */
#endif /* alloca not defined.  */
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
#ifndef __STDC__
#define const
#endif
#endif
#include <stdio.h>
#define YYBISON 1  

/* #line 73 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 85 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"
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


#line 28 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"


/* ------------------------------------------------------------------
   Initial code (copied verbatim to the output file)
   ------------------------------------------------------------------ */
  using namespace Renderer;   
 
  

#line 73 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
/* %{ and %header{ and %union, during decl */
#define YY_EffectParserBase_BISON 1
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
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_EffectParserBase_STYPE 
#define YY_EffectParserBase_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_EffectParserBase_DEBUG
#define  YY_EffectParserBase_DEBUG YYDEBUG
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

/* #line 117 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 166 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"

#line 117 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
/*  YY_EffectParserBase_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 121 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 175 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"

#line 121 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
/* prefix */
#ifndef YY_EffectParserBase_DEBUG

/* #line 123 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 182 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"

#line 123 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
/* YY_EffectParserBase_DEBUG */
#endif


#ifndef YY_EffectParserBase_LSP_NEEDED

/* #line 128 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 192 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"

#line 128 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
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
      /* We used to use `unsigned long' as YY_EffectParserBase_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

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
#if YY_EffectParserBase_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_EffectParserBase_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_EffectParserBase_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_EffectParserBase_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_EffectParserBase_PURE
#ifndef YYPURE
#define YYPURE YY_EffectParserBase_PURE
#endif
#endif
#ifdef YY_EffectParserBase_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_EffectParserBase_DEBUG 
#endif
#endif
#ifndef YY_EffectParserBase_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_EffectParserBase_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_EffectParserBase_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_EffectParserBase_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */

/* #line 236 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 305 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"
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


#line 236 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
 /* #defines tokens */
#else
/* CLASS */
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
#ifndef YY_EffectParserBase_CONSTRUCTOR_CODE
#define YY_EffectParserBase_CONSTRUCTOR_CODE
#endif
#ifndef YY_EffectParserBase_CONSTRUCTOR_INIT
#define YY_EffectParserBase_CONSTRUCTOR_INIT
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

/* #line 280 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 525 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"
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


#line 280 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
 /* decl const */
#else
enum YY_EffectParserBase_ENUM_TOKEN { YY_EffectParserBase_NULL_TOKEN=0

/* #line 283 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 704 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"
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


#line 283 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_EffectParserBase_PARSE (YY_EffectParserBase_PARSE_PARAM);
 virtual void YY_EffectParserBase_ERROR(char *msg) YY_EffectParserBase_ERROR_BODY;
#ifdef YY_EffectParserBase_PURE
#ifdef YY_EffectParserBase_LSP_NEEDED
 virtual int  YY_EffectParserBase_LEX (YY_EffectParserBase_STYPE *YY_EffectParserBase_LVAL,YY_EffectParserBase_LTYPE *YY_EffectParserBase_LLOC) YY_EffectParserBase_LEX_BODY;
#else
 virtual int  YY_EffectParserBase_LEX (YY_EffectParserBase_STYPE *YY_EffectParserBase_LVAL) YY_EffectParserBase_LEX_BODY;
#endif
#else
 virtual int YY_EffectParserBase_LEX() YY_EffectParserBase_LEX_BODY;
 YY_EffectParserBase_STYPE YY_EffectParserBase_LVAL;
#ifdef YY_EffectParserBase_LSP_NEEDED
 YY_EffectParserBase_LTYPE YY_EffectParserBase_LLOC;
#endif
 int   YY_EffectParserBase_NERRS;
 int    YY_EffectParserBase_CHAR;
#endif
#if YY_EffectParserBase_DEBUG != 0
 int YY_EffectParserBase_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_EffectParserBase_CLASS(YY_EffectParserBase_CONSTRUCTOR_PARAM);
public:
 YY_EffectParserBase_MEMBERS 
};
/* other declare folow */
#if YY_EffectParserBase_USE_CONST_TOKEN != 0

/* #line 314 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 911 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"
const int YY_EffectParserBase_CLASS::ERROR_TOKEN=258;
const int YY_EffectParserBase_CLASS::TOKEN_UNKNOWN=259;
const int YY_EffectParserBase_CLASS::TOKEN_EFFECT=260;
const int YY_EffectParserBase_CLASS::TOKEN_TECHNIQUE=261;
const int YY_EffectParserBase_CLASS::TOKEN_LODLEVEL=262;
const int YY_EffectParserBase_CLASS::TOKEN_RECEIVESHADOWS=263;
const int YY_EffectParserBase_CLASS::TOKEN_CASTSHADOWS=264;
const int YY_EffectParserBase_CLASS::TOKEN_SORT=265;
const int YY_EffectParserBase_CLASS::TOKEN_SKYDOME=266;
const int YY_EffectParserBase_CLASS::TOKEN_NORMAL=267;
const int YY_EffectParserBase_CLASS::TOKEN_TRANSPARENT=268;
const int YY_EffectParserBase_CLASS::TOKEN_PASS=269;
const int YY_EffectParserBase_CLASS::TOKEN_AMBIENT=270;
const int YY_EffectParserBase_CLASS::TOKEN_DIFFUSE=271;
const int YY_EffectParserBase_CLASS::TOKEN_SPECULAR=272;
const int YY_EffectParserBase_CLASS::TOKEN_SHININESS=273;
const int YY_EffectParserBase_CLASS::TOKEN_EMISSIVE=274;
const int YY_EffectParserBase_CLASS::TOKEN_VERTEXCOLOUR=275;
const int YY_EffectParserBase_CLASS::TOKEN_SCENEBLEND=276;
const int YY_EffectParserBase_CLASS::TOKEN_BLENDOP=277;
const int YY_EffectParserBase_CLASS::TOKEN_ADD=278;
const int YY_EffectParserBase_CLASS::TOKEN_MODULATE=279;
const int YY_EffectParserBase_CLASS::TOKEN_COLOURBLEND=280;
const int YY_EffectParserBase_CLASS::TOKEN_ALPHABLEND=281;
const int YY_EffectParserBase_CLASS::TOKEN_ONE=282;
const int YY_EffectParserBase_CLASS::TOKEN_ZERO=283;
const int YY_EffectParserBase_CLASS::TOKEN_SRCCOLOUR=284;
const int YY_EffectParserBase_CLASS::TOKEN_INVSRCCOLOUR=285;
const int YY_EffectParserBase_CLASS::TOKEN_SRCALPHA=286;
const int YY_EffectParserBase_CLASS::TOKEN_INVSRCALPHA=287;
const int YY_EffectParserBase_CLASS::TOKEN_SRCALPHASAT=288;
const int YY_EffectParserBase_CLASS::TOKEN_DESTALPHA=289;
const int YY_EffectParserBase_CLASS::TOKEN_INVDESTALPHA=290;
const int YY_EffectParserBase_CLASS::TOKEN_DESTCOLOUR=291;
const int YY_EffectParserBase_CLASS::TOKEN_INVDESTCOLOUR=292;
const int YY_EffectParserBase_CLASS::TOKEN_BLENDFACTOR=293;
const int YY_EffectParserBase_CLASS::TOKEN_INVBLENDFACTOR=294;
const int YY_EffectParserBase_CLASS::TOKEN_BOTHINVSRCALPHA=295;
const int YY_EffectParserBase_CLASS::TOKEN_ALPHATEST=296;
const int YY_EffectParserBase_CLASS::TOKEN_CULLINGMODE=297;
const int YY_EffectParserBase_CLASS::TOKEN_COUNTERCLOCKWISE=298;
const int YY_EffectParserBase_CLASS::TOKEN_CLOCKWISE=299;
const int YY_EffectParserBase_CLASS::TOKEN_NORMALISENORMALS=300;
const int YY_EffectParserBase_CLASS::TOKEN_LIGHTING=301;
const int YY_EffectParserBase_CLASS::TOKEN_MAXLIGHTS=302;
const int YY_EffectParserBase_CLASS::TOKEN_ITERATION=303;
const int YY_EffectParserBase_CLASS::TOKEN_POINT=304;
const int YY_EffectParserBase_CLASS::TOKEN_DIRECTIONAL=305;
const int YY_EffectParserBase_CLASS::TOKEN_SPOT=306;
const int YY_EffectParserBase_CLASS::TOKEN_ONCEPERLIGHT=307;
const int YY_EffectParserBase_CLASS::TOKEN_ONCE=308;
const int YY_EffectParserBase_CLASS::TOKEN_FOGOVERRIDE=309;
const int YY_EffectParserBase_CLASS::TOKEN_FOGTYPE=310;
const int YY_EffectParserBase_CLASS::TOKEN_FOGDENSITY=311;
const int YY_EffectParserBase_CLASS::TOKEN_FOGCOLOUR=312;
const int YY_EffectParserBase_CLASS::TOKEN_FOGSTART=313;
const int YY_EffectParserBase_CLASS::TOKEN_FOGEND=314;
const int YY_EffectParserBase_CLASS::TOKEN_NONE=315;
const int YY_EffectParserBase_CLASS::TOKEN_EXP=316;
const int YY_EffectParserBase_CLASS::TOKEN_EXP2=317;
const int YY_EffectParserBase_CLASS::TOKEN_LINEAR=318;
const int YY_EffectParserBase_CLASS::TOKEN_TEXTUREUNIT=319;
const int YY_EffectParserBase_CLASS::TOKEN_TEXTURE=320;
const int YY_EffectParserBase_CLASS::TOKEN_AUTOGENERATED=321;
const int YY_EffectParserBase_CLASS::TOKEN_1D=322;
const int YY_EffectParserBase_CLASS::TOKEN_2D=323;
const int YY_EffectParserBase_CLASS::TOKEN_CUBEMAP=324;
const int YY_EffectParserBase_CLASS::TOKEN_TEXCOORDSET=325;
const int YY_EffectParserBase_CLASS::TOKEN_ADDRESSINGMODE=326;
const int YY_EffectParserBase_CLASS::TOKEN_WRAP=327;
const int YY_EffectParserBase_CLASS::TOKEN_CLAMP=328;
const int YY_EffectParserBase_CLASS::TOKEN_MIRROR=329;
const int YY_EffectParserBase_CLASS::TOKEN_MIRRORONCE=330;
const int YY_EffectParserBase_CLASS::TOKEN_BORDER=331;
const int YY_EffectParserBase_CLASS::TOKEN_ADDRESSMODE_U=332;
const int YY_EffectParserBase_CLASS::TOKEN_ADDRESSMODE_V=333;
const int YY_EffectParserBase_CLASS::TOKEN_ADDRESSMODE_W=334;
const int YY_EffectParserBase_CLASS::TOKEN_FILTERING=335;
const int YY_EffectParserBase_CLASS::TOKEN_BILINEAR=336;
const int YY_EffectParserBase_CLASS::TOKEN_TRILINEAR=337;
const int YY_EffectParserBase_CLASS::TOKEN_ANISOTROPIC=338;
const int YY_EffectParserBase_CLASS::TOKEN_MAXANISOTROPY=339;
const int YY_EffectParserBase_CLASS::TOKEN_COLOUROP=340;
const int YY_EffectParserBase_CLASS::TOKEN_ALPHAOP=341;
const int YY_EffectParserBase_CLASS::TOKEN_DISABLE=342;
const int YY_EffectParserBase_CLASS::TOKEN_SELECTARG1=343;
const int YY_EffectParserBase_CLASS::TOKEN_SELECTARG2=344;
const int YY_EffectParserBase_CLASS::TOKEN_MODULATE2X=345;
const int YY_EffectParserBase_CLASS::TOKEN_MODULATE4X=346;
const int YY_EffectParserBase_CLASS::TOKEN_ADDSIGNED=347;
const int YY_EffectParserBase_CLASS::TOKEN_SUBTRACT=348;
const int YY_EffectParserBase_CLASS::TOKEN_ADDSMOOTH=349;
const int YY_EffectParserBase_CLASS::TOKEN_BLENDDIFFUSEALPHA=350;
const int YY_EffectParserBase_CLASS::TOKEN_BLENDTEXTUREALPHA=351;
const int YY_EffectParserBase_CLASS::TOKEN_BLENDFACTORALPHA=352;
const int YY_EffectParserBase_CLASS::TOKEN_BLENDTEXTUREALPHAPM=353;
const int YY_EffectParserBase_CLASS::TOKEN_BLENDCURRENTALPHA=354;
const int YY_EffectParserBase_CLASS::TOKEN_PREMODULATE=355;
const int YY_EffectParserBase_CLASS::TOKEN_MODULATEALPHA_ADDCOLOUR=356;
const int YY_EffectParserBase_CLASS::TOKEN_MODULATECOLOUR_ADDALPHA=357;
const int YY_EffectParserBase_CLASS::TOKEN_DOTPRODUCT3=358;
const int YY_EffectParserBase_CLASS::TOKEN_MULTIPLYADD=359;
const int YY_EffectParserBase_CLASS::TOKEN_LERP=360;
const int YY_EffectParserBase_CLASS::TOKEN_CURRENT=361;
const int YY_EffectParserBase_CLASS::TOKEN_CONSTANT=362;
const int YY_EffectParserBase_CLASS::TOKEN_CONSTANTCOLOUR=363;
const int YY_EffectParserBase_CLASS::TOKEN_TEXCOORDGEN=364;
const int YY_EffectParserBase_CLASS::TOKEN_SPHEREMAP=365;
const int YY_EffectParserBase_CLASS::TOKEN_EYESPACE_REFLECTION=366;
const int YY_EffectParserBase_CLASS::TOKEN_EYESPACE_NORMAL=367;
const int YY_EffectParserBase_CLASS::TOKEN_SCROLL=368;
const int YY_EffectParserBase_CLASS::TOKEN_ROTATE=369;
const int YY_EffectParserBase_CLASS::TOKEN_SCALE=370;
const int YY_EffectParserBase_CLASS::TOKEN_SCROLLANIM=371;
const int YY_EffectParserBase_CLASS::TOKEN_ROTATEANIM=372;
const int YY_EffectParserBase_CLASS::TOKEN_SCALEANIM=373;
const int YY_EffectParserBase_CLASS::TOKEN_WAVEXFORM=374;
const int YY_EffectParserBase_CLASS::TOKEN_WAVETYPE=375;
const int YY_EffectParserBase_CLASS::TOKEN_XFORMTYPE=376;
const int YY_EffectParserBase_CLASS::TOKEN_PHASE=377;
const int YY_EffectParserBase_CLASS::TOKEN_BASE=378;
const int YY_EffectParserBase_CLASS::TOKEN_FREQUENCY=379;
const int YY_EffectParserBase_CLASS::TOKEN_AMPLITUDE=380;
const int YY_EffectParserBase_CLASS::TOKEN_SCROLL_X=381;
const int YY_EffectParserBase_CLASS::TOKEN_SCROLL_Y=382;
const int YY_EffectParserBase_CLASS::TOKEN_SCALE_X=383;
const int YY_EffectParserBase_CLASS::TOKEN_SCALE_Y=384;
const int YY_EffectParserBase_CLASS::TOKEN_SINE=385;
const int YY_EffectParserBase_CLASS::TOKEN_SQUARE=386;
const int YY_EffectParserBase_CLASS::TOKEN_SAWTOOTH=387;
const int YY_EffectParserBase_CLASS::TOKEN_INVERSE_SAWTOOTH=388;
const int YY_EffectParserBase_CLASS::TOKEN_TRIANGLE=389;
const int YY_EffectParserBase_CLASS::TOKEN_COLOURWRITE=390;
const int YY_EffectParserBase_CLASS::TOKEN_DEPTHTEST=391;
const int YY_EffectParserBase_CLASS::TOKEN_DEPTHWRITE=392;
const int YY_EffectParserBase_CLASS::TOKEN_DEPTHFUNC=393;
const int YY_EffectParserBase_CLASS::TOKEN_DEPTHBIAS=394;
const int YY_EffectParserBase_CLASS::TOKEN_STENCILTEST=395;
const int YY_EffectParserBase_CLASS::TOKEN_STENCILWRITEMASK=396;
const int YY_EffectParserBase_CLASS::TOKEN_STENCILMASK=397;
const int YY_EffectParserBase_CLASS::TOKEN_STENCILPASS=398;
const int YY_EffectParserBase_CLASS::TOKEN_STENCILFAIL=399;
const int YY_EffectParserBase_CLASS::TOKEN_STENCILZFAIL=400;
const int YY_EffectParserBase_CLASS::TOKEN_KEEP=401;
const int YY_EffectParserBase_CLASS::TOKEN_REPLACE=402;
const int YY_EffectParserBase_CLASS::TOKEN_INCRSAT=403;
const int YY_EffectParserBase_CLASS::TOKEN_DECRSAT=404;
const int YY_EffectParserBase_CLASS::TOKEN_INVERT=405;
const int YY_EffectParserBase_CLASS::TOKEN_INCR=406;
const int YY_EffectParserBase_CLASS::TOKEN_DECR=407;
const int YY_EffectParserBase_CLASS::TOKEN_SHADING=408;
const int YY_EffectParserBase_CLASS::TOKEN_FLAT=409;
const int YY_EffectParserBase_CLASS::TOKEN_GOURAUD=410;
const int YY_EffectParserBase_CLASS::TOKEN_ALWAYS=411;
const int YY_EffectParserBase_CLASS::TOKEN_NEVER=412;
const int YY_EffectParserBase_CLASS::TOKEN_LESS=413;
const int YY_EffectParserBase_CLASS::TOKEN_LEQUAL=414;
const int YY_EffectParserBase_CLASS::TOKEN_EQUAL=415;
const int YY_EffectParserBase_CLASS::TOKEN_NOTEQUAL=416;
const int YY_EffectParserBase_CLASS::TOKEN_GEQUAL=417;
const int YY_EffectParserBase_CLASS::TOKEN_GREATER=418;
const int YY_EffectParserBase_CLASS::TOKEN_ENABLED=419;
const int YY_EffectParserBase_CLASS::TOKEN_DISABLED=420;
const int YY_EffectParserBase_CLASS::TOKEN_STRING=421;
const int YY_EffectParserBase_CLASS::TOKEN_FLOAT=422;
const int YY_EffectParserBase_CLASS::TOKEN_UINT=423;
const int YY_EffectParserBase_CLASS::TOKEN_INT=424;
const int YY_EffectParserBase_CLASS::TOKEN_COMMA=425;
const int YY_EffectParserBase_CLASS::TOKEN_LEFTCURLYBRACKET=426;
const int YY_EffectParserBase_CLASS::TOKEN_RIGHTCURLYBRACKET=427;


#line 314 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
 /* const YY_EffectParserBase_CLASS::token */
#endif
/*apres const  */
YY_EffectParserBase_CLASS::YY_EffectParserBase_CLASS(YY_EffectParserBase_CONSTRUCTOR_PARAM) YY_EffectParserBase_CONSTRUCTOR_INIT
{
#if YY_EffectParserBase_DEBUG != 0
YY_EffectParserBase_DEBUG_FLAG=0;
#endif
YY_EffectParserBase_CONSTRUCTOR_CODE;
};
#endif

/* #line 325 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 1098 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"


#define	YYFINAL		432
#define	YYFLAG		32768
#define	YYNTBASE	173

#define YYTRANSLATE(x) ((unsigned)(x) <= 427 ? yytranslate[x] : 344)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
   116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
   126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
   136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
   146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
   156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172
};

#if YY_EffectParserBase_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     8,    12,    13,    17,    18,    19,    23,    24,
    27,    29,    30,    36,    39,    40,    42,    44,    46,    47,
    51,    52,    53,    57,    58,    60,    62,    64,    67,    69,
    70,    76,    79,    80,    82,    84,    86,    88,    90,    92,
    94,    96,    98,   100,   102,   104,   106,   108,   110,   112,
   114,   116,   118,   120,   121,   125,   126,   130,   131,   135,
   136,   140,   141,   145,   147,   149,   150,   154,   156,   158,
   160,   162,   166,   168,   170,   172,   174,   176,   178,   180,
   182,   184,   186,   188,   190,   192,   194,   195,   199,   201,
   205,   207,   209,   211,   213,   214,   218,   219,   223,   224,
   228,   229,   233,   235,   237,   239,   241,   243,   245,   246,
   250,   252,   256,   257,   261,   262,   266,   267,   271,   272,
   276,   277,   281,   283,   285,   287,   289,   291,   293,   295,
   296,   300,   302,   304,   306,   307,   311,   312,   316,   317,
   321,   323,   325,   326,   330,   331,   335,   336,   342,   344,
   346,   348,   350,   352,   354,   356,   358,   360,   362,   364,
   365,   369,   370,   374,   376,   378,   380,   382,   383,   387,
   388,   392,   393,   397,   398,   402,   403,   409,   412,   413,
   416,   419,   420,   422,   424,   426,   428,   430,   432,   434,
   436,   438,   440,   442,   444,   446,   448,   450,   452,   453,
   459,   460,   464,   466,   468,   470,   471,   475,   476,   482,
   484,   486,   488,   490,   492,   494,   496,   498,   499,   503,
   505,   511,   513,   515,   517,   519,   521,   523,   525,   526,
   530,   531,   539,   540,   548,   549,   553,   555,   557,   559,
   561,   563,   565,   567,   569,   571,   573,   575,   577,   579,
   581,   583,   585,   587,   589,   591,   593,   595,   597,   599,
   601,   603,   605,   606,   610,   612,   614,   616,   618,   619,
   623,   624,   628,   629,   633,   634,   638,   639,   643,   644,
   648,   649,   655,   658,   659,   661,   663,   665,   667,   669,
   671,   672,   676,   678,   680,   682,   684,   686,   687,   691,
   693,   695,   697,   699,   701,   702,   706,   707,   711,   712,
   716,   717,   721,   723,   725,   727,   729,   731,   733,   735,
   737,   743,   751,   757,   761,   763,   765,   767,   769,   771,
   773,   775
};

static const short yyrhs[] = {    -1,
     5,   166,   174,   171,   175,   172,     0,   176,   178,   180,
     0,     0,     8,   177,   341,     0,     0,     0,     9,   179,
   341,     0,     0,   180,   181,     0,   181,     0,     0,     6,
   182,   171,   183,   172,     0,   183,   184,     0,     0,   187,
     0,   185,     0,   190,     0,     0,     7,   186,   340,     0,
     0,     0,    10,   188,   189,     0,     0,    11,     0,    12,
     0,    13,     0,   190,   191,     0,   191,     0,     0,    14,
   192,   171,   193,   172,     0,   193,   194,     0,     0,   195,
     0,   187,     0,   207,     0,   211,     0,   214,     0,   223,
     0,   238,     0,   245,     0,   248,     0,   241,     0,   256,
     0,   243,     0,   250,     0,   252,     0,   270,     0,   196,
     0,   198,     0,   200,     0,   202,     0,   204,     0,     0,
    15,   197,   206,     0,     0,    16,   199,   206,     0,     0,
    17,   201,   206,     0,     0,    18,   203,   339,     0,     0,
    19,   205,   206,     0,   336,     0,    20,     0,     0,    21,
   208,   209,     0,    23,     0,    24,     0,    25,     0,    26,
     0,   210,   170,   210,     0,    27,     0,    28,     0,    29,
     0,    30,     0,    31,     0,    32,     0,    33,     0,    34,
     0,    35,     0,    36,     0,    37,     0,    38,     0,    39,
     0,    40,     0,     0,    41,   212,   213,     0,   343,     0,
   335,   170,   339,     0,   215,     0,   217,     0,   219,     0,
   221,     0,     0,   136,   216,   341,     0,     0,   138,   218,
   335,     0,     0,   139,   220,   339,     0,     0,   137,   222,
   341,     0,   224,     0,   227,     0,   229,     0,   231,     0,
   233,     0,   235,     0,     0,   140,   225,   226,     0,   343,
     0,   335,   170,   340,     0,     0,   142,   228,   340,     0,
     0,   141,   230,   340,     0,     0,   143,   232,   237,     0,
     0,   144,   234,   237,     0,     0,   145,   236,   237,     0,
   146,     0,   147,     0,   148,     0,   149,     0,   150,     0,
   151,     0,   152,     0,     0,    42,   239,   240,     0,    60,
     0,    43,     0,    44,     0,     0,    45,   242,   341,     0,
     0,    46,   244,   341,     0,     0,   153,   246,   247,     0,
   154,     0,   155,     0,     0,   135,   249,   341,     0,     0,
    47,   251,   340,     0,     0,    48,   253,   254,   170,   255,
     0,    53,     0,    52,     0,    49,     0,    51,     0,    50,
     0,   257,     0,   259,     0,   262,     0,   264,     0,   266,
     0,   268,     0,     0,    54,   258,   341,     0,     0,    55,
   260,   261,     0,    60,     0,    63,     0,    61,     0,    62,
     0,     0,    56,   263,   339,     0,     0,    57,   265,   336,
     0,     0,    58,   267,   339,     0,     0,    59,   269,   339,
     0,     0,    64,   271,   171,   272,   172,     0,   272,   273,
     0,     0,   276,   274,     0,   274,   275,     0,     0,   278,
     0,   281,     0,   283,     0,   287,     0,   292,     0,   294,
     0,   296,     0,   298,     0,   302,     0,   305,     0,   311,
     0,   307,     0,   313,     0,   309,     0,   315,     0,   317,
     0,     0,    65,   277,   280,   170,   338,     0,     0,    66,
   279,   341,     0,    67,     0,    68,     0,    69,     0,     0,
    70,   282,   340,     0,     0,    71,   284,   285,   170,   286,
     0,    77,     0,    78,     0,    79,     0,    72,     0,    73,
     0,    74,     0,    75,     0,    76,     0,     0,    80,   288,
   289,     0,   290,     0,   291,   170,   291,   170,   291,     0,
    60,     0,    81,     0,    82,     0,    83,     0,    49,     0,
    63,     0,    83,     0,     0,    84,   293,   340,     0,     0,
    85,   295,   300,   170,   301,   170,   301,     0,     0,    86,
   297,   300,   170,   301,   170,   301,     0,     0,   108,   299,
   336,     0,    87,     0,    88,     0,    89,     0,    24,     0,
    90,     0,    91,     0,    23,     0,    92,     0,    93,     0,
    94,     0,    95,     0,    96,     0,    97,     0,    98,     0,
    99,     0,   100,     0,   101,     0,   102,     0,   103,     0,
   104,     0,   105,     0,   106,     0,    65,     0,    16,     0,
    17,     0,   107,     0,     0,   109,   303,   304,     0,    60,
     0,   110,     0,   111,     0,   112,     0,     0,   113,   306,
   337,     0,     0,   114,   308,   339,     0,     0,   115,   310,
   337,     0,     0,   116,   312,   337,     0,     0,   117,   314,
   339,     0,     0,   118,   316,   337,     0,     0,   119,   318,
   171,   319,   172,     0,   319,   320,     0,     0,   321,     0,
   324,     0,   329,     0,   327,     0,   331,     0,   333,     0,
     0,   121,   322,   323,     0,   126,     0,   127,     0,   114,
     0,   128,     0,   129,     0,     0,   120,   325,   326,     0,
   130,     0,   131,     0,   132,     0,   133,     0,   134,     0,
     0,   123,   328,   339,     0,     0,   122,   330,   339,     0,
     0,   125,   332,   339,     0,     0,   124,   334,   339,     0,
   156,     0,   157,     0,   158,     0,   159,     0,   160,     0,
   161,     0,   162,     0,   163,     0,   339,   170,   339,   170,
   339,     0,   339,   170,   339,   170,   339,   170,   339,     0,
   339,   170,   339,   170,   339,     0,   339,   170,   339,     0,
   166,     0,   167,     0,   167,     0,   167,     0,   342,     0,
   343,     0,   164,     0,   165,     0
};

#endif

#if YY_EffectParserBase_DEBUG != 0
static const short yyrline[] = { 0,
   239,   241,   245,   249,   250,   251,   255,   256,   257,   261,
   262,   266,   267,   271,   272,   276,   277,   278,   282,   283,
   284,   288,   289,   290,   294,   295,   296,   300,   301,   304,
   305,   309,   310,   314,   315,   316,   317,   318,   319,   320,
   321,   322,   323,   324,   325,   326,   327,   328,   332,   333,
   334,   335,   336,   340,   341,   345,   346,   350,   351,   355,
   356,   360,   361,   365,   366,   370,   371,   375,   376,   377,
   378,   379,   383,   384,   385,   386,   387,   388,   389,   390,
   391,   392,   393,   394,   395,   396,   400,   401,   405,   406,
   410,   411,   412,   413,   417,   418,   422,   423,   427,   428,
   432,   433,   437,   438,   439,   440,   441,   442,   446,   447,
   451,   452,   456,   457,   461,   462,   466,   467,   471,   472,
   476,   477,   481,   482,   483,   484,   485,   486,   487,   491,
   492,   496,   497,   498,   502,   503,   507,   508,   512,   513,
   517,   518,   522,   523,   527,   528,   532,   533,   537,   538,
   541,   542,   543,   547,   548,   549,   550,   551,   552,   556,
   557,   561,   562,   566,   567,   568,   569,   573,   574,   578,
   579,   583,   584,   588,   589,   593,   595,   599,   600,   603,
   607,   608,   612,   613,   614,   615,   616,   617,   618,   619,
   620,   621,   622,   623,   624,   625,   626,   627,   631,   632,
   636,   637,   641,   642,   643,   646,   647,   651,   652,   656,
   657,   658,   662,   663,   664,   665,   666,   670,   671,   675,
   676,   680,   681,   682,   683,   686,   687,   688,   691,   692,
   696,   697,   701,   702,   706,   707,   711,   712,   713,   714,
   715,   716,   717,   718,   719,   720,   721,   722,   723,   724,
   725,   726,   727,   728,   729,   730,   731,   735,   736,   737,
   738,   739,   743,   744,   748,   749,   750,   751,   755,   756,
   760,   761,   765,   766,   770,   771,   775,   776,   780,   781,
   785,   787,   792,   793,   796,   797,   798,   799,   800,   801,
   805,   806,   810,   811,   812,   813,   814,   818,   819,   823,
   824,   825,   826,   827,   831,   832,   836,   837,   841,   842,
   846,   847,   851,   852,   853,   854,   855,   856,   857,   858,
   862,   863,   867,   868,   872,   875,   886,   898,   910,   910,
   914,   918
};

static const char * const yytname[] = {   "$","error","$illegal.","ERROR_TOKEN",
"TOKEN_UNKNOWN","TOKEN_EFFECT","TOKEN_TECHNIQUE","TOKEN_LODLEVEL","TOKEN_RECEIVESHADOWS",
"TOKEN_CASTSHADOWS","TOKEN_SORT","TOKEN_SKYDOME","TOKEN_NORMAL","TOKEN_TRANSPARENT",
"TOKEN_PASS","TOKEN_AMBIENT","TOKEN_DIFFUSE","TOKEN_SPECULAR","TOKEN_SHININESS",
"TOKEN_EMISSIVE","TOKEN_VERTEXCOLOUR","TOKEN_SCENEBLEND","TOKEN_BLENDOP","TOKEN_ADD",
"TOKEN_MODULATE","TOKEN_COLOURBLEND","TOKEN_ALPHABLEND","TOKEN_ONE","TOKEN_ZERO",
"TOKEN_SRCCOLOUR","TOKEN_INVSRCCOLOUR","TOKEN_SRCALPHA","TOKEN_INVSRCALPHA",
"TOKEN_SRCALPHASAT","TOKEN_DESTALPHA","TOKEN_INVDESTALPHA","TOKEN_DESTCOLOUR",
"TOKEN_INVDESTCOLOUR","TOKEN_BLENDFACTOR","TOKEN_INVBLENDFACTOR","TOKEN_BOTHINVSRCALPHA",
"TOKEN_ALPHATEST","TOKEN_CULLINGMODE","TOKEN_COUNTERCLOCKWISE","TOKEN_CLOCKWISE",
"TOKEN_NORMALISENORMALS","TOKEN_LIGHTING","TOKEN_MAXLIGHTS","TOKEN_ITERATION",
"TOKEN_POINT","TOKEN_DIRECTIONAL","TOKEN_SPOT","TOKEN_ONCEPERLIGHT","TOKEN_ONCE",
"TOKEN_FOGOVERRIDE","TOKEN_FOGTYPE","TOKEN_FOGDENSITY","TOKEN_FOGCOLOUR","TOKEN_FOGSTART",
"TOKEN_FOGEND","TOKEN_NONE","TOKEN_EXP","TOKEN_EXP2","TOKEN_LINEAR","TOKEN_TEXTUREUNIT",
"TOKEN_TEXTURE","TOKEN_AUTOGENERATED","TOKEN_1D","TOKEN_2D","TOKEN_CUBEMAP",
"TOKEN_TEXCOORDSET","TOKEN_ADDRESSINGMODE","TOKEN_WRAP","TOKEN_CLAMP","TOKEN_MIRROR",
"TOKEN_MIRRORONCE","TOKEN_BORDER","TOKEN_ADDRESSMODE_U","TOKEN_ADDRESSMODE_V",
"TOKEN_ADDRESSMODE_W","TOKEN_FILTERING","TOKEN_BILINEAR","TOKEN_TRILINEAR","TOKEN_ANISOTROPIC",
"TOKEN_MAXANISOTROPY","TOKEN_COLOUROP","TOKEN_ALPHAOP","TOKEN_DISABLE","TOKEN_SELECTARG1",
"TOKEN_SELECTARG2","TOKEN_MODULATE2X","TOKEN_MODULATE4X","TOKEN_ADDSIGNED","TOKEN_SUBTRACT",
"TOKEN_ADDSMOOTH","TOKEN_BLENDDIFFUSEALPHA","TOKEN_BLENDTEXTUREALPHA","TOKEN_BLENDFACTORALPHA",
"TOKEN_BLENDTEXTUREALPHAPM","TOKEN_BLENDCURRENTALPHA","TOKEN_PREMODULATE","TOKEN_MODULATEALPHA_ADDCOLOUR",
"TOKEN_MODULATECOLOUR_ADDALPHA","TOKEN_DOTPRODUCT3","TOKEN_MULTIPLYADD","TOKEN_LERP",
"TOKEN_CURRENT","TOKEN_CONSTANT","TOKEN_CONSTANTCOLOUR","TOKEN_TEXCOORDGEN",
"TOKEN_SPHEREMAP","TOKEN_EYESPACE_REFLECTION","TOKEN_EYESPACE_NORMAL","TOKEN_SCROLL",
"TOKEN_ROTATE","TOKEN_SCALE","TOKEN_SCROLLANIM","TOKEN_ROTATEANIM","TOKEN_SCALEANIM",
"TOKEN_WAVEXFORM","TOKEN_WAVETYPE","TOKEN_XFORMTYPE","TOKEN_PHASE","TOKEN_BASE",
"TOKEN_FREQUENCY","TOKEN_AMPLITUDE","TOKEN_SCROLL_X","TOKEN_SCROLL_Y","TOKEN_SCALE_X",
"TOKEN_SCALE_Y","TOKEN_SINE","TOKEN_SQUARE","TOKEN_SAWTOOTH","TOKEN_INVERSE_SAWTOOTH",
"TOKEN_TRIANGLE","TOKEN_COLOURWRITE","TOKEN_DEPTHTEST","TOKEN_DEPTHWRITE","TOKEN_DEPTHFUNC",
"TOKEN_DEPTHBIAS","TOKEN_STENCILTEST","TOKEN_STENCILWRITEMASK","TOKEN_STENCILMASK",
"TOKEN_STENCILPASS","TOKEN_STENCILFAIL","TOKEN_STENCILZFAIL","TOKEN_KEEP","TOKEN_REPLACE",
"TOKEN_INCRSAT","TOKEN_DECRSAT","TOKEN_INVERT","TOKEN_INCR","TOKEN_DECR","TOKEN_SHADING",
"TOKEN_FLAT","TOKEN_GOURAUD","TOKEN_ALWAYS","TOKEN_NEVER","TOKEN_LESS","TOKEN_LEQUAL",
"TOKEN_EQUAL","TOKEN_NOTEQUAL","TOKEN_GEQUAL","TOKEN_GREATER","TOKEN_ENABLED",
"TOKEN_DISABLED","TOKEN_STRING","TOKEN_FLOAT","TOKEN_UINT","TOKEN_INT","TOKEN_COMMA",
"TOKEN_LEFTCURLYBRACKET","TOKEN_RIGHTCURLYBRACKET","effectfile","@1","effectblock",
"receiveshadows","@2","castshadows","@3","techniquelist","technique","@4","techniquestatementlist",
"techniquestatement","lodlevel","@5","sort","@6","sortmode","passlist","pass",
"@7","passstatementlist","passstatement","materialsettings","ambient","@8","diffuse",
"@9","specular","@10","shininess","@11","emissive","@12","materialcolour","sceneblend",
"@13","sceneBlendOption","blendOp","alphatest","@14","alphatestvalue","depthbufferstatement",
"depthtest","@15","depthfunc","@16","depthbias","@17","depthwrite","@18","stencilstatement",
"stenciltest","@19","stenciltestvalue","stencilmask","@20","stencilwritemask",
"@21","stencilpass","@22","stencilfail","@23","stencilzfail","@24","stencilop",
"cullingmode","@25","cullingmodetype","normalisenormals","@26","lighting","@27",
"shading","@28","shademode","colourwrite","@29","maxlights","@30","iteration",
"@31","iterationtype","lighttype","fogstatement","fogoverride","@32","fogtype",
"@33","fogtypesetting","fogdensity","@34","fogcolour","@35","fogstart","@36",
"fogend","@37","textureunit","@38","textureunitstatementlist","textureunitstatement",
"optionaltextureunitstatementlist","optionaltextureunitstatement","texture",
"@39","autogenerated","@40","texturetype","texcoordset","@41","addressingmode",
"@42","addressingmodetype","addressingmodesetting","filtering","@43","filtersetting",
"filtersettingsimple","filtertype","maxanisotropy","@44","colourop","@45","alphaop",
"@46","constantcolour","@47","colouroperation","colourarg","texcoordgen","@48",
"texcoordgentype","scroll","@49","rotate","@50","scale","@51","scrollanim","@52",
"rotateanim","@53","scaleanim","@54","wavexform","@55","wavexformsettinglist",
"wavexformsetting","wavexformtype","@56","wavexformtypesetting","wavetype","@57",
"wavetypesetting","wavebase","@58","wavephase","@59","waveamplitude","@60","wavefrequency",
"@61","cmpfunc","colour","vector","string","floatvalue","uintvalue","boolean",
"enabled","disabled","disabled"
};
#endif

static const short yyr1[] = {     0,
   174,   173,   175,   177,   176,   176,   179,   178,   178,   180,
   180,   182,   181,   183,   183,   184,   184,   184,   186,   185,
   185,   188,   187,   187,   189,   189,   189,   190,   190,   192,
   191,   193,   193,   194,   194,   194,   194,   194,   194,   194,
   194,   194,   194,   194,   194,   194,   194,   194,   195,   195,
   195,   195,   195,   197,   196,   199,   198,   201,   200,   203,
   202,   205,   204,   206,   206,   208,   207,   209,   209,   209,
   209,   209,   210,   210,   210,   210,   210,   210,   210,   210,
   210,   210,   210,   210,   210,   210,   212,   211,   213,   213,
   214,   214,   214,   214,   216,   215,   218,   217,   220,   219,
   222,   221,   223,   223,   223,   223,   223,   223,   225,   224,
   226,   226,   228,   227,   230,   229,   232,   231,   234,   233,
   236,   235,   237,   237,   237,   237,   237,   237,   237,   239,
   238,   240,   240,   240,   242,   241,   244,   243,   246,   245,
   247,   247,   249,   248,   251,   250,   253,   252,   254,   254,
   255,   255,   255,   256,   256,   256,   256,   256,   256,   258,
   257,   260,   259,   261,   261,   261,   261,   263,   262,   265,
   264,   267,   266,   269,   268,   271,   270,   272,   272,   273,
   274,   274,   275,   275,   275,   275,   275,   275,   275,   275,
   275,   275,   275,   275,   275,   275,   275,   275,   277,   276,
   279,   278,   280,   280,   280,   282,   281,   284,   283,   285,
   285,   285,   286,   286,   286,   286,   286,   288,   287,   289,
   289,   290,   290,   290,   290,   291,   291,   291,   293,   292,
   295,   294,   297,   296,   299,   298,   300,   300,   300,   300,
   300,   300,   300,   300,   300,   300,   300,   300,   300,   300,
   300,   300,   300,   300,   300,   300,   300,   301,   301,   301,
   301,   301,   303,   302,   304,   304,   304,   304,   306,   305,
   308,   307,   310,   309,   312,   311,   314,   313,   316,   315,
   318,   317,   319,   319,   320,   320,   320,   320,   320,   320,
   322,   321,   323,   323,   323,   323,   323,   325,   324,   326,
   326,   326,   326,   326,   328,   327,   330,   329,   332,   331,
   334,   333,   335,   335,   335,   335,   335,   335,   335,   335,
   336,   336,   337,   337,   338,   339,   340,    -1,   341,   341,
   342,   343
};

static const short yyr2[] = {     0,
     0,     6,     3,     0,     3,     0,     0,     3,     0,     2,
     1,     0,     5,     2,     0,     1,     1,     1,     0,     3,
     0,     0,     3,     0,     1,     1,     1,     2,     1,     0,
     5,     2,     0,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     0,     3,     0,     3,     0,     3,     0,
     3,     0,     3,     1,     1,     0,     3,     1,     1,     1,
     1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     0,     3,     1,     3,
     1,     1,     1,     1,     0,     3,     0,     3,     0,     3,
     0,     3,     1,     1,     1,     1,     1,     1,     0,     3,
     1,     3,     0,     3,     0,     3,     0,     3,     0,     3,
     0,     3,     1,     1,     1,     1,     1,     1,     1,     0,
     3,     1,     1,     1,     0,     3,     0,     3,     0,     3,
     1,     1,     0,     3,     0,     3,     0,     5,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
     3,     0,     3,     1,     1,     1,     1,     0,     3,     0,
     3,     0,     3,     0,     3,     0,     5,     2,     0,     2,
     2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     0,     5,
     0,     3,     1,     1,     1,     0,     3,     0,     5,     1,
     1,     1,     1,     1,     1,     1,     1,     0,     3,     1,
     5,     1,     1,     1,     1,     1,     1,     1,     0,     3,
     0,     7,     0,     7,     0,     3,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     0,     3,     1,     1,     1,     1,     0,     3,
     0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
     0,     5,     2,     0,     1,     1,     1,     1,     1,     1,
     0,     3,     1,     1,     1,     1,     1,     0,     3,     1,
     1,     1,     1,     1,     0,     3,     0,     3,     0,     3,
     0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
     5,     7,     5,     3,     1,     1,     1,     1,     1,     1,
     1,     1
};

static const short yydefact[] = {     0,
     0,     1,     0,     6,     4,     0,     9,     0,     2,     7,
     0,   331,   332,     5,   329,   330,     0,    12,     3,    11,
     8,     0,    10,    15,     0,    19,    22,    30,    13,    14,
    17,    16,    18,    29,     0,     0,     0,    28,   327,    20,
    25,    26,    27,    23,    33,     0,    54,    56,    58,    60,
    62,    66,    87,   130,   135,   137,   145,   147,   160,   162,
   168,   170,   172,   174,   176,   143,    95,   101,    97,    99,
   109,   115,   113,   117,   119,   121,   139,    31,    35,    32,
    34,    49,    50,    51,    52,    53,    36,    37,    38,    91,
    92,    93,    94,    39,   103,   104,   105,   106,   107,   108,
    40,    43,    45,    41,    42,    46,    47,    44,   154,   155,
   156,   157,   158,   159,    48,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    65,   326,    55,    64,
     0,    57,    59,    61,    63,    68,    69,    70,    71,    73,
    74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
    84,    85,    86,    67,     0,   313,   314,   315,   316,   317,
   318,   319,   320,    88,     0,    89,   133,   134,   132,   131,
   136,   138,   146,   150,   149,     0,   161,   164,   166,   167,
   165,   163,   169,   171,   173,   175,   179,   144,    96,   102,
    98,   100,   110,     0,   111,   116,   114,   123,   124,   125,
   126,   127,   128,   129,   118,   120,   122,   141,   142,   140,
     0,     0,     0,     0,     0,     0,     0,    72,    90,   151,
   153,   152,   148,   199,   177,   178,   182,   112,     0,     0,
   180,   321,   203,   204,   205,     0,   201,   206,   208,   218,
   229,   231,   233,   235,   263,   269,   271,   273,   275,   277,
   279,   281,   181,   183,   184,   185,   186,   187,   188,   189,
   190,   191,   192,   194,   196,   193,   195,   197,   198,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   322,   325,   200,
   202,   207,   210,   211,   212,     0,   226,   222,   227,   223,
   224,   225,   219,   220,     0,   230,   243,   240,   237,   238,
   239,   241,   242,   244,   245,   246,   247,   248,   249,   250,
   251,   252,   253,   254,   255,   256,   257,     0,     0,   236,
   265,   266,   267,   268,   264,   270,     0,   272,   274,   276,
   278,   280,   284,     0,     0,     0,     0,     0,     0,   213,
   214,   215,   216,   217,   209,   228,     0,   260,   261,   259,
   258,   262,     0,     0,   324,   298,   291,   307,   305,   311,
   309,   282,   283,   285,   286,   288,   287,   289,   290,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   221,
   232,   234,   323,   300,   301,   302,   303,   304,   299,   295,
   293,   294,   296,   297,   292,   308,   306,   312,   310,     0,
     0,     0
};

static const short yydefgoto[] = {   430,
     3,     6,     7,     8,    11,    17,    19,    20,    22,    25,
    30,    31,    35,    32,    36,    44,    33,    34,    37,    46,
    80,    81,    82,   116,    83,   117,    84,   118,    85,   119,
    86,   120,   149,    87,   121,   174,   175,    88,   122,   184,
    89,    90,   136,    91,   138,    92,   139,    93,   137,    94,
    95,   140,   213,    96,   142,    97,   141,    98,   143,    99,
   144,   100,   145,   225,   101,   123,   190,   102,   124,   103,
   125,   104,   146,   230,   105,   135,   106,   126,   107,   127,
   196,   243,   108,   109,   128,   110,   129,   202,   111,   130,
   112,   131,   113,   132,   114,   133,   115,   134,   235,   246,
   251,   273,   247,   250,   274,   292,   256,   275,   293,   276,
   294,   316,   375,   277,   295,   323,   324,   325,   278,   296,
   279,   297,   280,   298,   281,   299,   348,   383,   282,   300,
   355,   283,   301,   284,   302,   285,   303,   286,   304,   287,
   305,   288,   306,   289,   307,   369,   393,   394,   405,   425,
   395,   404,   419,   396,   407,   397,   406,   398,   409,   399,
   408,   185,   150,   356,   310,   151,    40,    14,    15,    16
};

static const short yypact[] = {    42,
  -115,-32768,  -114,    90,-32768,  -104,   119,   -24,-32768,-32768,
   111,-32768,-32768,-32768,-32768,-32768,   -24,-32768,   111,-32768,
-32768,   -29,-32768,-32768,    -2,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   146,-32768,     5,    28,     4,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,     8,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   -13,   -13,   -13,    14,   -13,
   172,    94,   -12,   -24,   -24,     5,   137,   -24,   -27,    14,
    14,    14,    14,    20,   -24,   -24,   -24,   104,    14,    94,
     5,     5,    16,    16,    16,    60,-32768,-32768,-32768,-32768,
     7,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    43,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    50,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    72,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    75,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    14,   201,    14,    10,   -61,     5,    77,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    14,    34,
   108,    78,-32768,-32768,-32768,    88,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    14,
   102,   -24,     5,    29,    55,     5,    -8,    -8,    14,   -41,
    14,    14,    14,    14,    14,    14,    98,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   100,-32768,-32768,-32768,-32768,
-32768,   101,-32768,-32768,   103,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   105,   106,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   109,-32768,-32768,-32768,
-32768,-32768,-32768,    59,    56,    -7,    -7,    14,   -47,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   110,-32768,-32768,-32768,
-32768,-32768,   112,   113,   115,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    56,
    -7,    -7,    14,    25,   -84,    14,    14,    14,    14,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   272,
   274,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   259,-32768,-32768,
-32768,-32768,-32768,   235,-32768,-32768,-32768,   253,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,     6,-32768,-32768,-32768,    61,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    74,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -348,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    -6,  -364,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   -11,  -130,   -60,-32768,  -119,  -120,   -15,-32768,   -94
};


#define	YYLAST		293


static const short yytable[] = {   154,
   204,    21,   384,   244,    26,   193,   147,    27,   378,   379,
   203,    28,   205,   206,   327,   328,   377,    27,   351,   212,
   216,   217,    47,    48,    49,    50,    51,   186,    52,   420,
   187,   188,   198,   199,   200,   201,   411,   412,    41,    42,
    43,   421,   422,   423,   424,   215,     1,   189,    53,    54,
     2,   410,    55,    56,    57,    58,     4,   380,   240,   241,
   242,    59,    60,    61,    62,    63,    64,     9,   352,   353,
   354,    65,   386,   387,   388,   389,   390,   391,   329,   330,
   331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
   341,   342,   343,   344,   345,   346,   347,     5,   381,   382,
   253,   254,   255,   317,   317,   313,   314,   315,   191,   192,
   245,   237,   197,   239,   318,   248,    18,   319,   319,   208,
   209,   210,   152,   153,   392,   155,   211,    10,   214,   252,
   370,   371,   372,   373,   374,   320,   321,   322,   376,    12,
    13,    24,    66,    67,    68,    69,    70,    71,    72,    73,
    74,    75,    76,   148,   414,   415,   416,   417,   418,    28,
    77,   218,   219,   220,   221,   222,   223,   224,   350,    29,
   308,    39,   312,   257,    45,   326,   231,   258,   259,    78,
   148,   357,   358,   357,   357,   361,   357,   260,   194,   195,
   207,   261,   262,   263,   156,   157,   158,   159,   160,   161,
   162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
   172,   173,   232,   228,   229,   264,   265,   226,   227,   233,
   266,   267,   268,   269,   270,   271,   272,   160,   161,   162,
   163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
   173,   234,   359,   360,   236,   362,   249,   290,   385,   176,
   177,   178,   179,   180,   181,   182,   183,   291,    13,   176,
   177,   178,   179,   180,   181,   182,   183,   309,   363,   364,
  -228,   431,   365,   432,   366,   367,   311,    23,   368,   400,
    79,   401,   402,   413,   403,    38,   426,   427,   428,   429,
     0,   349,   238
};

static const short yycheck[] = {   119,
   131,    17,   367,    65,     7,   126,    20,    10,    16,    17,
   130,    14,   132,   133,    23,    24,   365,    10,    60,   139,
   141,   142,    15,    16,    17,    18,    19,   122,    21,   114,
    43,    44,    60,    61,    62,    63,   401,   402,    11,    12,
    13,   126,   127,   128,   129,   140,     5,    60,    41,    42,
   166,   400,    45,    46,    47,    48,   171,    65,    49,    50,
    51,    54,    55,    56,    57,    58,    59,   172,   110,   111,
   112,    64,   120,   121,   122,   123,   124,   125,    87,    88,
    89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
    99,   100,   101,   102,   103,   104,   105,     8,   106,   107,
    67,    68,    69,    49,    49,    77,    78,    79,   124,   125,
   172,   231,   128,   233,    60,   236,     6,    63,    63,   135,
   136,   137,   117,   118,   172,   120,   138,     9,   140,   249,
    72,    73,    74,    75,    76,    81,    82,    83,    83,   164,
   165,   171,   135,   136,   137,   138,   139,   140,   141,   142,
   143,   144,   145,   167,   130,   131,   132,   133,   134,    14,
   153,   146,   147,   148,   149,   150,   151,   152,   299,   172,
   290,   167,   293,    66,   171,   296,   170,    70,    71,   172,
   167,   301,   302,   303,   304,   305,   306,    80,    52,    53,
   171,    84,    85,    86,    23,    24,    25,    26,    27,    28,
    29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
    39,    40,   170,   154,   155,   108,   109,   144,   145,   170,
   113,   114,   115,   116,   117,   118,   119,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,   170,   303,   304,   170,   306,   170,   170,   368,   156,
   157,   158,   159,   160,   161,   162,   163,   170,   165,   156,
   157,   158,   159,   160,   161,   162,   163,   166,   171,   170,
   170,     0,   170,     0,   170,   170,   292,    19,   170,   170,
    46,   170,   170,   403,   170,    33,   406,   407,   408,   409,
    -1,   298,   232
};

#line 325 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
 /* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: dollar marks section change
   the next  is replaced by the list of actions, each action
   as one case of the switch.  */ 

#if YY_EffectParserBase_USE_GOTO != 0
/* 
 SUPRESSION OF GOTO : on some C++ compiler (sun c++)
  the goto is strictly forbidden if any constructor/destructor
  is used in the whole function (very stupid isn't it ?)
 so goto are to be replaced with a 'while/switch/case construct'
 here are the macro to keep some apparent compatibility
*/
#define YYGOTO(lb) {yy_gotostate=lb;continue;}
#define YYBEGINGOTO  enum yy_labels yy_gotostate=yygotostart; \
                     for(;;) switch(yy_gotostate) { case yygotostart: {
#define YYLABEL(lb) } case lb: {
#define YYENDGOTO } } 
#define YYBEGINDECLARELABEL enum yy_labels {yygotostart
#define YYDECLARELABEL(lb) ,lb
#define YYENDDECLARELABEL  };
#else
/* macro to keep goto */
#define YYGOTO(lb) goto lb
#define YYBEGINGOTO 
#define YYLABEL(lb) lb:
#define YYENDGOTO
#define YYBEGINDECLARELABEL 
#define YYDECLARELABEL(lb)
#define YYENDDECLARELABEL 
#endif
/* LABEL DECLARATION */
YYBEGINDECLARELABEL
  YYDECLARELABEL(yynewstate)
  YYDECLARELABEL(yybackup)
/* YYDECLARELABEL(yyresume) */
  YYDECLARELABEL(yydefault)
  YYDECLARELABEL(yyreduce)
  YYDECLARELABEL(yyerrlab)   /* here on detecting error */
  YYDECLARELABEL(yyerrlab1)   /* here on error raised explicitly by an action */
  YYDECLARELABEL(yyerrdefault)  /* current state does not do anything special for the error token. */
  YYDECLARELABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */
  YYDECLARELABEL(yyerrhandle)  
YYENDDECLARELABEL
/* ALLOCA SIMULATION */
/* __HAVE_NO_ALLOCA */
#ifdef __HAVE_NO_ALLOCA
int __alloca_free_ptr(char *ptr,char *ref)
{if(ptr!=ref) free(ptr);
 return 0;}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_EffectParserBase_LSP_NEEDED
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		    __ALLOCA_free(yyls,yylsa)+\
		   (num))
#else
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		   (num))
#endif
#else
#define __ALLOCA_return(num) return(num)
#define __ALLOCA_alloca(size) alloca(size)
#define __ALLOCA_free(ptr,ref) 
#endif

/* ENDALLOCA SIMULATION */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_EffectParserBase_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        __ALLOCA_return(0)
#define YYABORT         __ALLOCA_return(1)
#define YYERROR         YYGOTO(yyerrlab1)
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          YYGOTO(yyerrlab)
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_EffectParserBase_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_EffectParserBase_CHAR = (token), YY_EffectParserBase_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_EffectParserBase_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_EffectParserBase_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_EffectParserBase_PURE
/* UNPURE */
#define YYLEX           YY_EffectParserBase_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_EffectParserBase_CHAR;                      /*  the lookahead symbol        */
YY_EffectParserBase_STYPE      YY_EffectParserBase_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_EffectParserBase_NERRS;                 /*  number of parse errors so far */
#ifdef YY_EffectParserBase_LSP_NEEDED
YY_EffectParserBase_LTYPE YY_EffectParserBase_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_EffectParserBase_LSP_NEEDED
#define YYLEX           YY_EffectParserBase_LEX(&YY_EffectParserBase_LVAL, &YY_EffectParserBase_LLOC)
#else
#define YYLEX           YY_EffectParserBase_LEX(&YY_EffectParserBase_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_EffectParserBase_DEBUG != 0
int YY_EffectParserBase_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif
#endif



/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif


#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)       __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */

#ifdef __cplusplus
static void __yy_bcopy (char *from, char *to, int count)
#else
#ifdef __STDC__
static void __yy_bcopy (char *from, char *to, int count)
#else
static void __yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
#endif
#endif
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}
#endif

int
#ifdef YY_USE_CLASS
 YY_EffectParserBase_CLASS::
#endif
     YY_EffectParserBase_PARSE(YY_EffectParserBase_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_EffectParserBase_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_EffectParserBase_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_EffectParserBase_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_EffectParserBase_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_EffectParserBase_LSP_NEEDED
  YY_EffectParserBase_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_EffectParserBase_LTYPE *yyls = yylsa;
  YY_EffectParserBase_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_EffectParserBase_PURE
  int YY_EffectParserBase_CHAR;
  YY_EffectParserBase_STYPE YY_EffectParserBase_LVAL;
  int YY_EffectParserBase_NERRS;
#ifdef YY_EffectParserBase_LSP_NEEDED
  YY_EffectParserBase_LTYPE YY_EffectParserBase_LLOC;
#endif
#endif

  YY_EffectParserBase_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_EffectParserBase_DEBUG != 0
  if (YY_EffectParserBase_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_EffectParserBase_NERRS = 0;
  YY_EffectParserBase_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_EffectParserBase_LSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
YYLABEL(yynewstate)

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YY_EffectParserBase_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_EffectParserBase_LSP_NEEDED
      YY_EffectParserBase_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_EffectParserBase_LSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YY_EffectParserBase_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_EffectParserBase_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_EffectParserBase_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_EffectParserBase_LSP_NEEDED
      yyls = (YY_EffectParserBase_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_EffectParserBase_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_EffectParserBase_DEBUG != 0
      if (YY_EffectParserBase_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_EffectParserBase_DEBUG != 0
  if (YY_EffectParserBase_DEBUG_FLAG)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  YYGOTO(yybackup);
YYLABEL(yybackup)

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* YYLABEL(yyresume) */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yydefault);

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (YY_EffectParserBase_CHAR == YYEMPTY)
    {
#if YY_EffectParserBase_DEBUG != 0
      if (YY_EffectParserBase_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_EffectParserBase_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_EffectParserBase_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_EffectParserBase_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_EffectParserBase_DEBUG != 0
      if (YY_EffectParserBase_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_EffectParserBase_CHAR);

#if YY_EffectParserBase_DEBUG != 0
      if (YY_EffectParserBase_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_EffectParserBase_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_EffectParserBase_CHAR, YY_EffectParserBase_LVAL);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    YYGOTO(yydefault);

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrlab);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrlab);

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YY_EffectParserBase_DEBUG != 0
  if (YY_EffectParserBase_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_EffectParserBase_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_EffectParserBase_CHAR != YYEOF)
    YY_EffectParserBase_CHAR = YYEMPTY;

  *++yyvsp = YY_EffectParserBase_LVAL;
#ifdef YY_EffectParserBase_LSP_NEEDED
  *++yylsp = YY_EffectParserBase_LLOC;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  YYGOTO(yynewstate);

/* Do the default action for the current state.  */
YYLABEL(yydefault)

  yyn = yydefact[yystate];
  if (yyn == 0)
    YYGOTO(yyerrlab);

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
YYLABEL(yyreduce)
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YY_EffectParserBase_DEBUG != 0
  if (YY_EffectParserBase_DEBUG_FLAG)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


/* #line 811 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 2143 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"

  switch (yyn) {

case 1:
#line 239 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddRootNode( NODETYPE_EFFECT ); 
																	m_tree.AddNode( NODETYPE_STRINGLITERAL, yyvsp[0] ); ;
    break;}
case 2:
#line 241 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{   m_tree.EndRootNode(); ;
    break;}
case 4:
#line 249 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddRootNode( NODETYPE_RECEIVESHADOWS ); ;
    break;}
case 5:
#line 250 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{   m_tree.EndRootNode(); ;
    break;}
case 7:
#line 255 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddRootNode( NODETYPE_CASTSHADOWS ); ;
    break;}
case 8:
#line 256 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{   m_tree.EndRootNode(); ;
    break;}
case 12:
#line 266 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	 m_tree.AddRootNode(NODETYPE_TECHNIQUE); ;
    break;}
case 13:
#line 267 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	 m_tree.EndRootNode(); ;
    break;}
case 19:
#line 282 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddRootNode( NODETYPE_LODLEVEL );	;
    break;}
case 20:
#line 283 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{   m_tree.EndRootNode( );						;
    break;}
case 22:
#line 288 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddRootNode( NODETYPE_SORT );		;
    break;}
case 23:
#line 289 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.EndRootNode( );						;
    break;}
case 25:
#line 294 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddNode( NODETYPE_SKYDOME, SORT_SKYDOME);		;
    break;}
case 26:
#line 295 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddNode( NODETYPE_NORMAL,  SORT_NORMAL );		;
    break;}
case 27:
#line 296 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddNode( NODETYPE_TRANSPARENT, SORT_TRANSPARENT ); ;
    break;}
case 30:
#line 304 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.AddRootNode(NODETYPE_PASS);	;
    break;}
case 31:
#line 305 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{	m_tree.EndRootNode();				;
    break;}
case 54:
#line 340 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_AMBIENT);	;
    break;}
case 55:
#line 341 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();					;
    break;}
case 56:
#line 345 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_DIFFUSE);	;
    break;}
case 57:
#line 346 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();					;
    break;}
case 58:
#line 350 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SPECULAR); ;
    break;}
case 59:
#line 351 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();					 ;
    break;}
case 60:
#line 355 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SHININESS);;
    break;}
case 61:
#line 356 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();					 ;
    break;}
case 62:
#line 360 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_EMISSIVE); ;
    break;}
case 63:
#line 361 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();					 ;
    break;}
case 65:
#line 366 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_VERTEXCOLOUR); ;
    break;}
case 66:
#line 370 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SCENEBLEND);	;
    break;}
case 67:
#line 371 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();						;
    break;}
case 68:
#line 375 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ADD);				;
    break;}
case 69:
#line 376 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MODULATE);			;
    break;}
case 70:
#line 377 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_COLOURBLEND);		;
    break;}
case 71:
#line 378 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ALPHABLEND);		;
    break;}
case 73:
#line 383 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ONE, BLEND_ONE);							;
    break;}
case 74:
#line 384 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ZERO, BLEND_ZERO);						;
    break;}
case 75:
#line 385 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SRCCOLOUR, BLEND_SRCCOLOUR);				;
    break;}
case 76:
#line 386 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INVSRCCOLOUR, BLEND_INVSRCCOLOUR);		;
    break;}
case 77:
#line 387 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SRCALPHA, BLEND_SRCALPHA);				;
    break;}
case 78:
#line 388 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INVSRCALPHA, BLEND_INVSRCALPHA);			;
    break;}
case 79:
#line 389 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SRCALPHASAT, BLEND_SRCALPHASAT);			;
    break;}
case 80:
#line 390 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DESTALPHA, BLEND_DESTALPHA);				;
    break;}
case 81:
#line 391 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INVDESTALPHA, BLEND_INVDESTALPHA);		;
    break;}
case 82:
#line 392 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DESTCOLOUR, BLEND_DESTCOLOUR);			;
    break;}
case 83:
#line 393 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INVDESTCOLOUR, BLEND_INVDESTCOLOUR);		;
    break;}
case 84:
#line 394 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BLENDFACTOR, BLEND_BLENDFACTOR);			;
    break;}
case 85:
#line 395 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INVBLENDFACTOR, BLEND_INVBLENDFACTOR);	;
    break;}
case 86:
#line 396 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BOTHINVSRCALPHA, BLEND_BOTHINVSRCALPHA);	;
    break;}
case 87:
#line 400 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_ALPHATEST);	;
    break;}
case 88:
#line 401 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();						;
    break;}
case 95:
#line 417 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_DEPTHTEST);	;
    break;}
case 96:
#line 418 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();						;
    break;}
case 97:
#line 422 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_DEPTHFUNC);	;
    break;}
case 98:
#line 423 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();						;
    break;}
case 99:
#line 427 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_DEPTHBIAS);	;
    break;}
case 100:
#line 428 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();						;
    break;}
case 101:
#line 432 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_DEPTHWRITE);	;
    break;}
case 102:
#line 433 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();						;
    break;}
case 109:
#line 446 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_STENCILTEST);		;
    break;}
case 110:
#line 447 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 113:
#line 456 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_STENCILMASK);		;
    break;}
case 114:
#line 457 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 115:
#line 461 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_STENCILWRITEMASK);;
    break;}
case 116:
#line 462 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 117:
#line 466 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_STENCILPASS);		;
    break;}
case 118:
#line 467 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 119:
#line 471 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_STENCILFAIL);		;
    break;}
case 120:
#line 472 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 121:
#line 476 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_STENCILZFAIL);	;
    break;}
case 122:
#line 477 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 123:
#line 481 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_KEEP, STENCILOP_KEEP);		;
    break;}
case 124:
#line 482 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_REPLACE, STENCILOP_REPLACE);	;
    break;}
case 125:
#line 483 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INCRSAT, STENCILOP_INCRSAT);	;
    break;}
case 126:
#line 484 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DECRSAT, STENCILOP_DECRSAT);	;
    break;}
case 127:
#line 485 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INVERT, STENCILOP_INVERT);	;
    break;}
case 128:
#line 486 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INCR, STENCILOP_INCR);		;
    break;}
case 129:
#line 487 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DECR, STENCILOP_DECR);		;
    break;}
case 130:
#line 491 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_CULLINGMODE);			;
    break;}
case 131:
#line 492 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 132:
#line 496 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_NONE, CULL_NONE);							;
    break;}
case 133:
#line 497 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_COUNTERCLOCKWISE, CULL_COUNTERCLOCKWISE);	;
    break;}
case 134:
#line 498 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_CLOCKWISE, CULL_CLOCKWISE);				;
    break;}
case 135:
#line 502 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_NORMALISENORMALS);	;
    break;}
case 136:
#line 503 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 137:
#line 507 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_LIGHTING);			;
    break;}
case 138:
#line 508 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 139:
#line 512 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SHADING);				;
    break;}
case 140:
#line 513 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 141:
#line 517 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_FLAT, SHADE_FLAT);		;
    break;}
case 142:
#line 518 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_GOURAUD, SHADE_GOURAUD);	;
    break;}
case 143:
#line 522 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_COLOURWRITE);			;
    break;}
case 144:
#line 523 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 145:
#line 527 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_MAXLIGHTS);			;
    break;}
case 146:
#line 528 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 147:
#line 532 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_ITERATION);			;
    break;}
case 148:
#line 533 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 149:
#line 537 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ONCE);					;
    break;}
case 150:
#line 538 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ONCEPERLIGHT);			;
    break;}
case 151:
#line 541 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_POINT, LIGHT_POINT);					;
    break;}
case 152:
#line 542 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SPOT, LIGHT_SPOT);					;
    break;}
case 153:
#line 543 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DIRECTIONAL, LIGHT_DIRECTIONAL);		;
    break;}
case 160:
#line 556 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FOGOVERRIDE);			;
    break;}
case 161:
#line 557 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 162:
#line 561 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FOGTYPE);				;
    break;}
case 163:
#line 562 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 164:
#line 566 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_NONE, FOGMODE_NONE);				;
    break;}
case 165:
#line 567 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_LINEAR, FOGMODE_LINEAR);			;
    break;}
case 166:
#line 568 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_EXP, FOGMODE_EXP);				;
    break;}
case 167:
#line 569 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_EXP2, FOGMODE_EXP2);				;
    break;}
case 168:
#line 573 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FOGDENSITY);		;
    break;}
case 169:
#line 574 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 170:
#line 578 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FOGCOLOUR);		;
    break;}
case 171:
#line 579 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 172:
#line 583 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FOGSTART);		;
    break;}
case 173:
#line 584 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 174:
#line 588 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FOGEND);			;
    break;}
case 175:
#line 589 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 176:
#line 593 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_TEXTUREUNIT);			;
    break;}
case 177:
#line 596 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();								;
    break;}
case 199:
#line 631 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_TEXTURE);			;
    break;}
case 200:
#line 632 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 201:
#line 636 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_AUTOGENERATED);	;
    break;}
case 202:
#line 637 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 203:
#line 641 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_TEX1D, TEXTURE_1D);						;
    break;}
case 204:
#line 642 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_TEX2D, TEXTURE_2D );						;
    break;}
case 205:
#line 643 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_TEXCUBEMAP, TEXTURE_CUBEMAP);				;
    break;}
case 206:
#line 646 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_TEXCOORDSET);		;
    break;}
case 207:
#line 647 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 208:
#line 651 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_ADDRESSINGMODE);	;
    break;}
case 209:
#line 652 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();		;
    break;}
case 210:
#line 656 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ADDRESSMODE_U, TEX_ADDRESS_U);		;
    break;}
case 211:
#line 657 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ADDRESSMODE_V, TEX_ADDRESS_V);		;
    break;}
case 212:
#line 658 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ADDRESSMODE_W, TEX_ADDRESS_W);		;
    break;}
case 213:
#line 662 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_WRAP, TEXADDRESS_WRAP);				;
    break;}
case 214:
#line 663 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_CLAMP, TEXADDRESS_CLAMP);				;
    break;}
case 215:
#line 664 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MIRROR, TEXADDRESS_MIRROR);			;
    break;}
case 216:
#line 665 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MIRRORONCE, TEXADDRESS_MIRRORONCE);	;
    break;}
case 217:
#line 666 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BORDER, TEXADDRESS_BORDER);			;
    break;}
case 218:
#line 670 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FILTERING);		;
    break;}
case 219:
#line 671 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 222:
#line 680 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_NONE);		;
    break;}
case 223:
#line 681 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BILINEAR);	;
    break;}
case 224:
#line 682 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_TRILINEAR);	;
    break;}
case 225:
#line 683 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ANISOTROPIC);	;
    break;}
case 226:
#line 686 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_POINT, TEXFILTER_POINT);		;
    break;}
case 227:
#line 687 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_LINEAR, TEXFILTER_LINEAR);		;
    break;}
case 228:
#line 688 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ANISOTROPIC, TEXFILTER_ANISOTROPIC);	;
    break;}
case 229:
#line 691 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_MAXANISOTROPY);	;
    break;}
case 230:
#line 692 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 231:
#line 696 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_COLOUROP);		;
    break;}
case 232:
#line 697 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 233:
#line 701 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_ALPHAOP);			;
    break;}
case 234:
#line 702 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();							;
    break;}
case 235:
#line 706 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_CONSTANTCOLOUR);			;
    break;}
case 236:
#line 707 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 237:
#line 711 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DISABLE, TEXOP_DISABLE);										;
    break;}
case 238:
#line 712 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SELECTARG1, TEXOP_SELECTARG1);									;
    break;}
case 239:
#line 713 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SELECTARG2, TEXOP_SELECTARG2);									;
    break;}
case 240:
#line 714 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MODULATE, TEXOP_MODULATE);										;
    break;}
case 241:
#line 715 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MODULATE2X, TEXOP_MODULATE2X);									;
    break;}
case 242:
#line 716 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MODULATE4X, TEXOP_MODULATE4X);									;
    break;}
case 243:
#line 717 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ADD, TEXOP_ADD);												;
    break;}
case 244:
#line 718 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ADDSIGNED, TEXOP_ADDSIGNED);									;
    break;}
case 245:
#line 719 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SUBTRACT, TEXOP_SUBTRACT);										;
    break;}
case 246:
#line 720 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ADDSMOOTH, TEXOP_ADDSMOOTH);									;
    break;}
case 247:
#line 721 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BLENDDIFFUSEALPHA, TEXOP_BLENDDIFFUSEALPHA	);					;
    break;}
case 248:
#line 722 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BLENDTEXTUREALPHA, TEXOP_BLENDTEXTUREALPHA	);					;
    break;}
case 249:
#line 723 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BLENDFACTORALPHA, TEXOP_BLENDFACTORALPHA	);					;
    break;}
case 250:
#line 724 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BLENDTEXTUREALPHAPM, TEXOP_BLENDTEXTUREALPHAPM);				;
    break;}
case 251:
#line 725 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BLENDCURRENTALPHA, TEXOP_BLENDCURRENTALPHA);					;
    break;}
case 252:
#line 726 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_PREMODULATE, TEXOP_PREMODULATE);								;
    break;}
case 253:
#line 727 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MODULATEALPHA_ADDCOLOUR, TEXOP_MODULATEALPHA_ADDCOLOUR);		;
    break;}
case 254:
#line 728 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MODULATECOLOUR_ADDALPHA, TEXOP_MODULATECOLOUR_ADDALPHA);		;
    break;}
case 255:
#line 729 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DOTPRODUCT3, TEXOP_DOTPRODUCT3);								;
    break;}
case 256:
#line 730 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_MULTIPLYADD, TEXOP_MULTIPLYADD);								;
    break;}
case 257:
#line 731 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_LERP, TEXOP_LERP);												;
    break;}
case 258:
#line 735 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_CURRENT, TEXARG_CURRENT);		;
    break;}
case 259:
#line 736 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_TEXTURE, TEXARG_TEXTURE);		;
    break;}
case 260:
#line 737 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_DIFFUSE, TEXARG_DIFFUSE);		;
    break;}
case 261:
#line 738 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SPECULAR, TEXARG_SPECULAR);	;
    break;}
case 262:
#line 739 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_CONSTANT, TEXARG_CONSTANT);	;
    break;}
case 263:
#line 743 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_TEXCOORDGEN);	;
    break;}
case 264:
#line 744 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();						;
    break;}
case 265:
#line 748 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_NONE, TEXGEN_NONE);								;
    break;}
case 266:
#line 749 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SPHEREMAP, TEXGEN_SPHEREMAP);						;
    break;}
case 267:
#line 750 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_EYESPACE_REFLECTION, TEXGEN_EYESPACE_REFLECTION);	;
    break;}
case 268:
#line 751 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_EYESPACE_NORMAL, TEXGEN_EYESPACE_NORMAL);			;
    break;}
case 269:
#line 755 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SCROLL);					;
    break;}
case 270:
#line 756 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 271:
#line 760 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_ROTATE);					;
    break;}
case 272:
#line 761 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 273:
#line 765 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SCALE);					;
    break;}
case 274:
#line 766 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 275:
#line 770 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SCROLLANIM);				;
    break;}
case 276:
#line 771 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 277:
#line 775 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_ROTATEANIM);				;
    break;}
case 278:
#line 776 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 279:
#line 780 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_SCALEANIM);				;
    break;}
case 280:
#line 781 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 281:
#line 785 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_WAVEXFORM);				;
    break;}
case 282:
#line 788 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 291:
#line 805 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_XFORMTYPE);				;
    break;}
case 292:
#line 806 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 293:
#line 810 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SCROLL_X, XFORM_SCROLL_X);					;
    break;}
case 294:
#line 811 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SCROLL_Y, XFORM_SCROLL_Y);					;
    break;}
case 295:
#line 812 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ROTATE, XFORM_ROTATE);						;
    break;}
case 296:
#line 813 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SCALE_X, XFORM_SCALE_X);					;
    break;}
case 297:
#line 814 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SCALE_Y, XFORM_SCALE_Y);					;
    break;}
case 298:
#line 818 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_WAVETYPE);				;
    break;}
case 299:
#line 819 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 300:
#line 823 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SINE, WAVE_SINE);							;
    break;}
case 301:
#line 824 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SQUARE, WAVE_SQUARE);						;
    break;}
case 302:
#line 825 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_SAWTOOTH, WAVE_SAWTOOTH);					;
    break;}
case 303:
#line 826 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_INVERSE_SAWTOOTH, WAVE_INVERSE_SAWTOOTH);	;
    break;}
case 304:
#line 827 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_TRIANGLE, WAVE_TRIANGLE);					;
    break;}
case 305:
#line 831 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_BASE);					;
    break;}
case 306:
#line 832 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 307:
#line 836 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_PHASE);					;
    break;}
case 308:
#line 837 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 309:
#line 841 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_AMPLITUDE);				;
    break;}
case 310:
#line 842 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 311:
#line 846 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddRootNode(NODETYPE_FREQUENCY);				;
    break;}
case 312:
#line 847 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.EndRootNode();									;
    break;}
case 313:
#line 851 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_ALWAYS, CMP_ALWAYS);				;
    break;}
case 314:
#line 852 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_NEVER, CMP_NEVER);				;
    break;}
case 315:
#line 853 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_LESS, CMP_LESS);					;
    break;}
case 316:
#line 854 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_LEQUAL, CMP_LEQUAL);				;
    break;}
case 317:
#line 855 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_EQUAL, CMP_EQUAL);				;
    break;}
case 318:
#line 856 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_NOTEQUAL, CMP_NOTEQUAL);			;
    break;}
case 319:
#line 857 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_GEQUAL, CMP_GEQUAL);				;
    break;}
case 320:
#line 858 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_GREATER, CMP_GREATER);			;
    break;}
case 325:
#line 872 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode( NODETYPE_STRINGLITERAL, yyvsp[0] ); ;
    break;}
case 326:
#line 875 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{   
							Float value = 0.0f;
						    std::stringstream str(yyvsp[0]);
						    str >> value;
						   
						    //std::cout << "Value = " << $1 << std::endl;
						   
							m_tree.AddNode(NODETYPE_FLOATVALUE, boost::any(value) );
						 ;
    break;}
case 327:
#line 887 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{   
							UInt value = 0.0f;
						    std::stringstream str(yyvsp[0]);
						    str >> value;
						   
						    //std::cout << "Value = " << $1 << std::endl;
						   
							m_tree.AddNode(NODETYPE_FLOATVALUE, boost::any(value) );
						 ;
    break;}
case 328:
#line 899 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{   
							Int value = 0.0f;
						    std::stringstream str(yyvsp[0]);
						    str >> value;
						   
						    //std::cout << "Value = " << $1 << std::endl;
						   
							m_tree.AddNode(NODETYPE_UINTVALUE, boost::any(value) );
						 ;
    break;}
case 331:
#line 914 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BOOLEAN, boost::any(true));	 ;
    break;}
case 332:
#line 918 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"
{ m_tree.AddNode(NODETYPE_BOOLEAN, boost::any(false));	 ;
    break;}
}

#line 811 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc"
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_EffectParserBase_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_EffectParserBase_DEBUG != 0
  if (YY_EffectParserBase_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_EffectParserBase_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_EffectParserBase_LLOC.first_line;
      yylsp->first_column = YY_EffectParserBase_LLOC.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  YYGOTO(yynewstate);

YYLABEL(yyerrlab)   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++YY_EffectParserBase_NERRS;

#ifdef YY_EffectParserBase_ERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      YY_EffectParserBase_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_EffectParserBase_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_EffectParserBase_ERROR_VERBOSE */
	YY_EffectParserBase_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_EffectParserBase_CHAR == YYEOF)
	YYABORT;

#if YY_EffectParserBase_DEBUG != 0
      if (YY_EffectParserBase_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_EffectParserBase_CHAR, yytname[yychar1]);
#endif

      YY_EffectParserBase_CHAR = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  YYGOTO(yyerrhandle);

YYLABEL(yyerrdefault)  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) YYGOTO(yydefault);
#endif

YYLABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YY_EffectParserBase_LSP_NEEDED
  yylsp--;
#endif

#if YY_EffectParserBase_DEBUG != 0
  if (YY_EffectParserBase_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

YYLABEL(yyerrhandle)

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yyerrdefault);

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    YYGOTO(yyerrdefault);

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrpop);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrpop);

  if (yyn == YYFINAL)
    YYACCEPT;

#if YY_EffectParserBase_DEBUG != 0
  if (YY_EffectParserBase_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_EffectParserBase_LVAL;
#ifdef YY_EffectParserBase_LSP_NEEDED
  *++yylsp = YY_EffectParserBase_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */

/* #line 1010 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Tools\\flex++bison++\\bison.cc" */
#line 3324 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar/EffectParserBase.cpp"
#line 921 "c:\\Documents and Settings\\Bryan\\My Documents\\PerforceWorkspace\\OidFX\\Source\\Renderer\\Grammar\\EffectParserBase.y"

