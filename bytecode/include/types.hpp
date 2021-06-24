// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_TYPES_HPP_
#define BYTECODE_INCLUDE_TYPES_HPP_

namespace project5 {

#define as_int(x) static_cast<Program::register_t>((x))

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
				NONE,
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
				ZERO
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

		}  // namespace project5
#endif  // BYTECODE_INCLUDE_TYPES_HPP_
