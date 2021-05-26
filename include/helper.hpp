#ifndef _HELPER_HPP
#define _HELPER_HPP

#include "type.hpp"
#include "symtab.hpp"

namespace ucc{

//	bool check_function_declaration(funcheadertype** inFunc,SymbolTable& table) ;
	void setflags(int flags);
	int getflags();
	
}

#endif