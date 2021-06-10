#include <cstdio>
#include <cstdlib>
#include <string>
#include <ostream>
#include <iostream>

#include "trans.hpp"

using namespace ucc;

CodeGenerator::CodeGenerator() : labelcounter{1},  canGenerate{true},outfile{&std::cout} {
}

CodeGenerator::CodeGenerator(std::ostream& out) : labelcounter{1},  canGenerate{true}, outfile{&out} {}

CodeGenerator::~CodeGenerator() {}

void CodeGenerator::setstream(std::ostream* outfile){
	this->outfile = outfile;
}


inline void CodeGenerator::initializelabel(){
	labelcounter = 1;
}

int CodeGenerator::getlabel(){
	labelcounter++;
	return (labelcounter-1);
}

void CodeGenerator::nullout(std::string& name, int length){
	name.clear();
}

std::string CodeGenerator::genlabelw(std::string name, int labelnum){
	std::string temp{"$"};
	temp += name;
	temp += std::to_string(labelnum);
	return temp;
}
void CodeGenerator::gen_instr(std::string name){
	if(canGenerate){
		*outfile << "\t" << name << "\n";
	}
}

void CodeGenerator::gen_instr_I(std::string name, int arg){
	if(canGenerate){
		*outfile << "\t" << name << "\t" << arg << "\n";
	}
}

void CodeGenerator::gen_instr_S(std::string name, std::string inS){
	if(canGenerate){
		if(name =="jump" || name == "jumpz"){
			*outfile << "\t" << name << "\t" << inS << "\n";
		}
		else{
		 	*outfile << "\t" << name << "\t" << "\"" << inS << "\"\n";
	 	}
	}
}

void CodeGenerator::gen_label(std::string name){
	if(canGenerate){
			*outfile << name << "\n";
	}
}

void CodeGenerator::gen_instr_F(std::string name, float arg){
	if(canGenerate){
			*outfile << "\t" << name << "\t" << arg << "\n";
	}
}

void CodeGenerator::gen_call(std::string funcname, int numargs){
	if(canGenerate){
			*outfile << "\tcall\t" << funcname << ", " << numargs << "\n";
	}
}

void CodeGenerator::gen_instr_tI(std::string name, int arg1, int arg2){
	if(canGenerate){
			*outfile << "\t" << name << "\t" << arg1 << ", " << arg2 << "\n";
	}
}


std::string CodeGenerator::concat(std::string char1, std::string char2){
	return char1 + char2;
}
bool CodeGenerator::canGenerateCode() const noexcept{
	return canGenerate;
}
void CodeGenerator::stop() noexcept{
	canGenerate = false;
}
void CodeGenerator::start() noexcept{
	canGenerate = true;	
}


