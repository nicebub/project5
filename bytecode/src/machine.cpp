// Copyright 2021 Scott Lorberbaum

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
//  #include <assert.h>
#include "machine.hpp"

namespace project5 {

	Machine::Machine() :
		programLoaded{false},
		memory{},
		program{},
		ip{1},
		sp{0},
		bp{0},
		AB{0},
		CD{0},
		XY{0},
		HL{0},
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
		AB{in.AB},
		CD{in.CD},
		XY{in.XY},
		HL{in.HL},
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
			AB = in.AB;
			CD = in.CD;
			XY = in.XY;
			HL = in.HL;
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
				file.read(&temp, sizeof temp);
				program.push_back(temp);
			}
			loadProgramIntoMemory();
			bp.value = sp.value = length + 1;  // stack starts after code for now
			// also add 1 because we leave byte 0 empty so sizeof program + 1
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

register16_t* Machine::resolvetype16(e_argument_type in, e_register reg) {
	switch(in) {
		case e_argument_type::REG16:
		 {
				switch(reg) {
					case e_register::AB:
					temp = &AB;
					break;
					case e_register::CD:
					temp = &CD;
					break;
					case e_register::HL:
					temp = &HL;
					break;
					case e_register::XY:
					temp = &XY;
					break;
					default:
					temp = nullptr;
					break;
				}
				return temp;
			}
			break;
			default:
			return nullptr;
			break;
		}
	return nullptr;
}
	memory_t* Machine::resolvetype(e_argument_type in) {
		switch(in) {
			case e_argument_type::REG16:
			case e_argument_type::REG8:
			 {
				switch(to_e_register(fetch())) {
					case e_register::A:
						return &AB.single[1];
						break;
					case e_register::AB:
					case e_register::B:
						return &AB.single[0];
						break;
					case e_register::C:
						return &CD.single[1];
						break;
					case e_register::CD:
					case e_register::D:
						return &CD.single[0];
						break;
					case e_register::H:
						return &HL.single[1];
						break;
					case e_register::HL:
					case e_register::L:
						return &HL.single[0];
						break;
					case e_register::X:
						return &XY.single[1];
						break;
					case e_register::XY:
					case e_register::Y:
						return &XY.single[0];
						break;
					default:
						return nullptr;
						break;
				}
				return nullptr;
			}
				break;
			case e_argument_type::MEM:
			 {
				return fetch_addr();
			}
				break;

			case e_argument_type::INL16:
			case e_argument_type::INL8:
			 {
				return fetch_addr();
			}
			break;

			case e_argument_type::IND:
			 {
				return fetch_addr_from(fetch());
			}
				break;

			default:
				return nullptr;
				break;
		}
		return nullptr;
	}

	bool Machine::is16bit(e_argument_type arg) {
		return (arg == e_argument_type::MEM || arg == e_argument_type::IND
				|| arg == e_argument_type::INL16);
	}

	void Machine::executeMOV16(e_argument_type arg1, e_argument_type arg2) {
			memory_t extra_dest{}, extra_value{};

			memory_t* dest{resolvetype(arg1)};
			if(is16bit(arg1))
				extra_dest = fetch();

			memory_t* value{resolvetype(arg2)};
			if(is16bit(arg2))
				extra_value = fetch();

			register16_t m, v;
			m.value = *dest;
			v.value = *value;
			switch(arg1) {
				case e_argument_type::REG16:
				 {
					register16_t* new_dest;
					new_dest = reinterpret_cast<register16_t*>(dest);
// 				register16_t* new_dest = resolvetype16(arg1,to_e_register(m.value));
					if (is16bit(arg2)) {
						v.value <<= 8;
						v.value += extra_value;
						new_dest->value = v.value;
						return;
					} else if (arg2 == e_argument_type::REG16) {
						temp = reinterpret_cast<register16_t*>(value);
																// temp is an internal register in the
																//   machine
						new_dest->value = temp->value;
						return;
					} else {
						new_dest->value = *value;
						return;
					}
				}
					break;
				case e_argument_type::MEM:
					m.value <<= 8;
					m.value += extra_dest;
					dest = &memory[m.value];
				default:
					break;
			}
			if (is16bit(arg2)) {
				v.value <<= 8;
				v.value += extra_value;
				*dest = v.value;
				return;
			 }
			 *dest = *value;
	}

	void Machine::executeInstr(const register_t& instr,
			void(Machine::*func)(e_argument_type, e_argument_type)) {
		static constexpr register_t arg1_mask{240};
		static constexpr register_t arg2_mask{15};

		register_t args{fetch()};
		e_argument_type arg1{ to_e_argument_type((args & arg1_mask) >> 4) };
		e_argument_type arg2{ to_e_argument_type((args & arg2_mask)) };
		(this->*func)(arg1, arg2);
	}

	void Machine::executeMOV(e_argument_type arg1, e_argument_type arg2) {
		if(is16bit(arg1) || arg1 == e_argument_type::REG16
		|| is16bit(arg2) || arg2 == e_argument_type::REG16) {
			executeMOV16(arg1, arg2);
		} else {
			memory_t* dest{resolvetype(arg1)};
			*dest = *resolvetype(arg2);
		}
	}
	void Machine::executeSUB16(e_argument_type arg1, e_argument_type arg2) {
	}
	void Machine::executeMUL16(e_argument_type arg1, e_argument_type arg2) {
	}
	void Machine::executeDIV16(e_argument_type arg1, e_argument_type arg2) {
	}

	void Machine::executeADD16(e_argument_type arg1, e_argument_type arg2) {
			memory_t extra_dest{}, extra_value{};

			memory_t* dest{resolvetype(arg1)};
			if(is16bit(arg1))
				extra_dest = fetch();

			memory_t* value{resolvetype(arg2)};
			if(is16bit(arg2))
				extra_value = fetch();

			register16_t m, v;
			m.value = *dest;
			v.value = *value;
			switch(arg1) {
				case e_argument_type::REG16:
				 {
					register16_t* new_dest;
					new_dest = reinterpret_cast<register16_t*>(dest);
// 				register16_t* new_dest = resolvetype16(arg1,to_e_register(m.value));
					if (is16bit(arg2)) {
						v.value <<= 8;
						v.value += extra_value;
						new_dest->value += v.value;
						return;
					} else if (arg2 == e_argument_type::REG16) {
						temp = reinterpret_cast<register16_t*>(value);
																// temp is an internal register in the
																//  machine
						new_dest->value += temp->value;
						return;
					} else {
						new_dest->value += *value;
						return;
					}
				}
					break;
				case e_argument_type::MEM:
					m.value <<= 8;
					m.value += extra_dest;
					dest = &memory[m.value];
				default:
					break;
			}
			if (is16bit(arg2)) {
				v.value <<= 8;
				v.value += extra_value;
				*dest = v.value;
				return;
			 }
			 *dest += *value;
	}

	void Machine::executeADD(e_argument_type arg1, e_argument_type arg2) {
		if(is16bit(arg1) || arg1 == e_argument_type::REG16
		|| is16bit(arg2) || arg2 == e_argument_type::REG16) {
			executeADD16(arg1, arg2);
		} else {
			memory_t* dest{resolvetype(arg1)};
			*dest += *resolvetype(arg2);
		}
	}
	void Machine::executeSUB(e_argument_type arg1, e_argument_type arg2) {
		if(is16bit(arg1) || arg1 == e_argument_type::REG16
		|| is16bit(arg2) || arg2 == e_argument_type::REG16) {
			executeSUB16(arg1, arg2);
		} else {
			memory_t* dest{resolvetype(arg1)};
			*dest -= *resolvetype(arg2);
		}
	}
	void Machine::executeMUL(e_argument_type arg1, e_argument_type arg2) {
		if(is16bit(arg1) || arg1 == e_argument_type::REG16
		|| is16bit(arg2) || arg2 == e_argument_type::REG16) {
			executeMUL16(arg1, arg2);
		} else {
			memory_t* dest{resolvetype(arg1)};
			*dest *= *resolvetype(arg2);
		}
	}
	void Machine::executeDIV(e_argument_type arg1, e_argument_type arg2) {
		if(is16bit(arg1) || arg1 == e_argument_type::REG16
		|| is16bit(arg2) || arg2 == e_argument_type::REG16) {
			executeDIV16(arg1, arg2);
		} else {
			memory_t* dest{resolvetype(arg1)};
			try {
			*dest /= *resolvetype(arg2);
			}
			catch(std::exception& e) {
				std::cerr << e.what();
			}
		}
	}

	register_t Machine::run() {
		if(!programLoaded)
			return EXIT_FAILURE;
		while(true) {
			register_t instr = fetch();
			e_instruction e_instr = decode(instr);
			switch(e_instr) {
				case e_instruction::MOV:
					executeInstr(instr, &Machine::executeMOV);
					break;
				case e_instruction::HALT:
					return CD.single[0];
				case e_instruction::ADD:
					executeInstr(instr, &Machine::executeADD);
					break;
				case e_instruction::SUB:
					executeInstr(instr, &Machine::executeSUB);
					break;
				case e_instruction::MUL:
					executeInstr(instr, &Machine::executeMUL);
					break;
				case e_instruction::DIV:
					executeInstr(instr, &Machine::executeDIV);
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
