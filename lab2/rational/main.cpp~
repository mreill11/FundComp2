/* Luke Garrison, main.cpp
 *
 * This program serves as a driver for the Rational class
 * It creates an "Interactive Mode" for the user, who is able to set the value for 
 * the mass and velocity that will be used to calculate Kinetic Energy
 * This program exhibits that the Rational class can correctly perform operations and be
 * displayed via cout. 
 */

#include <iostream>
#include "Rational.h"
using namespace std;

int main() {
	int mNum, mDen, vNum, vDen;		// initialze variables to store two rationals for mass and velocity
	
	// collect user input to create Rational objects	
	cout << "Enter numerator for mass: ";
	cin >> mNum;
	cout << "Enter denominator for mass: ";
	cin >> mDen;
	cout << "Enter numerator for velocity: ";
	cin >> vNum;
	cout << "Enter denominator for velocity: ";
	cin >> vDen;
	Rational m(mNum, mDen);		// create rationals
	Rational v(vNum, vDen);
	Rational half(1, 2);		// rational for 1/2
	
	// display summary of operations to the user
	if(m > v) {		// compare the value of mass and velocity. display relationship
		cout << mNum << "/" << mDen << " > " << vNum << "/" << vDen << endl;
	} else {		// if m !> v, then m <= v
		cout << mNum << "/" << mDen << " <= " << vNum << "/" << vDen << endl;
	}	
	cout << mNum << "/" << mDen << " + " << vNum << "/" << vDen << " = " << m + v << endl;
	cout << mNum << "/" << mDen << " - " << vNum << "/" << vDen << " = " << m - v << endl;
	cout << mNum << "/" << mDen << " * " << vNum << "/" << vDen << " = " << m * v << endl;
	cout << mNum << "/" << mDen << " / " << vNum << "/" << vDen << " - 1/2 " << " = " << m / v - half << endl;
	cout << "Kinetic Energy (K) = " << ".5*m*v^2 = 1/2 * " << mNum << "/" << mDen << " * " // display KE eqn
		 << vNum << "/" << vDen << " * " << vNum << "/" << vDen << " = " << half*m*v*v 
		 << " J" << endl;	// J = Joules = unit

	return 0;
}
