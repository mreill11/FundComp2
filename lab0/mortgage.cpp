/* Matt Reilly
 * mortgage.cpp, cse20212
 *
 * This is the implementation file for the Mortgage class.
 */

#include <iostream>
#include <iomanip>
#include "mortgage.h"

using namespace std;

//Handle and validate input with this constructor
Mortgage::Mortgage (double inputPrincipal, double inputRate, double inputPayment) {
	//initialize private variables to args
	principal = inputPrincipal;
	rate = inputRate;
	payment = inputPayment;

	//check args, adjusts values if there is an error
	while (principal <= 0) {
		cout << "Please enter a rate >= $0: ";
		cin >> principal;
	}

	while (rate < 0) {
		cout << "Please enter a rate >= $0: ";
		cin >> rate;
	}

	rate /= (100 * 12); //convert rate to monthly rate

	while (payment <= 0) {
		cout << "Please enter a payment > $0: ";
		cin >> payment;
	}

	while (principal * rate >= payment) {
		//making sure payment is sufficient
		cout << "This mortgage cannot be paid off with the selected payment" << endl;
		cout << fixed << setprecision(2) << "Please enter a payment greater than $" << principal * rate << ": ";
		cin >> payment;
	}
}

//credit method credits users mortgage the specified amount
void Mortgage::credit (double payment) {
	principal -= payment;
}

//simply returns principal
double Mortgage::getPrincipal() {
	return principal;
}

//The main method, handles the amortization
void Mortgage::amortize() {
	month = 1;
	cout << endl;
	cout << left << setw(7) << "Month" << setw(11) << "Payment" <<
		setw(11) << "Interest" << setw(8) << "Balance" << endl;
	//same process as FC1 amortization
	while (principal > .001) {
		interest = principal * rate;
		principal += interest;
		if (principal < payment)
			payment = principal;
		principal -= payment;
		cout << left << setw(7) << fixed << setprecision(2) << month <<
			setw(11) << payment << setw(11) << interest <<
			setw(8) << principal << endl;
		month++;
	}
}
