#ifndef RATIONAL_H
#define RATIONAL_H

/* Luke Garrison, Rational.h
 * Interface for rational class
 */

#include <iostream>
using namespace std;

class Rational {
	
	public:
		Rational(int num = 1, int den = 1); // default constructor with fallback values
		Rational(const Rational & rationalToCopy); // copy constructor
		friend ostream& operator<<(ostream &, const Rational &);	// overload << operator to display rational		
		Rational operator+(const Rational & rationalToAdd);	// overload + operator to add rationals
		Rational operator-(const Rational & rationalToSubtract);// overload - operator to subtract rational on right	
		Rational operator*(const Rational & rationalToMultiply);// overload * operator to multiply two rationals
		Rational operator/(const Rational & rationalDivisor); 	// overload / operator to divide two rationals
		bool operator>(const Rational & rationalToCompare);		// overload > operator to compare two rationals
		bool operator<(const Rational & rationalToCompare);		// overload < operator to compare two rationals

	private: 
		int lcm(int n1, int n2);	// find LCM of two numbers
		int gcd(int x, int y);		// find GCD of two numbers
		void reduce();		// simplify rational to reduced form

		int num;		// numerator of rational
		int den;		// denominator of rational
};

#endif
