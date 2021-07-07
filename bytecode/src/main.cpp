// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include "machine.hpp"

int main(const int argc, const char ** argv) {
	if(argc > 1) {
		project5::Machine m{};
		m.loadProgramFromFile(argv[1]);
		std::cout <<"Printing Program before run\n";
		m.printMachineState();
		auto result{m.run()};
		std::cout << "Printing Program after run\n";
		m.printMachineState();
		return result;
	}
	std::cout << "Usage: [exec] filename.asm -- where filename.asm is an assembly";
	std::cout << " file\n";
	return 0;
}
