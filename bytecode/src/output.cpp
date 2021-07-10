// Copyright 2021 Scott Lorberbaum
#include <iostream>
#include <fstream>
#include <iomanip>
#include "machine.hpp"

namespace project5 {
	
register16_t operator+(const register16_t a, const register16_t b) {
	register16_t temp;
	temp.value = a.value + b.value;
	return temp;
}

register16_t operator-(const register16_t a, const register16_t b) {
	register16_t temp;
	temp.value = a.value - b.value;
	return temp;
}

register16_t operator*(const register16_t a, const register16_t b) {
	register16_t temp;
	temp.value = a.value * b.value;
	return temp;
}

register16_t operator/(const register16_t a, const register16_t b) {
	register16_t c;
	try {
		c.value = a.value / b.value;
	}
	catch(std::exception& e) {
		std::cerr << e.what();
	}
	return c;
}
register16_t move(register16_t a, register16_t b) {
//	register16_t temp;
	a.value =  b.value;
	return a;
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
