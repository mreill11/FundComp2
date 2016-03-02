#ifndef C4BOARD_H
#define C4BOARD_H

/* Matt Reilly
 * C4Board.h
 * 
 * This is the header file for the Board class.
 * I included some helper functions.
 */

#include <iostream>
#include "C4Col.h"
using namespace std;

class C4Board {
	public: 
		C4Board();				// default constructor
		~C4Board();				// deconstructor
		C4Board(const C4Board & C4BoardToCopy); // copy constructor
		void display();			// display the board
		void play(); 			// Two player game
        	friend ostream &operator<<(ostream &, const C4Board &); //overload <<
		

	private:
		int gameWon(char, int, int);	// helper method that figures out if the game has been won.
							// return values: 1 = p1 won, 2 = p2 won, 0 = neither player has won
		void getColumn();	// helper function to get valid col selection from user for turn

		int numToWin;	 	// initialized to 4 for connect4		
		char p1;		// will be set to 'X' in constructor
		char p2;		// will be set to 'O' in constructor
		int turn;			// keeps track of turn number - ie whose turn it is
		int numCols;    		// number of columns on board
		int nFullCol;		// number of columns that are full. check when nFullCol == nCol
		int inputCol; 		// user's choice of column
		C4Col* board;		// array of C4Col columns that will comprise the board
};

#endif	
