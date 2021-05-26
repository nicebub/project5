#include "cpptypes.hpp"
#include "type.hpp"

namespace ucc{
	ReturnPacket::ReturnPacket() :
										offset{0},
										lval{false},
										numeric{false},
										ttype{ucc::type::INT}
										{}
		
	ReturnPacket::ReturnPacket(bool lval , 
										ucc::type ttype=ucc::type::INT, 
										bool ifnum=false, 
										int inoffset=0) : 
										offset{inoffset},
										lval{lval},
										numeric{ifnum},
										ttype{ttype}
										{}

	ReturnPacket::~ReturnPacket(){}

	bool ReturnPacket::getlval() const {
		return lval;
	}
	void ReturnPacket::setlval(const bool in){
		lval = in;
	}
	ucc::type  ReturnPacket::gettype() const {
		return ttype;
	}
	void ReturnPacket::settype(const ucc::type in){
		ttype = in;
	}
	bool ReturnPacket::getnumeric() const{
		return numeric;
	}
	void ReturnPacket::setnumeric(const bool in){
		numeric = in;
	}
	int ReturnPacket::getoffset() const{
		return offset;
	}
	void ReturnPacket::setoffset(const int in){
		offset = in;
	}


	Constant::~Constant() {}

	Constant::Constant() : ReturnPacket{} {}
	Constant::Constant(bool lval , ucc::type ttype, bool ifnum, int offset) : ReturnPacket{lval,ttype,ifnum,offset} {}

	IntConstant::IntConstant() : Constant{false,ucc::type::INT, true, 0}, value{0} {}

	IntConstant::IntConstant(const int invalue) : Constant{false,ucc::type::INT, true, 0}, value{invalue} {}
		
	IntConstant::IntConstant(const IntConstant& in) : Constant{in.lval,ucc::type::INT, true, 0}, value{in.value} {}
		
	IntConstant::~IntConstant(){}
		
	IntConstant& IntConstant::operator=(const IntConstant& in){
		if(&in != this){
			value = in.value;
			lval = in.lval;
//			setlval(in.getlval());
			numeric = true;
//			setnumeric(true);
			ttype = ucc::type::INT;
//			settype(ucc::type::INT);
		}
		return *this;
	}
	int IntConstant::getvalue() const {
		return value;
	}

	void IntConstant::setvalue(const int in){
		value = in;
	}	

	StrConstant::StrConstant() : Constant{false,ucc::type::STR, false, 0} {}
		
	StrConstant::StrConstant(const std::string invalue) : Constant{false,ucc::type::STR, false, 0} , value{invalue} {}
		
	StrConstant::StrConstant(const StrConstant& in) : Constant{in.lval,ucc::type::STR, false, in.offset} , value{in.value} {}
		
	StrConstant::~StrConstant() {}
		
	StrConstant& StrConstant::operator=(const StrConstant& in) {
		if(&in != this){
			value = in.value;
			lval = in.lval;
			numeric = false;
			ttype = ucc::type::STR;
			offset = in.offset;
		}
		return *this;
	}
	std::string StrConstant::getvalue() const{
		return value;
	}

	void StrConstant::setvalue(const std::string in){
		value = in;
	}

	FloatConstant::FloatConstant() : Constant{false,ucc::type::FLOAT, true, 0}, value{0.0f} {}

	FloatConstant::FloatConstant(const float invalue ) : Constant{false,ucc::type::FLOAT, true, 0}, value{invalue } {}


	FloatConstant::FloatConstant(const FloatConstant& in ) : Constant{in.lval,ucc::type::FLOAT, true, in.offset}, value{in.value } {}

	FloatConstant::~FloatConstant(){}

	FloatConstant& FloatConstant::operator=(const FloatConstant& in){
		if(&in != this){
			value = in.value;
			lval = in.lval;
			numeric = true;
			ttype = ucc::type::FLOAT;
			offset = in.offset;
		}
		return *this;
	}
	float FloatConstant::getvalue() const{
		return value;
	}
	void FloatConstant::setvalue(const float in){
		value = in;
	}

	Identifier::Identifier() : Constant{false,ucc::type::IDENT, false, 0} {}
		
	Identifier::Identifier(const std::string invalue) : Constant{false,ucc::type::IDENT, false, 0} , value{invalue} {}
		
	Identifier::Identifier(const StrConstant& in) : Constant{in.getlval(),ucc::type::IDENT, false, in.getoffset()} , value{in.getvalue()} {}
		
	Identifier::~Identifier() {}
		
	Identifier& Identifier::operator=(const Identifier& in) {
		if(&in != this){
			value = in.value;
			lval = in.lval;
			numeric = false;
			ttype = ucc::type::IDENT;
			offset = in.offset;
		}
		return *this;
	}
	std::string Identifier::getvalue() const{
		return value;
	}

	void Identifier::setvalue(const std::string in){
		value = in;
	}

	Funcb::Funcb() :	param_type{},
							returntype{ucc::type::VOID},
							bodydef{false},
							num_param{0},
							label{0},
							localcount{0},
							actual_num{0}
	{}
	Funcb::Funcb(ucc::type returntype, bool bodydef, int num_param, std::vector<ucc::type> param_type, int label, int localcount, int actual_num) :
						param_type{param_type},
		 				returntype{returntype},
						bodydef{bodydef},
						num_param{num_param},
						label{label},
						localcount{localcount},
						actual_num{actual_num}
	{}
		Funcb::Funcb(ucc::type returntype) : Funcb{} {this->returntype = returntype;}
	Funcb::Funcb(const Funcb& in) : 
						param_type{in.param_type},
						returntype{in.returntype},
						bodydef{in.bodydef},
						num_param{in.num_param},
						label{in.label},
						localcount{in.localcount},
						actual_num{in.actual_num}
	{}
		
	Funcb& Funcb::operator=(const Funcb& in) {
		if(&in != this){
			returntype = in.returntype;
			bodydef = in.bodydef;
			num_param = in.num_param;
			label = in.label;
			localcount = in.localcount;
			actual_num = in.actual_num;
			param_type = in.param_type;
		}
		return *this;
	}
	Funcb::~Funcb() {}
	std::vector<ucc::type> Funcb::getparam_type() {
		return param_type;
	}
	ucc::type Funcb::getreturntype() {
		return returntype;
	}
	bool Funcb::getbodydef() {
		return bodydef;
	}
	int Funcb::getnum_param() {
		return num_param;
	}
	int Funcb::getlabel() {
		return label;
	}
	int Funcb::getlocalcount() {
		return localcount;
	}
	int Funcb::getactual_num() {
		return actual_num;
	}
	void Funcb::Funcb::setparam_type(std::vector<ucc::type> param_type) {
		this->param_type = param_type;
	}
	void Funcb::setreturntype( ucc::type returntype ) {
		this->returntype = returntype;
	}
	void Funcb::setbodydef(bool bodydef) {
		this->bodydef = bodydef;
	}
	void Funcb::setnum_param(int num_param) {
		this->num_param = num_param;
	}
	void Funcb::setlabel(int label) {
		this->label = label;
	}
	void Funcb::setlocalcount(int localcount) {
		this->localcount = localcount;
	}
	void Funcb::setactual_num(int actual_num ){
		this->actual_num = actual_num;
	}

	Varb::Varb() : ReturnPacket{} {}
	Paramb::Paramb() : ReturnPacket{} {}
}
	