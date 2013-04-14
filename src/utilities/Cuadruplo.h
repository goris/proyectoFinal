#include <iostream>

class Cuadruplo {
		
		int ope;
		int ope1;
		int ope2;
		int avail;
		std::string ope1_s;
		std::string ope2_s;
		std::string avail_s;

	public:
	
		Cuadruplo (); 
		Cuadruplo(int, int, int, int);
		Cuadruplo(int, std::string, std::string, std::string);

		void print();

};
