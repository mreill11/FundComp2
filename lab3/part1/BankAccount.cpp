/* Matt Reilly
 *
 * BankAccount.cpp, cse20212
 * BankAccount class
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "BankAccount.h"

using namespace std;

// Constructor for a Bank Account
BankAccount:BankAccount() {
	srand(time(NULL)); 	// setup rand generator
	char nums[] = "0123456789"; 	// all possible digits
	int acctNumLen = 9; 	// number of digits in an account #
	for (int i = 0; i < acctNumLen; i++) 
		accountNumber.push_back(numbers[rand() % 10]); 	// generate random acct number
}

// print
void BankAccount::print() {
	// print Bank Account
}

// make a deposit
void BankAccount::deposit(double) {
	// deposit
}

// Reset PIN for this account
void BankAccount::resetPin() {
	cout << "Please enter a new PIN: ";
	cin >> pin;
}

// Return acct #
string BankAccount::getAccountNumber() {
	return accountNumber;
}

// Set the name of the account holder
void BankAccount::setAccountHolder(string name) {
	acountHolder = name;
}

// Return account holder
string BankAccount::getAccountHolder() {
	return accountHolder;
}
