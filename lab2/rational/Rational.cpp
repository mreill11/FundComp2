/* Matt Reilly
 * rational.cpp, cse20212
 * 
 * Rational class.
 * Contains constructor, copy constructor, operator overloaders, and other methods.
 */

#include <iostream>
#include "Rational.h"

using namespace std;

// Constructor
Rational::Rational(int n, int d) {
    num = n;
    if (d == 0) { // make sure denom isn't 0
        cout << "Can't divide by 0! Switching to 1." << endl;
        den = 1;
    } else {
        den = d;
    }
    (*this).reduce(); // reduce!
}

// copy constructor
Rational::Rational(const Rational & rationalToCopy) {
    num = rationalToCopy.num;
    if (rationalToCopy.den == 0) {
        cout << "Can't divide by 0! Switching to 1." << endl;
        den = 1;
    } else {
        den = rationalToCopy.den;
    }
}

// overload << operator
// prints object as fraction
ostream& operator<<(ostream & output, const Rational & myRational) {
    if (myRational.den == 1) { // don't display x/1, just x
        output << myRational.num;
    } else {
        output << myRational.num << "/" << myRational.den;
    }
}

// Handles the addition of rational numbers
// Overloads +
Rational Rational::operator+(const Rational & rationalToAdd) {
    Rational sum;
    
	// find common denominator
    int commonDen = lcm(den, rationalToAdd.den);
    int multiplier1 = commonDen / den;
    int multiplier2 = commonDen / rationalToAdd.den;
    
	// complete algorithm to add rationals
    sum.num = (num * multiplier1) + (rationalToAdd.num * multiplier2);
    sum.den = commonDen;
    sum.reduce();
    return sum;
}

// Handles subtraction of rationals
// overloads -
Rational Rational::operator-(const Rational & rationalToSubtract) {
	// Same process as + overloader, just subtraction instead
    Rational difference;
    int commonDen = lcm(den, rationalToSubtract.den);
    int multiplier1 = commonDen / den;
    int multiplier2 = commonDen / rationalToSubtract.den;
    difference.num = (num * multiplier1) - (rationalToSubtract.num * multiplier2);
    difference.den = commonDen;
    difference.reduce();
    return difference;
}

// Handles multiplication of rationals
// Overloads *
Rational Rational::operator*(const Rational & rationalToMultiply) {
    Rational product;
    product.num = num * rationalToMultiply.num;
    product.den = den * rationalToMultiply.den;
    product.reduce();
    return product;
}

// Handles division of rationals
// Overloads /
Rational Rational::operator/(const Rational & rationalDivisor) {
    Rational quotient;
    Rational inv;
    // NEVER DIVIDE BY 0
    if(rationalDivisor.num == 0) {
        cout << "Divide by 0 error. Divison operation not possible." << endl;
        quotient.num = 0;
        quotient.den = 1;
    } else {
        inv.num = rationalDivisor.den;
        inv.den = rationalDivisor.num;
        quotient = *this * inv;
    }
    quotient.reduce();
    return quotient;
}

// Handles greater than comparison
// Overloads >
bool Rational::operator>(const Rational & rationalToCompare) {
    if(((double) num / den) > ((double) rationalToCompare.num / rationalToCompare.den))
        return true;
    else
        return false;
}

// Handles less than comparison
// Overloads <
bool Rational::operator<(const Rational & rationalToCompare) {
    if(((double) num / den) < ((double) rationalToCompare.num / rationalToCompare.den))
        return true;
    else
        return false;
}

// Reduce fractions to make them easier to work with
void Rational::reduce() {
    // simple reduction algorithm
    int gcdRational = gcd(num, den);
    num /= gcdRational;
    den /= gcdRational;
    if(den < 0) {
        den*= -1;
        num*= -1;
    }
}

// return the least common multiple
int Rational::lcm(int n1, int n2) {
    return (n1 * n2) / gcd(n1, n2);
}

// return the greatest common denominator
int Rational::gcd(int x, int y) {
    int r;
    while(1) {
        r = x % y;
        if(r == 0) return y;
        else {
            x = y;
            y = r;
        }
    }
}

