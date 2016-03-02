#include <iostream>
#include "C4Col.h"
using namespace std;

// default constructor, intialize variables
C4Col::C4Col() {
	numDiscs = 0;
	maxDiscs = 6;
	discs = new char[maxDiscs];			// dynamic memory allocation
	for(int i = 0; i < maxDiscs; i++) {	// initialize col spaces to be blank
		discs[i] = ' ';
	}
}

// the deconstructor frees up memory
C4Col::~C4Col() {			
	delete [] discs;		
}

C4Col::C4Col(const C4Col & C4ColToCopy) {
    numDiscs = C4ColToCopy.numDiscs;
    maxDiscs = C4ColToCopy.maxDiscs;
    discs = new char[maxDiscs];
    for(int i = 0; i < maxDiscs; i++) {
        discs[i] = C4ColToCopy.discs[i];
    }

}

// return 1 if full, 0 if not full
int C4Col::isFull() {
	if(numDiscs == maxDiscs) // is it full?
		return 1;
	else 
		return 0;
}

// returns piece in specified row
char C4Col::getDisc(int row) {
	if(row < 0 || row > maxDiscs) {		// validate input
		cout << "Row " << row << " is invalid." << endl;	
		return ' '; // return blank because of invalid input
	}
	return discs[row]; // input is valid, return discs[row]
}

// returns the max num discs for a column
int C4Col::getMaxDiscs() {
	return maxDiscs;
}

// returns the num discs in column
int C4Col::getNumDiscs() {
	return numDiscs;
}

// adds a disc to this column after checking if column is filled
void C4Col::addDisc(char newDisc) {
	if(isFull() == 1) {
		cout << "No room. Try a different column." << endl;	
		return;
	}
	discs[numDiscs++] = newDisc; // numDiscs++ and add disc to discs[]
}

C4Col C4Col::operator+=(char newDisc) {
    addDisc(newDisc);
    return(*this);			// return the changed column
}
