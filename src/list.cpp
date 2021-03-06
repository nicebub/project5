#include <string>

#include "debug.hpp"
#include "list.hpp"
#include "type.hpp"


using namespace ucc;

namespace ucc{
BasicListNode::BasicListNode(eNodeType t) : nodeType{t} {}

eNodeType BasicListNode::get_nodeType() const {
	return nodeType;
}
void BasicListNode::set_nodeType(eNodeType in){
	nodeType = in;
}

BasicListNode::~BasicListNode() {}
	
ListNode::ListNode() : ListNode("") {}

ListNode::ListNode(std::string in) : BasicListNode{eNodeType::STANDARD}, val{in} {}

std::string ListNode::getval() const{
	return val;
}
void ListNode::setval(std::string in){
	val = in;
}

ReturnPacketListNode::ReturnPacketListNode() : ReturnPacketListNode{NULL} {}

ReturnPacketListNode::ReturnPacketListNode(ReturnPacket* expr) : BasicListNode{eNodeType::EXPR}, expr{expr}{}

ReturnPacketListNode::~ReturnPacketListNode(){
	if(expr){
		delete expr;
	}
}
ReturnPacketListNode::ReturnPacketListNode(const ReturnPacketListNode& in) : BasicListNode{in.get_nodeType()} {
	expr = in.expr;
}
ReturnPacketListNode& ReturnPacketListNode::operator=(const ReturnPacketListNode& in){
	if(this != &in){
		expr = in.expr;
	}
	return *this;
}
PListNode::PListNode() : ListNode{}, type{} {
	set_nodeType(eNodeType::P);
	setval("");
}
PListNode::PListNode(std::string inVal, ucc::type inType) : type{inType}{
	set_nodeType(eNodeType::P);
	setval(inVal);
}

ucc::type PListNode::gettype() const{
	return type;
}
void PListNode::settype(ucc::type type){
	this->type = type;
}

List::List() : list{} {}
List::List(const List& cp) : list{cp.list} {}
List::~List(){
	for(auto* element : list){
		delete element;
	}
}

std::vector<BasicListNode*>::iterator List::begin(){
	return list.begin();
}
std::vector<BasicListNode*>::iterator List::end(){
	return list.end();
}

int List::size() const{
	return static_cast<int>(list.size());
}

List& List::operator=(const List& in){
	return *this;
}
	
void List::push_back(BasicListNode* in){
	list.push_back(in);
}

List* List::mklist(std::string inVal){
	return (new List{})->appendList(inVal);
}
List* List::mklist(std::string inVal, type inType){
	return (new List{})->appendList(inVal,inType);
}
List* List::mklist(ReturnPacket* inExpr){
	return (new List{})->appendList(inExpr);
}

List* List::appendList(std::string inVal){
	ListNode* nnode{new ListNode{inVal}};
	list.push_back(dynamic_cast<BasicListNode*>(nnode));
	return this;
}
List* List::appendList(std::string inVal, type inType){
	PListNode* nnode{new PListNode{inVal,inType}};
	list.push_back(dynamic_cast<BasicListNode*>(nnode));
	return this;
}
List* List::appendList(ReturnPacket* inexpr){
	ReturnPacketListNode* nnode{new ReturnPacketListNode{inexpr}};
	list.push_back(dynamic_cast<BasicListNode*>(nnode));
	return this;
}
std::vector<BasicListNode*> List::getlist(){
	return list;
}

}
