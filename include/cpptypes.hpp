#ifndef _CPPSTYPES_HPP
#define _CPPSTYPES_HPP

#include <string>
#include "type.hpp"
namespace ucc{

	class TableEntry;
	
class ReturnPacket{
	public:
		ReturnPacket();
		ReturnPacket(bool lval , ucc::type ttype, bool ifnum, int offset);
		bool getlval() const;
		void setlval(const bool in);
		ucc::type gettype() const;
		void settype(const ucc::type in);
		bool getnumeric() const;
		void setnumeric(const bool in);
		virtual ~ReturnPacket();
		int getoffset() const;
		void setoffset(const int in);

		struct Pair m_pair;
		TableEntry* funcent;
		int params;
	protected:
		int offset;
		bool lval;
		bool numeric;
		ucc::type ttype;

};

class Constant : public ReturnPacket{
	public:
		Constant();
		Constant(bool lval , ucc::type ttype, bool ifnum, int offset);
		virtual ~Constant();
//		ReturnPacket
	private:
};

class IntConstant : public Constant{
	public:
		IntConstant();
		IntConstant(const int invalue);
		IntConstant(const IntConstant&);
		virtual ~IntConstant();
		IntConstant& operator=(const IntConstant& in);
		int getvalue() const;
		void setvalue(const int in);
	private:
		int value;
};
class StrConstant : public Constant{
	public:
		StrConstant();
		StrConstant(const std::string invalue);
		StrConstant(const StrConstant&);
		virtual ~StrConstant();
		StrConstant& operator=(const StrConstant& in);
		std::string getvalue() const;
		void setvalue(const std::string in);
	private:
		std::string value;
};
class FloatConstant : public Constant{
	public:
		FloatConstant();
		FloatConstant(const float invalue);
		FloatConstant(const FloatConstant&);
		virtual ~FloatConstant();
		FloatConstant& operator=(const FloatConstant& in);
		float getvalue() const;
		void setvalue(const float in);
	private:
		float value;
};

class Identifier : public Constant {
	public:
		Identifier();
		Identifier(const std::string invalue);
		Identifier(const StrConstant&);
		virtual ~Identifier();
		Identifier& operator=(const Identifier& in);
		std::string getvalue() const;
		void setvalue(const std::string in);
	private:
			std::string value;
};
class Funcb : public Identifier {
	public:
		Funcb();
		Funcb(ucc::type returntype);
		Funcb(ucc::type returntype, bool bodydef, int num_param, std::vector<ucc::type> param_type, int label, int localcount, int actual_num);
		Funcb(const Funcb& in);
		Funcb& operator=(const Funcb& in);
		virtual ~Funcb();
		std::vector<type>& getparam_type();
		type getreturntype();
		bool getbodydef();
		int getnum_param();
		int getlabel();
		int getlocalcount();
		int getactual_num();
		void setparam_type(std::vector<type> param_type);
		void setreturntype( ucc::type returntype );
		void setbodydef(bool bodydef);
		void setnum_param(int num_param);
		void setlabel(int label);
		void setlocalcount(int localcount);
		void setactual_num(int actual_num);

	private:
		std::vector<ucc::type> param_type;
		type 	returntype;
		bool 	bodydef;
		int 	num_param;
		int 	label;
		int 	localcount;
		int 	actual_num;
};

class Varb : public Identifier {
	public:
		Varb();
		virtual ~Varb();
	private:
};

class Paramb : public ReturnPacket {
	public:
		Paramb();
		virtual ~Paramb();
	private:
};




}

#endif
