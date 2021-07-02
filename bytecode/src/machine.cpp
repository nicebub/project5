// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include <fstream>
#include <iomanip>
#include "machine.hpp"

namespace project5 {

	Machine::Machine() :
		programLoaded{false},
		memory{},
		program{},
		ip{1},
		sp{0},
		bp{0},
		acc{0},
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
		acc{in.acc},
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
			acc = in.acc;
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
			std::cerr << name <<":file length: " << length << "bytes\n";
			/*
			if(program == nullptr) {
				program = Program::newProgram();
				}*/
			for(int i{0}; i < length; i++) {
				char temp;
				file.read(&temp, sizeof(Program::register_t));
				program.push_back(temp);
			}
			loadProgramIntoMemory();
			bp = sp = length;
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
		acc = inProgram->getacc();
	}

	Program::memory_t* Machine::resolvetype(Machine::e_argument_type in) {
		switch(in) {
			case e_argument_type::REG:
			 {
				Program::memory_t* dest{};
				switch(to_e_register(fetch())) {
					case Machine::e_register::AL:
						dest = &al;
						break;
					case Machine::e_register::BL:
						dest = &bl;
						break;
					case Machine::e_register::CL:
						dest = &cl;
						break;
					case Machine::e_register::DL:
						dest = &dl;
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
				Program::memory_t temp { fetch() };
				return fetch_addr_from(temp);
			}
				break;

			default:
				return nullptr;
				break;
		}
		return nullptr;
	}
	void Machine::executeMOV(const Program::register_t& instr) {
		static constexpr uint8_t arg1_mask{12};
		static constexpr uint8_t arg2_mask{3};

		Machine::e_argument_type arg1{ to_e_argument_type((instr & arg1_mask) >> 2) };
		Machine::e_argument_type arg2{ to_e_argument_type(instr & arg2_mask) };

		Program::memory_t* dest = resolvetype(arg1);
		Program::memory_t* value = resolvetype(arg2);

		*dest = *value;
	}

	void Machine::executeADD(const Program::register_t& instr) {
	}
	void Machine::run() {
		while(true) {
			Program::register_t instr = fetch();
			Machine::e_instruction e_instr = decode(instr);
			switch(e_instr) {
				case Machine::e_instruction::HALT:
				std::cout << "Printing Program after run\n";
					printMachineState();
// 					dl = fetch();
					exit(dl);
				case Machine::e_instruction::ADD:
					executeADD(instr);
					break;
				case Machine::e_instruction::MOV:
					executeMOV(instr);
					break;
				default:
					flags &= to_register_t(VM::e_flag::M_IOP);
					std::cerr << "Illegal Operation < "<< to_register_t(e_instr) << " >\n";
					break;
			}
		}
	}

	Program::register_t Machine::fetch() {
		return memory[ip++];
	}
	Program::register_t* Machine::fetch_addr() {
	return &memory[ip++];
	}

	Program::register_t* Machine::fetch_addr_from(Program::memory_t m) {
		return &memory[m];
	}

	Program::register_t Machine::encode(Machine::e_instruction e) {
	return (to_register_t(e) << 4);
	}

	Program::register_t Machine::encode(Machine::e_instruction e,
									Machine::e_argument_type a, Machine::e_argument_type b) {
		Program::register_t temp{ to_register_t((static_cast<uint8_t>(e) << 2))};
		temp += to_register_t(a);
		temp <<= 2;
		temp += to_register_t(b);
		return temp;
	}

	Machine::e_instruction Machine::decode(Program::register_t in) {
		return to_e_instruction(in >> 4);
	}

	void Machine::printMachineState() {
// 		if(program) {
			std::cout << "ip:	" << ip << "		sp:	" << sp << "		";
			std::cout <<"bp:	" << bp << "		acc:	" << acc << "\n";
			std::cout << "al:	" << al << "		cl:	" << cl << "		";
			std::cout <<"bl:	" << bl << "		dl:	" << dl << "		";
			std::cout << "flags:	" << flags << "\n";
			std::cout <<"-----------------------\n";
			std::cout << memory << "\n";
// 			std::cout << program.program_mem << "\n";
			std::cout <<"-----------------------\n";
//		}
	}


std::ostream& operator<<(std::ostream& o, const Machine::e_instruction& e) {
		o << "0x" << static_cast<uint8_t>(e);
		return o;
	}


std::ostream& operator<<(std::ostream& o, const uint8_t& in) {
			o << std::setfill('0') << std::setw(2) << std::right <<std::hex;
			o << unsigned(in);
			o << std::dec;
			return o;
		}

std::ostream& operator<<(std::ostream& o, const Machine::main_memory_t& in) {
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

std::ostream& operator<<(std::ostream& o, const Program::program_memory_t& in) {
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
