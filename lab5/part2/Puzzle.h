#ifndef PUZZLE_H
#define PUZZLE_H

/* Matt Reilly
 *
 * Puzzle.h, cse20212
 * Puzzle using Templating
 */

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template <typename T>
class Puzzle {
	public:
		Puzzle(int size = 9); 	// Constructor with default size
		void display(); 		// print puzzle

	private:
		vector<vector <T> > puzzle; 	// Vector to store puzzle
		int boardSize; 					// Side length of board
};

#endif

// Constructor
// Set initial values, obtain data for puzzle
// Assemble puzzle
template <typename T>
Puzzle<T>::Puzzle(int size) {
	boardSize = size;  		// setting private variable
	string file; 			// name of data file
	T piece; 				// piece to add to puzzle
	ifstream input; 		// input file

	// Getting file name
	while(1) {
		cout << "Enter a valid file name for the puzzle data: ";
		cin >> file;

		input.open(file.c_str(), ios::in);
		if(input.good())
			break;
		else
			cout << file << " doesn't exist. Try again." << endl;
	}

	// Assemble puzzle from input
	while(!input.eof()) {
		vector<T> r; 		// current row
		for (int i = 0; i < boardSize; i++) {
			input >> piece; 	// obtain next piece
			r.push_back(piece); // add piece
		}

		puzzle.push_back(r); 	// add row
	}
}

// Display puzzle data
template <typename T>
void Puzzle<T>::display() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
}
