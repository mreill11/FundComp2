#include <iostream>
#include "Puzzle.h"
using namespace std;

int main() {
	cout << "Enter a file name for a sudoku puzzle:" << endl;
	Puzzle<int> sudoku;		// puzzle of int's = sudoku
	sudoku.play();		
}
