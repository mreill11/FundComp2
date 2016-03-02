#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

/* Matt Reilly
 * 
 * BankAccount.h, cse20212
 * Header file for abstract BankAccount class
 */

 #include <string>

 using namespace std;

 class BankAccount {
 	public:
		BankAccount();
		virtual void print() = 0; 	// virtual print function to display acct info
		virtual void deposit(double) = 0; 	// make a deposit
		void resetPin(); 	// reset acct pin
		string getAccountNumber(); // return acct #
		void setAccountHolder(); // set holder name
		string getAccountHolder(); // get holder name

	private:
		string accountNumber; 	// acct #
		string accountHolder; 	// name of acct holder
		int pin; 				// acct pin
};

#endif
