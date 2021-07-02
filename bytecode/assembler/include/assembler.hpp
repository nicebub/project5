// Copyright 2021 Scott Lorberbaum

#ifndef BYTECODE_INCLUDE_ASSEMBLER_HPP_
#define BYTECODE_INCLUDE_ASSEMBLER_HPP_
#include <vector>
#include <string>
#include <array>
#include <map>
#include "types.hpp"
#include "program.hpp"
namespace project5 {

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

	using string = std::string;

	using token_array = std::vector<string>;
	using lines_of_code = std::vector<VM::memory_t>;
	using full_program = std::vector<lines_of_code>;

	using e_register = VM::e_register;
	using e_argument_type = VM::e_argument_type;
	using e_instruction = VM::e_instruction;

	using register_map = std::map<const string, const e_register>;
	using argument_map = std::map<const string, const e_argument_type>;
	using instruction_map = std::map<const string, const e_instruction>;

class Assembler {
	public:
		static register_map register_name;
		static argument_map argument_name;
		static instruction_map instruction_name;

		Assembler();
		virtual ~Assembler();
		Assembler(const Assembler&);
		Assembler& operator=(const Assembler&);

		register_t encode(e_instruction e);
		register_t encode(e_instruction e, e_argument_type a, e_argument_type b);

		void readFile(const string fileName);
		void outputToFile(const string fileName);

		lines_of_code convertCmd2ByteCode(const string& s);
		lines_of_code translateHALT();
		lines_of_code translateMOV(token_array*&);

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
		void outputToFileHeader(const string& header, std::ofstream& file);
		void outputToFileSegmentTable(std::ofstream& file);
		void outputToFileSectionNames(std::ofstream& file);

	private:
		full_program convertedCode;
};

}  // namespace project5



#endif  // BYTECODE_INCLUDE_ASSEMBLER_HPP_
