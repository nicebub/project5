#include <cstdio>
#include <cstdlib>
#include <string>

#ifndef MAIN
	#define MAIN
#endif

#include "debug.hpp"
#include "type.hpp"
#include "data.hpp"
#include "list.hpp"
#include "symtab.hpp"
#include "trans.hpp"
#include "compiler.hpp"
#include "ucc.tab.hpp"


//extern int yydebug;

using namespace ucc;

int main(int argc, const char **argv){
	Compiler compiler{};
//		yydebug = 1;
	if(! compiler.openedInputFile(argc,argv)){
		debugprint("No arguments given to compiler","");	//only when in debug mode
		return -1;
	}
	if( ! compiler.openOutputFile(argc, argv) ){
		return -1;
	}

	compiler.code_generator.setstream(compiler.outfile);

	compiler.parser->parse();

	#ifdef DEBUG
	compiler.mysymtab->printTree();
	#endif

	return 0;

}
