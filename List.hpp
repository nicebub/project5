#ifndef _MYLISTH
#define _MYLISTH
#include <vector>
#include <string>

#include "type.hpp"
#include "cpptypes.hpp"
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
class ReturnPacketListNode : public BasicListNode {
	public:
		ReturnPacketListNode();
		ReturnPacketListNode(ReturnPacket* expr);
		virtual ~ReturnPacketListNode();
		ReturnPacketListNode(const ReturnPacketListNode& in);
		virtual ReturnPacketListNode& operator=(const ReturnPacketListNode& in);
	private:
		ReturnPacket* expr;
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
		std::vector<BasicListNode*> getlist();
		static List* mklist(std::string inVal);
		static List* mklist(std::string inVal, type inType);
		static List* mklist(ReturnPacket* expr);
		std::vector<BasicListNode*>::iterator begin();
		std::vector<BasicListNode*>::iterator end();
		List* appendList(std::string inVal);
		List* appendList(std::string inVal, ucc::type inType);
		List* appendList(ReturnPacket* expr);
//		void printListP(ListP * inList);
		int size() const;
	private:
		std::vector<BasicListNode*> list;
};

}
#endif
