#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
#endif

#include "compiler.hpp"
#include "ucc.tab.hpp"

using namespace ucc;

namespace ucc{

bool Compiler::endsWC(const std::string& in){
	std::string extra{""};
	extra = in[(in.size()-1)];
	extra += in[(in.size()-2)];
	return extra == "c.";
	
}
int Compiler::checkargs(int argc, const char** argv){
	if(argc >1){
		std::string temp{argv[1]};
		if(endsWC(temp)){
			std::ifstream* next;
			next = new std::ifstream;
			next->open(argv[1], std::ifstream::in);
			if(!next->is_open()){
				std::cerr << argv[1] << ": cannot open input file\n";
				return -1;
			}
			else{
				lexer.switch_streams(next); 
				return 1;
			}
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

bool Compiler::openOutputFile(int argc, const char** argv){
	std::string tempstr{argv[1]};
	if(endsWC(tempstr)){
		const size_t a{tempstr.length()-2};

		tempstr[a] = '.';
		tempstr[a+1] = 'a';
		tempstr += 's';
		tempstr += 'm';
		#ifdef DEBUG
		std::cerr << "trying to open file: " << tempstr << std::endl;
		#endif
		std::ofstream* next{new std::ofstream{tempstr, std::fstream::out}};
		if(!next->is_open()){
			std::cerr << "cannot open file " << tempstr << " for writing\n";
			return false;
		}
		else{
			outfile = next;
			filename = tempstr;
			return true;
		}
	}
	else{
		return false;
	}
}

#ifndef MAIN
#define MAIN
//FILE* yyin;
int main(int argc, const char** argv){
	Compiler compiler{};

	if(compiler.checkargs(argc,argv) == -1){
		#ifdef DEBUG
			compiler.filename = "main.c";
			debugprint("No arguments given to compiler","");
		#endif
		return -1;
	}
	if(!compiler.openOutputFile(argc, argv)){
		return -1;
	}
	return 0;
}
}
#endif