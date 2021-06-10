#include <string>
#include <iostream>
#ifndef MAIN
	#define MAIN
#endif

#include "debug.hpp"
#include "compiler.hpp"
using namespace ucc;

int main(int argc, const char **argv){
	Compiler compiler{};

	if(! compiler.openedInputFile(argc,argv)){
//		std::cerr << "No arguments given to compiler\n";
		return -1;
	}
	if( ! compiler.openedOutputFile(argc, argv) ){
		return -1;
	}

	compiler.code_generator.setstream(compiler.outfile);

	compiler.parser->parse();

	#ifdef DEBUG
	compiler.mysymtab->printTree();
	#endif

	return 0;

}
