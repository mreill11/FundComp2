/* Matt Reilly
 * C4Col.cpp, cse20212
 *
 * This is the implementation of the C4Col class.
 */

#include <iostream>
#include "C4Col.h"

using namespace std;

//Default constructor
C4Col::C4Col() {
	nDiscs = 0;
	maxDiscs = 6;
	discs = new char[maxDiscs];
	for (int i = 0; i < maxDiscs; i++)
		discs[i] = ' ';
}

int C4Col::isFull() {
	if (nDiscs == maxDiscs)
		return 1;	
	return 0;
}

char C4Col::getDisc(int row) {
	if (row < 0 || row > maxDiscs) {
		cout << "Row " << row << " is invalid" << endl;
		return ' ';
	}
	return discs[row];
}

int C4Col::getMaxDiscs() {
	return maxDiscs;
}

int C4Col::getNumDiscs() {
	return nDiscs;
}

void C4Col::addDisc(char newDisc) {
	if (isFull() == 1)
		cout << "This column is full. Please try another one." << endl;
	discs[nDiscs++] = newDisc;
}
