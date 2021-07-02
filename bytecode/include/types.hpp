// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_TYPES_HPP_
#define BYTECODE_INCLUDE_TYPES_HPP_

#include <vector>
#include <array>

namespace project5 {
class VM {
	public:
		#define to_e_register(x) static_cast<VM::e_register>((x))
		#define to_e_argument_type(x) static_cast<VM::e_argument_type>((x))
		#define to_e_instruction(x) static_cast<VM::e_instruction>((x))
		#define to_register_t(x) static_cast<VM::register_t>((x))

		static constexpr size_t MEMSIZE = 65536;

		using register_t = u_int8_t;
		using memory_t = u_int8_t;
		using program_memory_t = std::vector<memory_t>;

		enum class e_register;
		enum class e_argument_type;
		enum class e_instruction;

		using e_instruction = VM::e_instruction;
		using e_register = VM::e_register;
		using e_argument_type = VM::e_argument_type;

		using main_memory_t = std::array<memory_t, VM::MEMSIZE>;

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
			// 	ZERO,
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
};
}  // namespace project5
#endif  // BYTECODE_INCLUDE_TYPES_HPP_
