/* Matt Reilly
 * 
 * C4Board.cpp, cse20212
 * Implementation of the C4Board class.
 */

 #include <iostream>
 #include <iomanip>
 #include <stdlib.h>
 #include <time.h>
 #include "C4Col.h"
 #include "C4Board.h"

 using namespace std;

// Default constructor, initializes variables
// Variable descriptions in the header file
 C4Board::C4Board() {
 	numCols = 7;
 	nFullCol = 0;
 	turn = 1;
 	numToWin = 4;
 	p1 = 'X';
 	p2 = 'O';
 	board = new C4Col[numCols];
 }

// Deconstructor frees up memory
 C4Board::~C4Board() {		
	delete [] board; 		
}

// copy constructor
// very basic, simply copies one object into the other
C4Board::C4Board(const C4Board & C4BoardToCopy) {
    numCols = C4BoardToCopy.numCols;
    nFullCol = C4BoardToCopy.nFullCol;
    turn = C4BoardToCopy.turn;
    numToWin = C4BoardToCopy.numToWin;
    p1 = C4BoardToCopy.p1;
    p2 = C4BoardToCopy.p2;
    board = new C4Col[numCols];
}

// overloaded << operator, enables cout << (*this) functionality in code
// Does the same thing as display()
ostream &operator<<( ostream & output, const C4Board & myBoard) {
    // iterate through columns and print them
    for (int h = 0; h < myBoard.numCols; h++)
        output << " " << h << "  "; 
    
    output << endl;
    
    // Span the entire board, top to bottom and left to right
    for (int i = myBoard.board[0].getMaxDiscs() - 1; i >= 0; i--) { // top of cols, downward
        for (int j = 0; j < myBoard.numCols; j++) {		// for each disc space in each row
            output << " " << myBoard.board[j].getDisc(i);
            if(j < myBoard.numCols - 1)
                output << " |";	// only place |'s btwn columns
        }
        
        output << endl;
    }
    return (output);
}

// Display the board
// cout << (*this) << endl; now works too
 void C4Board::display() {
 	//number columns
 	for (int h = 0; h < numCols; h++)
 		cout << " " << h << " " << " ";
 	cout << endl;

 	// populate board with pieces and lines
 	for (int i = board[0].getMaxDiscs() - 1; i >= 0; i--) {
 		for (int j = 0; j < numCols; j++) {
 			cout << " " << board[j].getDisc(i); // insert piece at this spot
 			if (j < numCols - 1)
 				cout << " |"; // insert pipe |
 		}
 		cout << endl;
 	}
 }

// This helper method serves many purposes. Tracking turns, validation, etc.
void C4Board::getColumn() {
	while(1) {			
		// use ternary operator to determine whose turn it is
		cout << (turn % 2 == 1 ? "p1(X)" : "p2(O)") << ": ";
		cin >> inputCol;	// read in user input										
		if(inputCol >= -1 && inputCol < numCols) {	
			// make sure column isn't full
			if(inputCol != -1 && board[inputCol].isFull() == 1) {
				cout << "No room. Try a different column." << endl;
				continue;	
			}
			break;   	
		}			
		cout << "Enter a valid column:" << endl; 
	}
}


void C4Board::play() {
	int winner = 0;		// 1 = player 1, 2 = player 2	
	int curPiece;		// 	either X or O
	int numDinC;		// num discs in column

	system("clear");		
	cout << "Select a column number to place disc. -1 to end the game" << endl;
	cout << *this << endl;
	while(1) {	
		getColumn();			
		if(inputCol == -1) {   	// user quit game
			cout << "Game over." << endl;
			break;		
		} else {				
			system("clear");								
			curPiece = (turn % 2 == 1) ? p1 : p2;	// adjusting current piece for turn
			board[inputCol]+=curPiece;
			if(board[inputCol].isFull() == 1) {		// column is full		
				nFullCol++;									
				if(nFullCol == numCols) {			// board is full, game is over			
                    cout << *this << endl;
					cout << "You tied." << endl;
					return;
				}
			}
			turn++;			// next turn
			winner = gameWon(curPiece, board[inputCol].getNumDiscs() - 1, inputCol);
			cout << *this << endl; // display board
			// determine if winner
			if (winner == 1) 
				cout << "Player 1 you win!" << endl;
			else if (winner == 2) 
				cout << "Player 2 you win!" << endl;
			if (winner != 0) 
				return;							
		}		
	}
}

// The most complicated function, determining if the game was won.
int C4Board::gameWon(char curPiece, int row, int col) {
	int trow;				// used to track winning progress
	int tcol;				// same ^^^
	int progress = 0;		// once it is 4, the game has been won

	// Checking horizontally around the new piece
	// Start to left of piece and check if winner as you move to the right
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	
		progress = 0;		// start progress at 0										
		for(int i = 0; i < numToWin; i++) {	// move to right						
			tcol = col + offset + i;		
			// make sure location is in bounds						
			if (!(trow >= 0 && trow < board[0].getMaxDiscs() && tcol >= 0 && tcol < numCols)) // make sure in bounds
				break; 	
		
			if(board[tcol].getDisc(row) == curPiece) {  
		  		if(++progress == numToWin) {		// increment piece
					if(curPiece == p1) return 1;	// return winner
					else return 2;
		  		} 
			} else {									
				break;			
			}
		}
	}
	
	// Same as above, but vertical
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	
		progress = 0;												
		for(int i = 0; i < numToWin; i++) {							
			trow = row + offset + i;						 	
			if (!(trow >= 0 && trow < board[0].getMaxDiscs() && tcol >= 0 && tcol < numCols))
				break; 		
			
			if(board[col].getDisc(trow) == curPiece) {		
				if(++progress == numToWin) {
					if(curPiece == p1) return 1;			
					else return 2;
				}
			} else {
				break;
			}
		}
	}

	// checking diagonally, bottom left to upper right
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	
		progress = 0;												
		for(int i = 0; i < numToWin; i++) {							
			trow = row + offset + i;							
			tcol = col + offset + i;
			if (!(trow >= 0 && trow < board[0].getMaxDiscs() && tcol >= 0 && tcol < numCols)) 
				break; 	

			if(board[tcol].getDisc(trow) == curPiece) {	
				if(++progress == numToWin) {					
					if(curPiece == p1) return 1;			
					else return 2;
				}
			} else {
				break;
			}
		}
	}

	// diagonally, opposite way
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	
		progress = 0;												
		for(int i = 0; i < numToWin; i++) {							
			trow = row + offset + i;							
			tcol = col - offset - i;
			if (!(trow >= 0 && trow < board[0].getMaxDiscs() && tcol >= 0 && tcol < numCols)) 
				break; 

			if(board[tcol].getDisc(trow) == curPiece) {	
				if(++progress == numToWin) {					
					if(curPiece == p1) return 1;			
					else return 2;
				}
			} else {
				break;
			}
		}
	}
	return 0;										
}
