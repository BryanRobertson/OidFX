//======================================================================================
//! @file         ConsoleCommandLineParser.cpp
//!               The ConsoleCommandLineParser takes in a command line string
//!				  and converts it into a command name string, with arguments.
//!				  The parser is capable of interpreting boolean, integer, unsigned integer
//!				  floating point arguments, and string literals, enclosed in quotes ("") 
//!				  
//!                              
//! @author       Bryan Robertson
//! @date         Friday, 11 March 2005
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

//Enable parser debugging
//#define BOOST_SPIRIT_ASSERT_EXCEPTION std::exception
//#define BOOST_SPIRIT_DEBUG


#include <boost/spirit/core.hpp>
#include <iostream>
#include "Core/BasicTypes.h"
#include "Core/Debug.h"
#include "Core/ConsoleCommandLineParser.h"


using namespace boost::spirit;
using namespace Core;


//======================================================================================
// Functors for actions, used by boost::spirit parser
//======================================================================================


//AddBooleanToArgs
//Add a boolean value to the argument list
class AddBooleanToArgs
{
	public:

		AddBooleanToArgs ( std::vector<boost::any>& args, bool value )
			: m_args(args), m_value(value)
		{
		}

		void operator()(const Char* start, const Char* end) const
		{
			//std::clog << __FUNCTION__ << m_value << std::endl;
			m_args.push_back( m_value );
		}

	private:
		std::vector<boost::any>& m_args;
		bool m_value;
};
//end class AddBooleanToArgs


//class AddIntegerToArgs
//Add a signed integer value to the argument list
class AddIntegerToArgs
{
	public:
		AddIntegerToArgs ( std::vector<boost::any>& args )
			: m_args(args)
		{
		}

		void operator()(Int value ) const
		{
			//std::clog << __FUNCTION__ << value << std::endl;
			m_args.push_back( value );
		}

	private:
		std::vector<boost::any>& m_args;
};
//end class AddIntegerToArgs


//class AddUnsignedIntegerToArgs
//add an unsigned integer to the argument list
class AddUnsignedIntegerToArgs
{

	public:
		AddUnsignedIntegerToArgs ( std::vector<boost::any>& args )
			: m_args(args)
		{
		}

		void operator()( unsigned int value ) const
		{
			//std::clog << __FUNCTION__ << value << std::endl;
			m_args.push_back( value );
		}

	private:
		std::vector<boost::any>& m_args;
};
//end AddUnsignedIntegerToArgs


//class AddFloatToArgs
//Add a floating point value to the argument list
class AddFloatToArgs
{
	public:
		AddFloatToArgs ( std::vector<boost::any>& args )
			: m_args(args)
		{
		}

		void operator()( float value ) const
		{
			//std::clog << __FUNCTION__ << value << std::endl;
			m_args.push_back( value );
		}

	private:
		std::vector<boost::any>& m_args;
};
//end class AddFloatToArgs


//class AddString
//Add a string to the argument list
class AddString
{
	public:
		AddString ( std::vector<boost::any>& args )
			: m_args(args)
		{
		}

		void operator() (const Char* start, const Char* end) const
		{
			std::string str;
			if ( ((end - start) > 2) )
			{
				if ((*start == '\"') && (*(end-1) == '\"'))
				{
					str.assign ( start+1, end-1 );
				}
				else
				{
					str.assign ( start, end );
				}
			}

			//std::clog << __FUNCTION__ << str << std::endl;

			m_args.push_back(str);
		}

	private:
		
		std::vector<boost::any>& m_args;
};
//end AddString


//=========================================================================
//Skip grammar for the console
//=========================================================================
struct SkipGrammar : public grammar<SkipGrammar>
{
    template <typename ScannerT>
    struct definition
    {
        definition(SkipGrammar const& self)
        {
			skipgrammar = space_p ;
						//| ('#' >> *(anychar_p -'\n') >> !ch_p('\n'))
						//| ("\\" >> *(anychar_p) >> !ch_p('\n'));
        }

        rule<ScannerT> skipgrammar;

        rule<ScannerT> const&
        start() const { return skipgrammar; }
    };
};

//======================================================================================
//Console grammar for boost::spirit parser
//======================================================================================
class ConsoleGrammar : public grammar<ConsoleGrammar>
{
	public:

		ConsoleGrammar ( std::string& name, std::vector<boost::any>& args )
			:m_name(name), m_args(args)
		{
		}

		template <typename ScannerT>
		struct definition 
		{
			definition(ConsoleGrammar const& self)
	
			{
				consoleinput_t = comment_t | (identifier_t >> *argument_t >> !comment_t);

				argument_t =  real_t 
							| uint_t
							| int_t  
							| string_t
							| bool_t;

				identifier_t = 
					lexeme_d[ +(alpha_p | '_') >> *(alnum_p | '_')][assign<std::string>(self.Name())];

				int_t = 
					lexeme_d[ int_p ][AddIntegerToArgs(self.Args())];

				uint_t = 
					lexeme_d[ uint_p ][AddUnsignedIntegerToArgs(self.Args())];

				real_t = 
					lexeme_d[ strict_real_p ][AddFloatToArgs(self.Args())];

				string_t = 
					lexeme_d[(ch_p('\"') >> (*(~ch_p('\"')))[AddString(self.Args())] >> ch_p('\"'))];

				bool_t =
					lexeme_d[ str_p("true")[AddBooleanToArgs(self.Args(), true)]
						   | str_p("false")[AddBooleanToArgs(self.Args(), false)]
							];

				//Sigh, we have to put this here, because the parser reports a fail
				//if we put it in the skip grammar..
				comment_t = 
					(ch_p('#') >> *(anychar_p -'\n') >> !ch_p('\n'));

			}

			rule<ScannerT> consoleinput_t, identifier_t, bool_t, string_t, int_t, uint_t, real_t, argument_t, comment_t;
			rule<ScannerT> const& start() const { return consoleinput_t; }
		};
		//end class definition

		std::string& Name() const { return m_name;}
		std::vector<boost::any>& Args() const { return m_args; }

	private:

		std::string& m_name;
		std::vector<boost::any>& m_args;

};
//end class ConsoleGrammar


//======================================================================================
//ConsoleCommandLineParser methods
//======================================================================================


//=========================================================================
//! @function    ConsoleCommandLineParser::ConsoleCommandLineParser
//! @brief       Constructs a ConsoleCommandLineParser object, and
//!				 parses the input given. Clients can call Succeeded()
//!				 to determine whether or not the parse was successful
//!              
//! @param       input [in] 
//!              
//! @return      
//! @throw       
//=========================================================================
ConsoleCommandLineParser::ConsoleCommandLineParser ( const Char* input )
: m_succeeded(false)
{
	SkipGrammar skip;
	ConsoleGrammar consoleGrammar(m_commandName, m_arguments);    //  Our parser
    parse_info<> info = parse(input, consoleGrammar, skip);

	if ( (info.full) )
	{
		m_succeeded = true;
	}
	else
    {
		std::cerr << "Command line parse error, stopped at -> " << info.stop << std::endl;
		m_succeeded = false;

    }
}
//end ConsoleCommandLineParser::ConsoleCommandLineParser