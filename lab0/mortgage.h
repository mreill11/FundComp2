/* Matt Reilly
 * mortgage.h, cse20212
 *
 * This is the .h file for mortgage.cpp.
 * It lists all public and private methods,
 * as well as private variables.
 */

#include <iostream>

class Mortgage {

	public:
		Mortgage(double = 150000, double = 4.0, double = 600);
		void credit(double);
		double getPrincipal();
		void amortize();

	private:
		void printHeader();
		double principal;
		double rate;
		double payment;
		double interest;
		int month;
};
