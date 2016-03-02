#ifndef RATIONAL_H
#define RATIONAL_H

/* Matt Reilly
 * Rational.h
 * Header file for rational class
 */

#include <iostream>
using namespace std;

class Rational {
	
	public:
		Rational(int num = 1, int den = 1); // default constructor
		Rational(const Rational & rationalToCopy); // copy constructor
		friend ostream& operator<<(ostream &, const Rational &);	// overload << operator		
		Rational operator+(const Rational & rationalToAdd);	// overload + operator
		Rational operator-(const Rational & rationalToSubtract);// overload - operator	
		Rational operator*(const Rational & rationalToMultiply);// overload * operator
		Rational operator/(const Rational & rationalDivisor); 	// overload / operator
		bool operator>(const Rational & rationalToCompare);		// overload > operator
		bool operator<(const Rational & rationalToCompare);		// overload < operator

	private: 
		int lcm(int n1, int n2);	// find lcm
		int gcd(int x, int y);		// find gcd
		void reduce();		// reduce raational

		int num;		// numerator
		int den;		// denominator
};

#endif
