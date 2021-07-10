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
			size_t length = file.tellg();
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
			// FIXME: should really be sizeof the header
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
	register_t Machine::run() {
		if(!programLoaded)
			return EXIT_FAILURE;
		while(true) {
			register_t instr = fetch();
			e_instruction e_instr = decode(instr);
			switch(e_instr) {
				case e_instruction::MOV:
					executeInstr(instr, &project5::move);
					break;
				case e_instruction::HALT:
					return CD.single[0];
				case e_instruction::ADD:
					executeInstr(instr, std::plus<register16_t>());
					resetflag(VM::e_flag::N);
					break;
				case e_instruction::SUB:
					executeInstr(instr, std::minus<register16_t>());
					setflag(VM::e_flag::N);
					break;
				case e_instruction::MUL:
					executeInstr(instr, std::multiplies<register16_t>());
					break;
				case e_instruction::DIV:
					executeInstr(instr, std::divides<register16_t>());
					break;
				case e_instruction::CCF:
					executeCCF(instr);
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

	bool Machine::is16bit(e_argument_type arg) noexcept {
		return (arg == e_argument_type::MEM || arg == e_argument_type::IND
				|| arg == e_argument_type::INL16);
	}
	void Machine::executeInstr(const register_t& instr,
			std::function<register16_t(register16_t,register16_t)> func) {
		static constexpr register_t arg1_mask{240};
		static constexpr register_t arg2_mask{15};

		register_t args{fetch()};
		e_argument_type arg1{ to_e_argument_type((args & arg1_mask) >> 4) };
		e_argument_type arg2{ to_e_argument_type((args & arg2_mask)) };
		if(is16bit(arg1) || arg1 == e_argument_type::REG16
		|| is16bit(arg2) || arg2 == e_argument_type::REG16) {
			executeInstr16(arg1, arg2, func);
		} else {
			memory_t* dest{resolvetype(arg1)};
			memory_t* src{resolvetype(arg2)};
			register16_t t;
			register16_t s;
			t.value = s.value = 0;
			t.single[0] = *dest;
			s.single[0] = *src;
			*dest = func(t,s).single[0];
		}

	}
	void Machine::executeInstr16(e_argument_type arg1, e_argument_type arg2,
		std::function<register16_t(register16_t,register16_t)> func) {
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
						if (is16bit(arg2)) {
							v.value <<= 8;
							v.value += extra_value;
							*new_dest = func(*new_dest, v);
							return;
						} else if (arg2 == e_argument_type::REG16) {
							temp = reinterpret_cast<register16_t*>(value);
																	// temp is an internal register in the
																	//  machine
							*new_dest = func(*new_dest, *temp);
							return;
						} else {
							register16_t t;
							t.value = 0;
							t.single[0] = *value;
							*new_dest = func(*new_dest, t);
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
					register16_t t;
					t.value = 0;
					t.single[0] = *dest;
					*dest = (func(t, v)).single[0];
					return;
				}
				register16_t t;
				t.value = 0;
				t.single[0] = *dest;
				register16_t s;
				s.value = 0;
				s.single[0] = *value;
				*dest = (func(t, s)).single[0];
	}
	
	void Machine::setflag(const VM::e_flag& f) noexcept {
		flags &= to_register_t(f);  // set flag f
	}
	void Machine::resetflag(const VM::e_flag& f) noexcept {
		flags &= ~(to_register_t(f)) ;  // reset flag f
	}
	void Machine::toggleflag(const VM::e_flag& f) noexcept {
		flags ^= (to_register_t(f));  // flags carry and H toggled
		
	}
	void Machine::executeCCF(const register_t& e) {
		toggleflag(VM::e_flag::M_CARRY);
		toggleflag(VM::e_flag::M_OVER);
		/*
		flags ^= (to_register_t(VM::e_flag::M_CARRY)  // flags carry and H toggled
			| to_register_t(VM::e_flag::M_OVER));
			*/
			resetflag(VM::e_flag::M_N);
//		flags &= ~(to_register_t(VM::e_flag::M_N)) ;  // reset flag N
	}
}  // namespace project5
