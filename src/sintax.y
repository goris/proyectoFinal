%{
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

	extern int contlin;
	extern int yyerror (char *s);
	extern int yylex();
	extern  FILE *yyin;
	extern int yyparse();
	extern char * yytext;
	void imprimeCubo();
	int id_actual;
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


/*
	*
	* 
	*	C U B O    S E M A N T I C O
	*
	* 0 num 1 bool 2 text  [indices]
	* 1 num 2 bool 3 text 0 ERRROR
	* 0+ 1- 2* 3/ 4= 5< 6> 7<= 8>= 9!= 10== 11( 12) 13goto 14gotoV
	* 15gotoF 
	* [tipo1] [tipo2] [operador] 
	*/
	int cubo_sem [3][3][11] = { 0 };

	void creaCubo();
	void manipulaStack();
	void actualizaScope(std::string);
	void creaVariable();
	void creaConstanteNum();
	void creaConstanteBool(int);
	void creaConstanteStr(const char *);
	void actualizaTipoVariables();
	void meterPilaO();
	void meterPilaOper(int);
	void imprimePila(std::stack<Node*>);
	void imprimePila(int a);
	void generaCuadruplo(int, int, int, int, int);
	void generaCuadruploEstatuto(int, int, int, int);
	void checaOperador(int);
	void cuadruploEstatuto(int);
	void imprimeVector(std::vector<Cuadruplo>);

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
%token <string*> VERDADERO
%token <string*> FALSO
%token <double> CTE_NUM
%token <string*> CTE_TEXTO 
%token <string*> ID
%token SUM MIN PRO DIV EQU LT GT LTE GTE DIF LPA RPA LBR RBR LSQ RSQ 
SEM DOU COM DOT DEQ
%left SUM MIN 
%left PRO DIV

/*** R E G L A S    G R A M A T I C A L E S**/

%%

program: PROGRAMA ID 
	   { scope_actual = "global"; actualizaScope("global"); }
 LBR vars bloque funciones RBR

vars: VAR vars2 tipo 
	{tipo_actual = yytext; actualizaTipoVariables(); }
 SEM vars
	|
vars2: ID 
	 {var_actual.push(yytext); }
 vars3 { creaVariable(); }
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

asignacion: ID { meterPilaO(); }
		  EQU { meterPilaOper(4); } sexp SEM 

condicion: SI LPA sexp RPA 
		LBR { cuadruploEstatuto(0); } bloque RBR
		 condicion1 { cuadruploEstatuto(2); } 
condicion1: SINO { cuadruploEstatuto(1); }LBR bloque RBR 
 			| 

escritura: IMPRIME LPA escritura1 RPA SEM
		 escritura1: exp escritura2 
escritura2: DOT escritura1
		  |

ciclos: mientras
	  | haz
	  | por

sexp: exp expresion1 { checaOperador(4); }
expresion1: operadores exp   
	  | 
operadores: LT { meterPilaOper(5); } 
		| GT  { meterPilaOper(6); } 
		| DIF { meterPilaOper(9); } 
		| LTE { meterPilaOper(7); } 
		| GTE { meterPilaOper(8); } 
		| DEQ { meterPilaOper(10); }
		| EQU { meterPilaOper(4); } 
exp: termino { checaOperador(0); } exp1
   exp1: SUM { meterPilaOper(0); } exp
	| MIN { meterPilaOper(1); }  exp
		|
termino: factor { checaOperador(2); } termino1 
termino1: PRO { meterPilaOper(2); } termino
	| DIV { meterPilaOper(3); }  termino
	|
factor: LPA { meterPilaOper(11); } sexp RPA { pOper.pop(); }
	  | var_cte
var_cte: cte_bool  
	   | CTE_NUM { creaConstanteNum(); }
		| CTE_TEXTO { creaConstanteStr(yytext); }
	| ID { meterPilaO(); }

cte_bool: VERDADERO { creaConstanteBool(1); }
		| FALSO { creaConstanteBool(0); }

funciones: FUNCION tipo ID
		 { scope_actual = yytext; actualizaScope("funcion"); }
 LBR vars bloque REGRESA var_cte SEM RBR funciones
	 | 

dibuja: triangulo
	  | cuadrado
	  | circulo
	  | linea

por: POR LPA sexp DOU sexp RPA LBR bloque RBR

haz: HAZ { cuadruploEstatuto(3); } LBR bloque RBR 
   MIENTRAS LPA sexp RPA { cuadruploEstatuto(5); } SEM 

mientras: MIENTRAS { cuadruploEstatuto(3); } LPA sexp RPA 
	   { cuadruploEstatuto(0); } LBR bloque RBR { cuadruploEstatuto(4); }

cuadrado: CUADRADO LPA CTE_NUM RPA SEM

circulo: CIRCULO LPA CTE_NUM RPA SEM

linea: LINEA LPA CTE_NUM COM CTE_NUM RPA SEM

triangulo: TRIANGULO LPA CTE_TEXTO COM CTE_NUM RPA SEM

%%




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

void cuadruploEstatuto(int tipo) {

	std::string nombre;
	switch(tipo) {
		/*
		* Del case 0 al 2 son para la implementacion de los if y los if/else,
		* del case 3 al 4 son para la implementacion del while,
		* del case 4 al 5 son para el do while
		*/
		case 0: {
			int a;
			Node *resultado;
			resultado = pilaO.top();
			a = resultado->tipo;
			if (a == -1 || a == 3  ) {
				std::cout << "Error de tipo: " << resultado->nombre << std::endl;
			} else {
				Cuadruplo::Cuadruplo cuad1(15, resultado->nombre, "", "___");
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
				std::cout << "Error de tipo: " << resultado->nombre << std::endl;
			} else {
				retorno = pSaltos.top();
				pSaltos.pop();
				sstm5 << "" << retorno;
				nombre = sstm5.str();
				Cuadruplo::Cuadruplo cuad5(15, resultado->nombre, "", nombre);
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
	Node* tmp1 = new Node();
	Node* tmp2 = new Node();
	int aux = -1;

	if (!pilaO.empty() && !pOper.empty()) {
		int operador = pOper.top();

		if (operador == 0 && a == 0) aux = a;
		else if (operador == 1 && a == 0) aux = a;
		else if (operador == 2 && a == 2) aux = a;
		else if (operador == 3 && a == 2) aux = a;
		else if (operador == 4 && a == 4) aux = a;
		else if (operador >= 5 && a == 4) aux = a;

		if(aux == a){
			
			if (operador == 11 || operador == 12){
			} else if (operador == 4) { 
				tmp2 = pilaO.top();
				pilaO.pop();
				tmp1 = pilaO.top();
				pilaO.pop();
				if(cubo_sem[tmp1->tipo - 1][tmp2->tipo - 1][operador] > 0) {
					std::stringstream sstm;
					Cuadruplo::Cuadruplo cuad(operador, tmp2->nombre, 
						" ", tmp1->nombre);
					pOper.pop();
					vec_cuadruplos.push_back(cuad);
					cuad_actual++;
				} else {
					std::cout << "Error2: " << tmp1->tipo - 1 << tmp2->tipo - 1
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
					scope_actual = "global";
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
					std::cout << "Error3: " << tmp1->tipo - 1 << tmp2->tipo - 1
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
					scope_actual = "global";
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
					std::cout << "Error1: " << tmp1->tipo - 1 << tmp2->tipo - 1
					<< operador	<< std::endl;
					imprimeVector(vec_cuadruplos);
				}
			}
		}
	}
}

void meterPilaOper(int esp) {

	pOper.push(esp);
	//std::cout << "Guardé: " << esp << std::endl;
}

void meterPilaO() {
	const char *aux;
	Node *var = new Node();
	std::string llave;

	llave = std::string(yytext) + "&" + scope_actual;
	aux = llave.c_str();
	MapType::const_iterator it = map_vars.find(aux);

	if(it == map_vars.end()) { 
			llave = std::string(yytext) + "&global";
			aux = llave.c_str();
			it = map_vars.find(llave);
			if(it != map_vars.end()) pilaO.push(it->second);
			else {
				std::cout << "Variable no encontrada:" << llave << std::endl;
				exit(1);
			}
	} else {
			pilaO.push(it->second);
	}


}

void creaConstanteNum(){
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
	int tipo = -1;
	std::string aux;
	const char  *llave; 
	Node *var = new Node();

	if(tipo_actual == "num") tipo = 1;
	else if(tipo_actual == "bool") tipo = 2;
	else if(tipo_actual == "texto") tipo = 3;
	else std::cout << std::endl << " E R R O R " << std::endl;

	while (!aux_vars.empty()) {
		var = aux_vars.top();
		aux_vars.pop();
		aux =  std::string(var->nombre) + "&" + scope_actual;
		llave = aux.c_str();
		var->tipo = tipo;
		map_vars[llave] = var;
	}
}

void creaVariable() {
	Node *var = new Node();
	var->nombre = var_actual.top();
	var->tipo = -1;
	var->scope = scope_actual;
	var->id = id_actual++;
	var_actual.pop();
	aux_vars.push(var);


}

void actualizaScope(std::string str){
	scopes.push_back(str);
}

void imprimePila(std::stack<Node*> pila) {
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
	Cuadruplo::Cuadruplo cuad;

	for (int i = 0; i < vec.size(); i++) {
		cuad = vec[i];
		std::cout << i+1 << ": ";
		cuad.print();
		
	}
	
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
