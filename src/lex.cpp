#include <string>
#include <istream>

#include "lex.hpp"
#include "location.hh"
#include "compiler.hpp"

using namespace ucc;

namespace ucc{
//		uccLexer::uccLexer() : string_buf{}, yylval{nullptr}, loc{new uccParser::location_type()}, compiler() {}
		uccLexer::~uccLexer(){ delete loc; loc = nullptr; }

		uccLexer::uccLexer(std::istream* in, Compiler& compiler) : yyFlexLexer(in), compiler{compiler} {
				loc = new uccParser::location_type();
				string_buf = "";
		}
}
