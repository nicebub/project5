#include <string>
#include "lex.hpp"

using namespace ucc;

Lex::Lex() : string_buf{} {}
	
int Lex::error(std::string,std::string){}
int Lex::warning(std::string,std::string){}
	