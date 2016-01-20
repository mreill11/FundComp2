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
		Mortgage(double = 300000, double = 3.0, double = 800);
		void credit(double);
		double getPrincipal();
		void amortize();

	private:
		double principal;
		double rate;
		double payment;
		double interest;
		int month;
};
