// Copyright 2021 Scott Lorberbaum

#include <string>
#include <vector>
#include <sstream>
#include "types.hpp"
#include "program.hpp"
// #include "machine.hpp"
namespace project5{

	using register_t = u_int8_t;
	using memory_t = u_int8_t;
	using program_memory_t = std::vector<memory_t>;

	Program::Program() :
		ip{1},
		sp{0},
		bp{0},
		acc{0},
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
		acc{in.acc},
		program_mem{in.program_mem},
		current{in.current}
		 {	}
	Program& Program::operator=(const Program & in) {
		if (this != &in) {
				ip = in.ip;
				sp = in.sp;
				bp = in.bp;
				acc = in.acc;
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
Program::register_t Program::getip() const noexcept {
	return ip;
}
Program::register_t Program::getsp() const noexcept {
	return sp;
}
Program::register_t Program::getbp() const noexcept {
	return bp;
}
Program::register_t Program::getacc() const noexcept {
	return acc;
}

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
