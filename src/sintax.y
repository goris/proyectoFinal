%{

/*
*
* D E C L A R A C I O N E S
*
*/

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
//	#include "SymbolsTable.h"

	extern int contlin;	
	extern int yyerror (char *s);
	extern int yylex();
	extern  FILE *yyin;
	extern  yyparse();
	extern char * yytext;

	char *var;
	char *tipo;

%}

%union{
	int int_val;
	float float_val;
	char* text;
}

%start program

%token <string*> PROGRAMA 
%token <string*> IMPRIME
%token <string*> DIBUJA 
%token <string*> FUNCION 
%token <string*> REGRESA 
%token <string*> VAR
%token <string*> BOOL
%token <string*> NUM
%token <string*> TEXTO
%token <string*> SI
%token <string*> SINO 
%token <string*> HAZ
%token <string*> POR
%token <string*> MIENTRAS
%token <string*> LINEA
%token <string*> CUADRADO
%token <string*> TRIANGULO
%token <string*> CIRCULO
%token <string*> ID
%token <double> CTE_NUM
%token <string*> CTE_BOOL 
%token <string*> CTE_TEXTO 


%token SUM MIN PRO DIV EQU LT GT LTE GTE DIF LPA RPA LBR RBR LSQ RSQ SEM DOU COM DOT DEQ

%left SUM MIN 
%left PRO DIV

/*
*
* R E G L A S    G R A M A T I C A L E S
*
*/

%%

program: PROGRAMA ID LBR vars bloque funciones RBR

vars: VAR vars2 tipo SEM vars
    |

vars2: ID vars3

vars3: LSQ CTE_NUM RSQ vars3
     | COM vars2
     |

tipo: NUM 
    | TEXTO 
    | BOOL 

bloque: estatutos bloque
      | ciclos bloque
      | dibuja bloque
      |

estatutos: asignacion 
	 | condicion 
	 | escritura 

asignacion: ID EQU sexp SEM 

condicion: SI LPA sexp RPA LBR bloque RBR condicion1
condicion1: | SINO LBR bloque RBR

escritura: IMPRIME LPA escritura1 RPA SEM
escritura1: exp escritura2 
escritura2: DOT escritura1
 	  |

ciclos: mientras 
      | haz
      | por

sexp: exp expresion1
expresion1: operadores exp
 | 

operadores: LT | GT | DIF | LTE | GTE | DEQ

exp: termino exp1
exp1: SUM exp 
    | MIN exp 
    | EQU exp
    |

termino: factor termino1
termino1: PRO termino 
	| DIV termino
	|

factor: LPA sexp RPA 
      | SUM var_cte 
      | MIN var_cte 
      | var_cte

var_cte: ID 
       | CTE_BOOL 
       | CTE_NUM
       | CTE_TEXTO 
	 
funciones: FUNCION tipo ID LBR vars bloque REGRESA var_cte SEM RBR funciones 
	| 

dibuja: triangulo
      | cuadrado
      | circulo
      | linea

por: POR LPA sexp DOU sexp RPA LBR bloque RBR

haz: HAZ LBR bloque RBR MIENTRAS LPA sexp RPA SEM 

mientras: MIENTRAS LPA sexp RPA LBR bloque RBR 

cuadrado: CUADRADO LPA CTE_NUM RPA SEM

circulo: CIRCULO LPA CTE_NUM RPA SEM

linea: LINEA LPA CTE_NUM COM CTE_NUM RPA SEM
	
triangulo: TRIANGULO LPA CTE_TEXTO COM CTE_NUM RPA SEM




%%

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			printf("Error reading from %s\n", argv[1]);
			return -1;
		}
		yyin = fp;

	} else {


	}
	int a = yyparse();
	if (!a) printf("Eres un campeon\n");  
}



int yyerror(char* s) 
{
  extern char *yytext;	// defined and maintained in lex.c

printf("ERROR: %s at symbol  %s  on line %d\n",s,yytext,contlin);
  //exit(1);
return 1;
}


