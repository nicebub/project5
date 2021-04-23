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

#include "type.h"
#include "data.h"
#include "List.h"
#include "symtab.h"
#include "trans.h"
#include "compiler.hpp"
#ifndef YYSTYPE
#define YYSTYPE ucc::data
#endif
#include "ucc.tab.hpp"
///#include "main.h"

extern FILE* yyin;
extern int yyparse(void);
extern int error(std::string s1, std::string s2);

using namespace ucc;

int main(int argc, const char **argv){
	Compiler compiler{};

	CodeGenerator::initializelabel();

	if(compiler.checkargs(argc,argv) == -1){
		#ifdef DEBUG
			compiler.filename = "main.c";
			debugprint("No arguments given to compiler","");
		#endif
		return -1;
	}
	if((compiler.filename = compiler.openfile(argc, argv)).empty()){
		return -1;
	}
//	compiler.mysymtab = createTree(100);
	if(compiler.mysymtab == NULL){
		compiler.filename = "main.c";
		error("Unable to construct symbol table","");
		return -1;
	}

	yyparse();

	#ifdef DEBUG
	printTree(compiler.mysymtab);
	#endif

//	deleteTree(compiler.mysymtab);
	if(compiler.infile !=NULL)
		fclose(compiler.infile);
	return 0;

}
