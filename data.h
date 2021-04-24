#ifndef _MYDATAH
#define _MYDATAH
#include "symtab.hpp"
#include "List.hpp"
#include "trans.h"
#include <string>
namespace ucc {
struct data{
	public:
	union p1{
		char 					cvalue;
		std::string 		svalue;
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
	
	int 					one;
	int 					two;
	int 					mainlabel;
	std::string 		name;
	type 					ttype;
	bool 					lval;
	TableEntry* 		funcent;
	bool 					numeric;
	TableEntry* 		entry;
	Funcb* 				funcbinding;
	int 					params;
};

}

#endif
