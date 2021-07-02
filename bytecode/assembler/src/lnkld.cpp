// Copyright 2021 Scott Lorberbaum

#include <fstream>
#include <iostream>
#include "assembler.hpp"
// #include "program.hpp"

namespace project5 {
void Assembler::outputToFileSectionNames(std::ofstream& file) {
	file << std::hex << (register_t)0x00;  // NULL STRING 0
	file << std::hex << (register_t)0x2E;  // string .shrtrtab
	file << std::hex << (register_t)0x73;
	file << std::hex << (register_t)0x68;
	file << std::hex << (register_t)0x73;
	file << std::hex << (register_t)0x74;
	file << std::hex << (register_t)0x72;
	file << std::hex << (register_t)0x74;
	file << std::hex << (register_t)0x61;
	file << std::hex << (register_t)0x62;
	file << std::hex << (register_t)0x00;  // END STRING 1
	file << std::hex << (register_t)0x2E;  // string .text
	file << std::hex << (register_t)0x74;
	file << std::hex << (register_t)0x65;
	file << std::hex << (register_t)0x78;
	file << std::hex << (register_t)0x74;
	file << std::hex << (register_t)0x00;  // END STRING 2
}
using string = std::string;
void Assembler::outputToFileHeader(const string& header, std::ofstream& file) {
	if(header == "ELF") {
		file << std::hex << (register_t)0x7F;  // ELF start header
		file << std::hex << (register_t)0x45;  // E
		file << std::hex << (register_t)0x4C;  // L
		file << std::hex << (register_t)0x46;  // F
		file << std::hex << (register_t)0x01;  // 1 32-bit , 2 64-bit
		file << std::hex << (register_t)0x02;  // 1 little endian 2 big
		file << std::hex << (register_t)0x01;  // 1 for current ELF ver
		file << std::hex << (register_t)0x00;  // ABI 0 is none
		file << std::hex << (register_t)0x00;  // ABI ver, ignored
		file << std::hex << (register_t)0x00;  // PADDING
		file << std::hex << (register_t)0x00;  // PADDING
		file << std::hex << (register_t)0x00;  // PADDING
		file << std::hex << (register_t)0x00;  // PADDING
		file << std::hex << (register_t)0x00;  // PADDING
		file << std::hex << (register_t)0x00;  // PADDING
		file << std::hex << (register_t)0x00;  // PADDING

		file << std::hex << (register_t)0x00;  // OJBECT TYPE 2 BYTES
		file << std::hex << (register_t)0x02;  // 00 none,01,reloc,02 exec
		file << std::hex << (register_t)0x00;  // ISA 2 BYTES
		file << std::hex << (register_t)0x00;  // ISA 00 is none specified
		file << std::hex << (register_t)0x00;  // e_version 4 BYTES
		file << std::hex << (register_t)0x00;
		file << std::hex << (register_t)0x00;
		file << std::hex << (register_t)0x01;  // set to version 1

		file << std::hex << (register_t)0x00;  // e_entry 4 BYTES
		file << std::hex << (register_t)0x00;  // for 32-bit, 8 BYTES for 64
		file << std::hex << (register_t)0x00;  // memory address of entry
		file << std::hex << (register_t)0x74;  // point

		file << std::hex << (register_t)0x00;  // e_phoff 4 BYTES
		file << std::hex << (register_t)0x00;  // for 32-bit, 8 BYTES for 64
		file << std::hex << (register_t)0x00;  // start of program header
		file << std::hex << (register_t)0x34;  // table, generally follows
		// the file header for offset 0x34 for 32-bit and 0x40 for 64-bit

		file << std::hex << (register_t)0x00;  // e_shoff 4 BYTES
		file << std::hex << (register_t)0x00;  // for 32-bit, 8 BYTES for 64
		file << std::hex << (register_t)0x00;  // start of section header
		file << std::hex << (register_t)0x8F;  // table

		file << std::hex << (register_t)0x00;  // e_flags 4 BYTES
		file << std::hex << (register_t)0x00;
		file << std::hex << (register_t)0x00;
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // size of this header, gener-
		file << std::hex << (register_t)0x34;  // ally 52Bytes for 32-bit
																		// or 64Bytes for 64 bit

		file << std::hex << (register_t)0x00;  // e_phentsize size of
		file << std::hex << (register_t)0x20;  // program header table

		file << std::hex << (register_t)0x00;  // e_phnum number of entries
		file << std::hex << (register_t)0x02;  // in program header table

		file << std::hex << (register_t)0x00;  // e_shentsize size of
		file << std::hex << (register_t)0x28;  // section header table

		file << std::hex << (register_t)0x00;  // e_shnum number of entries
		file << std::hex << (register_t)0x03;  // in section header table

		file << std::hex << (register_t)0x00;  // e_shstrndx contains index
		file << std::hex << (register_t)0x02;  // of section header table
														// entry that contains the section names
														/*
		Elf32_Phdr programHeader;
		programHeader.p_type = 0x01000000;
		programHeader.p_offset = 0x00000000;
		programHeader.p_vaddr = 0x00000000;
		programHeader.p_paddr = 0x00000000;
		programHeader.p_filesz = 0x00000000;
		programHeader.p_memsz = 0x00000000;
		programHeader.p_flags = 0x00000000;
		programHeader.p_align = 0x00000000;
		file << std::hex << programHeader.p_type;
		file << std::hex << programHeader.p_offset;
		file << std::hex << programHeader.p_vaddr;
		file << std::hex << programHeader.p_paddr;
		file << std::hex << programHeader.p_filesz;
		file << std::hex << programHeader.p_memsz;
		file << std::hex << programHeader.p_flags;
		file << std::hex << programHeader.p_align;
		*/

		file << std::hex << (register_t)0x00;  // program header
		file << std::hex << (register_t)0x00;  // entry 1
		file << std::hex << (register_t)0x00;
		file << std::hex << (register_t)0x06;  // Loadable segment

		file << std::hex << (register_t)0x00;  // 4 BYTES
		file << std::hex << (register_t)0x00;  // p_offset
		file << std::hex << (register_t)0x00;  // segment location offset
		file << std::hex << (register_t)0x20;

		file << std::hex << (register_t)0x00;  // 4 BYTES
		file << std::hex << (register_t)0x00;  // p_vaddr
		file << std::hex << (register_t)0x00;  // virtual address in mem
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // 4 BYTES
		file << std::hex << (register_t)0x00;  // reserved p_paddr
		file << std::hex << (register_t)0x00;  // physical address
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // p_filesz 4 BYTES
		file << std::hex << (register_t)0x00;  // byte size of segment
		file << std::hex << (register_t)0x00;  // in file can be 0
		file << std::hex << (register_t)0x40;

		file << std::hex << (register_t)0x00;  // p_memsz 4 BYTES
		file << std::hex << (register_t)0x00;  // byte size of segment
		file << std::hex << (register_t)0x00;  // in memory can be 0
		file << std::hex << (register_t)0x40;

		file << std::hex << (register_t)0x00;  // p_flags 4 BYTES
		file << std::hex << (register_t)0x00;  // 32-bit
		file << std::hex << (register_t)0x00;  // segment dependent
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // p_align 4 BYTES 0 and 1
		file << std::hex << (register_t)0x00;  // are no alignment, otherwi-
		file << std::hex << (register_t)0x00;  // se, positive power of 2
		file << std::hex << (register_t)0x00;  // pvaddr=poffset % p_align



		file << std::hex << (register_t)0x00;  // program header
		file << std::hex << (register_t)0x00;  // entry 2
		file << std::hex << (register_t)0x00;
		file << std::hex << (register_t)0x01;  // Loadable segment

		file << std::hex << (register_t)0x00;  // 4 BYTES
		file << std::hex << (register_t)0x00;  // p_offset
		file << std::hex << (register_t)0x00;  // segment location offset
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // 4 BYTES
		file << std::hex << (register_t)0x00;  // p_vaddr
		file << std::hex << (register_t)0x00;  // virtual address in mem
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // 4 BYTES
		file << std::hex << (register_t)0x00;  // reserved p_paddr
		file << std::hex << (register_t)0x00;  // physical address
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // p_filesz 4 BYTES
		file << std::hex << (register_t)0x00;  // byte size of segment
		file << std::hex << (register_t)0x00;  // in file can be 0
		file << std::hex << (register_t)0x8F;

		file << std::hex << (register_t)0x00;  // p_memsz 4 BYTES
		file << std::hex << (register_t)0x00;  // byte size of segment
		file << std::hex << (register_t)0x00;  // in memory can be 0
		file << std::hex << (register_t)0x8F;

		file << std::hex << (register_t)0x00;  // p_flags 4 BYTES
		file << std::hex << (register_t)0x00;  // 32-bit
		file << std::hex << (register_t)0x00;  // segment dependent
		file << std::hex << (register_t)0x00;

		file << std::hex << (register_t)0x00;  // p_align 4 BYTES 0 and 1
		file << std::hex << (register_t)0x00;  // are no alignment, otherwi-
		file << std::hex << (register_t)0x00;  // se, positive power of 2
		file << std::hex << (register_t)0x00;  // pvaddr=poffset % p_align
	}
}
void Assembler::outputToFileSegmentTable(std::ofstream& file) {
																// start of a section header
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

																// start of a section header
	file << std::hex << (register_t)0x00;  // sh_name 4 BYTES
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x0B;

	file << std::hex << (register_t)0x00;  // sh_type 4 BYTES
	file << std::hex << (register_t)0x00;  // 0x1 program data
	file << std::hex << (register_t)0x00;  // 0x8 bss(no data)
	file << std::hex << (register_t)0x01;  // others

	file << std::hex << (register_t)0x00;  // sh_flags 4 BYTES
	file << std::hex << (register_t)0x00;  // 0x1 writeable
	file << std::hex << (register_t)0x00;  // 0x2 in mem during exec
	file << std::hex << (register_t)0x06;  // 0x4 executable 0x20 has
																	// nul terminated strings

	file << std::hex << (register_t)0x00;  // sh_addr 4 BYTES
	file << std::hex << (register_t)0x00;  // virt address of
	file << std::hex << (register_t)0x00;  // section in memory
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // sh_offset 4 BYTES
	file << std::hex << (register_t)0x00;  // offset of section in file
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x74;

	file << std::hex << (register_t)0x00;  // sh_size 4 BYTES
	file << std::hex << (register_t)0x00;  // size of section
	file << std::hex << (register_t)0x00;  // bytes in file
	file << std::hex << (register_t)0x0A;  // may be 0

	file << std::hex << (register_t)0x00;  // sh_link 4 BYTES
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // sh_info 4 BYTES
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // sh_addralign 4 BYTES
	file << std::hex << (register_t)0x00;  // must be power of 2
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // sh_entsize 4 BYTES
	file << std::hex << (register_t)0x00;  // size in bytes of each entry
	file << std::hex << (register_t)0x00;  // if fixed size otherwise 0
	file << std::hex << (register_t)0x00;

																	// next section in table
	file << std::hex << (register_t)0x00;  // name
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x01;

	file << std::hex << (register_t)0x00;  // type
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x03;

	file << std::hex << (register_t)0x00;  // flags
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // address
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // offset
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x7E;

	file << std::hex << (register_t)0x00;  // size
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x11;

	file << std::hex << (register_t)0x00;  // shlink
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // info
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // addralign
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;

	file << std::hex << (register_t)0x00;  // entsize
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
	file << std::hex << (register_t)0x00;
}
}  // namespace project5
