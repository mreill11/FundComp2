#ifndef PUZZLE_H
#define PUZZLE_H

/* Matt Reilly 
 * 
 * Puzzle.h, cse20212 
 * Puzzle class using templating
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
		void play();			// play puzzle
		void display();			// display puzzle

	private:
		void displayRowDashes();						// display a row of dashes to format the puzzle
		bool isValidRow(int row, T val);				// return true if row placement is valid
		bool isValidCol(int col, T val); 				// return true if col placement is valid
		bool isValidMiniGrid(int row, int col, T val);	// return true if minigrid placement is valid
		int countRemainingSpaces();						// number of remaining spaces. if == 0, player has won

		vector<vector <T> > originalPuzzle;				// original puzzle as specified by the input file
		vector<vector <T> > puzzle;						// 2D vector to store puzzle data
		int boardSize;									// size/length of each side of the board
};

#endif

// Constructor
// Set boardsize, get filename, build vector
template <typename T>
Puzzle<T>::Puzzle(int size) {
	boardSize = size;			// set boardsize
	string input;				// c_str() filename
	T piece;					// store next piece
	ifstream inFile;			// input file

	// get input file
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
		originalPuzzle.push_back(row);
		puzzle.push_back(row);
	}

}

// The brains
template <typename T>
void Puzzle<T>::play() {

	display();

	int row, col;
	T val;					// new value to place in specified cell
	int sentinel = -1;		// sentinel value to trigger quit
	bool quit = false;		// flag to quit if user desires
	cout << "Enter " << sentinel << " at any time to quit, and use a value of 0 to erase the specified cell" << endl;
        while(!quit && countRemainingSpaces() != 0) {
		// get valid row
		while (!quit) {				
			cout << "   Row: ";
			cin >> row;
			if(row == sentinel)	quit = true;	// check if user wants to quit
			row--;								// allow user to input rows 1 - n, instead of 0 - (n-1)
			if (row >= 0 && row < boardSize || quit) break;	// valid entry
			cout << "Please enter a valid row" << endl;
		}
		
		// get valid col
		while (!quit) { 
			cout << "   Col: ";
			cin >> col;
			if(col == sentinel) quit = true;	// check if user wants to quit
			col--;								// allow user to input cols 1 - n, instead of 0 - (n-1)
			if(col >= 0 && col < boardSize || quit) break;	// valid entry
			cout << "Please enter a valid column" << endl;
		}

		// check if specified piece can be changed (was it an original piece, part of data file?)
		if(!quit && (int)originalPuzzle[row][col] != 0) {
			cout << "You cannot change this puzzle piece because it is from the original puzzle." << endl;
			continue;
		}

		// get valid value
		while(!quit) {
			cout << "   New value: ";
			cin >> val;
			if(val == sentinel) quit = true;				// check if user wants to quit
			if(val >= 0 && val <= boardSize || quit) break;	// valid entry
			cout << "Please enter a valid value between from 0-" << boardSize << " or the sentinel value." << endl;
		}

		if(quit) break;
		
		// check if puzzle is done
		if(!isValidRow(row, val)) continue;		// check if input is already there
		if(!isValidCol(col, val)) continue;		
		if(!isValidMiniGrid(row, col, val)) continue;	// check if entered value already exists in the mini-grid

		// at this point, location and value must be valid, so place the piece and redisplay board		
		puzzle[row][col] = val;
		display();
	}

	// check if player completed puzzle or not
	if(countRemainingSpaces() == 0) { // Winner winner, chicken dinner
		cout << "You successfully completed the puzzle! Congratulations! Try a harder one next!" << endl;
	} else {
		cout << "You have given up. Try again later!" << endl;
	}
}

// Check if valid for row
template <typename T>
bool Puzzle<T>::isValidRow(int row, T val) {
	if((int)val == 0) return true;		// there can be multiple 0's (blanks)

	// make sure input isn't in row
	for(int i = 0; i < boardSize; i++) {
		if(puzzle[row][i] == val) {
			cout << "Error: " << val << " already exists in row " << row + 1 << "." << endl;
			return false;
		}
	}
	return true;			// Works!
}

// Check if valid column
template <typename T>
bool Puzzle<T>::isValidCol(int col, T val) {
	if((int)val == 0) return true;		// there can be multiple 0's (blanks)

	for(int i = 0; i < boardSize; i++) {
		if(puzzle[i][col] == val) {
			cout << "Error: " << val << " already exists in column " << col + 1 << "." << endl;
			return false;
		}
	}
	return true;		// Works!
}

// Loop through mini grid to make sure value is valid
template <typename T>
bool Puzzle<T>::isValidMiniGrid(int row, int col, T val) {
	if((int)val == 0) return true;		// there can be multiple 0's (blanks)

	int topLeftX = row / 3 * 3;		
	int topLeftY = col / 3 * 3;	

	// now that the top-left corner of the minigrid is known, check entire square
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(puzzle[topLeftX + i][topLeftY + j] == val) {
				cout << "Error: " << val << " already exists in that mini-grid." << endl;
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
			if((int)puzzle[i][j] == 0) {
				nRemaining++;
			}
		}
	}
	return nRemaining;
}
	

// Display
template <typename T>
void Puzzle<T>::display() {
	system("clear");	// clear screen so puzzle is displayed at the top
	
	for(int i = 0; i < boardSize; i++) {	// rows
		if(i % (int)sqrt(boardSize) == 0) {
			displayRowDashes();
		}

		// display each piece in the row
		for(int j = 0; j < boardSize; j++) {	
			if(j % (int)sqrt(boardSize) == 0) cout << "| ";	// |'s every sqrt(boardSize) cols, start at left
			if((int)puzzle[i][j] ==	0) {		// if puzzle value is a 0, display a blank space instead
				cout << "  ";					
			} else {
				cout << puzzle[i][j] << " ";	
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


