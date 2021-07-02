// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include "machine.hpp"

int main(const int argc, const char ** argv) {
	using Machine = project5::Machine;
	using e_instruction = Machine::e_instruction;
	using e_register = Machine::e_register;
	using e_argument_type = Machine::e_argument_type;

	Machine m{};

	m.loadProgramFromFile("example.o");
	std::cout <<"Printing Program before run\n";
	m.printProgram();
	m.run();
	return 0;
}
