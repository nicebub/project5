#ifndef _MYTYPE_H
#define _MYTYPE_H

#include <vector>

namespace ucc{

enum class addtype{
	PLS,
	MIN
};

enum class multype{
	DIV,
	MULT
};

enum class eqtype{
	NEQ,
	EQEQ
};

enum class reltype{
	LES,
	LEQ,
	GRE,
	GEQ
};

enum class btype{
	FUNC,
	VAR,
	PARAM
};

enum class type{
	INT,
	FLOAT,
	VOID,
	CHAR,
	STR,
	REFINT,
	REFFLOAT,
	REFSTR
};

enum class mbool{
	TRUE,
	FALSE
};

struct Funcb {
	std::vector<type> param_type;
//	type* param_type;
	type 	returntype;
	bool 	bodydef;
	int 	num_param;
	int 	label;
	int 	localcount;
	int 	actual_num;
};

struct Varb {
	ucc::type 	type;
	int 	offset;
};

struct Paramb {
	ucc::type 	type;
	int 	offset;
};

struct Pair{
	int one;
	int two;
};
struct exprtype{
	bool lval;
	ucc::type type;
	bool numeric;
};

}

#endif
