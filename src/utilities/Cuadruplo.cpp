#include "Cuadruplo.h"
#include <iostream>

Cuadruplo::Cuadruplo (void) {
	ope = 0;
	ope1 = 0;
	ope2 = 0;
	avail =0;
	ope1_s = "";
	ope2_s = "";
	avail_s = "";

}


Cuadruplo::Cuadruplo(int oper, int op1, int op2, int res) {

				ope = oper;
				ope1 = op1;
				ope2 = op2;
				avail = res;
}

Cuadruplo::Cuadruplo(int oper, std::string op1, std::string op2,
							 		std::string res) {

				ope = oper;
				ope1_s = op1;
				ope2_s = op2;
				avail_s = res;

}

void Cuadruplo::print (){
//	std::cout << "Cuadruplo: "<< ope << ", " << ope1 << ", " <<
//				 	ope2 << ", " << avail << std::endl; 
	std::cout << "Cuadruplo: "<< ope << ", " << ope1_s << ", " <<
				 	ope2_s << ", " << avail_s << std::endl; 

}


