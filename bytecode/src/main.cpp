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

	Machine m{};
	Assembler as{&m};
	if(argc > 1) {
		std::string name{argv[1]};
		as.readFile(name);
		as.outputToFile("example.o");
	}
	/*
	Machine m{};
	Machine::program_t program{};
	program.ip = 1;
	program.sp = 1;
	program.bp = 1;
	program.acc = 0;
	program.program_mem[1] = m.encode(e_instruction::MOV, e_argument_type::REG,
													e_argument_type::MEM);  // MOV AL, 66
	program.program_mem[2] = static_cast<uint8_t>(e_register::AL);  // AL register
	program.program_mem[3] = 42;  // decimal 42 hex 2a
	program.program_mem[4] = m.encode(e_instruction::MOV, e_argument_type::REG,
													e_argument_type::INL);  // MOV
	program.program_mem[5] = static_cast<uint8_t>(e_register::CL);  // AL register
	program.program_mem[6] = 61;  // decimal 42 hex 2a
	program.program_mem[7] = m.encode(e_instruction::MOV, e_argument_type::REG,
													e_argument_type::MEM);  // MOV DL, 42
	program.program_mem[8] = static_cast<uint8_t>(e_register::DL);
	program.program_mem[9] = 66;  // decimal 66 hex 42
	program.program_mem[10] = m.encode(e_instruction::HALT);  // HALT with return
																			// value of dl register
	program.program_mem[61] = 120;
	m.loadProgram(&program);
	std::cout <<"Printing Program before run\n";
	m.printProgram();
	m.run();
*/
	return 0;
}
