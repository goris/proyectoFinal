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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 78 "sintax.y"
{
	int int_val;	
	float float_val;
	char* text;
}
/* Line 1529 of yacc.c.  */
#line 147 "quack.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

