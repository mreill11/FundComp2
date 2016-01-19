/* pi.cpp
 * Matt Reilly, cse20212
 *
 * My program estimates pi using a user-input number of terms.
 * It then displays the approximated value, starting with one term,
 * until it reaches the specified number of terms.
 */

#include <iostream>
#include <cmath> 	
#include <iomanip> 	//Contains an easy to use round function setprecision()

using namespace std;

int main() {
	int num; 	//number of terms
	double pi = 0;

	//By looping over 1, the program is able to wait for valid input
	while (1) {
		cout << "Please enter the number of terms in the series: ";
		cin >> num;
		if (num < 2) //invalid input
			cout << "Error! Provided value must be >= 2!" << endl;
		else 	//valid input
			break;
	}

	for (int i = 1; i <= num; i++) {
		pi += (4. / (2 * i - 1)) * pow(-1, i + 1); //the brains of the operation
		cout << fixed << setprecision(3) << "Estimate after " << i << " term(s): " << pi << endl;
		//fixed makes the number of decimals constant
	}

	return 0;
}
