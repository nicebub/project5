// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_MACHINE_HPP_
#define BYTECODE_INCLUDE_MACHINE_HPP_

#include <unistd.h>
#include <array>
#include <string>
#include "types.hpp"
#include "program.hpp"

namespace project5 {

	using register16_t = VM::register16_t;
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

		memory_t* resolvetype(e_argument_type in);
		register16_t* resolvetype16(e_argument_type in, e_register reg);

		e_instruction decode(register_t in);
		const bool isProgramLoaded() noexcept;
		void executeADD(e_argument_type arg1, e_argument_type arg2);
		void executeSUB(e_argument_type arg1, e_argument_type arg2);
		void executeMUL(e_argument_type arg1, e_argument_type arg2);
		void executeDIV(e_argument_type arg1, e_argument_type arg2);
		void executeMOV(e_argument_type arg1, e_argument_type arg2);

	protected:
	bool is16bit(e_argument_type arg);
		void loadProgramIntoMemory();
		void executeInstr(const register_t& instr,
			void(Machine::*func)(e_argument_type, e_argument_type));
		void executeMOV16(e_argument_type arg1, e_argument_type arg2);
		void executeADD16(e_argument_type arg1, e_argument_type arg2);
		void executeSUB16(e_argument_type arg1, e_argument_type arg2);
		void executeMUL16(e_argument_type arg1, e_argument_type arg2);
		void executeDIV16(e_argument_type arg1, e_argument_type arg2);
		register16_t* temp;

	private:
		bool programLoaded;
		main_memory_t memory;  // actual machine memory for now
		Program program;  // when loading a program
		register16_t ip;  // instruction pointer
		register16_t sp;  // stack pointer
		register16_t bp;  // base pointer
		register16_t AB;  // 16 bit or 2 8 bit registers
		register16_t CD;  // 16 bit or 2 8 bit registers
		register16_t HL;  // 16 bit or 2 8 bit registers
		register16_t XY;  // 16 bit or 2 8 bit registers
		register_t flags;  // flags, carry from ALU, ZERO, INTERRUPT,
								//  OTHERSS< ETC
	};
// 	using program_memory_t = VM::program_memory_t;

std::ostream& operator<<(std::ostream& o, const e_instruction& e);
std::ostream& operator<<(std::ostream& o, const register_t& in);
std::ostream& operator<<(std::ostream& o, const register16_t& in);
std::ostream& operator<<(std::ostream& o, const program_memory_t& in);
std::ostream& operator<<(std::ostream& o, const main_memory_t& in);

};  // namespace project5

#endif  // BYTECODE_INCLUDE_MACHINE_HPP_
