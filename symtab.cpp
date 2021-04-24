#include <string>
#include <cstdio>
#include <cstdlib>
#include <search.h>
#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
#endif

#include "symtab.hpp"
#include "type.h"
#include "List.hpp"
#include "data.h"
using namespace ucc;

extern int error(std::string,std::string);


TableEntry::TableEntry() : TableEntry{""} {}
TableEntry::TableEntry(std::string name) :name{name}, binding{NULL}, self{btype::FUNC} {}
TableEntry::TableEntry(std::string name, void* binding, btype self) : name{name}, binding{binding}, self{self} {}
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
std::string TableEntry::getName() const{
	return name;
}

Table::Table() : table{} {}
Table::~Table(){
	for(auto& element : table){
		//decompose the element and delete the pointer data
//		delete element;
	}
}
void Table::install(TableEntry* entry){
	#ifdef DEBUG
	fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",actualStacksize, actualStacksize-1,Stacksize);
	#endif

	const auto [thepair, status] = table.insert(entry->getName(),entry);

	if(!status){
		error("symbol already declared in current scope","");		
	}

	#ifdef DEBUG
	fprintf(stderr,"through install function of symbol table. Printing symbol table tree\n");
	printTree(symtab);
	#endif
}

SymbolTable::SymbolTable() : Stack{} {}
SymbolTable::~SymbolTable(){}

void SymbolTable::openmainscope(){
	if(actualStacksize == Stacksize)
		error("Scope Stack already too full","");
	else{
		#ifdef DEBUG
		fprintf(stderr,"Opening new Scope\n");
		#endif
		
		offset_counter=5;
	}
	
}
void SymbolTable::openscope(){
	if(actualStacksize == Stacksize)
		error("Scope Stack already too full","");
	else{
		#ifdef DEBUG
		fprintf(stderr,"Opening new Scope\n");
		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif

	 	actualStacksize += 1;

		offset_counter=5;
		#ifdef DEBUG
		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif
	}
}

void SymbolTable::closescope(){
	if(actualStacksize == 1)
		error("Cannot close Global scope","");
	else{
		#ifdef DEBUG
		fprintf(stderr,"Closing Scope\n");
		#endif
		if(!Stack.empty()) {
			Stack.pop();
			/*
			while(Stack[actualStacksize-1] != NULL){
				temp = *((TableEntry**)(Stack[actualStacksize-1] ));
				tdelete((void*)temp,(void **) &(Stack[actualStacksize-1]), Ecmp);
				delete temp;
			}
			Stack[actualStacksize-1]=NULL;*/
			actualStacksize -= 1;
		}
	}
}

void SymbolTable::closemainscope(){
	if(actualStacksize == 1)
		error("Cannot close Global scope","");
	else{
		#ifdef DEBUG
		fprintf(stderr,"Closing Scope\n");
		#endif
		if(!Stack.empty()){
			Stack.pop();
			/*
			while(Stack[actualStacksize-1] != NULL){
				temp = *((TableEntry**)(Stack[actualStacksize-1] ));
				tdelete((void*)temp,(void **) &(Stack[actualStacksize-1]), Ecmp);
				delete temp;

			}
			Stack[actualStacksize-1]=NULL;
			*/
			actualStacksize -= 1;
		}
	}
}


void* SymbolTable::lookup(const std::string name){
	TableEntry ** found;
    found = NULL;
	TableEntry* temp;
	int a;
	if(!name.empty()){
		auto& answer = table.find(name);
		if(answer != table.end()){
			
		}
		temp = new TableEntry;
		temp->name = name;
		#ifdef DEBUG
		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif
		for(a = actualStacksize-1;a>=0;a--){
			#ifdef DEBUG
			fprintf(stderr, "still in for loop\n");
			#endif
			found = (TableEntry**) tfind((void*) temp, (void**) &(Stack[a]),Ecmp);
			if(found != NULL){
				if(*found !=NULL) break;
			}
		}
		if(found != NULL){
			if(*found ==NULL){
				free(temp->name);
				temp->name = NULL;
				free(temp);
				temp = NULL;
				return NULL;
			}
			else{
				free(temp);
				temp = NULL;
				return ((void*) (*found)->binding);
			}
		}
		else{
			free(temp->name);
			temp->name = NULL;
			free(temp);
			temp = NULL;
			return NULL;
		}

	}
	else{
		error("cannot lookup variable without a name","");
		return NULL;
	}
}

void SymbolTable::install(TableEntry * temp){
	TableEntry ** found;
	#ifdef DEBUG
	fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",actualStacksize, actualStacksize-1,Stacksize);
	#endif
	found = (TableEntry**) tsearch((void*) temp, (void**) &((Stack[actualStacksize-1])),Ecmp);

	if(*found !=temp)
		error("symbol already declared in current scope","");
	#ifdef DEBUG
	fprintf(stderr,"through install function of symbol table. Printing symbol table tree\n");
	printTree(symtab);
	#endif
}

bool Ecmp(const void *TableEntry1, const void *TableEntry2){
	return ((TableEntry*)TableEntry1)->name == ((TableEntry*)TableEntry2)->name;
}

#ifdef DEBUG
void SymbolTable::printTree(Symtab *symtab){
	if(symtab->Stack[0] != NULL || symtab->Stack[symtab->actualStacksize-1] != NULL)
		twalk((void*) (symtab->Stack[symtab->actualStacksize-1]), Swalk);
	else
		fprintf(stderr,"Stack was null\n");
}

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
#endif
Symtab * SymbolTable::createTree(int Stacksize){
	Symtab *temp;
	int a;
	temp = (Symtab*) malloc(sizeof(Symtab));
	temp->actualStacksize=1;
	temp->Stacksize = Stacksize;
	temp->Stack = (TableEntry**) malloc((sizeof(TableEntry*) * temp->Stacksize));
	for(a=0;a<temp->Stacksize;a++) temp->Stack[a]=NULL;
	return temp;
}

void SymbolTable::deleteTree(Symtab *symtab){
	TableEntry * temp;
	//TableEntry ** found;
	if(symtab != NULL){
	   #ifdef DEBUG
	   fprintf(stderr,"Deleting Tree: \n");
	   #endif
	    while(symtab->actualStacksize != 1)
		closescope(symtab);
	    if((symtab->Stack[symtab->actualStacksize-1]) !=NULL){
                        while(symtab->Stack[symtab->actualStacksize-1] != NULL){
                                temp = *((TableEntry**)(symtab->Stack[symtab->actualStacksize-1] ));
                                tdelete((void*)temp,(void **) &(symtab->Stack[symtab->actualStacksize-1]), Ecmp);
                                deleteTableEntry(temp);

                        }
                        symtab->Stack[symtab->actualStacksize-1]=NULL;
            }
	    #ifdef DEBUG
	    fprintf(stderr,"Deleting Stack\n");
	    #endif
	    free(symtab->Stack);
	    #ifdef DEBUG
	    fprintf(stderr,"Deleting Symbol Table\n");
	    #endif
	    free(symtab);
	    symtab=NULL;
	}
}
void SymbolTable::deleteTableEntry(TableEntry * temp){
	if(temp != NULL){
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
						temp=NULL;
						break;
			case(VAR):
						#ifdef DEBUG
						fprintf(stderr,"Deleting variable %s\n", temp->name);
						#endif
						free(temp->name);
						free(temp->binding);
						free(temp);
						temp=NULL;
						break;
			case(PARAM):
						#ifdef DEBUG
						fprintf(stderr,"Deleteing Parameter %s\n", temp->name);
						#endif
						free(temp->name);
						free(temp->binding);
						free(temp);
						temp= NULL;
						break;
			default:	
						#ifdef DEBUG	
						fprintf(stderr,"Error in Node, doesn't have correct binding\n");
						#endif
						;
		}
	}

}


TableEntry* SymbolTable::createFunc(char * name, type returntype, ListP* paramlist){
	TableEntry * temp;
	listnodeP * tempP;
	int a;
	bool elip=FALSE;
	temp = (TableEntry*) malloc(sizeof(TableEntry));
	if(name !=NULL){
		temp->name = (char*)strdup(((const char*)name));
		temp->self = FUNC;
		//Funcb * tBinding = (Funcb*)temp->binding;
        Funcb * tBinding = NULL;
		//((Funcb*)(temp->binding)) = (Funcb*) malloc(sizeof(Funcb));
		//((Funcb*)(temp->binding))->returntype = returntype;
		tBinding = (Funcb*) malloc(sizeof(Funcb));
		tBinding->returntype = returntype;
        tBinding->num_param = 0;
        tBinding->bodydef = FALSE;
        tBinding->label = 0;
        tBinding->localcount=0;
        tBinding->actual_num=0;
        tBinding->param_type=NULL;
        temp->binding = tBinding;

        if(paramlist!=NULL ){
            #ifdef DEBUG
            fprintf(stderr,"in Function install- temp->binding->num_param is: %d\n", ((Funcb*)(temp->binding))->num_param);
            #endif
            Funcb * extraBind = (Funcb*)(temp->binding);
            #ifdef DEBUG
            fprintf(stderr,"in Function install- extraBind->num_param is: %d\n", extraBind->num_param);
            #endif
			((Funcb*)(temp->binding))->num_param = paramlist->listsize;
        }
/*		else
			((Funcb*)(temp->binding))->num_param=0;
*/
		if(((Funcb*)(temp->binding))->num_param >0){
			((Funcb*)(temp->binding))->param_type = (type*)malloc((sizeof(type) * paramlist->listsize));
			tempP = paramlist->list;
			for(a=0;a<paramlist->listsize;a++){
				((Funcb*)(temp->binding))->param_type[a] = tempP->ttype;
				#ifdef DEBUG
				fprintf(stderr,"in Function install type is %d\n",tempP->ttype);
				#endif
				if( strcmp("...", tempP->val)==0)
					elip = TRUE;
				else
					elip=FALSE;

				tempP = (listnodeP*) tempP->nextnode;

			}
			if(elip == TRUE) {
				((Funcb*)(temp->binding))->actual_num= ((Funcb*)(temp->binding))->num_param;
				((Funcb*)(temp->binding))->num_param = -1;
			}
		}
/*		else
			((Funcb*)(temp->binding))->param_type = NULL;
 */
//		((Funcb*)(temp->binding))->bodydef = FALSE;
//		((Funcb*)(temp->binding))->label=0;
		return temp;
	}
	else{
		error("name not found\n","");
		return NULL;
	}
}

TableEntry* SymbolTable::createVar(char * name, type t_type, int offset){
	TableEntry * temp;
	temp = (TableEntry*) malloc(sizeof(TableEntry));
	temp->name = (char*)strdup(((const char *)name));
	temp->self = VAR;
	//Varb * tBindingV = (Varb *)temp->binding;
    Varb * tBindingV = NULL;
	//((Varb*)(temp->binding)) = (Varb*) malloc(sizeof(Varb));
	tBindingV = (Varb*) malloc(sizeof(Varb));
    tBindingV->type = t_type;

	//((Varb*)(temp->binding))->type = t_type;
	#ifdef DEBUG
	fprintf(stderr,"in Var install type is :%d\n",t_type);
	#endif
    //((Varb*)(temp->binding))->offset = offset;
	tBindingV->offset = offset;
    temp->binding = tBindingV;
	return temp;
}

TableEntry* SymbolTable::createParam(char * name, type t_type, int offset){
	TableEntry * temp;
	temp = (TableEntry*) malloc(sizeof(TableEntry));
	temp->name = (char*)strdup(((const char*)name));
	temp->self = PARAM;
    temp->binding = NULL;
    Paramb * tBindingP = NULL;
	//((Paramb*)(temp->binding)) = (Paramb*) malloc(sizeof(Varb));
	//((Paramb*)(temp->binding))->type = t_type;
	tBindingP = (Paramb*) malloc(sizeof(Paramb));
	tBindingP->type = t_type;
    tBindingP->offset = offset;
    temp->binding = tBindingP;
	#ifdef DEBUG
	fprintf(stderr,"in Param install type is :%d\n",t_type);
	#endif
	//((Paramb*)(temp->binding))->offset = offset;
	return temp;
}

void SymbolTable::addtosymtab(Symtab *mysymtab, type mytype, List * myList){
	int a;
	listnode * tempN;
	TableEntry * temp;
	if(mysymtab !=NULL){
		if(myList !=NULL){
			tempN = (listnode*)(myList->list);
			for(a=1;a<=myList->listsize;a++){
				temp= createVar(tempN->val, mytype, offset_counter);
				offset_counter++;
				if((mysymtab->actualStacksize-1) == 0){
					globalcount++;
				}
				install(temp,mysymtab);
				tempN = (listnode*)tempN->nextnode;
			}
			deleteList(myList);
		}
		else error("myList was NULL","");
	}
	else error("mysymtab was NULL","");
}

TableEntry * SymbolTable::lookupB(const char * name, Symtab *symtab){
	TableEntry ** found;
    found = NULL;
	TableEntry *temp;
	int a;
	if(name != NULL){
		temp = (TableEntry*) malloc(sizeof(TableEntry));
		temp->name = (char *)name;
		#ifdef DEBUG
		fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
		#endif

		for(a=symtab->actualStacksize-1;a>=0;a--){
			#ifdef DEBUG
			fprintf(stderr, "still in for loop\n");
			#endif
			
			if(symtab->Stack[0] != NULL || symtab->Stack[a] != NULL)
				found = (TableEntry**) tfind((void*) temp, (void**) &(symtab->Stack[a]),Ecmp);
			if(found != NULL){
				if(*found !=NULL) break;
			}
		}
		if(found != NULL){
			if(*found ==NULL){
				free(temp->name);
				free(temp);
				return NULL;
			}
			else{
				free(temp);
				return *found;
			}
		}
		else{
			//free(temp->name);
		    temp->name = NULL;
			free(temp);
		    temp = NULL;
			return NULL;
		}

	}
    return NULL;
}

bool SymbolTable::inCscope(const char *name, Symtab *symtab){
        TableEntry ** found;
	   found = NULL;
        TableEntry *temp;
        int a;
        if(name != NULL){
                temp = (TableEntry*) malloc(sizeof(TableEntry));
                temp->name = (char *)name;
                a=symtab->actualStacksize-1;
			 if(symtab->Stack[0] != NULL || symtab->Stack[a] != NULL)
                	found = (TableEntry**) tfind((void*) temp, (void**) &(symtab->Stack[a]),Ecmp);
                if(found != NULL){
                        if(*found ==NULL){
                        //        free(temp->name);
								temp->name = NULL;
                                free(temp);
								temp = NULL;
                                return FALSE;
                        }
                        else{
								#ifdef DEBUG
								fprintf(stderr, "symtab->actualStacksize %d and symtab->actualStacksize - 1 : %d, and symtab->Stacksize: %d\n",symtab->actualStacksize, symtab->actualStacksize-1, symtab->Stacksize);
								fprintf(stderr,"in current scope is TRUE\n");
								#endif
                                free(temp);
								temp = NULL;
                                return TRUE;
                        }
                }
                else{
                       // free(temp->name);
						temp->name = NULL;
                        free(temp);
						temp = NULL;
                        return FALSE;
                }

        }
    return FALSE;
}

int SymbolTable::getleveldif(char *name, Symtab *symtab){
	        TableEntry ** found;
            found = NULL;
	        TableEntry *temp;
	        int a;
	if(name !=NULL && symtab!=NULL){
	        if(name != NULL){
	                temp = (TableEntry*) malloc(sizeof(TableEntry));
	                temp->name = (char *)name;
	                for(a=symtab->actualStacksize-1;a>=0;a--){
					 	if(symtab->Stack[0] != NULL || symtab->Stack[a] !=NULL)
	                        		found = (TableEntry**) tfind((void*) temp, (void**) &(symtab->Stack[a]),Ecmp);
	                        if(found != NULL){
	                                if(*found !=NULL) break;
	                        }
	                }
	                if(found != NULL){
	                        if(*found ==NULL){
	                              //  free(temp->name);
								temp->name = NULL;
	                                free(temp);
									temp = NULL;
	                                return -1;
	                        }
	                        else{
	                                free(temp);
									temp = NULL;
	                                return ((symtab->actualStacksize)-1)-a;
//					return symtab->actualStacksize-a;
	                        }
	                }
	                else{
	                     //   free(temp->name);
						temp->name = NULL;
	                        free(temp);
							temp = NULL;
	                        return -1;
	                }

	        }

	}
	else return -1;
    return -1;
}
