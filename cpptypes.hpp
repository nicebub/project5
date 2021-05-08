#ifndef _CPPSTYPES_HPP
#define _CPPSTYPES_HPP

#include <string>
#include "type.hpp"

namespace ucc{


	
class ReturnPacket{
	public:
		ReturnPacket(bool, ucc::type, bool);
		bool getlval() const;
		void setlval(const bool in);
		ucc::type gettype() const;
		void settype(const ucc::type in);
		bool getnumeric() const;
		void setnumeric(const bool in);
		virtual ~ReturnPacket();
	private:
		bool lval;
		ucc::type ttype;
		bool numeric;
};



class IntConstant : public ReturnPacket{
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
class StrConstant : public ReturnPacket{
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
class FloatConstant : public ReturnPacket{
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

}

#endif