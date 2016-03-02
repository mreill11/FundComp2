// Make sure all dependencies have been defined
#ifndef C4COL_H
#define C4COL_H

/* Matt Reilly
 * C4Col.h, cse20212
 *
 * Header file for C4Col class
 * I added getNumDiscs as a helper method because it made tracking the placement
 * of discs much easier.
 */

#include <iostream>

class C4Col {
	public:
		C4Col();			// default constructor
		~C4Col();			// deconstructor
		C4Col(const C4Col & C4ColToCopy); // copy constructor
		int isFull();		// Is column full?
		char getDisc(int);	// returns the requested element of the priate char array
		int getMaxDiscs(); 	// returns max num discs (6)
		int getNumDiscs();	// returns numDiscs, helper method I added
		void addDisc(char);	// adds a disc to the column
        	C4Col operator+=(char); // overload += for addDisc

	private:
		int numDiscs;		// num discs in column
		int maxDiscs;	// 6
		char* discs;	// char array to hold discs
};

#endif
