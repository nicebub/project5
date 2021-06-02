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


#include "ucc.tab.hpp"


using namespace ucc;

int main(int argc, const char **argv){
	Compiler compiler{};

	if(compiler.checkargs(argc,argv) == -1){

		#ifdef DEBUG
			debugprint("No arguments given to compiler","");
		#endif

		return -1;
	}
	if( ! compiler.openOutputFile(argc, argv) ){
		return -1;
	}

	compiler.code_generator.setstream(compiler.outfile);

	/*
	if(compiler.mysymtab == NULL){
		compiler.error("Unable to construct symbol table","");
		return -1;
	}
	*/
	compiler.parser->parse();

	#ifdef DEBUG
	compiler.mysymtab.printTree();
	#endif

	return 0;

}