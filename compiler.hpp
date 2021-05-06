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
	class Compiler{
		public:
			uccLexer	 				lexer;
			uccParser				parser;
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
			void block2_func_funcheader_source();
			void block3_func_funcheader_source_funcbody();
			void block4_func_funcheader_semi();
			void block5_funcheader_error_semi();
			void block6_funcheader_void_ident_lpar_paramdef_rpar();
			void block7_funcheader_int_ident_lpar_paramdef_rpar();
			void block8_funcheader_float_ident_lpar_paramdef_rpar();
			void block9_funcheader_void_error_rpar();
			void block10_funcheader_int_error_rpar();
			void block11_funcheader_float_error_rpar();
			void block12_funcheader_void_ident_lpar_error_rpar();
			void block13_funcheader_float_ident_lpar_error_rpar();
			void block14_funcheader_int_ident_lpar_error_rpar();
			void block15_paramdef_paramdeflist();
			void block15_paramdef_paramdeflist_comma_elip();
			void block16_paramdef_void();
			void block17_paramdef_paramdeflist_error_rpar();
			void block18_paramdef_paramdeflist_comma_error_rpar();
			void block19_paramdeflist_int_ident();
			void block20_paramdeflist_float_ident();
			void block21_paramdeflist_char_star_ident();
			void block22_paramdeflist_paramdeflist_comma_int_ident();
			void block23_paramdeflist_paramdeflist_comma_float_ident();
			void block24_paramdeflist_paramdeflist_comma_char_star_ident();
			void block25_funcbody_lcbra_decls_source();
			void block26_funcbody_lcbra_decls_source_stmtlist_rcbra();
			void block27_variabledecl_int_identlist_semi();
			void block28_variabledecl_float_identlist_semi();
			void block29_stmt_expr_semi();
			void block30_stmt_return_semi();
			void block31_stmt_return_expr_semi();
			void block32_stmt_while_source();
			void block33_stmt_while_source_expr_semi_source_lpar_expr_rpar();
			void block34_stmt_while_source_expr_semi_source_lpar_expr_rpar_source_stmt();
			void block35_stmt_ifexprstmt_else();
			void block36_stmt_ifexprstmt_else_source_stmt();
			void block37_stmt_ifexprstmt();
			void block38_ifexprstmt_if_lpar_expr_source();
			void block39_ifexprstmt_if_lpar_expr_source_rpar_stmt();
			void block40_expr_equalexpr_equal_equalexpr();
			void block41_expr_equalexpr();
			void block42_equalexpr_relexpr_eqop_source();
			void block43_equalexpr_relexpr_eqop_source_relexpr();
			void block44_equalexpr_relexpr();
			void block45_relexpr_simpleexpr_relop_source();
			void block46_relexpr_simpleexpr_relop_source_simpleexpr();
			void block47_relexpr_simpleexpr();
			void block48_simpleexpr_simpleexpr_addop_source();
			void block49_simpleexpr_simpleexpr_addop_source_term();
			void block50_simpleepr_term();
			void block51_term_term_mulop_source();
			void block52_term_term_mulop_source_factor();
			void block53_term_factor();
			void block54_factor_constant();
			void block55_factor_ident();
			void block56_factor_lpar_expr_rpar();
			void block57_factor_addop_factor_uminus();
			void block58_factor_adof_ident();
			void block59_factor_function_call();
			void block60_function_call_ident_lpar_rpar();
			void block61_function_call_func_call_with_params();
			void block62_func_call_with_params_name_and_params_rpar();
			void block63_name_and_params_ident_lpar_source();
			void block64_name_and_params_ident_lpar_source_expr();
			void block65_name_and_params_name_and_params_comma_expr();
			void block66_constant_strconstant();
			void block67_constant_intconstant();
			void block68_constant_floatconstant();
			void block69_identlist_ident();
			void block70_identlist_comma_ident();
			
			
			
			
			
			
			
			std::ostream*	outfile;
			std::string 	filename;
			int 				Line_Number;
			int 				globalcount;
			int				offset_counter;
			int				labelcounter;
			int 				othercounter;
			int 				param_offset;
			int 				mainlocal;

		protected:
			static bool endsWC(const std::string& in);

		private:
			bool 			founderror;
//			extern FILE*	infile;
//			Symtab*			mysymtab;
	};
}
#endif
