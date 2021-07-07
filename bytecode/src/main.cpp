// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include "machine.hpp"

int main(const int argc, const char ** argv) {
	using Machine = project5::Machine;

	std::cout <<"Printing Program before run\n";

	Machine m{};
	   m.loadProgramFromFile(argv[1]);
	m.printMachineState();
	auto result = m.run();
	std::cout << "Printing Program after run\n";
	m.printMachineState();
	return result;
}
