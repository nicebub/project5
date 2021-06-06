#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include "debug.hpp"
#include "compiler.hpp"
#include "ucc.tab.hpp"

namespace ucc{

bool Compiler::endsWC(const std::string& in){
	std::string extra{""};
	extra = in[(in.size()-1)];
	extra += in[(in.size()-2)];
	return extra == "c.";
}
bool Compiler::openedInputFile(int argc, const char** argv){
	if(argc >1){
		if(endsWC(argv[1])){
			try{
			std::ifstream* next{new std::ifstream{argv[1], std::ifstream::in}};
//			next = new std::ifstream;
//			next->open(argv[1], std::ifstream::in);
			if(next->is_open()){
				lexer.switch_streams(next); 
				return true;
			}
			}
			catch(std::bad_alloc& e){
//				std::cerr << argv[1] << ": cannot open input file\n";
				debugprint(e.what(),"");
			}
			std::cerr << argv[1] << ": cannot open input file\n";
		}
		else
			std::cerr << argv[1] << ": does not end in .c\n";
	}
	else
		std::cerr << "did not recieve an input file\n";
	return false;
}

bool Compiler::openOutputFile(int argc, const char** argv){
	std::string tempstr{argv[1]};
	if(endsWC(tempstr)){
		const size_t a{tempstr.length()-2};

		tempstr[a] = '.';
		tempstr[a+1] = 'a';
		tempstr += "sm";
		
		debugprint("trying to open file: ", tempstr);
		try{
			std::ofstream* next{new std::ofstream{tempstr, std::fstream::out}};
			if(next->is_open()){
				outfile = next;
				filename = tempstr;
				return true;
			}
		}
		catch(std::bad_alloc& e){
			std::cerr << "cannot open file " << tempstr << " for writing\n";
			debugprint(e.what(),"");
//			return false;
		}
	}
		return false;
}

#ifndef MAIN
#define MAIN
//FILE* yyin;
int main(int argc, const char** argv){
	Compiler compiler{};

	if(! compiler.openedInputFile(argc,argv) ){
		compiler.filename = "main.c";
		debugprint("No arguments given to compiler","");
		return -1;
	}
	if(!compiler.openOutputFile(argc, argv)){
		return -1;
	}
	return 0;
}
}
#endif
