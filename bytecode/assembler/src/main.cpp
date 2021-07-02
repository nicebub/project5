// Copyright 2021 Scott Lorberbaum

#include <iostream>
// #include "machine.hpp"

#include "assembler.hpp"

int main(const int argc, const char ** argv) {
	using Assembler = project5::Assembler;

	Assembler as{};
	if(argc > 1) {
		std::string name{argv[1]};
		as.readFile(name);
		as.outputToFile("example.o");
	}
	return 0;
}
