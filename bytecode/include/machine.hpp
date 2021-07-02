// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_MACHINE_HPP_
#define BYTECODE_INCLUDE_MACHINE_HPP_

#include <unistd.h>
#include <array>
#include <string>
#include "program.hpp"
namespace project5 {

class Machine {
	public:
		#define to_e_register(x) static_cast<Machine::e_register>((x))
		#define to_e_argument_type(x) static_cast<Machine::e_argument_type>((x))
		#define to_e_instruction(x) static_cast<Machine::e_instruction>((x))

		static constexpr size_t MEMSIZE = 65536;

		enum class e_register {
				IP,  // Instruction Pointer
				SP,  // Stack Pointer
				BP,  // Base Pointer
				ACPP,  // Accumulator Pointer
				AL,  // General Purpose #1 Pointer
				BL,  // General Purpose #2 Pointer
				CL,  // General Purpose #3 Pointer
				DL  // General Purpose #4 Pointer
		};
		enum class e_argument_type {
				INL,  // Inline -- included as part of instruction
				REG,  // Register
				MEM,  // Memory -- can be found in memory
				IND  // Memory -- but indirect addressing
		};
		enum class e_instruction{
				HALT = 0x1,  // Stop Machine
				MOV,  // Move value or address to 1st argument
				ADD,  // add two values store in 1st argument
				SUB,  // sub 2nd from 1st value store in 1st
				DIV,  // div 2nd from 1st argument store in 1st may be in 2 registers
				MUL,  // mul 1st by 2nd argument
				JMP,  // set next instruction to where Jmp label is located
				JMPZ,  // if zero flag is set, then jump to label
// 				ZERO,
				CALL,  // Call a function stored elsewhere
				PUSH,  // push a value or address onto the stack
				POP,  // pop a value or address off of the stack
				LEA,  // Load Effective address, loads more complex address if needed
				XOR,  // logical exclusive or
				OR,  // logical or
				AND,  // logical and
				SHL,  // shift bits left by argument 1, ending 0s added
				SHR,  // shift bits right by argument 1, leading 0s added for extension
		};
		enum class e_flag {
				M_IOP = 0x01,  // Invalid Operation - no such instruction
				M_ZERO = 0x02,  // last ALU operation was zero?
				M_CARRY = 0x04,  // last ALU operation had a carry over bit in MSb
				M_OVER = 0x08,  // overflow
				M_UNDER = 0x10,  // underflow
				z = 0x20,
				r = 0x40,
				f = 0x80
		};

// 		using program_t = Program;  // type to use for programs
		using register_t = Program::register_t;
		using memory_t = Program::memory_t;

		using e_instruction = Machine::e_instruction;
		using e_register = Machine::e_register;
		using e_argument_type = Machine::e_argument_type;
		using main_memory_t = std::array<memory_t, MEMSIZE>;

		Machine();
		virtual ~Machine();
		Machine(const Machine&);
		Machine& operator=(const Machine&);
		void loadProgram(Program* program);
		void loadProgramFromFile(const std::string name);
		void run();
		void printProgram();

		register_t fetch();
		register_t* fetch_addr();
		register_t* fetch_addr_from(Program::memory_t m);
		register_t encode(e_instruction);
		register_t encode(e_instruction, e_argument_type, e_argument_type);

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

std::ostream& operator<<(std::ostream& o, const Machine::e_instruction& e);
std::ostream& operator<<(std::ostream& o, const uint8_t& in);
std::ostream& operator<<(std::ostream& o, const program_memory_t& in);
std::ostream& operator<<(std::ostream& o, const Machine::main_memory_t& in);

};  // namespace project5

#endif  // BYTECODE_INCLUDE_MACHINE_HPP_
