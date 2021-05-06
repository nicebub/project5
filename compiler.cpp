#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "compiler.hpp"
#include "ucc.tab.hpp"

using namespace ucc;
namespace ucc{

//std::string 	Compiler::filename{""};
/*
int 				Compiler::Line_Number{1};
int 				Compiler::globalcount{0};
int 				Compiler::offset_counter{5};
int 				Compiler::othercounter{1};
int 				Compiler::param_offset{0};
int 				Compiler::mainlocal{0};
*/
/*
std::ostream* 			Compiler::outfile{&std::cout};
*/

Compiler::Compiler(): mysymtab{SymbolTable::createTree(INITIAL_TREE_SIZE)}, 
							code_generator{},
							lexer{NULL,*this}, 
							founderror{false},
							parser(*this),
							Line_Number(1),
							globalcount(0),
							offset_counter(5),
							othercounter(1),
							param_offset(0),
							mainlocal(0) {
	if(mysymtab == NULL){
		error("Unable to construct symbol table","");
	}
}

Compiler::Compiler(int argc, const char** argv) : 	mysymtab{SymbolTable::createTree(INITIAL_TREE_SIZE)}, 
																	code_generator{}, 
																	founderror{false}, 
																	lexer{NULL,*this}, 
																	parser(*this),
																	Line_Number(1),
																	globalcount(0),
																	offset_counter(5),
																	othercounter(1),
																	param_offset(0),
																	mainlocal(0) {
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
	code_generator.gen_instr_I("alloc",Compiler::globalcount);
	code_generator.gen_instr_I("enter",0);
	code_generator.gen_call(code_generator.genlabelw("main",mainlabel),0);
	code_generator.gen_instr("return");
}
void Compiler::block2_func_funcheader_source(){
				Entry* tempEntry;
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
				if("main" == ($1->name)){
		                        #ifdef DEBUG
             			        fprintf(stderr,"hello from inside\n");
          				        #endif
					templist = (List*)$1->paramlist;
//main function
					if($1->returntype != type::INT)
						error("Main function has to have int as return type","");
					if(templist != NULL && templist->size() != 1)
						error("Main function only has one parameter","");
					else if($1->ttype != type::VOID)
						error("Main function has to have one parameter of void","");
					#ifdef DEBUG							
					fprintf(stderr, "opening up a new scope\n");
					#endif		
					SymbolTable::openscope(mysymtab);
					 alreadyopen=true;
					if(Compiler::founderror==false){
						mainlabel=compiler->code_generator.getlabel();
						compiler->code_generator.gen_label(compiler->code_generator.genlabelw("main", mainlabel));
					}
				}
				else{
					if((tempb=(Funcb*)SymbolTable::lookup($1->name, mysymtab)) ==NULL)
						error("Function name not in symbol table","");
					else{
						Entry *tempEn; Entry * tempEn2;
						tempEn2 = (Entry*) malloc(sizeof(Entry));
						tempEn2->name = $1->name;
						tempEn = SymbolTable::lookupB($1->name,mysymtab);
						//tempEn = *(Entry**)tfind((void*)tempEn2, (void**) &(SymbolTable::Stack[SymbolTable::actualStacksize -1]),Ecmp);
						if(tempEn!=NULL && tempEn->self == btype::FUNC){
							if(tempb->returntype != $<value.funcheadervalue>1->returntype)
								error("Function declared with different return type","");
							else{
								templist= (List*)$<value.funcheadervalue>1->paramlist;
								if(tempb->num_param == -1)
									error("Function cannot have those parameters","");
								else if( templist!=NULL && (templist->size()) != tempb->num_param)
									error("Function has different number of parameters","");
								else{
									if(templist!=NULL){
										tempnode = (ListNode*)templist->list;
										for(a=0;a<templist->size() && a<tempb->num_param &&  stop!=true;a++){
											if(tempb->param_type[a] != tempnode->ttype){
												fprintf(stderr,"Error: Line: %d: argument %d: has different parameter type than in function declaration\n",Compiler::Line_Number,(a+1));
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
											SymbolTable::openscope(mysymtab);
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
													tempEntry = SymbolTable::createParam(tempnode->getval(), tempnode->ttype,(Compiler::offset_counter));
													SymbolTable::install(tempEntry, mysymtab);
													Compiler::offset_counter++;
													tempnode = (listnodeP*)tempnode->nextnode;
												}
											}
											if(Compiler::founderror==false){
												//tempb->label=getlabel();
												compiler->code_generator.gen_label(compiler->code_generator.genlabelw($1->name,tempb->label ));

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
					if(alreadyopen==false) SymbolTable::openscope(mysymtab);
				}
}
void Compiler::block3_func_funcheader_source_funcbody(){
				code_generator.gen_instr("returnf");
//			if(currentFunc == NULL)
//				closemainscope(mysymtab);
//			else
				SymbolTable::closescope(mysymtab);
}
void Compiler::block4_func_funcheader_semi(){
   Entry * temp; Funcb* found; int a;
   #ifdef DEBUG
	printTree(mysymtab);
   #endif
   temp =  SymbolTable::createFunc($1->name, $1->returntype, (List*)($1->paramlist));
   if($1->paramlist !=NULL) delete ((List*)($1->paramlist));
   if($1 !=NULL) free($1);
   if( temp->name == "main"){
		if( ((Funcb*)(temp->binding))->returntype != type::INT)
			error("Main function needs return type of int","");
		if( ((Funcb*)(temp->binding))->num_param != 1)
			error("Main function only takes 1 parameter","");
		if( ((Funcb*)(temp->binding))->param_type[0] != type::VOID)
			error("Main function parameter has to be void","");
		delete temp;
   }
   else{
	   found = (Funcb*)(SymbolTable::lookup(temp->name, mysymtab));
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
	   if(found == NULL){ SymbolTable::install(temp, mysymtab); /*printTree(mysymtab)*/;}
	   else{
		if(((Funcb*)(temp->binding))->returntype != found->returntype)
			error("Function already declared with different return type","");
		if(((Funcb*)(temp->binding))->num_param == -1 || found->num_param == -1){
			if(((Funcb*)(temp->binding))->param_type[0] != found->param_type[0])
				error("In Function %s ", $1->name);
				fprintf(stderr,"argument 0 is of different type than in previous declaration\n");
		}
		else{
			if(((Funcb*)(temp->binding))->num_param != found->num_param)
				error("Function already decleared with different number of parameters","");
			if( ((Funcb*)(temp->binding))->num_param > 0 && found->num_param >0){
				for(a=0;a<((Funcb*)(temp->binding))->num_param && a<found->num_param ;a++){
					if(((Funcb*)(temp->binding))->param_type[a] != found->param_type[a]){
						error("In Function %s ", $1->name);
						fprintf(stderr, "argument %d is of different type than in previous declaration\n", a);
					}

				}
			}
		}
	   delete temp;
	   }
   }
}
void Compiler::block5_funcheader_error_semi(){
	if($1 !=NULL) if($1->paramlist !=NULL) delete ((List*)($1->paramlist));
	if($1 !=NULL) free($1); $1 = NULL;
}
void Compiler::block6_funcheader_void_ident_lpar_paramdef_rpar(){
	$$ = (funcheadertype*)malloc(sizeof(funcheadertype));
					$$->returntype = type::VOID;
					$$->name = $2;
                     $$->paramlist=NULL;
                     if($4.ttype == type::VOID) $$->ttype = type::VOID;
					//(ListP*)($$->paramlist) = $<value.lstpvalue>4;
					List * tempLP = NULL;
					tempLP = $<value.lstpvalue>4;
                     $$->paramlist = tempLP;
}
void Compiler::block7_funcheader_int_ident_lpar_paramdef_rpar(){
	$$ = (funcheadertype*)malloc(sizeof(funcheadertype));
				$$->returntype = type::INT;
				$$->name = $2;
                  $$->paramlist = NULL;
				if($4.ttype == type::VOID) $$->ttype = type::VOID;
				//(List*)($$->paramlist) = $<value.lstpvalue>4;
				List* tempLP = NULL;
				tempLP = $<value.lstpvalue>4;
                  $$->paramlist = tempLP;
}
void Compiler::block8_funcheader_float_ident_lpar_paramdef_rpar(){
	$$ = (funcheadertype*)malloc(sizeof(funcheadertype));
					$$->returntype = type::FLOAT;
					$$->name = $2;
                     if($4.ttype == type::VOID) $$->ttype = type::VOID;
					//(ListP*)($$->paramlist) = $<value.lstpvalue>4;
					List* tempLP = NULL;
					tempLP = $<value.lstpvalue>4;
                     $$->paramlist = tempLP;
}
void Compiler::block9_funcheader_void_error_rpar(){
 List* tempP; yyerrok;
		$$ =(funcheadertype*) malloc(sizeof(funcheadertype));
		$$->name ="";
		$$->returntype= type::VOID;
		//(List*)($$->paramlist) = (ListP*) malloc(sizeof(List));
		List* tempLP;
		tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
		tempP= (List*)tempLP;
		$$->paramlist= tempLP;
}

void Compiler::block10_funcheader_int_error_rpar(){
 List* tempP; yyerrok;
	$$ =(funcheadertype*) malloc(sizeof(funcheadertype));
	$$->name ="";
	$$->returntype= type::INT;
	//(List*)($$->paramlist) = (ListP*) malloc(sizeof(List));
	List* tempLP;
	tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
	tempP= (List*)tempLP;
	$$->paramlist= tempLP;
}
void Compiler::block11_funcheader_float_error_rpar(){
 List* tempP; yyerrok;
		$$ =(funcheadertype*) malloc(sizeof(funcheadertype));
		$$->name ="";
		$$->returntype= type::FLOAT;
		//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
		List* tempLP;
		tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
		tempP= (List*)tempLP;
		$$->paramlist= tempLP;
}

void Compiler::block12_funcheader_void_ident_lpar_error_rpar(){
	List* tempP; yyerrok;
	$$ =(funcheadertype*) malloc(sizeof(funcheadertype));
	$$->name =$2;
	$$->returntype= type::VOID;
	//(Lis*)($$->paramlist) = NULL;
	List* tempLP1 = (List *)$$->paramlist;
	tempLP1 = NULL;
	//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
	List* tempLP;
	tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
	tempP= (List*)tempLP;
	$$->paramlist= tempLP;
}
void Compiler::block13_funcheader_float_ident_lpar_error_rpar(){
 List* tempP; yyerrok;
		$$ =(funcheadertype*) malloc(sizeof(funcheadertype));
		$$->name =$2;
		$$->returntype= type::FLOAT;
		//(ListP*)($$->paramlist) = NULL;
		List* tempLP1 = (List *)$$->paramlist;
		tempLP1 = NULL;
		//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
		List* tempLP;
		tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
		tempP= (List*)tempLP;
		$$->paramlist= tempLP;
}
void Compiler::block14_funcheader_int_ident_lpar_error_rpar(){
	List* tempP; yyerrok;
			$$ = (funcheadertype*)  malloc(sizeof(funcheadertype));
			$$->name=$2;
			$$->returntype= type::INT;
			//(List*)($$->paramlist) = NULL;
			List* tempLP1 = (List *)$$->paramlist;
			tempLP1 = NULL;
			//(List*)($$->paramlist) = (List*) malloc(sizeof(List));
			List* tempLP;
			tempLP = (List*) List::mklist(std::string{"error"}, type::VOID);
			tempP= (List*)tempLP;
			$$->paramlist= tempLP;
}
void Compiler::block15_paramdef_paramdeflist(){
	$<value.lstpvalue>$= $1;
}
void Compiler::block15_paramdef_paramdeflist_comma_elip(){

		$<value.lstpvalue>$ = $1->appendList("...", type::VOID);
          #ifdef DEBUG
          printListP($<value.lstpvalue>$);
          #endif
}
void Compiler::block16_paramdef_void(){
	$<value.lstpvalue>$ = NULL;
	$$.ttype = type::VOID;
}
void Compiler::block17_paramdef_paramdeflist_error_rpar(){
	delete $1;
}
void Compiler::block18_paramdef_paramdeflist_comma_error_rpar(){
	delete $1;
}
void Compiler::block19_paramdeflist_int_ident(){
	$$ = List::mklist(std::string{$2}, type::INT);
       #ifdef DEBUG
       printListP($$);
       #endif
}
void Compiler::block20_paramdeflist_float_ident(){
	$$ = List::mklist(std::string{$2}, type::FLOAT);
       #ifdef DEBUG
       printListP($$);
       #endif
}
void Compiler::block21_paramdeflist_char_star_ident(){
	$$ = List::mklist(std::string{$3}, type::STR);
       #ifdef DEBUG
       printListP($$);
       #endif
}
void Compiler::block22_paramdeflist_paramdeflist_comma_int_ident(){
	$$ = $1->appendList(std::string{$4},type::INT);
       #ifdef DEBUG
       printListP($$);
       #endif
}
void Compiler::block23_paramdeflist_paramdeflist_comma_float_ident(){
	$$ = $1->appendList(std::string{$4}, type::FLOAT);
       #ifdef DEBUG
       printListP($$);
       #endif
}
void Compiler::block24_paramdeflist_paramdeflist_comma_char_star_ident(){
	$$ = $1->appendList(std::string{$5}, type::STR);
       #ifdef DEBUG
       printListP($$);
       #endif
}
void Compiler::block25_funcbody_lcbra_decls_source(){

	if(Compiler::founderror==false){
		Compiler::mainlocal=Compiler::offset_counter-5;
		if(currentFunc==NULL)
			compiler->code_generator.gen_instr_I("alloc", Compiler::mainlocal);
		else{
			currentFunc->localcount=Compiler::offset_counter-5-currentFunc->num_param;
			compiler->code_generator.gen_instr_I("alloc",currentFunc->localcount);
		}
	}
}

void Compiler::block26_funcbody_lcbra_decls_source_stmtlist_rcbra(){
	#ifdef DEBUG
	printTree(mysymtab);
	#endif
}

void Compiler::block27_variabledecl_int_identlist_semi(){

 if($<value.lstvalue>2 !=NULL) SymbolTable::addtosymtab(mysymtab, type::INT, $<value.lstvalue>2);
				#ifdef DEBUG
					fprintf(stderr,"Found a single Integer declaration or a list of integers being declared\n");
					printTree(mysymtab);
				#endif
}
void Compiler::block28_variabledecl_float_identlist_semi(){
		if($<value.lstvalue>2 !=NULL) 
			SymbolTable::addtosymtab(mysymtab, type::FLOAT, $<value.lstvalue>2); }
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

					if(Compiler::founderror==false){
						if($2->lval==true){
							switch($2->type){
								case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
								case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
                                   default: break;
							}
						}
						if($2->type != type::INT) compiler->code_generator.gen_instr("int");
						compiler->code_generator.gen_instr("setrvI");
					}

			}
			else{
				#ifdef DEBUG
				printf("type and returntype : %d: %d\n",$2->type,currentFunc->returntype);
				#endif
				if($2->type != currentFunc->returntype)
					warning("function has different returntype","");

					if(Compiler::founderror==false){
                                       if($2->lval==true){
                                           switch($2->type){
                                               case type::INT:       compiler->code_generator.gen_instr("fetchI"); break;
                                               case type::FLOAT:     compiler->code_generator.gen_instr("fetchR"); break;
                                               default:    break;
                                                                       }
                                                               }
						switch(currentFunc->returntype){
							case type::INT:	switch($2->type){
										case type::FLOAT:	compiler->code_generator.gen_instr("int");
										case type::INT:	compiler->code_generator.gen_instr("setrvI"); break;
                                           default: break;
									}
									break;
							case type::FLOAT:	switch($2->type){
										case type::INT:	compiler->code_generator.gen_instr("flt");
										case type::FLOAT:	compiler->code_generator.gen_instr("setrvR"); break;
                                           default:    break;
									}
									break;
                               default: break;
						}
                           
						compiler->code_generator.gen_instr("returnf");
                                                       }



			}
		}
}
void Compiler::block32_stmt_while_source(){
	if(Compiler::founderror==false){
		$$.one= Compiler::othercounter;
		Compiler::othercounter++;
		$$.two = Compiler::othercounter;
		Compiler::othercounter++;
		compiler->code_generator.gen_label(compiler->code_generator.genlabelw("",$$.one));
	}
}
void Compiler::block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(){
	if(Compiler::founderror==false){
		if($4->numeric==true){
			if($4->lval==true ){
				switch($4->type){
					case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
					case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); compiler->code_generator.gen_instr("int"); break;
                     default:    break;
				}
			}
		}
		compiler->code_generator.gen_instr_S("jumpz", compiler->code_generator.genlabelw("",$2.two));

	}
}
void Compiler::block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt(){
	if($4->numeric !=true)
		error("non numeric expression in while statement","");
	else{
			if($4->type != type::INT)
				error("expression in while statement is not an integer","");
			if(Compiler::founderror==false){
				compiler->code_generator.gen_instr_S("jump", compiler->code_generator.genlabelw("",$2.one));
				compiler->code_generator.gen_label(compiler->code_generator.genlabelw("",$2.two));
			}

	}
}
void Compiler::block35_stmt_ifexprstmt_else(){
	if(Compiler::founderror==false){
		compiler->code_generator.gen_instr_S("jump", compiler->code_generator.genlabelw("",$1.two));
		compiler->code_generator.gen_label(compiler->code_generator.genlabelw("",$1.one));
	}
}

void Compiler::block36_stmt_ifexprstmt_else_source_stmt(){
	if($1.numeric !=true)
			error("non numeric expression in if statement","");
		else{
			if($1.ttype != type::INT)
				error("expression in if statement is not an integer","");
			else{
				if(Compiler::founderror==false){
					compiler->code_generator.gen_label(compiler->code_generator.genlabelw("",$1.two));
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

			if(Compiler::founderror==false) compiler->code_generator.gen_label(compiler->code_generator.genlabelw("",$1.one));
		}
	}
}

void Compiler::block38_ifexprstmt_if_lpar_expr_source(){
	$$.one=Compiler::othercounter;
	Compiler::othercounter++;
	$$.two=Compiler::othercounter;
	Compiler::othercounter++;
	if(Compiler::founderror==false){
		if($3->lval==true && $3->numeric==true){
			switch($3->type){
				case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); compiler->code_generator.gen_instr("int"); break;
                 default:    break;
			}
		}
		compiler->code_generator.gen_instr_S("jumpz", compiler->code_generator.genlabelw("",$$.one));
	}
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
		if(Compiler::founderror==false){
			if($3.lval==true){
				switch($3.ttype){
					case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
					case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
                        default:    break;
				}
			}
		}
		if(($1.ttype== type::INT && $3.ttype == type::INT) || ($1.ttype == type::FLOAT && $3.ttype== type::FLOAT)) {
			$$ = (exprtype*) malloc(sizeof(exprtype));
			if(Compiler::founderror==false){
				switch($1.ttype){
					case(type::INT): $$->type= type::INT; compiler->code_generator.gen_instr("storeI"); break;
					case(type::FLOAT): $$->type= type::FLOAT; compiler->code_generator.gen_instr("storeR"); break;
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
			if(Compiler::founderror==false){
				compiler->code_generator.gen_instr("int");
				compiler->code_generator.gen_instr("storeI");
			}
		}
		else if($1.ttype == type::FLOAT && $3.ttype == type::INT) {
			warning("expression are of different type, data may be lost","");
			$$ = (exprtype*) malloc(sizeof(exprtype));
			$$->type= type::FLOAT;
			$$->numeric=true;
			$$->lval=true;
			if(Compiler::founderror==false){
				compiler->code_generator.gen_instr("flt");
				compiler->code_generator.gen_instr("storeR");
			}
		}

	}
}

void Compiler::block41_expr_equalexpr(){
	$$ = (exprtype*) malloc(sizeof(exprtype));
	$$->lval = $1.lval; $$->numeric = $1.numeric; $$->type =$1.ttype;
}


void Compiler::block42_equalexpr_relexpr_eqop_source(){
	if(Compiler::founderror==false){
		if($1.numeric==true){
			switch($1.ttype){
				case type::INT:	if($1.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($1.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                 default:    break;
			}
		}
	}
}

void Compiler::block43_equalexpr_relexpr_eqop_source_relexpr(){
	if(Compiler::founderror==false){
		if($4.numeric==true){
			switch($4.ttype){
				case type::INT:	if($4.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($4.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                 default:    break;
			}
		}
	}
				$$.lval = false;
				if($1.numeric==true && $4.numeric==true){
					$$.numeric = true;
					$$.ttype= type::INT;
					if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype= type::INT;
						if(Compiler::founderror==false){
                                                                     switch($<value.eqopvalue>2){
                                                                             case eqtype::NEQ:       if($1.ttype== type::INT) compiler->code_generator.gen_instr("neI");
                                                                                             else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("neR");
                                                                                             break;
                                                                             case eqtype::EQEQ:      if($1.ttype== type::INT) compiler->code_generator.gen_instr("eqI");
                                                                                             else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("eqR");
                                                                                             break;
                                                                             default:    break;
                                                                     }
                                                     }

					}
					else if($1.ttype == type::INT && $4.ttype== type::FLOAT){
						warning("expressons are of different type, data may be lost","");
						$$.ttype = type::INT;
							if(Compiler::founderror==false){
                                                                     switch($<value.eqopvalue>2){
                                                                             case eqtype::NEQ:       compiler->code_generator.gen_instr("fltb");
                                                                                             compiler->code_generator.gen_instr("neR");
                                                                                             break;
                                                                             case eqtype::EQEQ:       compiler->code_generator.gen_instr("fltb");
                                                                                             compiler->code_generator.gen_instr("eqR");
                                                                                             break;
                                                                             default:    break;
                                                                     }
                                                             }

					}
					else if($1.ttype == type::FLOAT && $4.ttype == type::INT) {
						 warning("expression are of different type, data may be lost","");
						$$.ttype= type::INT;
						if(Compiler::founderror==false){
                                                                     switch($<value.eqopvalue>2){
                                                                             case eqtype::NEQ:       compiler->code_generator.gen_instr("flt");
                                                                                             compiler->code_generator.gen_instr("neR");
                                                                                             break;
                                                                             case eqtype::EQEQ:       compiler->code_generator.gen_instr("flt");
                                                                                             compiler->code_generator.gen_instr("eqR");
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
	if(Compiler::founderror==false){
		if($1.numeric==true){
			switch($1.ttype){
				case type::INT:	if($1.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($1.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                 default:    break;
             }
		}
	}
}

void Compiler::block46_relexpr_simpleexpr_relop_source_simpleexpr(){
	if(Compiler::founderror==false){
		if($4.numeric==true){
			switch($4.ttype){
				case type::INT:	if($4.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($4.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                  default:    break;
			}
		}
	}
				$$.lval = false;
				if($1.numeric == true && $4.numeric ==true){
					$$.numeric=true;
					$$.ttype= type::INT;
					if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype= type::INT;
						if(Compiler::founderror==false){
							switch($<value.relopvalue>2){
                                  case reltype::LES:       if($1.ttype== type::INT) compiler->code_generator.gen_instr("ltI");
                                                          else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("ltR");
                                                                      break;
                                  case reltype::LEQ:       if($1.ttype== type::INT) compiler->code_generator.gen_instr("leI");
                                                          else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("leR");
                                                                      break;
								case reltype::GRE:	if($1.ttype== type::INT) compiler->code_generator.gen_instr("gtI");
										else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("gtR");
										break;
								case reltype::GEQ:	if($1.ttype== type::INT) compiler->code_generator.gen_instr("geI");
										else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("geR");
										break;
                                  default:    break;
                                                                  }
						}

					}
					else if($1.ttype == type::INT && $4.ttype== type::FLOAT){
						warning("expressons are of different type, data may be lost","");
						$$.ttype = type::INT;
						if( Compiler::founderror==false){
                                          switch($<value.relopvalue>2){
                                                  case reltype::LES:       compiler->code_generator.gen_instr("fltb");
										compiler->code_generator.gen_instr("ltR");
                                                                                          break;
                                                  case reltype::LEQ:       compiler->code_generator.gen_instr("fltb");
										compiler->code_generator.gen_instr("leR");
                                                                                          break;
                                                  case reltype::GRE:       compiler->code_generator.gen_instr("fltb");
										compiler->code_generator.gen_instr("gtR");
                                                                                          break;
                                                  case reltype::GEQ:       compiler->code_generator.gen_instr("fltb");
										compiler->code_generator.gen_instr("geR");
                                                                                          break;
                                                  default:    break;
                                                                  }
                                                          }
					}
					else if($1.ttype == type::FLOAT && $4.ttype == type::INT) {
						warning("expression are of different type, data may be lost","");
						$$.ttype = type::INT;
						if( Compiler::founderror==false){
                                                                  switch($<value.relopvalue>2){
                                                                          case reltype::LES:       compiler->code_generator.gen_instr("flt");
                                                                                          compiler->code_generator.gen_instr("ltR");
                                                                                          break;
                                                                          case reltype::LEQ:       compiler->code_generator.gen_instr("flt");
                                                                                          compiler->code_generator.gen_instr("leR");
                                                                                          break;
                                                                          case reltype::GRE:       compiler->code_generator.gen_instr("flt");
                                                                                          compiler->code_generator.gen_instr("gtR");
                                                                                          break;
                                                                          case reltype::GEQ:       compiler->code_generator.gen_instr("flt");
                                                                                          compiler->code_generator.gen_instr("geR");
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
	if(Compiler::founderror==false){
                     if($1.numeric==true){
                             switch($1.ttype){
                                     case type::INT:       if($1.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
                                     case type::FLOAT:     if($1.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                                     default:        break;
                             }
                     }
             }

}

void Compiler::block49_simpleexpr_simpleexpr_addop_source_term(){
	if(Compiler::founderror==false){
                          if($4.numeric ==true){
                                  switch($4.ttype){
                                          case type::INT:       if($4.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
                                          case type::FLOAT:     if($4.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                                          default:        break;
                                  }
                          }
                  }
				$$.lval = false;
				if($1.numeric == true && $4.numeric==true){
					$$.numeric=true;
					if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype=$1.ttype;
						if(Compiler::founderror==false){
  		                                                switch($<value.addopvalue>2){
          		                                                case addtype::PLS:       if($1.ttype== type::INT) compiler->code_generator.gen_instr("addI");
                  		                                                        else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("addR");
                          		                                                break;
                                  		                        case addtype::MIN:       if($1.ttype== type::INT) compiler->code_generator.gen_instr("subI");
                                          		                                else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("subR");
                                                  		                        break;
                                                                  default:        break;
                     	                       		      	}
                             	            	}
					}
					else if($1.ttype ==type::INT && $4.ttype== type::FLOAT){ warning("expressons are of different type, data may be lost","");
						$$.ttype = type::FLOAT;
                                                if( Compiler::founderror==false){
                                                        switch($<value.addopvalue>2){
                                                                case addtype::PLS:       compiler->code_generator.gen_instr("fltb");
                                                                                compiler->code_generator.gen_instr("addR");
                                                                                break;
                                                                case addtype::MIN:       compiler->code_generator.gen_instr("fltb");
                                                                                compiler->code_generator.gen_instr("subR");
                                                                                break;
                                                                  default:        break;
                                                        }
                                                }
					}
					else if($1.ttype == type::FLOAT && $4.ttype == type::INT) { warning("expression are of different type, data may be lost","");
						$$.ttype = type::FLOAT;
                  		                        if( Compiler::founderror==false){
                  		                                switch($<value.addopvalue>2){
                  		                                        case addtype::PLS:       compiler->code_generator.gen_instr("flt");
                  		                                                        compiler->code_generator.gen_instr("addR");
                  		                                                        break;
                  		                                        case addtype::MIN:       compiler->code_generator.gen_instr("flt");
                  		                                                        compiler->code_generator.gen_instr("subR");
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

void Compiler::block51_term_term_mulop_source(){
	if(Compiler::founderror==false){
		if($1.numeric==true){
			switch($1.ttype){
				case type::INT:	if($1.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($1.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                 default:    break;
			}
		}
	}
}

void Compiler::block52_term_term_mulop_source_factor(){
	if(Compiler::founderror==false){
		if($4.numeric ==true){
			switch($4.ttype){
				case type::INT:	if($4.lval==true) compiler->code_generator.gen_instr("fetchI"); break;
				case type::FLOAT:	if($4.lval==true) compiler->code_generator.gen_instr("fetchR"); break;
                  default:    break;
			}
		}
	}
		$$.lval = false;
		if($1.numeric ==true && $4.numeric ==true){
			$$.numeric =true;
			if(($1.ttype== type::INT && $4.ttype == type::INT) || ($1.ttype == type::FLOAT && $4.ttype== type::FLOAT)) {$$.ttype = $1.ttype;
				if(Compiler::founderror==false){
					switch($<value.multopvalue>2){
						case multype::DIV:	if($1.ttype== type::INT) compiler->code_generator.gen_instr("divI");
								else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("divR");
								break;
						case multype::MULT:	if($1.ttype== type::INT) compiler->code_generator.gen_instr("mulI");
								else if($1.ttype== type::FLOAT) compiler->code_generator.gen_instr("mulR");
								break;
                                  default:    break;
					}
				}
			}
			else if($1.ttype == type::INT && $4.ttype== type::FLOAT){
				warning("expressons are of different type, data may be lost","");
				$$.ttype = type::FLOAT;
				if(Compiler::founderror==false){
					switch($<value.multopvalue>2){
  	                                                case multype::DIV:       compiler->code_generator.gen_instr("fltb");
								compiler->code_generator.gen_instr("divR");
                  	                                                break;
                          	                        case multype::MULT:      compiler->code_generator.gen_instr("fltb");
								compiler->code_generator.gen_instr("mulR");
                                          	                        break;
                                                      default:    break;
                                             }
				}
			}
			else if($1.ttype == type::FLOAT && $4.ttype == type::INT) {
				warning("expression are of different type, data may be lost","");
				$$.ttype = type::FLOAT;
				if(Compiler::founderror==false){
					switch($<value.multopvalue>2){
  	                                                case multype::DIV:       compiler->code_generator.gen_instr("flt");
          	                                                        compiler->code_generator.gen_instr("divR");
                  	                                                break;
                          	                        case multype::MULT:      compiler->code_generator.gen_instr("flt");
                                  	                                compiler->code_generator.gen_instr("mulR");
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

void Compiler::block54_factor_constant(){
	$$.ttype = $1.ttype; $$.lval = false; $$.numeric=true;
		if(Compiler::founderror==false){
			if($$.ttype == type::INT)
				compiler->code_generator.gen_instr_I("pushcI",$<value.ivalue>1);
			else if($$.ttype == type::FLOAT)
				compiler->code_generator.gen_instr_F("pushcR",$<value.fvalue>1);
			else if($$.ttype == type::STR){
				compiler->code_generator.gen_instr_S("pushs",$<value.svalue>1);
				$$.numeric=false;
			}
			else
				error("constant is not a correct type of constant","");
		}
}

void Compiler::block55_factor_ident(){
	Entry *tempE, *tempE2; $<value.svalue>$ = $1;
		if($<value.svalue>1 != "main"){
			//if(lookup((char*)$<value.svalue>1, mysymtab) == NULL)
			//	error("variable undeclared, please declare variables before using them","");
			if(1){
				tempE2 = (Entry*) malloc(sizeof(Entry));
				tempE2->name =$<value.svalue>1;
				#ifdef DEBUG
				fprintf(stderr,"the name of the identifier here is:  %s\n", (char*)$<value.svalue>1);
				#endif
				if((tempE= SymbolTable::lookupB(tempE2->name,mysymtab)) !=NULL){

					if(tempE->self == btype::VAR || tempE->self == btype::PARAM){
						switch(tempE->self){
							case btype::VAR:
								$$.ttype = ((Varb*)(tempE->binding))->type;
								#ifdef DEBUG
								char temp_char = (char)$$.ttype;
								if($$.ttype !=  NULL) fprintf(stderr,"type is: %s\n", &temp_char);
								if(((Varb*)(tempE->binding))->type !=NULL) fprintf(stderr,"type is: %d\n", ((Varb*)(tempE->binding))->type);
								#endif
								$$.lval = true;
								if(((Varb*)(tempE->binding))->type == type::INT || ((Varb*)(tempE->binding))->type == type::FLOAT) $$.numeric=true;
								if(Compiler::founderror==false){
									if(SymbolTable::inCscope(tempE2->name, mysymtab) == true)
										compiler->code_generator.gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
									else{
										compiler->code_generator.gen_instr_tI("pushga",SymbolTable::getleveldif(tempE2->name,mysymtab),((Varb*)(tempE->binding))->offset);
										//do something else

									}
								}
								break;
							case btype::PARAM:
								$$.ttype = ((Paramb*)(tempE->binding))->type;
								#ifdef DEBUG
								fprintf(stderr,"type is: %d\n", (int)$$.ttype);
								#endif
								$$.lval = true;
								if(((Paramb*)(tempE->binding))->type == type::INT || ((Paramb*)(tempE->binding))->type == type::FLOAT) $$.numeric=true;
								if(Compiler::founderror==false){
									if(SymbolTable::inCscope(tempE2->name,mysymtab) ==true){
										compiler->code_generator.gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
									}
									else{
										//do something else
									}
								}
								break;
                              default:        break;

						}
					}
					else
						error("Variable is unknown or undelcared","");
				}
				else{
					$$.lval=false;
					$$.numeric=false;
					$$.ttype= type::VOID;
					error("Variable is unknown or undelcared, couldn't find in symbol table'","");
				}
			}
		}
		else{
			error("Main is not a variable name","");
				//tempE2 = (Entry*) malloc(sizeof(Entry));
				//tempE2->name = $<value.svalue>1;

		}
}

void Compiler::block56_factor_lpar_expr_rpar(){
	$$.lval = $2->lval; $$.ttype = $2->type; $$.numeric= $2->numeric;
}

void Compiler::block57_factor_addop_factor_uminus(){
	if(Compiler::founderror==false){
		if($2.numeric==true){
			if($1 == addtype::MIN){
				if($2.lval ==true){
					switch($2.ttype){
						case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
						case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
                           default:    break;
					}
				}
				switch($2.ttype){
					case type::INT:	compiler->code_generator.gen_instr("negI"); break;
					case type::FLOAT:	compiler->code_generator.gen_instr("negR"); break;
                       default:    break;
				}
			}
			else if($1 == addtype::PLS){
				if($2.lval == true){
					switch($2.ttype){
						case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
						case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
                           default:    break;
					}
				}
			}
		}
	}
			$$.lval = false;
			$$.ttype = $2.ttype;
			if($2.numeric ==true) $$.numeric=true;
			else
				error("cannot change sign of non numeric expression","");
}

void Compiler::block58_factor_adof_ident(){
	Entry *tempE, *tempE2; $<value.svalue>$ = $2;
                       if($<value.svalue>2 != "main"){
                               if(SymbolTable::lookup($<value.svalue>2, mysymtab) == NULL)
							error("variable undeclared, please declare variables before using them","");
                               else{
                                       tempE2 = (Entry*) malloc(sizeof(Entry));
                                       tempE2->name = $<value.svalue>2;
               if((tempE= SymbolTable::lookupB($<value.svalue>2,mysymtab)) !=NULL){

                   if(tempE->self == btype::VAR || tempE->self == btype::PARAM){
                       switch(tempE->self){
                           case btype::VAR:
                               $$.ttype = ((Varb*)(tempE->binding))->type;
                               #ifdef DEBUG
                               fprintf(stderr,"type is: %d\n", (int)$$.ttype);
                               #endif
                               $$.lval = false;
                               if(((Varb*)(tempE->binding))->type == type::INT || ((Varb*)(tempE->binding))->type == type::FLOAT)
                                   $$.numeric=true;
							if(Compiler::founderror==false){
                                   if(SymbolTable::inCscope($<value.svalue>2, mysymtab) == true)
                                       compiler->code_generator.gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
                                   else{
                                       compiler->code_generator.gen_instr_tI("pushga",SymbolTable::getleveldif($<value.svalue>2,mysymtab),((Varb*)(tempE->binding))->offset);
                           //do something else

                                   }
                               }
                               break;
                           case btype::PARAM:
                               $$.ttype = ((Paramb*)(tempE->binding))->type;
                               #ifdef DEBUG
                               fprintf(stderr,"type is: %d\n", (int)$$.ttype);
                               #endif
                               $$.lval = false;
                               if(((Paramb*)(tempE->binding))->type == type::INT || ((Paramb*)(tempE->binding))->type == type::FLOAT)
                                   $$.numeric=true;
                               if(Compiler::founderror==false){
                                   if(SymbolTable::inCscope($<value.svalue>2,mysymtab) ==true){
                                       compiler->code_generator.gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
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
                                               $$.lval=false;
                                               $$.numeric=false;
                                               $$.ttype= type::VOID;
                                               error("Variable is unknown or undelcared","");
                                       }
                               }
                       }
                       else{
                               error("Main is not a variable name", "");
                                       //tempE2 = (Entry*) malloc(sizeof(Entry));
                                       //tempE2->name = (char*) $<value.svalue>1;

                       }
}

void Compiler::block59_factor_function_call(){
	$$.ttype = $1.ttype; $$.lval = false; $$.numeric=$1.numeric; 
}

void Compiler::block60_function_call_ident_lpar_rpar(){
	$$.lval = false; Funcb* tempb; Entry* tempE; Entry *tempE2;
                                if((tempb=(Funcb*)SymbolTable::lookup($<value.svalue>1,mysymtab)) == NULL){
                                        error("function undeclared, please declare functions before using them","");
				}
                                else{
                                        tempE2 = (Entry*) malloc(sizeof(Entry));
                                        tempE2->name = $<value.svalue>1;
                                        if((tempE= SymbolTable::lookupB($<value.svalue>1,mysymtab))!=NULL){
                                                if(tempE->self == btype::FUNC){
							if(tempb->returntype != type::VOID) $$.lval =true; else $$.lval=false;
                                                        if(tempb->num_param != 0)
                                                                error("Function call without correct number of parameters if any","");
                                                        $$.ttype = tempb->returntype;
                                                        if($$.ttype == type::INT || $$.ttype == type::FLOAT) $$.numeric =true; else $$.numeric =false;
							if(Compiler::founderror==false){
								compiler->code_generator.gen_instr_I("enter",1);
								compiler->code_generator.gen_call(compiler->code_generator.genlabelw($<value.svalue>1, tempb->label), 0);
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
	$$.ttype =$1.ttype; $$.numeric = $1.numeric; $$.lval = $1.lval;
}

void Compiler::block62_func_call_with_params_name_and_params_rpar(){
	$$.numeric =$1.numeric; $$.lval = false; $$.ttype = $1.ttype;
				if($1.funcent!=NULL){
						if(($1.funcent)->self == btype::FUNC){
							if( ((Funcb*)(($1.funcent)->binding))->returntype != type::VOID) $$.numeric = true; else $$.numeric=false;
						}
						if(Compiler::founderror==false){
							if( "scanf" == $1.funcent->name){
//								compiler->code_generator.gen_call("$scanf",((Funcb*)($1.funcent->binding))->actual_num);
								compiler->code_generator.gen_call("$scanf",$1.params);
							}
							else if("printf" ==  $1.funcent->name){
//								compiler->code_generator.gen_call("$printf",((Funcb*)($1.funcent->binding))->actual_num);
								compiler->code_generator.gen_call("$printf",$1.params);
							}
							else{
								if( ((Funcb*)($1.funcent->binding))->label==0) ((Funcb*)($1.funcent->binding))->label= compiler->code_generator.getlabel();
								compiler->code_generator.gen_call( compiler->code_generator.genlabelw($1.funcent->name,((Funcb*)($1.funcent->binding))->label),
									((Funcb*)($1.funcent->binding))->num_param);
							}
						}
				}
}

void Compiler::block63_name_and_params_ident_lpar_source(){
	$$.funcent =NULL;
	$$.funcent = SymbolTable::lookupB($<value.svalue>1,mysymtab);
	#ifdef DEBUG
	printTree(mysymtab);
	fprintf(stderr,"this the name of function called and the lookup value: %s\n",$1);
	if(lookupB($1,mysymtab)==NULL) fprintf(stderr,"it was null\n");
	else fprintf(stderr,"wasn't null\n");
	#endif
	if ($$.funcent != NULL){
		$$.name = $$.funcent->name;
		if(Compiler::founderror==false) compiler->code_generator.gen_instr_I("enter",1);
	}
}

void Compiler::block64_name_and_params_ident_lpar_source_expr(){
        Entry *tempE, *tempE2;
        $$.lval = false;
        //listnodeE* tempexprN;
        //ListE * tempLE;
        //int a;
        Funcb* tempB;
        if((tempB= (Funcb*)SymbolTable::lookup($<value.svalue>1,mysymtab)) ==NULL){
            error("function undelcared, please declare functions before using them","");
            error("1","");
            $$.funcent=NULL;
        }
        else {
					//warning("just checking value of entry: %s",$<value.funcentvalue>$->name);
            tempE2 = (Entry*) malloc(sizeof(Entry));
            tempE2->name =  $<value.svalue>1;
            if( (tempE= SymbolTable::lookupB($<value.svalue>1,mysymtab))!=NULL){
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
                            if(Compiler::founderror==false){
										//compiler->code_generator.gen_instr_S("pushs",$<value.svalue>4);
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
                            if(Compiler::founderror==false){
                                switch($4->type){
                                    case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
                                    case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
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
                                                if(Compiler::founderror==false)
                                                    compiler->code_generator.gen_instr("int");
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
                                                    if(Compiler::founderror==false)
                                                        compiler->code_generator.gen_instr("flt");
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
	Entry *tempE, *tempE2;
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
          tempE2 = (Entry*) malloc(sizeof(Entry));
          tempE2->name = $1.funcent->name;
		tempB= (Funcb*)SymbolTable::lookup( $1.funcent->name,mysymtab);
          if( (tempE= SymbolTable::lookupB($1.funcent->name,mysymtab))!=NULL){
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
							if(Compiler::founderror==false){
								switch($4->type){
									case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
									case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
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
						if(Compiler::founderror==false){
							if($4->lval==true){
								switch($4->type){
									case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
									case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
                                      default:    break;
								}
							}
							if(tempB->param_type[$1.params]== type::FLOAT){
								compiler->code_generator.gen_instr("flt");
							}
							else if(tempB->param_type[$1.params]== type::INT){
								compiler->code_generator.gen_instr("int");
							}
						}
					}
					else{
						if(Compiler::founderror==false){
							if($4->lval==true){
								switch($4->type){
									case type::INT:	compiler->code_generator.gen_instr("fetchI"); break;
									case type::FLOAT:	compiler->code_generator.gen_instr("fetchR"); break;
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

void Compiler::block66_constant_strconstant(){
 $<value.svalue>$ = $1;
			$$.ttype = type::STR;
			$$.lval = false;
			$$.numeric=false;
}

void Compiler::block67_constant_intconstant(){
	$<value.ivalue>$ = $1;
		$$.ttype = type::INT;
		$$.lval = false;
		$$.numeric= true;
}

void Compiler::block68_constant_floatconstant(){
	$<value.fvalue>$ = $1;
		$$.ttype = type::FLOAT;
		$$.lval = false;
		$$.numeric= true;
}

void Compiler::block69_identlist_ident(){
	$$ = List::mklist($1));
}

void Compiler::block70_identlist_comma_ident(){
	$$ = $1->appendList($3);
}

}