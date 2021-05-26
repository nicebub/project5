#ifndef _COMPILER_HPP
#define _COMPILER_HPP
#include <string>
/*
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#define yyFlexLexer yyFlexLexer
#endif
*/
#include "type.hpp"
#include "trans.hpp"
#include "symtab.hpp"
#include "ucc.tab.hpp"
#include "lex.hpp"
//extern FILE* 						yyin;
//extern int error(std::string, std::string);


const int INITIAL_TREE_SIZE = 100;

namespace ucc{
	class SymbolTable;
	
	class Compiler{
		public:
			uccLexer	 				lexer;
			uccParser*				parser;
			CodeGenerator 			code_generator;
			SymbolTable* 			mysymtab;

			Compiler();
			Compiler(int argc, const char** argv);
			~Compiler();

			bool openOutputFile(int argc, const char** argv);
			int checkargs(int argc, const char** argv);

			 int error(std::string,std::string) noexcept;
			 int warning(std::string,std::string) noexcept;

			void block1_start_trans_unit();

			bool is_function_decl_or_def_accurate(funcheadertype** inFunc, Funcb*& currentFunc, bool isdeclaration);
			void install_parameters_into_symbol_table_curren_scope(funcheadertype** inFuncHeaderptr);

			void block2_func_funcheader_source(funcheadertype** funcheaderptr);
			void block3_func_funcheader_source_funcbody();
			void block4_func_funcheader_semi(funcheadertype** inFuncHeaderptr);

			void block5_funcheader_error_semi(funcheadertype** inFuncHeaderptr);

			void funcheader_returntype_ident_lpar_paramdef_rpar_helper(funcheadertype** outFuncHeaderptr, ucc::Identifier inIdent, List* inParamdeflist,ucc::type inreturntype);
			
			void block6_funcheader_void_ident_lpar_paramdef_rpar(funcheadertype** outFuncHeaderptr,ucc::Identifier ident, List* paramdeflist);
			void block7_funcheader_int_ident_lpar_paramdef_rpar(funcheadertype** outFuncHeaderptr,ucc::Identifier inIdent, List* inParamdeflist);
			void block8_funcheader_float_ident_lpar_paramdef_rpar(funcheadertype** outFuncHeaderptr, ucc::Identifier inIdent, List* inParamdeflist);
			void block9_funcheader_void_error_rpar(funcheadertype** outFuncHeaderptr);
			void block10_funcheader_int_error_rpar(funcheadertype** outFuncHeaderptr);
			void block11_funcheader_float_error_rpar(funcheadertype** outFuncHeaderptr);
			void block12_funcheader_void_ident_lpar_error_rpar(funcheadertype** outFuncHeaderptr, ucc::Identifier inIdent);
			void block13_funcheader_float_ident_lpar_error_rpar(funcheadertype** outFuncHeaderptr, ucc::Identifier inIdent);
			void block14_funcheader_int_ident_lpar_error_rpar(funcheadertype** outFuncHeaderptr, ucc::Identifier inIdent);

			void block15_paramdef_paramdeflist(List** outParamdefptr, List** inParamdeflistptr);
			void block15_paramdef_paramdeflist_comma_elip(List** outParamdefptr, List** inParamdeflistptr);
			void block16_paramdef_void(List** outParamdefptr);
			void block17_paramdef_paramdeflist_error_rpar(List** inParamdeflistptr);
			void block18_paramdef_paramdeflist_comma_error_rpar(List** inParamdeflistptr);

			void paramdeflist_type_ident_helper(List** outParamdeflistptr, ucc::Identifier inIdent, ucc::type intype);
			void block19_paramdeflist_int_ident(List** outParamdeflistptr, ucc::Identifier inIdent);
			void block20_paramdeflist_float_ident(List** outParamdeflistptr, ucc::Identifier inIdent);
			void block21_paramdeflist_char_star_ident(List** outParamdeflistptr, ucc::Identifier inIdent);

			void paramdeflist_paramdeflist_comma_type_ident_helper(List** outParamdeflistptr, List** inParamdeflistptr, ucc::Identifier inIdent, ucc::type intype);
			void block22_paramdeflist_paramdeflist_comma_int_ident(List** outParamdeflistptr, List** inParamdeflist, ucc::Identifier inIdent);
			void block23_paramdeflist_paramdeflist_comma_float_ident(List** outParamdeflistptr, List** inParamdeflist, ucc::Identifier inIdent);
			void block24_paramdeflist_paramdeflist_comma_char_star_ident(List** outParamdeflistptr, List** inParamdeflist, ucc::Identifier inIdent);

			void block25_funcbody_lcbra_decls_source();
			void block26_funcbody_lcbra_decls_source_stmtlist_rcbra();

			void block27_variabledecl_int_identlist_semi(List** inIdentlist);
			void block28_variabledecl_float_identlist_semi(List** inIdentlist);

			void block29_stmt_expr_semi();
			void block30_stmt_return_semi();
			void block31_stmt_return_expr_semi_helper(ReturnPacket* inPacket, bool conversionNeeded);
			void block31_stmt_return_expr_semi(ReturnPacket** inPacket);

			void variableFetchWithNumericCheck(ReturnPacket** inPacketptr, bool conversionNeeded);

			void block32_stmt_while_source(ReturnPacket** inPacket);
			void block33_stmt_while_source_expr_semi_source_lpar_expr_rpar(ReturnPacket** insourcePacketptr, ReturnPacket** inexprPacketptr);

			void block34_5_stmt_helper(int one, int two);

			void while_and_if_reducer(ReturnPacket** insourcePacketptr, ReturnPacket** inexprPacketptr, int number, std::string while_or_if);

			void block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt(ReturnPacket** insourcePacketptr, ReturnPacket** inexprPacketptr);
			void block35_stmt_ifexprstmt_else(ReturnPacket** insourcePacketptr);

			void block36_7_stmt_helper(ReturnPacket** inPacketptr, int number);

			void block36_stmt_ifexprstmt_else_source_stmt(ReturnPacket** inPacketptr);
			void block37_stmt_ifexprstmt(ReturnPacket** inPacketptr);

			struct Pair block38_ifexprstmt_if_lpar_expr_source(struct Pair* outPair, ReturnPacket** inexprPacketptr);
			void block39_ifexprstmt_if_lpar_expr_source_rpar_stmt();

			void block40_expr_equalexpr_helper(ReturnPacket** outPacketptr, ucc::type intype);
			void block40_expr_equalexpr_equal_equalexpr(ReturnPacket** outPacketptr, ReturnPacket** inequalexprPacketptr,ReturnPacket** inotherequalexprPacketptr);
			void block41_expr_equalexpr();

			void block42_equalexpr_relexpr_eqop_source(ReturnPacket** relexprPacketptr);

			void block43_equalexpr_relexpr_helper(ReturnPacket** outPacketptr, ucc::eqtype ineqop, std::string need_letter_b);

			void block43_equalexpr_relexpr_eqop_source_relexpr(ReturnPacket** outPacketptr, ucc::eqtype ineqop, ReturnPacket** relexprPacketptr, ReturnPacket** otherrelexprPacketptr);
			void block44_equalexpr_relexpr();

			void block45_relexpr_simpleexpr_relop_source(ReturnPacket** insimplePacketptr);
			
			void block46_relexpr_simpleexpr_relop_helper(ReturnPacket** outPacketptr, ucc::reltype inrelop, std::string need_letter_b);

			void block46_relexpr_simpleexpr_relop_source_simpleexpr(ReturnPacket** outPacketptr, ReturnPacket** simpleexprPacketptr, ucc::reltype inrelop, ReturnPacket** othersimpleexprPacketptr);
			void block47_relexpr_simpleexpr();

			void block48_simpleexpr_simpleexpr_addop_source(ReturnPacket** insimplePacketptr);

			void block49_simpleexpr_addop_helper(ReturnPacket** outPacketptr, ucc::addtype inaddop,std::string need_letter_b);

			void block49_simpleexpr_simpleexpr_addop_source_term(ReturnPacket** outPacketptr, ReturnPacket** simpleexprPacketptr, ucc::addtype inaddop, ReturnPacket** termPacketptr);
			void block50_simpleepr_term();

			void block51_term_term_mulop_source(ReturnPacket** inPacketptr);

			void block52_term_mulop_helper(ReturnPacket** outtermPacketptr, ucc::multype inmulop,std::string need_letter_b);

			void block52_term_term_mulop_source_factor(ReturnPacket** outermptr,ReturnPacket** intermptr, ucc::multype inmulop,ReturnPacket** infactorptr);
			void block53_term_factor();

			void block54_factor_constant(ReturnPacket** outPacket, Constant** inConstant);
			void block55_factor_ident(ReturnPacket** outPacket, ucc::Identifier inIdent);
			void block56_factor_lpar_expr_rpar(ReturnPacket** outPacket, ReturnPacket** inPacket);
			void block57_factor_addop_factor_uminus(ReturnPacket** outPacket,ucc::addtype inop, ReturnPacket** inPacket);
			void block58_factor_adof_ident(ReturnPacket** outPacket, ucc::Identifier inPacket);
			void block59_factor_function_call(ReturnPacket** outPacket,ReturnPacket** inPacket);

			void block60_function_call_ident_lpar_rpar(ReturnPacket** outPacket, ucc::Identifier inIdent);
			void block61_function_call_func_call_with_params();

			void block62_func_call_with_params_name_and_params_rpar(ReturnPacket** funcCallWparamptr, ReturnPacket** nameAndparamptr);

			void block63_name_and_params_ident_lpar_source(TableEntry** inEntryptr, ucc::Identifier inPacket);
			void block64_name_and_params_ident_lpar_source_expr(ReturnPacket** outPacketptr, TableEntry** inEntryptr, ReturnPacket** inPacketptr);
			void block65_name_and_params_name_and_params_comma_expr(ReturnPacket** outPacketptr, ReturnPacket** innameAndparamPacketptr, ReturnPacket** inexprPacketptr);

			void block66_constant_strconstant(ucc::ReturnPacket* mcon, std::string instrconstant);
			void block67_constant_intconstant(ucc::ReturnPacket* mcon, int intconstant);
			void block68_constant_floatconstant(ucc::ReturnPacket* mcon, float floatconstant);
			
			void block69_identlist_ident(List** outIdentListptr, ucc::Identifier inIdent);
			void block70_identlist_comma_ident(List** outIdentListptr, List** inIdentListptr, ucc::Identifier inIdent);
			
			
			
			
			
			
			Funcb*			currentFunc;
			std::ostream*	outfile;
			std::string 	filename;
			int 				Line_Number;
			int 				globalcount;
			int				offset_counter;
			int				labelcounter;
			int 				othercounter;
			int 				param_offset;
			int 				mainlocal;
			int 				mainlabel;

		protected:
			static bool endsWC(const std::string& in);

		private:
			bool 			founderror;
//			extern FILE*	infile;
//			Symtab*			mysymtab;
	};
}
#endif
