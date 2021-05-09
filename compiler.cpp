#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "compiler.hpp"
#include "ucc.tab.hpp"

using namespace ucc;
namespace ucc{

Compiler::Compiler(): mysymtab{new SymbolTable{ *this} }, 
							code_generator{},
							lexer{NULL,*this},
							parser{nullptr},
							founderror{false}
{
	Line_Number=1;
	globalcount=0;
	offset_counter=5;
	othercounter=1;
	param_offset=0;
	mainlocal=0;
	mainlabel = code_generator.getlabel();

	if(mysymtab == NULL){
		error("Unable to construct symbol table","");
	}
}

Compiler::Compiler(int argc, const char** argv) : 	mysymtab{new SymbolTable{ *this} }, 
																	code_generator{}, 
																	founderror{false}, 
																	lexer{NULL,*this}, 
																	parser{nullptr},
																	Line_Number(1),
																	globalcount(0),
																	offset_counter(5),
																	othercounter(1),
																	param_offset(0),
																	mainlocal(0)
{
	mainlabel = code_generator.getlabel();

	if(mysymtab == NULL){
		error("Unable to construct symbol table","");
	}
	checkargs(argc,argv);
}

Compiler::~Compiler(){
	if(outfile->good()){

		#ifdef DEBUG
		std::cerr << "Closing file\n";
		#endif

		outfile->flush();
	}

	if(mysymtab != NULL){
		delete mysymtab;
		mysymtab = NULL;
	}
}
int Compiler::warning(const std::string s1, const std::string s2) noexcept
{
	std::cerr << "Warning:::"<< filename << ":"<< Line_Number << "-> " << s1 << " " << s2 << "\n";
    return 0;
}

int Compiler::error(const std::string s1, const std::string s2) noexcept {
	std::cerr << "Error:::"<< filename << ":"<< Line_Number << "-> " << s1 << " " << s2 << "\n";
	founderror=true;
	code_generator.stop();
	 return 0;
}


void Compiler::block1_start_trans_unit(){
	code_generator.gen_label("main");
	code_generator.gen_instr_I("enter",0);
	code_generator.gen_instr_I("alloc", globalcount);
	code_generator.gen_instr_I("enter",0);
	code_generator.gen_call(code_generator.genlabelw("main",mainlabel),0);
	code_generator.gen_instr("return");
}
void Compiler::block2_func_funcheader_source(funcheadertype** inFuncHeaderptr){
				funcheadertype* inFuncHeader{*inFuncHeaderptr};
				TableEntry* tempEntry;
				Funcb* tempb;
				//Funcb* found;
				int a;
				List* templist;
                 templist= NULL;
				//type tempparam;
				ListNode* tempnode;
				#ifdef DEBUG
				printTree(mysymtab);
				#endif
				bool stop=false;
				bool alreadyopen=false;
                 tempnode = NULL;
				if("main" == (inFuncHeader->name)){
		                        #ifdef DEBUG
             			        fprintf(stderr,"hello from inside\n");
          				        #endif
					templist = (List*)inFuncHeader->paramlist;
//main function
					if(inFuncHeader->returntype != type::INT)
						error("Main function has to have int as return type","");
					if(templist != NULL && templist->size() != 1)
						error("Main function only has one parameter","");
					else if(inFuncHeader->ttype != type::VOID)
						error("Main function has to have one parameter of void","");
					#ifdef DEBUG							
					fprintf(stderr, "opening up a new scope\n");
					#endif
					mysymtab->openscope();
					 alreadyopen=true;
					code_generator.gen_label(code_generator.genlabelw("main", mainlabel));
				}
				else{
					if((tempb=(Funcb*) mysymtab->lookup(inFuncHeader->name)) ==NULL)
						error("Function name not in symbol table","");
					else{
						TableEntry*tempEn; TableEntry* tempEn2;
						tempEn2 = (TableEntry*) malloc(sizeof(TableEntry));
						tempEn2->setName(inFuncHeader->name);
						tempEn =  mysymtab->lookupB(inFuncHeader->name);
						//tempEn = *(TableEntry**)tfind((void*)tempEn2, (void**) &(SymbolTable::Stack[SymbolTable::actualStacksize -1]),Ecmp);
						if(tempEn!=NULL && tempEn->getself() == btype::FUNC){
							if(tempb->returntype != inFuncHeader->returntype)
								error("Function declared with different return type","");
							else{
								templist= (List*)inFuncHeader->paramlist;
								if(tempb->num_param == -1)
									error("Function cannot have those parameters","");
								else if( templist!=NULL && (templist->size()) != tempb->num_param)
									error("Function has different number of parameters","");
								else{
									if(templist!=NULL){
										tempnode = (ListNode*)templist->getlist();
										for(a=0;a<templist->size() && a<tempb->num_param &&  stop!=true;a++){
											if(tempb->param_type[a] != tempnode->ttype){
												fprintf(stderr,"Error: Line: %d: argument %d: has different parameter type than in function declaration\n",Line_Number,(a+1));
												fprintf(stderr, "\nThey are %d and %d\n", tempb->param_type[a], tempnode->ttype);
												stop=true;
											}
											tempnode = (listnodeP*)tempnode->nextnode;
										}
									}
									if(stop!= true){
										if(tempb->bodydef == true){
											error("Function definition is previously declared","");
										}
										else{
											//tempb->localcount=offset_counter;
											mysymtab->openscope();
											alreadyopen=true;
											if(templist!=NULL){
												tempnode= (listnodeP*)templist->list;
											#ifdef DEBUG
											if(tempnode->ttype != type::VOID){
											    fprintf(stderr,"in funcheader before funcbody, param val and type is ");
			//								    fprintf(stderr,"%s %s\n",tempnode->val,(char*)tempnode->ttype);
											}
											else{
											    fprintf(stderr,"in funcheader before funcbody type is ");
											    fprintf(stderr,"%s\n",(char*)tempnode->ttype);
											}
											#endif
											}
											if(templist!=NULL){
												for(a=0;a<templist->size();a++){
													tempEntry = mysymtab->createParam(tempnode->getval(), tempnode->ttype,(offset_counter));
													mysymtab->install(tempEntry);
													offset_counter++;
													tempnode = (listnodeP*)tempnode->nextnode;
												}
											}
											if(founderror==false){
												//tempb->label=getlabel();
												code_generator.gen_label(code_generator.genlabelw(inFuncHeader->name,tempb->label ));

											}
										}
									}
									else error("Stopped","");

								}
							}
						}
						else
							error("Not a function", "");
						if(tempEn2!=NULL){ free(tempEn2); tempEn2=NULL;}
					currentFunc=tempb; //fprintf(stderr,"createFunc: return type %d\ntempb: return type %d\n",currentFunc->returntype, tempb->returntype);
					}
					if(alreadyopen==false) mysymtab->openscope();
				}
}
void Compiler::block3_func_funcheader_source_funcbody(){
				code_generator.gen_instr("returnf");
//			if(currentFunc == NULL)
//				closemainscope(mysymtab);
//			else
				mysymtab->closescope();
}
void Compiler::block4_func_funcheader_semi(funcheadertype** inFuncHeaderptr){
	funcheadertype* inFuncHeader{*inFuncHeaderptr};
   TableEntry* temp; Funcb* found; int a;
   #ifdef DEBUG
	printTree(mysymtab);
   #endif
   temp =  mysymtab->createFunc(inFuncHeader->name, inFuncHeader->returntype, (List*)(inFuncHeader->paramlist));
   if(inFuncHeader->paramlist !=NULL) delete ((List*)(inFuncHeader->paramlist));
   if(inFuncHeader !=NULL) free(inFuncHeader);
   if( temp->getName() == "main"){
		if( ((Funcb*)(temp->binding))->returntype != type::INT)
			error("Main function needs return type of int","");
		if( ((Funcb*)(temp->binding))->num_param != 1)
			error("Main function only takes 1 parameter","");
		if( ((Funcb*)(temp->binding))->param_type[0] != type::VOID)
			error("Main function parameter has to be void","");
		delete temp;
   }
   else{
	   found = (Funcb*)( mysymtab->lookup(temp->getName()));
          #ifdef DEBUG
		if(temp->name ==NULL)
         	 fprintf(stderr,"FUNCTION: temp before symbol table: %s\n", "NULL");
		 else
         	 fprintf(stderr,"FUNCTION: temp before symbol table: %s\n", temp->name);
		 #endif
          Funcb * paramOftemp = (Funcb*)temp->binding;
          #ifdef DEBUG
          fprintf(stderr,"binding of temp as Funcb: value num_param in symbol table: %d\n", (paramOftemp->num_param));
          fprintf(stderr,"param_type of paramOftemp as typeOftemp: value param_type in symbol table: %d\n", (paramOftemp->param_type[2]));
          #endif
	   if(found == NULL){ mysymtab->install(temp); /*printTree(mysymtab)*/;}
	   else{
		if(((Funcb*)(temp->binding))->returntype != found->returntype)
			error("Function already declared with different return type","");
		if(((Funcb*)(temp->binding))->num_param == -1 || found->num_param == -1){
			if(((Funcb*)(temp->binding))->param_type[0] != found->param_type[0])
				error("In Function %s ", inFuncHeader->name);
				fprintf(stderr,"argument 0 is of different type than in previous declaration\n");
		}
		else{
			if(((Funcb*)(temp->binding))->num_param != found->num_param)
				error("Function already decleared with different number of parameters","");
			if( ((Funcb*)(temp->binding))->num_param > 0 && found->num_param >0){
				for(a=0;a<((Funcb*)(temp->binding))->num_param && a<found->num_param ;a++){
					if(((Funcb*)(temp->binding))->param_type[a] != found->param_type[a]){
						error("In Function %s ", inFuncHeader->name);
						fprintf(stderr, "argument %d is of different type than in previous declaration\n", a);
					}

				}
			}
		}
	   delete temp;
	   }
   }
}
void Compiler::block5_funcheader_error_semi(funcheadertype** inFuncHeaderptr){
	funcheadertype* inFuncHeader{*inFuncHeaderptr};
	if(inFuncHeader !=NULL) if(inFuncHeader->paramlist !=NULL) delete ((List*)(inFuncHeader->paramlist));
	if(inFuncHeader !=NULL) free(inFuncHeader); inFuncHeader = NULL;
}
void Compiler::block6_funcheader_void_ident_lpar_paramdef_rpar(funcheadertype** outFuncHeaderptr,std::string inIdent, List* inParamdeflist){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
	outFuncHeader = (funcheadertype*)malloc(sizeof(funcheadertype));
					outFuncHeader->returntype = type::VOID;
					outFuncHeader->name = inIdent;
                     outFuncHeader->paramlist=NULL;
                     if(inParamdeflist.ttype == type::VOID) outFuncHeader->ttype = type::VOID;
					//(ListP*)($$->paramlist) = $<value.lstpvalue>4;
					List * tempLP = NULL;
					tempLP = inParamdeflist;
                     outFuncHeader->paramlist = tempLP;
}
void Compiler::block7_funcheader_int_ident_lpar_paramdef_rpar(funcheadertype** outFuncHeaderptr,std::string inIdent, List* inParamdeflist){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
	outFuncHeader = (funcheadertype*)malloc(sizeof(funcheadertype));
				outFuncHeader->returntype = type::INT;
				outFuncHeader->name = inIdent;
                  outFuncHeader->paramlist = NULL;
				if(inParamdeflist.ttype == type::VOID) outFuncHeader->ttype = type::VOID;
				//(List*)($$->paramlist) = $<value.lstpvalue>4;
				List* tempLP = NULL;
				tempLP = inParamdeflist;
                  outFuncHeader->paramlist = tempLP;
}
void Compiler::block8_funcheader_float_ident_lpar_paramdef_rpar(funcheadertype** outFuncHeaderptr, std::string inIdent, inParamdeflist){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
	outFuncHeader = (funcheadertype*)malloc(sizeof(funcheadertype));
					outFuncHeader->returntype = type::FLOAT;
					outFuncHeader->name = inIdent;
                     if(inParamdeflist.ttype == type::VOID) outFuncHeader->ttype = type::VOID;
					//(ListP*)($$->paramlist) = $<value.lstpvalue>4;
					List* tempLP = NULL;
					tempLP = inParamdeflist;
                     outFuncHeader->paramlist = tempLP;
}
void Compiler::block9_funcheader_void_error_rpar(funcheadertype** outFuncHeaderptr){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
 List* tempP; yyerrok;
		outFuncHeader =(funcheadertype*) malloc(sizeof(funcheadertype));
		outFuncHeader->name ="";
		outFuncHeader->returntype= type::VOID;
		//(List*)($$->paramlist) = (ListP*) malloc(sizeof(List));
		List* tempLP;
		tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
		tempP= (List*)tempLP;
		outFuncHeader->paramlist= tempLP;
}

void Compiler::block10_funcheader_int_error_rpar(funcheadertype** outFuncHeaderptr){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
 List* tempP; yyerrok;
	outFuncHeader =(funcheadertype*) malloc(sizeof(funcheadertype));
	outFuncHeader->name ="";
	outFuncHeader->returntype= type::INT;
	//(List*)($$->paramlist) = (ListP*) malloc(sizeof(List));
	List* tempLP;
	tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
	tempP= (List*)tempLP;
	outFuncHeader->paramlist= tempLP;
}
void Compiler::block11_funcheader_float_error_rpar(funcheadertype** outFuncHeaderptr){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
 List* tempP; yyerrok;
		outFuncHeader =(funcheadertype*) malloc(sizeof(funcheadertype));
		outFuncHeader->name ="";
		outFuncHeader->returntype= type::FLOAT;
		//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
		List* tempLP;
		tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
		tempP= (List*)tempLP;
		outFuncHeader->paramlist= tempLP;
}

void Compiler::block12_funcheader_void_ident_lpar_error_rpar(funcheadertype** outFuncHeaderptr, std::string inIdent){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
	List* tempP; yyerrok;
	outFuncHeader =(funcheadertype*) malloc(sizeof(funcheadertype));
	outFuncHeader->name = inIdent;
	outFuncHeader->returntype= type::VOID;
	//(Lis*)($$->paramlist) = NULL;
	List* tempLP1 = (List *)outFuncHeader->paramlist;
	tempLP1 = NULL;
	//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
	List* tempLP;
	tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
	tempP= (List*)tempLP;
	outFuncHeader->paramlist= tempLP;
}
void Compiler::block13_funcheader_float_ident_lpar_error_rpar(funcheadertype** outFuncHeaderptr, std::string inIdent){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
 List* tempP; yyerrok;
		outFuncHeader =(funcheadertype*) malloc(sizeof(funcheadertype));
		outFuncHeader->name =inIdent;
		outFuncHeader->returntype= type::FLOAT;
		//(ListP*)($$->paramlist) = NULL;
		List* tempLP1 = (List *)outFuncHeader->paramlist;
		tempLP1 = NULL;
		//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
		List* tempLP;
		tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
		tempP= (List*)tempLP;
		outFuncHeader->paramlist= tempLP;
}
void Compiler::block14_funcheader_int_ident_lpar_error_rpar(funcheadertype** outFuncHeaderptr, std::string inIdent){
	funcheadertype* outFuncHeader{*outFuncHeaderptr};
	List* tempP; yyerrok;
			outFuncHeader = (funcheadertype*)  malloc(sizeof(funcheadertype));
			outFuncHeader->name= inIdent;
			outFuncHeader->returntype= type::INT;
			//(List*)($$->paramlist) = NULL;
			List* tempLP1 = (List *)outFuncHeader->paramlist;
			tempLP1 = NULL;
			//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
			List* tempLP;
			tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
			tempP= (List*)tempLP;
			outFuncHeader->paramlist= tempLP;
}
void Compiler::block15_paramdef_paramdeflist(List** outParamdefptr, List** inParamdeflistptr){
	*outParamdefptr = *inParamdeflistptr;
//	$<value.lstpvalue>$= $1;
}
void Compiler::block15_paramdef_paramdeflist_comma_elip(List** outParamdefptr, List** inParamdeflistptr){

		*outParamdefptr = (*inParamdeflistptr)->appendList("...", type::VOID);
          #ifdef DEBUG
          printListP(*outParamdefptr);
          #endif
}
void Compiler::block16_paramdef_void(List** outParamdefptr){
	(*outParamdefptr) = NULL;
	outParamdefptr->ttype = type::VOID;
}
void Compiler::block17_paramdef_paramdeflist_error_rpar(List** inParamdeflistptr){
	delete (*inParamdeflistptr);
}
void Compiler::block18_paramdef_paramdeflist_comma_error_rpar(List** inParamdeflistptr){
	delete (*inParamdeflistptr);
}
void Compiler::block19_paramdeflist_int_ident(List** outParamdeflistptr, std::string inIdent){
	(*outParamdeflistptr) = List::mklist(inIdent, type::INT);
       #ifdef DEBUG
       printListP((*outParamdeflistptr));
       #endif
}
void Compiler::block20_paramdeflist_float_ident(List** outParamdeflistptr, std::string inIdent){
	(*outParamdeflistptr) = List::mklist(inIdent, type::FLOAT);
       #ifdef DEBUG
       printListP((*outParamdeflistptr));
       #endif
}
void Compiler::block21_paramdeflist_char_star_ident(List** outParamdeflistptr, std::string inIdent){
	(*outParamdeflistptr) = List::mklist(inIdent, type::STR);
       #ifdef DEBUG
       printListP((*outParamdeflistptr));
       #endif
}
void Compiler::block22_paramdeflist_paramdeflist_comma_int_ident(List** outParamdeflistptr, List** inParamdeflistptr, std::string inIdent){
	(*outParamdeflistptr) = (*inParamdeflistptr)->appendList(inIdent,type::INT);
       #ifdef DEBUG
       printListP((*outParamdeflistptr));
       #endif
}
void Compiler::block23_paramdeflist_paramdeflist_comma_float_ident(List** outParamdeflistptr, List** inParamdeflistptr, std::string inIdent){
	(*outParamdeflistptr) = (*intParamdeflistptr)->appendList(inIdent, type::FLOAT);
       #ifdef DEBUG
       printListP((*outParamdeflistptr));
       #endif
}
void Compiler::block24_paramdeflist_paramdeflist_comma_char_star_ident(List** outParamdeflistptr, List** inParamdeflistptr, std::string inIdent){
	(*outParamdeflistptr) = (*inParamdeflistptr)->appendList(inIdent, type::STR);
       #ifdef DEBUG
       printListP((*outParamdeflistptr));
       #endif
}
void Compiler::block25_funcbody_lcbra_decls_source(){

	if(founderror==false){
		mainlocal= offset_counter-5;
		if(currentFunc==NULL)
			code_generator.gen_instr_I("alloc", mainlocal);
		else{
			currentFunc->localcount= offset_counter-5-currentFunc->num_param;
			code_generator.gen_instr_I("alloc",currentFunc->localcount);
		}
	}
}

void Compiler::block26_funcbody_lcbra_decls_source_stmtlist_rcbra(){
	#ifdef DEBUG
	printTree(mysymtab);
	#endif
}

void Compiler::block27_variabledecl_int_identlist_semi(){

 if($<value.lstvalue>2 !=NULL) mysymtab->addtosymtab(type::INT, $<value.lstvalue>2);
				#ifdef DEBUG
					fprintf(stderr,"Found a single Integer declaration or a list of integers being declared\n");
					printTree(mysymtab);
				#endif
}
void Compiler::block28_variabledecl_float_identlist_semi(){
		if($<value.lstvalue>2 !=NULL) 
			mysymtab->addtosymtab(type::FLOAT, $<value.lstvalue>2); }
		#ifdef DEBUG
		printTree(mysymtab);
		#endif
}
void Compiler::block29_stmt_expr_semi(){
		code_generator.gen_instr_I("popI",4);
}
void Compiler::block30_stmt_return_semi(){
	if(currentFunc ==NULL)
		error("main function has to return a value","");
	else{
		if(currentFunc->returntype != type::VOID)
			error("Function has return type that is not void","");
		else{
				code_generator.gen_instr("returnf");
		}
	}
}
void Compiler::block31_stmt_return_expr_semi(){
	if($2->numeric != true)
			error("non numeric expression in return statement or return type is void", "");
		else{
			if(currentFunc ==NULL){
				if($2->type != type::INT)
					warning("main function has int return type","");

					if(founderror==false){
						if($2->lval==true){
							switch($2->type){
								case type::INT:	code_generator.gen_instr("fetchI"); break;
								case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                                   default: break;
							}
						}
						if($2->type != type::INT) code_generator.gen_instr("int");
						code_generator.gen_instr("setrvI");
					}

			}
			else{
				#ifdef DEBUG
				printf("type and returntype : %d: %d\n",$2->type,currentFunc->returntype);
				#endif
				if($2->type != currentFunc->returntype)
					warning("function has different returntype","");

					if(founderror==false){
                                       if($2->lval==true){
                                           switch($2->type){
                                               case type::INT:       code_generator.gen_instr("fetchI"); break;
                                               case type::FLOAT:     code_generator.gen_instr("fetchR"); break;
                                               default:    break;
                                                                       }
                                                               }
						switch(currentFunc->returntype){
							case type::INT:	switch($2->type){
										case type::FLOAT:	code_generator.gen_instr("int");
										case type::INT:	code_generator.gen_instr("setrvI"); break;
                                           default: break;
									}
									break;
							case type::FLOAT:	switch($2->type){
										case type::INT:	code_generator.gen_instr("flt");
										case type::FLOAT:	code_generator.gen_instr("setrvR"); break;
                                           default:    break;
									}
									break;
                               default: break;
						}
                           
						code_generator.gen_instr("returnf");
                                                       }



			}
		}
}
void Compiler::block32_stmt_while_source(){
	if(founderror==false){
		$$.one=  othercounter;
		othercounter++;
		$$.two =  othercounter;
		othercounter++;
		code_generator.gen_label(code_generator.genlabelw("",$$.one));
	}
}
void Compiler::block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(){
	if(founderror==false){
		if($4->numeric==true){
			if($4->lval==true ){
				switch($4->type){
					case type::INT:	code_generator.gen_instr("fetchI"); break;
					case type::FLOAT:	code_generator.gen_instr("fetchR"); code_generator.gen_instr("int"); break;
                     default:    break;
				}
			}
		}
		code_generator.gen_instr_S("jumpz", code_generator.genlabelw("",$2.two));

	}
}
void Compiler::block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt(){
	if($4->numeric !=true)
		error("non numeric expression in while statement","");
	else{
			if($4->type != type::INT)
				error("expression in while statement is not an integer","");
			if(founderror==false){
				code_generator.gen_instr_S("jump", code_generator.genlabelw("",$2.one));
				code_generator.gen_label(code_generator.genlabelw("",$2.two));
			}

	}
}
void Compiler::block35_stmt_ifexprstmt_else(){
	if(founderror==false){
		code_generator.gen_instr_S("jump", code_generator.genlabelw("",$1.two));
		code_generator.gen_label(code_generator.genlabelw("",$1.one));
	}
}

void Compiler::block36_stmt_ifexprstmt_else_source_stmt(){
	if($1.numeric !=true)
			error("non numeric expression in if statement","");
		else{
			if($1.ttype != type::INT)
				error("expression in if statement is not an integer","");
			else{
				if(founderror==false){
					code_generator.gen_label(code_generator.genlabelw("",$1.two));
				}
			}
		}
}

void Compiler::block37_stmt_ifexprstmt(){
	if($1.numeric !=true)
		error("non numeric expression in if statement","");
	else{
		if($1.ttype != type::INT)
			error("expression in if statement is not an integer","");
		else{

			if(founderror==false) code_generator.gen_label(code_generator.genlabelw("",$1.one));
		}
	}
}

struct Pair Compiler::block38_ifexprstmt_if_lpar_expr_source(){
	struct Pair rvalue;
	
	rvalue.one= othercounter;
	othercounter++;
	rvalue.two= othercounter;
	othercounter++;
	if($3->lval==true && $3->numeric==true){
		switch($3->type){
			case type::INT:	code_generator.gen_instr("fetchI"); break;
			case type::FLOAT:	code_generator.gen_instr("fetchR"); code_generator.gen_instr("int"); break;
              default:    break;
		}
	}
	code_generator.gen_instr_S("jumpz", code_generator.genlabelw("",$$.one));
	return rvalue;
}

void Compiler::block39_ifexprstmt_if_lpar_expr_source_rpar_stmt(){
	$$.lval=$3->lval; $$.numeric=$3->numeric; $$.ttype = $3->type; $$.one = $4.one; $$.two=$4.two;
}

void Compiler::block40_expr_equalexpr_equal_equalexpr(){
	if($1.lval !=true){
		error("Cannot make assignment. Left hand side is not a correct lval","");
	}
	else if($3.numeric !=true){
		error("Cannot make assignment, Right hand side is not numeric.","");
	}
	else {
		if(founderror==false){
			if($3.lval==true){
				switch($3.ttype){
					case type::INT:	code_generator.gen_instr("fetchI"); break;
					case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                        default:    break;
				}
			}
		}
		if(($1.ttype== type::INT && $3.ttype == type::INT) || ($1.ttype == type::FLOAT && $3.ttype== type::FLOAT)) {
			$$ = (exprtype*) malloc(sizeof(exprtype));
			if(founderror==false){
				switch($1.ttype){
					case(type::INT): $$->type= type::INT; code_generator.gen_instr("storeI"); break;
					case(type::FLOAT): $$->type= type::FLOAT; code_generator.gen_instr("storeR"); break;
                        default:    break;
				}
			}
			$$->lval = true;
			$$->numeric =true;

		}
		else if($1.ttype == type::INT && $3.ttype== type::FLOAT){
			warning("expressons are of different type, data may be lost","");
			$$ = (exprtype*) malloc(sizeof(exprtype));
			$$->type = type::INT;
			$$->lval=true;
			$$->numeric=true;
			if(founderror==false){
				code_generator.gen_instr("int");
				code_generator.gen_instr("storeI");
			}
		}
		else if($1.ttype == type::FLOAT && $3.ttype == type::INT) {
			warning("expression are of different type, data may be lost","");
			$$ = (exprtype*) malloc(sizeof(exprtype));
			$$->type= type::FLOAT;
			$$->numeric=true;
			$$->lval=true;
			if(founderror==false){
				code_generator.gen_instr("flt");
				code_generator.gen_instr("storeR");
			}
		}

	}
}

void Compiler::block41_expr_equalexpr(){
	$$ = (exprtype*) malloc(sizeof(exprtype));
	$$->lval = $1.lval; $$->numeric = $1.numeric; $$->type =$1.ttype;
}


void Compiler::block42_equalexpr_relexpr_eqop_source(){
	if(founderror==false){
		if($1.numeric==true){
			switch($1.ttype){
				case type::INT:	if($1.lval==true) code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($1.lval==true) code_generator.gen_instr("fetchR"); break;
                 default:    break;
			}
		}
	}
}

void Compiler::block43_equalexpr_relexpr_eqop_source_relexpr(){
	if(founderror==false){
		if($4.numeric==true){
			switch($4.ttype){
				case type::INT:	if($4.lval==true) code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($4.lval==true) code_generator.gen_instr("fetchR"); break;
                 default:    break;
			}
		}
	}
				$$.lval = false;
				if($1.numeric==true && $4.numeric==true){
					$$.numeric = true;
					$$.ttype= type::INT;
					if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype= type::INT;
						if(founderror==false){
                                                                     switch($<value.eqopvalue>2){
                                                                             case eqtype::NEQ:       if($1.ttype== type::INT) code_generator.gen_instr("neI");
                                                                                             else if($1.ttype== type::FLOAT) code_generator.gen_instr("neR");
                                                                                             break;
                                                                             case eqtype::EQEQ:      if($1.ttype== type::INT) code_generator.gen_instr("eqI");
                                                                                             else if($1.ttype== type::FLOAT) code_generator.gen_instr("eqR");
                                                                                             break;
                                                                             default:    break;
                                                                     }
                                                     }

					}
					else if($1.ttype == type::INT && $4.ttype== type::FLOAT){
						warning("expressons are of different type, data may be lost","");
						$$.ttype = type::INT;
							if(founderror==false){
                                                                     switch($<value.eqopvalue>2){
                                                                             case eqtype::NEQ:       code_generator.gen_instr("fltb");
                                                                                             code_generator.gen_instr("neR");
                                                                                             break;
                                                                             case eqtype::EQEQ:       code_generator.gen_instr("fltb");
                                                                                             code_generator.gen_instr("eqR");
                                                                                             break;
                                                                             default:    break;
                                                                     }
                                                             }

					}
					else if($1.ttype == type::FLOAT && $4.ttype == type::INT) {
						 warning("expression are of different type, data may be lost","");
						$$.ttype= type::INT;
						if(founderror==false){
                                                                     switch($<value.eqopvalue>2){
                                                                             case eqtype::NEQ:       code_generator.gen_instr("flt");
                                                                                             code_generator.gen_instr("neR");
                                                                                             break;
                                                                             case eqtype::EQEQ:       code_generator.gen_instr("flt");
                                                                                             code_generator.gen_instr("eqR");
                                                                                             break;
                                                                             default:    break;
                                                                     }
                                                      }
					}
				}
				else{ error("non numeric in operation",""); $$.numeric=true; }
}

void Compiler::block44_equalexpr_relexpr(){
$$.lval = $1.lval; $$.ttype = $1.ttype; $$.numeric= $1.numeric;
}

void Compiler::block45_relexpr_simpleexpr_relop_source(){
	if(founderror==false){
		if($1.numeric==true){
			switch($1.ttype){
				case type::INT:	if($1.lval==true) code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($1.lval==true) code_generator.gen_instr("fetchR"); break;
                 default:    break;
             }
		}
	}
}

void Compiler::block46_relexpr_simpleexpr_relop_source_simpleexpr(){
	if(founderror==false){
		if($4.numeric==true){
			switch($4.ttype){
				case type::INT:	if($4.lval==true) code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($4.lval==true) code_generator.gen_instr("fetchR"); break;
                  default:    break;
			}
		}
	}
				$$.lval = false;
				if($1.numeric == true && $4.numeric ==true){
					$$.numeric=true;
					$$.ttype= type::INT;
					if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype= type::INT;
						if(founderror==false){
							switch($<value.relopvalue>2){
                                  case reltype::LES:       if($1.ttype== type::INT) code_generator.gen_instr("ltI");
                                                          else if($1.ttype== type::FLOAT) code_generator.gen_instr("ltR");
                                                                      break;
                                  case reltype::LEQ:       if($1.ttype== type::INT) code_generator.gen_instr("leI");
                                                          else if($1.ttype== type::FLOAT) code_generator.gen_instr("leR");
                                                                      break;
								case reltype::GRE:	if($1.ttype== type::INT) code_generator.gen_instr("gtI");
										else if($1.ttype== type::FLOAT) code_generator.gen_instr("gtR");
										break;
								case reltype::GEQ:	if($1.ttype== type::INT) code_generator.gen_instr("geI");
										else if($1.ttype== type::FLOAT) code_generator.gen_instr("geR");
										break;
                                  default:    break;
                                                                  }
						}

					}
					else if($1.ttype == type::INT && $4.ttype== type::FLOAT){
						warning("expressons are of different type, data may be lost","");
						$$.ttype = type::INT;
						if( founderror==false){
                                          switch($<value.relopvalue>2){
                                                  case reltype::LES:       code_generator.gen_instr("fltb");
										code_generator.gen_instr("ltR");
                                                                                          break;
                                                  case reltype::LEQ:       code_generator.gen_instr("fltb");
										code_generator.gen_instr("leR");
                                                                                          break;
                                                  case reltype::GRE:       code_generator.gen_instr("fltb");
										code_generator.gen_instr("gtR");
                                                                                          break;
                                                  case reltype::GEQ:       code_generator.gen_instr("fltb");
										code_generator.gen_instr("geR");
                                                                                          break;
                                                  default:    break;
                                                                  }
                                                          }
					}
					else if($1.ttype == type::FLOAT && $4.ttype == type::INT) {
						warning("expression are of different type, data may be lost","");
						$$.ttype = type::INT;
						if( founderror==false){
                                                                  switch($<value.relopvalue>2){
                                                                          case reltype::LES:       code_generator.gen_instr("flt");
                                                                                          code_generator.gen_instr("ltR");
                                                                                          break;
                                                                          case reltype::LEQ:       code_generator.gen_instr("flt");
                                                                                          code_generator.gen_instr("leR");
                                                                                          break;
                                                                          case reltype::GRE:       code_generator.gen_instr("flt");
                                                                                          code_generator.gen_instr("gtR");
                                                                                          break;
                                                                          case reltype::GEQ:       code_generator.gen_instr("flt");
                                                                                          code_generator.gen_instr("geR");
                                                                                          break;
                                                                          default:     break;
                                                                  }
                                                          }
					}

				}
				else{
					error("non numeric in operation","");
					$$.numeric=false;
				}
}

void Compiler::block47_relexpr_simpleexpr(){
		$$.lval = $1.lval; $$.ttype = $1.ttype; $$.numeric=$1.numeric;
}

void Compiler::block48_simpleexpr_simpleexpr_addop_source(){
	if(founderror==false){
                     if($1.numeric==true){
                             switch($1.ttype){
                                     case type::INT:       if($1.lval==true) code_generator.gen_instr("fetchI"); break;
                                     case type::FLOAT:     if($1.lval==true) code_generator.gen_instr("fetchR"); break;
                                     default:        break;
                             }
                     }
             }

}

void Compiler::block49_simpleexpr_simpleexpr_addop_source_term(){
	if(founderror==false){
                          if($4.numeric ==true){
                                  switch($4.ttype){
                                          case type::INT:       if($4.lval==true) code_generator.gen_instr("fetchI"); break;
                                          case type::FLOAT:     if($4.lval==true) code_generator.gen_instr("fetchR"); break;
                                          default:        break;
                                  }
                          }
                  }
				$$.lval = false;
				if($1.numeric == true && $4.numeric==true){
					$$.numeric=true;
					if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype=$1.ttype;
						if(founderror==false){
  		                                                switch($<value.addopvalue>2){
          		                                                case addtype::PLS:       if($1.ttype== type::INT) code_generator.gen_instr("addI");
                  		                                                        else if($1.ttype== type::FLOAT) code_generator.gen_instr("addR");
                          		                                                break;
                                  		                        case addtype::MIN:       if($1.ttype== type::INT) code_generator.gen_instr("subI");
                                          		                                else if($1.ttype== type::FLOAT) code_generator.gen_instr("subR");
                                                  		                        break;
                                                                  default:        break;
                     	                       		      	}
                             	            	}
					}
					else if($1.ttype ==type::INT && $4.ttype== type::FLOAT){ warning("expressons are of different type, data may be lost","");
						$$.ttype = type::FLOAT;
                                                if( founderror==false){
                                                        switch($<value.addopvalue>2){
                                                                case addtype::PLS:       code_generator.gen_instr("fltb");
                                                                                code_generator.gen_instr("addR");
                                                                                break;
                                                                case addtype::MIN:       code_generator.gen_instr("fltb");
                                                                                code_generator.gen_instr("subR");
                                                                                break;
                                                                  default:        break;
                                                        }
                                                }
					}
					else if($1.ttype == type::FLOAT && $4.ttype == type::INT) { warning("expression are of different type, data may be lost","");
						$$.ttype = type::FLOAT;
                  		                        if( founderror==false){
                  		                                switch($<value.addopvalue>2){
                  		                                        case addtype::PLS:       code_generator.gen_instr("flt");
                  		                                                        code_generator.gen_instr("addR");
                  		                                                        break;
                  		                                        case addtype::MIN:       code_generator.gen_instr("flt");
                  		                                                        code_generator.gen_instr("subR");
          		                                                                break;
                                                                  default:                break;
          		                                        }
                                                }
					}
				}
				else{
					error("non numeric in operation","");
					$$.numeric=false;
				}

}

void Compiler::block50_simpleepr_term(){
	$$.lval = $1.lval; $$.ttype = $1.ttype; $$.numeric = $1.numeric; 
}

void Compiler::block51_term_term_mulop_source(ReturnPacket** outPacket, ReturnPacket** inPacket){
	if((*inPacket)->getnumeric() && (*inPacket)->getlval()){
		switch((*inPacket)->gettype()){
			case type::INT:
				code_generator.gen_instr("fetchI"); 
				break;
			case type::FLOAT:
				code_generator.gen_instr("fetchR"); 
				break;
			default:
				break;
		}
	}
}

void Compiler::block52_term_term_mulop_source_factor(){
	if(founderror==false){
		if($4.numeric ==true){
			switch($4.ttype){
				case type::INT:	if($4.lval==true) code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($4.lval==true) code_generator.gen_instr("fetchR"); break;
                  default:    break;
			}
		}
	}
		$$.lval = false;
		if($1.numeric ==true && $4.numeric ==true){
			$$.numeric =true;
			if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype = $1.ttype;
				if(founderror==false){
					switch($<value.multopvalue>2){
						case multype::DIV:	if($1.ttype== type::INT) code_generator.gen_instr("divI");
								else if($1.ttype== type::FLOAT) code_generator.gen_instr("divR");
								break;
						case multype::MULT:	if($1.ttype== type::INT) code_generator.gen_instr("mulI");
								else if($1.ttype== type::FLOAT) code_generator.gen_instr("mulR");
								break;
                                  default:    break;
					}
				}
			}
			else if($1.ttype == type::INT && $4.ttype== type::FLOAT){
				warning("expressons are of different type, data may be lost","");
				$$.ttype = type::FLOAT;
				if(founderror==false){
					switch($<value.multopvalue>2){
  	                                                case multype::DIV:       code_generator.gen_instr("fltb");
								code_generator.gen_instr("divR");
                  	                                                break;
                          	                        case multype::MULT:      code_generator.gen_instr("fltb");
								code_generator.gen_instr("mulR");
                                          	                        break;
                                                      default:    break;
                                             }
				}
			}
			else if($1.ttype == type::FLOAT && $4.ttype == type::INT) {
				warning("expression are of different type, data may be lost","");
				$$.ttype = type::FLOAT;
				if(founderror==false){
					switch($<value.multopvalue>2){
  	                                                case multype::DIV:       code_generator.gen_instr("flt");
          	                                                        code_generator.gen_instr("divR");
                  	                                                break;
                          	                        case multype::MULT:      code_generator.gen_instr("flt");
                                  	                                code_generator.gen_instr("mulR");
                                          	                        break;
                                                      default:            break;
                                             }
				}
			}

		}
		else{
			error("non numeric in operation","");
			$$.numeric =false;
		}
}

void Compiler::block53_term_factor(){
	$$.lval = $1.lval; $$.ttype = $1.ttype; $$ = $1; $$.numeric=$1.numeric;
}

void Compiler::block54_factor_constant(ReturnPacket** outPacket, Constant** inConstant){

	(*outPacket) = (*inConstant;
//	(*outPacket)->setlval(false); 

	switch((*outPacket)->gettype()){
		case type::INT:
			code_generator.gen_instr_I("pushcI",dynamic_cast<IntConstant*>(*inConstant).getvalue());
			break;
		case type::FLOAT:
			code_generator.gen_instr_F("pushcR",dynamic_cast<FloatConstant*>(*inConstant).getvalue());
			break;
		case type::STR:
			code_generator.gen_instr_S("pushs",dynamic_cast<StrConstant*>(*inConstant).getvalue()));
			break;
		default:
			error("constant is not a correct type of constant","");
			break;
		}
}

void Compiler::block55_factor_ident(ReturnPacket** outPacket, std::string inIdent){
	TableEntry *resultLookup;
	TableEntry *tempE2; 
	(*outPacket) = new Identifier{inIdent};
//	(*outPacket) = (*inIdent);
//	$<value.svalue>$ = $1;
		if(inIdent != "main"){
				#ifdef DEBUG
				fprintf(stderr,"the name of the identifier here is:  %s\n", (char*)$<value.svalue>1);
				#endif
				
			if(( (resultLookup =  mysymtab->lookupB(inIdent)) != nullptr ){
				(*outPacket)->settype(resultLookup->binding->gettype());
				(*outPacket)->setlval(true);
				if(resultLookup->binding->gettype() == type::INT || resultLookup->binding->gettype() == type::FLOAT){
					 (*outPacket)->setnumeric(true);
				 }
				if(mysymtab->inCscope(inIdent)){
					code_generator.gen_instr_I("pusha", resultLookup->binding->getoffset());
				}
				else{
					switch(resultLookup->self){
						case btype::VAR:

							#ifdef DEBUG
							char temp_char = (char)(*outPacket)->gettype();
							if((*outPacket)->gettype() !=  nullptr) fprintf(stderr,"type is: %s\n", &temp_char);
							if(resultLookup->binding->gettype() != nullptr) fprintf(stderr,"type is: %d\n", resultLookup->binding->gettype());
							#endif

							code_generator.gen_instr_tI("pushga",mysymtab->getleveldif(inIdent,resultLookup->binding->getoffset());
							break;

						case btype::PARAM:
							#ifdef DEBUG
							fprintf(stderr,"type is: %d\n", (int)(*outPacket)->getttype());
							#endif

							break;
						default:
							error("Variable is unknown or undelcared","");
							break;
					}
				}
			}
			else{
				(*outPacket)->settype(type::VOID);
				error("Variable is unknown or undelcared, couldn't be found in symbol table'","");
			}
		}
		else{
			error("Main is not a variable name","");
		}
}

void Compiler::block56_factor_lpar_expr_rpar(ReturnPacket** outPacket, ReturnPacket** inPacket){
	(*outPacket) = (*inPacket);
}

void Compiler::block57_factor_addop_factor_uminus(){
	if(founderror==false){
		if($2.numeric==true){
			if($1 == addtype::MIN){
				if($2.lval ==true){
					switch($2.ttype){
						case type::INT:	code_generator.gen_instr("fetchI"); break;
						case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                           default:    break;
					}
				}
				switch($2.ttype){
					case type::INT:	code_generator.gen_instr("negI"); break;
					case type::FLOAT:	code_generator.gen_instr("negR"); break;
                       default:    break;
				}
			}
			else if($1 == addtype::PLS){
				if($2.lval == true){
					switch($2.ttype){
						case type::INT:	code_generator.gen_instr("fetchI"); break;
						case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                           default:    break;
					}
				}
			}
		}
	}
			(*outPacket)->lval = false;
			(*outPacket)->ttype = $2.ttype;
			if($2.numeric ==true) (*outPacket)->numeric=true;
			else
				error("cannot change sign of non numeric expression","");
}

void Compiler::block58_factor_adof_ident(){
	TableEntry*tempE, *tempE2; $<value.svalue>$ = $2;
                       if($<value.svalue>2 != "main"){
                               if( mysymtab->lookup($<value.svalue>2) == NULL)
							error("variable undeclared, please declare variables before using them","");
                               else{
                                       tempE2 = (TableEntry*) malloc(sizeof(TableEntry));
                                       tempE2->name = $<value.svalue>2;
               if((tempE=  mysymtab->lookupB($<value.svalue>2)) !=NULL){

                   if(tempE->self == btype::VAR || tempE->self == btype::PARAM){
                       switch(tempE->self){
                           case btype::VAR:
                               (*outPacket)->ttype = ((Varb*)(tempE->binding))->type;
                               #ifdef DEBUG
                               fprintf(stderr,"type is: %d\n", (int)(*outPacket)->ttype);
                               #endif
                               (*outPacket)->lval = false;
                               if(((Varb*)(tempE->binding))->type == type::INT || ((Varb*)(tempE->binding))->type == type::FLOAT)
                                   (*outPacket)->numeric=true;
							if(founderror==false){
                                   if(mysymtab->inCscope($<value.svalue>2) == true)
                                       code_generator.gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
                                   else{
                                       code_generator.gen_instr_tI("pushga",mysymtab->getleveldif($<value.svalue>2),((Varb*)(tempE->binding))->offset);
                           //do something else

                                   }
                               }
                               break;
                           case btype::PARAM:
                               (*outPacket)->ttype = ((Paramb*)(tempE->binding))->type;
                               #ifdef DEBUG
                               fprintf(stderr,"type is: %d\n", (int)(*outPacket)->ttype);
                               #endif
                               (*outPacket)->lval = false;
                               if(((Paramb*)(tempE->binding))->type == type::INT || ((Paramb*)(tempE->binding))->type == type::FLOAT)
                                   (*outPacket)->numeric=true;
                               if(founderror==false){
                                   if(mysymtab->inCscope($<value.svalue>2) ==true){
                                       code_generator.gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
                                   }
                                   else{
                       //do something else
                                   }
                               }
                               break;
                           default:            break;
                       }
                                               }
                                               else
					error("Variable is unknown or undelcared", "");
                                       }
                                       else{
                                               (*outPacket)->lval=false;
                                               (*outPacket)->numeric=false;
                                               (*outPacket)->ttype= type::VOID;
                                               error("Variable is unknown or undelcared","");
                                       }
                               }
                       }
                       else{
                               error("Main is not a variable name", "");
                                       //tempE2 = (TableEntry*) malloc(sizeof(TableEntry));
                                       //tempE2->name = (char*) $<value.svalue>1;

                       }
}

void Compiler::block59_factor_function_call(){
	(*outPacket)->ttype = $1.ttype; (*outPacket)->lval = false; (*outPacket)->numeric=$1.numeric; 
}

void Compiler::block60_function_call_ident_lpar_rpar(){
	(*outPacket)->lval = false; Funcb* tempb; TableEntry* tempE; TableEntry*tempE2;
                                if((tempb=(Funcb*) mysymtab->lookup($<value.svalue>1)) == NULL){
                                        error("function undeclared, please declare functions before using them","");
				}
                                else{
                                        tempE2 = (TableEntry*) malloc(sizeof(TableEntry));
                                        tempE2->name = $<value.svalue>1;
                                        if((tempE=  mysymtab,lookupB($<value.svalue>1))!=NULL){
                                                if(tempE->self == btype::FUNC){
							if(tempb->returntype != type::VOID) (*outPacket)->lval =true; else (*outPacket)->lval=false;
                                                        if(tempb->num_param != 0)
                                                                error("Function call without correct number of parameters if any","");
                                                        (*outPacket)->ttype = tempb->returntype;
                                                        if((*outPacket)->ttype == type::INT || (*outPacket)->ttype == type::FLOAT) (*outPacket)->numeric =true; else (*outPacket)->numeric =false;
							if(founderror==false){
								code_generator.gen_instr_I("enter",1);
								code_generator.gen_call(code_generator.genlabelw($<value.svalue>1, tempb->label), 0);
							}
                                                }
                                                else
                                                        error("Function call with an unknown function name", "");
                                        }
                                        else
                                                error("fuction undeclared","");
                                        free(tempE2); tempE2=NULL;
                                }
}

void Compiler::block61_function_call_func_call_with_params(){
	(*outPacket)->ttype =$1.ttype; (*outPacket)->numeric = $1.numeric; (*outPacket)->lval = $1.lval;
}

void Compiler::block62_func_call_with_params_name_and_params_rpar(){
	(*outPacket)->numeric =$1.numeric; (*outPacket)->lval = false; (*outPacket)->ttype = $1.ttype;
				if($1.funcent!=NULL){
						if(($1.funcent)->self == btype::FUNC){
							if( ((Funcb*)(($1.funcent)->binding))->returntype != type::VOID) (*outPacket)->numeric = true; else (*outPacket)->numeric=false;
						}
						if(founderror==false){
							if( "scanf" == $1.funcent->name){
//								code_generator.gen_call("$scanf",((Funcb*)($1.funcent->binding))->actual_num);
								code_generator.gen_call("$scanf",$1.params);
							}
							else if("printf" ==  $1.funcent->name){
//								code_generator.gen_call("$printf",((Funcb*)($1.funcent->binding))->actual_num);
								code_generator.gen_call("$printf",$1.params);
							}
							else{
								if( ((Funcb*)($1.funcent->binding))->label==0) ((Funcb*)($1.funcent->binding))->label= code_generator.getlabel();
								code_generator.gen_call( code_generator.genlabelw($1.funcent->name,((Funcb*)($1.funcent->binding))->label),
									((Funcb*)($1.funcent->binding))->num_param);
							}
						}
				}
}

void Compiler::block63_name_and_params_ident_lpar_source(){
	(*outPacket)->funcent =NULL;
	(*outPacket)->funcent =  mysymtab->lookupB($<value.svalue>1);
	#ifdef DEBUG
	printTree(mysymtab);
	fprintf(stderr,"this the name of function called and the lookup value: %s\n",$1);
	if( mysymtab->lookupB($1)==NULL) fprintf(stderr,"it was null\n");
	else fprintf(stderr,"wasn't null\n");
	#endif
	if ((*outPacket)->funcent != NULL){
		$$.name = $$.funcent->name;
		if(founderror==false) code_generator.gen_instr_I("enter",1);
	}
}

void Compiler::block64_name_and_params_ident_lpar_source_expr(){
        TableEntry*tempE, *tempE2;
        $$.lval = false;
        //listnodeE* tempexprN;
        //ListE * tempLE;
        //int a;
        Funcb* tempB;
        if((tempB= (Funcb*) mysymtab->lookup($<value.svalue>1)) ==NULL){
            error("function undelcared, please declare functions before using them","");
            error("1","");
            $$.funcent=NULL;
        }
        else {
					//warning("just checking value of entry: %s",$<value.funcentvalue>$->name);
            tempE2 = (TableEntry*) malloc(sizeof(TableEntry));
            tempE2->name =  $<value.svalue>1;
            if( (tempE=  mysymtab->lookupB($<value.svalue>1))!=NULL){
                if(tempE->self != btype::FUNC){
                    error("function undeclared, please declare functions before using them", "");
                    error("2","");
                    $$.funcent=NULL;
                }
                else{
                    if(tempB->num_param ==0){
                        error("Paramter given for a function that takes no parameters.","");
                    }
                    else if(tempB->num_param == -1){
                        #ifdef DEBUG
                        fprintf(stderr,"SPRINTF OR PRINTF mismatch: FUNCTION NAME: %s\n",$1);
                        fprintf(stderr,"SPRINTF OR PRINTF: FUNCTION TYPE: %d\n",(int)$4->type);
//                                                            fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
  //                                                          fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                        fprintf(stderr,"SPRINTF OR PRINTF: $4 TYPE: %d\n",(int)$4->type);
                        fprintf(stderr,"SPRINTF OR PRINTF: tempB->param_type[0] TYPE: %d\n",(int)tempB->param_type[0]);
                        #endif
                        if($4->type != tempB->param_type[0]){
                            error("parameter type is different in declaration and in function call","");
                        }
                        else{
                            if(founderror==false){
										//code_generator.gen_instr_S("pushs",$<value.svalue>4);
                            }
                        }
                        $$.ttype = tempB->param_type[0];
                        if($$.ttype== type::INT || $$.ttype == type::FLOAT)
                            $$.numeric=true;
                        else
                            $$.numeric=false;
                        $$.funcent=$3.funcent;
						$$.params = 1;
                    }
                    else{
                        if($4->lval==true && $4->numeric==true){
                            if(founderror==false){
                                switch($4->type){
                                    case type::INT:	code_generator.gen_instr("fetchI"); break;
                                    case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                                    default:    break;
                                }
                            }
                        }
                        if(tempB->param_type !=NULL){
                            if($4->type != tempB->param_type[0]){
                                #ifdef DEBUG
                                fprintf(stderr,"Function mismatch 2: FUNCTION NAME: %s\n",$1);
                                fprintf(stderr,"Function mismatch 2: FUNCTION TYPE: %d\n",(int)$4->type);
                                            //                                                            fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                            //                                                          fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                #endif
                                if(tempB->param_type[0]!= type::INT && tempB->param_type[0]!= type::FLOAT)
                                    error("Parameter type is different in declaration and in function call","");
                                else if(tempB->param_type[0]== type::INT){
                                        #ifdef DEBUG
                                        fprintf(stderr,"Function mismatch 3: FUNCTION NAME: %s\n",$1);
                                        fprintf(stderr,"Function mismatch 3: FUNCTION TYPE: %d\n",(int)$4->type);
                                                //                                                            fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                                //                                                          fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                        #endif
                                        switch($4->type){
                                            case type::FLOAT:
                                                warning("Paramter expression will lose data because of different type","");
                                                if(founderror==false)
                                                    code_generator.gen_instr("int");
                                                break;
                                            case type::INT:	break;
                                            default:	error("Parameter type is different in declaration and function call","");
                                                        break;
                                        }
                                }
                                else if(tempB->param_type[0]== type::FLOAT){
                                    #ifdef DEBUG
                                    fprintf(stderr,"Function mismatch 4: FUNCTION NAME: %s\n",$1);
                                    #endif
                                    switch($4->type){
                                        case type::INT:	warning("Parameter expression is different type than in declaration","");
                                                    if(founderror==false)
                                                        code_generator.gen_instr("flt");
                                                    break;
                                        case type::FLOAT:	break;
                                        default:	error("Parameter type is different in declaration and function call","");
                                                            break;
                                    }
                                }

                            }
                        }
                        $$.funcent=$3.funcent;

                        if(tempB->param_type !=NULL)
                            $$.ttype=tempB->param_type[0];
                        if($$.ttype== type::INT || $$.ttype== type::FLOAT)
                            $$.numeric =true;
                        else
                            $$.numeric=false;
                        $$.params=1;
                    }
                }
            }
            else
                error("Function is undeclared","");
            free(tempE2); tempE2=NULL;

        }
}

void Compiler::block65_name_and_params_name_and_params_comma_expr(){
	TableEntry*tempE, *tempE2;
      $$.lval = false;
      //listnodeE* tempexprN;
      //ListE * tempLE;
      //int a;
      Funcb* tempB;
      if($1.funcent==NULL){
      	error("function undelcared, please declare functions before using them","");
	   error("3","");
	}
      else {
		$$.funcent = $1.funcent;
          tempE2 = (TableEntry*) malloc(sizeof(TableEntry));
          tempE2->name = $1.funcent->name;
		tempB= (Funcb*) mysymtab->lookup( $1.funcent->name);
          if( (tempE=  mysymtab->lookupB($1.funcent->name))!=NULL){
          	if(tempE->self != btype::FUNC){
              	error("function undeclared, please declare functions before using them", "");
				error("4","");
			}
              else{
              	if(tempB->num_param ==0){
				}
			    else if(tempB->num_param == -1){
                  	$$.ttype = tempB->param_type[$1.params];
                      if($$.ttype== type::INT || $$.ttype == type::FLOAT) $$.numeric=true; else $$.numeric=false;
						$$.params = $1.params +1;
						$$.funcent=$1.funcent;
						if($4->lval==true && $4->numeric==true && strcmp("scanf",$$.funcent->name)!=0){
							if(founderror==false){
								switch($4->type){
									case type::INT:	code_generator.gen_instr("fetchI"); break;
									case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                                      default:    break;
								}
							}
						}
						
				}
                  else if($$.params < tempB->num_param){
                  	if($4->type != tempB->param_type[$1.params]){
                      	#ifdef DEBUG
                          fprintf(stderr,"Function mismatch before warning: FUNCTION NAME: %s\n",$1.name);
                          #endif

                          warning("Parameter type is different in declaration and in function call","");
						if(founderror==false){
							if($4->lval==true){
								switch($4->type){
									case type::INT:	code_generator.gen_instr("fetchI"); break;
									case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                                      default:    break;
								}
							}
							if(tempB->param_type[$1.params]== type::FLOAT){
								code_generator.gen_instr("flt");
							}
							else if(tempB->param_type[$1.params]== type::INT){
								code_generator.gen_instr("int");
							}
						}
					}
					else{
						if(founderror==false){
							if($4->lval==true){
								switch($4->type){
									case type::INT:	code_generator.gen_instr("fetchI"); break;
									case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
                                      default:    break;
								}
							}
						}

					}
                      $$.ttype=tempB->param_type[$1.params];
                      if($$.ttype== type::INT || $$.ttype== type::FLOAT) $$.numeric =true; else $$.numeric=false;
					$$.params=$1.params +1;
					$$.funcent=$1.funcent;
                }
			  else{
			  	error("Too many parameters given for function in function call.","");
			  }
		  }
	   }
	   else
         	error("Function is undeclared","");
         free(tempE2); tempE2=NULL;

   }
}
/*
void Compiler::block66_constant_strconstant(ucc::Constant* mcon, std::string instrconstant){
 			*mcon = instrconstant;
			(*mcon).ttype = type::STR;
			(*mcon).lval = false;
			(*mcon).numeric=false;
}

void Compiler::block67_constant_intconstant(ucc::Constant* mcon, int intconstant){
	 	(*mcon) = intconstant;
		(*mcon).ttype = type::INT;
		(*mcon).lval = false;
		(*mcon).numeric= true;
}

void Compiler::block68_constant_floatconstant(ucc::Constant* mcon, float floatconstant){
	(*mcon) = new Constant{};
		(*mcon) = floatconstant;
		(*mcon).ttype = type::FLOAT;
		(*mcon).lval = false;
		(*mcon).numeric= true;
}
*/
void Compiler::block69_identlist_ident(List** outIdentListptr, ucc::Identifier inIdent){
	(*outIdentListptr) = List::mklist(inIdent);
}

void Compiler::block70_identlist_comma_ident(List** outIdentListptr, List** inIdentListptr, ucc::Identifier inIdent){
	(*outIdentListptr) = (*inIdentListptr)->appendList(inIdent);
}

}