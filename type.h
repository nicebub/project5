#ifndef _MYTYPEH
#define _MYTYPEH

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
	type returntype;
	int num_param;
	type* param_type;
	bool bodydef;
	int label;
	int localcount;
	int actual_num;
};

struct Varb {
	type type;
	int offset;
};

struct Paramb {
	type type;
	int offset;
};

struct Entry{
	std::string name;
	void * binding;
	btype self;
};

struct Symtab {
	Entry ** Stack; //Stack of Binary Search Trees
	int actualStacksize; //used to keep size and top of stack
	int Stacksize; //default of 100
};

}

#endif
