// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include "machine.hpp"

#include "assembler.hpp"

int main(const int argc, const char ** argv) {
// 	using namespace project5;
	using Machine = project5::Machine;
	using Assembler = project5::Assembler;
	using e_instruction = Machine::e_instruction;
	using e_register = Machine::e_register;
	using e_argument_type = Machine::e_argument_type;

	Assembler as{};
	if(argc > 1) {
		std::string name{argv[1]};
		as.readFile(name);
		as.outputToFile("example.o");
	}
	return 0;
}
