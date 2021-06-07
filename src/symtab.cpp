#include <string>
#include <cstdio>
#include <cstdlib>
#include <search.h>

#include "debug.hpp"
#include "symtab.hpp"
#include "type.hpp"
#include "list.hpp"
#include "data.hpp"
#include "cpptypes.hpp"

using namespace ucc;
namespace ucc{
//extern int error(std::string,std::string);

TableEntry::TableEntry() : TableEntry{""} {}
TableEntry::TableEntry(std::string name) :name{name}, binding{nullptr}, self{btype::FUNC} {}
TableEntry::TableEntry(std::string name, ReturnPacket* binding, btype self) : name{name}, binding{binding}, self{self} {}
TableEntry::~TableEntry(){
	if(binding){
//		delete binding;
// delete binding depeinding on FUNC, VAR, PARAM, need to create classes for those with destructors to make
//	this work better
	}
}
TableEntry::TableEntry(const TableEntry& in) : name{in.name}, binding{in.binding}, self{in.self} {}

TableEntry& TableEntry::operator=(const TableEntry& in){
	if(this != &in){
		name = in.name;
		binding = in.binding;
		self = in.self;
	}
	return *this;
}
void TableEntry::setName(std::string inName){
	name = inName;
}
std::string TableEntry::getName() const{
	return name;
}
ReturnPacket* TableEntry::getBinding(){
	return binding;
}

btype TableEntry::getself() const{
	return self;
}


Table::Table() : table{} {}
Table::~Table(){
/*
    for(auto& element : table){
		//decompose the element and delete the pointer data
//		delete element;
	}
*/
}
ReturnPacket* Table::lookup(const std::string name){
	auto result{table.find(name)};
	if(result != table.end()){
		return result->second->getBinding();
	}
	return nullptr;
}
TableEntry* Table::lookupB(const std::string name){
	try{
		auto result{table.at(name)};
		return result;
	}
	catch(std::out_of_range& e){
		// not in table
	    std::cerr << "caught out of range" << std::endl;
	}
    return nullptr;
}

bool Table::install(TableEntry* entry){
	#ifdef DEBUG
//	fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",actualStacksize, actualStacksize-1,Stacksize);
	#endif
	bool answer;
	try{
		table.at(entry->getName());
	    std::cerr << "symbol already declared in current scope" << std::endl;
		answer = false;
	}
	catch(std::exception& e){
		table[entry->getName()] = entry;
		answer = true;
	}
	debugprint("through install function of symbol table. Printing symbol table tree\n","");
//	printTree(symtab);

	return answer;
}
//SymbolTable::SymbolTable() : stack{}, compiler{}, actualStacksize(1),Stacksize(1),offset_counter{0} {}

SymbolTable::SymbolTable(Compiler& compiler) : stack{}, compiler{compiler}, actualStacksize(1), Stacksize(1), offset_counter{0} {
	openscope();
	
}
//SymbolTable::SymbolTable() : stack{}, compiler{nullptr}, actualStacksize(1), Stacksize(1) {}
SymbolTable::~SymbolTable(){
	for(auto element : stack){
		delete element;
		element = nullptr;
	}
}

void SymbolTable::openmainscope(){
/*	if(actualStacksize == Stacksize)
		compiler.error("Scope Stack already too full","");
	else{*/
		#ifdef DEBUG
		fprintf(stderr,"Opening new Scope\n");
		#endif
		stack.push_back(new Table{});
		
		offset_counter=5;
/*	}*/
	
}
void SymbolTable::openscope(){
/*	if(actualStacksize == Stacksize)
		compiler.error("Scope Stack already too full","");
	else{*/
		#ifdef DEBUG
		fprintf(stderr,"Opening new Scope\n");
//		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif
		stack.push_back(new Table{});
	 	actualStacksize += 1;

		offset_counter=5;
		#ifdef DEBUG
//		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif
/*		}*/
}

void SymbolTable::closescope(){
	if(actualStacksize == 1)
		compiler.error("Cannot close Global scope","");
	else{
		#ifdef DEBUG
		fprintf(stderr,"Closing Scope\n");
		#endif
		if(!stack.empty()) {
			stack.pop_back();
			/*
			while(Stack[actualStacksize-1] != nullptr){
				temp = *((TableEntry**)(Stack[actualStacksize-1] ));
				tdelete((void*)temp,(void **) &(Stack[actualStacksize-1]), Ecmp);
				delete temp;
			}
			Stack[actualStacksize-1]=nullptr;*/
			actualStacksize -= 1;
		}
	}
}

void SymbolTable::closemainscope(){
	if(actualStacksize == 1)
		compiler.error("Cannot close Global scope","");
	else{
		#ifdef DEBUG
		fprintf(stderr,"Closing Scope\n");
		#endif
		if(!stack.empty()){
			stack.pop_back();
			/*
			while(Stack[actualStacksize-1] != nullptr){
				temp = *((TableEntry**)(Stack[actualStacksize-1] ));
				tdelete((void*)temp,(void **) &(Stack[actualStacksize-1]), Ecmp);
				delete temp;

			}
			Stack[actualStacksize-1]=nullptr;
			*/
			actualStacksize -= 1;
		}
	}
}


ReturnPacket* SymbolTable::lookup(const std::string name){
//	TableEntry* temp;
//	int a;
	if(!name.empty()){

		#ifdef DEBUG
//		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif
		for(auto it = stack.rbegin(); it != stack.rend(); it++){
			auto result = (*it)->lookup(name);
			if(result != nullptr){
				return result;
			}
		}
		return nullptr;
	}
	else{
		compiler.error("cannot lookup variable without a name","");
		return nullptr;
	}
}

void SymbolTable::install(TableEntry* temp){
	#ifdef DEBUG
    std::cerr << "symtab->actualStacksize " << actualStacksize << "and symtab->actualStacksize - 1 : " <<  actualStacksize-1 << ", and symtab->Stacksize: " << Stacksize << std::endl;
	#endif
	Table* locatedTable{stack.back()};
	if(!locatedTable->install(temp)){
		compiler.error("symbol already declared in current scope","");
	}

	debugprint("through install function of symbol table. Printing symbol table tree\n","");
//	printTree(symtab);
}
/*
bool Ecmp(const void *TableEntry1, const void *TableEntry2){
	return ((TableEntry*)TableEntry1)->name == ((TableEntry*)TableEntry2)->name;
}
*/
#ifdef DEBUG
void ucc::SymbolTable::printTree() const{
}
/*void SymbolTable::printTree(SymbolTable *symtab){
	if(symtab != nullptr){
//		twalk((void*) (symtab->Stack[symtab->actualStacksize-1]), Swalk);
	}
	else{
		fprintf(stderr,"Stack was null\n");
	}
}*/
/*
void SymbolTable::Swalk(const void *node, VISIT myorder, int level){
		TableEntry * temp;
		Funcb * tempb;
		int a=0;
	if(myorder == preorder || myorder == leaf){
		temp = (*(TableEntry**) node);
		tempb = ((Funcb*)(temp->binding));
		switch(temp->self){

		case(FUNC):		fprintf(stderr,"Name: %s\n", temp->name);
						fprintf(stderr,"Return Type: ");
					switch(tempb->returntype){
						case(INT):	fprintf(stderr,"INT\n"); break;
						case(FLOAT):	fprintf(stderr,"FLOAT\n"); break;
						case(VOID):	fprintf(stderr,"VOID\n"); break;
                        case CHAR:
                            
                            break;
                        case STR:
                            
                            break;
                        case REFINT:
                            
                            break;
                        case REFFLOAT:
                            
                            break;
                        case REFSTR:
                            
                            break;
                    }
					fprintf(stderr,"Body Defined: %d\n", tempb->bodydef);
					fprintf(stderr,"Number Parameters: %d\n",tempb->num_param);
					if(tempb->num_param >0){
						fprintf(stderr,"Parameter Types: ");
						for(a=0;a<tempb->num_param;a++){
							switch(tempb->param_type[a]){
								case(INT):	fprintf(stderr,"INT ");break;
								case(FLOAT):	fprintf(stderr,"FLOAT "); break;
								case(REFINT):	fprintf(stderr,"REFINT "); break;
								case(REFFLOAT):	fprintf(stderr, "REFFLOAT "); break;
								case(REFSTR):	fprintf(stderr, "REFSTR "); break;
								case(STR):	fprintf(stderr, "STR "); break;
								case(VOID):	fprintf(stderr, "VOID "); break;
                                case CHAR:
                                    
                                    break;
                            }
						}
					}
					if(tempb->num_param == -1){
						fprintf(stderr,"Parameter Types: ");
                        for(a=0;a<tempb->actual_num;a++){
                            switch(tempb->param_type[a]){
                                                                case(INT):      fprintf(stderr,"INT ");break;
                                                                case(FLOAT):    fprintf(stderr,"FLOAT "); break;
                                                                case(REFINT):   fprintf(stderr,"REFINT "); break;
                                                                case(REFFLOAT): fprintf(stderr, "REFFLOAT "); break;
                                                                case(REFSTR):   fprintf(stderr, "REFSTR "); break;
                                                                case(STR):      fprintf(stderr, "STR "); break;
                                                                case(VOID):     fprintf(stderr, "VOID "); break;
                                case CHAR:
                                
                                break;
                            }
                        }
						//fprintf(stderr,"...");

					}
					fprintf(stderr,"\n\n");

					break;
		case(PARAM):		fprintf(stderr,"Name: %s\n", temp->name);
							fprintf(stderr,"Type: ");
					switch( ((Paramb*)(temp->binding))->type){
						case(INT):	fprintf(stderr,"INT\n"); break;
						case(FLOAT):	fprintf(stderr,"FLOAT\n"); break;
                        case VOID:
                            
                            break;
                        case CHAR:
                            
                            break;
                        case(STR):	fprintf(stderr, "STR\n"); break;
						case(REFINT):	fprintf(stderr, "REFINT\n"); break;
						case(REFFLOAT):	fprintf(stderr, "REFFLOAT\n"); break;
						case(REFSTR):	fprintf(stderr, "REFSTR\n"); break;
					}
					fprintf(stderr,"Offset: %d\n\n", ((Paramb*)(temp->binding))->offset);

					break;
		case(VAR):		fprintf(stderr,"Name: %s\n", temp->name);
						fprintf(stderr,"Type: ");
					switch(((Varb*)(temp->binding))->type){
						case(INT):	fprintf(stderr, "INT\n");
								break;
						case(FLOAT):	fprintf(stderr, "FLOAT\n");

                        case VOID:
                            
                            break;
                        case CHAR:
                            
                            break;
                        case STR:
                            
                            break;
                        case REFINT:
                            
                            break;
                        case REFFLOAT:
                            
                            break;
                        case REFSTR:
                            
                            break;
                    }
					fprintf(stderr,"Offset: %d\n", ((Varb*)(temp->binding))->offset);

					break;

		}
	}
}

*/
#endif
SymbolTable* SymbolTable::createTree(Compiler& compiler,int Stacksize){
	SymbolTable *temp;
	temp = new SymbolTable{compiler};
	temp->actualStacksize=1;
	temp->Stacksize = Stacksize;
	return temp;
}
/*
void SymbolTable::deleteTree(SymbolTable *symtab){
	TableEntry * temp;
	//TableEntry ** found;
	if(symtab != nullptr){
	   #ifdef DEBUG
	   fprintf(stderr,"Deleting Tree: \n");
	   #endif
	    while(symtab->actualStacksize != 1)
		closescope(symtab);
	    if((symtab->Stack[symtab->actualStacksize-1]) !=nullptr){
                        while(symtab->Stack[symtab->actualStacksize-1] != nullptr){
                                temp = *((TableEntry**)(symtab->Stack[symtab->actualStacksize-1] ));
                                tdelete((void*)temp,(void **) &(symtab->Stack[symtab->actualStacksize-1]), Ecmp);
                                deleteTableEntry(temp);

                        }
                        symtab->Stack[symtab->actualStacksize-1]=nullptr;
            }
	    #ifdef DEBUG
	    fprintf(stderr,"Deleting Stack\n");
	    #endif
	    free(symtab->Stack);
	    #ifdef DEBUG
	    fprintf(stderr,"Deleting Symbol Table\n");
	    #endif
	    free(symtab);
	    symtab=nullptr;
	}
}
*/
/*
void SymbolTable::deleteTableEntry(TableEntry * temp){
	if(temp != nullptr){
		switch(temp->self){

			case(FUNC):
						#ifdef DEBUG
						fprintf(stderr,"Deleting Function %s\n", temp->name);
						#endif
						if( ((Funcb*)(temp->binding))->num_param > 0 || ((Funcb*)(temp->binding))->num_param == -1)
							free( ((Funcb*)(temp->binding))->param_type);
						free(temp->binding);
						free(temp->name);
						free(temp);
						temp=nullptr;
						break;
			case(VAR):
						#ifdef DEBUG
						fprintf(stderr,"Deleting variable %s\n", temp->name);
						#endif
						free(temp->name);
						free(temp->binding);
						free(temp);
						temp=nullptr;
						break;
			case(PARAM):
						#ifdef DEBUG
						fprintf(stderr,"Deleteing Parameter %s\n", temp->name);
						#endif
						free(temp->name);
						free(temp->binding);
						free(temp);
						temp= nullptr;
						break;
			default:	
						#ifdef DEBUG	
						fprintf(stderr,"Error in Node, doesn't have correct binding\n");
						#endif
						;
		}
	}

}
*/

TableEntry* SymbolTable::createFunc(std::string name, type returntype, List* paramlist){
	TableEntry * temp;
//	ListNode* tempP;
//	int a;
	bool elip=false;
	
	if(!name.empty()){
		//Funcb * tBinding = (Funcb*)temp->binding;
        Funcb* tBinding{};
		//((Funcb*)(temp->binding)) = (Funcb*) malloc(sizeof(Funcb));
		//((Funcb*)(temp->binding))->returntype = returntype;
		tBinding = new Funcb{returntype};

//        tBinding->param_type=nullptr;
//        temp->binding = tBinding;
			temp = new TableEntry{name,tBinding,btype::FUNC};

        if(paramlist!=nullptr ){
            #ifdef DEBUG
//            fprintf(stderr,"in Function install- temp->binding->num_param is: %d\n", ((Funcb*)(temp->binding))->num_param);
            #endif


            #ifdef DEBUG
//            Funcb * extraBind = (Funcb*)(temp->getBinding());
//            fprintf(stderr,"in Function install- extraBind->num_param is: %d\n", extraBind->num_param);
            #endif

			tBinding->setnum_param(paramlist->size());
        }
/*		else
			tBinding->num_param=0;
*/
		if(tBinding->getnum_param() >0){
//			tBinding->param_type = (type*)malloc((sizeof(type) * paramlist->size()));
//			tempP = paramlist->list;
			for(auto element : *paramlist){
//			for(a=0;a<paramlist->size();a++){
	PListNode * n_element{dynamic_cast<PListNode*>(element)};
				tBinding->getparam_type().push_back(n_element->gettype());

				#ifdef DEBUG
				fprintf(stderr,"in Function install type is %d\n",n_element->gettype());
				#endif

				if( "..." == n_element->getval()){
					elip = true;
				}
				else{
					elip=false;
				}

//				tempP = (ListNode*) tempP->nextnode;

			}
			if(elip == true) {
				tBinding->setactual_num(tBinding->getnum_param());
				tBinding->setnum_param(-1);
			}
		}
/*		else
			tBinding->param_type = nullptr;
 */
//		tBinding->bodydef = FALSE;
//		tBinding->label=0;
		return temp;
	}
	else{
		compiler.error("name not found\n","");
		return nullptr;
	}
}

TableEntry* SymbolTable::createVar(std::string name, type t_type, int offset){
	TableEntry * temp{nullptr};
	//Varb * tBindingV = (Varb *)temp->binding;
    Varb* tBindingV{nullptr};
	//((Varb*)(temp->binding)) = (Varb*) malloc(sizeof(Varb));
	tBindingV = new Varb{};
	tBindingV->settype(t_type);
 	tBindingV->setoffset(offset);

	//((Varb*)(temp->binding))->type = t_type;
	#ifdef DEBUG
	fprintf(stderr,"in Var install type is :%d\n",t_type);
	#endif
    //((Varb*)(temp->binding))->offset = offset;
//    temp->binding = tBindingV;
	temp = new TableEntry{name,tBindingV,btype::VAR};
	return temp;
}

TableEntry* SymbolTable::createParam(std::string name, type t_type, int offset){
	TableEntry* temp{nullptr};
//    temp->binding = nullptr;
    Paramb* tBindingP{nullptr};
	//((Paramb*)(temp->binding)) = (Paramb*) malloc(sizeof(Varb));
	//((Paramb*)(temp->binding))->type = t_type;
	tBindingP = new Paramb{};
	tBindingP->settype(t_type);
   tBindingP->setoffset(offset);
//   temp->binding = tBindingP;
	#ifdef DEBUG
	fprintf(stderr,"in Param install type is :%d\n",t_type);
	#endif
	//((Paramb*)(temp->binding))->offset = offset;
	temp = new TableEntry{name,tBindingP,btype::PARAM};
	return temp;
}

void SymbolTable::addtosymtab(type mytype, List * myList){
//	int a;
//	ListNode * tempN;
	TableEntry * temp;
		if(myList !=nullptr){
//			tempN = (ListNode*)(myList->list);
			for(auto& element : *myList){
				ListNode* n_element{static_cast<ListNode*>(element)};
				temp= createVar(n_element->getval(), mytype, offset_counter);
				offset_counter++;
				if((actualStacksize-1) == 0){
					compiler.globalcount++;
				}
				install(temp);
				temp = nullptr;
//				tempN = (ListNode*)tempN->nextnode;
			}
//			delete myList;
		}
		else compiler.error("myList was nullptr","");
}

TableEntry * SymbolTable::lookupB(const std::string name){
//	TableEntry* temp;
//	int a;
	if(!name.empty()){

		#ifdef DEBUG
//		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif
		for(auto it = stack.rbegin(); it != stack.rend(); it++){
			auto result = (*it)->lookupB(name);
			if(result != nullptr){
				return static_cast<TableEntry*>(result);
			}
		}
		return nullptr;
	}
	else{
		compiler.error("cannot lookup variable without a name","");
		return nullptr;
	}
}

bool SymbolTable::inCscope(const std::string name){
        if(!name.empty()){
			  auto table = stack.rbegin();
			  auto result = (*table)->lookup(name);
			  if(result != nullptr){
				  return true;
			  }
        }
    return false;
}

int SymbolTable::getleveldif(std::string name){
	TableEntry ** found;
	found = nullptr;
//	TableEntry *temp;
//	int a;
	if(!name.empty()){
			#ifdef DEBUG
//			fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
			#endif
			for(auto it = stack.rbegin(); it != stack.rend(); it++){
				auto result = (*it)->lookup(name);
				if(result != nullptr){
					return static_cast<int>(it - stack.rend());
				}
			}
	}
	return -1;
}
}
