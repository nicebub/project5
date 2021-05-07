#ifndef _LEX_HPP
#define _LEX_HPP 1

#include <string>
#include <istream>
#include <iostream>
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

//#include "Compiler.hpp"
#include "ucc.tab.hpp"
#include "location.hh"
namespace ucc{

	class uccLexer : public yyFlexLexer {
		public:
//			uccLexer();
			uccLexer(std::istream* in, Compiler& compiler);

//			using FlexLexer::yylex;

			virtual uccParser::symbol_type yylex(uccParser::semantic_type* const lval,
					uccParser::location_type* location);
					
			virtual ~uccLexer();
		private:
			uccParser::semantic_type* yylval = nullptr;
			uccParser::location_type* loc = nullptr;
			Compiler& compiler;
			std::string string_buf{""};
//			std::string* string_buf_ptr = nullptr;
	};
}

#endif