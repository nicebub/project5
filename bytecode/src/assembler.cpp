// Copyright 2021 Scott Lorberbaum

#include <vector>
#include <string>
#include <sstream>
#include "assembler.hpp"
#include "machine.hpp"
#include "program.hpp"
namespace project5 {

Assembler::Assembler() : mach{nullptr} {}
Assembler::Assembler(Machine* inMach) : mach{inMach} {}

Assembler::Assembler(const Assembler& in) : mach{in.mach} {}

Assembler& Assembler::operator=(const Assembler& in) {
	if(this != &in) {
		mach = in.mach;
	}
	return *this;
}


token_array* split(const std::string& s, char delimiter) {
		auto tokens = new token_array{};
		std::string token{};
		std::istringstream tokenStream{s};
		while (std::getline(tokenStream, token, delimiter)) {
			tokens->push_back(token);
		}
		return tokens;
	}

Program::register_t* Assembler::convertCmd2ByteCode(const std::string& s) {
		std::string instruction{};
		std::string arg1{};
		std::string arg2{};

		Machine::e_argument_type arg1_type;
		Machine::e_argument_type arg2_type;
		token_array* tokens = split(s, ' ');
		instruction = tokens->front();
		if(instruction == "halt") {
			return translateHALT();
		} else if (instruction == "mov") {
			return translateMOV(tokens);
		} else {
		}
	}

class argument {
	public:
			Machine::e_argument_type type;
			std::string value;
	};

	project5::argument translateArg(std::string a) {
		project5::argument result;
		switch(a[0]) {
			case '$':
				result.type = Machine::e_argument_type::REG;
				result.value = a.erase(0);
				break;
			case 'm':
				result.type = Machine::e_argument_type::MEM;
				result.value = a.erase(0);
				break;
			default:
				result.type = Machine::e_argument_type::INL;
				result.value = a;
				break;
		}
		return result;
	}

Program::register_t* Assembler::translateMOV(token_array*& tokens) {
			project5::argument arg1{ translateArg( (*tokens)[1] ) };
			project5::argument arg2{ translateArg( (*tokens)[2] ) };

			Program::register_t* result{ new Program::register_t[3] {} };
			result[0] = mach->encode(Machine::e_instruction::MOV, arg1.type, arg2.type);
			result[1] = arg1.value;
			result[2] = arg2.value;
			return result;
	}

// Program::register_t


Program::register_t* Assembler::translateHALT() {
		return new Program::register_t[1]{mach->encode(Machine::e_instruction::HALT)};
	}
void Assembler::translatePUSH() {
	}
void Assembler::translatePOP() {
	}
void Assembler::translateCALL() {
	}
void Assembler::translateADD() {
	}
void Assembler::translateSUB() {
	}
void Assembler::translateDIV() {
	}
void Assembler::translateMULT() {
	}
void Assembler::tranlsateJMP() {
	}
void Assembler::translateJMPZ() {
	}
void Assembler::translateZERO() {
	}

}  // namespace project5
