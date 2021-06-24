// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_PROGRAM_HPP_
#define BYTECODE_INCLUDE_PROGRAM_HPP_

#include <unistd.h>
#include <cstddef>
#include <array>
#include <string>
namespace project5 {


class Program {
	public:
		static const size_t max_program_size{64};
		using register_t = u_int8_t;
		using memory_t = u_int8_t;
		using program_memory_t = std::array<memory_t, max_program_size>;
		#define to_register_t(x) static_cast<Program::register_t>((x))
		Program();
		virtual ~Program();
		Program(const Program&);
		Program& operator=(const Program &);
		void addline(std::string line);
		register_t ip;  // instruction pointer start vallue for this program
		register_t sp;  // stack pointer start vallue for this program
		register_t bp;  // base pointer start vallue for this program
		register_t acc;  // accumulator start vallue for this program
		program_memory_t program_mem;
	private:
	program_memory_t::iterator current;
};
}  // namespace project5
#endif  // BYTECODE_INCLUDE_PROGRAM_HPP_
