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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 138 "sintax.y"
{
	int int_val;	
	float float_val;
	char* text;
}
/* Line 1529 of yacc.c.  */
#line 149 "quack.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

