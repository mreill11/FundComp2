#ifndef PUZZLE_H
#define PUZZLE_H

/* Matt Reilly 
 * 
 * Puzzle.h, cse20212 
 * Puzzle class using templating
 * STL Singleton!!!
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

template <typename T>
class Puzzle {
	public:
		Puzzle(int size = 9);	// constructor with default size = 9
		void solve(); 			// solve puzzle
		void display();			// display puzzle

	private:
		void displayRowDashes();						// display a row of dashes to format the puzzle
		bool isValidRow(int row, T val);				// return true if row placement is valid
		bool isValidCol(int col, T val); 				// return true if col placement is valid
		bool isValidMiniGrid(int row, int col, T val);	// return true if minigrid placement is valid
		int countRemainingSpaces();						// number of remaining spaces. if == 0, player has won

		// solve() needs helper functions:
		void getPossibleVals(int row, int col); 		// get possible vals for arg, update pVals
		void getValue(int row, int col); 				// figure out value of cell
		int getSumPosVals(int row, int col); 			// return sum of pVals
		void markAsKnown(int row, int col, int val); 	// update pVals because cell as known
		void scanSingletons(int row, int col); 			// scan all singletons to determine values

		vector<vector <vector <int> > > pVals; 			//3D vector that stores posisble values

		/*
		 *vector<vector <T> > originalPuzzle;			// original puzzle as specified by the input file
		 *vector<vector <T> > puzzle;					// 2D vector to store puzzle data
		 */

		int boardSize;									// size/length of each side of the board

		// instance vars to avoid hardcoding possibility of values
		int NP; 										// Value is not possible, NP = 0
		int P; 											// Value is possible, P = 1
		int K; 											// Value is known, K = 1
		int UK; 										// Value is unknown, UK = 0;
};

#endif

// Constructor
// Set boardsize, get filename, build vector
template <typename T>
Puzzle<T>::Puzzle(int size) {
	// Initialize instance variables
	P = 1;
	NP = 0;
	K = 1;
	UK = 0;

	// Initialize other variables
	boardSize = size;			// set boardsize
	string input;				// c_str() filename
	T piece;					// store next piece
	ifstream inFile;			// input file
	vector<vector <T> > puzzle;  // 2D vector to store puzzle data

	// get input file and validate
	while(1) {
		cout << "Enter a valid file name for the puzzle data: ";
		cin >> input;
	
		inFile.open(input.c_str(), ios::in);
		if(inFile.good()) break;			// valid file name 
		else cout << input << " does not exist. Please try again." << endl;
	}

	// build puzzle
	while(!inFile.eof()) {

		vector<T> row;							// add one row at a time
		for(int i = 0; i < boardSize; i++) {	// create 1 vector per row
			inFile >> piece;		// store next puzzle piece
			row.push_back(piece);	// add piece to row
		}
		
		// add each row to the original 2-D puzzle board and the ongoing puzzle board
		// originalPuzzle.push_back(row);
		puzzle.push_back(row);
	}

	// Now we must build a 3D vector to track all possible solutions
	

	// Create a vector boardSize + 1 with a 0 and boardSize 1's
	vector<int> binaryVals; 		// initialize vector
	binaryVals.push_back(0); 		// binaryVals[0] is not solved
	// fill the rest with 1
	for (int i = 0; i < boardSize; i++) 
		binaryVals.push_back(1);

	// Building second dimension, vector of vector of ints
	vector<vector <int> > twoDim;
	for (int i = 0; i < boardSize; i++)
		twoDim.push_back(binaryVals);

	// Creating 3D pVals
	for (int i = 0; i < boardSize; i++)
		pVals.push_back(twoDim);

	// Now we must fill in the known values from the original puzzle
	// We will also mark that cell as known
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (puzzle[i][j] != UK) {
				// if piece has value, update pVals
				markAsKnown(i, j, puzzle[i][j]);
			}
		}
	}
}

// Solve the puzzle!
// Each cell is treated as a bit vector
template <typename T>
void Puzzle<T>::solve() {
	while(countRemainingSpaces() != 0) {
		// puzzle is not empty
		// iterate through, checking for unknown pieces
		// update pVals, solve puzzle from there

		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (pVals[i][j][0] == UK) {
					// cell is unknown
					getPossibleVals(i, j); 		// update pVals vector
					getValue(i, j); 			// attempt to solve for piece
					scanSingletons(i, j); 		// try to solve with singleton method
				}
			}
		}
	}
}

// Search for singletons in every row, column, and minigrid.
// This was hard
template <typename T>
void Puzzle<T>::scanSingletons(int row, int col) {
	int numOccur = 0; 			// number of times val is possible in r/c/mini grid
	int singletonR; 			// stores row of potential singleton
	int singletonC; 			// stores col of potential singleton

	// For every valid value (This is a big loop)
	for (int val = 1; val <= boardSize; val++) {

	// ROW SINGLETONS
	// --------------
		for (int i = 0; i < boardSize; i++) {
			// cell unknown, val possible
			if (pVals[row][i][0] == UK && pVals[row][i][val] == P) {
				numOccur++;  		// val is possible here
				
				// store possible singleton's location
				if (numOccur == 1) {
					singletonR = row;
					singletonC = i;
				}
			}
		}

		// is value a singleton?? Let's find out.
		if (numOccur == 1 && isValidRow(singletonR, val) && isValidCol(singletonC, val)
				&& isValidMiniGrid(singletonR, singletonC, val)) {
			// update pVals
			markAsKnown(singletonR, singletonC, val);
		}

		numOccur = 0; 		// reset

	// COL SINGLETONS
	// --------------	
		for (int i = 0; i < boardSize; i++) {
			// cell unknown, val possible
			if (pVals[i][col][0] == UK && pVals[row][col][val] == P) {
				numOccur++;  		// val is possible here
				
				// store possible singleton's location
				if (numOccur == 1) {
					singletonR = i;
					singletonC = col;
				}
			}
		}

		// is value a singleton?? Let's find out.
		if (numOccur == 1 && isValidRow(singletonR, val) && isValidCol(singletonC, val)
				&& isValidMiniGrid(singletonR, singletonC, val)) {
			// update pVals
			markAsKnown(singletonR, singletonC, val);
		}

		numOccur = 0; 		// reset

	// MINI GRID SINGLETONS
	// -------------------
		int sqrtBS = sqrt(boardSize); 		// dimension of mini grid
		
		for (int i = 0; i < sqrtBS; i++) {
			for (int j = 0; j < sqrtBS; j++) {
				// cell unknown, val possible
				if (pVals[i][j][0] == UK && pVals[i][j][val] == P) {
					numOccur++;  		// val is possible here
				
					// store possible singleton's location
					if (numOccur == 1) {
						singletonR = i;
						singletonC = j;
					}
				}
			}
		}

		// is value a singleton?? Let's find out.
		if (numOccur == 1 && isValidRow(singletonR, val) && isValidCol(singletonC, val)
				&& isValidMiniGrid(singletonR, singletonC, val)) {
			// update pVals
			markAsKnown(singletonR, singletonC, val);
		}
		// numOccur = 0 ???
	}
}

// Mark cell as known by updating pVals
template <typename T>
void Puzzle<T>::markAsKnown(int row, int col, int val) {
	pVals[row][col][0] == val; 		// first index should be val

	// set all other indicies to 0
	for (int i = 1; i <= boardSize; i++) {
		if (i != val)
			pVals[row][col][i] = NP;
	}
}

// Find possible values for cell, update pVals
template <typename T>
void Puzzle<T>::getPossibleVals(int row, int col) {
	for (int val = 1; val <= boardSize; val++) {
		// if val makes everything valid, update pVals
		if (isValidRow(row, val) && isValidCol(col, val) && isValidMiniGrid(row, col, val)) {
			pVals[row][col][val] = P;
		} else {
			pVals[row][col][val] = NP;
		}
	}
}

// Attempt to find the value for the cell
template <typename T>
void Puzzle<T>::getValue(int row, int col) {
	if (getSumPosVals(row, col) == 1) 	// if sum = 1, there is only one possible value
		for (int i = 1; i <= boardSize; i++) {
			if (pVals[row][col][i] == P) {
				markAsKnown(row, col, i);
			}
		}
}

// Returns sum of indicies 1-9 int 3rd dim of pVals
template <typename T>
int Puzzle<T>::getSumPosVals(int row, int col) {
	int sum = 0;

	for (int i = 1; i <= boardSize; i++)
		sum += pVals[row][col][i];

	return sum;
}

// Check if valid for row
template <typename T>
bool Puzzle<T>::isValidRow(int row, T val) {
	if((int)val == UK)
		return true;		// there can be multiple 0's (blanks)

	// make sure input isn't in row
	for(int i = 0; i < boardSize; i++) {
		if(pVals[row][i][0] == val) {
			return false;
		}
	}
	return true;			// Works!
}

// Check if valid column
template <typename T>
bool Puzzle<T>::isValidCol(int col, T val) {
	if((int)val == UK)
		return true;		// there can be multiple 0's (blanks)

	for(int i = 0; i < boardSize; i++) {
		if(pVals[i][col][0] == val) {
			return false;
		}
	}
	return true;		// Works!
}

// Loop through mini grid to make sure value is valid
template <typename T>
bool Puzzle<T>::isValidMiniGrid(int row, int col, T val) {
	if((int)val == UK)
		return true;		// there can be multiple 0's (blanks)
	int sqrtBS = sqrt(boardSize);
	int topLeftX = row / sqrtBS * sqrtBS;		
	int topLeftY = col / sqrtBS * sqrtBS;	

	// now that the top-left corner of the minigrid is known, check entire square
	for(int i = 0; i < sqrtBS; i++) {
		for(int j = 0; j < sqrtBS; j++) {
			if(pVals[topLeftX + i][topLeftY + j][0] == val) {
				return false;
			}
		}
	}
	return true;		// Works!
}

// Check for empty spaces
template <typename T>
int Puzzle<T>::countRemainingSpaces() {
	int nRemaining = 0;

	// count all 0's (empty spaces) on board
	for(int i = 0; i < boardSize; i++) {
		for(int j = 0; j < boardSize; j++) {
			if((int)pVals[i][j][0] == NP) {
				nRemaining++;
			}
		}
	}
	return nRemaining;
}
	

// Display
template <typename T>
void Puzzle<T>::display() {
	
	for(int i = 0; i < boardSize; i++) {	// rows
		if(i % (int)sqrt(boardSize) == 0) {
			displayRowDashes();
		}

		// display each piece in the row
		for(int j = 0; j < boardSize; j++) {	
			if(j % (int)sqrt(boardSize) == 0)
				cout << "| ";	// |'s every sqrt(boardSize) cols, start at left
			if((int)pVals[i][j][0] == UK) {		// if puzzle value is a 0, display a blank space instead
				cout << "  ";					
			} else {
				cout << pVals[i][j][0] << " ";	
			}
		}
		cout << "|" << endl;	// add right boarder and a newline after each row is displayed
	}
	displayRowDashes();		// bottom boarder of puzzle
}

// Display dashes
template <typename T>
void Puzzle<T>::displayRowDashes() {
	int nExtras = sqrt(boardSize);	// beginning of board + each in-between vertical section
	for(int a = 0; a < boardSize + nExtras; a++) {
		cout << " -";		// display a row of dashes
	}
	cout << endl;			// newline
}


