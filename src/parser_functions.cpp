#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "debug.hpp"
#include "compiler.hpp"
#include "ucc.tab.hpp"

using namespace ucc;
namespace ucc{

void Compiler::block1_start_trans_unit(){
	code_generator.gen_label("main");
	code_generator.gen_instr_I("enter",0);
	code_generator.gen_instr_I("alloc", globalcount);
	code_generator.gen_instr_I("enter",0);
	code_generator.gen_call(code_generator.genlabelw("main",mainlabel),0);
	code_generator.gen_instr("return");
}
void Compiler::block2_func_funcheader_source(funcheadertype** inFuncHeaderptr){
	auto templabel{mainlabel};
	if(is_function_decl_or_def_accurate(inFuncHeaderptr,false)){
		mysymtab->openscope();
		if((*inFuncHeaderptr)->name != "main"){
			templabel = currentFunc->getlabel();
			install_parameters_into_symbol_table_curren_scope(inFuncHeaderptr);
		}
		code_generator.gen_label(code_generator.genlabelw((*inFuncHeaderptr)->name, templabel ));
	}
}
 void Compiler::block3_func_funcheader_source_funcbody(){
				code_generator.gen_instr("returnf");
				mysymtab->closescope();
}

void Compiler::block4_func_funcheader_semi(funcheadertype* inFuncHeader){
//   TableEntry* tempEntry{nullptr}; 
	auto found = mysymtab->lookupB(inFuncHeader->name);
	if(  found  == nullptr ){
	   auto tempEntry =  mysymtab->createFunc(	inFuncHeader->name, 
												inFuncHeader->returntype,
												inFuncHeader->paramlist 
											 );
		mysymtab->install(tempEntry);
		return;
	}
	is_function_decl_or_def_accurate(&inFuncHeader,true);
}

void Compiler::block5_funcheader_error_semi(funcheadertype** inFuncHeaderptr){
	funcheadertype* inFuncHeader{*inFuncHeaderptr};
	if(inFuncHeader !=nullptr){
		 delete inFuncHeader;
		 inFuncHeader = nullptr;
	 }
}

funcheadertype*  Compiler::funcheader_returntype_ident_lpar_paramdef_rpar_helper(ucc::Identifier inIdent, List* inParamdeflist,ucc::type inreturntype){
	funcheadertype* outFuncHeader{nullptr};

	outFuncHeader = new funcheadertype;
	outFuncHeader->returntype = inreturntype;
	outFuncHeader->name = inIdent.getvalue();
	outFuncHeader->paramlist=inParamdeflist;
	return outFuncHeader;
	/* FIXME: NEED TO REINCORPORATE THIS BACK IN. Somehow lists provide a type? where and why?
	if(inParamdeflist->gettype() == type::VOID){
		outFuncHeader->ttype = type::VOID;
	}	
	*/
}
/*
funcheadertype* Compiler::block6_funcheader_void_ident_lpar_paramdef_rpar(ucc::Identifier inIdent, List* inParamdeflist){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(inIdent, inParamdeflist,  ucc::type::VOID);
}
funcheadertype* Compiler::block7_funcheader_int_ident_lpar_paramdef_rpar(ucc::Identifier inIdent, List* inParamdeflist){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(inIdent, inParamdeflist,  ucc::type::INT);
}
funcheadertype* Compiler::block8_funcheader_float_ident_lpar_paramdef_rpar(ucc::Identifier inIdent, List* inParamdeflist){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(inIdent, inParamdeflist,  ucc::type::FLOAT);
}
funcheadertype* Compiler::block9_funcheader_void_error_rpar(){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(ucc::Identifier{""}, List::mklist(std::string{"error"}, type::VOID),  ucc::type::VOID);
}

funcheadertype* Compiler::block10_funcheader_int_error_rpar(){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(ucc::Identifier{""}, List::mklist(std::string{"error"}, type::VOID),  ucc::type::INT);
}
funcheadertype* Compiler::block11_funcheader_float_error_rpar(){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(ucc::Identifier{""}, List::mklist(std::string{"error"}, type::VOID),  ucc::type::FLOAT);
}

funcheadertype* Compiler::block12_funcheader_void_ident_lpar_error_rpar(ucc::Identifier inIdent){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(inIdent, List::mklist(std::string{"error"}, type::VOID),  ucc::type::VOID);
}
funcheadertype* Compiler::block13_funcheader_float_ident_lpar_error_rpar(ucc::Identifier inIdent){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(inIdent, List::mklist(std::string{"error"}, type::VOID),  ucc::type::FLOAT);
}
funcheadertype* Compiler::block14_funcheader_int_ident_lpar_error_rpar(ucc::Identifier inIdent){
	return funcheader_returntype_ident_lpar_paramdef_rpar_helper(inIdent, List::mklist(std::string{"error"}, type::VOID),  ucc::type::INT);
}
*/
/*
void Compiler::block15_paramdef_paramdeflist(List** outParamdefptr, List** inParamdeflistptr){
	*outParamdefptr = *inParamdeflistptr;
//	$<value.lstpvalue>$= $1;
}
*/
/*
List* Compiler::block15_paramdef_paramdeflist_comma_elip(List** inParamdeflistptr){

		return (*inParamdeflistptr)->appendList("...", type::VOID);

		#ifdef DEBUG
//		printListP(*outParamdefptr);
		#endif
}
List* Compiler::block16_paramdef_void(){
	return List::mklist("", ucc::type::VOID);
//	(*outParamdefptr) = nullptr;
//	(*outParamdefptr)->ttype = type::VOID; //FIXME need to add this back in somehow or see how it fits in
}
*/
/*
 void Compiler::block17_paramdef_paramdeflist_error_rpar(List** inParamdeflistptr){
	delete (*inParamdeflistptr);
	(*inParamdeflistptr) = nullptr;
}
 void Compiler::block18_paramdef_paramdeflist_comma_error_rpar(List** inParamdeflistptr){
	delete (*inParamdeflistptr);
	(*inParamdeflistptr) = nullptr;
}
*/
/*
List* Compiler::paramdeflist_type_ident_helper(ucc::Identifier inIdent, ucc::type intype){
	return List::mklist(inIdent.getvalue(), intype);

	#ifdef DEBUG
//	printListP((*outParamdeflistptr));
	#endif
	
}
*/
/*
 List* Compiler::block19_paramdeflist_int_ident(ucc::Identifier inIdent){
	return paramdeflist_type_ident_helper(inIdent,ucc::type::INT);
}
 List* Compiler::block20_paramdeflist_float_ident(ucc::Identifier inIdent){
	return paramdeflist_type_ident_helper(inIdent,ucc::type::FLOAT);
}
 List* Compiler::block21_paramdeflist_char_star_ident(ucc::Identifier inIdent){
	return paramdeflist_type_ident_helper(inIdent,ucc::type::STR);
}
*/
/*
List* Compiler::paramdeflist_paramdeflist_comma_type_ident_helper(List** inParamdeflistptr, ucc::Identifier inIdent, ucc::type intype){
	return (*inParamdeflistptr)->appendList(inIdent.getvalue(),intype);

	#ifdef DEBUG
//	printListP((*outParamdeflistptr));
	#endif
	
}
*/
/*
List* Compiler::block22_paramdeflist_paramdeflist_comma_int_ident(List** inParamdeflistptr, ucc::Identifier inIdent){
	return paramdeflist_paramdeflist_comma_type_ident_helper(inParamdeflistptr,inIdent,ucc::type::INT);
}
List* Compiler::block23_paramdeflist_paramdeflist_comma_float_ident(List** inParamdeflistptr, ucc::Identifier inIdent){
	return paramdeflist_paramdeflist_comma_type_ident_helper(inParamdeflistptr,inIdent,ucc::type::FLOAT);
}
List* Compiler::block24_paramdeflist_paramdeflist_comma_char_star_ident(List** inParamdeflistptr, ucc::Identifier inIdent){
	return paramdeflist_paramdeflist_comma_type_ident_helper(inParamdeflistptr,inIdent,ucc::type::STR);
}
*/
void Compiler::block25_funcbody_lcbra_decls_source(){
	auto temp{mainlocal};
	if(currentFunc->getvalue() == "main"){
		mainlocal = offset_counter-5;
		temp = mainlocal;
	}
	else{
	    switch(currentFunc->getparam_type()[0]){
		   case ucc::type::VOID:
			  currentFunc->setlocalcount( offset_counter - 5);
			  break;
		   default:
			  currentFunc->setlocalcount( offset_counter - 5 - currentFunc->getnum_param());
			  break;
	    }
		temp = currentFunc->getlocalcount();
	}
	code_generator.gen_instr_I("alloc", temp);
}

/*
 void Compiler::block26_funcbody_lcbra_decls_source_stmtlist_rcbra(){
	#ifdef DEBUG
//	printTree(mysymtab);
	#endif
}
*/
/*
void Compiler::block27_variabledecl_int_identlist_semi(List** inIdentlist){
	if( (*inIdentlist) != nullptr){
		mysymtab->addtosymtab(type::INT, (*inIdentlist));
	}

	#ifdef DEBUG
//	fprintf(stderr,"Found a single Integer declaration or a list of integers being declared\n");
//	printTree(mysymtab);
	#endif
}
void Compiler::block28_variabledecl_float_identlist_semi(List** inIdentlist){
		if( (*inIdentlist) != nullptr){
			mysymtab->addtosymtab(type::FLOAT, (*inIdentlist) );
		}

		#ifdef DEBUG
//		printTree(mysymtab);
		#endif
}
*/
 void Compiler::block29_stmt_expr_semi(){
		code_generator.gen_instr_I("popI",4);
}
void Compiler::block30_stmt_return_semi(){
	if(currentFunc == nullptr){
		error("main function has to return a value","");
		return;
	}

	if(currentFunc->getreturntype() != type::VOID){
		error("Function has return type that is not void","");
		return;
	}

	code_generator.gen_instr("returnf");
}

 void Compiler::variableFetch(ReturnPacket* inPacket, bool conversionNeeded){
	if( inPacket->getlval()){
		const static std::string fetch{"fetch"};
		switch(inPacket->gettype()){

			case type::INT:	code_generator.gen_instr(fetch + "I");
									break;

			case type::FLOAT:	code_generator.gen_instr(fetch + "R");

			default:
									if(conversionNeeded){
										code_generator.gen_instr("int");
									}
									break;
		}
	}
}
 void Compiler::variableFetchWithNumericCheck(ReturnPacket* inPacket, bool conversionNeeded){
	if(inPacket->getnumeric() ){
		variableFetch(inPacket,conversionNeeded);
	}
}
void Compiler::block31_stmt_return_expr_semi(ReturnPacket* inPacket){
	if( ! inPacket->getnumeric() ){
		error("non numeric expression in return statement or return type is void", "");
		return;
	}
	if(currentFunc == nullptr ){
		if( inPacket->gettype() != type::INT){
			warning("main function has int return type","");
		}

		variableFetchWithNumericCheck(inPacket,true); //conversion to integer needed

		code_generator.gen_instr("setrvI");
		return;
	}
	#ifdef DEBUG
//	std::cerr << "type and returntype : " << inPacket->gettype()  << ": "<< currentFunc->getreturntype()) << std::endl;
	#endif

	if( inPacket->gettype() != currentFunc->getreturntype()){
		warning("function has different returntype","");
	}

	variableFetchWithNumericCheck(inPacket,false);//conversion to integer not needed

	switch(currentFunc->getreturntype()){
		case type::INT:
			switch(inPacket->gettype()){
				case type::FLOAT:	code_generator.gen_instr("int");
				case type::INT:	code_generator.gen_instr("setrvI");
										break;
				default: break;
			}
			break;
		case type::FLOAT:	
			switch( inPacket->gettype() ){
				case type::INT:	code_generator.gen_instr("flt");
				case type::FLOAT:	code_generator.gen_instr("setrvR");
										break;
				default:				break;
			}
			break;
		default: 
			break;
	}
	code_generator.gen_instr("returnf");
}
ReturnPacket* Compiler::block32_stmt_while_source(){
	ReturnPacket* inPacket{new ReturnPacket{}};
		inPacket->m_pair.one=  othercounter;
		othercounter++;
		inPacket->m_pair.two =  othercounter;
		othercounter++;

		code_generator.gen_label(code_generator.genlabelw("",inPacket->m_pair.one));
		return inPacket;
}
 void Compiler::block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket){
	variableFetchWithNumericCheck(inexprPacket,true);
	code_generator.gen_instr_S("jumpz", code_generator.genlabelw("",insourcePacket->m_pair.two));
}

 void Compiler::block34_5_stmt_helper(int one, int two){
	code_generator.gen_instr_S("jump", code_generator.genlabelw("",one));
	code_generator.gen_label(code_generator.genlabelw("",two));
}
void Compiler::while_and_if_reducer(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket, int number, std::string while_or_if){
	ReturnPacket* inPacket{inexprPacket};
	if(! inPacket->getnumeric()){
		error("non numeric expression in " + while_or_if + " statement","");
		return;
	}
	else if(inPacket->gettype() != ucc::type::INT){
		error("expression in " + while_or_if + " statement is not an integer","");
		return;
	}
	if(while_or_if == "while"){
		block34_5_stmt_helper(insourcePacket->m_pair.one,insourcePacket->m_pair.two);
	}
	else{
		code_generator.gen_label(code_generator.genlabelw("",number));
	}
}
 void Compiler::block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt(ReturnPacket* insourcePacket, ReturnPacket* inexprPacket){
	while_and_if_reducer(insourcePacket,inexprPacket,0,"while");
}

 void Compiler::block35_stmt_ifexprstmt_else(ReturnPacket* insourcePacket){
	block34_5_stmt_helper(insourcePacket->m_pair.two,insourcePacket->m_pair.one);
}

 void Compiler::block36_7_stmt_helper(ReturnPacket* insourcePacket, int number){
	while_and_if_reducer(nullptr,insourcePacket,number,"if"); //FIXME: need to acutally put in a value perhaps for inexprPacketptr
}

 void Compiler::block36_stmt_ifexprstmt_else_source_stmt(ReturnPacket* inPacket){
	block36_7_stmt_helper(inPacket,inPacket->m_pair.two);
}

 void Compiler::block37_stmt_ifexprstmt(ReturnPacket* inPacket){
	block36_7_stmt_helper(inPacket,inPacket->m_pair.one);
}

struct Pair Compiler::block38_ifexprstmt_if_lpar_expr_source(ReturnPacket* inexprPacket){
//	ReturnPacket* inexprPacket{*inexprPacketptr};

	struct Pair rvalue;
	
	rvalue.one= othercounter;
	othercounter++;
	rvalue.two= othercounter;
	othercounter++;

	variableFetchWithNumericCheck(inexprPacket,true);
	code_generator.gen_instr_S("jumpz", code_generator.genlabelw("",rvalue.one));
	return rvalue;
}
/*
void Compiler::block39_ifexprstmt_if_lpar_expr_source_rpar_stmt(){
	$$.lval=$3->lval; $$.numeric=$3->numeric; $$.ttype = $3->type; $$.one = $4.one; $$.two=$4.two;
}
*/
void Compiler::normalStore(ucc::type intype){
	switch(intype){
		case(ucc::type::INT):	code_generator.gen_instr("storeI");
										break;
		case(ucc::type::FLOAT):	code_generator.gen_instr("storeR");
										break;
		default:						break;
	}
}
void Compiler::variableStore(ucc::type intype){
	static std::string instruction{""};
	static std::string letter{""};
	switch(intype){
		case ucc::type::INT:
										instruction = "int";
										letter = "I";
										break;
		case ucc::type::FLOAT:
										instruction = "flt";
										letter = "R";
										break;
		default:
										break;
	}
	warning("expressons are of different type, data may be lost","");

	code_generator.gen_instr(instruction);
	code_generator.gen_instr("store" + letter);
}
ReturnPacket* Compiler::block40_expr_equalexpr_equal_equalexpr(ReturnPacket** inequalexprPacketptr,ReturnPacket** inotherequalexprPacketptr){
	ReturnPacket* outPacket{nullptr};
	ReturnPacket* inequalexprPacket{*inequalexprPacketptr};
	ReturnPacket* inotherequalexprPacket{*inotherequalexprPacketptr};

	if( ! inequalexprPacket->getlval() ){
		error("Cannot make assignment. Left hand side is not a correct lval","");
		return outPacket;
	}
	else if( ! inotherequalexprPacket->getnumeric() ){
		error("Cannot make assignment, Right hand side is not numeric.","");
		return outPacket;
	}
	variableFetchWithNumericCheck(inotherequalexprPacket,false); //conversion to integer not needed

	if( inequalexprPacket->gettype() == inotherequalexprPacket->gettype() ) {
		outPacket = new ReturnPacket{true,inequalexprPacket->gettype(),true,0};
		normalStore(inequalexprPacket->gettype());
	}
	else if(inequalexprPacket->gettype() == ucc::type::INT && 
				inotherequalexprPacket->gettype() == type::FLOAT){
		variableStore(ucc::type::INT);
		outPacket = new ReturnPacket{true,ucc::type::INT,true,0};
		
	}
	else if(inequalexprPacket->gettype() == ucc::type::FLOAT && 
				inotherequalexprPacket->gettype() == ucc::type::INT) {
		variableStore(ucc::type::FLOAT);
		outPacket = new ReturnPacket{true,ucc::type::FLOAT,true,0};
	}
	return outPacket;
}
/*
void Compiler::block41_expr_equalexpr(){
	$$ = (exprtype*) malloc(sizeof(exprtype));
	$$->lval = $1.lval; $$->numeric = $1.numeric; $$->type =$1.ttype;
}
*/

 void Compiler::block42_equalexpr_relexpr_eqop_source(ReturnPacket** relexprPacketptr){
	variableFetchWithNumericCheck(*relexprPacketptr,false);
}

ReturnPacket* Compiler::block43_equalexpr_relexpr_helper(ucc::eqtype ineqop, std::string need_letter_b){
	warning("expressons are of different type, data may be lost","");
	switch(ineqop){
		case eqtype::NEQ: 	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("neR");
									break;
		case eqtype::EQEQ: 	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("eqR");
									break;
		default:					break;
	}
	return new ReturnPacket{false,ucc::type::INT,true,0};

}
ReturnPacket* Compiler::block43_equalexpr_relexpr_eqop_source_relexpr(ucc::eqtype ineqop, ReturnPacket** relexprPacketptr, ReturnPacket** otherrelexprPacketptr){
	ReturnPacket * outPacket{new ReturnPacket{}};
	ReturnPacket * relexprPacket{* relexprPacketptr};
	ReturnPacket * otherrelexprPacket{* otherrelexprPacketptr};

	variableFetchWithNumericCheck(*otherrelexprPacketptr,false);
	outPacket->setlval(false);
	if(relexprPacket->getnumeric() && otherrelexprPacket->getnumeric() ){
		outPacket->setnumeric(true);
		outPacket->settype(ucc::type::INT);
		if( relexprPacket->gettype() == otherrelexprPacket->gettype() ){
			outPacket->settype( ucc::type::INT);
			switch(ineqop){
				case eqtype::NEQ:	
										if(relexprPacket->gettype() == ucc::type::INT)
											code_generator.gen_instr("neI");
										else if(relexprPacket->gettype() == ucc::type::FLOAT)
											code_generator.gen_instr("neR");
										break;
				case eqtype::EQEQ: if(relexprPacket->gettype() == ucc::type::INT)
											code_generator.gen_instr("eqI");
										else if(relexprPacket->gettype() == ucc::type::FLOAT)
											code_generator.gen_instr("eqR");
										break;
				default:				break;
			}
		}
		else if(relexprPacket->gettype() == ucc::type::INT && 
						otherrelexprPacket->gettype()== ucc::type::FLOAT){
			outPacket = block43_equalexpr_relexpr_helper(ineqop,"b");
		}
		else if(relexprPacket->gettype() == ucc::type::FLOAT && 
					otherrelexprPacket->gettype() == ucc::type::INT) {
			outPacket = block43_equalexpr_relexpr_helper(ineqop,"");
		}
	}
	else{
		error("non numeric in operation","");
		outPacket->setnumeric(false);  //should be false right?
	}
	return outPacket;
}
/*
void Compiler::block44_equalexpr_relexpr(){
$$.lval = $1.lval; $$.ttype = $1.ttype; $$.numeric= $1.numeric;
}
*/
 void Compiler::block45_relexpr_simpleexpr_relop_source(ReturnPacket** insimplePacketptr){
	variableFetchWithNumericCheck(*insimplePacketptr,false);
}
ReturnPacket* Compiler::block46_relexpr_simpleexpr_relop_helper(ucc::reltype inrelop, std::string need_letter_b){
	warning("expressons are of different type, data may be lost","");
//	ReturnPacket * outPacket{new ReturnPacket{}};
//	outPacket->settype( ucc::type::INT);
	switch(inrelop){
		case reltype::LES:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("ltR");
									break;
		case reltype::LEQ:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("leR");
									break;
		case reltype::GRE:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("gtR");
									break;
		case reltype::GEQ:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("geR");
									break;
		default:					break;
	}
	return new ReturnPacket{false,ucc::type::INT,true,0};
}
ReturnPacket* Compiler::block46_relexpr_simpleexpr_relop_source_simpleexpr(ReturnPacket** simpleexprPacketptr, ucc::reltype inrelop, ReturnPacket** othersimpleexprPacketptr){
	ReturnPacket * outPacket{new ReturnPacket{}};
	ReturnPacket * simpleexprPacket{*simpleexprPacketptr};
	ReturnPacket * othersimpleexprPacket{*othersimpleexprPacketptr};
	
	variableFetchWithNumericCheck(*othersimpleexprPacketptr,false);
	outPacket->setlval(false);
	if(simpleexprPacket->getnumeric() && othersimpleexprPacket->getnumeric() ){
		outPacket->setnumeric(true);
		outPacket->settype( ucc::type::INT);
		if( simpleexprPacket->gettype() == othersimpleexprPacket->gettype() ) {
			outPacket->settype( ucc::type::INT);
			switch(inrelop){
				case reltype::LES:	if(simpleexprPacket->gettype() == type::INT) 
												code_generator.gen_instr("ltI");
											else if(simpleexprPacket->gettype() == type::FLOAT)
												code_generator.gen_instr("ltR");
											break;
				case reltype::LEQ:	if(simpleexprPacket->gettype() == type::INT)
												code_generator.gen_instr("leI");
											else if(simpleexprPacket->gettype() == type::FLOAT)
												code_generator.gen_instr("leR");
												break;
				case reltype::GRE:	if(simpleexprPacket->gettype() == type::INT)
												code_generator.gen_instr("gtI");
											else if(simpleexprPacket->gettype() == type::FLOAT)
												code_generator.gen_instr("gtR");
												break;
				case reltype::GEQ:	if(simpleexprPacket->gettype() == type::INT)
												code_generator.gen_instr("geI");
											else if(simpleexprPacket->gettype() == type::FLOAT)
												code_generator.gen_instr("geR");
												break;
				default:					break;
			}
		}
		else if(simpleexprPacket->gettype() == ucc::type::INT && 
					othersimpleexprPacket->gettype() == type::FLOAT){
			outPacket = block46_relexpr_simpleexpr_relop_helper(inrelop,"b");
		}
		else if(simpleexprPacket->gettype() == type::FLOAT && 
					othersimpleexprPacket->gettype() == type::INT) {
			outPacket = block46_relexpr_simpleexpr_relop_helper(inrelop,"");
		}
	}
	else{
		error("non numeric in operation","");
		outPacket->setnumeric(false);
	}
	return outPacket;
}
/*
void Compiler::block47_relexpr_simpleexpr(){
		$$.lval = $1.lval; $$.ttype = $1.ttype; $$.numeric=$1.numeric;
}
*/
void Compiler::variableFetchWithNumericCheckAndLvalCheck(ReturnPacket* insimplePacket, bool conversionNeeded){
	if(insimplePacket->getlval()){
		variableFetchWithNumericCheck(insimplePacket,conversionNeeded);
	}
}

 void Compiler::block48_simpleexpr_simpleexpr_addop_source(ReturnPacket** insimplePacketptr){
	variableFetchWithNumericCheckAndLvalCheck(*insimplePacketptr,false);
}
ReturnPacket* Compiler::block49_simpleexpr_addop_helper(ucc::addtype inaddop,std::string need_letter_b){
	warning("expressons are of different type, data may be lost","");
//	ReturnPacket* outPacket{new ReturnPacket{}};
//	outPacket->settype( ucc::type::FLOAT);
	switch(inaddop){
		case addtype::PLS:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("addR");
									break;
		case addtype::MIN:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("subR");
									break;
		default:					break;
	}
	return new ReturnPacket{false,ucc::type::FLOAT,true,0};
}

ReturnPacket* Compiler::block49_simpleexpr_simpleexpr_addop_source_term(ReturnPacket** simpleexprPacketptr, ucc::addtype inaddop, ReturnPacket** termPacketptr){
	ReturnPacket * outPacket{new ReturnPacket{}};
	ReturnPacket * simpleexprPacket{*simpleexprPacketptr};
	ReturnPacket * termPacket{*termPacketptr};

	variableFetchWithNumericCheck(*termPacketptr,false);
	outPacket->setlval(false);
	if(simpleexprPacket->getnumeric() && termPacket->getnumeric()){
		outPacket->setnumeric(true);
		if( simpleexprPacket->gettype() == termPacket->gettype() ){
			outPacket->settype( simpleexprPacket->gettype());
			switch(inaddop){
				case addtype::PLS:	if(simpleexprPacket->gettype() == type::INT)
												code_generator.gen_instr("addI");
											else if(simpleexprPacket->gettype() == type::FLOAT)
												code_generator.gen_instr("addR");
											break;
				case addtype::MIN:	if(simpleexprPacket->gettype() == type::INT)
												code_generator.gen_instr("subI");
											else if(simpleexprPacket->gettype() == type::FLOAT)
												code_generator.gen_instr("subR");
											break;
				default:					break;
			}
		}
		else if(simpleexprPacket->gettype() == ucc::type::INT 
			&& termPacket->gettype() == type::FLOAT){
				outPacket = block49_simpleexpr_addop_helper(inaddop,"b");
		}
		else if(simpleexprPacket->gettype() == ucc::type::FLOAT 
			&& termPacket->gettype() == type::INT) {
				outPacket = block49_simpleexpr_addop_helper(inaddop,"");
		}
	}
	else{
		error("non numeric in operation","");
		outPacket->setnumeric(false);
	}
	return outPacket;
}
/*
void Compiler::block50_simpleepr_term(){
	$$.lval = $1.lval; $$.ttype = $1.ttype; $$.numeric = $1.numeric; 
}
*/
 void Compiler::block51_term_term_mulop_source(ReturnPacket** inPacketptr){
	variableFetchWithNumericCheckAndLvalCheck(*inPacketptr,false);
}

ReturnPacket* Compiler::block52_term_mulop_helper(ucc::multype inmulop,std::string need_letter_b){
	warning("expressons are of different type, data may be lost","");
//	ReturnPacket *outPacket{new ReturnPacket{}};
//	outPacket->settype(type::FLOAT);
	switch(inmulop){
		case multype::DIV:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("divR");
									break;
		case multype::MULT:	code_generator.gen_instr("flt" + need_letter_b);
									code_generator.gen_instr("mulR");
									break;
		default:					break;
	}
	return new ReturnPacket{false,ucc::type::FLOAT,true,0};
}
ReturnPacket* Compiler::block52_term_term_mulop_source_factor(ReturnPacket** intermPacketptr, ucc::multype inmulop,ReturnPacket** infactorPacketptr){
	ReturnPacket* outtermPacket{new ReturnPacket{}};
	ReturnPacket* intermPacket{*intermPacketptr};
	ReturnPacket* infactorPacket{*infactorPacketptr};
	variableFetchWithNumericCheck(*infactorPacketptr,false);
	outtermPacket->setlval(false);
	if(intermPacket->getnumeric() && infactorPacket->getnumeric()){
		outtermPacket->setnumeric(true);
		if( intermPacket->gettype() == infactorPacket->gettype() ) {
			outtermPacket->settype(  intermPacket->gettype() );
			switch(inmulop){
				case multype::DIV:
									if(intermPacket->gettype()== type::INT){
										code_generator.gen_instr("divI");
									}
									else if(intermPacket->gettype()== type::FLOAT){
										code_generator.gen_instr("divR");
									}
									break;
				case multype::MULT:
									if(intermPacket->gettype()== type::INT){
										code_generator.gen_instr("mulI");
									}
									else if(intermPacket->gettype()== type::FLOAT){
										code_generator.gen_instr("mulR");
									}
									break;
				default:			break;
			}
		}
		else if(intermPacket->gettype() == type::INT 
					&& infactorPacket->gettype()== type::FLOAT){
			outtermPacket = block52_term_mulop_helper(inmulop,"b");
		}
		else if(intermPacket->gettype() == type::FLOAT && infactorPacket->gettype() == type::INT) {
			outtermPacket =  block52_term_mulop_helper(inmulop,"");
		}
	}
	else{
		error("non numeric in operation","");
		outtermPacket->setnumeric(false);
	}
	return outtermPacket;
}
/*
void Compiler::block53_term_factor(){
	$$.lval = $1.lval; $$.ttype = $1.ttype; $$ = $1; $$.numeric=$1.numeric;
}
*/
ReturnPacket* Compiler::block54_factor_constant(Constant** inConstant){
//	ReturnPacket* outPacket{new ReturnPacket{}};
//	outPacket = (*inConstant);
//	(*outPacket)->setlval(false); 

	switch((*inConstant)->gettype()){
		case type::INT:
			code_generator.gen_instr_I("pushcI",dynamic_cast<IntConstant*>(*inConstant)->getvalue());
			break;
		case type::FLOAT:
			code_generator.gen_instr_F("pushcR",dynamic_cast<FloatConstant*>(*inConstant)->getvalue());
			break;
		case type::STR:
			code_generator.gen_instr_S("pushs",dynamic_cast<StrConstant*>(*inConstant)->getvalue());
			break;
		default:
			error("constant is not a correct type of constant","");
			break;
	}
	return (*inConstant);;
}

ReturnPacket* Compiler::block55_factor_ident(ucc::Identifier inIdent){
	ReturnPacket* outPacket{nullptr};
	TableEntry *resultLookup;
	outPacket = new Identifier{inIdent};
		if(inIdent.getvalue() != "main"){
				#ifdef DEBUG
//				fprintf(stderr,"the name of the identifier here is:  %s\n", (char*)$<value.svalue>1);
				#endif
				
			if( (resultLookup =  mysymtab->lookupB(inIdent.getvalue())) != nullptr ){
				outPacket->settype(resultLookup->getBinding()->gettype());
				outPacket->setlval(true);
				if(resultLookup->getBinding()->gettype() == type::INT || resultLookup->getBinding()->gettype() == type::FLOAT){
					 outPacket->setnumeric(true);
				 }
				if(mysymtab->inCscope(inIdent.getvalue())){
					code_generator.gen_instr_I("pusha", resultLookup->getBinding()->getoffset());
				}
				else{
					switch(resultLookup->getself()){
						case btype::VAR:
					    {
							#ifdef DEBUG
//							char temp_char = (char)(*outPacket)->gettype();
//							if((*outPacket)->gettype() !=  nullptr) fprintf(stderr,"type is: %s\n", &temp_char);
//							if(resultLookup->getBinding()->gettype() != nullptr) fprintf(stderr,"type is: %d\n", resultLookup->getBinding()->gettype());
							#endif
							int level_diff{mysymtab->getleveldif(inIdent.getvalue())};
							if(level_diff != -1){
								code_generator.gen_instr_tI("pushga",level_diff,resultLookup->getBinding()->getoffset());
							}
							else{
								debugprint("error, somehow level difference was -1\n","");
							}
					    }
							break;

						case btype::PARAM:
							#ifdef DEBUG
						   std::cerr << "type is: " <<  (int)outPacket->gettype() << std::endl ;
							#endif

							break;
						default:
							error("Variable is unknown or undelcared","");
							break;
					}
				}
			}
			else{
				outPacket->settype(type::VOID);
				error("Variable is unknown or undelcared, couldn't be found in symbol table'","");
			}
//			return outPacket;
		}
		else{
			error("Main is not a variable name","");
		}
		return outPacket;
}
/*
void Compiler::block56_factor_lpar_expr_rpar(ReturnPacket** outPacket, ReturnPacket** inPacket){
	(*outPacket) = (*inPacket);
}
*/
ReturnPacket* Compiler::block57_factor_addop_factor_uminus(ucc::addtype inop, ReturnPacket** inPacketptr){
	ReturnPacket* outPacket{new ReturnPacket{}};
	ReturnPacket* inPacket{*inPacketptr};
	if(inPacket->getnumeric()){
		switch(inop){
			case ucc::addtype::MIN:
					variableFetchWithNumericCheck(*inPacketptr,false);
					switch(inPacket->gettype()){
						case type::INT:	code_generator.gen_instr("negI");
												break;
						case type::FLOAT:	code_generator.gen_instr("negR");
												break;
						default:				break;
					}
												break;
			case ucc::addtype::PLS:
					variableFetchWithNumericCheck(*inPacketptr,false);
												break;
			default:							break;
		}
	}
		outPacket->setlval(false);
		outPacket->settype(inPacket->gettype() );
		if(inPacket->getnumeric()){
			outPacket->setnumeric(true);
		}
		else{
			error("cannot change sign of non numeric expression","");
		}
		return outPacket;
}

ReturnPacket* Compiler::block58_factor_adof_ident(ucc::Identifier inPacket){
	ReturnPacket* outPacket{new ReturnPacket{}};
	TableEntry*tempE; //, *tempE2;
	if( inPacket.getvalue() != "main"){
		if( mysymtab->lookup(inPacket.getvalue()) == nullptr)
		error("variable undeclared, please declare variables before using them","");
		else{
//			tempE2 = new TableEntry{inPacket.getvalue()};
			tempE =	mysymtab->lookupB(inPacket.getvalue());
			if(tempE != nullptr){
				if(tempE->getself() == btype::VAR || tempE->getself() == btype::PARAM){
					switch(tempE->getself()){
						case btype::VAR:
						outPacket->settype(((Varb*)(tempE->getBinding()))->gettype());
						#ifdef DEBUG
//						std::cerr << "type is: "  << (int)outPacket->gettype()) << std::endl;
						#endif
						outPacket->setlval(false);
						if(((Varb*)(tempE->getBinding()))->gettype() == type::INT || ((Varb*)(tempE->getBinding()))->gettype() == type::FLOAT)
						outPacket->setnumeric(true);
						if(mysymtab->inCscope(inPacket.getvalue())){
							code_generator.gen_instr_I("pusha", ((Varb*)(tempE->getBinding()))->getoffset());
						}
						else{
							int level_diff{mysymtab->getleveldif(inPacket.getvalue())};
							if(level_diff != -1){
								code_generator.gen_instr_tI("pushga", level_diff,((Varb*)(tempE->getBinding()))->getoffset());
							}
							else{
								debugprint("error level differince was -1\n","");
							}
							//do something else
						}
							break;
						case btype::PARAM:
						outPacket->settype( ((Paramb*)(tempE->getBinding()))->gettype());
						#ifdef DEBUG
//						std::cerr <<  "type is: " <<  (int)outPacket->gettype()) << std::endl;
						#endif
						outPacket->setlval(false);
						if(((Paramb*)(tempE->getBinding()))->gettype() == type::INT || ((Paramb*)(tempE->getBinding()))->gettype() == type::FLOAT)
						outPacket->setnumeric(true);
						if(mysymtab->inCscope(inPacket.getvalue())){
							code_generator.gen_instr_I("pusha", ((Varb*)(tempE->getBinding()))->getoffset());
						}
						else{
							//do something else
						}
						break;
						default:	break;
					}
				}
				else
				error("Variable is unknown or undelcared", "");
			}
			else{
				outPacket->setlval(false);
				outPacket->setnumeric(false);
				outPacket->settype(type::VOID);
				error("Variable is unknown or undelcared","");
			}
		}
		return outPacket;
	}
	else{
		error("Main is not a variable name", "");

	}
	return outPacket;
}
/*
void Compiler::block59_factor_function_call(){
	(*outPacket)->ttype = $1.ttype; (*outPacket)->lval = false; (*outPacket)->numeric=$1.numeric; 
}
*/
ReturnPacket* Compiler::block60_function_call_ident_lpar_rpar(ucc::Identifier inIdent){
	ReturnPacket* outPacket{new ReturnPacket{}};
	outPacket->setlval(false);
	Funcb* tempb;
	TableEntry* tempE;
	TableEntry*tempE2;
	if((tempb=(Funcb*) mysymtab->lookup(inIdent.getvalue())) == nullptr){
		error("function undeclared, please declare functions before using them","");
	}
	else{
		tempE2 = new TableEntry{inIdent.getvalue()};
		tempE =	mysymtab->lookupB(inIdent.getvalue());
		if( tempE !=nullptr){
			if(tempE->getself() == btype::FUNC){
				if(tempb->getreturntype() != type::VOID){
					outPacket->setlval(true);
				}
				else{
					outPacket->setlval(false);
				}
				if(tempb->getnum_param() > 1 ){
				    error("Function takes no parameters, only void in the declaration and definition","");
				}
			    if(tempb->getnum_param() == 1){
				   if(tempb->getparam_type()[0] != ucc::type::VOID){
					  error("Function takes no parameters, only void in the declaration and definition","");
				   }
			    }
				outPacket->settype( tempb->getreturntype());
				if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT){
					outPacket->setnumeric(true);
				}
				else{
					outPacket->setnumeric(false);
				}
				code_generator.gen_instr_I("enter",1);
				code_generator.gen_call(code_generator.genlabelw(inIdent.getvalue(), tempb->getlabel()), 0);
			}
			else{
				error("Function call with an unknown function name", "");
			}
		}
		else{
			error("fuction undeclared","");
		}
		delete tempE2;
		tempE2=nullptr;
		return outPacket;
	}
	return outPacket;
}
/*
void Compiler::block61_function_call_func_call_with_params(){
	(*outPacket)->ttype =$1.ttype; (*outPacket)->numeric = $1.numeric; (*outPacket)->lval = $1.lval;
}
*/
ReturnPacket* Compiler::block62_func_call_with_params_name_and_params_rpar(ReturnPacket** nameAndparamptr){
	ReturnPacket* funcCallWparam{new ReturnPacket{}};
	funcCallWparam->setnumeric((* nameAndparamptr)->getnumeric());
	funcCallWparam->setlval(false);
	funcCallWparam->settype((* nameAndparamptr)->gettype());
	if((* nameAndparamptr)->funcent!=nullptr){
		if(((* nameAndparamptr)->funcent)->getself() == btype::FUNC){
			if( ((Funcb*)(((* nameAndparamptr)->funcent)->getBinding()))->getreturntype() != type::VOID){
				funcCallWparam->setnumeric(true);
			}
			else{
				funcCallWparam->setnumeric(false);
			}
		}
		if( "scanf" == (*nameAndparamptr)->funcent->getName()){
			code_generator.gen_call("$scanf",(*nameAndparamptr)->params);
		}
		else if("printf" ==  (*nameAndparamptr)->funcent->getName()){
			code_generator.gen_call("$printf",(*nameAndparamptr)->params);
		}
		else{
			if( ((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->getlabel()==0){
				((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->setlabel(code_generator.getlabel());
			}
			code_generator.gen_call( code_generator.genlabelw((*nameAndparamptr)->funcent->getName(),
				((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->getlabel()),
				((Funcb*)((*nameAndparamptr)->funcent->getBinding()))->getnum_param());
		}
	}
	return funcCallWparam;
}

ReturnPacket* Compiler::block63_name_and_params_ident_lpar_source(ucc::Identifier inPacket){
	ReturnPacket* inEntry{new ReturnPacket{}};
	/*
    if( *inEntryptr == nullptr){
	   error("name and params is null","");
	   return;
    }*/
	inEntry->funcent = nullptr;
	inEntry->funcent =  mysymtab->lookupB(inPacket.getvalue());
	#ifdef DEBUG
	//	printTree(mysymtab);
//	std::cerr <<  "this the name of function called and the lookup value: "  << inPacket.getvalue().c_str()) << std::endl;
	if( mysymtab->lookupB(inPacket.getvalue())==nullptr)
		std::cerr <<  "it was null\n";
	else
		std::cerr << "wasn't null\n";
	#endif
	if (inEntry->funcent != nullptr){
		inEntry->funcent->setName(inPacket.getvalue());
		code_generator.gen_instr_I("enter",1);
	}
	return inEntry;
}

ReturnPacket* Compiler::block64_name_and_params_ident_lpar_source_expr(ucc::Identifier inIdent, ReturnPacket** inEntryptr, ReturnPacket** inPacketptr){
	TableEntry*tempE, *tempE2;
	ReturnPacket* outPacket{new ReturnPacket{}};
	ReturnPacket* inPacket{*inPacketptr};
	ReturnPacket* inEntry{*inEntryptr};
	outPacket->setlval(false);
	Funcb* tempB;
	tempB = (Funcb*) mysymtab->lookup(inIdent.getvalue());
	if(tempB ==nullptr){
		error("function undelcared, please declare functions before using them","");
		error("1","");
		outPacket->funcent=nullptr;
	}
	else {
		//warning("just checking value of entry: %s",$<value.funcentvalue>$->name);
		tempE2 = new TableEntry{inIdent.getvalue()};
		tempE = mysymtab->lookupB(inIdent.getvalue());
		if( tempE !=nullptr){
			if(tempE->getself() != btype::FUNC){
				error("function undeclared, please declare functions before using them", "");
				error("2","");
				outPacket->funcent=nullptr;
			}
			else{
				if(tempB->getnum_param() ==0){
					error("Paramter given for a function that takes no parameters.","");
				}
				else if(tempB->getnum_param() == -1){
					#ifdef DEBUG
//					fprintf(stderr,"SPRINTF OR PRINTF mismatch: FUNCTION NAME: %s\n",$1);
	//				fprintf(stderr,"SPRINTF OR PRINTF: FUNCTION TYPE: %d\n",(int)$4->type);
//					fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
//					fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
//					fprintf(stderr,"SPRINTF OR PRINTF: $4 TYPE: %d\n",(int)$4->type);
//					fprintf(stderr,"SPRINTF OR PRINTF: tempB->param_type[0] TYPE: %d\n",(int)tempB->param_type[0]);
					#endif
					if(inPacket->gettype() != tempB->getparam_type()[0]){
						error("parameter type is different in declaration and in function call","");
					}
					else{
//							code_generator.gen_instr_S("pushs",$<value.svalue>4);
					}
					outPacket->settype(tempB->getparam_type()[0]);
					if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT){
						outPacket->setnumeric(true);
					}
					else{
						outPacket->setnumeric(false);
					}
					outPacket->funcent = inEntry->funcent;
					outPacket->params = 1;
				}
				else{
					variableFetchWithNumericCheck(inPacket,false);
					/*
					if(inPacket->getlval()  && inPacket->getnumeric()){
						switch(inPacket->gettype()){
							case type::INT:	code_generator.gen_instr("fetchI");
													break;
							case type::FLOAT:	code_generator.gen_instr("fetchR");
													break;
							default:				break;
						}
						}*/
					if( ! tempB->getparam_type().empty()){
						if(inPacket->gettype() != tempB->getparam_type()[0]){
							#ifdef DEBUG
//							fprintf(stderr,"Function mismatch 2: FUNCTION NAME: %s\n",$1);
//							fprintf(stderr,"Function mismatch 2: FUNCTION TYPE: %d\n",(int)$4->type);
//							fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
//							fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
							#endif
							if(tempB->getparam_type()[0]!= type::INT && tempB->getparam_type()[0]!= type::FLOAT)
							error("Parameter type is different in declaration and in function call","");
							else if(tempB->getparam_type()[0]== type::INT){
								#ifdef DEBUG
//								fprintf(stderr,"Function mismatch 3: FUNCTION NAME: %s\n",$1);
//								fprintf(stderr,"Function mismatch 3: FUNCTION TYPE: %d\n",(int)$4->type);
//								fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
//								fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
								#endif
								switch(inPacket->gettype()){
									case type::FLOAT:
															warning("Paramter expression will lose data because of different type","");
															code_generator.gen_instr("int");
															break;
									case type::INT:	break;
									default:				error("Parameter type is different in declaration and function call","");
															break;
								}
							}
							else if(tempB->getparam_type()[0]== type::FLOAT){
								#ifdef DEBUG
//								fprintf(stderr,"Function mismatch 4: FUNCTION NAME: %s\n",$1);
								#endif
								switch(inPacket->gettype()){
									case type::INT:	warning("Parameter expression is different type than in declaration","");
															code_generator.gen_instr("flt");
															break;
									case type::FLOAT:	break;
									default:				error("Parameter type is different in declaration and function call","");
															break;
								}
							}
						}
					}
					outPacket->funcent=inEntry->funcent;
					if(! tempB->getparam_type().empty())
						outPacket->settype(tempB->getparam_type()[0]);
					if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT)
						outPacket->setnumeric(true);
					else
						outPacket->setnumeric(false);
					outPacket->params=1;
				}
			}
		}
		else{
			error("Function is undeclared","");
		}
		delete tempE2;
		tempE2=nullptr;
	}
	return outPacket;
}

ReturnPacket* Compiler::block65_name_and_params_name_and_params_comma_expr(ReturnPacket** innameAndparamPacketptr, ReturnPacket** inexprPacketptr){
	ReturnPacket* outPacket{new ReturnPacket{}};
	ReturnPacket* innameAndparamPacket{*innameAndparamPacketptr};
	ReturnPacket* inexprPacket{*inexprPacketptr};
	
	TableEntry*tempE, *tempE2;
	outPacket->setlval( false);
	Funcb* tempB;
	if(innameAndparamPacket->funcent == nullptr){
		error("function undelcared, please declare functions before using them","");
		error("3","");
	}
	else {
		outPacket->funcent = innameAndparamPacket->funcent;
		tempE2 = new TableEntry{innameAndparamPacket->funcent->getName()};
		//	tempE2->name = innameAndparamPacket->funcent->name;
		tempB= (Funcb*) mysymtab->lookup( innameAndparamPacket->funcent->getName());
		if( (tempE=  mysymtab->lookupB(innameAndparamPacket->funcent->getName()))!=nullptr){
			if(tempE->getself() != btype::FUNC){
				error("function undeclared, please declare functions before using them", "");
				error("4","");
			}
			else{
				if(tempB->getnum_param() ==0){
				}
				else if(tempB->getnum_param() == -1){
					outPacket->settype( tempB->getparam_type()[innameAndparamPacket->params] );
					if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT){
						outPacket->setnumeric(true);
					}
					else{
						outPacket->setnumeric(false);
					}
					outPacket->params = innameAndparamPacket->params +1;
					outPacket->funcent= innameAndparamPacket->funcent;
					if(outPacket->funcent->getName() != "scanf"){
						variableFetchWithNumericCheck(inexprPacket,false);
					}
					/*
					if(inexprPacket->getlval() && inexprPacket->getnumeric() && "scanf" != outPacket->funcent->getName()){
						switch(inexprPacket->gettype()){
							case type::INT:		code_generator.gen_instr("fetchI");
														break;
							case type::FLOAT:		code_generator.gen_instr("fetchR");
														break;
							default:					break;
						}
					}
					*/
				}
				else if( innameAndparamPacket->params < tempB->getnum_param()){
					if(inexprPacket->gettype() != tempB->getparam_type()[innameAndparamPacket->params]){
						#ifdef DEBUG
//						fprintf(stderr,"Function mismatch before warning: FUNCTION NAME: %s\n", innameAndparamPacket->getname());
						#endif

						warning("Parameter type is different in declaration and in function call","");
						variableFetch(inexprPacket,false);
						/*
						if(inexprPacket->getlval()){
							switch(inexprPacket->gettype()){
								case type::INT:	code_generator.gen_instr("fetchI"); break;
								case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
								default:    break;
							}
						}
						*/
						if(tempB->getparam_type()[innameAndparamPacket->params]== type::FLOAT){
							code_generator.gen_instr("flt");
						}
						else if(tempB->getparam_type()[innameAndparamPacket->params]== type::INT){
							code_generator.gen_instr("int");
						}
					}
					else{
						variableFetch(inexprPacket,false);
					/*
						if(inexprPacket->getlval()){
							switch(inexprPacket->gettype()){
								case type::INT:	code_generator.gen_instr("fetchI"); break;
								case type::FLOAT:	code_generator.gen_instr("fetchR"); break;
								default:    break;
							}
						}
						*/

					}
					outPacket->settype( tempB->getparam_type()[innameAndparamPacket->params] );
					if(outPacket->gettype() == type::INT || outPacket->gettype() == type::FLOAT)
						outPacket->setnumeric(true);
					else
						outPacket->setnumeric(false);
					outPacket->params= innameAndparamPacket->params +1;
					outPacket->funcent= innameAndparamPacket->funcent;
				}
				else{
					error("Too many parameters given for function in function call.","");
				}
			}
		}
		else{
			error("Function is undeclared","");
		}
		delete tempE2;
		tempE2=nullptr;
	}
	return outPacket;
}/*
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
List* Compiler::block69_identlist_ident(ucc::Identifier inIdent){
	return List::mklist(&inIdent);
}

List* Compiler::block70_identlist_comma_ident(List** inIdentListptr, ucc::Identifier inIdent){
	return (*inIdentListptr)->appendList(&inIdent);
}

}
