#include <cstdio>
#include <cstdlib>
#include <string>

#include "Debug.h"

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
Debug::set_yydebug(1);
#endif

#include "data.h"
#define YYSTYPE data

#include "ucc.tab.h"
#include "symtab.h"
#include "List.h"
#include "command.h"
#include "main.h"
#include "trans.h"
#include "ucc.l.h"
extern int yyparse(void);

int main(int argc, char **argv){
	Compiler compiler{};
	compiler.founderror=FALSE;
	compiler.othercounter=1;
	compiler.globalcount=0;
	param_offset=0;
	initializelabel();
	compiler.filename = NULL;
	if(checkargs(argc,argv) == -1){
		#ifdef DEBUG
			compiler.filename = "main.c";
			debugprint("No arguments given to compiler","");
		#endif
		return -1;
	}
	if((compiler.filename = openfile(argc, argv)) == NULL){
		return -1;
	}
	compiler.mysymtab = createTree(100);
	if(compiler.mysymtab == NULL){
		compiler.filename=NULL;
		compiler.filename = "main.c";
		error("Unable to construct symbol table","");
		return -1;
	}

	compiler.offset_counter=5;
	yyparse();

	#ifdef DEBUG
	printTree(compiler.mysymtab);
	#endif
	deleteTree(compiler.mysymtab);
	if(compiler.infile !=NULL)
		fclose(compiler.infile);
	return 0;

}
