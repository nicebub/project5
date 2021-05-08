#include "cpptypes.hpp"
#include "type.hpp"

namespace ucc{

	Constant::Constant(bool lval , ucc::type ttype, bool ifnum) : lval{lval}, ttype{ttype}, numeric{ifnum} {}

	Constant::~Constant(){}

	bool Constant::getlval() const {
		return lval;
	}
	void Constant::setlval(const bool in){
		lval = in;
	}
	ucc::type  Constant::gettype() const {
		return ttype;
	}
	void Constant::settype(const ucc::type in){
		ttype = in;
	}
	bool Constant::getnumeric() const{
		return numeric;
	}
	void Constant::setnumeric(const bool in){
		numeric = in;
	}

	IntConstant::IntConstant() : Constant{false,ucc::type::INT, true}, value{0} {}

	IntConstant::IntConstant(const int invalue) : Constant{false,ucc::type::INT, true}, value{invalue} {}
		
	IntConstant::IntConstant(const IntConstant& in) : Constant{in.getlval(),ucc::type::INT, true}, value{in.value} {}
		
	IntConstant::~IntConstant(){}
		
	IntConstant& IntConstant::operator=(const IntConstant& in){
		if(&in != this){
			value = in.value;
			setlval(in.getlval());
			setnumeric(true);
			settype(ucc::type::INT);
		}
		return *this;
	}
	int IntConstant::getvalue() const {
		return value;
	}

	void IntConstant::setvalue(const int in){
		value = in;
	}	

	StrConstant::StrConstant() : Constant{false,ucc::type::STR, false} {}
		
	StrConstant::StrConstant(const std::string invalue) : Constant{false,ucc::type::STR, false} , value{invalue} {}
		
	StrConstant::StrConstant(const StrConstant& in) : Constant{in.getlval(),ucc::type::STR, false} , value{in.value} {}
		
	StrConstant::~StrConstant() {}
		
	StrConstant& StrConstant::operator=(const StrConstant& in) {
		if(&in != this){
			value = in.value;
			setlval(in.getlval());
			setnumeric(false);
			settype(ucc::type::STR);
		}
		return *this;
	}
	std::string StrConstant::getvalue() const{
		return value;
	}

	void StrConstant::setvalue(const std::string in){
		value = in;
	}

	FloatConstant::FloatConstant() : Constant{false,ucc::type::FLOAT, true}, value{0.0f} {}

	FloatConstant::FloatConstant(const float invalue ) : Constant{false,ucc::type::FLOAT, true}, value{invalue } {}


	FloatConstant::FloatConstant(const FloatConstant& in ) : Constant{in.getlval(),ucc::type::FLOAT, true}, value{in.value } {}

	FloatConstant::~FloatConstant(){}

	FloatConstant& FloatConstant::operator=(const FloatConstant& in){
		if(&in != this){
			value = in.value;
			setlval(in.getlval());
			setnumeric(true);
			settype(ucc::type::FLOAT);
		}
		return *this;
	}
	float FloatConstant::getvalue() const{
		return value;
	}
	void FloatConstant::setvalue(const float in){
		value = in;
	}



}
	