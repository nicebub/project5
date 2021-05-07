#ifndef _CPPSTYPES_HPP
#define _CPPSTYPES_HPP

#include "ucc.tab.hpp"

namespace ucc{
	
class Constant{
	public:
		Constant(uccParser::symbol_type& symbol);
		virtual ~Constant();
		Constant(const Constant& in);
		virtual Constant& operator=(const Constant& in);
	private:
		uccParser::symbol_type& symbol;
};


/*
class IntConstant : public Constant{
	IntConstant();
	virtual ~IntConstant();
	IntConstant
};
class StrtConstant : public Constant{
};
class FloattConstant : public Constant{
};
*/

}

#endif