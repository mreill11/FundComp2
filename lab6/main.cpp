/* Matt Reilly
 *
 * main.cpp, cse20212
 * Driver program that solves a sudoku board
 */

#include <iostream>
#include "Puzzle.h"

using namespace std;

int main() {
	cout << "Enter a file name for a sudoku puzzle: " << endl;
	Puzzle<int> sudoku;
	cout << "Original puzzle: " << endl;
	sudoku.display();

	cout << "Solved puzzle: " << endl;
	sudoku.solve();
	sudoku.display();
}
