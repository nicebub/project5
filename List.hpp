#ifndef _MYLISTH
#define _MYLISTH
#include <vector>
#include <string>

#include "type.hpp"

namespace ucc{


enum class eNodeType { STANDARD, EXPR, P };

class BasicListNode{
	public:
		BasicListNode(eNodeType t);
		virtual ~BasicListNode() = 0;
		eNodeType get_nodeType() const;
		void set_nodeType(eNodeType);
	private:
		eNodeType nodeType;
};

class ListNode : public BasicListNode {
	public:
		ListNode();
		ListNode(std::string in);
		virtual ~ListNode() = default;
//		ListNode(const ListNode& in);
//		virtual ListNode& operator=(const ListNode& in);
		std::string getval() const;
		void setval(std::string in);
	private:
		std::string val;
};
class ExprListNode : public BasicListNode {
	public:
		ExprListNode();
		ExprListNode(exprtype* expr);
		virtual ~ExprListNode();
		ExprListNode(const ExprListNode& in);
		virtual ExprListNode& operator=(const ExprListNode& in);
	private:
		exprtype* expr;
};
class PListNode : public ListNode {
	public:
		PListNode();
		PListNode(std::string, ucc::type);
		virtual ~PListNode() = default;
//		PListNode(const PListNode& in);
//		virtual PListNode& operator=(const PListNode& in);
		ucc::type gettype() const;
		void settype(ucc::type type);
	private:
		ucc::type type;
};
class List{
	public:
		List();
		~List();
		List(const List& cp);
		List& operator=(const List& in);
		void push_back(BasicListNode* node);

		static List* mklist(std::string inVal);
		static List* mklist(std::string inVal, type inType);
		static List* mklist(exprtype* expr);

		List* appendList(std::string inVal);
		List* appendList(std::string inVal, ucc::type inType);
		List* appendList(exprtype* expr);
//		void printListP(ListP * inList);
		int size() const;
	private:
		std::vector<BasicListNode*> list;
};
	struct funcheadertype {
    std::string 	name;
    List* 			paramlist;
    type 			returntype;
    type 			ttype;
};

}
#endif
