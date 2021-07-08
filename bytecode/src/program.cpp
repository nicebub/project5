// Copyright 2021 Scott Lorberbaum

#include <string>
#include <vector>
#include <sstream>
#include "program.hpp"
namespace project5{

using program_memory_t = VM::program_memory_t;
	Program::Program() :
		ip{1},
		sp{0},
		bp{0},
		AB{0},
		CD{0},
		XY{0},
		HL{0},
		program_mem{}
		 {
			current = program_mem.begin();
			current++;
		}
	Program::~Program() {}
	Program::Program(const Program& in) :
		ip{in.ip},
		sp{in.sp},
		bp{in.bp},
		AB{in.AB},
		CD{in.CD},
		XY{in.XY},
		HL{in.HL},
		program_mem{in.program_mem},
		current{in.current}
		 {	}
	Program& Program::operator=(const Program & in) {
		if (this != &in) {
				ip = in.ip;
				sp = in.sp;
				bp = in.bp;
				AB = in.AB;
				CD = in.CD;
				XY = in.XY;
				HL = in.HL;
				program_mem = in.program_mem;
				current = in.current;
		}
		return *this;
	}

program_memory_t::iterator Program::begin() {
	return program_mem.begin();
}
program_memory_t::iterator Program::end() {
	return program_mem.end();
}

void Program::push_back(memory_t in) {
	program_mem.push_back(in);
}


Program* Program::newProgram(const size_t len) {
	return new Program{};
}
Program::register16_t Program::getip() const noexcept {
	return ip;
}
Program::register16_t Program::getsp() const noexcept {
	return sp;
}
Program::register16_t Program::getbp() const noexcept {
	return bp;
}
/*
Program::register_t Program::getacc() const noexcept {
	return acc;
}
*/

		/*
		std::vector<std::string>* split(const std::string& s, char delimiter)
		{
		   auto tokens{new std::vector<std::string>{}} ;
		   std::string token{};
		   std::istringstream tokenStream{s};
		   while (std::getline(tokenStream, token, delimiter))
		   {
		      tokens->push_back(token);
		   }
		   return tokens;
		}
		
		void Program::addline(std::string line)
		{
			std::string instruction{};
			std::string arg1{};
			std::string arg2{};
			std::vector<std::string>* tokens = split(line,' ');
			instruction = tokens->front();
			switch(instruction){
				case
				}
		}
		*/

	};  // namespace project5
