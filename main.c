#include <cstdio>
#include <cstdlib>
#include <string>

#define MAIN
#include "Debug.h"

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
Debug::set_yydebug(1);
#endif

#include "data.h"
#define YYSTYPE data

#include "ucc.tab.hpp"
#include "symtab.h"
#include "List.h"
#include "command.hpp"
#include "main.h"
#include "trans.h"
#include "ucc.l.h"
extern int yyparse(void);

int main(int argc, char **argv){
	Compiler compiler{};

	initializelabel();

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
