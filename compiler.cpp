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
int 				Compiler::labelcounter{0};
int 				Compiler::othercounter{1};
int 				Compiler::param_offset{0};
int 				Compiler::mainlocal{0};

FILE* 			Compiler::infile{NULL};


Compiler::Compiler(): mysymtab{createTree(100)} {
	if(mysymtab == NULL){
		compiler.filename = "main.c";
		error("Unable to construct symbol table","");
	}
}
Compiler::~Compiler(){
	if(infile){
		#ifdef DEBUG
		std::cout << "Closing file\n";
		#endif
		std::fclose(infile);
	}
	if(mysymtab != NULL){
		deleteTree(mysymtab);
//		delete mysymtab;
		mysymtab = NULL;
	}
}
