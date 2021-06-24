// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_ASSEMBLER_HPP_
#define BYTECODE_INCLUDE_ASSEMBLER_HPP_
#include <vector>
#include <string>
#include "program.hpp"
#include "machine.hpp"
namespace project5 {

// class Machine;

	using token_array = std::vector<std::string>;

class Assembler {
	public:
			Assembler();
			explicit Assembler(Machine* mach);
			virtual ~Assembler() = 0;
			Assembler(const Assembler&);
			Assembler& operator=(const Assembler&);

			Program::register_t* convertCmd2ByteCode(const std::string& s);

			Program::register_t* translateHALT();
			Program::register_t* translateMOV(token_array*&);
			void translatePUSH();
			void translatePOP();
			void translateCALL();
			void translateADD();
			void translateSUB();
			void translateDIV();
			void translateMULT();
			void tranlsateJMP();
			void translateJMPZ();
			void translateZERO();

	private:
		Machine* mach;
};

}  // namespace project5



#endif  // BYTECODE_INCLUDE_ASSEMBLER_HPP_
