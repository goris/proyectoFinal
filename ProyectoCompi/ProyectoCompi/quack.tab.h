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
     ID = 276,
     CTE_NUM = 277,
     CTE_BOOL = 278,
     CTE_TEXTO = 279,
     SUM = 280,
     MIN = 281,
     PRO = 282,
     DIV = 283,
     EQU = 284,
     LT = 285,
     GT = 286,
     LTE = 287,
     GTE = 288,
     DIF = 289,
     LPA = 290,
     RPA = 291,
     LBR = 292,
     RBR = 293,
     LSQ = 294,
     RSQ = 295,
     SEM = 296,
     DOU = 297,
     COM = 298,
     DOT = 299,
     DEQ = 300
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
#define ID 276
#define CTE_NUM 277
#define CTE_BOOL 278
#define CTE_TEXTO 279
#define SUM 280
#define MIN 281
#define PRO 282
#define DIV 283
#define EQU 284
#define LT 285
#define GT 286
#define LTE 287
#define GTE 288
#define DIF 289
#define LPA 290
#define RPA 291
#define LBR 292
#define RBR 293
#define LSQ 294
#define RSQ 295
#define SEM 296
#define DOU 297
#define COM 298
#define DOT 299
#define DEQ 300




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 55 "sintax.y"
{
	int int_val;
	float float_val;
	char* text;
}
/* Line 1529 of yacc.c.  */
#line 145 "quack.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

