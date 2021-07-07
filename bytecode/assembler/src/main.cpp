// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include "assembler.hpp"

int main(const int argc, const char ** argv) {
	if(argc > 1) {
		std::string name{argv[1]};
		project5::Assembler as{};
		as.readFile(name);
		as.outputToFile(name+".o");
	}
	return 0;
}
