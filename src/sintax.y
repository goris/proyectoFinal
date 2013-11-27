%{
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
		EspacioMemoria memoria;
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
	* 99Fin
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
	int sumar;

	std::ofstream myfile;

	std::string avail;
	std::string func_actual;
	std::string func_llamada;
	std::string scope_actual;
	std::string tipo_actual;
	std::string tipo_func;
	std::string tmp;
	std::stack<int> pOper;
	std::stack<int> pSaltos;
	std::stack<Node*> aux_vars;
	std::stack<Node*> pilaO;
	std::stack<std::string> var_actual;
	std::stack<std::string> pTipoParams;
	std::vector<Cuadruplo> vec_cuadruplos;
	std::vector<std::string> scopes;
	MapType map_vars;
	MapFunc map_func;


	int convierteTipo(std::string);
	int memoriaAUsar(int, std::string);
	int* traePuntos(int);
	void actualizaScope(std::string);
	void actualizaTipoVariables();
	void agregaFuncion();
	void agregaVarMemFunc(int, int);
	void checaOperador(int);
	void creaConstanteNum();
	void creaConstanteBool(int);
	void creaConstanteStr(const char *);
	void creaCubo();
	void creaVarFunc(std::string, int);
	void creaVariable();
	void cuadruploEstatuto(int);
	void cuadruploEnd();
	void cuadruploMain();
	void finParametros();
	void limpiaContMemoria();
	void imprimeCubo();
	void imprimeMapaFunc();
	void imprimeMapaVars();
	void imprimePila(std::stack<Node*>);
	void imprimePila(int);
	void imprimeVector(std::vector<Cuadruplo>);
	void manipulaStack();
	void meterPilaO();
	void meterPilaOper(int);
	void modificaMemoria(std::string);
	EspacioMemoria* inicializaMemoria(EspacioMemoria*);
	MapType creaTablaFuncion(std::string);


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
%token <string*> LIBRE
%token <string*> SI
%token <string*> SINO
%token <string*> HAZ
%token <string*> POR
%token <string*> MIENTRAS
%token <string*> LINEA
%token <string*> RECTANGULO
%token <string*> TRIANGULO
%token <string*> ELIPSE
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

program: PROGRAMA ID { scope_actual = "global"; actualizaScope("global");
	   	cuadruploEstatuto(10); } LBR vars
	funciones { scope_actual = "global"; actualizaScope("global"); }
	{ cuadruploMain(); } bloque dibuja RBR { cuadruploEnd(); }

vars: VAR vars2 tipo { tipo_actual = yytext; actualizaTipoVariables(); }
	SEM vars
	|
vars2: ID { var_actual.push(yytext); param_count++; } vars3 { creaVariable(); }
vars3: LSQ CTE_NUM RSQ vars3
	 | COM vars2
	 |

tipo: NUM { agregaVarMemFunc(0, sumar); }
	| TEXTO { agregaVarMemFunc(1, sumar); }
	| BOOL { agregaVarMemFunc(2, sumar); }
	| LIBRE

bloque: estatutos bloque
	  | ciclos bloque
	  |

estatutos: condicion
		 | asig_llamada
	 	 | escritura
		 | funciones1
funciones1: REGRESA sexp SEM { cuadruploEstatuto(6); } 

asig_llamada: ID { meterPilaO(); tmp=yytext; } llamada_
llamada_: asignacion
		| llamada SEM
llamada: leftp
	   { cuadruploEstatuto(7); param_count = 0;  } varsss rightp
	   { /*finParametros();*/ cuadruploEstatuto(9); }

varsss: sexp { param_count++; cuadruploEstatuto(8); } varsss2
varsss2: COM varsss
		| LSQ CTE_NUM RSQ varsss2
		|

funciones: tipo { param_count = 0; tipo_actual = yytext;
		 tipo_func = yytext; } FUNCION ID
		{scope_actual = yytext; func_actual= yytext; actualizaScope("funcion");
		agregaFuncion(); limpiaContMemoria(); } leftp 
		{ sumar = 1; } varss rightp LBR
		vars { agregaVarMemFunc(3,1); param_count = 0; sumar = 0; }
		bloque  RBR { scope_actual = "global"; }
		{ cuadruploEstatuto(11); } funciones
		|


varss: varss2
	 |
varss2: tipo { tipo_actual = yytext; pTipoParams.push(yytext);
		Funcion *func = map_func[func_actual]; func->pTipoParams = pTipoParams;
		map_func[func_actual] = func; } ID
	  	{ actualizaTipoVariables(); var_actual.push(yytext);
	  	 param_count++; modificaMemoria(scope_actual);  }
		varss3 { creaVariable(); actualizaTipoVariables(); }
varss3: COM varss2
	  	| LSQ CTE_NUM RSQ varss3
		|

asignacion: EQU { meterPilaOper(4); } asignacion1 SEM
asignacion1: sexp

condicion: SI leftp sexp rightp
		LBR { cuadruploEstatuto(0); } bloque RBR
		 condicion1 { cuadruploEstatuto(2); }
condicion1: SINO { cuadruploEstatuto(1); } LBR bloque RBR
 			|

escritura: IMPRIME leftp escritura1 rightp  SEM
escritura1: exp { cuadruploEstatuto(12); } escritura2
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
factor: leftp sexp rightp
	  | var_cte
var_cte: cte_bool
	  	| cte_nume 
		| CTE_TEXTO { creaConstanteStr(yytext); }
		| ID { meterPilaO(); } llamada_opt

cte_nume: CTE_NUM { creaConstanteNum(); }

llamada_opt: llamada
		   |

cte_bool: VERDADERO { creaConstanteBool(1); }
		| FALSO { creaConstanteBool(0); }

dibuja: DIBUJA LBR dibuja1 bloque RBR
	  |
dibuja1: formas
	  	|

formas: triangulo dibuja1 
	  | rectangulo dibuja1
	  | elipse dibuja1 
	  | linea dibuja1

por: POR leftp sexp DOU sexp rightp LBR bloque RBR

haz: HAZ { cuadruploEstatuto(3); } LBR bloque RBR
   MIENTRAS leftp sexp rightp { cuadruploEstatuto(5); } SEM

mientras: MIENTRAS { cuadruploEstatuto(3); } leftp sexp rightp
	  { cuadruploEstatuto(0); } LBR bloque RBR { cuadruploEstatuto(4); }

linea: LINEA leftp exp COM exp COM exp COM exp 
	 rightp { cuadruploEstatuto(13); } SEM

rectangulo: RECTANGULO leftp exp COM exp COM exp COM exp
		 { cuadruploEstatuto(14); } rightp SEM

elipse: ELIPSE leftp exp COM exp COM exp COM exp
	 { cuadruploEstatuto(15); } rightp SEM

{ /* Se usan tres puntos para dibujar el triangulo */}
triangulo: TRIANGULO leftp exp COM exp COM exp COM exp 
		COM exp COM exp rightp { cuadruploEstatuto(16); } SEM

leftp: LPA { meterPilaOper(11); }
rightp: RPA { pOper.pop(); }
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
	//imprimePila(pilaO);
	myfile.open("cuacks.cuads");
	imprimeMapaFunc();
	imprimeMapaVars();
	imprimeVector(vec_cuadruplos);
	myfile.close();
	if (!a) printf("Eres un campeon\n");
}

/**
* Trae el numero de puntos indicados y devuelve un arreglo con ellos
**/
int* traePuntos (int cant) {
	//std::cout << "TraePuntos" << std::endl;
	int *puntos = new int[cant];
	if(pilaO.size() < cant - 1) {
		std::cout << "Insuficientes valores para generar cuadruplo " 
		<< cant << " : " << pilaO.size() << std::endl;
		imprimePila(pilaO);
		exit(1);
	} 
	std::stack<Node*> aux = pilaO;
	for (int i = 0; i < cant; i++){
		Node* var = aux.top();
		puntos[i] = var->loc_mem;
		std::cout << i << ": " << var->loc_mem << std::endl;
		aux.pop();
	}

	return puntos;
}

/**
* Aumenta el contador de variables para las funciones
**/
void agregaVarMemFunc(int a, int var){
	//std::cout << "agregaVarMemFunc" << std::endl;
	//std::cout << scope_actual << " : " << func_actual << std::endl;
	MapFunc::iterator it = map_func.find(func_actual);
	if(it != map_func.end() && var == 1 ){
		Funcion *func = new Funcion();
		func = it->second;
		EspacioMemoria mem = func->memoria;
		if(a == 0) mem.numl++;
		if(a == 1) mem.booll++;
		if(a == 2) mem.textol++;
		if(a == 3) mem.total = param_count;
		func->memoria = mem;
		map_func[func_actual] = func;
	} else {
		//std::cout << " no se encontro: " << func_actual << std::endl;
	}
}

/**
* Imprime todas las variables que se guardaron
**/
void imprimeMapaFunc() {
	//std::cout << imprimeMapaFunc << std::endl;
	Funcion *tmp = new Funcion();
	std::string str;
	MapFunc::const_iterator end = map_func.end();

	for(MapFunc::const_iterator it = map_func.begin() ;
		it != end; ++it) {
		tmp = it->second;
		EspacioMemoria mem;
		mem = tmp->memoria;
		myfile << tmp->nombre << ", " << tmp->tipo << ", " <<
		tmp->memoria.total << ", " << tmp->cuad_ini << std::endl;
		std::cout << tmp->nombre << ", " << tmp->tipo << ", " <<
		tmp->memoria.total << ", " << tmp->cuad_ini << std::endl;
	}

	myfile << "&&&" << std::endl;
	std::cout << "&&&" << std::endl;
}

/**
* Imprime todas las variables que se guardaron
**/
void imprimeMapaVars() {
	Node *tmp = new Node();
	std::string str;
	MapType::const_iterator end = map_vars.end();

	for(MapType::const_iterator it = map_vars.begin() ;
		it != end; ++it) {
			//std::cout << "llave: " << it->first << std::endl;
			if (std::string::npos != it->first.find("cN")) {
				tmp = it->second;
				myfile << tmp->loc_mem << "," << tmp->valor_num << std::endl;
				std::cout << tmp->loc_mem << "," << tmp->valor_num 
				<< std::endl;
			}
			/*
			std::cout << "nombre: " << tmp->nombre << std::endl;
			std::cout << "tipo: " << tmp->tipo << std::endl;
			std::cout << "scope: " << tmp->scope << std::endl;
			std::cout << "mem: " << tmp->loc_mem << std::endl;
			*/
	}

	myfile << "&&&" << std::endl;
	std::cout << "&&&" << std::endl;
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
void cuadruploEnd() {
	//std::cout << "cuadruploEnd" << std::endl;
	std::stringstream sstm;
	Cuadruplo::Cuadruplo cuad(99, -1, -1, "");
	vec_cuadruplos.push_back(cuad);

}

/**
* Cambia el cuadruplo que busca el MAIN
**/
void cuadruploMain() {
	//std::cout << "cuadruploMain" << std::endl;
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
EspacioMemoria inicializaMemoria(EspacioMemoria memory) {
	//std::cout << "incializaMemoria" << std::endl;
	EspacioMemoria memset = memory;
	memset.numl = 0;
	memset.nump = 0;
	memset.booll = 0;
	memset.boolp = 0;
	memset.textol = 0;
	memset.textop = 0;
	memset.total = 0;

	return memset;
}

/**
* Va agregando la cantidad de variables necesarias para la funcion
**/
void modificaMemoria (std::string str) {
	//std::cout << "modificaMemoria" << std::endl;
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
				func->memoria.nump++;
				break;
			}
			case 2: {
				func->memoria.boolp++;
				break;
			}
			case 3: {
				func->memoria.textop++;
				break;
			}

		}
		func->memoria.total++;
		//std::cout << "mem:" << func->memoria.nump << func->memoria.boolp
		//	 << func->memoria.boolp << std::endl;
		map_func[str] = func;

	}
}

/**
* Inicializa una funcion y le asigna ciertos parametros
**/
void agregaFuncion (){
	//std::cout << "AgregaFuncion" << std::endl;
	Funcion *func =  new Funcion();
	EspacioMemoria memset;
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
	//std::cout << "CuadruploEstatuto" << std::endl;
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
		* el case 10 es el primer GOTO y busca el MAIN
		* el case 11 imprime un resultado
		*/
		case 0: {
			//std::cout << "Case0" << std::endl;
			int a;
			Node *resultado;
			if(!pilaO.empty())resultado = pilaO.top();
			else {std::cout << "Error case0" << std::endl; exit(1);}
			a = resultado->tipo;
			if (a == -1 || a == 3  ) {
				std::cout << "Error de tipo: " << resultado->nombre
				<< std::endl;
			} else {
				//std::cout << "15, " << resultado->nombre << ", -1, ____\n";
				Cuadruplo::Cuadruplo cuad1(15, resultado->loc_mem,
					 -1, "___");
				vec_cuadruplos.push_back(cuad1);
				cuad_actual++;
				pSaltos.push(cuad_actual - 1);
			}
			break;
		}

		case 1: {
			//std::cout << "Case1" << std::endl;
			std::stringstream sstm1;
			//std::cout << "13, " << "-1" << ", -1, ___\n";
			Cuadruplo::Cuadruplo cuad3(13, -1, -1, "___");
			vec_cuadruplos.push_back(cuad3);
			cuad_actual++;
			if(pSaltos.empty()) std::cout << "EY1" << std::endl;
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
			//std::cout << "Case2" << std::endl;
			std::stringstream sstm2;
			if(pSaltos.empty()) std::cout << "EY2" << std::endl;
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
			//std::cout << "Case3" << std::endl;
			pSaltos.push(cuad_actual);
			break;
		}

		case 4: {
			//std::cout << "Case4" << std::endl;
			std::stringstream sstm3;
			std::stringstream sstm4;
			if(pSaltos.empty()) std::cout << "EY4.1" << std::endl;
			int falso, retorno;
			falso = pSaltos.top();
			pSaltos.pop();
			if(pSaltos.empty()) std::cout << "EY4.2" << std::endl;
			retorno = pSaltos.top();
			pSaltos.pop();
			sstm3 << "" << retorno;
			nombre = sstm3.str();
			//std::cout << "13, " << "-1" << ", -1, " << nombre << "\n";
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
			//std::cout << "Case5" << std::endl;
			int a, retorno;
			Node *resultado;
			std::stringstream sstm5;
			resultado = pilaO.top();
			a = resultado->tipo;
			if (a == 3 || a == -1 ) {
				std::cout << "Error de tipo: " << resultado->nombre
				<< std::endl;
			} else {
				if(pSaltos.empty()) std::cout << "EY5" << std::endl;
				retorno = pSaltos.top();
				pSaltos.pop();
				sstm5 << "" << retorno;
				nombre = sstm5.str();
				//std::cout << "15, " << resultado->nombre << ", -1, " 
				//<< nombre <<"\n";
				Cuadruplo::Cuadruplo cuad5(15, resultado->loc_mem,
					 -1, nombre);
				vec_cuadruplos.push_back(cuad5);
				cuad_actual++;
			}
			break;
		}
		case 6: {
			//std::cout << "Case6" << std::endl;
			if(tipo_func != "libre") {
				Node *retorno = new Node();
				if (!pilaO.empty()) {
					retorno = pilaO.top();
					int a = convierteTipo(tipo_func);
					if ( a != retorno ->tipo) {
						std::cout << "Error tipos" << std::endl;
						exit(1);
					} else {
						//std::cout << "18, " << retorno->nombre <<
						// ", -1, " << "" << "\n";
						Cuadruplo::Cuadruplo cuad6(18,
							retorno->loc_mem, -1, " ");
						vec_cuadruplos.push_back(cuad6);
						cuad_actual++;
					}
				} else {}
				break;
			}
		}

		case 7: {
			//std::cout << "Case7" << std::endl;
			//std::cout << "16, " << func_actual << ", w, " << "" << "\n";
			Cuadruplo::Cuadruplo cuad7(16, func_actual, "w", " ");
			func_llamada = func_actual;
			vec_cuadruplos.push_back(cuad7);
			cuad_actual++;
			break;
		}
		case 8: {
			//std::cout << "Case8" << std::endl;
			std::string str;
			Funcion *func = new Funcion();
			MapFunc::iterator itr;
			itr = map_func.end();
			--itr;
			func = itr->second;
			func = map_func[func_actual];
			if (pilaO.empty() ) {
				std::cout << "PilaO vacia" << std::endl;
			} else  if (func->pTipoParams.empty()) {
				std::cout << "pTipoParams vacia" << std:: endl;
			} else {
				Node *var = pilaO.top();
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
					//std::cout << "19, " << var->nombre << var->scope 
					//<< scope_actual << "\n";
					Cuadruplo::Cuadruplo cuad8(19, var->loc_mem,
						 -1, str);
					vec_cuadruplos.push_back(cuad8);
					cuad_actual++;
					if(pilaO.empty()){
						std::cout << "E R R O RR" << std::endl;
						exit(1);
					} else {
						pilaO.pop();
					}
				} else {
					std::cout << "No coinciden los tipos PARAM" <<std::endl;
					std::cout << var->tipo << " <> " << str << std::endl;
					std::cout << var->nombre << std::endl;
				}
			}
			break;
		}
		case 9: {
			//std::cout << "Case9" << std::endl;
	//		std::cout << func_actual << std::endl;
			MapFunc::iterator it = map_func.find(func_actual);
			if(it == map_func.end()) {
				//std::cout << "Error en encontrar funcion: " << func_actual
				//	<< std::endl;
				//exit(1);
			} else {
				Funcion *func = it->second;
				std::string str;
				std::stringstream sstm;
				sstm << "" << func->cuad_ini;
				str = sstm.str();
				if(pilaO.empty()){
						std::cout << "E R R O RR" << std::endl;
						exit(1);
					} else {
						// pilaO.pop();
				}
				creaVarFunc(func_actual, func->tipo);
				Node* var = pilaO.top();
				Cuadruplo::Cuadruplo cuad9(17, var->loc_mem, -1, str);
				vec_cuadruplos.push_back(cuad9);
				cuad_actual++;
				//std::cout << "17, " << func_actual << ", w, " << str << "\n";
				//std::cout << "cas9: " << func_actual << std::endl;
				//imprimePila(pilaO);
			}
			break;
		}

		case 10: {
			//std::cout << "Case10" << std::endl;
			//std::cout << "13, " << "-1" << ", -1, " << "___" << "\n";
			Cuadruplo::Cuadruplo cuad10(13, -1, -1, "___");
			vec_cuadruplos.push_back(cuad10);
			cuad_actual++;
			break;
		}
		case 11: {
				//std::cout << "18, " << "-1" << ", -1, " << "" << "\n";
			Cuadruplo::Cuadruplo cuad11(18, -1, -1, " ");
			vec_cuadruplos.push_back(cuad11);
			cuad_actual++;
			break;
		}
		case 12: {
			//std::cout << "Case 13" << std::endl;
			//std::cout << "20, " << var->loc_mem << "-1, \n";
			if (pilaO.empty()) {
				std::cout << "12 Error " << std::endl;
				exit(1);
			} 
			Node* var = pilaO.top();
			Cuadruplo::Cuadruplo cuad12(20, var->loc_mem, -1, "");
			vec_cuadruplos.push_back(cuad12);
			cuad_actual++;
			break;
		}
		case 13: {
			//std::cout << "Case 13" << std::endl;
			//std::cout << "21, " << var->loc_mem << "-1, \n";
			if (pilaO.empty()) {
				std::cout << "13 Error " << std::endl;
				exit(1);
			}
			int *points = traePuntos(4);
			Cuadruplo::Cuadruplo cuad13a(21, points[0], points[1], points[2]);
			Cuadruplo::Cuadruplo cuad13b(21, points[3], 0, "");
			vec_cuadruplos.push_back(cuad13a);
			cuad_actual++;
			vec_cuadruplos.push_back(cuad13b);
			cuad_actual++;
			break;
		}
		case 14: {
			//std::cout << "Case 13" << std::endl;
			//std::cout << "21, " << var->loc_mem << "-1, \n";
			if (pilaO.empty()) {
				std::cout << "14 Error " << std::endl;
				exit(1);
			}
			int *points = traePuntos(4);
			Cuadruplo::Cuadruplo cuad14a(22, points[0], points[1], points[2]);
			Cuadruplo::Cuadruplo cuad14b(22, points[3], 0, "");
			vec_cuadruplos.push_back(cuad14a);
			cuad_actual++;
			vec_cuadruplos.push_back(cuad14b);
			cuad_actual++;
			break;
		}
		case 15: {
			//std::cout << "Case 13" << std::endl;
			//std::cout << "21, " << var->loc_mem << "-1, \n";
			if (pilaO.empty()) {
				std::cout << "15 Error " << std::endl;
				exit(1);
			}
			int *points = traePuntos(4);
			Cuadruplo::Cuadruplo cuad15a(23, points[0], points[1], points[2]);
			Cuadruplo::Cuadruplo cuad15b(23, points[3], 0, "");
			vec_cuadruplos.push_back(cuad15a);
			cuad_actual++;
			vec_cuadruplos.push_back(cuad15b);
			cuad_actual++;
			break;
		}
		case 16: {
			//std::cout << "Case 13" << std::endl;
			//std::cout << "21, " << var->loc_mem << "-1, \n";
			if (pilaO.empty()) {
				std::cout << "16 Error " << std::endl;
				exit(1);
			}
			int *points = traePuntos(6);
			Cuadruplo::Cuadruplo cuad16a(24, points[0], points[1], points[2]);
			Cuadruplo::Cuadruplo cuad16b(24, points[3], points[4], points[5]);
			vec_cuadruplos.push_back(cuad16a);
			cuad_actual++;
			vec_cuadruplos.push_back(cuad16b);
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
	//std::cout << "checaOperador" << std::endl;
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
				//imprimePila(pilaO);
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
					//std::cout << operador << ", " << tmp2->nombre 
					//<< ", -1, " << tmp1->nombre << "\n";
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
					//std::cout << operador << ", " << tmp1->nombre << 
					//", " << tmp2->nombre << ", " << var->nombre << "\n";
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
					//std::cout << operador << ", " << tmp1->nombre << ", " 
					//<< tmp2->nombre << ", " << var->nombre << "\n";
					Cuadruplo::Cuadruplo cuad(operador, tmp1->loc_mem,
						tmp2->loc_mem, var->loc_mem);
					vec_cuadruplos.push_back(cuad);
					cuad_actual++;
					//imprimePila(1);
				} else {
					std::cout << "Error1: " << tmp1->tipo - 1
						<< " -- " << tmp2->tipo - 1
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
	//std::cout << "meterPilaO" << std::endl;

	const char *aux;
	Node *var = new Node();
	std::string llave;
	llave = std::string(yytext) + "&" + scope_actual;
	aux = llave.c_str();
	MapType::const_iterator it = map_vars.find(aux);
	//std::cout << llave << std::endl;
	if(it == map_vars.end()) {
		llave = std::string(yytext);
		aux = llave.c_str();
		it = map_vars.find(yytext);
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
	int memset = memoriaAUsar(1, "constante");
	std::stringstream sstm;

	MapType::iterator it = map_vars.find("cN" + memset);
	if(it == map_vars.end()) {
		std::string aux;
		sstm << "cN" << memset;
		var->nombre = sstm.str();
		var->tipo = 1;
		var->scope = "constante";
		var->valor_num = ::atof(yytext);
	//	std::cout << var->valor_num << "  " << memset << std::endl;
		var->id = id_actual++;
		var->loc_mem = memset;
		sstm.str(std::string());
		map_vars[var->nombre] = var;

	//std::cout << var->nombre << "\t\t\tmem: " << var->loc_mem << std::endl;
	} else {
		var = it->second;
		sstm << "cN" << memset;
		var->nombre = sstm.str();
		var->tipo = 1;
		var->scope = "constante";
	//	std::cout << var->valor_num << "  " << memset-- << std::endl;
		var->valor_num = ::atof(yytext);
		var->loc_mem = memset--;
		sstm.str(std::string());
		map_vars[var->nombre] = var;
	}
	pilaO.push(var);
}

/**
* Crea una variable para las constantes booleanas
**/
void creaConstanteBool(int a) {
	//std::cout << "CreaConstanteBool" << std::endl;
	Node *var = new Node();
	int memset = memoriaAUsar(2, "constante");
	std::stringstream sstm;
	std::string aux;

	MapType::iterator it = map_vars.find("cB1");
	MapType::iterator it2 = map_vars.find("cB0");
	if(!a) aux = "cB0";
	else aux = "cB1";

	if(it == map_vars.end() && it2 == map_vars.end()) {

		var->nombre = aux;
		var->tipo = 2;
		var->scope = "constante";
		var->valor_num = a;
		var->id = id_actual++;
		var->loc_mem = memset;
		sstm.str(std::string());
		map_vars[var->nombre] = var;
		//std::cout << var->nombre << "\t\tmem: " << var->loc_mem << std::endl;
	} else {
		var = it->second;
		var->loc_mem = memset--;
		map_vars[var->nombre] = var;
	}
	pilaO.push(var);

}

void creaConstanteStr(const char *){

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
* Actualiza el tipo de las variables que han sido declaradas
**/
void actualizaTipoVariables () {
	//std::cout << "ActualizaTipoVariables" << std::endl;
	int tipo = -1;
	int memset = 0;
	std::string aux;
	const char  *llave;
	Node *var = new Node();

	tipo = convierteTipo(tipo_actual);

	if (tipo<0) std::cout << std::endl << " E R R O R " << std::endl;

	while (!aux_vars.empty()) {
		var = aux_vars.top();
		memset = memoriaAUsar(tipo, var->scope);
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
* Inicializa una variable con la informacion disponible
**/
void creaVariable() {
	//std::cout << "CreaVariable" << std::endl;
	Node *var = new Node();
	var->nombre = var_actual.top();
	var->tipo = -1;
	var->loc_mem = 999999;
	var->scope = scope_actual;
	var->id = id_actual++;
	var->valor_num = 0;
	var_actual.pop();
	aux_vars.push(var);

	//std::cout << "nombre: " << var->nombre << "\t scope: " << scope_actual
	//<< std::endl;

}

/**
* Crea la variable de retorno de las funciones
**/
void creaVarFunc(std::string str, int tipo){
	//std::cout << "creaVarFunc" << std::endl;
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
	var = pilaO.top();
	var->tipo = tipo;
	tmp_actual++;
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
		std::cout << "Nombre: " << var->nombre <<
			" Scope: " << var->scope <<
			" Mem: " << var->loc_mem << std::endl;
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
}

/**
* Vuelve a sus valores por default a los contadores de memoria
**/
void limpiaContMemoria(){
	mem_num_local = 3000;
	mem_bool_local = 10000;

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

	limpiaContMemoria();

	mem_num_global = 999;
	mem_num_constante = 7000;
	mem_bool_constante = 11000;
	mem_bool_global = 9000;

	id_actual = 1;
	cuad_actual = 1;
	tmp_actual = 1;
	param_count = 0;
	sumar = 0;

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
