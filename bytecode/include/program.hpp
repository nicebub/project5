// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_PROGRAM_HPP_
#define BYTECODE_INCLUDE_PROGRAM_HPP_

#include <unistd.h>
#include <cstddef>
#include <vector>
#include <string>
#include "types.hpp"
namespace project5 {

class Program {
	public:
		using register_t = VM::register_t;
		using memory_t = VM::memory_t;
		using program_memory_t = VM::program_memory_t;

		Program();
		virtual ~Program();
		Program(const Program&);
		Program& operator=(const Program &);
		Program* newProgram(const size_t len);
		void addline(std::string line);
		void push_back(memory_t);

		register_t getip() const noexcept;
		register_t getsp() const noexcept;
		register_t getbp() const noexcept;
		register_t getacc() const noexcept;

		program_memory_t::iterator begin();
		program_memory_t::iterator end();

	private:
		program_memory_t program_mem;
		program_memory_t::iterator current;
		register_t ip;  // instruction pointer start vallue for this program
		register_t sp;  // stack pointer start vallue for this program
		register_t bp;  // base pointer start vallue for this program
		register_t acc;  // accumulator start vallue for this program
};

}  // namespace project5
#endif  // BYTECODE_INCLUDE_PROGRAM_HPP_
