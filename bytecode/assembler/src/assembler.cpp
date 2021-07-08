// Copyright 2021 Scott Lorberbaum

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include "assembler.hpp"

// using statements get rid of std:: on std::string, VM:: on
// e_register, e_argument_type, e_instruction

namespace project5 {
	std::map<const string, const e_register> Assembler::register_name = {
		{"A", e_register::A },
		{"B", e_register::B },
		{"C", e_register::C },
		{"D", e_register::D },
		{ "H", e_register::H },
		{ "L", e_register::L },
		{ "X", e_register::X },
		{ "Y", e_register::Y },
		{ "IP", e_register::IP },
		{ "SP", e_register::SP },
		{ "BP", e_register::BP },
		{ "AB", e_register::AB },
		{ "CD", e_register::CD },
		{ "HL", e_register::HL },
		{ "XY", e_register::XY },
	};

	std::map<const string, const e_argument_type> Assembler::argument_name = {
		{ "INL", e_argument_type::INL8 },
		{ "INL16", e_argument_type::INL16 },
		{ "REG", e_argument_type::REG8 },
		{ "REG16", e_argument_type::REG16 },
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
		{ "CALL", e_instruction::CALL },
		{ "PUSH", e_instruction::PUSH },
		{ "POP", e_instruction::POP },
		{ "LEA", e_instruction::LEA },
		{ "XOR", e_instruction::XOR },
		{ "OR", e_instruction::OR },
		{ "AND", e_instruction::AND },
		{ "SHL", e_instruction::SHL },
		{ "SHR", e_instruction::SHR },
		{ "INC", e_instruction::INC },
		{ "DEC", e_instruction::DEC },
	};
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
	return to_register_t(e);
}

register16_t Assembler::encode(e_instruction e,
								e_argument_type a, e_argument_type b) {
	register16_t temp;
	temp.single[1] =  to_register_t(e);
	temp.single[0] = to_register_t(a);
	temp.single[0] <<= 4;
	temp.single[0] += to_register_t(b);
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
		token_array* tokens{split(s, ' ')};
		std::string instruction{tokens->front()};

		if(instruction == "halt") {
			return translateHALT();
		} else if (instruction == "mov") {
			return translateMOV(tokens);
		} else if (instruction == "add") {
			return translateADD();
		} else if (instruction == "sub") {
			return translateSUB();
		} else if (instruction == "mul") {
			return translateMUL();
		} else if (instruction == "div") {
			return translateDIV();
		} else if (instruction == "jmp") {
			return translateJMP();
		} else if (instruction == "jmpz") {
			return translateJMPZ();
		} else if (instruction == "push") {
			return translatePUSH();
		} else if (instruction == "pop") {
			return translatePOP();
		} else if (instruction == "call") {
			return translateCALL();
		} else if (instruction == "ret") {
			return translateRET();
		}
		else {

		}
		return lines_of_code{};
	}

class argument {
	public:
			e_argument_type type;
			std::string value;
			register_t r_value;
			register_t u_value;
	};

project5::argument translateArg(std::string a) {
	project5::argument result;
	switch(a[0]) {
		case '$':
			result.value = a.erase(0, 1);
		  result.type = (result.value.length() == 1) ? e_argument_type::REG8 : e_argument_type::REG16;
			result.r_value = to_register_t(Assembler::register_name[result.value]);
			break;
		case 'm':
			result.type = e_argument_type::MEM;
			result.value = a.erase(0, 1);
			result.r_value = to_register_t(stoul(result.value,nullptr,16) >> 8) ;
			result.u_value = to_register_t(stoul(result.value,nullptr,16) & 0x00FF);
			break;
		default:
			result.type = e_argument_type::INL8;
			result.value = a;
		   result.r_value = stoul(result.value);
//			result.r_value = to_register_t(stoul(result.value,nullptr,16) >> 8) ;
//			result.u_value = to_register_t(stoul(result.value,nullptr,16) & 0x00FF);
			break;
	}
	return result;
}

lines_of_code Assembler::translateMOV(token_array*& tokens) {
	project5::argument arg1{ translateArg( (*tokens)[1] ) };
	project5::argument arg2{ translateArg( (*tokens)[2] ) };

	lines_of_code result{};
		register16_t temp;
		temp = encode(e_instruction::MOV, arg1.type, arg2.type);
	result.push_back(
		temp.single[1]
//		encode(e_instruction::MOV, arg1.type, arg2.type)
	);
	result.push_back(
		temp.single[0]
	);
	result.push_back(arg1.r_value);
	if(arg1.type == e_argument_type::MEM || arg1.type == e_argument_type::IND)
		result.push_back(arg1.u_value);
	result.push_back(arg2.r_value);
	if(arg2.type == e_argument_type::MEM || arg2.type == e_argument_type::IND)
		result.push_back(arg2.u_value);
	return result;
	}


lines_of_code Assembler::translateHALT() {
	lines_of_code result{};
	result.push_back(encode(e_instruction::HALT));
	return result;
}
lines_of_code Assembler::translatePUSH() {
	return lines_of_code{};
}
lines_of_code Assembler::translatePOP() {
	return lines_of_code{};
}
lines_of_code Assembler::translateCALL() {
	return lines_of_code{};
}
lines_of_code Assembler::translateRET() {
	return lines_of_code{};
}

lines_of_code Assembler::translateADD() {
	return lines_of_code{};
}
lines_of_code Assembler::translateSUB() {
	return lines_of_code{};
}
lines_of_code Assembler::translateDIV() {
	return lines_of_code{};
}
lines_of_code Assembler::translateMUL() {
	return lines_of_code{};
}
lines_of_code Assembler::translateJMP() {
	return lines_of_code{};
}
lines_of_code Assembler::translateJMPZ() {
	return lines_of_code{};
}
void Assembler::translateZERO() {
	}

}  // namespace project5
