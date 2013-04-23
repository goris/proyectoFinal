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
     PROGRAMA = 258,
     IMPRIME = 259,
     DIBUJA = 260,
     FUNCION = 261,
     REGRESA = 262,
     VAR = 263,
     BOOL = 264,
     NUM = 265,
     TEXTO = 266,
     SI = 267,
     SINO = 268,
     HAZ = 269,
     POR = 270,
     MIENTRAS = 271,
     LINEA = 272,
     CUADRADO = 273,
     TRIANGULO = 274,
     CIRCULO = 275,
     VERDADERO = 276,
     FALSO = 277,
     CTE_NUM = 278,
     CTE_TEXTO = 279,
     ID = 280,
     SUM = 281,
     MIN = 282,
     PRO = 283,
     DIV = 284,
     EQU = 285,
     LT = 286,
     GT = 287,
     LTE = 288,
     GTE = 289,
     DIF = 290,
     LPA = 291,
     RPA = 292,
     LBR = 293,
     RBR = 294,
     LSQ = 295,
     RSQ = 296,
     SEM = 297,
     DOU = 298,
     COM = 299,
     DOT = 300,
     DEQ = 301
   };
#endif
/* Tokens.  */
#define PROGRAMA 258
#define IMPRIME 259
#define DIBUJA 260
#define FUNCION 261
#define REGRESA 262
#define VAR 263
#define BOOL 264
#define NUM 265
#define TEXTO 266
#define SI 267
#define SINO 268
#define HAZ 269
#define POR 270
#define MIENTRAS 271
#define LINEA 272
#define CUADRADO 273
#define TRIANGULO 274
#define CIRCULO 275
#define VERDADERO 276
#define FALSO 277
#define CTE_NUM 278
#define CTE_TEXTO 279
#define ID 280
#define SUM 281
#define MIN 282
#define PRO 283
#define DIV 284
#define EQU 285
#define LT 286
#define GT 287
#define LTE 288
#define GTE 289
#define DIF 290
#define LPA 291
#define RPA 292
#define LBR 293
#define RBR 294
#define LSQ 295
#define RSQ 296
#define SEM 297
#define DOU 298
#define COM 299
#define DOT 300
#define DEQ 301




/* Copy the first part of user declarations.  */
#line 1 "sintax.y"

/*
*
* D E C L A R A C I O N E S
*
*/
	#include <string>
	#include <stack>
	#include <vector>
	#include <map>
	#include <iostream>
	#include <sstream>

	#include "utilities/Cuadruplo.h"

	struct Node {
		int tipo;
		int valor_num;
		int id;
		std::string nombre;
		std::string valor_str;
		std::string scope;
	};

	typedef std::map <std::string, Node*> MapType;

	struct Funcion {
		int tipo;
		int param_cant;
		int vars_cant;
		int cuad_ini;
		std::string nombre;
		MapType variables;
	};
	
	typedef std::map <std::string, Funcion*> MapFunc;

	extern int contlin;
	extern int yyerror (char *s);
	extern int yylex();
	extern  FILE *yyin;
	extern int yyparse();
	extern char * yytext;

	int id_actual;
	int param_count;
	int tmp_actual;
	int cuad_actual;
	std::string avail;
	std::stack <std::string> var_actual;
	std::string tipo_actual;
	std::string scope_actual;
	std::vector<std::string> scopes;	
	std::stack<Node*> aux_vars;
	std::stack<Node*> pilaO;
	std::stack<int> pOper;
	std::stack<int> pSaltos;
	std::vector<Cuadruplo> vec_cuadruplos;
	MapType map_vars;
	MapFunc map_func;

	/*
	*
	* 
	*	C U B O    S E M A N T I C O
	*
	* 0 num 1 bool 2 text  [indices]
	* 1 num 2 bool 3 text 0 ERRROR
	* 0+ 1- 2* 3/ 4= 5< 6> 7<= 8>= 9!= 10== 11( 12) 13goto 14gotoV
	* 15gotoF 16Era 17GoSub 18Ret 
	* [tipo1] [tipo2] [operador] 
	*/
	int cubo_sem [3][3][11] = { 0 };

	int convierteTipo(std::string);
	void creaCubo();
	void imprimeCubo();
	void manipulaStack();
	void actualizaScope(std::string);
	void creaVariable();
	void creaConstanteNum();
	void creaConstanteBool(int);
	void creaConstanteStr(const char *);
	void agregaFuncion();
	void actualizaTipoVariables();
	void meterPilaO();
	void meterPilaOper(int);
	void imprimePila(std::stack<Node*>);
	void imprimePila(int a);
	void checaOperador(int);
	void cuadruploEstatuto(int);
	void imprimeVector(std::vector<Cuadruplo>);
	MapType creaTablaFuncion(std::string);
	



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
typedef union YYSTYPE
#line 98 "sintax.y"
{
	int int_val;	
	float float_val;
	char* text;
}
/* Line 193 of yacc.c.  */
#line 291 "quack.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 304 "quack.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNRULES -- Number of states.  */
#define YYNSTATES  216

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,    15,    16,    23,    24,    25,
      29,    34,    37,    38,    40,    42,    44,    47,    50,    53,
      54,    56,    58,    60,    61,    65,    67,    70,    71,    76,
      79,    82,    86,    87,    88,    93,    95,    96,   106,   107,
     113,   114,   120,   123,   126,   127,   129,   131,   133,   136,
     139,   140,   142,   144,   146,   148,   150,   152,   154,   155,
     159,   160,   164,   165,   169,   170,   171,   175,   176,   180,
     181,   185,   186,   187,   192,   194,   196,   198,   200,   201,
     205,   207,   208,   210,   212,   213,   214,   229,   230,   234,
     235,   237,   238,   239,   240,   246,   249,   254,   255,   257,
     259,   261,   263,   273,   274,   275,   287,   288,   289,   299,
     305,   311,   319
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    -1,    -1,     3,    25,    49,    38,    51,
      96,    50,    57,    39,    -1,    -1,     8,    53,    56,    52,
      42,    51,    -1,    -1,    -1,    25,    54,    55,    -1,    40,
      23,    41,    55,    -1,    44,    53,    -1,    -1,    10,    -1,
      11,    -1,     9,    -1,    58,    57,    -1,    76,    57,    -1,
     105,    57,    -1,    -1,    69,    -1,    59,    -1,    73,    -1,
      -1,    25,    60,    61,    -1,    66,    -1,    62,    42,    -1,
      -1,    63,    36,    64,    37,    -1,    77,    65,    -1,    44,
      64,    -1,    40,    41,    65,    -1,    -1,    -1,    30,    67,
      68,    42,    -1,    77,    -1,    -1,    12,    36,    77,    37,
      38,    70,    57,    39,    71,    -1,    -1,    13,    72,    38,
      57,    39,    -1,    -1,     4,    36,    74,    37,    42,    -1,
      80,    75,    -1,    45,    74,    -1,    -1,   110,    -1,   107,
      -1,   106,    -1,    80,    78,    -1,    79,    80,    -1,    -1,
      31,    -1,    32,    -1,    35,    -1,    33,    -1,    34,    -1,
      46,    -1,    30,    -1,    -1,    85,    81,    82,    -1,    -1,
      26,    83,    80,    -1,    -1,    27,    84,    80,    -1,    -1,
      -1,    90,    86,    87,    -1,    -1,    28,    88,    85,    -1,
      -1,    29,    89,    85,    -1,    -1,    -1,    36,    91,    77,
      37,    -1,    92,    -1,    95,    -1,    23,    -1,    24,    -1,
      -1,    25,    93,    94,    -1,    62,    -1,    -1,    21,    -1,
      22,    -1,    -1,    -1,    56,    97,     6,    25,    98,    36,
     100,    37,    38,    51,    57,    99,    39,    96,    -1,    -1,
       7,    92,    42,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      56,   102,    25,   103,   104,    -1,    44,   101,    -1,    40,
      23,    41,   104,    -1,    -1,   116,    -1,   113,    -1,   114,
      -1,   115,    -1,    15,    36,    77,    43,    77,    37,    38,
      57,    39,    -1,    -1,    -1,    14,   108,    38,    57,    39,
      16,    36,    77,    37,   109,    42,    -1,    -1,    -1,    16,
     111,    36,    77,    37,   112,    38,    57,    39,    -1,    18,
      36,    23,    37,    42,    -1,    20,    36,    23,    37,    42,
      -1,    17,    36,    23,    44,    23,    37,    42,    -1,    19,
      36,    24,    44,    23,    37,    42,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   139,   138,   142,   142,   144,   145,   145,
     146,   147,   148,   150,   151,   152,   154,   155,   156,   157,
     159,   160,   161,   162,   162,   163,   164,   165,   165,   167,
     168,   169,   170,   173,   173,   174,   178,   177,   180,   180,
     181,   183,   184,   185,   186,   188,   189,   190,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   202,
     203,   203,   204,   204,   205,   206,   206,   207,   207,   208,
     208,   209,   210,   210,   211,   212,   213,   214,   215,   215,
     216,   217,   219,   220,   222,   223,   222,   226,   227,   228,
     229,   229,   230,   231,   230,   233,   234,   235,   237,   238,
     239,   240,   243,   245,   246,   245,   248,   249,   248,   251,
     253,   255,   257
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAMA", "IMPRIME", "DIBUJA",
  "FUNCION", "REGRESA", "VAR", "BOOL", "NUM", "TEXTO", "SI", "SINO", "HAZ",
  "POR", "MIENTRAS", "LINEA", "CUADRADO", "TRIANGULO", "CIRCULO",
  "VERDADERO", "FALSO", "CTE_NUM", "CTE_TEXTO", "ID", "SUM", "MIN", "PRO",
  "DIV", "EQU", "LT", "GT", "LTE", "GTE", "DIF", "LPA", "RPA", "LBR",
  "RBR", "LSQ", "RSQ", "SEM", "DOU", "COM", "DOT", "DEQ", "$accept",
  "program", "@1", "@2", "vars", "@3", "vars2", "@4", "vars3", "tipo",
  "bloque", "estatutos", "asig_llamada", "@5", "llamada_", "llamada", "@6",
  "varsss", "varsss2", "asignacion", "@7", "asignacion1", "condicion",
  "@8", "condicion1", "@9", "escritura", "escritura1", "escritura2",
  "ciclos", "sexp", "expresion1", "operadores", "exp", "@10", "exp1",
  "@11", "@12", "termino", "@13", "termino1", "@14", "@15", "factor",
  "@16", "var_cte", "@17", "llamada_opt", "cte_bool", "funciones", "@18",
  "@19", "funciones1", "varss", "varss2", "@20", "@21", "varss3", "dibuja",
  "por", "haz", "@22", "@23", "mientras", "@24", "@25", "cuadrado",
  "circulo", "linea", "triangulo", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    49,    50,    48,    52,    51,    51,    54,    53,
      55,    55,    55,    56,    56,    56,    57,    57,    57,    57,
      58,    58,    58,    60,    59,    61,    61,    63,    62,    64,
      65,    65,    65,    67,    66,    68,    70,    69,    72,    71,
      71,    73,    74,    75,    75,    76,    76,    76,    77,    78,
      78,    79,    79,    79,    79,    79,    79,    79,    81,    80,
      83,    82,    84,    82,    82,    86,    85,    88,    87,    89,
      87,    87,    91,    90,    90,    92,    92,    92,    93,    92,
      94,    94,    95,    95,    97,    98,    96,    96,    99,    99,
     100,   100,   102,   103,   101,   104,   104,   104,   105,   105,
     105,   105,   106,   108,   109,   107,   111,   112,   110,   113,
     114,   115,   116
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     9,     0,     6,     0,     0,     3,
       4,     2,     0,     1,     1,     1,     2,     2,     2,     0,
       1,     1,     1,     0,     3,     1,     2,     0,     4,     2,
       2,     3,     0,     0,     4,     1,     0,     9,     0,     5,
       0,     5,     2,     2,     0,     1,     1,     1,     2,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     3,     0,     3,     0,     0,     3,     0,     3,     0,
       3,     0,     0,     4,     1,     1,     1,     1,     0,     3,
       1,     0,     1,     1,     0,     0,    14,     0,     3,     0,
       1,     0,     0,     0,     5,     2,     4,     0,     1,     1,
       1,     1,     9,     0,     0,    11,     0,     0,     9,     5,
       5,     7,     7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     7,     0,    87,     8,
       0,    15,    13,    14,    84,     3,    12,     5,     0,    19,
       0,     0,     9,     0,     0,     0,     0,   103,     0,   106,
       0,     0,     0,     0,    23,     0,    19,    21,    20,    22,
      19,    19,    47,    46,    45,    99,   100,   101,    98,     0,
      11,     7,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     4,    16,    17,    18,    12,     6,     0,
      82,    83,    76,    77,    78,    72,     0,    44,    58,    65,
      74,    75,     0,    50,    19,     0,     0,     0,     0,     0,
       0,    33,    24,     0,     0,    25,    10,    91,    81,     0,
       0,     0,    42,    64,    71,     0,    57,    51,    52,    54,
      55,    53,    56,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,    92,     0,    90,    80,    79,
       0,    41,    43,    60,    62,    59,    67,    69,    66,    36,
      49,     0,     0,   107,     0,   109,     0,   110,     0,    35,
       0,    32,     0,     0,    73,     0,     0,     0,     0,    19,
       0,     0,     0,     0,     0,    34,    28,     0,     0,    29,
      93,     7,    61,    63,    68,    70,     0,     0,    19,    19,
     111,   112,    32,    30,    97,    19,    40,     0,     0,     0,
      31,     0,     0,    94,    89,    38,    37,   104,   102,   108,
       0,    95,     0,     0,     0,     0,    97,     0,    87,    19,
     105,    96,    88,    86,     0,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    19,     8,    23,    10,    16,    22,    14,
      35,    36,    37,    62,    92,    93,    94,   150,   169,    95,
     122,   148,    38,   159,   196,   204,    39,    76,   102,    40,
     151,   113,   114,    83,   103,   135,   155,   156,    78,   104,
     138,   157,   158,    79,    99,    80,    98,   129,    81,    15,
      18,    69,   203,   126,   127,   152,   184,   193,    41,    42,
      43,    55,   205,    44,    57,   162,    45,    46,    47,    48
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -100
static const yytype_int8 yypact[] =
{
      12,    -8,    33,  -100,  -100,    10,    46,    35,    42,  -100,
      42,  -100,  -100,  -100,  -100,  -100,   -14,  -100,    55,     4,
      39,    35,  -100,    21,    40,    31,    36,  -100,    37,  -100,
      38,    41,    43,    44,  -100,    27,     4,  -100,  -100,  -100,
       4,     4,  -100,  -100,  -100,  -100,  -100,  -100,  -100,    28,
    -100,    46,  -100,    14,    14,    45,    14,    48,    52,    53,
      47,    58,    56,  -100,  -100,  -100,  -100,   -14,  -100,    49,
    -100,  -100,  -100,  -100,  -100,  -100,    51,    50,  -100,  -100,
    -100,  -100,    54,   -21,     4,    57,    14,    34,    59,    60,
      61,  -100,  -100,    63,    65,  -100,  -100,    42,    66,    14,
      64,    14,  -100,    30,    17,    69,  -100,  -100,  -100,  -100,
    -100,  -100,  -100,  -100,    14,    72,    14,    62,    67,    70,
      71,    73,    14,  -100,    14,  -100,    76,  -100,  -100,  -100,
      77,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,    81,    79,  -100,    80,  -100,    82,  -100,    78,  -100,
      84,   -13,    68,    88,  -100,    14,    14,    14,    14,     4,
      86,    89,    90,    87,    91,  -100,  -100,    93,    14,  -100,
    -100,    46,  -100,  -100,  -100,  -100,    92,    14,     4,     4,
    -100,  -100,   -13,  -100,   -12,     4,    95,    98,    97,    99,
    -100,   107,    42,  -100,    75,  -100,  -100,  -100,  -100,  -100,
      96,  -100,    19,   100,    94,   103,   -12,   104,    42,     4,
    -100,  -100,  -100,  -100,   101,  -100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -100,  -100,  -100,  -100,   -48,  -100,   120,  -100,    22,   -10,
     -35,  -100,  -100,  -100,  -100,    -6,  -100,   -65,   -64,  -100,
    -100,  -100,  -100,  -100,  -100,  -100,  -100,    74,  -100,  -100,
     -52,  -100,  -100,   -46,  -100,  -100,  -100,  -100,   -99,  -100,
    -100,  -100,  -100,  -100,  -100,   -60,  -100,  -100,  -100,   -61,
    -100,  -100,  -100,  -100,   -44,  -100,  -100,   -57,  -100,  -100,
    -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -28
static const yytype_int16 yytable[] =
{
      17,    64,    82,    68,    85,    65,    66,    77,    25,   106,
     107,   108,   109,   110,   111,     1,    26,     3,    27,    28,
      29,    30,    31,    32,    33,   112,    20,   167,   191,    34,
      21,   168,   192,     4,   117,    70,    71,    72,    73,    74,
      70,    71,    72,    73,    74,   136,   137,   130,     6,   115,
      75,    11,    12,    13,     7,    77,   133,   134,   174,   175,
       9,    24,    49,    51,   142,    52,    63,    53,   140,    67,
     149,    89,    54,    56,    58,    87,    88,    59,   118,    60,
      61,    90,   202,    84,    86,    97,    91,   125,   100,    96,
     144,   105,   128,   170,   146,   101,   119,   160,   121,   143,
     116,   124,   -27,   183,   120,   123,   131,   139,   195,   172,
     173,   141,   145,   153,   154,   147,   161,   163,   190,   164,
     165,   166,   177,   185,   176,   187,   171,   178,   179,   180,
     200,   186,   209,   181,   182,   197,   198,   206,   199,   208,
     215,    50,   207,   188,   189,   210,   212,   213,   201,   211,
     194,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   214,   132,     0,     0,     0,     0,
       0,     0,   125
};

static const yytype_int16 yycheck[] =
{
      10,    36,    54,    51,    56,    40,    41,    53,     4,    30,
      31,    32,    33,    34,    35,     3,    12,    25,    14,    15,
      16,    17,    18,    19,    20,    46,    40,    40,    40,    25,
      44,    44,    44,     0,    86,    21,    22,    23,    24,    25,
      21,    22,    23,    24,    25,    28,    29,    99,    38,    84,
      36,     9,    10,    11,     8,   101,    26,    27,   157,   158,
      25,     6,    23,    42,   116,    25,    39,    36,   114,    41,
     122,    24,    36,    36,    36,    23,    23,    36,    44,    36,
      36,    23,     7,    38,    36,    36,    30,    97,    37,    67,
      23,    37,    98,    25,    23,    45,    37,    16,    37,    37,
      43,    36,    36,   168,    44,    42,    42,    38,    13,   155,
     156,    39,    42,    37,    37,    42,    37,    37,   182,    37,
      42,    37,    36,   171,   159,   177,    38,    38,    38,    42,
      23,    39,    38,    42,    41,    37,    39,    41,    39,    39,
      39,    21,   202,   178,   179,    42,    42,   208,   192,   206,
     185,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   209,   101,    -1,    -1,    -1,    -1,
      -1,    -1,   192
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    48,    25,     0,    49,    38,     8,    51,    25,
      53,     9,    10,    11,    56,    96,    54,    56,    97,    50,
      40,    44,    55,    52,     6,     4,    12,    14,    15,    16,
      17,    18,    19,    20,    25,    57,    58,    59,    69,    73,
      76,   105,   106,   107,   110,   113,   114,   115,   116,    23,
      53,    42,    25,    36,    36,   108,    36,   111,    36,    36,
      36,    36,    60,    39,    57,    57,    57,    41,    51,    98,
      21,    22,    23,    24,    25,    36,    74,    80,    85,    90,
      92,    95,    77,    80,    38,    77,    36,    23,    23,    24,
      23,    30,    61,    62,    63,    66,    55,    36,    93,    91,
      37,    45,    75,    81,    86,    37,    30,    31,    32,    33,
      34,    35,    46,    78,    79,    57,    43,    77,    44,    37,
      44,    37,    67,    42,    36,    56,   100,   101,    62,    94,
      77,    42,    74,    26,    27,    82,    28,    29,    87,    38,
      80,    39,    77,    37,    23,    42,    23,    42,    68,    77,
      64,    77,   102,    37,    37,    83,    84,    88,    89,    70,
      16,    37,   112,    37,    37,    42,    37,    40,    44,    65,
      25,    38,    80,    80,    85,    85,    57,    36,    38,    38,
      42,    42,    41,    64,   103,    51,    39,    77,    57,    57,
      65,    40,    44,   104,    57,    13,    71,    37,    39,    39,
      23,   101,     7,    99,    72,   109,    41,    92,    39,    38,
      42,   104,    42,    96,    57,    39
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
#line 138 "sintax.y"
    { scope_actual = "global"; actualizaScope("global"); ;}
    break;

  case 3:
#line 139 "sintax.y"
    { scope_actual = "global"; actualizaScope("global"); ;}
    break;

  case 5:
#line 142 "sintax.y"
    { tipo_actual = yytext; actualizaTipoVariables(); ;}
    break;

  case 8:
#line 145 "sintax.y"
    { var_actual.push(yytext); ;}
    break;

  case 9:
#line 145 "sintax.y"
    { creaVariable(); ;}
    break;

  case 23:
#line 162 "sintax.y"
    { meterPilaO(); ;}
    break;

  case 27:
#line 165 "sintax.y"
    { std::cout << "Wrar!\n\n"; ;}
    break;

  case 33:
#line 173 "sintax.y"
    { meterPilaOper(4); ;}
    break;

  case 36:
#line 178 "sintax.y"
    { cuadruploEstatuto(0); ;}
    break;

  case 37:
#line 179 "sintax.y"
    { cuadruploEstatuto(2); ;}
    break;

  case 38:
#line 180 "sintax.y"
    { cuadruploEstatuto(1); ;}
    break;

  case 48:
#line 192 "sintax.y"
    { checaOperador(4); ;}
    break;

  case 51:
#line 195 "sintax.y"
    { meterPilaOper(5); ;}
    break;

  case 52:
#line 196 "sintax.y"
    { meterPilaOper(6); ;}
    break;

  case 53:
#line 197 "sintax.y"
    { meterPilaOper(9); ;}
    break;

  case 54:
#line 198 "sintax.y"
    { meterPilaOper(7); ;}
    break;

  case 55:
#line 199 "sintax.y"
    { meterPilaOper(8); ;}
    break;

  case 56:
#line 200 "sintax.y"
    { meterPilaOper(10); ;}
    break;

  case 57:
#line 201 "sintax.y"
    { meterPilaOper(4); ;}
    break;

  case 58:
#line 202 "sintax.y"
    { checaOperador(0); ;}
    break;

  case 60:
#line 203 "sintax.y"
    { meterPilaOper(0); ;}
    break;

  case 62:
#line 204 "sintax.y"
    { meterPilaOper(1); ;}
    break;

  case 65:
#line 206 "sintax.y"
    { checaOperador(2); ;}
    break;

  case 67:
#line 207 "sintax.y"
    { meterPilaOper(2); ;}
    break;

  case 69:
#line 208 "sintax.y"
    { meterPilaOper(3); ;}
    break;

  case 72:
#line 210 "sintax.y"
    { meterPilaOper(11); ;}
    break;

  case 73:
#line 210 "sintax.y"
    { pOper.pop(); ;}
    break;

  case 76:
#line 213 "sintax.y"
    { creaConstanteNum(); ;}
    break;

  case 77:
#line 214 "sintax.y"
    { creaConstanteStr(yytext); ;}
    break;

  case 78:
#line 215 "sintax.y"
    { meterPilaO(); ;}
    break;

  case 82:
#line 219 "sintax.y"
    { creaConstanteBool(1); ;}
    break;

  case 83:
#line 220 "sintax.y"
    { creaConstanteBool(0); ;}
    break;

  case 84:
#line 222 "sintax.y"
    { tipo_actual = yytext; ;}
    break;

  case 85:
#line 223 "sintax.y"
    { scope_actual = yytext; actualizaScope("funcion");
		agregaFuncion(); ;}
    break;

  case 92:
#line 230 "sintax.y"
    { tipo_actual = yytext; ;}
    break;

  case 93:
#line 231 "sintax.y"
    { var_actual.push(yytext); actualizaTipoVariables(); ;}
    break;

  case 94:
#line 232 "sintax.y"
    { creaVariable(); ;}
    break;

  case 103:
#line 245 "sintax.y"
    { cuadruploEstatuto(3); ;}
    break;

  case 104:
#line 246 "sintax.y"
    { cuadruploEstatuto(5); ;}
    break;

  case 106:
#line 248 "sintax.y"
    { cuadruploEstatuto(3); ;}
    break;

  case 107:
#line 249 "sintax.y"
    { cuadruploEstatuto(0); ;}
    break;

  case 108:
#line 249 "sintax.y"
    { cuadruploEstatuto(4); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1904 "quack.tab.c"
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


#line 259 "sintax.y"





int main(int argc, char *argv[]){

	creaCubo();

	if (argc > 1)	{

		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL)	{
			printf("Error reading from %s\n", argv[1]);
			return -1;
		}

		yyin = fp;
	} else {}

	int a = yyparse();
	//imprimePila(1);
	imprimeVector(vec_cuadruplos);
	if (!a) printf("Eres un campeon\n");

/*	Node *tmp = new Node();

MapType::const_iterator end = map_vars.end();

for(MapType::const_iterator it = map_vars.begin() ;
		it != end; ++it) {
			std::cout << "llave: " << it->first << std::endl;
			tmp = it->second;
			std::cout << "nombre: " << tmp->nombre << std::endl;
			std::cout << "tipo: " << tmp->tipo << std::endl;
			std::cout << "scope: " << tmp->scope << std::endl;
	}*/

}

MapType creaTablaFuncion(std::string str){
	std::cout << "CreaTablaFuncion" << std::endl;
	MapType vars;

	return vars;
}

void agregaFuncion (){
	std::cout << "AgregaFuncion" << std::endl;
	Funcion *func =  new Funcion();
	func-> nombre = yytext;
	func-> tipo = convierteTipo(tipo_actual);
	func-> variables = map_vars;
	func-> param_cant = 0;
	func-> vars_cant = 0;
	func-> cuad_ini = 0;
	
	map_func[func->nombre] = func;
	//std::cout << "FuncGuar: " << func->nombre << std::endl;

}

void cuadruploEstatuto(int tipo) {
	std::cout << "CuadruploEstatuto" << std::endl;
	std::string nombre;
	switch(tipo) {
		/*
		* Del case 0 al 2 son para la implementacion de los if y los else,
		* del case 3 al 4 son para la implementacion del while,
		* del case 4 al 5 son para el do while
		*/
		case 0: {
			int a;
			Node *resultado;
			resultado = pilaO.top();
			a = resultado->tipo;
			if (a == -1 || a == 3  ) {
				std::cout << "Error de tipo: " << resultado->nombre 
				<< std::endl;
			} else {
				Cuadruplo::Cuadruplo cuad1(15, resultado->nombre, "", "__");
				vec_cuadruplos.push_back(cuad1);
				cuad_actual++;
				pSaltos.push(cuad_actual - 1);
			}
			break; 
		}
		
		case 1: {
			std::stringstream sstm1;
			Cuadruplo::Cuadruplo cuad3(13, "", "", "___");
			vec_cuadruplos.push_back(cuad3);
			cuad_actual++;
			int falso = pSaltos.top();
			pSaltos.pop();
			cuad3 = vec_cuadruplos[falso-1];
			sstm1 << "" << cuad_actual;
			nombre = sstm1.str();
			cuad3.setAvail_s(nombre);
			vec_cuadruplos[falso-1] = cuad3;
			pSaltos.push(cuad_actual-1);
			break;
		}
		
		case 2: {
			std::stringstream sstm2;
			int salto = pSaltos.top();
			pSaltos.pop();
			Cuadruplo::Cuadruplo cuad2;
			cuad2 = vec_cuadruplos[salto-1];
			sstm2 << "" << cuad_actual;
			nombre = sstm2.str();
			cuad2.setAvail_s(nombre);
			vec_cuadruplos[salto-1] = cuad2;
			break;
		}

		case 3: {
			pSaltos.push(cuad_actual);
			break;
		}
		
		case 4: {
			std::stringstream sstm3;
			std::stringstream sstm4;
			int falso, retorno;
			falso = pSaltos.top();
			pSaltos.pop();
			retorno = pSaltos.top();
			pSaltos.pop();
			sstm3 << "" << retorno;
			nombre = sstm3.str();
			Cuadruplo::Cuadruplo cuad4(13, "", "", nombre);
			vec_cuadruplos.push_back(cuad4);
			cuad_actual++;
			cuad4 = vec_cuadruplos[falso-1];
			sstm4 << "" << cuad_actual;
			nombre = sstm4.str();
			cuad4.setAvail_s(nombre);
			vec_cuadruplos[falso-1] = cuad4;
			break;
		}
		
		case 5: {
			int a, retorno;
			Node *resultado;
			std::stringstream sstm5;
			resultado = pilaO.top();
			a = resultado->tipo;
			if (a == 3 || a == -1 ) {
				std::cout << "Error de tipo: " << resultado->nombre
				<< std::endl;
			} else {
				retorno = pSaltos.top();
				pSaltos.pop();
				sstm5 << "" << retorno;
				nombre = sstm5.str();
				Cuadruplo::Cuadruplo cuad5(15, resultado->nombre, "",
					nombre);
				vec_cuadruplos.push_back(cuad5);
				cuad_actual++;
			}
			break;
		}
	} 
}


/**
*
* La función sirve para generar un cuadruplo de acuerdo a la operacion que 
* se vaya a realizar.
*
**/

void checaOperador(int a) {
	std::cout << "checaOperador" << std::endl;
	Node* tmp1 = new Node();
	Node* tmp2 = new Node();
	int aux = -1;
	//imprimeVector(vec_cuadruplos);


	if (!pilaO.empty() && !pOper.empty()) {
		int operador = pOper.top();

		if (operador == 0 && a == 0) aux = a;
		else if (operador == 1 && a == 0) aux = a;
		else if (operador == 2 && a == 2) aux = a;
		else if (operador == 3 && a == 2) aux = a;
		else if (operador == 4 && a == 4) aux = a;
		else if (operador >= 5 && a == 4) aux = a;

		if(aux == a){
			imprimePila(pilaO);
			
			if (operador == 11 || operador == 12){
			} else if (operador == 4) {
				tmp2 = pilaO.top();
				pilaO.pop();
				tmp1 = pilaO.top();
				pilaO.pop();
				std::cout << "pops superados" << std::endl;	
				if(cubo_sem[tmp1->tipo - 1][tmp2->tipo - 1][operador] > 0) {
					std::stringstream sstm;
					Cuadruplo::Cuadruplo cuad(operador, tmp2->nombre, 
						" ", tmp1->nombre);
					pOper.pop();
					vec_cuadruplos.push_back(cuad);
					cuad.print();
					cuad_actual++;
				} else {
					std::cout << "Error2: " << tmp1->tipo - 1 
						<< tmp2->tipo - 1
					<< operador	<< std::endl;
					imprimeVector(vec_cuadruplos);
				}
			}  else if(operador >= 5 ) {
				tmp2 = pilaO.top();
				pilaO.pop();
				tmp1 = pilaO.top();
				pilaO.pop();
				if(cubo_sem[tmp1->tipo - 1][tmp2->tipo - 1][operador] > 0) {
					std::stringstream sstm;
					sstm << "t" << tmp_actual;
					avail = sstm.str();
					Cuadruplo::Cuadruplo cuad(operador, tmp1->nombre, 
						tmp2->nombre, avail);
					var_actual.push(avail);
					tipo_actual = "num";
					creaVariable();
					actualizaTipoVariables();
					yytext = strdup(avail.c_str());
					meterPilaO();
					tmp_actual++;
					cuad_actual++;
					pOper.pop();
					vec_cuadruplos.push_back(cuad);
					//imprimePila(1);
				} else {
					std::cout << "Error3: " << tmp1->tipo - 1 
						<< tmp2->tipo - 1
					<< operador	<< std::endl;
					imprimeVector(vec_cuadruplos);
				} 
			} else if (operador != 4) {
				tmp2 = pilaO.top();
				pilaO.pop();
				tmp1 = pilaO.top();
				pilaO.pop();
				if(cubo_sem[tmp1->tipo - 1][tmp2->tipo - 1][operador] > 0) {
					std::stringstream sstm;
					sstm << "t" << tmp_actual;
					avail = sstm.str();
					Cuadruplo::Cuadruplo cuad(operador, tmp1->nombre, 
						tmp2->nombre, avail);
					var_actual.push(avail);
					tipo_actual = "num";
					creaVariable();
					actualizaTipoVariables();
					yytext = strdup(avail.c_str());
					meterPilaO();
					tmp_actual++;
					pOper.pop();
					vec_cuadruplos.push_back(cuad);
					cuad_actual++;
					//imprimePila(1);
				} else {
					std::cout << "Error1: " << tmp1->tipo - 1 
						<< tmp2->tipo - 1
					<< operador	<< std::endl;
					imprimeVector(vec_cuadruplos);
				}
			}
		}
	}
}

void meterPilaOper(int esp) {
	std::cout << "meterPilaOper" << std::endl;
	pOper.push(esp);
	std::cout << "Guardé: " << esp << std::endl;
}

void meterPilaO() {
	std::cout << "meterPilaO" << std::endl;
	
	const char *aux;
	Node *var = new Node();
	std::string llave;
	if(strcmp(yytext,"=") == 0) { std::cout << yytext << contlin << std::endl; }
	else  {
		llave = std::string(yytext) + "&" + scope_actual;
		aux = llave.c_str();
		MapType::const_iterator it = map_vars.find(aux);
	
		if(it == map_vars.end()) { 
			llave = std::string(yytext) + "&global";
			aux = llave.c_str();
			it = map_vars.find(llave);
			if(it != map_vars.end()) pilaO.push(it->second);
			else {
				MapFunc::iterator it = map_func.find(std::string(yytext));
				if(it ==  map_func.end()) {
					std::cout << "Variable no encontrada: " << yytext 
						<< std::endl;
					std::cout << contlin << std::endl;
					exit(1);
				}
			}
		} else {
				pilaO.push(it->second);
		}
	}
}

void creaConstanteNum(){
	std::cout << "creaConstateNum" << std::endl;	
	Node *var = new Node();
	std::string aux = std::string(yytext);
	var->nombre = "cN" + aux;
	var->tipo = 1;
	var->scope = "global";
	var->valor_num = ::atof(yytext);
	var->id = id_actual++;
	pilaO.push(var);

}

void creaConstanteBool(int a) {
	std::cout << "CreaConstanteBool" << std::endl;
	Node *var = new Node();
	std::string aux;
	if(!a) aux = "cB0"; 
	else aux = "cB1";
	var->nombre = aux;
	var->tipo = 2;
	var->scope = scope_actual ;
	var->valor_num = a;
	var->id = id_actual++;
	pilaO.push(var);

}

void creaConstanteStr(const char *){

}


void actualizaTipoVariables () {
	std::cout << "ActualizaTipoVariables" << std::endl;	
	int tipo = -1;
	std::string aux;
	const char  *llave; 
	Node *var = new Node();

	tipo = convierteTipo(tipo_actual);	
	
	if (tipo<0) std::cout << std::endl << " E R R O R " << std::endl;

	while (!aux_vars.empty()) {
		var = aux_vars.top();
		aux_vars.pop();
		aux =  std::string(var->nombre) + "&" + scope_actual;
		llave = aux.c_str();
		var->tipo = tipo;
		map_vars[llave] = var;
	}
}

int convierteTipo(std::string str) {
	std::cout << "convierteTipo" << std::endl;	
	if(str == "num") return (1);
	else if(str == "bool") return (2);
	else if(str == "texto") return (3);
	else return (-1);
}

void creaVariable() {
	std::cout << "CreaVariable" << std::endl;	
	Node *var = new Node();
	var->nombre = var_actual.top();
	var->tipo = -1;
	var->scope = scope_actual;
	var->id = id_actual++;
	var_actual.pop();
	aux_vars.push(var);
	
//	std::cout << "nombre: " << var->nombre << "\t scope: " << scope_actual
//	<< std::endl;

}

void actualizaScope(std::string str){
	std::cout << "ActualizaScope" << std::endl;
	scopes.push_back(str);
}

void imprimePila(std::stack<Node*> pila) {
	std::cout << "imprimePila" << std::endl;	
	std::stack<Node*> tmp;
	Node* var = new Node();
	tmp = pila;

	while(!tmp.empty()) {
		var = tmp.top();
		std::cout << "Nombre: " << var->nombre << std::endl;
		tmp.pop();
	}

	std::cout << "----------------------------------------" << std::endl;
   }

void imprimePila(int a) {
	std::cout << "ImprimePila2" << std::endl;
	std::stack<int> tmp;
	int var;
	tmp = pOper;

	while(!tmp.empty()) {
	std::cout << "----------------------------------------" << std::endl;

		var = tmp.top();
		std::cout << "Operador: " << var << std::endl;
		tmp.pop();
	}

	std::cout << "----------------------------------------" << std::endl;

}

void imprimeVector(std::vector<Cuadruplo> vec) {
	std::cout << "imprimeVector" << std::endl;

	Cuadruplo::Cuadruplo cuad;

	for (int i = 0; i < vec.size(); i++) {
		cuad = vec[i];
		std::cout << i+1 << ": ";
		cuad.print();
		
	}
	std::cout << "Terminé lala" << std::endl;	
	
}

void creaCubo(){
	cubo_sem[0][0][0] = 1;
	cubo_sem[0][0][1] = 1;
	cubo_sem[0][0][2] = 1;
	cubo_sem[0][0][3] = 1;
	cubo_sem[0][0][4] = 1;
	cubo_sem[0][0][5] = 2;
	cubo_sem[0][0][6] = 2;
	cubo_sem[0][0][7] = 2;
	cubo_sem[0][0][8] = 2;
	cubo_sem[0][0][9] = 2;
	cubo_sem[0][0][10] = 2; 
	cubo_sem[0][1][4] = 2;
	cubo_sem[0][1][9] = 2;
	cubo_sem[0][1][10] = 2;
	cubo_sem[1][0][4] = 2;
	cubo_sem[1][0][9] = 2;
	cubo_sem[1][0][10] = 2;
	cubo_sem[1][1][4] = 2;
	cubo_sem[1][1][9] = 2;
	cubo_sem[1][1][10] = 2;
	cubo_sem[2][2][4] = 3;
	cubo_sem[2][2][5] = 3;
	cubo_sem[2][2][6] = 3;
	cubo_sem[2][2][7] = 3;
	cubo_sem[2][2][8] = 3;
	cubo_sem[2][2][9] = 3;
	cubo_sem[2][2][10] = 3;

	id_actual = 1;
	cuad_actual = 1;
	tmp_actual = 1;
	param_count = 0;
/*
	std::cout << "         + - * / = < > < > ! ==";

for(int i =0; i < 3; i++) {
		for(int j =0; j < 3; j++) {
			std::cout << std::endl;
			std::cout << "[" << i << "]" << "[" << j << "]:  ";
			for(int k =0; k < 11; k++) {
				 std::cout << cubo_sem[i][j][k] << " "; 
			}
		}
	}

std::cout << std::endl;	
   std::cout << std::endl; 
*/

}

int yyerror(char* s) {
  extern char *yytext;	// defined and maintained in lex.c  
  printf("ERROR: %s at symbol  %s  on line %d\n",s,yytext,contlin);
  exit(1);
  return 1;
}

