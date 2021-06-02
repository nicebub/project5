#include "helper.hpp"
#include "compiler.hpp"

namespace ucc{

	#define error_and_return_false(x) error((x),""); \
	return false

	void Compiler::install_parameters_into_symbol_table_curren_scope(funcheadertype** inFuncHeaderptr){
		funcheadertype* inFuncHeader{*inFuncHeaderptr};
		for(auto element : *inFuncHeader->paramlist){
			PListNode* nelement{dynamic_cast<PListNode*>(element)};
			auto tempEntry = mysymtab->createParam(nelement->getval(), nelement->gettype(),(offset_counter));
			mysymtab->install(tempEntry);
			offset_counter++;
		}
	}
	bool Compiler::is_function_decl_or_def_accurate(funcheadertype** inFuncHeaderptr, Funcb*& currentFunc, bool isdeclaration) {
		funcheadertype* inFuncHeader{*inFuncHeaderptr};
//		Funcb* currentFunc{};

		currentFunc = dynamic_cast<Funcb*>(mysymtab->lookup(inFuncHeader->name));
		auto foundPacket{mysymtab->lookupB(inFuncHeader->name)};
//		mysymtab->openscope();
		if(!foundPacket){
			error_and_return_false("Function name not in symbol mysymtab");
		}
		if(foundPacket->getself() != ucc::btype::FUNC){
			error_and_return_false("Not a function");
		}
		if(currentFunc->getreturntype() != inFuncHeader->returntype){
			error_and_return_false("Function declared with different return type");
		}
		if(currentFunc->getnum_param() == -1){
			error_and_return_false("Function cannot have those parameters");
		}
		if(inFuncHeader->paramlist != nullptr &&
			 (inFuncHeader->paramlist->size()) != currentFunc->getnum_param()){
	 		error_and_return_false("Function has different number of parameters");
		}
		int list_index{0};
		for(auto element : * inFuncHeader->paramlist){
			PListNode* nelement{dynamic_cast<PListNode*>(element)};
			if(currentFunc->getparam_type()[list_index] != nelement->gettype()){
				fprintf(stderr,"Error: Line: %d: argument %d: has different parameter type than in function declaration\n",Line_Number,(list_index+1));
				fprintf(stderr, "\nThey are %d and %d\n", currentFunc->getparam_type()[list_index], nelement->gettype());
				return false;
			}
			list_index++;
		}
		if(list_index != inFuncHeader->paramlist->size()){
	 		error_and_return_false("Stopped");
		}
		if(currentFunc->getbodydef() && ( ! isdeclaration) ){
	 		error_and_return_false("Function definition is previously declared");
		}

//		PListNode* tempnode{dynamic_cast<PListNode*>(*inFuncHeader->paramlist->begin())};

		#ifdef DEBUG
		if(tempnode->gettype() != type::VOID){
			fprintf(stderr,"in funcheader before funcbody, param val and type is ");
			//fprintf(stderr,"%s %s\n",tempnode->val,(char*)tempnode->ttype);
		}
		else{
			fprintf(stderr,"in funcheader before funcbody type is ");
			fprintf(stderr,"%s\n",(char*)tempnode->gettype());
		}
		#endif
		return true;
	}
	#undef error_and_return_false
}