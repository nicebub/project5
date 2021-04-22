#ifndef _MYEXPRH
#define _MYEXPRH
#include "type.h"


namespace ucc{

struct exprtype{
	bool lval;
	type type;
	bool numeric;
};

}
#endif
