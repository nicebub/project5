#ifndef _MYDATAH
#define _MYDATAH

#include <string>

#include "type.h"
#include "symtab.hpp"
#include "List.hpp"

namespace ucc {
struct data{
	public:
	union p1{
		std::string 		svalue;
		char 					cvalue;
		int 					ivalue;
		float 				fvalue;
		List*					lstvalue;
		List* 				lstpvalue;
		type 					tvalue;
		addtype 				addopvalue;
		multype 				multopvalue;
		eqtype 				eqopvalue;
		List* 				lstevalue;
		Pair 					pairvalue;
		exprtype* 			exprvalue;
		reltype 				relopvalue;
		funcheadertype* 	funcheadervalue;
		//Entry *funcentvalue;
	} value;
	
	TableEntry* 		entry;
	TableEntry* 		funcent;
	Funcb* 				funcbinding;
	std::string 		name;
	type 					ttype;
	bool 					lval;
	bool 					numeric;
	int 					one;
	int 					two;
	int 					mainlabel;
	int 					params;
};

}

#endif
