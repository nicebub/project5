#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "compiler.hpp"

using namespace ucc;

bool 				Compiler::founderror{false};

std::string 	Compiler::filename{""};

int 				Compiler::Line_Number{1};
int 				Compiler::globalcount{0};
int 				Compiler::offset_counter{5};
int 				Compiler::othercounter{1};
int 				Compiler::param_offset{0};
int 				Compiler::mainlocal{0};

std::ostream* 			Compiler::outfile{&std::cout};


Compiler::Compiler(): mysymtab{SymbolTable::createTree(INITIAL_TREE_SIZE)}, code_generator{} {
	if(mysymtab == NULL){
		error("Unable to construct symbol table","");
	}
}
Compiler::~Compiler(){
	if(outfile->good()){

		#ifdef DEBUG
		std::cerr << "Closing file\n";
		#endif

		outfile->flush();
	}

	if(mysymtab != NULL){
		delete mysymtab;
		mysymtab = NULL;
	}
}
