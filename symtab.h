#ifndef _SYMTABH
#define _SYMTABH
#include <search.h>
#include <cstdio>
#include <map>
#include "List.h"
#include "type.h"
#include "main.h"

//extern int Line_Number;
//extern FILE *infile;
//extern int offset_counter;
//extern int globalcount;

//extern int warning(char*, char*);

//extern int error(char*,char*);


namespace ucc{
	class SymbolTable{
		public:
		SymbolTable();
		~SymbolTable();
			int Ecmp(const void *Entry1, const void *Entry2);  //comparison function
			void printTree(Symtab *symtab);
			void Swalk(const void *node, VISIT myorder, int level);
			static void install(Entry*, Symtab *symtab);
			static void * lookup(const std::string name, Symtab *symtab);
			static Entry * lookupB(const std::string name, Symtab *symtab);
			static bool inCscope(const std::string name, Symtab *symtab);
			static void openscope(Symtab *symtab);
			static void openmainscope(Symtab *symtab);
			static void closemainscope(Symtab *symtab);
			static void closescope(Symtab *symtab);
			void deleteEntry(Entry * temp);
			void deleteTree(Symtab *symtab);
			static Symtab * createTree(int Stacksize);
			static Entry* createFunc(std::string name, type returntype, ListP *paramlist);
			static Entry* createVar(std::string name, type t_type, int offset);
			static Entry* createParam(std::string name, type t_type, int offset);
			static void addtosymtab(Symtab* mysymtab, type mytype, List * myList);
			static int getleveldif(std::string name, Symtab *mysymtab);
		private:
			std::map<std::string,Entry*> table;
		};
}
#endif
