#ifndef _SYMTABH
#define _SYMTABH

#include <search.h>
#include <cstdio>
#include <map>
#include <deque>

#include "List.hpp"
#include "type.hpp"
//#include "main.h"

//extern int Line_Number;
//extern FILE *infile;
//extern int offset_counter;
//extern int globalcount;

//extern int warning(char*, char*);

//extern int error(char*,char*);


namespace ucc{

	class TableEntry{
		public:
			TableEntry();
			TableEntry(std::string name);
			TableEntry(std::string name, void* binding, btype self);
			~TableEntry();
			TableEntry(const TableEntry& in);
			TableEntry& operator=(const TableEntry& in);
			std::string getName() const;
			void setName(std::string name);
			void* getBinding();
		private:
			std::string name;
			void * binding;
			btype self;
	};
	class Table{
		public:
			Table();
			~Table();
			void* lookup(const std::string name);
			TableEntry* lookupB(const std::string name);
			bool install(TableEntry * temp);
		private:
			std::map<std::string,TableEntry*> table;
	};
	using stable = std::map<std::string,void*,btype>;
	class SymbolTable{
		public:
		SymbolTable();
		~SymbolTable();
			void printTree() const;
			void Swalk(const void *node, VISIT myorder, int level);
			void install(TableEntry* entry);
			void* lookup(const std::string name);
			TableEntry* lookupB(const std::string name);
			bool inCscope(const std::string name);
			void openscope();
			void openmainscope();
			void closemainscope();
			void closescope();
			void deleteEntry(TableEntry * temp);
			void deleteTree();
			static SymbolTable* createTree(int Stacksize);
			void addtosymtab(type mytype, List* myList);
		private:
			std::deque<Table*> stack; //Stack of Binary Search Trees
			int actualStacksize; //used to keep size and top of stack
			int Stacksize; //default of 100
			int offset_counter;
		};
		int getleveldif(std::string name, SymbolTable* mysymtab);
		TableEntry* createFunc(std::string name, type returntype, List* paramlist);
		TableEntry* createVar(std::string name, type t_type, int offset);
		TableEntry* createParam(std::string name, type t_type, int offset);
		bool Ecmp(const void *TableEntry1, const void *TableEntry2);  //comparison function

}
#endif
