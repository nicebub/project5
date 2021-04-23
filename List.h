#ifndef _MYLISTH
#define _MYLISTH
#include "type.h"
#include "expr.h"

namespace ucc{
	
//typedef struct _listnodeE listnodeE;
using listnodeE = struct _listnodeE;

struct _listnodeE{
	exprtype* expr;
	listnodeE *nextnode;
};

struct ListE {
	int listsize;
	listnodeE *list;
};


//typedef struct _listnode listnode;
using listnode = struct _listnode;

struct _listnode{
	char * val;
	listnode *nextnode;
};

//typedef struct _listnodeP listnodeP;
using listnodeP = struct _listnodeP;

struct _listnodeP{
	char * val;
	type ttype;
	listnodeP *nextnode;
};


//typedef struct _ListP ListP;

using ListP = struct _ListP;

struct _ListP{
	listnodeP * list;
	int listsize;
};

struct funcheadertype {
    char * name;
    ListP * paramlist;
    type returntype;
    type ttype;
};
class List{
	public:
		List();
		~List();
		List(const List& cp);
		List& operator=(const List& in);
		void deleteList(List * inList);
		List * mklist(char * inVal);

		List * appendList(List * inList, char* inVal);

		void deleteListP(ListP * inList);

		ListP * mklistP(char* inName, type intype);

		ListP * appendListP(ListP *inList, char* inName, type intype);

		void deleteListE(ListE *inList);

		ListE * mklistE(exprtype* expr);

		ListE * appendListE(ListE * inList, exprtype* expr);

		void printListP(ListP * inList);

	private:
		listnode* list;
		int size;
};
}
#endif
