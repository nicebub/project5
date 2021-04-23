#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
#endif

#include "List.hpp"
#include "type.h"

//extern int warning(char*,char*);
extern int error(std::string,std::string);

using namespace ucc;

BasicListNode::BasicListNode(eNodeType t) : nodeType{t} {}

eNodeType BasicListNode::get_nodeType() const {
	return nodeType;
}
void BasicListNode::set_nodeType(eNodeType in){
	nodeType = in;
}
	
ListNode::ListNode() : ListNode("") {}

ListNode::ListNode(std::string in) : BasicListNode{eNodeType::STANDARD}, val{in} {}

std::string ListNode::getval() const{
	return val;
}
void ListNode::setval(std::string in){
	val = in;
}

ExprListNode::ExprListNode() : ExprListNode{NULL} {}

ExprListNode::ExprListNode(exprtype* expr) : BasicListNode{eNodeType::EXPR}, expr{expr}{}

ExprListNode::~ExprListNode(){
	if(expr){
		delete expr;
	}
}
ExprListNode::ExprListNode(const ExprListNode& in) : BasicListNode{in.get_nodeType()} {
	expr = in.expr;
}
ExprListNode& ExprListNode::operator=(const ExprListNode& in){
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

int size() const{
	return list.size();
}

List& List::operator=(const List& in){
	return *this;
}
	
void List::push_back(BasicListNode* in){
	list.push_back(in);
}

List* List::mklist(std::string inVal){
	List* temp{new List{}};
	temp->appendList(inVal);
	return temp;
}
List* List::mklist(std::string inVal, type inType){
	List* temp{new List{}};
	temp->appendList(inVal,inType);
	return temp;
}
List* List::mklist(exprtype* inExpr){
	List* temp{new List{}};
	temp->appendList(inExpr);
	return temp;
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
List* List::appendList(exprtype* inexpr){
	ExprListNode* nnode{new ExprListNode{inexpr}};
	list.push_back(dynamic_cast<BasicListNode*>(nnode));
	return this;
}

void printListP(ListP * inList){
	#ifdef DEBUG
    debugprintd("inList size: ",inList->listsize);
	#endif
    if(inList != NULL){
        listnodeP* inNode = inList->list;
        if(inNode !=NULL){
            while(inNode != NULL){
				#ifdef DEBUG
                	debugprint("inNode value val: ",inNode->val);
                	debugprintd("inNode ttype: ",inNode->ttype);
                	inNode = (listnodeP*)inNode->nextnode;
				#endif
                
            }
        }
    }

}
