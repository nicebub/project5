/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     Ident = 258,
     IntConstant = 259,
     FloatConstant = 260,
     StrConstant = 261,
     voidt = 262,
     intt = 263,
     floatt = 264,
     chart = 265,
     ift = 266,
     whilet = 267,
     returnt = 268,
     elset = 269,
     equequ = 270,
     neq = 271,
     leq = 272,
     geq = 273,
     adof = 274,
     elip = 275,
     lpar = 276,
     rpar = 277,
     lcbra = 278,
     rcbra = 279,
     semi = 280,
     comma = 281,
     lesst = 282,
     greatt = 283,
     equal = 284,
     plus = 285,
     minus = 286,
     divide = 287,
     star = 288,
     uminus = 289
   };
#endif
/* Tokens.  */
#define Ident 258
#define IntConstant 259
#define FloatConstant 260
#define StrConstant 261
#define voidt 262
#define intt 263
#define floatt 264
#define chart 265
#define ift 266
#define whilet 267
#define returnt 268
#define elset 269
#define equequ 270
#define neq 271
#define leq 272
#define geq 273
#define adof 274
#define elip 275
#define lpar 276
#define rpar 277
#define lcbra 278
#define rcbra 279
#define semi 280
#define comma 281
#define lesst 282
#define greatt 283
#define equal 284
#define plus 285
#define minus 286
#define divide 287
#define star 288
#define uminus 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

