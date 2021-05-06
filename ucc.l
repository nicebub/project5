%option c++
%{
#include <cstdint>

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
#endif


#include "lex.hpp"

using namespace ucc;

#include "List.hpp"


#include "symtab.hpp"
#include "data.hpp"

//#define YYSTYPE data
#include "ucc.tab.hpp"

#include "lex.hpp"
#include "compiler.hpp"
#undef YY_DECL
#define YY_DECL int ucc::uccLexer::yylex(uccParser::semantic_type* const lval, uccParser::location_type* location)
using token = uccParser::token;
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);
//int Line_Number = 1;
%}

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
%{
	yylval = lval;
%}
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
	yylval->build<std::string>(string_buf);
	return(token::StrConstant);
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
	return(token::voidt);
	}

if {/* keyword if*/
	return(token::ift);
	}

return {/* keyword return*/
	return(token::returnt);
	}

else {/* keyword else*/
	return(token::elset);
	}


while {/*keyword while*/
	return(token::whilet);
	}

int { /*keyword int*/
//	yylval.ttype = type::INT;
	return(token::intt);
	}

float {/* keyword float*/
//	yylval.ttype = type::FLOAT;
	return(token::floatt);
	}

char { /* keyword char*/
//	yylval.ttype = type::CHAR;
	return(token::chart);
	}

\( {
	return(token::lpar);
	}

\) {
	return(token::rpar);
	}

\{ {
	return(token::lcbra);
	}

\} {
	return(token::rcbra);
	}

\; {
	return(token::semi);
	}

\, {
	return(token::comma);
	}

\< {	
//	yylval.value.relopvalue = reltype::LES;
	return(token::lesst);
	}

\> {	
//	yylval.value.relopvalue = reltype::GRE;
	return(token::greatt);
	}

\= {
	return(token::equalt);
	}

\+ {	
//	yylval.value.addopvalue = addtype::PLS;
	return(token::plus);
	}

\- {	
//	yylval.value.addopvalue = addtype::MIN;
	return(token::minus);
	}

\/ {	
//	yylval.value.multopvalue =multype:: DIV;
	return(token::divide);
	}
\* {	
//	yylval.value.multopvalue = multype::MULT;
	return(token::star);
	}

{GEQ} {		
//	yylval.value.relopvalue = reltype::GEQ;
		return(token::geq);
	}

{LEQ} {		
//	yylval.value.relopvalue = reltype::LEQ;
		return(token::leq);
	}

{NEQ} {		
//	yylval.value.eqopvalue = eqtype::NEQ;
		return(token::neq);
	}

{EQUEQU} {	
//	yylval.value.eqopvalue = eqtype::EQEQ;
		return(token::equequ);
	}

{ADOF} {
		return(token::adof);
	}

{BEGCOM} {
		BEGIN(comment);
	}

{LETTER}({LETTER}|{DIGIT})* 	{/* identifier*/
//				yylval.ttype = type::STR;
				std::string tempstr(yytext);
				yylval->build<std::string>(tempstr);
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
					yylval->build<float>(std::atof(yytext));
//					yylval.value.fvalue=(float)std::atof(yytext);
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
				yylval->build<int>(std::atoi(yytext));
//				yylval.value.ivalue =(int)std::atoi(yytext);
				return(token::IntConstant);
				}

{ELIP} {
	return(token::elip);
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
	return '\0';
	}

. 	{
	compiler.error("illegal character: %s",yytext);
	}

%%