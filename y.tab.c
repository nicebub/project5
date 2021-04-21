/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 7 "ucc.y"

#ifdef DEBUGON
#ifndef DEBUG
#define DEBUG
#endif
#endif
#include "type.h"
#include "List.h"
#include "symtab.h"
#include "data.h"
#include "trans.h"
#include <stdio.h>
//#define yyerrok
#define YYDEBUG 0
#define YYERROR_VERBOSE 1
#define YYSTYPE data
#include "ucc.l.h"
#include "main.h"
#include <string.h>
extern int Line_Number;
bool founderror=FALSE;
extern int globalcount;
extern int mainlocal;
extern int othercounter;
extern int param_offset;
extern int offset_counter;
extern Symtab* mysymtab;
int mainlabel;
Funcb* currentFunc;
extern int yyerror(char *);
extern int yylex (void);
extern int warning(char*,char*);
extern int error(char*,char*);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 209 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNRULES -- Number of states.  */
#define YYNSTATES  175

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    15,    18,    19,
      23,    26,    30,    36,    42,    48,    52,    56,    60,    66,
      72,    78,    80,    84,    86,    90,    95,    98,   101,   105,
     110,   115,   121,   122,   128,   129,   132,   135,   139,   143,
     146,   149,   151,   154,   157,   161,   162,   163,   171,   172,
     177,   179,   183,   186,   190,   194,   199,   200,   207,   211,
     213,   217,   218,   223,   225,   229,   230,   235,   237,   241,
     242,   247,   249,   253,   254,   259,   261,   265,   267,   269,
     273,   276,   279,   281,   284,   289,   293,   295,   298,   299,
     304,   305,   310,   312,   314,   316,   318,   322,   326,   328,
     330,   332,   334,   336,   338,   340,   342,   344
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    -1,    38,    -1,    46,    -1,    37,
      38,    -1,    37,    46,    -1,    37,     1,    -1,    -1,    40,
      39,    43,    -1,    40,    25,    -1,    40,     1,    25,    -1,
       7,     3,    21,    41,    22,    -1,     8,     3,    21,    41,
      22,    -1,     9,     3,    21,    41,    22,    -1,     7,     1,
      22,    -1,     8,     1,    22,    -1,     9,     1,    22,    -1,
       7,     3,    21,     1,    22,    -1,     9,     3,    21,     1,
      22,    -1,     8,     3,    21,     1,    22,    -1,    42,    -1,
      42,    26,    20,    -1,     7,    -1,    42,     1,    22,    -1,
      42,    26,     1,    22,    -1,     8,     3,    -1,     9,     3,
      -1,    10,    33,     3,    -1,    42,    26,     8,     3,    -1,
      42,    26,     9,     3,    -1,    42,    26,    10,    33,     3,
      -1,    -1,    23,    45,    44,    47,    24,    -1,    -1,    45,
      46,    -1,    45,    38,    -1,     8,    70,    25,    -1,     9,
      70,    25,    -1,     1,    25,    -1,    47,    48,    -1,    48,
      -1,    54,    25,    -1,    13,    25,    -1,    13,    54,    25,
      -1,    -1,    -1,    12,    49,    21,    54,    22,    50,    48,
      -1,    -1,    52,    14,    51,    48,    -1,    52,    -1,    23,
      47,    24,    -1,    13,     1,    -1,    12,     1,    25,    -1,
      11,     1,    48,    -1,    23,    47,     1,    24,    -1,    -1,
      11,    21,    54,    53,    22,    48,    -1,    55,    29,    55,
      -1,    55,    -1,    55,    29,     1,    -1,    -1,    57,    73,
      56,    57,    -1,    57,    -1,    57,    73,     1,    -1,    -1,
      59,    74,    58,    59,    -1,    59,    -1,    59,    74,     1,
      -1,    -1,    59,    71,    60,    61,    -1,    61,    -1,    59,
      71,     1,    -1,    -1,    61,    72,    62,    63,    -1,    63,
      -1,    61,    72,     1,    -1,    69,    -1,     3,    -1,    21,
      54,    22,    -1,    71,    63,    -1,    19,     3,    -1,    64,
      -1,    71,     1,    -1,    21,    54,     1,    22,    -1,     3,
      21,    22,    -1,    65,    -1,    66,    22,    -1,    -1,     3,
      21,    67,    54,    -1,    -1,    66,    26,    68,    54,    -1,
       6,    -1,     4,    -1,     5,    -1,     3,    -1,    70,    26,
       3,    -1,    70,    26,     1,    -1,    30,    -1,    31,    -1,
      33,    -1,    32,    -1,    15,    -1,    16,    -1,    27,    -1,
      17,    -1,    18,    -1,    28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   130,   131,   132,   133,   135,   138,   138,
     263,   319,   327,   337,   347,   356,   367,   378,   389,   403,
     417,   434,   436,   443,   444,   448,   454,   460,   466,   472,
     478,   484,   494,   493,   518,   519,   521,   525,   531,   536,
     540,   541,   544,   548,   561,   621,   632,   621,   662,   661,
     683,   696,   699,   700,   702,   704,   714,   711,   736,   791,
     795,   799,   798,   872,   873,   877,   876,   971,   972,   976,
     975,  1050,  1051,  1054,  1054,  1128,  1129,  1133,  1147,  1218,
    1221,  1255,  1323,  1325,  1330,  1336,  1363,  1366,  1393,  1391,
    1532,  1531,  1632,  1637,  1642,  1650,  1651,  1652,  1659,  1660,
    1663,  1664,  1667,  1668,  1671,  1672,  1673,  1674
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Ident", "IntConstant", "FloatConstant",
  "StrConstant", "voidt", "intt", "floatt", "chart", "ift", "whilet",
  "returnt", "elset", "equequ", "neq", "leq", "geq", "adof", "elip",
  "lpar", "rpar", "lcbra", "rcbra", "semi", "comma", "lesst", "greatt",
  "equal", "plus", "minus", "divide", "star", "uminus", "$accept",
  "starter", "translation_unit", "func", "@1", "funcheader", "paramdef",
  "paramdeflist", "funcbody", "@2", "decls", "variabledecl", "stmtlist",
  "stmt", "@3", "@4", "@5", "ifexprstmt", "@6", "expr", "equalexpr", "@7",
  "relexpr", "@8", "simpleexpr", "@9", "term", "@10", "factor",
  "function_call", "func_call_with_params", "name_and_params", "@11",
  "@12", "constant", "identlist", "addop", "mulop", "eqop", "relop", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    37,    37,    37,    39,    38,
      38,    38,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    41,    41,    41,    41,    41,    42,    42,    42,    42,
      42,    42,    44,    43,    45,    45,    45,    46,    46,    46,
      47,    47,    48,    48,    48,    49,    50,    48,    51,    48,
      48,    48,    48,    48,    48,    48,    53,    52,    54,    54,
      54,    56,    55,    55,    55,    58,    57,    57,    57,    60,
      59,    59,    59,    62,    61,    61,    61,    63,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    65,    67,    66,
      68,    66,    69,    69,    69,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    74,    74,    74,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     2,     0,     3,
       2,     3,     5,     5,     5,     3,     3,     3,     5,     5,
       5,     1,     3,     1,     3,     4,     2,     2,     3,     4,
       4,     5,     0,     5,     0,     2,     2,     3,     3,     2,
       2,     1,     2,     2,     3,     0,     0,     7,     0,     4,
       1,     3,     2,     3,     3,     4,     0,     6,     3,     1,
       3,     0,     4,     1,     3,     0,     4,     1,     3,     0,
       4,     1,     3,     0,     4,     1,     3,     1,     1,     3,
       2,     2,     1,     2,     4,     3,     1,     2,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     3,     0,     4,
      39,     0,     0,     0,    95,     0,     0,    95,     0,     1,
       7,     5,     6,     0,    10,     0,    15,     0,    16,     0,
      37,     0,    17,     0,    38,    11,    34,     9,     0,    23,
       0,     0,     0,     0,     0,     0,     0,    97,    96,     0,
       0,     0,    18,    26,    27,     0,    12,     0,     0,    20,
      13,    19,    14,    36,     0,    35,    28,    24,     0,     0,
       0,     0,    22,    78,    93,    94,    92,     0,     0,     0,
       0,     0,     0,    98,    99,     0,    41,    50,     0,    59,
      63,    67,    71,    75,    82,    86,     0,    77,     0,    25,
      29,    30,     0,    88,     0,     0,     0,     0,    52,    43,
       0,    81,     0,     0,    33,    40,    48,    42,     0,   102,
     103,     0,   105,   106,   104,   107,     0,     0,   101,   100,
       0,    87,    90,    83,    80,    31,    85,     0,    54,    56,
      53,     0,    44,     0,    79,     0,    51,     0,    60,    58,
      64,     0,    72,     0,    68,     0,    76,     0,     0,    89,
       0,     0,    84,    55,    49,    62,    70,    66,    74,    91,
       0,    46,    57,     0,    47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,    25,     8,    43,    44,    37,    64,
      51,     9,    85,    86,   107,   173,   147,    87,   160,    88,
      89,   151,    90,   155,    91,   153,    92,   157,    93,    94,
      95,    96,   137,   158,    97,    15,    98,   130,   121,   127
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int16 yypact[] =
{
     164,    20,    14,    15,    23,    77,    13,   -94,    30,   -94,
     -94,     7,    49,    65,    71,   136,    73,    82,   142,   -94,
      20,   -94,   -94,    90,   -94,    85,   -94,    89,   -94,   109,
     -94,    83,   -94,   146,   -94,   -94,   -94,   -94,   113,   -94,
     125,   127,   119,   135,    11,   137,   141,   -94,   -94,   152,
     156,    35,   -94,   -94,   -94,   138,   -94,   162,    59,   -94,
     -94,   -94,   -94,   -94,   246,   -94,   -94,   -94,   177,   193,
     195,   167,   -94,   181,   -94,   -94,   -94,    29,    51,   101,
     201,     4,   246,   -94,   -94,   217,   -94,   191,   183,   180,
     174,   106,   159,   -94,   -94,   -94,    99,   -94,   108,   -94,
     -94,   -94,   207,   189,   246,     4,   190,   203,   -94,   -94,
     200,   -94,    10,    70,   -94,   -94,   -94,   -94,   139,   -94,
     -94,   145,   -94,   -94,   -94,   -94,   176,   182,   -94,   -94,
     213,   -94,   -94,   -94,   -94,   -94,   -94,     4,   -94,   -94,
     -94,     4,   -94,   204,   -94,   209,   -94,   246,   -94,   -94,
     -94,     4,   -94,     4,   -94,     4,   -94,     4,     4,   -94,
     205,   215,   -94,   -94,   -94,   -94,   159,   163,   -94,   -94,
     246,   -94,   -94,   246,   -94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   -94,    -2,   -94,   -94,    28,   -94,   -94,   -94,
     -94,     0,   149,   -85,   -94,   -94,   -94,   -94,   -94,   -78,
     117,   -94,    88,   -94,    87,   -94,    92,   -94,   -93,   -94,
     -94,   -94,   -94,   -94,   -94,   242,   -89,   -94,   -94,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -74
static const yytype_int16 yytable[] =
{
     115,   110,   126,   112,    21,   134,    22,    73,    74,    75,
      76,   143,    57,    -2,    20,    11,    13,    12,    14,   138,
       2,     3,     4,    80,    16,    81,    17,   139,   115,    26,
     104,    23,   144,   -21,    83,    84,     1,    58,   -32,   -32,
     -32,   -32,     2,     3,     4,    10,   -32,   -32,   -32,    63,
     105,    65,   106,    -8,   -32,    24,   -32,    46,   -32,   159,
      68,    50,   164,   161,   168,   -32,   -32,    69,    70,    71,
      27,   145,   -45,    73,    74,    75,    76,    19,   126,    72,
     169,    77,    78,    79,    47,   172,    48,    28,   174,    80,
      38,    81,    29,    82,   146,    32,    39,    40,    41,    42,
      83,    84,   108,    33,    73,    74,    75,    76,    36,   133,
      45,    73,    74,    75,    76,    35,    39,    40,    41,    42,
      80,   131,    81,   122,   123,   132,   109,    80,    53,    81,
      54,    83,    84,   124,   125,    52,    83,    84,    83,    84,
     148,    66,    73,    74,    75,    76,   150,    49,   -61,   -61,
     -61,   -61,    55,    39,    40,    41,    42,    56,    80,    59,
      81,    30,    31,    60,   -61,     1,   -61,    34,    31,    83,
      84,     2,     3,     4,    61,   -61,   -61,   152,    62,   -69,
     -69,   -69,   -69,   154,    67,   -65,   -65,   -65,   -65,   119,
     120,   128,   129,    83,    84,   -69,   100,   -69,   101,    99,
     102,   -65,   103,   -65,   111,   116,   -69,   -69,   117,   118,
     135,   136,   -65,   -65,   156,   140,   -73,   -73,   -73,   -73,
      73,    74,    75,    76,   141,   142,   162,   170,    77,    78,
      79,   113,   -73,   163,   -73,   149,    80,   171,    81,   165,
      82,   114,   167,   -73,   -73,   166,    18,    83,    84,    73,
      74,    75,    76,     0,     0,     0,     0,    77,    78,    79,
       0,     0,     0,     0,     0,    80,     0,    81,     0,    82,
       0,     0,     0,     0,     0,     0,    83,    84
};

static const yytype_int16 yycheck[] =
{
      85,    79,    91,    81,     6,    98,     6,     3,     4,     5,
       6,     1,     1,     0,     1,     1,     1,     3,     3,   104,
       7,     8,     9,    19,     1,    21,     3,   105,   113,    22,
       1,     1,    22,    22,    30,    31,     1,    26,     3,     4,
       5,     6,     7,     8,     9,    25,    11,    12,    13,    51,
      21,    51,     1,    23,    19,    25,    21,    29,    23,   137,
       1,    33,   147,   141,   157,    30,    31,     8,     9,    10,
      21,     1,    21,     3,     4,     5,     6,     0,   167,    20,
     158,    11,    12,    13,     1,   170,     3,    22,   173,    19,
       1,    21,    21,    23,    24,    22,     7,     8,     9,    10,
      30,    31,     1,    21,     3,     4,     5,     6,    23,     1,
       1,     3,     4,     5,     6,    25,     7,     8,     9,    10,
      19,    22,    21,    17,    18,    26,    25,    19,     3,    21,
       3,    30,    31,    27,    28,    22,    30,    31,    30,    31,
       1,     3,     3,     4,     5,     6,     1,     1,     3,     4,
       5,     6,    33,     7,     8,     9,    10,    22,    19,    22,
      21,    25,    26,    22,    19,     1,    21,    25,    26,    30,
      31,     7,     8,     9,    22,    30,    31,     1,    22,     3,
       4,     5,     6,     1,    22,     3,     4,     5,     6,    15,
      16,    32,    33,    30,    31,    19,     3,    21,     3,    22,
      33,    19,    21,    21,     3,    14,    30,    31,    25,    29,
       3,    22,    30,    31,     1,    25,     3,     4,     5,     6,
       3,     4,     5,     6,    21,    25,    22,    22,    11,    12,
      13,    82,    19,    24,    21,   118,    19,    22,    21,   151,
      23,    24,   155,    30,    31,   153,     4,    30,    31,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     8,     9,    36,    37,    38,    40,    46,
      25,     1,     3,     1,     3,    70,     1,     3,    70,     0,
       1,    38,    46,     1,    25,    39,    22,    21,    22,    21,
      25,    26,    22,    21,    25,    25,    23,    43,     1,     7,
       8,     9,    10,    41,    42,     1,    41,     1,     3,     1,
      41,    45,    22,     3,     3,    33,    22,     1,    26,    22,
      22,    22,    22,    38,    44,    46,     3,    22,     1,     8,
       9,    10,    20,     3,     4,     5,     6,    11,    12,    13,
      19,    21,    23,    30,    31,    47,    48,    52,    54,    55,
      57,    59,    61,    63,    64,    65,    66,    69,    71,    22,
       3,     3,    33,    21,     1,    21,     1,    49,     1,    25,
      54,     3,    54,    47,    24,    48,    14,    25,    29,    15,
      16,    73,    17,    18,    27,    28,    71,    74,    32,    33,
      72,    22,    26,     1,    63,     3,    22,    67,    48,    54,
      25,    21,    25,     1,    22,     1,    24,    51,     1,    55,
       1,    56,     1,    60,     1,    58,     1,    62,    68,    54,
      53,    54,    22,    24,    48,    57,    61,    59,    63,    54,
      22,    22,    48,    50,    48
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 117 "ucc.y"
    {
			if(founderror == FALSE){
				gen_label("main");
				gen_instr_I("enter",0);
				gen_instr_I("alloc",globalcount);
				gen_instr_I("enter",0);
				gen_call(genlabelw("main",mainlabel),0);
				gen_instr("return");

			}
	}
    break;

  case 3:
#line 130 "ucc.y"
    {}
    break;

  case 4:
#line 131 "ucc.y"
    {}
    break;

  case 5:
#line 132 "ucc.y"
    {}
    break;

  case 6:
#line 133 "ucc.y"
    {}
    break;

  case 7:
#line 135 "ucc.y"
    { error("(unexpected token between translation units or at end of program)","");}
    break;

  case 8:
#line 138 "ucc.y"
    {
					Entry* tempEntry;
					Funcb* tempb;
					//Funcb* found;
					int a;
					ListP* templist;
                    templist= NULL;
					//type tempparam;
					listnodeP* tempnode;
					#ifdef DEBUG
					printTree(mysymtab);
					#endif
					bool stop=FALSE;
					bool alreadyopen=FALSE;
                    tempnode = NULL;
					if(strcmp("main", (char*)((yyvsp[(1) - (1)].value.funcheadervalue)->name)) ==0){
			                        #ifdef DEBUG
                			        fprintf(stderr,"hello from inside\n");
             				        #endif
						templist = (ListP*)(yyvsp[(1) - (1)].value.funcheadervalue)->paramlist;
	//main function
						if((yyvsp[(1) - (1)].value.funcheadervalue)->returntype != INT)
							error("Main function has to have int as return type","");
						if(templist != NULL && templist->listsize != 1)
							error("Main function only has one parameter","");
						else if((yyvsp[(1) - (1)].value.funcheadervalue)->ttype != VOID)
							error("Main function has to have one parameter of void","");
						#ifdef DEBUG							
						fprintf(stderr, "opening up a new scope\n");
						#endif		
						openscope(mysymtab);
						 alreadyopen=TRUE;
						if(founderror==FALSE){
							mainlabel=getlabel();
							gen_label(genlabelw("main", mainlabel));
						}
					}
					else{
						if((tempb=(Funcb*)lookup((char*)((yyvsp[(1) - (1)].value.funcheadervalue)->name), mysymtab)) ==NULL)
							error("Function name not in symbol table","");
						else{
							Entry *tempEn; Entry * tempEn2;
							tempEn2 = (Entry*) malloc(sizeof(Entry));
							tempEn2->name = (yyvsp[(1) - (1)].value.funcheadervalue)->name;
							tempEn = lookupB((char*)((yyvsp[(1) - (1)].value.funcheadervalue)->name),mysymtab);
							//tempEn = *(Entry**)tfind((void*)tempEn2, (void**) &(mysymtab->Stack[mysymtab->actualStacksize -1]),Ecmp);
							if(tempEn!=NULL && tempEn->self == FUNC){
								if(tempb->returntype != (yyvsp[(1) - (1)].value.funcheadervalue)->returntype)
									error("Function declared with different return type","");
								else{
									templist= (ListP*)(yyvsp[(1) - (1)].value.funcheadervalue)->paramlist;
									if(tempb->num_param == -1)
										error("Function cannot have those parameters","");
									else if( templist!=NULL && (templist->listsize) != tempb->num_param)
										error("Function has different number of parameters","");
									else{
										if(templist!=NULL){
											tempnode = (listnodeP*)templist->list;
											for(a=0;a<templist->listsize && a<tempb->num_param &&  stop!=TRUE;a++){
												if(tempb->param_type[a] != tempnode->ttype){
													fprintf(stderr,"Error: Line: %d: argument %d: has different parameter type than in function declaration\n",Line_Number,(a+1));
													fprintf(stderr, "\nThey are %d and %d\n", tempb->param_type[a], tempnode->ttype);
													stop=TRUE;
												}
												tempnode = (listnodeP*)tempnode->nextnode;
											}
										}
										if(stop!= TRUE){
											if(tempb->bodydef == TRUE){
												error("Function definition is previously declared","");
											}
											else{
												//tempb->localcount=offset_counter;
												openscope(mysymtab);
												alreadyopen=TRUE;
												if(templist!=NULL){
													tempnode= (listnodeP*)templist->list;
												#ifdef DEBUG
												if(tempnode->ttype != VOID){
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
													for(a=0;a<templist->listsize;a++){
														tempEntry = createParam((char*)strdup((char*)tempnode->val), tempnode->ttype,(offset_counter));
														install(tempEntry, mysymtab);
														offset_counter++;
														tempnode = (listnodeP*)tempnode->nextnode;
													}
												}
												if(founderror==FALSE){
													//tempb->label=getlabel();
													gen_label(genlabelw((yyvsp[(1) - (1)].value.funcheadervalue)->name,tempb->label ));

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
						if(alreadyopen==FALSE) openscope(mysymtab);
					}
		}
    break;

  case 9:
#line 254 "ucc.y"
    {
			if(founderror==FALSE){
				gen_instr("returnf");
			}
//			if(currentFunc == NULL)
//				closemainscope(mysymtab);
//			else
				closescope(mysymtab);
	}
    break;

  case 10:
#line 263 "ucc.y"
    {
			   Entry * temp; Funcb* found; int a;
			   #ifdef DEBUG
				printTree(mysymtab);
			   #endif
			   temp =  createFunc((char*)strdup((yyvsp[(1) - (2)].value.funcheadervalue)->name), (yyvsp[(1) - (2)].value.funcheadervalue)->returntype, (ListP*)((yyvsp[(1) - (2)].value.funcheadervalue)->paramlist));
			   if((yyvsp[(1) - (2)].value.funcheadervalue)->paramlist !=NULL) deleteListP((ListP*)((yyvsp[(1) - (2)].value.funcheadervalue)->paramlist));
			   if((yyvsp[(1) - (2)].value.funcheadervalue) !=NULL) free((yyvsp[(1) - (2)].value.funcheadervalue));
			   if( strcmp("main", (char*)temp->name)==0){
					if( ((Funcb*)(temp->binding))->returntype != INT)
						error("Main function needs return type of int","");
					if( ((Funcb*)(temp->binding))->num_param != 1)
						error("Main function only takes 1 parameter","");
					if( ((Funcb*)(temp->binding))->param_type[0] != VOID)
						error("Main function parameter has to be void","");
					deleteEntry(temp);
			   }
			   else{
				   found = lookup((char*)temp->name, mysymtab);
                   #ifdef DEBUG
					if(temp->name ==NULL)
                  	 fprintf(stderr,"FUNCTION: temp before symbol table: %s\n", "NULL");
					 else
                  	 fprintf(stderr,"FUNCTION: temp before symbol table: %s\n", temp->name);
					 #endif
                   Funcb * paramOftemp = temp->binding;
                   #ifdef DEBUG
                   fprintf(stderr,"binding of temp as Funcb: value num_param in symbol table: %d\n", (paramOftemp->num_param));
                   fprintf(stderr,"param_type of paramOftemp as typeOftemp: value param_type in symbol table: %d\n", (paramOftemp->param_type[2]));
                   #endif
				   if(found == NULL){ install(temp, mysymtab); /*printTree(mysymtab)*/;}
				   else{
					if(((Funcb*)(temp->binding))->returntype != found->returntype)
						error("Function already declared with different return type","");
					if(((Funcb*)(temp->binding))->num_param == -1 || found->num_param == -1){
						if(((Funcb*)(temp->binding))->param_type[0] != found->param_type[0])
							error("In Function %s ", (yyvsp[(1) - (2)].value.funcheadervalue)->name);
							fprintf(stderr,"argument 0 is of different type than in previous declaration\n");
					}
					else{
						if(((Funcb*)(temp->binding))->num_param != found->num_param)
							error("Function already decleared with different number of parameters","");
						if( ((Funcb*)(temp->binding))->num_param > 0 && found->num_param >0){
							for(a=0;a<((Funcb*)(temp->binding))->num_param && a<found->num_param ;a++){
								if(((Funcb*)(temp->binding))->param_type[a] != found->param_type[a]){
									error("In Function %s ", (yyvsp[(1) - (2)].value.funcheadervalue)->name);
									fprintf(stderr, "argument %d is of different type than in previous declaration\n", a);
								}

							}
						}
					}
				   deleteEntry(temp);
				   }
			   }
			}
    break;

  case 11:
#line 319 "ucc.y"
    { yyerrok;
					error("(unexpected token before semi in function)","");
					if((yyvsp[(1) - (3)].value.funcheadervalue) !=NULL) if((yyvsp[(1) - (3)].value.funcheadervalue)->paramlist !=NULL) deleteListP((ListP*)((yyvsp[(1) - (3)].value.funcheadervalue)->paramlist));
					if((yyvsp[(1) - (3)].value.funcheadervalue) !=NULL) free((yyvsp[(1) - (3)].value.funcheadervalue)); (yyvsp[(1) - (3)].value.funcheadervalue) = NULL;
				}
    break;

  case 12:
#line 327 "ucc.y"
    {	(yyval.value.funcheadervalue) = (funcheadertype*)malloc(sizeof(funcheadertype));
						(yyval.value.funcheadervalue)->returntype = VOID;
						(yyval.value.funcheadervalue)->name = (yyvsp[(2) - (5)].value.svalue);
                        (yyval.value.funcheadervalue)->paramlist=NULL;
                        if((yyvsp[(4) - (5)]).ttype == VOID) (yyval.value.funcheadervalue)->ttype = VOID;
						//(ListP*)($$->paramlist) = $<value.lstpvalue>4;
						ListP * tempLP = NULL;
						tempLP = (yyvsp[(4) - (5)].value.lstpvalue);
                        (yyval.value.funcheadervalue)->paramlist = tempLP;
						}
    break;

  case 13:
#line 337 "ucc.y"
    {	(yyval.value.funcheadervalue) = (funcheadertype*)malloc(sizeof(funcheadertype));
						(yyval.value.funcheadervalue)->returntype = INT;
						(yyval.value.funcheadervalue)->name = (yyvsp[(2) - (5)].value.svalue);
                        (yyval.value.funcheadervalue)->paramlist = NULL;
						if((yyvsp[(4) - (5)]).ttype == VOID) (yyval.value.funcheadervalue)->ttype = VOID;
						//(ListP*)($$->paramlist) = $<value.lstpvalue>4;
						ListP * tempLP = NULL;
						tempLP = (yyvsp[(4) - (5)].value.lstpvalue);
                        (yyval.value.funcheadervalue)->paramlist = tempLP;
						}
    break;

  case 14:
#line 347 "ucc.y"
    {	(yyval.value.funcheadervalue) = (funcheadertype*)malloc(sizeof(funcheadertype));
						(yyval.value.funcheadervalue)->returntype = FLOAT;
						(yyval.value.funcheadervalue)->name = (yyvsp[(2) - (5)].value.svalue);
                        if((yyvsp[(4) - (5)]).ttype == VOID) (yyval.value.funcheadervalue)->ttype = VOID;
						//(ListP*)($$->paramlist) = $<value.lstpvalue>4;
						ListP * tempLP = NULL;
						tempLP = (yyvsp[(4) - (5)].value.lstpvalue);
                        (yyval.value.funcheadervalue)->paramlist = tempLP;
						}
    break;

  case 15:
#line 356 "ucc.y"
    { ListP* tempP; yyerrok;
				(yyval.value.funcheadervalue) =(funcheadertype*) malloc(sizeof(funcheadertype));
				(yyval.value.funcheadervalue)->name ="";
				(yyval.value.funcheadervalue)->returntype=VOID;
				//(ListP*)($$->paramlist) = (ListP*) malloc(sizeof(ListP));
				ListP * tempLP;
				tempLP = (ListP*) mklistP((char*)strdup("error"), VOID);
				tempP= (ListP*)tempLP;
				(yyval.value.funcheadervalue)->paramlist= tempLP;
				error("(expecting lpar before rpar in function)","");
			}
    break;

  case 16:
#line 367 "ucc.y"
    { ListP* tempP; yyerrok;
				(yyval.value.funcheadervalue) =(funcheadertype*) malloc(sizeof(funcheadertype));
				(yyval.value.funcheadervalue)->name ="";
				(yyval.value.funcheadervalue)->returntype=INT;
				//(ListP*)($$->paramlist) = (ListP*) malloc(sizeof(ListP));
				ListP * tempLP;
				tempLP = (ListP*) mklistP((char*)strdup("error"), VOID);
				tempP= (ListP*)tempLP;
				(yyval.value.funcheadervalue)->paramlist= tempLP;
				error("(expecting lpar before rpar in function)","");
			}
    break;

  case 17:
#line 378 "ucc.y"
    { ListP* tempP; yyerrok;
				(yyval.value.funcheadervalue) =(funcheadertype*) malloc(sizeof(funcheadertype));
				(yyval.value.funcheadervalue)->name ="";
				(yyval.value.funcheadervalue)->returntype=FLOAT;
				//(ListP*)($$->paramlist) = (ListP*) malloc(sizeof(ListP));
				ListP * tempLP;
				tempLP = (ListP*) mklistP((char*)strdup("error"), VOID);
				tempP= (ListP*)tempLP;
				(yyval.value.funcheadervalue)->paramlist= tempLP;
				error("(expecting lpar before rpar in function)","");
			}
    break;

  case 18:
#line 389 "ucc.y"
    {ListP* tempP; yyerrok;
				(yyval.value.funcheadervalue) =(funcheadertype*) malloc(sizeof(funcheadertype));
				(yyval.value.funcheadervalue)->name =(yyvsp[(2) - (5)].value.svalue);
				(yyval.value.funcheadervalue)->returntype=VOID;
				//(ListP*)($$->paramlist) = NULL;
				ListP * tempLP1 = (ListP *)(yyval.value.funcheadervalue)->paramlist;
				tempLP1 = NULL;
				//(ListP*)($$->paramlist) = (ListP*) malloc(sizeof(ListP));
				ListP * tempLP;
				tempLP = (ListP*) mklistP((char*)strdup("error"), VOID);
				tempP= (ListP*)tempLP;
				(yyval.value.funcheadervalue)->paramlist= tempLP;
				error("(unexpected token after lpar and before rpar in function)","");
			}
    break;

  case 19:
#line 403 "ucc.y"
    { ListP* tempP; yyerrok;
				(yyval.value.funcheadervalue) =(funcheadertype*) malloc(sizeof(funcheadertype));
				(yyval.value.funcheadervalue)->name =(yyvsp[(2) - (5)].value.svalue);
				(yyval.value.funcheadervalue)->returntype=FLOAT;
				//(ListP*)($$->paramlist) = NULL;
				ListP * tempLP1 = (ListP *)(yyval.value.funcheadervalue)->paramlist;
				tempLP1 = NULL;
				//(ListP*)($$->paramlist) = (ListP*) malloc(sizeof(ListP));
				ListP * tempLP;
				tempLP = (ListP*) mklistP((char*)strdup("error"), VOID);
				tempP= (ListP*)tempLP;
				(yyval.value.funcheadervalue)->paramlist= tempLP;
				error("(unexpected token after lpar and before rpar in function)","");
			}
    break;

  case 20:
#line 417 "ucc.y"
    {ListP* tempP; yyerrok;
				(yyval.value.funcheadervalue) = (funcheadertype*)  malloc(sizeof(funcheadertype));
				(yyval.value.funcheadervalue)->name=(yyvsp[(2) - (5)].value.svalue);
				(yyval.value.funcheadervalue)->returntype=INT;
				//(ListP*)($$->paramlist) = NULL;
				ListP * tempLP1 = (ListP *)(yyval.value.funcheadervalue)->paramlist;
				tempLP1 = NULL;
				//(ListP*)($$->paramlist) = (ListP*) malloc(sizeof(ListP));
				ListP * tempLP;
				tempLP = (ListP*) mklistP((char*)strdup("error"), VOID);
				tempP= (ListP*)tempLP;
				(yyval.value.funcheadervalue)->paramlist= tempLP;
				error("(unexpected token after lpar and before rpar in function)","");
			}
    break;

  case 21:
#line 434 "ucc.y"
    {(yyval.value.lstpvalue)= (yyvsp[(1) - (1)].value.lstpvalue);
				}
    break;

  case 22:
#line 436 "ucc.y"
    {
				(yyval.value.lstpvalue) = appendListP((yyvsp[(1) - (3)].value.lstpvalue), "...", VOID);
                #ifdef DEBUG
                printListP((yyval.value.lstpvalue));
                #endif

				}
    break;

  case 23:
#line 443 "ucc.y"
    {(yyval.value.lstpvalue) = NULL; (yyval).ttype = VOID;}
    break;

  case 24:
#line 444 "ucc.y"
    { yyerrok;
					error("(unexpected token before rpar in parameter definition)","");
					deleteListP((yyvsp[(1) - (3)].value.lstpvalue));
						}
    break;

  case 25:
#line 448 "ucc.y"
    { yyerrok;
					error("(unexpected token before rpar in parameter definition)","");
					deleteListP((yyvsp[(1) - (4)].value.lstpvalue));
					}
    break;

  case 26:
#line 454 "ucc.y"
    {
				(yyval.value.lstpvalue) = mklistP((char*)strdup((yyvsp[(2) - (2)].value.svalue)), INT);
                #ifdef DEBUG
                printListP((yyval.value.lstpvalue));
                #endif
				}
    break;

  case 27:
#line 460 "ucc.y"
    {
				(yyval.value.lstpvalue) = mklistP((char*)strdup((yyvsp[(2) - (2)].value.svalue)), FLOAT);
                #ifdef DEBUG
                printListP((yyval.value.lstpvalue));
                #endif
				}
    break;

  case 28:
#line 466 "ucc.y"
    {
				(yyval.value.lstpvalue) = mklistP((char*)strdup((yyvsp[(3) - (3)].value.svalue)), STR);
                #ifdef DEBUG
                printListP((yyval.value.lstpvalue));
                #endif
                }
    break;

  case 29:
#line 472 "ucc.y"
    {
				(yyval.value.lstpvalue) = appendListP((yyvsp[(1) - (4)].value.lstpvalue), (char*)strdup((yyvsp[(4) - (4)].value.svalue)),INT);
                #ifdef DEBUG
                printListP((yyval.value.lstpvalue));
                #endif
				}
    break;

  case 30:
#line 478 "ucc.y"
    {
				(yyval.value.lstpvalue) = appendListP((yyvsp[(1) - (4)].value.lstpvalue), (char*)strdup((yyvsp[(4) - (4)].value.svalue)), FLOAT);
                #ifdef DEBUG
                printListP((yyval.value.lstpvalue));
                #endif
				}
    break;

  case 31:
#line 484 "ucc.y"
    {
				(yyval.value.lstpvalue) = appendListP((yyvsp[(1) - (5)].value.lstpvalue), (char*)strdup((yyvsp[(5) - (5)].value.svalue)), STR);
                #ifdef DEBUG
                printListP((yyval.value.lstpvalue));
                #endif
				}
    break;

  case 32:
#line 494 "ucc.y"
    {
			if(founderror==FALSE){
				mainlocal=offset_counter-5;
				if(currentFunc==NULL)
					gen_instr_I("alloc", mainlocal);
				else{
					currentFunc->localcount=offset_counter-5-currentFunc->num_param;
					gen_instr_I("alloc",currentFunc->localcount);
				}
			}
		}
    break;

  case 33:
#line 506 "ucc.y"
    {
					#ifdef DEBUG
					printTree(mysymtab);
					#endif
					}
    break;

  case 35:
#line 519 "ucc.y"
    { //$<value.lstvalue>$ = $<value.lstvalue>2;
				}
    break;

  case 36:
#line 521 "ucc.y"
    {}
    break;

  case 37:
#line 525 "ucc.y"
    { if((yyvsp[(2) - (3)].value.lstvalue) !=NULL) addtosymtab(mysymtab, INT, (yyvsp[(2) - (3)].value.lstvalue));
					#ifdef DEBUG
						fprintf(stderr,"Found a single Integer declaration or a list of integers being declared\n");
						printTree(mysymtab);
					#endif
					}
    break;

  case 38:
#line 531 "ucc.y"
    { if((yyvsp[(2) - (3)].value.lstvalue) !=NULL) addtosymtab(mysymtab, FLOAT, (yyvsp[(2) - (3)].value.lstvalue));
					#ifdef DEBUG
					printTree(mysymtab);
					#endif
				}
    break;

  case 39:
#line 536 "ucc.y"
    { yyerrok; error("(unexpected token in variable decl)",""); }
    break;

  case 40:
#line 540 "ucc.y"
    {}
    break;

  case 41:
#line 541 "ucc.y"
    {}
    break;

  case 42:
#line 544 "ucc.y"
    {
		if(founderror==FALSE)
			gen_instr_I("popI",4);
	}
    break;

  case 43:
#line 548 "ucc.y"
    {
					if(currentFunc ==NULL)
						error("main function has to return a value","");
					else{
						if(currentFunc->returntype != VOID)
							error("Function has return type that is not void","");
						else{
							if(founderror==FALSE){
								gen_instr("returnf");
							}
						}
					}
			}
    break;

  case 44:
#line 561 "ucc.y"
    {		if((yyvsp[(2) - (3)].value.exprvalue)->numeric != TRUE)
						error("non numeric expression in return statement or return type is void", "");
					else{
						if(currentFunc ==NULL){
							if((yyvsp[(2) - (3)].value.exprvalue)->type != INT)
								warning("main function has int return type","");

								if(founderror==FALSE){
									if((yyvsp[(2) - (3)].value.exprvalue)->lval==TRUE){
										switch((yyvsp[(2) - (3)].value.exprvalue)->type){
											case INT:	gen_instr("fetchI"); break;
											case FLOAT:	gen_instr("fetchR"); break;
                                            default: break;
										}
									}
									if((yyvsp[(2) - (3)].value.exprvalue)->type != INT) gen_instr("int");
									gen_instr("setrvI");
								}

						}
						else{
							#ifdef DEBUG
							printf("type and returntype : %d: %d\n",(yyvsp[(2) - (3)].value.exprvalue)->type,currentFunc->returntype);
							#endif
							if((yyvsp[(2) - (3)].value.exprvalue)->type != currentFunc->returntype)
								warning("function has different returntype","");

								if(founderror==FALSE){
                                                if((yyvsp[(2) - (3)].value.exprvalue)->lval==TRUE){
                                                    switch((yyvsp[(2) - (3)].value.exprvalue)->type){
                                                        case INT:       gen_instr("fetchI"); break;
                                                        case FLOAT:     gen_instr("fetchR"); break;
                                                        default:    break;
                                                                                }
                                                                        }
									switch(currentFunc->returntype){
										case INT:	switch((yyvsp[(2) - (3)].value.exprvalue)->type){
													case FLOAT:	gen_instr("int");
													case INT:	gen_instr("setrvI"); break;
                                                    default: break;
												}
												break;
										case FLOAT:	switch((yyvsp[(2) - (3)].value.exprvalue)->type){
													case INT:	gen_instr("flt");
													case FLOAT:	gen_instr("setrvR"); break;
                                                    default:    break;
												}
												break;
                                        default: break;
									}
                                    
									gen_instr("returnf");
                                                                }



						}
					}

				}
    break;

  case 45:
#line 621 "ucc.y"
    {
		if(founderror==FALSE){
			(yyval).one= othercounter;
			othercounter++;
			(yyval).two = othercounter;
			othercounter++;
			gen_label(genlabelw("",(yyval).one));
		}
	}
    break;

  case 46:
#line 632 "ucc.y"
    {
		if(founderror==FALSE){
			if((yyvsp[(4) - (5)].value.exprvalue)->numeric==TRUE){
				if((yyvsp[(4) - (5)].value.exprvalue)->lval==TRUE ){
					switch((yyvsp[(4) - (5)].value.exprvalue)->type){
						case INT:	gen_instr("fetchI"); break;
						case FLOAT:	gen_instr("fetchR"); gen_instr("int"); break;
                        default:    break;
					}
				}
			}
			gen_instr_S("jumpz", genlabelw("",(yyvsp[(2) - (5)]).two));

		}
	}
    break;

  case 47:
#line 647 "ucc.y"
    {
				if((yyvsp[(4) - (7)].value.exprvalue)->numeric !=TRUE)
					error("non numeric expression in while statement","");
				else{
						if((yyvsp[(4) - (7)].value.exprvalue)->type !=INT)
							error("expression in while statement is not an integer","");
						if(founderror==FALSE){
							gen_instr_S("jump", genlabelw("",(yyvsp[(2) - (7)]).one));
							gen_label(genlabelw("",(yyvsp[(2) - (7)]).two));
						}

				}
	}
    break;

  case 48:
#line 662 "ucc.y"
    {
		if(founderror==FALSE){
			gen_instr_S("jump", genlabelw("",(yyvsp[(1) - (2)]).two));
			gen_label(genlabelw("",(yyvsp[(1) - (2)]).one));
		}
	}
    break;

  case 49:
#line 669 "ucc.y"
    {
				if((yyvsp[(1) - (4)]).numeric !=TRUE)
						error("non numeric expression in if statement","");
					else{
						if((yyvsp[(1) - (4)]).ttype !=INT)
							error("expression in if statement is not an integer","");
						else{
							if(founderror==FALSE){
								gen_label(genlabelw("",(yyvsp[(1) - (4)]).two));
							}
						}
					}
	}
    break;

  case 50:
#line 683 "ucc.y"
    {
					if((yyvsp[(1) - (1)]).numeric !=TRUE)
						error("non numeric expression in if statement","");
					else{
						if((yyvsp[(1) - (1)]).ttype !=INT)
							error("expression in if statement is not an integer","");
						else{

							if(founderror==FALSE) gen_label(genlabelw("",(yyvsp[(1) - (1)]).one));
						}
					}
	}
    break;

  case 51:
#line 696 "ucc.y"
    {
				//closescope(mysymtab);
				}
    break;

  case 52:
#line 699 "ucc.y"
    { yyerrok; error("(unexpected token after return in return stmt)","");}
    break;

  case 53:
#line 700 "ucc.y"
    { yyerrok; error("(unexpected token before semi in while stmt)","");}
    break;

  case 54:
#line 702 "ucc.y"
    { yyerrok; error("(unexpected token before stmt in if stmt)","");}
    break;

  case 55:
#line 704 "ucc.y"
    { yyerrok;
					error("(unexpected token before rcbra in stmt)","");
					//closescope(mysymtab);
				}
    break;

  case 56:
#line 714 "ucc.y"
    {
		(yyval).one=othercounter;
		othercounter++;
		(yyval).two=othercounter;
		othercounter++;
		if(founderror==FALSE){
			if((yyvsp[(3) - (3)].value.exprvalue)->lval==TRUE && (yyvsp[(3) - (3)].value.exprvalue)->numeric==TRUE){
				switch((yyvsp[(3) - (3)].value.exprvalue)->type){
					case INT:	gen_instr("fetchI"); break;
					case FLOAT:	gen_instr("fetchR"); gen_instr("int"); break;
                    default:    break;
				}
			}
			gen_instr_S("jumpz", genlabelw("",(yyval).one));
		}
	}
    break;

  case 57:
#line 731 "ucc.y"
    {
		(yyval).lval=(yyvsp[(3) - (6)].value.exprvalue)->lval; (yyval).numeric=(yyvsp[(3) - (6)].value.exprvalue)->numeric; (yyval).ttype = (yyvsp[(3) - (6)].value.exprvalue)->type; (yyval).one = (yyvsp[(4) - (6)]).one; (yyval).two=(yyvsp[(4) - (6)]).two;
	}
    break;

  case 58:
#line 736 "ucc.y"
    {
					if((yyvsp[(1) - (3)]).lval !=TRUE){
						error("Cannot make assignment. Left hand side is not a correct lval","");
					}
					else if((yyvsp[(3) - (3)]).numeric !=TRUE){
						error("Cannot make assignment, Right hand side is not numeric.","");
					}
					else {
						if(founderror==FALSE){
							if((yyvsp[(3) - (3)]).lval==TRUE){
								switch((yyvsp[(3) - (3)]).ttype){
									case INT:	gen_instr("fetchI"); break;
									case FLOAT:	gen_instr("fetchR"); break;
                                    default:    break;
								}
							}
						}
						if(((yyvsp[(1) - (3)]).ttype==INT && (yyvsp[(3) - (3)]).ttype ==INT) || ((yyvsp[(1) - (3)]).ttype == FLOAT && (yyvsp[(3) - (3)]).ttype==FLOAT)) {
							(yyval.value.exprvalue) = (exprtype*) malloc(sizeof(exprtype));
							if(founderror==FALSE){
								switch((yyvsp[(1) - (3)]).ttype){
									case(INT): (yyval.value.exprvalue)->type=INT; gen_instr("storeI"); break;
									case(FLOAT): (yyval.value.exprvalue)->type=FLOAT; gen_instr("storeR"); break;
                                    default:    break;
								}
							}
							(yyval.value.exprvalue)->lval = TRUE;
							(yyval.value.exprvalue)->numeric =TRUE;

						}
						else if((yyvsp[(1) - (3)]).ttype ==INT && (yyvsp[(3) - (3)]).ttype==FLOAT){
							warning("expressons are of different type, data may be lost","");
							(yyval.value.exprvalue) = (exprtype*) malloc(sizeof(exprtype));
							(yyval.value.exprvalue)->type = INT;
							(yyval.value.exprvalue)->lval=TRUE;
							(yyval.value.exprvalue)->numeric=TRUE;
							if(founderror==FALSE){
								gen_instr("int");
								gen_instr("storeI");
							}
						}
						else if((yyvsp[(1) - (3)]).ttype ==FLOAT && (yyvsp[(3) - (3)]).ttype ==INT) {
							warning("expression are of different type, data may be lost","");
							(yyval.value.exprvalue) = (exprtype*) malloc(sizeof(exprtype));
							(yyval.value.exprvalue)->type=FLOAT;
							(yyval.value.exprvalue)->numeric=TRUE;
							(yyval.value.exprvalue)->lval=TRUE;
							if(founderror==FALSE){
								gen_instr("flt");
								gen_instr("storeR");
							}
						}

					}
				}
    break;

  case 59:
#line 791 "ucc.y"
    {
			(yyval.value.exprvalue) = (exprtype*) malloc(sizeof(exprtype));
			(yyval.value.exprvalue)->lval = (yyvsp[(1) - (1)]).lval; (yyval.value.exprvalue)->numeric = (yyvsp[(1) - (1)]).numeric; (yyval.value.exprvalue)->type =(yyvsp[(1) - (1)]).ttype;
			}
    break;

  case 60:
#line 795 "ucc.y"
    { yyerrok; error("(unexpected token after equal operator in expr)","");}
    break;

  case 61:
#line 799 "ucc.y"
    {
		if(founderror==FALSE){
			if((yyvsp[(1) - (2)]).numeric==TRUE){
				switch((yyvsp[(1) - (2)]).ttype){
					case INT:	if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchI"); break;
					case FLOAT:	if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchR"); break;
                    default:    break;
				}
			}
		}
	}
    break;

  case 62:
#line 810 "ucc.y"
    {
		if(founderror==FALSE){
			if((yyvsp[(4) - (4)]).numeric==TRUE){
				switch((yyvsp[(4) - (4)]).ttype){
					case INT:	if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchI"); break;
					case FLOAT:	if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchR"); break;
                    default:    break;
				}
			}
		}
					(yyval).lval = FALSE;
					if((yyvsp[(1) - (4)]).numeric==TRUE && (yyvsp[(4) - (4)]).numeric==TRUE){
						(yyval).numeric = TRUE;
						(yyval).ttype=INT;
						if(((yyvsp[(1) - (4)]).ttype==INT && (yyvsp[(4) - (4)]).ttype ==INT) || ((yyvsp[(1) - (4)]).ttype == FLOAT && (yyvsp[(4) - (4)]).ttype==FLOAT)) {(yyval).ttype=INT;
							if(founderror==FALSE){
                                                                        switch((yyvsp[(2) - (4)].value.relopvalue)){
                                                                                case NEQ:       if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("neI");
                                                                                                else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("neR");
                                                                                                break;
                                                                                case EQEQ:      if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("eqI");
                                                                                                else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("eqR");
                                                                                                break;
                                                                                default:    break;
                                                                        }
                                                        }

						}
						else if((yyvsp[(1) - (4)]).ttype ==INT && (yyvsp[(4) - (4)]).ttype==FLOAT){
							warning("expressons are of different type, data may be lost","");
							(yyval).ttype = INT;
								if(founderror==FALSE){
                                                                        switch((yyvsp[(2) - (4)].value.relopvalue)){
                                                                                case NEQ:       gen_instr("fltb");
                                                                                                gen_instr("neR");
                                                                                                break;
                                                                                case EQEQ:       gen_instr("fltb");
                                                                                                gen_instr("eqR");
                                                                                                break;
                                                                                default:    break;
                                                                        }
                                                                }

						}
						else if((yyvsp[(1) - (4)]).ttype ==FLOAT && (yyvsp[(4) - (4)]).ttype ==INT) {
							 warning("expression are of different type, data may be lost","");
							(yyval).ttype=INT;
							if(founderror==FALSE){
                                                                        switch((yyvsp[(2) - (4)].value.relopvalue)){
                                                                                case NEQ:       gen_instr("flt");
                                                                                                gen_instr("neR");
                                                                                                break;
                                                                                case EQEQ:       gen_instr("flt");
                                                                                                gen_instr("eqR");
                                                                                                break;
                                                                                default:    break;
                                                                        }
                                                         }
						}
					}
					else{ error("non numeric in operation",""); (yyval).numeric=TRUE; }
				}
    break;

  case 63:
#line 872 "ucc.y"
    { (yyval).lval = (yyvsp[(1) - (1)]).lval; (yyval).ttype = (yyvsp[(1) - (1)]).ttype; (yyval).numeric= (yyvsp[(1) - (1)]).numeric;}
    break;

  case 64:
#line 873 "ucc.y"
    { yyerrok; error("(unexpected token after equality operator in expr)","");}
    break;

  case 65:
#line 877 "ucc.y"
    {
		if(founderror==FALSE){
			if((yyvsp[(1) - (2)]).numeric==TRUE){
				switch((yyvsp[(1) - (2)]).ttype){
					case INT:	if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchI"); break;
					case FLOAT:	if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchR"); break;
                    default:    break;
                }
			}
		}
	}
    break;

  case 66:
#line 888 "ucc.y"
    {
			if(founderror==FALSE){
				if((yyvsp[(4) - (4)]).numeric==TRUE){
					switch((yyvsp[(4) - (4)]).ttype){
						case INT:	if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchI"); break;
						case FLOAT:	if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchR"); break;
                        default:    break;
					}
				}
			}
						(yyval).lval = FALSE;
						if((yyvsp[(1) - (4)]).numeric == TRUE && (yyvsp[(4) - (4)]).numeric ==TRUE){
							(yyval).numeric=TRUE;
							(yyval).ttype=INT;
							if(((yyvsp[(1) - (4)]).ttype==INT && (yyvsp[(4) - (4)]).ttype ==INT) || ((yyvsp[(1) - (4)]).ttype == FLOAT && (yyvsp[(4) - (4)]).ttype==FLOAT)) {(yyval).ttype=INT;
								if(founderror==FALSE){
									switch((yyvsp[(2) - (4)].value.relopvalue)){
                                        case LES:       if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("ltI");
                                                                else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("ltR");
                                                                            break;
                                        case LEQ:       if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("leI");
                                                                else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("leR");
                                                                            break;
										case GRE:	if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("gtI");
												else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("gtR");
												break;
										case GEQ:	if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("geI");
												else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("geR");
												break;
                                        default:    break;
                                                                        }
								}

							}
							else if((yyvsp[(1) - (4)]).ttype ==INT && (yyvsp[(4) - (4)]).ttype==FLOAT){
								warning("expressons are of different type, data may be lost","");
								(yyval).ttype = INT;
								if(founderror==FALSE){
                                                switch((yyvsp[(2) - (4)].value.relopvalue)){
                                                        case LES:       gen_instr("fltb");
												gen_instr("ltR");
                                                                                                break;
                                                        case LEQ:       gen_instr("fltb");
												gen_instr("leR");
                                                                                                break;
                                                        case GRE:       gen_instr("fltb");
												gen_instr("gtR");
                                                                                                break;
                                                        case GEQ:       gen_instr("fltb");
												gen_instr("geR");
                                                                                                break;
                                                        default:    break;
                                                                        }
                                                                }
							}
							else if((yyvsp[(1) - (4)]).ttype ==FLOAT && (yyvsp[(4) - (4)]).ttype ==INT) {
								warning("expression are of different type, data may be lost","");
								(yyval).ttype = INT;
								if(founderror==FALSE){
                                                                        switch((yyvsp[(2) - (4)].value.relopvalue)){
                                                                                case LES:       gen_instr("flt");
                                                                                                gen_instr("ltR");
                                                                                                break;
                                                                                case LEQ:       gen_instr("flt");
                                                                                                gen_instr("leR");
                                                                                                break;
                                                                                case GRE:       gen_instr("flt");
                                                                                                gen_instr("gtR");
                                                                                                break;
                                                                                case GEQ:       gen_instr("flt");
                                                                                                gen_instr("geR");
                                                                                                break;
                                                                                default:     break;
                                                                        }
                                                                }
							}

						}
						else{
							error("non numeric in operation","");
							(yyval).numeric=FALSE;
						}
					}
    break;

  case 67:
#line 971 "ucc.y"
    { (yyval).lval = (yyvsp[(1) - (1)]).lval; (yyval).ttype = (yyvsp[(1) - (1)]).ttype; (yyval).numeric=(yyvsp[(1) - (1)]).numeric;}
    break;

  case 68:
#line 972 "ucc.y"
    { yyerrok; error("(unexpected token after relational operator","");}
    break;

  case 69:
#line 976 "ucc.y"
    {
		if(founderror==FALSE){
                        if((yyvsp[(1) - (2)]).numeric==TRUE){
                                switch((yyvsp[(1) - (2)]).ttype){
                                        case INT:       if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchI"); break;
                                        case FLOAT:     if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchR"); break;
                                        default:        break;
                                }
                        }
                }

	}
    break;

  case 70:
#line 989 "ucc.y"
    {
			if(founderror==FALSE){
                                if((yyvsp[(4) - (4)]).numeric ==TRUE){
                                        switch((yyvsp[(4) - (4)]).ttype){
                                                case INT:       if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchI"); break;
                                                case FLOAT:     if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchR"); break;
                                                default:        break;
                                        }
                                }
                        }
						(yyval).lval = FALSE;
						if((yyvsp[(1) - (4)]).numeric == TRUE && (yyvsp[(4) - (4)]).numeric==TRUE){
							(yyval).numeric=TRUE;
							if(((yyvsp[(1) - (4)]).ttype==INT && (yyvsp[(4) - (4)]).ttype ==INT) || ((yyvsp[(1) - (4)]).ttype == FLOAT && (yyvsp[(4) - (4)]).ttype==FLOAT)) {(yyval).ttype=(yyvsp[(1) - (4)]).ttype;
								if(founderror==FALSE){
        		                                                switch((yyvsp[(2) - (4)].value.addopvalue)){
                		                                                case PLS:       if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("addI");
                        		                                                        else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("addR");
                                		                                                break;
                                        		                        case MIN:       if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("subI");
                                                		                                else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("subR");
                                                        		                        break;
                                                                        default:        break;
                           	                       		      	}
	                                	            	}
							}
							else if((yyvsp[(1) - (4)]).ttype ==INT && (yyvsp[(4) - (4)]).ttype==FLOAT){ warning("expressons are of different type, data may be lost","");
								(yyval).ttype = FLOAT;
		                                                if(founderror==FALSE){
		                                                        switch((yyvsp[(2) - (4)].value.addopvalue)){
		                                                                case PLS:       gen_instr("fltb");
		                                                                                gen_instr("addR");
		                                                                                break;
		                                                                case MIN:       gen_instr("fltb");
		                                                                                gen_instr("subR");
		                                                                                break;
                                                                        default:        break;
		                                                        }
		                                                }
							}
							else if((yyvsp[(1) - (4)]).ttype ==FLOAT && (yyvsp[(4) - (4)]).ttype ==INT) { warning("expression are of different type, data may be lost","");
								(yyval).ttype = FLOAT;
                        		                        if(founderror==FALSE){
                        		                                switch((yyvsp[(2) - (4)].value.addopvalue)){
                        		                                        case PLS:       gen_instr("flt");
                        		                                                        gen_instr("addR");
                        		                                                        break;
                        		                                        case MIN:       gen_instr("flt");
                        		                                                        gen_instr("subR");
                		                                                                break;
                                                                        default:                break;
                		                                        }
		                                                }
							}
						}
						else{
							error("non numeric in operation","");
							(yyval).numeric=FALSE;
						}

	}
    break;

  case 71:
#line 1050 "ucc.y"
    {(yyval).lval = (yyvsp[(1) - (1)]).lval; (yyval).ttype = (yyvsp[(1) - (1)]).ttype; (yyval).numeric = (yyvsp[(1) - (1)]).numeric;}
    break;

  case 72:
#line 1051 "ucc.y"
    { yyerrok; error("(unexpected token after additive operator)","");}
    break;

  case 73:
#line 1054 "ucc.y"
    {
		if(founderror==FALSE){
			if((yyvsp[(1) - (2)]).numeric==TRUE){
				switch((yyvsp[(1) - (2)]).ttype){
					case INT:	if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchI"); break;
					case FLOAT:	if((yyvsp[(1) - (2)]).lval==TRUE) gen_instr("fetchR"); break;
                    default:    break;
				}
			}
		}
	}
    break;

  case 74:
#line 1065 "ucc.y"
    {
			if(founderror==FALSE){
				if((yyvsp[(4) - (4)]).numeric ==TRUE){
					switch((yyvsp[(4) - (4)]).ttype){
						case INT:	if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchI"); break;
						case FLOAT:	if((yyvsp[(4) - (4)]).lval==TRUE) gen_instr("fetchR"); break;
                        default:    break;
					}
				}
			}
				(yyval).lval = FALSE;
				if((yyvsp[(1) - (4)]).numeric ==TRUE && (yyvsp[(4) - (4)]).numeric ==TRUE){
					(yyval).numeric =TRUE;
					if(((yyvsp[(1) - (4)]).ttype==INT && (yyvsp[(4) - (4)]).ttype ==INT) || ((yyvsp[(1) - (4)]).ttype == FLOAT && (yyvsp[(4) - (4)]).ttype==FLOAT)) {(yyval).ttype = (yyvsp[(1) - (4)]).ttype;
						if(founderror==FALSE){
							switch((yyvsp[(2) - (4)].value.multopvalue)){
								case DIV:	if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("divI");
										else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("divR");
										break;
								case MULT:	if((yyvsp[(1) - (4)]).ttype==INT) gen_instr("mulI");
										else if((yyvsp[(1) - (4)]).ttype==FLOAT) gen_instr("mulR");
										break;
                                        default:    break;
							}
						}
					}
					else if((yyvsp[(1) - (4)]).ttype ==INT && (yyvsp[(4) - (4)]).ttype==FLOAT){
						warning("expressons are of different type, data may be lost","");
						(yyval).ttype = FLOAT;
						if(founderror==FALSE){
							switch((yyvsp[(2) - (4)].value.multopvalue)){
        	                                                case DIV:       gen_instr("fltb");
										gen_instr("divR");
                        	                                                break;
                                	                        case MULT:      gen_instr("fltb");
										gen_instr("mulR");
                                                	                        break;
                                                            default:    break;
	                                                }
						}
					}
					else if((yyvsp[(1) - (4)]).ttype ==FLOAT && (yyvsp[(4) - (4)]).ttype ==INT) {
						warning("expression are of different type, data may be lost","");
						(yyval).ttype = FLOAT;
						if(founderror==FALSE){
							switch((yyvsp[(2) - (4)].value.multopvalue)){
        	                                                case DIV:       gen_instr("flt");
                	                                                        gen_instr("divR");
                        	                                                break;
                                	                        case MULT:      gen_instr("flt");
                                        	                                gen_instr("mulR");
                                                	                        break;
                                                            default:            break;
	                                                }
						}
					}

				}
				else{
					error("non numeric in operation","");
					(yyval).numeric =FALSE;
				}
			}
    break;

  case 75:
#line 1128 "ucc.y"
    {(yyval).lval = (yyvsp[(1) - (1)]).lval; (yyval).ttype = (yyvsp[(1) - (1)]).ttype; (yyval) = (yyvsp[(1) - (1)]); (yyval).numeric=(yyvsp[(1) - (1)]).numeric;}
    break;

  case 76:
#line 1129 "ucc.y"
    { yyerrok; error("(unexpected token after multiplicative operator)","");
				}
    break;

  case 77:
#line 1133 "ucc.y"
    { (yyval).ttype = (yyvsp[(1) - (1)]).ttype; (yyval).lval = FALSE; (yyval).numeric=TRUE;
		if(founderror==FALSE){
			if((yyval).ttype ==INT)
				gen_instr_I("pushcI",(yyvsp[(1) - (1)].value.ivalue));
			else if((yyval).ttype == FLOAT)
				gen_instr_F("pushcR",(yyvsp[(1) - (1)].value.fvalue));
			else if((yyval).ttype == STR){
				gen_instr_S("pushs",(yyvsp[(1) - (1)].value.svalue));
				(yyval).numeric=FALSE;
			}
			else
				error("constant is not a correct type of constant","");
		}
	}
    break;

  case 78:
#line 1147 "ucc.y"
    { Entry *tempE, *tempE2; (yyval.value.svalue) = (yyvsp[(1) - (1)].value.svalue);
				if(strcmp((char*)(yyvsp[(1) - (1)].value.svalue), "main")!=0){
					//if(lookup((char*)$<value.svalue>1, mysymtab) == NULL)
					//	error("variable undeclared, please declare variables before using them","");
					if(1){
						tempE2 = (Entry*) malloc(sizeof(Entry));
						tempE2->name =(char*) strdup((yyvsp[(1) - (1)].value.svalue));
						#ifdef DEBUG
						fprintf(stderr,"the name of the identifier here is:  %s\n", (char*)(yyvsp[(1) - (1)].value.svalue));
						#endif
						if((tempE=lookupB((char*)tempE2->name,mysymtab)) !=NULL){

							if(tempE->self ==VAR || tempE->self == PARAM){
								switch(tempE->self){
									case VAR:
										(yyval).ttype = ((Varb*)(tempE->binding))->type;
										#ifdef DEBUG
										char temp_char = (char)(yyval).ttype;
										if((yyval).ttype !=  NULL) fprintf(stderr,"type is: %s\n", &temp_char);
										if(((Varb*)(tempE->binding))->type !=NULL) fprintf(stderr,"type is: %d\n", ((Varb*)(tempE->binding))->type);
										#endif
										(yyval).lval = TRUE;
										if(((Varb*)(tempE->binding))->type == INT || ((Varb*)(tempE->binding))->type ==FLOAT) (yyval).numeric=TRUE;
										if(founderror==FALSE){
											if(inCscope(tempE2->name, mysymtab) == TRUE)
												gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
											else{
												gen_instr_tI("pushga",getleveldif(tempE2->name,mysymtab),((Varb*)(tempE->binding))->offset);
												//do something else

											}
										}
										break;
									case PARAM:
										(yyval).ttype = ((Paramb*)(tempE->binding))->type;
										#ifdef DEBUG
										fprintf(stderr,"type is: %d\n", (int)(yyval).ttype);
										#endif
										(yyval).lval = TRUE;
										if(((Paramb*)(tempE->binding))->type == INT || ((Paramb*)(tempE->binding))->type ==FLOAT) (yyval).numeric=TRUE;
										if(founderror==FALSE){
											if(inCscope(tempE2->name,mysymtab) ==TRUE){
												gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
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
							(yyval).lval=FALSE;
							(yyval).numeric=FALSE;
							(yyval).ttype=VOID;
							error("Variable is unknown or undelcared, couldn't find in symbol table'","");
						}
					}
				}
				else{
					error("Main is not a variable name","");
						//tempE2 = (Entry*) malloc(sizeof(Entry));
						//tempE2->name = (char*) $<value.svalue>1;

				}
		}
    break;

  case 79:
#line 1218 "ucc.y"
    { (yyval).lval = (yyvsp[(2) - (3)].value.exprvalue)->lval; (yyval).ttype = (yyvsp[(2) - (3)].value.exprvalue)->type; (yyval).numeric= (yyvsp[(2) - (3)].value.exprvalue)->numeric;

				}
    break;

  case 80:
#line 1221 "ucc.y"
    {
				if(founderror==FALSE){
					if((yyvsp[(2) - (2)]).numeric==TRUE){
						if((yyvsp[(1) - (2)].value.addopvalue) == MIN){
							if((yyvsp[(2) - (2)]).lval ==TRUE){
								switch((yyvsp[(2) - (2)]).ttype){
									case INT:	gen_instr("fetchI"); break;
									case FLOAT:	gen_instr("fetchR"); break;
                                    default:    break;
								}
							}
							switch((yyvsp[(2) - (2)]).ttype){
								case INT:	gen_instr("negI"); break;
								case FLOAT:	gen_instr("negR"); break;
                                default:    break;
							}
						}
						else if((yyvsp[(1) - (2)].value.addopvalue) == PLS){
							if((yyvsp[(2) - (2)]).lval == TRUE){
								switch((yyvsp[(2) - (2)]).ttype){
									case INT:	gen_instr("fetchI"); break;
									case FLOAT:	gen_instr("fetchR"); break;
                                    default:    break;
								}
							}
						}
					}
				}
						(yyval).lval = FALSE;
						(yyval).ttype = (yyvsp[(2) - (2)]).ttype;
						if((yyvsp[(2) - (2)]).numeric ==TRUE) (yyval).numeric=TRUE;
						else
							error("cannot change sign of non numeric expression","");
					}
    break;

  case 81:
#line 1255 "ucc.y"
    {
				Entry *tempE, *tempE2; (yyval.value.svalue) = (yyvsp[(2) - (2)].value.svalue);
                                if(strcmp((char*)(yyvsp[(2) - (2)].value.svalue), "main")!=0){
                                        if(lookup((char*)(yyvsp[(2) - (2)].value.svalue), mysymtab) == NULL)
										error("variable undeclared, please declare variables before using them","");
                                        else{
                                                tempE2 = (Entry*) malloc(sizeof(Entry));
                                                tempE2->name =(char*) (yyvsp[(2) - (2)].value.svalue);
                        if((tempE=lookupB((char*)(yyvsp[(2) - (2)].value.svalue),mysymtab)) !=NULL){

                            if(tempE->self ==VAR || tempE->self == PARAM){
                                switch(tempE->self){
                                    case VAR:
                                        (yyval).ttype = ((Varb*)(tempE->binding))->type;
                                        #ifdef DEBUG
                                        fprintf(stderr,"type is: %d\n", (int)(yyval).ttype);
                                        #endif
                                        (yyval).lval = FALSE;
                                        if(((Varb*)(tempE->binding))->type == INT || ((Varb*)(tempE->binding))->type ==FLOAT)
                                            (yyval).numeric=TRUE;
										if(founderror==FALSE){
                                            if(inCscope((char*)strdup((yyvsp[(2) - (2)].value.svalue)), mysymtab) == TRUE)
                                                gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
                                            else{
                                                gen_instr_tI("pushga",getleveldif((yyvsp[(2) - (2)].value.svalue),mysymtab),((Varb*)(tempE->binding))->offset);
                                    //do something else

                                            }
                                        }
                                        break;
                                    case PARAM:
                                        (yyval).ttype = ((Paramb*)(tempE->binding))->type;
                                        #ifdef DEBUG
                                        fprintf(stderr,"type is: %d\n", (int)(yyval).ttype);
                                        #endif
                                        (yyval).lval = FALSE;
                                        if(((Paramb*)(tempE->binding))->type == INT || ((Paramb*)(tempE->binding))->type ==FLOAT)
                                            (yyval).numeric=TRUE;
                                        if(founderror==FALSE){
                                            if(inCscope((char*)(yyvsp[(2) - (2)].value.svalue),mysymtab) ==TRUE){
                                                gen_instr_I("pusha", ((Varb*)(tempE->binding))->offset);
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
                                                        (yyval).lval=FALSE;
                                                        (yyval).numeric=FALSE;
                                                        (yyval).ttype=VOID;
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
    break;

  case 82:
#line 1323 "ucc.y"
    { (yyval).ttype = (yyvsp[(1) - (1)]).ttype; (yyval).lval = FALSE; (yyval).numeric=(yyvsp[(1) - (1)]).numeric; }
    break;

  case 83:
#line 1325 "ucc.y"
    { yyerrok; error("(unexpected token after unary additive operator)","");

					}
    break;

  case 84:
#line 1330 "ucc.y"
    { yyerrok; error("(unexpected token before rpar)","");

					}
    break;

  case 85:
#line 1336 "ucc.y"
    {(yyval).lval = FALSE; Funcb* tempb; Entry* tempE; Entry *tempE2;
                                if((tempb=lookup((char*)(yyvsp[(1) - (3)].value.svalue),mysymtab)) == NULL){
                                        error("function undeclared, please declare functions before using them","");
				}
                                else{
                                        tempE2 = (Entry*) malloc(sizeof(Entry));
                                        tempE2->name = (char*)(yyvsp[(1) - (3)].value.svalue);
                                        if((tempE=lookupB((char*)(yyvsp[(1) - (3)].value.svalue),mysymtab))!=NULL){
                                                if(tempE->self ==FUNC){
							if(tempb->returntype !=VOID) (yyval).lval =TRUE; else (yyval).lval=FALSE;
                                                        if(tempb->num_param != 0)
                                                                error("Function call without correct number of parameters if any","");
                                                        (yyval).ttype = tempb->returntype;
                                                        if((yyval).ttype == INT || (yyval).ttype ==FLOAT) (yyval).numeric =TRUE; else (yyval).numeric =FALSE;
							if(founderror==FALSE){
								gen_instr_I("enter",1);
								gen_call(genlabelw((yyvsp[(1) - (3)].value.svalue), tempb->label), 0);
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
    break;

  case 86:
#line 1363 "ucc.y"
    {(yyval).ttype =(yyvsp[(1) - (1)]).ttype; (yyval).numeric = (yyvsp[(1) - (1)]).numeric; (yyval).lval = (yyvsp[(1) - (1)]).lval;}
    break;

  case 87:
#line 1366 "ucc.y"
    {(yyval).numeric =(yyvsp[(1) - (2)]).numeric; (yyval).lval = FALSE; (yyval).ttype = (yyvsp[(1) - (2)]).ttype;
				if((yyvsp[(1) - (2)]).funcent!=NULL){
						if(((yyvsp[(1) - (2)]).funcent)->self == FUNC){
							if( ((Funcb*)(((yyvsp[(1) - (2)]).funcent)->binding))->returntype != VOID) (yyval).numeric = TRUE; else (yyval).numeric=FALSE;
						}
						if(founderror==FALSE){
							if(strcmp("scanf",(yyvsp[(1) - (2)]).funcent->name)==0){
//								gen_call("$scanf",((Funcb*)($1.funcent->binding))->actual_num);
								gen_call("$scanf",(yyvsp[(1) - (2)]).params);
							}
							else if(strcmp("printf", (yyvsp[(1) - (2)]).funcent->name)==0){
//								gen_call("$printf",((Funcb*)($1.funcent->binding))->actual_num);
								gen_call("$printf",(yyvsp[(1) - (2)]).params);
							}
							else{
								if( ((Funcb*)((yyvsp[(1) - (2)]).funcent->binding))->label==0) ((Funcb*)((yyvsp[(1) - (2)]).funcent->binding))->label=getlabel();
								gen_call( genlabelw((yyvsp[(1) - (2)]).funcent->name,((Funcb*)((yyvsp[(1) - (2)]).funcent->binding))->label),
									((Funcb*)((yyvsp[(1) - (2)]).funcent->binding))->num_param);
							}
						}
				}
			}
    break;

  case 88:
#line 1393 "ucc.y"
    {
		(yyval).funcent =NULL;
		(yyval).funcent = lookupB((char*)(yyvsp[(1) - (2)].value.svalue),mysymtab);
		#ifdef DEBUG
		printTree(mysymtab);
		fprintf(stderr,"this the name of function called and the lookup value: %s\n",(yyvsp[(1) - (2)].value.svalue));
		if(lookupB((yyvsp[(1) - (2)].value.svalue),mysymtab)==NULL) fprintf(stderr,"it was null\n");
		else fprintf(stderr,"wasn't null\n");
		#endif
		if ((yyval).funcent != NULL){
			(yyval).name = (yyval).funcent->name;
			if(founderror==FALSE) gen_instr_I("enter",1);
		}
	}
    break;

  case 89:
#line 1407 "ucc.y"
    {
        Entry *tempE, *tempE2;
        (yyval).lval = FALSE;
        //listnodeE* tempexprN;
        //ListE * tempLE;
        //int a;
        Funcb* tempB;
        if((tempB=lookup((char*)(yyvsp[(1) - (4)].value.svalue),mysymtab)) ==NULL){
            error("function undelcared, please declare functions before using them","");
            error("1","");
            (yyval).funcent=NULL;
        }
        else {
					//warning("just checking value of entry: %s",$<value.funcentvalue>$->name);
            tempE2 = (Entry*) malloc(sizeof(Entry));
            tempE2->name = (char*) (yyvsp[(1) - (4)].value.svalue);
            if( (tempE=lookupB((char*)(yyvsp[(1) - (4)].value.svalue),mysymtab))!=NULL){
                if(tempE->self != FUNC){
                    error("function undeclared, please declare functions before using them", "");
                    error("2","");
                    (yyval).funcent=NULL;
                }
                else{
                    if(tempB->num_param ==0){
                        error("Paramter given for a function that takes no parameters.","");
                    }
                    else if(tempB->num_param == -1){
                        #ifdef DEBUG
                        fprintf(stderr,"SPRINTF OR PRINTF mismatch: FUNCTION NAME: %s\n",(yyvsp[(1) - (4)].value.svalue));
                        fprintf(stderr,"SPRINTF OR PRINTF: FUNCTION TYPE: %d\n",(int)(yyvsp[(4) - (4)].value.exprvalue)->type);
//                                                            fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
  //                                                          fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                        fprintf(stderr,"SPRINTF OR PRINTF: $4 TYPE: %d\n",(int)(yyvsp[(4) - (4)].value.exprvalue)->type);
                        fprintf(stderr,"SPRINTF OR PRINTF: tempB->param_type[0] TYPE: %d\n",(int)tempB->param_type[0]);
                        #endif
                        if((yyvsp[(4) - (4)].value.exprvalue)->type != tempB->param_type[0]){
                            error("parameter type is different in declaration and in function call","");
                        }
                        else{
                            if(founderror==FALSE){
										//gen_instr_S("pushs",$<value.svalue>4);
                            }
                        }
                        (yyval).ttype = tempB->param_type[0];
                        if((yyval).ttype==INT || (yyval).ttype ==FLOAT)
                            (yyval).numeric=TRUE;
                        else
                            (yyval).numeric=FALSE;
                        (yyval).funcent=(yyvsp[(3) - (4)]).funcent;
						(yyval).params = 1;
                    }
                    else{
                        if((yyvsp[(4) - (4)].value.exprvalue)->lval==TRUE && (yyvsp[(4) - (4)].value.exprvalue)->numeric==TRUE){
                            if(founderror==FALSE){
                                switch((yyvsp[(4) - (4)].value.exprvalue)->type){
                                    case INT:	gen_instr("fetchI"); break;
                                    case FLOAT:	gen_instr("fetchR"); break;
                                    default:    break;
                                }
                            }
                        }
                        if(tempB->param_type !=NULL){
                            if((yyvsp[(4) - (4)].value.exprvalue)->type != tempB->param_type[0]){
                                #ifdef DEBUG
                                fprintf(stderr,"Function mismatch 2: FUNCTION NAME: %s\n",(yyvsp[(1) - (4)].value.svalue));
                                fprintf(stderr,"Function mismatch 2: FUNCTION TYPE: %d\n",(int)(yyvsp[(4) - (4)].value.exprvalue)->type);
                                            //                                                            fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                            //                                                          fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                #endif
                                if(tempB->param_type[0]!=INT && tempB->param_type[0]!=FLOAT)
                                    error("Parameter type is different in declaration and in function call","");
                                else if(tempB->param_type[0]==INT){
                                        #ifdef DEBUG
                                        fprintf(stderr,"Function mismatch 3: FUNCTION NAME: %s\n",(yyvsp[(1) - (4)].value.svalue));
                                        fprintf(stderr,"Function mismatch 3: FUNCTION TYPE: %d\n",(int)(yyvsp[(4) - (4)].value.exprvalue)->type);
                                                //                                                            fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                                //                                                          fprintf(stderr,"Function mismatch 1: FUNCTION NAME: %s\n",$1);
                                        #endif
                                        switch((yyvsp[(4) - (4)].value.exprvalue)->type){
                                            case FLOAT:
                                                warning("Paramter expression will lose data because of different type","");
                                                if(founderror==FALSE)
                                                    gen_instr("int");
                                                break;
                                            case INT:	break;
                                            default:	error("Parameter type is different in declaration and function call","");
                                                        break;
                                        }
                                }
                                else if(tempB->param_type[0]==FLOAT){
                                    #ifdef DEBUG
                                    fprintf(stderr,"Function mismatch 4: FUNCTION NAME: %s\n",(yyvsp[(1) - (4)].value.svalue));
                                    #endif
                                    switch((yyvsp[(4) - (4)].value.exprvalue)->type){
                                        case INT:	warning("Parameter expression is different type than in declaration","");
                                                    if(founderror==FALSE)
                                                        gen_instr("flt");
                                                    break;
                                        case FLOAT:	break;
                                        default:	error("Parameter type is different in declaration and function call","");
                                                            break;
                                    }
                                }

                            }
                        }
                        (yyval).funcent=(yyvsp[(3) - (4)]).funcent;

                        if(tempB->param_type !=NULL)
                            (yyval).ttype=tempB->param_type[0];
                        if((yyval).ttype==INT || (yyval).ttype==FLOAT)
                            (yyval).numeric =TRUE;
                        else
                            (yyval).numeric=FALSE;
                        (yyval).params=1;
                    }
                }
            }
            else
                error("Function is undeclared","");
            free(tempE2); tempE2=NULL;

        }
    }
    break;

  case 90:
#line 1532 "ucc.y"
    {}
    break;

  case 91:
#line 1533 "ucc.y"
    {
			Entry *tempE, *tempE2;
            (yyval).lval = FALSE;
            //listnodeE* tempexprN;
            //ListE * tempLE;
            //int a;
            Funcb* tempB;
            if((yyvsp[(1) - (4)]).funcent==NULL){
            	error("function undelcared, please declare functions before using them","");
			   error("3","");
			}
            else {
				(yyval).funcent = (yyvsp[(1) - (4)]).funcent;
                tempE2 = (Entry*) malloc(sizeof(Entry));
                tempE2->name = (char*) (yyvsp[(1) - (4)]).funcent->name;
				tempB=lookup((char*)(yyvsp[(1) - (4)]).funcent->name,mysymtab);
                if( (tempE=lookupB((char*)(yyvsp[(1) - (4)]).funcent->name,mysymtab))!=NULL){
                	if(tempE->self != FUNC){
                    	error("function undeclared, please declare functions before using them", "");
						error("4","");
					}
                    else{
                    	if(tempB->num_param ==0){
						}
 					    else if(tempB->num_param == -1){
                        	(yyval).ttype = tempB->param_type[(yyvsp[(1) - (4)]).params];
                            if((yyval).ttype==INT || (yyval).ttype ==FLOAT) (yyval).numeric=TRUE; else (yyval).numeric=FALSE;
								(yyval).params = (yyvsp[(1) - (4)]).params +1;
								(yyval).funcent=(yyvsp[(1) - (4)]).funcent;
								if((yyvsp[(4) - (4)].value.exprvalue)->lval==TRUE && (yyvsp[(4) - (4)].value.exprvalue)->numeric==TRUE && strcmp("scanf",(yyval).funcent->name)!=0){
									if(founderror==FALSE){
										switch((yyvsp[(4) - (4)].value.exprvalue)->type){
											case INT:	gen_instr("fetchI"); break;
											case FLOAT:	gen_instr("fetchR"); break;
                                            default:    break;
										}
									}
								}
								
						}
                        else if((yyval).params < tempB->num_param){
                        	if((yyvsp[(4) - (4)].value.exprvalue)->type != tempB->param_type[(yyvsp[(1) - (4)]).params]){
                            	#ifdef DEBUG
                                fprintf(stderr,"Function mismatch before warning: FUNCTION NAME: %s\n",(yyvsp[(1) - (4)]).name);
                                #endif

                                warning("Parameter type is different in declaration and in function call","");
								if(founderror==FALSE){
									if((yyvsp[(4) - (4)].value.exprvalue)->lval==TRUE){
										switch((yyvsp[(4) - (4)].value.exprvalue)->type){
											case INT:	gen_instr("fetchI"); break;
											case FLOAT:	gen_instr("fetchR"); break;
                                            default:    break;
										}
									}
									if(tempB->param_type[(yyvsp[(1) - (4)]).params]==FLOAT){
										gen_instr("flt");
									}
									else if(tempB->param_type[(yyvsp[(1) - (4)]).params]==INT){
										gen_instr("int");
									}
								}
							}
							else{
								if(founderror==FALSE){
									if((yyvsp[(4) - (4)].value.exprvalue)->lval==TRUE){
										switch((yyvsp[(4) - (4)].value.exprvalue)->type){
											case INT:	gen_instr("fetchI"); break;
											case FLOAT:	gen_instr("fetchR"); break;
                                            default:    break;
										}
									}
								}

							}
                            (yyval).ttype=tempB->param_type[(yyvsp[(1) - (4)]).params];
                            if((yyval).ttype==INT || (yyval).ttype==FLOAT) (yyval).numeric =TRUE; else (yyval).numeric=FALSE;
							(yyval).params=(yyvsp[(1) - (4)]).params +1;
							(yyval).funcent=(yyvsp[(1) - (4)]).funcent;
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
    break;

  case 92:
#line 1632 "ucc.y"
    { (yyval.value.svalue) = (yyvsp[(1) - (1)].value.svalue);
				(yyval).ttype = STR;
				(yyval).lval = FALSE;
				(yyval).numeric=FALSE;
				}
    break;

  case 93:
#line 1637 "ucc.y"
    {(yyval.value.ivalue) = (yyvsp[(1) - (1)].value.ivalue);
				(yyval).ttype = INT;
				(yyval).lval = FALSE;
				(yyval).numeric= TRUE;
				}
    break;

  case 94:
#line 1642 "ucc.y"
    { (yyval.value.fvalue) = (yyvsp[(1) - (1)].value.fvalue);
				(yyval).ttype = FLOAT;
				(yyval).lval = FALSE;
				(yyval).numeric= TRUE;
				}
    break;

  case 95:
#line 1650 "ucc.y"
    { (yyval.value.lstvalue) = mklist(((char*)(yyvsp[(1) - (1)].value.svalue)));}
    break;

  case 96:
#line 1651 "ucc.y"
    { (yyval.value.lstvalue) = appendList( (yyvsp[(1) - (3)].value.lstvalue), (yyvsp[(3) - (3)].value.svalue));}
    break;

  case 97:
#line 1652 "ucc.y"
    {yyerrok; error("(unexpected token after comma)","");
						//deleteList($1);

				}
    break;

  case 98:
#line 1659 "ucc.y"
    { (yyval.value.addopvalue) = (yyvsp[(1) - (1)].value.addopvalue);}
    break;

  case 99:
#line 1660 "ucc.y"
    { (yyval.value.addopvalue) = (yyvsp[(1) - (1)].value.addopvalue);}
    break;

  case 100:
#line 1663 "ucc.y"
    { (yyval.value.multopvalue) = (yyvsp[(1) - (1)].value.multopvalue);}
    break;

  case 101:
#line 1664 "ucc.y"
    {(yyval.value.multopvalue) = (yyvsp[(1) - (1)].value.multopvalue);}
    break;

  case 102:
#line 1667 "ucc.y"
    { (yyval.value.eqopvalue) = (yyvsp[(1) - (1)].value.eqopvalue);}
    break;

  case 103:
#line 1668 "ucc.y"
    { (yyval.value.eqopvalue) = (yyvsp[(1) - (1)].value.eqopvalue);}
    break;

  case 104:
#line 1671 "ucc.y"
    { (yyval.value.relopvalue) = (yyvsp[(1) - (1)].value.relopvalue);}
    break;

  case 105:
#line 1672 "ucc.y"
    { (yyval.value.relopvalue) = (yyvsp[(1) - (1)].value.relopvalue);}
    break;

  case 106:
#line 1673 "ucc.y"
    { (yyval.value.relopvalue) = (yyvsp[(1) - (1)].value.relopvalue);}
    break;

  case 107:
#line 1674 "ucc.y"
    { (yyval.value.relopvalue) = (yyvsp[(1) - (1)].value.relopvalue);}
    break;


/* Line 1267 of yacc.c.  */
#line 3466 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1678 "ucc.y"


int yyerror(char *s)
{
//	fprintf(stderr,"Error: Line: %d: %s\n", Line_Number, s);
	fprintf(stderr,"Error:::%s:%d-> %s\n",filename,Line_Number,s);
    return 0;
}


int warning(char *s1, char* s2)
{
//	fprintf(stderr,"Warning: Line: %d: %s %s\n",Line_Number,s1,s2);
	fprintf(stderr,":::::Warning:::%s:%d-> %s %s\n",filename,Line_Number,s1,s2);
    return 0;
}

int error(char* s1, char* s2){
//	fprintf(stderr,"Error: Line: %d: %s %s\n",Line_Number,s1,s2);
	fprintf(stderr,"Error:::%s:%d-> %s %s\n",filename,Line_Number,s1, s2);
	founderror=TRUE;
    return 0;
}


