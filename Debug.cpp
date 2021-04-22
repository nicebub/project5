#include "Debug.h"

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
