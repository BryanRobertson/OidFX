//======================================================================================
//! @file         EffectParser.cpp
//! @brief        Class that parses effects from .ofx files on disk
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
#include "Core/SyntaxTree.h"
#include "Renderer/Effect.h"
#include "Renderer/EffectParser.h"
#include "Renderer/EffectSyntaxTreeNodeTypes.h"
#include "Renderer/EffectSyntaxTreeParser.h"
#include "EffectParserBase.h"
#include "EffectLexer.h"


using namespace Renderer;



//!@class	EffectFileParser
//!@brief	Class that parses an effect file, and generates a syntax tree from it
class EffectFileParser : protected EffectParserBase
{

	public:

		EffectFileParser( Core::SyntaxTree<Renderer::EEffectNodeType>& tree, const Char* fileName );
		
		void Parse( );


	protected:

		virtual void yyerror( Char* msg );
		virtual Int yylex();

	private:

		std::string					   m_fileName;
		std::ifstream				   m_file;
		boost::shared_ptr<EffectLexer> m_lexer;

};
//End class EffectFileParser



//=========================================================================
//! @function    EffectFileParser::EffectFileParser
//! @brief       EffectFileParser constructor
//!              
//! @throw		 Core::RuntimeError if the         
//=========================================================================
EffectFileParser::EffectFileParser ( Core::SyntaxTree<Renderer::EEffectNodeType>& tree, const Char* fileName )
: EffectParserBase(tree), m_fileName(fileName)
{

	debug_assert ( fileName, "Error, null pointer passed as effect filename!" );

	m_file.open ( fileName );

	if ( !m_file )
	{
		std::ostringstream errorMessage;
		errorMessage << "Error, couldn't find effect file " << fileName << ". Loading failed!" << std::endl;

		throw ( Core::RuntimeError( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ ) );
	}

	std::clog << "\nEffect file " << fileName << " opened for reading" << std::endl;

	m_lexer = boost::shared_ptr<EffectLexer> ( new EffectLexer(m_file) );
}
//End EffectFileParser::EffectFileParser



//=========================================================================
//! @function    EffectFileParser::yyerror
//! @brief       Function called on parser error
//!              
//! @throw		 Core::RuntimeError if parsing failed             
//=========================================================================
void EffectFileParser::yyerror( Char* msg )
{
	std::stringstream errorMessage;

	errorMessage << "Error parsing effect " << m_fileName << "\n"
				 << " line: " << yylloc.first_line << " char: " << yylloc.first_column <<  ": "
				 << msg << " : Stopped at <" << yylloc.text << ">" <<  std::endl;

	throw Core::RuntimeError ( errorMessage.str().c_str(), 0, __FILE__, __FUNCTION__, __LINE__ );
}
//End EffectFileParser::yyerror



//=========================================================================
//! @function    EffectFileParser::yylex
//! @brief       Function called by the parser to do lexical analysis
//!              
//=========================================================================
Int EffectFileParser::yylex()
{
	yylloc.first_line	= m_lexer->m_line;
	yylloc.first_column = m_lexer->m_column;
	Int token			= m_lexer->yylex(&yylval, &yylloc);
	yylloc.last_line	= m_lexer->m_line;
	yylloc.last_column  = m_lexer->m_column;
	yylloc.text			= (Char*)m_lexer->yytext;

	return token;
}
//End EffectFileParser::yylex



//=========================================================================
//! @function    EffectFileParser::Parse
//! @brief       Causes the effect file parser to parse the effect file
//!              
//! 
//! @throw       Core::RuntimeError if parsing failed
//=========================================================================
void EffectFileParser::Parse ()
{
	Int result = yyparse();

	if ( result == 0 )
	{
		std::clog << "Effect file parsed successfully!" << std::endl;
	}
}
//End EffectFileParser::Parse



//=========================================================================
//! @function    EffectParser::EffectParser
//! @brief       Effect parser constructor
//!              
//!              
//=========================================================================
EffectParser::EffectParser ( )
{

}
//End EffectParser::EffectParser



//=========================================================================
//! @function    EffectParser::ParseEffectFromFile
//! @brief       Parse an effect from a file
//!              
//! @param       fileName [in] Filename of the effect 
//! @param		 renderer [in] Reference to the renderer
//!              
//! @return      A pointer to the effect
//! @throw       Core::RuntimeError if the effect could not be loaded
//=========================================================================
boost::shared_ptr<Effect> EffectParser::ParseEffectFromFile ( const Char* fileName, Renderer::IRenderer& renderer )
{
	Core::SyntaxTree<EEffectNodeType> tree ( NODETYPE_ROOT );
	EffectFileParser fileParser( tree, fileName );
	boost::shared_ptr<Effect> effect;

	try
	{
		fileParser.Parse();

		std::clog << "Parsing effect syntax tree" << std::endl;

		EffectSyntaxTreeParser treeParser ( tree, fileName, renderer );
		effect = boost::shared_ptr<Effect>(treeParser.ParseTree());

		std::clog << "Effect syntax tree parsed successfully\n" << std::endl;
	}
	catch ( Core::RuntimeError& exp )
	{
		std::cerr << "Error parsing effect:\n\n" << exp.What() << "\n\n setting effect to defaults" << std::endl;

		effect = boost::shared_ptr<Effect>(new Effect(fileName));

		Technique technique;
		technique.AddPass(Pass(RenderState()));

		effect->AddTechnique(technique);
	}

	return effect;	
}
//End EffectParser::ParseEffectForFile