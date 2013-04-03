%{

/*
*
* D E C L A R A C I O N E S
*
*/

	#include <stdlib>
	#include <string>
	#include <iostream>
	#include "utilities/strmap.h"

	extern int contlin;	
	extern int yyerror (char *s);
	extern int yylex();
	extern  FILE *yyin;
	extern int yyparse();
	extern char * yytext;
	void imprimeCubo();

	char *var;
	char *tipo;
	StrMap *vars_glob;

	/* 
	*
	* C U B O    S E M A N T I C O
	* 
	* 0 num 1 bool 2 text  [indices]
	* 1 num 2 bool 3 text 0 ERRROR
	* 0+ 1- 2* 3/ 4= 5< 6> 7<= 8>= 9!= 10==
	*
	*/

	int cubo_sem [3][3][11] = { 0 };

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
void imprimeCubo();

int main(int argc, const char * argv[])
{

	
	imprimeCubo();
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

void imprimeCubo(){

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
	std::cout << std::endl
	std::cout << std::endl;
}


int yyerror(char* s) 
{
  extern char *yytext;	// defined and maintained in lex.c

  printf("ERROR: %s at symbol  %s  on line %d\n",s,yytext,contlin);
  //exit(1);
  return 1;
}


