#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
#endif

#include "compiler.hpp"

using namespace ucc;

int Compiler::checkargs(int argc, const char** argv){
	if(argc >1){
		std::string temp{argv[1]};

		if(temp.ends_with(".c")){
			yyin = std::fopen(argv[1], "r");
			if(yyin == NULL){
				std::cerr << argv[1] << ": cannot open input file\n";
				return -1;
			}
			else return 1;
		}
		else{
			std::cerr << argv[1] << ": does not end in .c\n";
			return -1;
		}
	}
	else{
		std::cerr << "did not recieve an input file\n";
		return -1;
	}

}

std::string Compiler::openfile(int argc, const char** argv){
	std::string tempstr{argv[1]};
	if(tempstr.ends_with(".c")){
		const size_t a{tempstr.length()-2};

		tempstr[a] = '.';
		tempstr[a+1] = 'a';
		tempstr += 's';
		tempstr += 'm';
		#ifdef DEBUG
		std::cerr << "trying to open file: " << tempstr << std::endl;
		#endif
		if((infile = std::fopen(tempstr.c_str(),"w"))==NULL){
			std::cerr << "cannot open file " << tempstr << " for writing\n";
			return NULL;
		}
		else{
			return tempstr;
		}
	}
	else{
		return NULL;
	}
}

#ifndef MAIN
#define MAIN
FILE* yyin;
int main(int argc, const char** argv){
	Compiler compiler{};

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
	return 0;
}
#endif