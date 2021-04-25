/*scott lorberbaum
   compilers spring 2004
	This file is the flex specificiation file for the uC language.  It will recognize and return all tokens and output if there are any ucc::errors.
*/
%{
#include <cstdint>

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
#endif

#include "List.hpp"

using namespace ucc;

#include "symtab.hpp"
#include "data.hpp"

#define YYSTYPE data
#include "ucc.tab.hpp"

#include "lex.hpp"
#include "compiler.hpp"

using namespace ucc;

Lex lexer{};
//int Line_Number = 1;
%}

%option stack
%option yylineno
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
[^*\n]*\n 	++Compiler::Line_Number;
\*+[^*/\n]*
\*+[^*/\n]*\n 	++Compiler::Line_Number;
{ENDCOM} {
		BEGIN(INITIAL);}
<<EOF>> {
	ucc::error("eof terminated comment","");
	BEGIN(INITIAL);
	}
}

<astring>{
\" {	BEGIN(INITIAL);
	yylval.value.svalue = lexer.string_buf;
	return(StrConstant);
	}
\n {	BEGIN(INITIAL);
	++Compiler::Line_Number;
	ucc::error("unterminated string constant","");
	}

\\n {
	lexer.string_buf += "\\n";
}
\\\" {
	lexer.string_buf += "\\\"";
}

\\[^n\\\"] {
		int c;
		BEGIN(INITIAL);
		ucc::error("illegal character:%s in string",yytext);
		while(((c = yyinput()) != '\"') && (c != EOF)){
			;
		}
		if(c == EOF){
			ucc::error("eof terminated string","");
		}
		}

((\\\\{SPACE}+)*|[&@$\%^/,.+'-\[\]{}();~`|=#\!:<>]*|{LETTER}|{DIGIT}|{PERCENT}|{SPACE}|{BEGCOM}|{ENDCOM}|{QUESTION})* {
	char *yptr = yytext;
	while((*yptr != (int)NULL) && *yptr){
		lexer.string_buf += *yptr++;
	}
	}

<<EOF>> {
	ucc::error("eof terminated string","");
	BEGIN(INITIAL);
	}
}


void {/*keyword void*/
	return(voidt);
	}

if {/* keyword if*/
	return(ift);
	}

return {/* keyword return*/
	return(returnt);
	}

else {/* keyword else*/
	return(elset);
	}


while {/*keyword while*/
	return(whilet);
	}

int { /*keyword int*/
	yylval.ttype = type::INT;
	return(intt);
	}

float {/* keyword float*/
	yylval.ttype = type::FLOAT;
	return(floatt);
	}

char { /* keyword char*/
	yylval.ttype = type::CHAR;
	return(chart);
	}

\( {
	return(lpar);
	}

\) {
	return(rpar);
	}

\{ {
	return(lcbra);
	}

\} {
	return(rcbra);
	}

\; {
	return(semi);
	}

\, {
	return(comma);
	}

\< {	yylval.value.relopvalue = reltype::LES;
	return(lesst);
	}

\> {	yylval.value.relopvalue = reltype::GRE;
	return(greatt);
	}

\= {
	return(equalt);
	}

\+ {	yylval.value.addopvalue = addtype::PLS;
	return(plus);
	}

\- {	yylval.value.addopvalue = addtype::MIN;
	return(minus);
	}

\/ {	yylval.value.multopvalue =multype:: DIV;
	return(divide);
	}
\* {	yylval.value.multopvalue = multype::MULT;
	return(star);
	}

{GEQ} {		yylval.value.relopvalue = reltype::GEQ;
		return(geq);
	}

{LEQ} {		yylval.value.relopvalue = reltype::LEQ;
		return(leq);
	}

{NEQ} {		yylval.value.eqopvalue = eqtype::NEQ;
		return(neq);
	}

{EQUEQU} {	yylval.value.eqopvalue = eqtype::EQEQ;
		return(equequ);
	}

{ADOF} {
		return(adof);
	}

{BEGCOM} {
		BEGIN(comment);
	}

{LETTER}({LETTER}|{DIGIT})* 	{/* identifier*/
				yylval.ttype = type::STR;
				std::string tempstr(yytext);
				yylval.value.svalue = tempstr;
				return(Ident);
				}

((0|([1-9]{DIGIT}*)))(while|if|void|return|char|int|float|else|for|extern) {
									ucc::error("illegal token: %s", yytext);
							}

((0|([1-9]{DIGIT}*))(\.{DIGIT}+))(while|if|void|return|char|int|float|else|for|extern) {
									ucc::error("illegal token: %s",yytext);
									}

(0|([1-9]{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) { /* bad form*/
						ucc::error("illegal token: %s", yytext);
						}

((0|([1-9]{DIGIT}*))(\.{DIGIT}{DIGIT}*))({LETTER}({LETTER}|{DIGIT})*) {/*bad form*/
							ucc::error("illegal token: %s",yytext);
							}



(0|([1-9]{DIGIT}*))\.{DIGIT}{DIGIT}* {/*float*/
					yylval.ttype = type::FLOAT;
					yylval.value.fvalue=(float)std::atof(yytext);
					return(FloatConstant);
					}

0{DIGIT}+\.{DIGIT}+		{/* bad float*/
					ucc::error("illegal float: %s",yytext);
				}


0{DIGIT}+	{/* bad integer*/
				ucc::error("illegal integer: %s", yytext);
		}

(0|([1-9]{DIGIT}*))		{/*integer constant*/
				yylval.ttype = type::INT;
				yylval.value.ivalue =(int)std::atoi(yytext);
				return(IntConstant);
				}

{ELIP} {
	return(elip);
	}

\" {
	BEGIN(astring);
	}


\n	{
	++Compiler::Line_Number;
	}

[ \t\r]+	{ /*eat up tabs, whitespace */
	}

<<EOF>> {
	return '\0';
	}

. 	{
	ucc::error("illegal character: %s",yytext);
	}

%%

#ifdef DEBUG
void debugprint(std::string s1, std::string s2){
	if(!s1.empty() && ~s2.empty()){
			std::cerr << "Debug:::" << compiler.filename << ":" << yylineno << " yylineno-> " << s1 << "\"" << s2 << "\"\n";
	}
	else if(s1!=NULL && *s1 && s2==NULL){
			std::cerr << "Debug:::" << compiler.filename << ":" << yylineno << " yylineno-> " << s1 << "\n";
	}
}
void debugprintd(std::string s1, int s2){
	if(!s1.empty()){
			std::cerr << "Debug:::" << compiler.filename << ":" << yylineno << " yylineno-> " << s1 << "\"" << s2 << "\"\n";
	}
}

#endif
