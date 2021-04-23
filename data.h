#ifndef _MYDATAH
#define _MYDATAH
#include "symtab.h"
#include "List.h"
#include "trans.h"
#include <string>
namespace ucc {
struct data{
	union {
		char cvalue;
		std::string svalue;
		int ivalue;
		float fvalue;
		List *lstvalue;
		ListP *lstpvalue;
		type tvalue;
		addtype addopvalue;
		multype multopvalue;
		eqtype eqopvalue;
		ListE *lstevalue;
		Pair pairvalue;
		exprtype *exprvalue;
		reltype relopvalue;
		funcheadertype *funcheadervalue;
		//Entry *funcentvalue;
	} value;
	int one;
	int two;
	int mainlabel;
	std::string name;
	type ttype;
	bool lval;
	Entry *funcent;
	bool numeric;
	Entry* entry;
	Funcb* funcbinding;
	int params;
};

}

#endif
