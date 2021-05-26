#include <iostream>

#include "Debug.hpp"

using namespace ucc;

int Debug::yydebug = 0;

Debug::Debug(){}

Debug::~Debug(){
		
}

int Debug::get_yydebug() {
	return yydebug;
}
void Debug::set_yydebug(const int value){
	yydebug = value;
}
#ifdef DEBUG
void Debug::debugprint(std::string s1, std::string s2){
	if(!s1.empty() && ~s2.empty()){
			std::cerr << "Debug:::" << compiler.filename << ":" << yylineno << " yylineno-> " << s1 << "\"" << s2 << "\"\n";
	}
	else if(s1!=NULL && *s1 && s2==NULL){
			std::cerr << "Debug:::" << compiler.filename << ":" << yylineno << " yylineno-> " << s1 << "\n";
	}
}
void Debug::debugprintd(std::string s1, int s2){
	if(!s1.empty()){
			std::cerr << "Debug:::" << compiler.filename << ":" << yylineno << " yylineno-> " << s1 << "\"" << s2 << "\"\n";
	}
}

#endif
