#include "cpptypes.hpp"

namespace ucc{

Constant::Constant(uccParser::symbol_type& symbol) : symbol{symbol} {}
Constant::~Constant(){}
Constant::Constant(const Constant& in): symbol{in.symbol} {}
Constant& Constant::operator=(const Constant& in){
	if(in != *this){
		symbol = in.symbol;
	}
	return this;
}

}