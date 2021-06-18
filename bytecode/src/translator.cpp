#include <vector>
#include <string>
#include <sstream>
#include "translator.hpp"
#include "machine.hpp"
#include "program.hpp"
namespace project5{

	Translator::Translator(Machine& inMach) : mach{inMach} {}
		Translator::Translator(const Translator& in) : mach{in.mach} {}
			Translator& Translator::operator=(const Translator& in){
				if(this != &in){
					mach = in.mach;
				}
				return *this;
			}

	std::vector<std::string>* split(const std::string& s, char delimiter)
	{
		auto tokens = new std::vector<std::string>{} ;
		std::string token{};
		std::istringstream tokenStream{s};
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens->push_back(token);
		}
		return tokens;
	}

	Program::register_t Translator::convertCmd2ByteCode(std::string& s)
	{
		
		std::string instruction{};
		std::string arg1{};
		std::string arg2{};

		Machine::e_argument_type arg1_type;
		Machine::e_argument_type arg2_type;
			
		std::vector<std::string>* tokens = split(s,' ');
		instruction = tokens->front();
		if(instruction == "halt"){
				Program::register_t i = mach.encode(Machine::e_instruction::HALT);
		}
		else if(instruction == "mov")
		{
			arg1 = (*tokens)[1];
			arg2 = (*tokens)[2];
			if(arg1[0] == '$'){
				arg1_type = Machine::e_argument_type::REG
			}
			else{
				
			}
			if(arg2[0] == '$'){
				arg2_type = Machine::e_argument_type::REG
				
			}
			else{
				
			}
//			Program::register_t i = mach.encode(Machine::e_instruction::MOV,,);
//			Machine::e_instruction::MOV:
		}
		else
		{
			
		}
	}
	void Translator::translateMOV()
	{
		
	}
	void Translator::translateHALT()
	{
		
	}
	void Translator::translatePUSH()
	{
		
	}
	void Translator::translatePOP()
	{
		
	}
	void Translator::translateCALL()
	{
		
	}
	void Translator::translateADD()
	{
		
	}
	void Translator::translateSUB()
	{
		
	}
	void Translator::translateDIV()
	{
		
	}
	void Translator::translateMULT()
	{
		
	}
	void Translator::tranlsateJMP()
	{
		
	}
	void Translator::translateJMPZ()
	{
		
	}
	void Translator::translateZERO()
	{
		
	}

}
