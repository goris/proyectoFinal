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
     LIBRE = 267,
     SI = 268,
     SINO = 269,
     HAZ = 270,
     POR = 271,
     MIENTRAS = 272,
     LINEA = 273,
     RECTANGULO = 274,
     TRIANGULO = 275,
     ELIPSE = 276,
     VERDADERO = 277,
     FALSO = 278,
     CTE_NUM = 279,
     CTE_TEXTO = 280,
     ID = 281,
     SUM = 282,
     MIN = 283,
     PRO = 284,
     DIV = 285,
     EQU = 286,
     LT = 287,
     GT = 288,
     LTE = 289,
     GTE = 290,
     DIF = 291,
     LPA = 292,
     RPA = 293,
     LBR = 294,
     RBR = 295,
     LSQ = 296,
     RSQ = 297,
     SEM = 298,
     DOU = 299,
     COM = 300,
     DOT = 301,
     DEQ = 302
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
#define LIBRE 267
#define SI 268
#define SINO 269
#define HAZ 270
#define POR 271
#define MIENTRAS 272
#define LINEA 273
#define RECTANGULO 274
#define TRIANGULO 275
#define ELIPSE 276
#define VERDADERO 277
#define FALSO 278
#define CTE_NUM 279
#define CTE_TEXTO 280
#define ID 281
#define SUM 282
#define MIN 283
#define PRO 284
#define DIV 285
#define EQU 286
#define LT 287
#define GT 288
#define LTE 289
#define GTE 290
#define DIF 291
#define LPA 292
#define RPA 293
#define LBR 294
#define RBR 295
#define LSQ 296
#define RSQ 297
#define SEM 298
#define DOU 299
#define COM 300
#define DOT 301
#define DEQ 302




/* Copy the first part of user declarations.  */
#line 1 "sintax.y"

/*
*
* D E C L A R A C I O N E S
*
*/
	#include <map>
	#include <stack>
	#include <string>
	#include <vector>
	#include <cstdlib>
	#include <fstream>
	#include <sstream>
	#include <iostream>

	#include "utilities/Cuadruplo.h"

	struct EspacioMemoria {
		int numl;
		int nump;
		int booll;
		int boolp;
		int textol;
		int textop;
		int total;
	};


	struct Node {
		int tipo;
		double valor_num;
		int loc_mem;
		int id;
		std::string nombre;
		std::string valor_str;
		std::string scope;
	};

	typedef std::map <std::string, Node*> MapType;

	struct Funcion {
		int tipo;
		int cuad_ini;
		EspacioMemoria *memoria;
		std::string nombre;
		std::stack<std::string> pTipoParams;
		MapType variables;
	};
	
	typedef std::map <std::string, Funcion*> MapFunc;

	
	extern int contlin;
	extern int yyerror (char *s);
	extern int yylex();
	extern  FILE *yyin;
	extern int yyparse();
	extern char * yytext;

	/*
	* 
	*	C U B O    S E M A N T I C O
	*
	* 0 num 1 bool 2 text  [indices]
	* 1 num 2 bool 3 text 0 ERRROR
	* 0+ 1- 2* 3/ 4= 5< 6> 7<= 8>= 9!= 10== 11( 12) 13goto 14gotoV
	* 15gotoF 16Era 17GoSub 18Ret 19Param
	* [tipo1] [tipo2] [operador] 
	*
	*/
	int cubo_sem[3][3][11] = { 0 };
	int mem_num_global;
	int mem_num_local;
	int mem_num_constante;
	int mem_bool_global;
	int mem_bool_local;
	int mem_bool_constante;
	int cuad_actual;
	int id_actual;
	int param_count;
	int tmp_actual;
	std::string avail;
	std::stack <std::string> var_actual;
	std::string tipo_actual;
	std::string tipo_func;
	std::string scope_actual;
	std::string func_actual;
	std::vector<std::string> scopes;	
	std::stack<Node*> aux_vars;
	std::stack<Node*> pilaO;
	std::stack<int> pOper;
	std::stack<int> pSaltos;
	std::stack<std::string> pTipoParams;
	std::vector<Cuadruplo> vec_cuadruplos;
	MapType map_vars;
	MapFunc map_func;


	int convierteTipo(std::string);
	int memoriaAUsar(int, std::string); 
	void actualizaScope(std::string);
	void actualizaTipoVariables();
	void agregaFuncion();
	void checaOperador(int);
	void creaConstanteNum();
	void creaConstanteBool(int);
	void creaConstanteStr(const char *);
	void creaCubo();
	void creaVariable();
	void cuadruploEstatuto(int);
	void cuadruploMain();
	void finParametros();
	void imprimeCubo();
	void imprimePila(std::stack<Node*>);
	void imprimePila(int a);
	void imprimeVector(std::vector<Cuadruplo>);
	void manipulaStack();
	void meterPilaO();
	void meterPilaOper(int);
	void modificaMemoria(std::string);
	EspacioMemoria* inicializaMemoria(EspacioMemoria*);
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
#line 127 "sintax.y"
{
	int int_val;	
	float float_val;
	char* text;
}
/* Line 193 of yacc.c.  */
#line 322 "quack.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 335 "quack.tab.c"

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
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNRULES -- Number of states.  */
#define YYNSTATES  222

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

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
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    17,    18,    25,    26,
      27,    31,    36,    39,    40,    42,    44,    46,    48,    51,
      54,    57,    58,    60,    62,    64,    65,    69,    71,    74,
      75,    80,    81,    85,    88,    93,    94,    95,    96,    97,
      98,   115,   116,   120,   121,   123,   124,   125,   126,   132,
     135,   140,   141,   142,   147,   149,   150,   160,   161,   167,
     168,   174,   177,   180,   181,   183,   185,   187,   190,   193,
     194,   196,   198,   200,   202,   204,   206,   208,   209,   213,
     214,   218,   219,   223,   224,   225,   229,   230,   234,   235,
     239,   240,   241,   246,   248,   250,   252,   254,   255,   259,
     261,   262,   264,   266,   268,   270,   272,   274,   284,   285,
     286,   298,   299,   300,   310,   316,   322,   330
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    -1,    -1,    -1,     3,    26,    50,    39,
      53,    69,    51,    52,    59,    40,    -1,    -1,     8,    55,
      58,    54,    43,    53,    -1,    -1,    -1,    26,    56,    57,
      -1,    41,    24,    42,    57,    -1,    45,    55,    -1,    -1,
      10,    -1,    11,    -1,     9,    -1,    12,    -1,    60,    59,
      -1,    90,    59,    -1,   110,    59,    -1,    -1,    83,    -1,
      61,    -1,    87,    -1,    -1,    26,    62,    63,    -1,    80,
      -1,    64,    43,    -1,    -1,    37,    65,    66,    38,    -1,
      -1,    91,    67,    68,    -1,    45,    66,    -1,    41,    24,
      42,    68,    -1,    -1,    -1,    -1,    -1,    -1,    58,    70,
       6,    26,    71,    37,    72,    75,    38,    39,    53,    59,
      74,    40,    73,    69,    -1,    -1,     7,    91,    43,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    58,    77,    26,    78,
      79,    -1,    45,    76,    -1,    41,    24,    42,    79,    -1,
      -1,    -1,    31,    81,    82,    43,    -1,    91,    -1,    -1,
      13,    37,    91,    38,    39,    84,    59,    40,    85,    -1,
      -1,    14,    86,    39,    59,    40,    -1,    -1,     4,    37,
      88,    38,    43,    -1,    94,    89,    -1,    46,    88,    -1,
      -1,   115,    -1,   112,    -1,   111,    -1,    94,    92,    -1,
      93,    94,    -1,    -1,    32,    -1,    33,    -1,    36,    -1,
      34,    -1,    35,    -1,    47,    -1,    31,    -1,    -1,    99,
      95,    96,    -1,    -1,    27,    97,    94,    -1,    -1,    28,
      98,    94,    -1,    -1,    -1,   104,   100,   101,    -1,    -1,
      29,   102,    99,    -1,    -1,    30,   103,    99,    -1,    -1,
      -1,    37,   105,    91,    38,    -1,   106,    -1,   109,    -1,
      24,    -1,    25,    -1,    -1,    26,   107,   108,    -1,    64,
      -1,    -1,    22,    -1,    23,    -1,   121,    -1,   118,    -1,
     119,    -1,   120,    -1,    16,    37,    91,    44,    91,    38,
      39,    59,    40,    -1,    -1,    -1,    15,   113,    39,    59,
      40,    17,    37,    91,    38,   114,    43,    -1,    -1,    -1,
      17,   116,    37,    91,    38,   117,    39,    59,    40,    -1,
      19,    37,    24,    38,    43,    -1,    21,    37,    24,    38,
      43,    -1,    18,    37,    24,    45,    24,    38,    43,    -1,
      20,    37,    25,    45,    24,    38,    43,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   168,   168,   170,   171,   168,   173,   173,   175,   176,
     176,   177,   178,   179,   181,   182,   183,   184,   186,   187,
     188,   189,   191,   192,   193,   194,   194,   195,   196,   198,
     197,   201,   201,   202,   203,   204,   206,   207,   208,   209,
     206,   210,   211,   212,   214,   215,   216,   219,   216,   222,
     223,   224,   226,   226,   227,   230,   229,   232,   232,   233,
     235,   236,   237,   238,   240,   241,   242,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   254,   255,
     255,   256,   256,   257,   258,   258,   259,   259,   260,   260,
     261,   262,   262,   263,   264,   265,   266,   267,   267,   268,
     269,   271,   272,   275,   276,   277,   278,   281,   283,   284,
     283,   286,   287,   286,   289,   291,   293,   295
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAMA", "IMPRIME", "DIBUJA",
  "FUNCION", "REGRESA", "VAR", "BOOL", "NUM", "TEXTO", "LIBRE", "SI",
  "SINO", "HAZ", "POR", "MIENTRAS", "LINEA", "RECTANGULO", "TRIANGULO",
  "ELIPSE", "VERDADERO", "FALSO", "CTE_NUM", "CTE_TEXTO", "ID", "SUM",
  "MIN", "PRO", "DIV", "EQU", "LT", "GT", "LTE", "GTE", "DIF", "LPA",
  "RPA", "LBR", "RBR", "LSQ", "RSQ", "SEM", "DOU", "COM", "DOT", "DEQ",
  "$accept", "program", "@1", "@2", "@3", "vars", "@4", "vars2", "@5",
  "vars3", "tipo", "bloque", "estatutos", "asig_llamada", "@6", "llamada_",
  "llamada", "@7", "varsss", "@8", "varsss2", "funciones", "@9", "@10",
  "@11", "@12", "funciones1", "varss", "varss2", "@13", "@14", "varss3",
  "asignacion", "@15", "asignacion1", "condicion", "@16", "condicion1",
  "@17", "escritura", "escritura1", "escritura2", "ciclos", "sexp",
  "expresion1", "operadores", "exp", "@18", "exp1", "@19", "@20",
  "termino", "@21", "termino1", "@22", "@23", "factor", "@24", "var_cte",
  "@25", "llamada_opt", "cte_bool", "dibuja", "por", "haz", "@26", "@27",
  "mientras", "@28", "@29", "rectangulo", "elipse", "linea", "triangulo", 0
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
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    50,    51,    52,    49,    54,    53,    53,    56,
      55,    57,    57,    57,    58,    58,    58,    58,    59,    59,
      59,    59,    60,    60,    60,    62,    61,    63,    63,    65,
      64,    67,    66,    68,    68,    68,    70,    71,    72,    73,
      69,    69,    74,    74,    75,    75,    77,    78,    76,    79,
      79,    79,    81,    80,    82,    84,    83,    86,    85,    85,
      87,    88,    89,    89,    90,    90,    90,    91,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    95,    94,    97,
      96,    98,    96,    96,   100,    99,   102,   101,   103,   101,
     101,   105,   104,   104,   106,   106,   106,   107,   106,   108,
     108,   109,   109,   110,   110,   110,   110,   111,   113,   114,
     112,   116,   117,   115,   118,   119,   120,   121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,    10,     0,     6,     0,     0,
       3,     4,     2,     0,     1,     1,     1,     1,     2,     2,
       2,     0,     1,     1,     1,     0,     3,     1,     2,     0,
       4,     0,     3,     2,     4,     0,     0,     0,     0,     0,
      16,     0,     3,     0,     1,     0,     0,     0,     5,     2,
       4,     0,     0,     4,     1,     0,     9,     0,     5,     0,
       5,     2,     2,     0,     1,     1,     1,     2,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     0,     3,     0,
       3,     0,     3,     0,     0,     3,     0,     3,     0,     3,
       0,     0,     4,     1,     1,     1,     1,     0,     3,     1,
       0,     1,     1,     1,     1,     1,     1,     9,     0,     0,
      11,     0,     0,     9,     5,     5,     7,     7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     8,     0,    41,     9,
       0,    16,    14,    15,    17,    36,     3,    13,     6,     0,
       4,     0,     0,    10,     0,     0,    21,     0,    12,     8,
      37,     0,     0,   108,     0,   111,     0,     0,     0,     0,
      25,     0,    21,    23,    22,    24,    21,    21,    66,    65,
      64,   104,   105,   106,   103,    13,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,    18,
      19,    20,    11,    38,   101,   102,    95,    96,    97,    91,
       0,    63,    77,    84,    93,    94,     0,    69,    21,     0,
       0,     0,     0,     0,     0,    52,    29,    26,     0,    27,
      45,   100,     0,     0,     0,    61,    83,    90,     0,    76,
      70,    71,    73,    74,    72,    75,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    46,     0,
      44,    99,    98,     0,    60,    62,    79,    81,    78,    86,
      88,    85,    55,    68,     0,     0,   112,     0,   114,     0,
     115,     0,    54,     0,    31,     0,     0,    92,     0,     0,
       0,     0,    21,     0,     0,     0,     0,     0,    53,    30,
      35,    47,     8,    80,    82,    87,    89,     0,     0,    21,
      21,   116,   117,     0,     0,    32,    51,    21,    59,     0,
       0,     0,     0,    33,     0,     0,    48,    43,    57,    56,
     109,   107,   113,    35,     0,    49,     0,     0,     0,     0,
      34,    51,     0,    39,    21,   110,    50,    42,    41,     0,
      40,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    20,    26,     8,    24,    10,    17,    23,
      15,    41,    42,    43,    67,    97,    98,   126,   153,   170,
     185,    16,    19,    57,   100,   218,   207,   129,   130,   155,
     186,   196,    99,   125,   151,    44,   162,   199,   208,    45,
      80,   105,    46,   154,   116,   117,    87,   106,   138,   158,
     159,    82,   107,   141,   160,   161,    83,   102,    84,   101,
     132,    85,    47,    48,    49,    60,   209,    50,    62,   165,
      51,    52,    53,    54
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -107
static const yytype_int8 yypact[] =
{
       9,    15,    39,  -107,  -107,     6,    46,    32,    13,  -107,
      13,  -107,  -107,  -107,  -107,  -107,  -107,    -1,  -107,    53,
    -107,    36,    32,  -107,    18,    37,     0,    22,  -107,    46,
    -107,    28,    29,  -107,    31,  -107,    33,    34,    35,    38,
    -107,    40,     0,  -107,  -107,  -107,     0,     0,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,    -1,  -107,    41,    11,    11,
      30,    11,    42,    50,    52,    56,    58,   -23,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
      45,    43,  -107,  -107,  -107,  -107,    47,    -4,     0,    44,
      11,    48,    49,    51,    54,  -107,  -107,  -107,    55,  -107,
      13,    57,    11,    59,    11,  -107,   -17,    23,    60,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,    11,    61,    11,
      62,    67,    63,    71,    64,    11,    11,  -107,  -107,    70,
    -107,  -107,  -107,    72,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,    69,    73,  -107,    74,  -107,    75,
    -107,    66,  -107,    76,  -107,    79,    77,  -107,    11,    11,
      11,    11,     0,    78,    80,    81,    82,    84,  -107,  -107,
       1,  -107,    46,  -107,  -107,  -107,  -107,    83,    11,     0,
       0,  -107,  -107,    93,    11,  -107,    10,     0,   104,    86,
      88,    89,    90,  -107,    98,    13,  -107,   123,  -107,  -107,
    -107,  -107,  -107,     1,    91,  -107,    11,    94,    92,    97,
    -107,    10,    99,  -107,     0,  -107,  -107,  -107,    13,    95,
    -107,  -107
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,  -107,  -107,  -107,  -107,   -27,  -107,   114,  -107,    96,
     -10,   -41,  -107,  -107,  -107,  -107,   -24,  -107,  -100,  -107,
    -106,   -81,  -107,  -107,  -107,  -107,  -107,  -107,   -54,  -107,
    -107,   -68,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
      65,  -107,  -107,   -52,  -107,  -107,   -55,  -107,  -107,  -107,
    -107,  -104,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      18,    69,    56,    81,    31,    70,    71,    86,    95,    89,
     136,   137,     1,    32,    96,    33,    34,    35,    36,    37,
      38,    39,    11,    12,    13,    14,    40,   109,   110,   111,
     112,   113,   114,    74,    75,    76,    77,    78,   120,     4,
      21,     3,   183,   115,    22,     6,   184,   118,    79,    81,
     133,   194,   139,   140,     7,   195,   175,   176,     9,    25,
      27,    29,   143,    30,    55,    58,    59,   145,    61,    88,
      63,    64,    65,   152,    91,    66,    92,   131,    73,    90,
      68,    93,    94,   103,   193,   108,   163,   122,   119,   104,
     128,   147,   124,   121,    96,   149,   123,   210,   127,   142,
     146,   144,   134,   173,   174,   171,   148,   150,   156,   168,
     157,   164,   166,   167,   169,   178,   172,   192,   198,   179,
     180,   177,   204,   188,   200,   181,   189,   182,   201,   202,
     206,   214,   203,   211,   213,   221,    28,   220,   190,   191,
     215,   205,   217,   216,     0,   187,   197,     0,     0,     0,
       0,    72,     0,     0,   212,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
       0,     0,     0,   219,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128
};

static const yytype_int16 yycheck[] =
{
      10,    42,    29,    58,     4,    46,    47,    59,    31,    61,
      27,    28,     3,    13,    37,    15,    16,    17,    18,    19,
      20,    21,     9,    10,    11,    12,    26,    31,    32,    33,
      34,    35,    36,    22,    23,    24,    25,    26,    90,     0,
      41,    26,    41,    47,    45,    39,    45,    88,    37,   104,
     102,    41,    29,    30,     8,    45,   160,   161,    26,     6,
      24,    43,   117,    26,    42,    37,    37,   119,    37,    39,
      37,    37,    37,   125,    24,    37,    24,   101,    37,    37,
      40,    25,    24,    38,   184,    38,    17,    38,    44,    46,
     100,    24,    38,    45,    37,    24,    45,   203,    43,    39,
      38,    40,    43,   158,   159,    26,    43,    43,    38,    43,
      38,    38,    38,    38,    38,    37,    39,    24,    14,    39,
      39,   162,    24,    40,    38,    43,   178,    43,    40,    40,
       7,    39,    42,    42,    40,    40,    22,   218,   179,   180,
      43,   195,    43,   211,    -1,   172,   187,    -1,    -1,    -1,
      -1,    55,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      -1,    -1,    -1,   214,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   195
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    49,    26,     0,    50,    39,     8,    53,    26,
      55,     9,    10,    11,    12,    58,    69,    56,    58,    70,
      51,    41,    45,    57,    54,     6,    52,    24,    55,    43,
      26,     4,    13,    15,    16,    17,    18,    19,    20,    21,
      26,    59,    60,    61,    83,    87,    90,   110,   111,   112,
     115,   118,   119,   120,   121,    42,    53,    71,    37,    37,
     113,    37,   116,    37,    37,    37,    37,    62,    40,    59,
      59,    59,    57,    37,    22,    23,    24,    25,    26,    37,
      88,    94,    99,   104,   106,   109,    91,    94,    39,    91,
      37,    24,    24,    25,    24,    31,    37,    63,    64,    80,
      72,   107,   105,    38,    46,    89,    95,   100,    38,    31,
      32,    33,    34,    35,    36,    47,    92,    93,    59,    44,
      91,    45,    38,    45,    38,    81,    65,    43,    58,    75,
      76,    64,   108,    91,    43,    88,    27,    28,    96,    29,
      30,   101,    39,    94,    40,    91,    38,    24,    43,    24,
      43,    82,    91,    66,    91,    77,    38,    38,    97,    98,
     102,   103,    84,    17,    38,   117,    38,    38,    43,    38,
      67,    26,    39,    94,    94,    99,    99,    59,    37,    39,
      39,    43,    43,    41,    45,    68,    78,    53,    40,    91,
      59,    59,    24,    66,    41,    45,    79,    59,    14,    85,
      38,    40,    40,    42,    24,    76,     7,    74,    86,   114,
      68,    42,    91,    40,    39,    43,    79,    43,    73,    59,
      69,    40
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
#line 168 "sintax.y"
    { scope_actual = "global"; actualizaScope("global"); 
	   	cuadruploEstatuto(10); ;}
    break;

  case 3:
#line 170 "sintax.y"
    { scope_actual = "global"; actualizaScope("global"); ;}
    break;

  case 4:
#line 171 "sintax.y"
    { cuadruploMain(); ;}
    break;

  case 6:
#line 173 "sintax.y"
    { tipo_actual = yytext; actualizaTipoVariables(); ;}
    break;

  case 9:
#line 176 "sintax.y"
    { var_actual.push(yytext); ;}
    break;

  case 10:
#line 176 "sintax.y"
    { creaVariable(); ;}
    break;

  case 25:
#line 194 "sintax.y"
    { meterPilaO();  ;}
    break;

  case 29:
#line 198 "sintax.y"
    { cuadruploEstatuto(7); param_count = 0; ;}
    break;

  case 30:
#line 199 "sintax.y"
    { /*finParametros();*/ cuadruploEstatuto(9); ;}
    break;

  case 31:
#line 201 "sintax.y"
    { param_count++; cuadruploEstatuto(8); ;}
    break;

  case 36:
#line 206 "sintax.y"
    { tipo_actual = yytext; tipo_func = yytext; ;}
    break;

  case 37:
#line 207 "sintax.y"
    { scope_actual = yytext; func_actual= yytext; actualizaScope("funcion");
		agregaFuncion(); ;}
    break;

  case 38:
#line 208 "sintax.y"
    { param_count = 0; ;}
    break;

  case 39:
#line 209 "sintax.y"
    { cuadruploEstatuto(6); ;}
    break;

  case 44:
#line 214 "sintax.y"
    {;}
    break;

  case 46:
#line 216 "sintax.y"
    { tipo_actual = yytext; pTipoParams.push(yytext); 
		Funcion *func = map_func[func_actual]; func->pTipoParams = pTipoParams;
		map_func[func_actual] = func; ;}
    break;

  case 47:
#line 219 "sintax.y"
    {actualizaTipoVariables(); var_actual.push(yytext);  
			modificaMemoria(scope_actual); param_count++; ;}
    break;

  case 48:
#line 221 "sintax.y"
    { creaVariable(); actualizaTipoVariables(); ;}
    break;

  case 52:
#line 226 "sintax.y"
    { meterPilaOper(4); ;}
    break;

  case 55:
#line 230 "sintax.y"
    { cuadruploEstatuto(0); ;}
    break;

  case 56:
#line 231 "sintax.y"
    { cuadruploEstatuto(2); ;}
    break;

  case 57:
#line 232 "sintax.y"
    { cuadruploEstatuto(1); ;}
    break;

  case 67:
#line 244 "sintax.y"
    { checaOperador(4); ;}
    break;

  case 70:
#line 247 "sintax.y"
    { meterPilaOper(5); ;}
    break;

  case 71:
#line 248 "sintax.y"
    { meterPilaOper(6); ;}
    break;

  case 72:
#line 249 "sintax.y"
    { meterPilaOper(9); ;}
    break;

  case 73:
#line 250 "sintax.y"
    { meterPilaOper(7); ;}
    break;

  case 74:
#line 251 "sintax.y"
    { meterPilaOper(8); ;}
    break;

  case 75:
#line 252 "sintax.y"
    { meterPilaOper(10); ;}
    break;

  case 76:
#line 253 "sintax.y"
    { meterPilaOper(4); ;}
    break;

  case 77:
#line 254 "sintax.y"
    { checaOperador(0); ;}
    break;

  case 79:
#line 255 "sintax.y"
    { meterPilaOper(0); ;}
    break;

  case 81:
#line 256 "sintax.y"
    { meterPilaOper(1); ;}
    break;

  case 84:
#line 258 "sintax.y"
    { checaOperador(2); ;}
    break;

  case 86:
#line 259 "sintax.y"
    { meterPilaOper(2); ;}
    break;

  case 88:
#line 260 "sintax.y"
    { meterPilaOper(3); ;}
    break;

  case 91:
#line 262 "sintax.y"
    { meterPilaOper(11); ;}
    break;

  case 92:
#line 262 "sintax.y"
    { pOper.pop(); ;}
    break;

  case 95:
#line 265 "sintax.y"
    { creaConstanteNum(); ;}
    break;

  case 96:
#line 266 "sintax.y"
    { creaConstanteStr(yytext); ;}
    break;

  case 97:
#line 267 "sintax.y"
    { meterPilaO(); ;}
    break;

  case 101:
#line 271 "sintax.y"
    { creaConstanteBool(1); ;}
    break;

  case 102:
#line 272 "sintax.y"
    { creaConstanteBool(0); ;}
    break;

  case 108:
#line 283 "sintax.y"
    { cuadruploEstatuto(3); ;}
    break;

  case 109:
#line 284 "sintax.y"
    { cuadruploEstatuto(5); ;}
    break;

  case 111:
#line 286 "sintax.y"
    { cuadruploEstatuto(3); ;}
    break;

  case 112:
#line 287 "sintax.y"
    { cuadruploEstatuto(0); ;}
    break;

  case 113:
#line 287 "sintax.y"
    { cuadruploEstatuto(4); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1975 "quack.tab.c"
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


#line 297 "sintax.y"



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

/**
* Devuelve la memoria que se tiene que usar de acuerdo al tipo de la  
* variable
**/
int memoriaAUsar (int tipo, std::string str) {
	//std::cout << "memoriaAUsar" << std::endl;
	int memset = 0;
	int scope = -1;
	if (str == "global") scope = 0;
	else if (str == "constante") scope = 1;
	else scope = 2;
	switch (tipo) {
		case 1:
			if(scope == 0) {
				memset = ++mem_num_global;
			} else if (scope == 1) {
				memset = ++mem_num_constante;	
			} else if (scope == 2) {
				memset = ++mem_num_local;
			}
			break;
		case 2:
			if(scope == 0) {
				memset = ++mem_bool_global;
			} else if (scope == 1) {
				memset = ++mem_bool_constante;	
			} else if (scope == 2) {
				memset = ++mem_bool_local;
			}
			break;
		case 3:
			break;
	}
	//std::cout << "Memset: " << memset << std::endl;
	return memset;
	
}



/**
* Simplemente devuelve la tabla de variables que contiene TODAS las variables
**/
MapType creaTablaFuncion(std::string str){
	//std::cout << "CreaTablaFuncion" << std::endl;
	MapType vars;

	return vars;
}

/**
* Cambia el cuadruplo que busca el MAIN
**/
void cuadruploMain() {
	//std::cout << cuadruploMain << std::endl;
	std::stringstream sstm;
	std::string str;
	sstm << "" << cuad_actual;
	str = sstm.str();
	Cuadruplo::Cuadruplo cuad(13, -1, -1, str);
	vec_cuadruplos[0] = cuad;
	
}

/**
* Busca que se hayan usado todos los parametros de la funcion
**/
void finParametros(){
	if(!pTipoParams.empty()) {
		std::cout << "No se vacio pila de params =(" << std::endl;
		std::stack<std::string> aux = pTipoParams;
		while(!aux.empty()) {
			std::cout << aux.top() << std::endl;
			aux.pop();
		}
	} else {
		std::cout << "Pila tipo parametros vacia =) " << std::endl;
	}
}

/**
* Inicializa la memoria en 0 para una funcion en especifico
**/
EspacioMemoria* inicializaMemoria(EspacioMemoria *memory) {
	//std::cout << incializaMemoria << std::endl;
	EspacioMemoria *memset = memory;
	memset->numl = 0;
	memset->nump = 0;
	memset->booll = 0;
	memset->boolp = 0;
	memset->textol = 0;
	memset->textop = 0;
	memset->total = 0;

	return memset;
}

/**
* Va agregando la cantidad de variables necesarias para la funcion
**/ 
void modificaMemoria (std::string str) {
//	std::cout << "modificaMemoria" << std::endl;
	MapFunc::iterator it = map_func.find(std::string(str));
	if(it ==  map_func.end()) {
		std::cout << "Funcion no encontrada: " << str 
			<< std::endl;
		std::cout << contlin << std::endl;
		exit(1);
	} else {
		int a = convierteTipo(tipo_actual);
		Funcion *func = new Funcion();
		func = it->second;
		switch (a) {
			case 1: {
				func->memoria->nump++;	
				break;
			}
			case 2: {
				func->memoria->boolp++;					
				break;
			}
			case 3: {
				func->memoria->textop++;					
				break;
			}

		}
		func->memoria->total++;
//		std::cout << "mem:" << func->memoria->nump << func->memoria->boolp
//			 << func->memoria->boolp << std::endl;
		map_func[str] = func;	
	
	}
}

/**
* Inicializa una funcion y le asigna ciertos parametros
**/
void agregaFuncion (){
//	std::cout << "AgregaFuncion" << std::endl;
	Funcion *func =  new Funcion();
	EspacioMemoria *memset;
	memset = inicializaMemoria(memset);
	func-> nombre = yytext;
	func-> tipo = convierteTipo(tipo_actual);
	func-> variables = map_vars;
	func-> cuad_ini = cuad_actual;
	func-> memoria = memset;
	
	map_func[func->nombre] = func;
	//std::cout << "FuncGuar: " << func->nombre << std::endl;

}

/**
* Va generando los cuadruplos para los estatutos de ciclos y demas funciones
* ya predefinidas por el lenguaje.
**/
void cuadruploEstatuto(int tipo) {
//	std::cout << "CuadruploEstatuto" << std::endl;
	std::string nombre;
	switch(tipo) {
		/*
		* Del case 0 al 2 son para la implementacion de los if y else,
		* del case 3 al 4 son para la implementacion del while,
		* del case 4 al 5 son para el do while,
		* el case 6 es para un RET con o sin tipo,
		* el case 7 genera el ERA de la función actual,
		* el case 8 crea los PARAM de las llamadas a funcion, 
		* el case 9 busca el cuadruplo donde inicia para crear el GOSUB
		+ el case 10 es el primer GOTO y busca el MAIN
		*/
		case 0: {
	//		std::cout << "Case0" << std::endl;
			int a;
			Node *resultado;
			if(!pilaO.empty())resultado = pilaO.top();
			else {std::cout << "Error case0" << std::endl; exit(1);}
			a = resultado->tipo;
			if (a == -1 || a == 3  ) {
				std::cout << "Error de tipo: " << resultado->nombre 
				<< std::endl;
			} else {
				std::cout << "15, " << resultado->nombre << ", -1, ____\n";
				Cuadruplo::Cuadruplo cuad1(15, resultado->loc_mem,
					 -1, "___");
				vec_cuadruplos.push_back(cuad1);
				cuad_actual++;
				pSaltos.push(cuad_actual - 1);
			}
			break; 
		}
		
		case 1: {
	//		std::cout << "Case1" << std::endl;
			std::stringstream sstm1;
			std::cout << "13, " << "-1" << ", -1, ___\n";
			Cuadruplo::Cuadruplo cuad3(13, -1, -1, "___");
			vec_cuadruplos.push_back(cuad3);
			cuad_actual++;
			if(pSaltos.empty()) std::cout << "EY" << std::endl;
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
	//		std::cout << "Case2" << std::endl;
			std::stringstream sstm2;
			if(pSaltos.empty()) std::cout << "EY" << std::endl;
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
			std::cout << "Case3" << std::endl;
			pSaltos.push(cuad_actual);
			break;
		}
		
		case 4: {
	//		std::cout << "Case4" << std::endl;
			std::stringstream sstm3;
			std::stringstream sstm4;
			if(pSaltos.empty()) std::cout << "EY" << std::endl;
			int falso, retorno;
			falso = pSaltos.top();
			pSaltos.pop();
			if(pSaltos.empty()) std::cout << "EY2" << std::endl;
			retorno = pSaltos.top();
			pSaltos.pop();
			sstm3 << "" << retorno;
			nombre = sstm3.str();
			std::cout << "13, " << "-1" << ", -1, " << nombre << "\n";
			Cuadruplo::Cuadruplo cuad4(13, -1, -1, nombre);
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
	//		std::cout << "Case5" << std::endl;
			int a, retorno;
			Node *resultado;
			std::stringstream sstm5;
			resultado = pilaO.top();
			a = resultado->tipo;
			if (a == 3 || a == -1 ) {
				std::cout << "Error de tipo: " << resultado->nombre
				<< std::endl;
			} else {
				if(pSaltos.empty()) std::cout << "EY" << std::endl;
				retorno = pSaltos.top();
				pSaltos.pop();
				sstm5 << "" << retorno;
				nombre = sstm5.str();
				std::cout << "15, " << resultado->nombre << ", -1, " << nombre <<"\n";
				Cuadruplo::Cuadruplo cuad5(15, resultado->loc_mem,
					 -1, nombre);
				vec_cuadruplos.push_back(cuad5);
				cuad_actual++;
			}
			break;
		}
		case 6: {
	//		std::cout << "Case6" << std::endl;
			if(tipo_func != "libre") {
				Node *retorno = new Node();
				if (!pilaO.empty()) {
					retorno = pilaO.top();
					int a = convierteTipo(tipo_func);
					if ( a != retorno ->tipo) { 
						std::cout << "Error tipos" << std::endl;
						exit(1);
					} else {
						std::cout << "18, " << retorno->nombre << ", -1, " << "" << "\n";
						Cuadruplo::Cuadruplo cuad6(18,
							retorno->loc_mem, -1, " ");
						vec_cuadruplos.push_back(cuad6);
						cuad_actual++; 
					}
				} else {}
			} else {
				std::cout << "18, " << "-1" << ", -1, " << "" << "\n";
				Cuadruplo::Cuadruplo cuad6(18, -1, -1, " ");
				vec_cuadruplos.push_back(cuad6);
				cuad_actual++;
			}
			break;
		}
		case 7: {
	//		std::cout << "Case7" << std::endl;		
			std::cout << "16, " << func_actual << ", w, " << "" << "\n";
			Cuadruplo::Cuadruplo cuad7(16, func_actual, "w", " ");
			vec_cuadruplos.push_back(cuad7);
			cuad_actual++;
			break;
		}
		case 8: {
	//		std::cout << "Case8" << std::endl;
			std::string str;
			Node *var = pilaO.top();
			Funcion *func = new Funcion();
			func = map_func[func_actual];
			if (pilaO.empty() ) {
				std::cout << "PilaO vacia" << std::endl;
			} else  if (func->pTipoParams.empty()) {
				std::cout << "pTipoParams vacia" << std:: endl;
			} else {
				int b;
				int a = var->tipo;
				str = func->pTipoParams.top();
				b = convierteTipo(str);
				//std::cout << var->nombre << std::endl;
				if(a == b) {
					//std::cout << "generando..." << std::endl;
					std::stringstream sstm;
					sstm << "param" << param_count;
					str = sstm.str();
					std::cout << "19, " << var->nombre << ", -1, " << str << "\n";
					Cuadruplo::Cuadruplo cuad8(19, var->loc_mem,
						 -1, str);
					vec_cuadruplos.push_back(cuad8);
					cuad_actual++;
				} else {
					std::cout << "No coinciden los tipos PARAM" <<std::endl;
					std::cout << var->tipo << " <> " << str << std::endl;
					std::cout << var->nombre << std::endl;
				}	
			} 
			break;
		}
		case 9: {
	//		std::cout << "Case9" << std::endl;
	//		std::cout << func_actual << std::endl;
			MapFunc::iterator it = map_func.find(func_actual);
			if(it == map_func.end()) {
				//meterPilaO();
				//std::cout << "Error en encontrar funcion: " << func_actual 
				//	<< std::endl;
				//exit(1);
			} else {
				Funcion *func = it->second;
				std::string str;
				std::stringstream sstm;
				sstm << "" << func->cuad_ini;
				str = sstm.str();	
				std::cout << "17, " << func_actual << ", w, " << str << "\n";
				Cuadruplo::Cuadruplo cuad9(17, func_actual, "w", str);
				vec_cuadruplos.push_back(cuad9);
				cuad_actual++;
			}	
			break;
		}

		case 10: {
		//	std::cout << "Case10" << std::endl;		
			std::cout << "13, " << "-1" << ", -1, " << "___" << "\n";
			Cuadruplo::Cuadruplo cuad0(13, -1, -1, "___");
			vec_cuadruplos.push_back(cuad0);
			cuad_actual++;
			break;
		}
	}
//	std::cout << "sali cuadruploEstatuto" << std::endl; 
}


/**
*
* La función sirve para generar un cuadruplo de acuerdo a la operacion que se
* vaya a realizar.
*
**/
void checaOperador(int a) {
//	std::cout << "checaOperador" << std::endl;
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
			//imprimePila(pilaO);
			
			if (operador == 11 || operador == 12){
			} else if (operador == 4) {
				tmp2 = pilaO.top();
				pilaO.pop();
				tmp1 = pilaO.top();
				pilaO.pop();
				if(cubo_sem[tmp1->tipo - 1][tmp2->tipo - 1][operador]
					> 0) {
					std::stringstream sstm;
					std::string str;
					sstm << "" << tmp2->loc_mem;
					str = sstm.str();
					std::cout << operador << ", " << tmp2->nombre << ", -1, " << tmp1->nombre << "\n";
					Cuadruplo::Cuadruplo cuad(operador, tmp2->loc_mem, 
						-1, tmp1->loc_mem);
					vec_cuadruplos.push_back(cuad);
					cuad_actual++;
					pOper.pop();
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
				if(cubo_sem[tmp1->tipo - 1][tmp2->tipo - 1][operador]
					> 0) {
					Node *var = new Node();
					std::stringstream sstm;
					sstm << "t" << tmp_actual;
					avail = sstm.str();
					var_actual.push(avail);
					tipo_actual = "bool";
					creaVariable();
					actualizaTipoVariables();
					yytext = strdup(avail.c_str());
					meterPilaO();
					tmp_actual++;
					var = pilaO.top();
					std::cout << operador << ", " << tmp1->nombre << ", " << tmp2->nombre << ", " << var->nombre << "\n";
					Cuadruplo::Cuadruplo cuad(operador, tmp1->loc_mem, 
						tmp2->loc_mem, var->loc_mem);
					cuad_actual++;
					vec_cuadruplos.push_back(cuad);
					pOper.pop();
					//imprimePila(1);
				} else {
					std::cout << "Error3: " << tmp1->tipo - 1 
						<< tmp2->tipo - 1
					<< operador	<< std::endl;
					imprimeVector(vec_cuadruplos);
				} 
			} else if (operador < 4) {
				//std::cout << "Operador < 4 " << std::endl;
				tmp2 = pilaO.top();
				pilaO.pop();
				tmp1 = pilaO.top();
				pilaO.pop();
				if(cubo_sem[tmp1->tipo - 1][tmp2->tipo - 1][operador] 
					> 0) {
					Node *var = new Node();
					std::stringstream sstm;
					sstm << "t" << tmp_actual;
					avail = sstm.str();
					var_actual.push(avail);
					tipo_actual = "num";
					creaVariable();
					actualizaTipoVariables();
					yytext = strdup(avail.c_str());
					meterPilaO();
					tmp_actual++;
					var = pilaO.top();
					if(!pOper.empty()) pOper.pop();
					else {std::cout << "Error mil" << std::endl;}
					std::cout << operador << ", " << tmp1->nombre << ", " << tmp2->nombre << ", " << var->nombre << "\n";
					Cuadruplo::Cuadruplo cuad(operador, tmp1->loc_mem, 
						tmp2->loc_mem, var->loc_mem);
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

/**
* Agrega los operadores a la pira correspondiente
**/
void meterPilaOper(int esp) {
	//std::cout << "meterPilaOper" << std::endl;
	pOper.push(esp);
	//std::cout << "Guardé: " << esp << std::endl;
}

/**
* Mete a la pila de operandos las variables que se va encontrando
**/
void meterPilaO() {
//	std::cout << "meterPilaO" << std::endl;
	
	const char *aux;
	Node *var = new Node();
	std::string llave;
	llave = std::string(yytext) + "&" + scope_actual;
	aux = llave.c_str();
	MapType::const_iterator it = map_vars.find(aux);
	//std::cout << llave << std::endl;
	if(it == map_vars.end()) { 
		llave = std::string(yytext) + "&global";
		aux = llave.c_str();
		it = map_vars.find(llave);
		if(it != map_vars.end()) pilaO.push(it->second);
		else {
			func_actual = yytext;
			MapFunc::iterator it = map_func.find(std::string(yytext));
			if(it ==  map_func.end()) {
				std::cout << "Variable no encontrada:: " << yytext 
					<< std::endl;
				std::cout << contlin << std::endl;
				exit(1);
			}
		}
	} else {
			pilaO.push(it->second);
	}	
}

/**
* Crea una variable para las constantes numericas
**/
void creaConstanteNum(){
	//std::cout << "creaConstateNum" << std::endl;	
	Node *var = new Node();
	std::string aux = std::string(yytext);
	var->nombre = "cN" + aux;
	var->tipo = 1;
	var->scope = "constante";
	var->valor_num = ::atof(yytext);
	var->id = id_actual++;
	var->loc_mem = memoriaAUsar(1, "constante");
	//std::cout << var->nombre << "\t\t\tmem: " << var->loc_mem << std::endl;
	pilaO.push(var);

}

/**
* Crea una variable para las constantes booleanas
**/
void creaConstanteBool(int a) {
	//std::cout << "CreaConstanteBool" << std::endl;
	Node *var = new Node();
	std::string aux;
	if(!a) aux = "cB0"; 
	else aux = "cB1";
	var->nombre = aux;
	var->tipo = 2;
	var->scope = "constante";
	var->valor_num = a;
	var->id = id_actual++;
	var->loc_mem = memoriaAUsar(2, "constante");
	//std::cout << var->nombre << "\t\tmem: " << var->loc_mem << std::endl;
	pilaO.push(var);

}

void creaConstanteStr(const char *){

}

/**
* Actualiza el tipo de las variables que han sido declaradas 
**/
void actualizaTipoVariables () {
//	std::cout << "ActualizaTipoVariables" << std::endl;	
	int tipo = -1;
	int memset = 0;
	std::string aux;
	const char  *llave; 
	Node *var = new Node();

	tipo = convierteTipo(tipo_actual);	
	
	if (tipo<0) std::cout << std::endl << " E R R O R " << std::endl;
	
	while (!aux_vars.empty()) {
		memset = memoriaAUsar(tipo, scope_actual);
		var = aux_vars.top();
		aux_vars.pop();
		aux =  std::string(var->nombre) + "&" + scope_actual;
		llave = aux.c_str();
		var->tipo = tipo;
		var->loc_mem = memset++;
		map_vars[llave] = var;
//		std::cout << var->nombre << " scope: " << var->scope << " tipo: " 
//			<< var->tipo << " llave: " << llave << std::endl;
	}
}

/**
* Cambia el tipo de String a int
**/
int convierteTipo(std::string str) {
	//std::cout << "convierteTipo" << std::endl;	
	if(str == "num") return (1);
	else if(str == "bool") return (2);
	else if(str == "texto") return (3);
	else if(str == "libre") return (4);
	else return (-1);
}

/**
* Inicializa una variable con la informacion disponible
**/
void creaVariable() {
//	std::cout << "CreaVariable" << std::endl;	
	Node *var = new Node();
	var->nombre = var_actual.top();
	var->tipo = -1;
	var->loc_mem = 999999;
	var->scope = scope_actual;
	var->id = id_actual++;
	var_actual.pop();
	aux_vars.push(var);
	
//	std::cout << "nombre: " << var->nombre << "\t scope: " << scope_actual
//	<< std::endl;

}

/**
* Actualiza el scope global para las variables y funciones
**/
void actualizaScope(std::string str){
	//std::cout << "ActualizaScope" << std::endl;
	scopes.push_back(str);
	tmp_actual = 1;
}

/**
* Imprime una pila de variables
**/
void imprimePila(std::stack<Node*> pila) {
	//std::cout << "imprimePila" << std::endl;	
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

/**
* imprime la pila de operadores
**/
void imprimePila(int a) {
	//std::cout << "ImprimePila2" << std::endl;
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

/**
* Imprime el vector de cuadruplos 
**/
void imprimeVector(std::vector<Cuadruplo> vec) {
	//std::cout << "imprimeVector" << std::endl;
	std::ofstream myfile;
  	myfile.open ("cuacks.cuads");
	std::string str;
	Cuadruplo::Cuadruplo cuad;

	for (int i = 0; i < vec.size(); i++) {
		cuad = vec[i];
		std::cout << i+1 << ": ";
		myfile << i+1 << ": ";
		cuad.print();
		str = cuad.cuadruploStr();
		myfile << str ;
	}
  	myfile.close();
}

/**
* inicializa el cubo con las combinaciones posibles e inicializa los
+ contadores de algunas variables.
**/
void creaCubo(){
	//std::cout << "creaCubo" << std::endl;
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
	mem_num_global = 999;
	mem_num_local = 3000;
	mem_num_constante = 7000;
	mem_bool_global = 9000;
	mem_bool_local = 10000;
	mem_bool_constante = 11000;
	
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

/**
* Genera un error si falla la lectura de algun simbolo (sintaxis)
**/
int yyerror(char* s) {
  extern char *yytext;	// defined and maintained in lex.c  
  printf("ERROR: %s at symbol  %s  on line %d\n",s,yytext,contlin);
  exit(1);
  return 1;
}

