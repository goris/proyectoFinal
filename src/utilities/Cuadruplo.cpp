#include "Cuadruplo.h"
#include <iostream>
#include <sstream>


Cuadruplo::Cuadruplo (void) {
	ope = -1;
	ope1 = -1;
	ope2 = -1;
	avail = -1;
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

Cuadruplo::Cuadruplo(int oper, int op1, int op2, std::string res) {
		ope = oper;
		ope1 = op1;
		ope2 = op2;
		avail_s = res;
}


void Cuadruplo::setAvail_s(std::string str){
		avail_s = str;
}

void Cuadruplo::print (){
//	std::cout << "Cuadruplo: "<< ope << ", " << ope1 << ", " <<
//				 	ope2 << ", " << avail << std::endl; 
	std::string str1;
	std::string str2;
	std::string str3;
	std::string str4;
	std::stringstream sstm;

	if (ope1 == -1) ope1 = 0;
	
	sstm << "" << ope;
	str1 = sstm.str();
	sstm.str(std::string());

	if (ope1 == 0) sstm << "" << ope1_s;
	else if(ope1_s != "") sstm << "" <<ope1_s;
	else  sstm << "" << ope1;
	str2 = sstm.str();
	sstm.str(std::string());
	
	if (ope2_s == "w" || ope2 == -1) sstm << "";
	else sstm << "" << ope2;
	str3 = sstm.str();
	sstm.str(std::string());
	
	if(avail_s != "") sstm << "" << avail_s;
	else sstm << "" << avail;
	str4 = sstm.str();
	sstm.str(std::string());

	std::cout << "Cuadruplo: "<< str1 << " \t " << str2 << " \t " <<
				 	str3 << " \t " << str4 << std::endl; 

}

std::string Cuadruplo::cuadruploStr() {
	std::string str1;
	std::string str2;
	std::string str3;
	std::string str4;
	std::stringstream sstm;
	std::string str;

	if (ope1 == -1) ope1 = 0;
	
	sstm << "" << ope;
	str1 = sstm.str();
	sstm.str(std::string());

	if (ope1 == 0) sstm << "" << ope1_s;
	else if(ope1_s != "") sstm << "" <<ope1_s;
	else  sstm << "" << ope1;
	str2 = sstm.str();
	sstm.str(std::string());
	
	if (ope2_s == "w" || ope2 == -1) sstm << "";
	else sstm << "" << ope2;
	str3 = sstm.str();
	sstm.str(std::string());
	
	if(avail_s != "") sstm << "" << avail_s;
	else sstm << "" << avail;
	str4 = sstm.str();
	sstm.str(std::string());

	sstm << str1 << ", " << str2 << ", " <<
				 	str3 << ", " << str4 << std::endl; 
	str = sstm.str();
	return str;
}


