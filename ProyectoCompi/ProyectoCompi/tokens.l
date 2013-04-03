/**
*
* D E C L A R A C I O N E S
*
*/

%{

	#include <stdio.h>
	#include <stdlib.h>
	#include "quack.tab.h"
	
	int contlin = 1;
	int yyerror (char *s);

%}
%option noyywrap
/**
*
* R  E  G  L  A  S 
*
*/

%%

programa { return (PROGRAMA);}
imprime { return (IMPRIME);}
dibuja { return (DIBUJA);}
funcion { return (FUNCION);}
regresa { return (REGRESA);} 
var { return (VAR);}
bool { return (BOOL);}
num { return (NUM);}
texto { return (TEXTO);}
si { return (SI);}
sino { return (SINO);}
haz { return (HAZ);}
por { return (POR);}
mientras { return (MIENTRAS);}
linea { return (LINEA);}
cuadrado { return (CUADRADO);}
triangulo { return (TRIANGULO);}
circulo { return (CIRCULO);}
[a-z]+[a-zA-Z0-9_]* { return (ID);}
[0-9]+[\.]?+[0-9]* { return (CTE_NUM);}
[verdadero|falso] { return (CTE_BOOL);}
\".*\" { return  (CTE_TEXTO);}
"\n" { contlin++; }
[ \t\r\f] {}

"+" {return (SUM);}
"-" {return (MIN);}
"*" {return (PRO);}
"/" {return (DIV);}
"=" {return (EQU);}
"<" {return (LT);}
">" {return (GT);}
"<=" {return (LTE);}
">=" {return (GTE);}
"!=" {return (DIF);}
"(" {return (LPA);}
")" {return (RPA);}
"{" {return (LBR);}
"}" {return (RBR);}
"[" {return (LSQ);}
"]" {return (RSQ);}
";" {return (SEM);}
":" {return (DOU);}
"," {return (COM);}
"." {return (DOT);}
"==" {return (DEQ);} 

. printf("Error lexico en la linea no. %d \n", contlin);
