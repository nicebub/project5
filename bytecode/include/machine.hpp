// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_MACHINE_HPP_
#define BYTECODE_INCLUDE_MACHINE_HPP_

#include <unistd.h>
#include <array>
#include <string>
#include "types.hpp"
#include "program.hpp"

namespace project5 {

	using register_t = VM::register_t;
	using memory_t = VM::memory_t;
	using program_memory_t = VM::program_memory_t;
	using main_memory_t = VM::main_memory_t;

	using e_instruction = VM::e_instruction;
	using e_register = VM::e_register;
	using e_argument_type = VM::e_argument_type;

class Machine {
	public:
		Machine();
		virtual ~Machine();
		Machine(const Machine&);
		Machine& operator=(const Machine&);
		void loadProgram(const Program* program);
		void loadProgramFromFile(const std::string name);
		register_t run();
		void printMachineState();

		register_t fetch();
		register_t* fetch_addr();
		register_t* fetch_addr_from(memory_t m);
// 		register_t encode(e_instruction);
// 		register_t encode(e_instruction, e_argument_type, e_argument_type);

		memory_t* resolvetype(e_argument_type in);

		e_instruction decode(register_t in);
		const bool isProgramLoaded() noexcept;
		void executeADD(const register_t& instr);
		void executeMOV(const register_t& instr);

	protected:
		void loadProgramIntoMemory();

	private:
		bool programLoaded;
		main_memory_t memory;  // actual machine memory for now
		Program program;  // when loading a program
		register_t ip;  // instruction pointer
		register_t sp;  // stack pointer
		register_t bp;  // base pointer
		register_t acc;  // accumulator
		register_t al;  // GPR
		register_t bl;  // GPR
		register_t cl;  // GPR
		register_t dl;  // GPR
		register_t flags;  // flags, carry from ALU, ZERO, INTERRUPT,
								//  OTHERSS< ETC
	};

	using program_memory_t = Program::program_memory_t;

std::ostream& operator<<(std::ostream& o, const e_instruction& e);
std::ostream& operator<<(std::ostream& o, const uint8_t& in);
std::ostream& operator<<(std::ostream& o, const program_memory_t& in);
std::ostream& operator<<(std::ostream& o, const main_memory_t& in);

};  // namespace project5

#endif  // BYTECODE_INCLUDE_MACHINE_HPP_
