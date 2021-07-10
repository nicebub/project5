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
		#define to_register16_t(x) static_cast<VM::register16_t>((x))

		static constexpr size_t MEMSIZE = 65536;
		union reg16 {
			uint16_t value;
			uint8_t single[2];
		};
		using register16_t = reg16;
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
			IP = 0x0,  // Instruction Pointer
			SP,  // Stack Pointer
			BP,  // Base Pointer
			A,  // Accumulator / General Purpose #1 Pointer
			B,  // General Purpose #2 Pointer
			C,  // General Purpose #3 Pointer
			D,  // General Purpose #4 Pointer
			X,  // index register 8 bit
			Y,  // index register 8 bit
			H,  // 8 bit higher
			L,  // 8 bit lower
			HL,  // 16 bit combo of H and L
			AB,  // 16 bit combo of A and B
			CD,  // 16 bit combo of C and D
			XY,  // 16 bit combo of X and Y
		};
		enum class e_argument_type {
			INL8,  // Inline 1byte-- included as part of instruction
			INL16,  // Inline 2 byte -- included as part of instruction
			REG8,  // Register 8bit
			REG16,  // Register 16bit
			MEM,  // Memory -- can be found in memory
			IND,  // Memory -- but indirect addressing
		};
		enum class e_instruction{
			NOP = 0x0,  // NOP
			HALT = 0x1,  // Stop Machine
			MOV,  // Move value or address to 1st argument
			ADD,  // add two values store in 1st argument
			SUB,  // sub 2nd from 1st value store in 1st
			DIV,  // div 2nd from 1st argument store in 1st may be in 2 registers
			MUL,  // mul 1st by 2nd argument
			JMP,  // set next instruction to where Jmp label is located
			JMPZ,  // if zero flag is set, then jump to label
			 //  	ZERO,
			 //  FIXME: will be implemented soon
			 //  call and ret can take a conditional before ie `call cc, lable`
			 // conditions call and ret can take, c, nc, z, nz, m, p, pe, po
			 // flags preserved by either pushing and poping from stack
			 // or internal? prob stack is easier, espcially with multiple calls
			CALL,  // Call a function stored elsewhere, push instr after
			 								// this to top of stack, jumps to label
			RET,  // return from a call, pop top of stack into IP
			PUSH,  // push a value or address onto the stack
			POP,  // pop a value or address off of the stack
			LEA,  // Load Effective address, loads more complex address if needed
			XOR,  // logical exclusive or
			OR,  // logical or
			AND,  // logical and
			SHL,  // shift bits left by argument 1, ending 0s added
			SHR,  // shift bits right by argument 1, leading 0s added for extension
			INC,  // increment accumulator by 1
			DEC,  // decrement accumulator by 1
			CCF,  //  Invert Carry flag and H flag, clears N
			SCF,  //  Set Carry flag and clears N & H
			ADC,  // Add with carry
			CP,  // compare, subtract from a, only set flags
			CPL,  // invert all bits of A, set H and N flags, same as A^FF, A-FF
			 //  FIXME: to be included - the use of conditionals soon
			 //  either jump can be preceded by a conditonal ie  `jp cc, label`
			 //  jp can use c,nc,z,nz,m,p,pe,po
			 //  jr can use c, nc, z, nz
			JP,  // absolute jump to address, can only jump to labels and 16bit address
			JR,  // relative jumps only 128bytes away, with 1byte rel address
			NEG,  // negate value given and set N flag same as  0 - arg
			RES,  // resets a byte to 0 not 2bytes
			RL,  // rotate left includes carry, flags changed: C, H&N reset, P/V, S, Z
//			RLA,  // maybe faster RL A with preserved P/V, S, & Z ??
			RLC,  // rotate left, but 7th bit goes to 0th and carry, same flags as RL
//			RLCA,  // maybe faster RLC A with preserved P/V, S, & Z ??
			RR,  // rotate right includes carry, flags changed: C, H&N reset, P/V, S, Z
//			RRA,  // maybe faster RR A with preserved P/V, S, & Z ??
			RRC,  // rotate right, but 0th bit goes to 7th and Carry, same flags as RR
//			RRCA,  // maybe faster RRC A with preserved P/V, S, & Z ??
			RST,  // reset to a specific address by putting next byte on stack and 
					//			going to  0x00 x - for RST x - is the lowest byte
			SBC,  // add arg2 to carry, subtract that from arg1, store in arg1
					 // set N flag, P/V for overflow or OVER? others maybe
			SLA,  // shift left 7th goes to carry, 0 goes to 0th
			SRA,  // arithmetic shift right, 0 to carry, 7th unchanged
					// , all flags changed, H&N reset
			SRL,  // arithmetic shift right, 0 to carry, 7th changed to 0
					// , all flags changed, S&H&N reset
					
		};
		enum class e_flag {
			M_IOP = 0x01,  // Invalid Operation - no such instruction
			M_ZERO = 0x02,  // last ALU operation was zero? Z
			M_CARRY = 0x04,  // last ALU operation had a carry over bit in MSb C
			M_OVER = 0x08,  // overflow O prob needs to be H
			M_UNDER = 0x10,  // underflow U prob needs to something else
			M_PARITY = 0x20,  // logical parity of bits in accumulator P/V
			M_S = 0x40,   // S
			M_N = 0x80   // N
		};
};
}  // namespace project5
#endif  // BYTECODE_INCLUDE_TYPES_HPP_
