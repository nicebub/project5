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
	std::cout << "Usage:\n"<< argv[0] << " [filename.o] -- where filename.o is a";
	std::cout << " bytecode object file\n";
	return 0;
}
