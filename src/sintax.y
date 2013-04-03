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
	
	struct Node {
		int tipo;
		float valor_num;
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
	std::stack <std::string> var_actual;
	std::string tipo_actual;
	std::string scope_actual;
	std::vector<std::string> scopes;	
	std::stack<Node*> aux_vars;
	std::stack<Node*> pilaO;
	std::stack<Node*> pOper;
	std::stack<Node*> pTipos;
	MapType map_vars;
	
	
	/*
	*
	* 
	*	C U B O    S E M A N T I C O
	*
	* 0 num 1 bool 2 text  [indices]
	* 1 num 2 bool 3 text 0 ERRROR
	* 0+ 1- 2* 3/ 4= 5< 6> 7<= 8>= 9!= 10==
	*
	*/
	int cubo_sem [3][3][11] = { 0 };

	void creaCubo();
	void manipulaStack();
	void actualizaScope(std::string str);
	void creaVariable();
	void creaConstanteNum();
	void creaConstanteStr();
	void actualizaTipoVariables();
	void meterPilaO();
	void imprimePila(std::stack<Node*> pila);


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
%token SUM MIN PRO DIV EQU LT GT LTE GTE DIF LPA RPA LBR RBR LSQ RSQ SEM DOU COM DOT DEQ

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
				 	EQU sexp SEM 
	  
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
var_cte: cte_bool 
        | CTE_NUM { creaConstanteNum(); }
        | CTE_TEXTO { creaConstanteStr(); }
	| ID { meterPilaO(); }

cte_bool: VERDADERO
	| FALSO

funciones: FUNCION tipo ID
 { scope_actual = yytext; actualizaScope("funcion"); }
 LBR vars bloque REGRESA var_cte SEM RBR funciones
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

	imprimePila(pilaO);
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
	pilaO.push(var);
	
}

void creaConstanteStr(){

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

	while(!pila.empty()) {
		var = pila.top();
		std::cout << "Nombre: " << var->nombre << std::endl;
		pila.pop();
	}

	std::cout << "----------------------------------------" << std::endl;
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

/*	std::cout << "         + - * / = < > < > ! ==";
	
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
	std::cout << std::endl; */
}

int yyerror(char* s) {
  extern char *yytext;	// defined and maintained in lex.c  
  printf("ERROR: %s at symbol  %s  on line %d\n",s,yytext,contlin);
  exit(1);
  return 1;
}
