%option c++
%{
#include <cstdint>

#include "debug.hpp"
#include "type.hpp"
#include "cpptypes.hpp"
#include "lex.hpp"
#include "list.hpp"
#include "symtab.hpp"
#include "data.hpp"

#undef YY_DECL
#define YY_DECL int uccLexer::yylex(uccParser::semantic_type* const lval, uccParser::location_type* location)

#include "ucc.tab.hpp"
#include "compiler.hpp"

using namespace ucc;


using token = uccParser::token;
#define YY_USER_ACTION loc->step(); loc->columns(yyleng); yylval = lval;

%}
%option noyywrap
%option stack
%option yylineno
%option yyclass="uccLexer"

%s	initial
%x	astring
%x	comment

DIGIT	[0-9]
LETTER	[A-Za-z\_]
SPACE	[ ]
EOLN	\\n
PERCENT	\%
QUESTION \?
NULLS	\\0
BEGCOM	"\/\*"
ENDCOM	"\*\/"
ELIP	"..."

EQUEQU	"=="
NEQ	"\!="
LEQ	"<="
GEQ	">="
ADOF	"&"


%%
<comment>{
[^*\n]*
[^*\n]*\n 	++compiler.Line_Number;
\*+[^*/\n]*
\*+[^*/\n]*\n 	++compiler.Line_Number;
{ENDCOM} {
		BEGIN(INITIAL);}
<<EOF>> {
	compiler.error("eof terminated comment","");
	BEGIN(INITIAL);
	}
}

<astring>{
\" {	BEGIN(INITIAL);
	
	yylval->emplace<ucc::StrConstant>() = string_buf;
	return(token::StrConstant);
	
//	return uccParser::make_StrConstant(string_buf,*loc);
	}
\n {	BEGIN(INITIAL);
	++compiler.Line_Number;
	compiler.error("unterminated string constant","");
	}

\\n {
	string_buf += "\\n";
}
\\\" {
	string_buf += "\\\"";
}

\\[^n\\\"] {
		int c;
		BEGIN(INITIAL);
		compiler.error("illegal character:%s in string",yytext);
		while(((c = yyinput()) != '\"') && (c != EOF)){
			;
		}
		if(c == EOF){
			compiler.error("eof terminated string","");
		}
		}

((\\\\{SPACE}+)*|[&@$\%^/,.+'-\[\]{}();~`|=#\!:<>]*|{LETTER}|{DIGIT}|{PERCENT}|{SPACE}|{BEGCOM}|{ENDCOM}|{QUESTION})* {
	char *yptr = yytext;
	while((*yptr != (int)NULL) && *yptr){
		string_buf += *yptr++;
	}
	}

<<EOF>> {
	compiler.error("eof terminated string","");
	BEGIN(INITIAL);
	}
}


void {/*keyword void*/
	return token::voidt;
//	return uccParser::make_voidt(0,*loc);
	}

if {/* keyword if*/
	return token::ift;
//	return uccParser::make_ift(0,*loc);
	}

return {/* keyword return*/
	return token::returnt;
//	return uccParser::make_returnt(*loc);
}

else {/* keyword else*/
	return token::elset;
//	return uccParser::make_elset(0,*loc);
	}


while {/*keyword while*/
	return token::whilet;
//	return uccParser::make_whilet(0,*loc);
	}

int { /*keyword int*/
//	yylval.ttype = type::INT;
	return token::intt;
//	return uccParser::make_intt(0,*loc);
}

float {/* keyword float*/
//	yylval.ttype = type::FLOAT;
	return token::floatt;
//	return uccParser::make_floatt(0,*loc);
	}

char { /* keyword char*/
//	yylval.ttype = type::CHAR;
	return token::chart;
//	return uccParser::make_chart(0,*loc);
	}

\( {
	return token::lpar;
//	return uccParser::make_lpar(0,*loc);
	}

\) {
	return token::rpar;
//	return uccParser::make_rpar(0,*loc);
	}

\{ {
	return token::lcbra;
//	return uccParser::make_lcbra(0,*loc);
	}

\} {
	return token::rcbra;
//	return uccParser::make_rcbra(0,*loc);
	}

\; {
	return token::semi;
//	return uccParser::make_semi(0,*loc);
	}

\, {
	return token::comma;
//	return uccParser::make_comma(0,*loc);
	}

\< {	
//	yylval.value.relopvalue = reltype::LES;
	return token::lesst;
//	return uccParser::make_lesst(reltype::LES,*loc);
	}

\> {	
//	yylval.value.relopvalue = reltype::GRE;
	return token::greatt;
//return uccParser::make_greatt(reltype::GRE,*loc);
	}

\= {
	return token::equalt;
//	return uccParser::make_equalt(0,*loc);
	}

\+ {	
//	yylval.value.addopvalue = addtype::PLS;
	return token::plus;
//	return uccParser::make_plus(addtype::PLS,*loc);
	}

\- {	
//	yylval.value.addopvalue = addtype::MIN;
		return token::minus;
//	return uccParser::make_minus(addtype::MIN,*loc);
	}

\/ {	
//	yylval.value.multopvalue = multype::DIV;
		return token::divide;
//		return uccParser::make_divide(multype::DIV,*loc);
	}
\* {	
//	yylval.value.multopvalue = multype::MULT;
		return token::star;
//		return uccParser::make_star(multype::MULT,*loc);
	}

{GEQ} {		
//	yylval.value.relopvalue = reltype::GEQ;
	return token::geq;
//	return uccParser::make_geq(reltype::GEQ,*loc);
	}

{LEQ} {		
//	yylval.value.relopvalue = reltype::LEQ;
	return token::leq;
//	return uccParser::make_leq(reltype::LEQ,*loc);
	}

{NEQ} {		
//	yylval.value.eqopvalue = eqtype::NEQ;
	return token::neq;
//	return uccParser::make_neq(eqtype::NEQ,*loc);
	}

{EQUEQU} {	
//	yylval.value.eqopvalue = eqtype::EQEQ;
	return token::equequ;
//	return uccParser::make_equequ(eqtype::EQEQ,*loc);
	}

{ADOF} {
	return token::adof;
//	return uccParser::make_adof(0,*loc);
	}

{BEGCOM} {
		BEGIN(comment);
	}

{LETTER}({LETTER}|{DIGIT})* 	{/* identifier*/
//				yylval.ttype = type::STR;
				std::string tempstr(yytext);
				yylval->emplace<ucc::Identifier>() = Identifier{tempstr};
//				return uccParser::make_Ident(tempstr,*loc);
				return(token::Ident);
				}

((0|([1-9]{DIGIT}*)))(while|if|void|return|char|int|float|else|for|extern) {
									compiler.error("illegal token: %s", yytext);
							}

((0|([1-9]{DIGIT}*))(\.{DIGIT}+))(while|if|void|return|char|int|float|else|for|extern) {
									compiler.error("illegal token: %s",yytext);
									}

(0|([1-9]{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) { /* bad form*/
						compiler.error("illegal token: %s", yytext);
						}

((0|([1-9]{DIGIT}*))(\.{DIGIT}{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) {/*bad form*/
							compiler.error("illegal token: %s",yytext);
							}



(0|([1-9]{DIGIT}*))\.{DIGIT}{DIGIT}* {/*float*/
//					yylval.ttype = type::FLOAT;
					yylval->emplace<float>() = std::atof(yytext);
//					yylval.value.fvalue=(float)std::atof(yytext);
//					return uccParser::make_FloatConstant((float)std::atof(yytext),*loc);
					return(token::FloatConstant);
					}

0{DIGIT}+\.{DIGIT}+		{/* bad float*/
					compiler.error("illegal float: %s",yytext);
				}


0{DIGIT}+	{/* bad integer*/
				compiler.error("illegal integer: %s", yytext);
		}

(0|([1-9]{DIGIT}*))		{/*integer constant*/
//				yylval.ttype = type::INT;
yylval = lval;
				yylval->emplace<int>() = std::atoi(yytext);
//				yylval.value.ivalue =(int)std::atoi(yytext);
//				return uccParser::make_IntConstant((int)std::atoi(yytext),*loc);
				return(token::IntConstant);
				}

{ELIP} {
	return token::elip;
//	return uccParser::make_elip(0,*loc);
}

\" {
	string_buf.clear();
	BEGIN(astring);
	}


\n	{
	++compiler.Line_Number;
	}

[ \t\r]+	{ /*eat up tabs, whitespace */
	}

<<EOF>> {

//	return uccParser::make_YYEOF(*loc);
	return '\0';
	}

. 	{
	compiler.error("illegal character: %s",yytext);
	}

%%