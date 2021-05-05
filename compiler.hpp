#ifndef _COMPILER_HPP
#define _COMPILER_HPP
#include <string>

#undef yyFlexLexer
#include <FlexLexer.h>
#define yyFlexLexer yyFlexLexer

#include "type.hpp"
#include "trans.hpp"
#include "symtab.hpp"

extern FILE* 						yyin;
extern int error(std::string, std::string);


const int INITIAL_TREE_SIZE = 100;

namespace ucc{
	class Compiler{
		public:
			yyFlexLexer	 			lexer;
			CodeGenerator 			code_generator;
			SymbolTable* 			mysymtab;

			Compiler();
			~Compiler();

			std::string openfile(int argc, const char** argv);
			int checkargs(int argc, const char** argv);

			static int error(std::string,std::string) noexcept;
			static int warning(std::string,std::string) noexcept;

			static std::ostream*	outfile;
			static std::string 	filename;
			static int 				Line_Number;
			static int 				globalcount;
			static int				offset_counter;
			static int				labelcounter;
			static int 				othercounter;
			static int 				param_offset;
			static int 				mainlocal;
			static bool 			founderror;

		private:
//			extern FILE*	infile;
//			Symtab*			mysymtab;
	};
}
#endif
