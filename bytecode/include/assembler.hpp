// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_ASSEMBLER_HPP_
#define BYTECODE_INCLUDE_ASSEMBLER_HPP_
#include <vector>
#include <string>
#include <array>
#include <map>
#include "program.hpp"
#include "machine.hpp"
namespace project5 {

// class Machine;
using Elf32_Word = uint32_t;
using Elf32_Off = uint32_t;
using Elf32_Addr = uint32_t;

typedef struct {
        Elf32_Word      p_type;
        Elf32_Off       p_offset;
        Elf32_Addr      p_vaddr;
        Elf32_Addr      p_paddr;
        Elf32_Word      p_filesz;
        Elf32_Word      p_memsz;
        Elf32_Word      p_flags;
        Elf32_Word      p_align;
} Elf32_Phdr;

	using token_array = std::vector<std::string>;
	using lines_of_code = std::vector<Program::register_t>;
	using full_program = std::vector<lines_of_code>;
class Assembler {
	public:
			static  std::map<const std::string, const Machine::e_register> register_name;
			static  std::map<const std::string, const Machine::e_argument_type> argument_name;
			static  std::map<const std::string, const Machine::e_instruction> instruction_name;

	/*
			static const size_t num_registers = 8;
			static const std::array<std::string, num_registers> register_name;
			static const size_t num_args = 4;
			static const std::array<std::string, num_args> argumentType_name;
			static const size_t num_instructions = 13;
			static const std::array<std::string, num_instructions> instruction_name;
			*/
			Assembler();
			explicit Assembler(Machine* mach);
			virtual ~Assembler();
			Assembler(const Assembler&);
			Assembler& operator=(const Assembler&);

			lines_of_code convertCmd2ByteCode(const std::string& s);

			lines_of_code translateHALT();
			lines_of_code translateMOV(token_array*&);
			void readFile(const std::string fileName);
			void outputToFile(const std::string fileName);
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
	protected:
		void outputToFileHeader(const std::string& header, std::ofstream& file);
		void outputToFileSegmentTable(std::ofstream& file);
		void outputToFileSectionNames(std::ofstream& file);
	private:
		Machine* mach;
		full_program convertedCode;
};

}  // namespace project5



#endif  // BYTECODE_INCLUDE_ASSEMBLER_HPP_
