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
#define as_int(x) static_cast<Program::register_t>((x))
#define as_reg_t(x) static_cast<Program::register_t>((x))

			enum class e_register {
				IP,
				SP,
				BP,
				ACPP,
				AL,
				BL,
				CL,
				DL
			};
#define to_e_register(x) static_cast<Machine::e_register>((x))
			enum class e_argument_type {
				INL,
				REG,
				MEM,
				IND
			};
#define to_e_argument_type(x) static_cast<Machine::e_argument_type>((x))
			enum class e_instruction{
				HALT = 0x1,
				MOV,
				ADD,
				SUB,
				DIV,
				MUL,
				JMP,
				JMPZ,
				ZERO,
				CALL,
				PUSH,
				POP,
				LEA
			};
#define to_e_instruction(x) static_cast<Machine::e_instruction>((x))

			enum class e_flag {
				M_IOP = 0x01,
				M_ZERO = 0x02,
				M_CARRY = 0x04,
				x = 0x08,
				y = 0x10,
				z = 0x20,
				r = 0x40,
				f = 0x80
			};


			using program_t = Program;

			Machine();
// 			explicit Machine(Machine::program_t* program);
			virtual ~Machine();
			Machine(const Machine&);
			Machine& operator=(const Machine&);
			void loadProgram(Machine::program_t* program);
			void loadProgramFromFile(const std::string name);
			void run();
			void printProgram();

			Program::register_t fetch();
			Program::register_t* fetch_addr();
			Program::register_t* fetch_addr_from(Program::memory_t m);
			Machine::e_instruction decode(Program::register_t in);
			Program::register_t encode(Machine::e_instruction);
			Program::register_t encode(Machine::e_instruction, Machine::e_argument_type,
				 Machine::e_argument_type);
			Program::memory_t* resolvetype(Machine::e_argument_type in);

			void executeADD(const Program::register_t& instr);
			void executeMOV(const Program::register_t& instr);

	private:
			Machine::program_t* program;
			Program::register_t ip;  // instruction pointer
			Program::register_t sp;  // stack pointer
			Program::register_t bp;  // base pointer
			Program::register_t acc;  // accumulator
			Program::register_t al;  // GPR
			Program::register_t bl;  // GPR
			Program::register_t cl;  // GPR
			Program::register_t dl;  // GPR
			Program::register_t flags;  // flags, carry from ALU, ZERO, INTERRUPT,
													//  OTHERSS< ETC
	};

std::ostream& operator<<(std::ostream& o, const Machine::e_instruction& e);
// std::ostream& operator<<(std::ostream& o, const uint8_t& in);
std::ostream& operator<<(std::ostream& o, const Program::program_memory_t& in);

};  // namespace project5

#endif  // BYTECODE_INCLUDE_MACHINE_HPP_
