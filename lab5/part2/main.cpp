/* Matt Reilly
 * 
 * main.cpp, cse20212
 * Driver for Puzzle.h
 */

#include <iostream>
#include "Puzzle.h"
using namespace std;

int main() {
	
	Puzzle<int> sudoku;	// instantiates 9x9 board
	sudoku.display();
	
	//Puzzle<char> wordoku; // 9 x 9 by default
	//wordoku.display();
}

