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
//		acc{0},
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
//		acc{in.acc},
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
//			acc = in.acc;
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
//		acc = inProgram->getacc();
	}

	memory_t* Machine::resolvetype(e_argument_type in) {
		switch(in) {
			case e_argument_type::REG:
			 {
				memory_t* dest{};
				switch(to_e_register(fetch())) {
					case e_register::AL:
						dest = &AB.single[1];
//						dest = ((register16_t)(&AB) & 0xFF00);
						break;
					case e_register::BL:
						dest = &AB.single[0];
//						dest = &bl;
						break;
					case e_register::CL:
						dest = &CD.single[1];
//						dest = &cl;
						break;
					case e_register::DL:
						dest = &CD.single[0];
//						dest = &dl;
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

			case e_argument_type::INL:
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

	/*
	register_t Machine::encode(Machine::e_instruction e) {
	return (to_register_t(e) << 4);
	}

	register_t Machine::encode(Machine::e_instruction e,
									e_argument_type a, e_argument_type b) {
		register_t temp{ to_register_t((static_cast<uint8_t>(e) << 2))};
		temp += to_register_t(a);
		temp <<= 2;
		temp += to_register_t(b);
		return temp;
	}
	*/
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
		return to_e_instruction(in >> 4);
	}

	void Machine::printMachineState() {
// 		if(program) {
//	    std::cout << std::hex;
			std::cout << "ip:	" << ip << "		sp:	" << sp << "		";
			std::cout <<"bp:	" << bp <</* "		acc:	" << acc << */"\n";
			std::cout << "AB:	" << AB << "		CD:	" << CD << "		";
//			std::cout <<"bl:	" << AB.single[0] << "		dl:	" << CD.single[0] << "		";
			std::cout << "flags:	" << flags << "\n";
			std::cout <<"-----------------------\n";
			std::cout << memory << "\n";
// 			std::cout << program.program_mem << "\n";
			std::cout <<"-----------------------\n";
//		  std::cout << std::dec;
//		}
	}


std::ostream& operator<<(std::ostream& o, const e_instruction& e) {
		o << "0x" << static_cast<uint8_t>(e);
		return o;
	}


std::ostream& operator<<(std::ostream& o, const register_t& in) {
	o << std::setfill('0') << std::setw(2) << std::right <<std::hex;
	o << unsigned(in);
	o << std::dec;
	return o;
}

std::ostream& operator<<(std::ostream& o, const register16_t& in) {
	o << std::setfill('0') << std::setw(4) << std::right <<std::hex;
	o << unsigned(in.value);
	o << std::dec;
	return o;
}

std::ostream& operator<<(std::ostream& o, const main_memory_t& in) {
	uint16_t counter{0};
	o << std::hex;
	for(auto& element : in) {
		if (!(counter % 8)) {
			o << std::hex << std::setw(4) << counter << ": " << std::setw(2);
		}
		o << element << ' ';
		counter++;
		if ( !(counter%8) ) {
			o << '\n';
		}
	}
	o << std::dec;
	return o;
}

std::ostream& operator<<(std::ostream& o, const program_memory_t& in) {
	uint16_t counter{0};
	o << std::hex;
	for(auto& element : in) {
		if (!(counter % 8)) {
			o << std::hex << std::setw(4) << counter << ": " << std::setw(2);
		}
		o << element << ' ';
		counter++;
		if ( !(counter%8) ) {
			o << '\n';
		}
	}
	o << std::dec;
	return o;
}
}  // namespace project5
