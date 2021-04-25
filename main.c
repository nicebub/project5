#include <cstdio>
#include <cstdlib>
#include <string>

#define MAIN

#ifdef DEBUGON
#include "Debug.hpp"
#ifndef DEBUG
#define DEBUG
#endif
Debug::set_yydebug(1);
#endif

#include "type.hpp"
#include "data.hpp"
#include "List.hpp"
#include "symtab.hpp"
#include "trans.hpp"
#include "compiler.hpp"

#ifndef YYSTYPE
#define YYSTYPE ucc::data
#endif

#include "ucc.tab.hpp"

extern FILE* 			yyin;

extern int 				yyparse(void);
extern int 				error(std::string s1, std::string s2);

using namespace ucc;

Compiler compiler{};

int main(int argc, const char **argv){

	if(compiler.checkargs(argc,argv) == -1){

		#ifdef DEBUG
			debugprint("No arguments given to compiler","");
		#endif

		return -1;
	}
	if((compiler.filename = compiler.openfile(argc, argv)).empty()){
		return -1;
	}
	compiler.code_generator.set_stream(compiler.outfile);
	if(compiler.mysymtab == NULL){
		error("Unable to construct symbol table","");
		return -1;
	}

	yyparse();

	#ifdef DEBUG
	compiler.mysymtab.printTree();
	#endif

	return 0;

}
