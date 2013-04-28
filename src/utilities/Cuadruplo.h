#include <iostream>

class Cuadruplo {
		

	public:
		int ope;
		int ope1;
		int ope2;
		int avail;
		std::string ope1_s;
		std::string ope2_s;
		std::string avail_s;
	
		Cuadruplo (); 
		Cuadruplo(int, std::string, std::string, std::string);
		Cuadruplo(int, int, int, std::string);
		Cuadruplo(int, int, int, int);

		void setAvail_s(std::string);
		void print();
		std::string cuadruploStr();

};
