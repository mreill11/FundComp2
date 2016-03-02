/* Matt Reilly
 * main.cpp
 *
 * This program serves as a driver for the Rational class
 * It both creates an interactive mode where the user can calculate final velocity by providing inputs,
 * and it proves that all of the operator overloading is working.
 */

#include <iostream>
#include "Rational.h"
using namespace std;

int main() {
	int v0Num, v0Den, tNum, tDen;		// initialze variables to store two rationals for mass and velocity
	
	// collect user input to create Rational objects	
	cout << "Enter numerator for initial velocity: ";
	cin >> v0Num;
	cout << "Enter denominator for initial velocity: ";
	cin >> v0Den;
	cout << "Enter numerator for time: ";
	cin >> tNum;
	cout << "Enter denominator for time: ";
	cin >> tDen;
	Rational v0(v0Num, v0Den);		// initial velocity rational
	Rational t(tNum, tDen); 		// time rational
	Rational a(98, 10);		// rational for acceleration
	
	// display summary of operations to the user
	if(v0 > t) {		// compare the value of time and velocity
		cout << v0Num << "/" << v0Den << " > " << tNum << "/" << tDen << endl;
	} else {		// if m !> v, then m <= v
		cout << v0Num << "/" << v0Den << " <= " << tNum << "/" << tDen << endl;
	}	
	cout << v0Num << "/" << v0Den << " + " << tNum << "/" << tDen << "*" << a << " = " << v0 + a*t << endl;
	cout << v0Num << "/" << v0Den << " - " << tNum << "/" << tDen << "*" << a << " = " << v0 - a*t << endl;
	cout << v0Num << "/" << v0Den << " * " << tNum << "/" << tDen << "*" << a << " = " << v0 * a * t << endl;
	cout << "Final velocity (m/s) = " << "v0 + a*t = " << v0Num << "/" << v0Den << " + " << tNum << "/" << tDen << " * " << a << " = " << v0 + a*t << " (m/s)" << endl;	// m/s = units

	return 0;
}
