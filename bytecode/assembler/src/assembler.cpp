// Copyright 2021 Scott Lorberbaum

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include "assembler.hpp"
//#include "types.hpp"
//#include "program.hpp"

// using statements get rid of std:: on std::string, VM:: on
// e_register, e_argument_type, e_instruction

namespace project5 {
	std::map<const string, const e_register> Assembler::register_name = {
		{"AL", e_register::AL },
		{"BL", e_register::BL },
		{"CL", e_register::CL },
		{"DL", e_register::DL },
		{ "IP", e_register::IP },
		{ "SP", e_register::SP },
		{ "BP", e_register::BP },
		{ "ACPP", e_register::ACPP }
	};

	std::map<const string, const e_argument_type> Assembler::argument_name = {
		{ "INL", e_argument_type::INL },
		{ "REG", e_argument_type::REG },
		{ "MEM", e_argument_type::MEM },
		{ "IND", e_argument_type::IND }
	};

	std::map<const string, const e_instruction> Assembler::instruction_name = {
		{ "HALT", e_instruction::HALT },
		{ "MOV", e_instruction::MOV },
		{ "ADD", e_instruction::ADD },
		{ "SUB", e_instruction::SUB },
		{ "DIV", e_instruction::DIV },
		{ "MUL", e_instruction::MUL },
		{ "JMP", e_instruction::JMP },
		{ "JMPZ", e_instruction::JMPZ },
//		{ "ZERO", e_instruction::ZERO },
		{ "CALL", e_instruction::CALL },
		{ "PUSH", e_instruction::PUSH },
		{ "POP", e_instruction::POP },
		{ "LEA", e_instruction::LEA }
	};
	/*
using reg_array = std::array<std::string, Assembler::num_registers>;
const reg_array Assembler::register_name = {
		"IP",
		"SP",
		"BP",
		"ACPP",
		"AL",
		"BL",
		"CL",
		"DL"
};
using arg_array = std::array<std::string, Assembler::num_args>;
const arg_array Assembler::argumentType_name = {
		"INL",
		"REG",
		"MEM",
		"IND"
};
using instruction_array = std::array<std::string, Assembler::num_instructions>;
const instruction_array Assembler::instruction_name = {
		"HALT",
		"MOV",
		"ADD",
		"SUB",
		"DIV",
		"MUL",
		"JMP",
		"JMPZ",
		"ZERO",
		"CALL",
		"PUSH",
		"POP",
		"LEA"
};
*/
Assembler::~Assembler() {}
Assembler::Assembler() : convertedCode{} {}

Assembler::Assembler(const Assembler& in) : convertedCode{in.convertedCode} {}

Assembler& Assembler::operator=(const Assembler& in) {
	if(this != &in) {
		convertedCode = in.convertedCode;
	}
	return *this;
}
register_t Assembler::encode(e_instruction e) {
	return (to_register_t(e) << 4);
}

register_t Assembler::encode(e_instruction e,
								e_argument_type a, e_argument_type b) {
	register_t temp{ to_register_t((static_cast<uint8_t>(e) << 2))};
	temp += to_register_t(a);
	temp <<= 2;
	temp += to_register_t(b);
	return temp;
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

void Assembler::readFile(const std::string fileName) {
	std::ifstream file{fileName, std::ifstream::in };
	if(file.is_open()) {
		std::string token{};
		while (std::getline(file, token)) {
		    if (!token.empty()) {
			convertedCode.push_back(convertCmd2ByteCode(token));
		    }
		}
		file.close();
	}
}

void Assembler::outputToFile(const std::string fileName) {
	std::ofstream file{fileName, std::ios::binary};
	if(file.is_open()) {
// 		outputToFileHeader("ELF",file);
		for( auto& element : convertedCode ) {
			for(auto& bte : element) {
				file << std::hex << bte;
			}
		}
// 		outputToFileSectionNames(file);
// 		outputToFileSegmentTable(file);

		file.close();
	}
}

lines_of_code Assembler::convertCmd2ByteCode(const std::string& s) {
		std::string instruction{};
		std::string arg1{};
		std::string arg2{};

		e_argument_type arg1_type;
		e_argument_type arg2_type;
		token_array* tokens = split(s, ' ');
		instruction = tokens->front();

		if(instruction == "halt") {
			return translateHALT();
		} else if (instruction == "mov") {
			return translateMOV(tokens);
		} else {
		}
		return lines_of_code{};
	}

class argument {
	public:
			e_argument_type type;
			std::string value;
			register_t r_value;
	};

	project5::argument translateArg(std::string a) {
		project5::argument result;
		switch(a[0]) {
			case '$':
				result.type = e_argument_type::REG;
				result.value = a.erase(0, 1);
				result.r_value = to_register_t(Assembler::register_name[result.value]);
				break;
			case 'm':
				result.type = e_argument_type::MEM;
				result.value = a.erase(0, 1);
				result.r_value = to_register_t(Assembler::register_name[result.value]);
				break;
			default:
				result.type = e_argument_type::INL;
				result.value = a;
				result.r_value = to_register_t(stoul(a));
				break;
		}
		return result;
	}

lines_of_code Assembler::translateMOV(token_array*& tokens) {
	project5::argument arg1{ translateArg( (*tokens)[1] ) };
	project5::argument arg2{ translateArg( (*tokens)[2] ) };

	lines_of_code result{};
	result.push_back(
		encode(e_instruction::MOV, arg1.type, arg2.type)
	);
	result.push_back(arg1.r_value);
	result.push_back(arg2.r_value);
	return result;
	}

// Program::register_t


lines_of_code Assembler::translateHALT() {
	lines_of_code result{};
	result.push_back(encode(e_instruction::HALT));
	return result;
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
