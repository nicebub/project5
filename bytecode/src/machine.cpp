// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "machine.hpp"

namespace project5 {

	Machine::Machine() :
		programLoaded{false},
		memory{},
		program{},
		ip{1},
		sp{0},
		bp{0},
		al{0},
		bl{0},
		cl{0},
		dl{0},
		flags{0}
		 {	}
	Machine::~Machine() {
	}
	Machine::Machine(const Machine& in) :
		programLoaded{false},
		memory{in.memory},
		program{in.program},
		ip{in.ip},
		sp{in.sp},
		bp{in.bp},
		al{in.al},
		bl{in.bl},
		cl{in.cl},
		dl{in.dl},
		flags{in.flags}
		 {
// 			loadProgramIntoMemory();
		}
	Machine& Machine::operator=(const Machine& in) {
		if(this != &in) {
			programLoaded = false;
			memory = in.memory;
			program = in.program;
			ip = in.ip;
			sp = in.sp;
			bp = in.bp;
			al = in.al;
			bl = in.bl;
			cl = in.cl;
			dl = in.dl;
			flags = in.flags;
			// loadprogramIntoMemory();
		}
		return *this;
	}
	void Machine::loadProgramFromFile(const std::string name) {
		std::ifstream file{name, std::ios::binary | std::ifstream::in };
		if(!file.fail() || file.is_open()) {
			file.seekg(0, file.end);
			int length = file.tellg();
			file.seekg(0, file.beg);
// 			std::cerr << name <<":file length: " << length << "bytes\n";
			for(int i{0}; i < length; i++) {
				char temp;
				file.read(&temp, sizeof(register_t));
				program.push_back(temp);
			}
			loadProgramIntoMemory();
			bp.value = sp.value = length;
		}
		file.close();
	}
	void Machine::loadProgramIntoMemory() {
		size_t i{1};
		for(auto& element : program) {
// 			if i >= MEMSIZE throw an exception program larger than memory??
			memory[i] = element;
			i++;
		}
		programLoaded = true;
	}
	const  bool Machine::isProgramLoaded() noexcept {
		return programLoaded;
	}

	void Machine::loadProgram(const Program* inProgram) {
		program = *inProgram;
		ip = inProgram->getip();
		sp = inProgram->getsp();
		bp = inProgram->getbp();
	}

	memory_t* Machine::resolvetype(e_argument_type in) {
		switch(in) {
			case e_argument_type::REG8:
			 {
				memory_t* dest{};
				switch(to_e_register(fetch())) {
					case e_register::AL:
						dest = &AB.single[1];
						break;
					case e_register::BL:
						dest = &AB.single[0];
						break;
					case e_register::CL:
						dest = &CD.single[1];
						break;
					case e_register::DL:
						dest = &CD.single[0];
						break;
					default:
						dest = nullptr;
						break;
				}
				return dest;
			}
				break;
			case e_argument_type::MEM:
			 {
				return fetch_addr();
			}
				break;

			case e_argument_type::INL8:
			 {
				return fetch_addr();
			}
			break;

			case e_argument_type::IND:
			 {
				memory_t temp { fetch() };
				return fetch_addr_from(temp);
			}
				break;

			default:
				return nullptr;
				break;
		}
		return nullptr;
	}
	void Machine::executeMOV(const register_t& instr) {
		static constexpr uint8_t arg1_mask{12};
		static constexpr uint8_t arg2_mask{3};

		e_argument_type arg1{ to_e_argument_type((instr & arg1_mask) >> 2) };
		e_argument_type arg2{ to_e_argument_type(instr & arg2_mask) };

			memory_t* dest = resolvetype(arg1);
			memory_t extra_dest{};

			if(arg1 == e_argument_type::MEM || arg1 == e_argument_type::IND)
				extra_dest = fetch();

			memory_t* value = resolvetype(arg2);
			memory_t extra_value{};
			if(arg2 == e_argument_type::MEM || arg2 == e_argument_type::IND)
				extra_value = fetch();

			if(arg1 == e_argument_type::MEM || arg1 == e_argument_type::IND
				|| arg2 == e_argument_type::MEM || arg2 == e_argument_type::IND) {
				register16_t m, v;
			    m.value = *dest;
			    v.value = *value;
				if(arg1 == e_argument_type::MEM || arg1 == e_argument_type::IND) {
					m.value <<= 8;
					m.value += extra_dest;
				    dest = &memory[m.value];
				}
				if(arg2 == e_argument_type::MEM || arg2 == e_argument_type::IND) {
					v.value <<= 8;
					v.value += extra_value;
				    *dest = v.value;
				    return;
				}
			}
				*dest = *value;
	}

	void Machine::executeADD(const register_t& instr) {
	}

	register_t Machine::run() {
		if(!programLoaded)
			return -EXIT_FAILURE;
		while(true) {
			register_t instr = fetch();
			e_instruction e_instr = decode(instr);
			switch(e_instr) {
				case e_instruction::HALT:
					return dl;
				case e_instruction::ADD:
					executeADD(instr);
					break;
				case e_instruction::MOV:
					executeMOV(instr);
					break;
				default:
					flags &= to_register_t(VM::e_flag::M_IOP);
					std::cerr << "Illegal Operation < "<< to_register_t(e_instr) << " >\n";
					break;
			}
		}
	}

	register_t Machine::fetch() {
		return memory[ip.value++];
	}
	register_t* Machine::fetch_addr() {
	return &memory[ip.value++];
	}

	register_t* Machine::fetch_addr_from(memory_t m) {
		return &memory[m];
	}

	e_instruction Machine::decode(register_t in) {
		return to_e_instruction(in);
	}

	void Machine::printMachineState() {
			std::cout << "ip:	" << ip << "		sp:	" << sp << "		";
			std::cout <<"bp:	" << bp << "\n";
			std::cout << "AB:	" << AB << "		CD:	" << CD << "		";
			std::cout << "HL:	" << HL << "		XY:	" << XY << "		";
			std::cout << "flags:	" << flags << "\n";
			std::cout <<"-----------------------\n";
			std::cout << memory << "\n";
			std::cout <<"-----------------------\n";
	}
}  // namespace project5
