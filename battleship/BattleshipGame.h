/* cse20212, BattleshipGame.h
Authors: Christopher Beaufils, David Durkin, Matthew Reilly
This is the class for the battleship game program.
*/

#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include "Ship.h"
#include "Carrier.h"
#include "Battleship1.h"
#include "Destroyer.h"
#include "Submarine.h"
#include "PatrolBoat.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string>
#include <ctime>
using namespace std;

class BattleshipGame {

	public:
	BattleshipGame(int size=10);	// constructor
	int userplaceship(Ship s, int, int, int);	// takes input from the user on where to place the ships
	void computerplaceship(Ship s, int, int, int);	// randomly places the computers ships
	int turn(int, int);	// run the users turn
	int checkValid(int, int);	// check if the user can shoot a missile in this location
	vector< vector<char> > getUser() const;	// return the contents of the boards to the graphics program
	vector< vector<char> > getComputer();
	void displayUser();	// display the user board in the terminal
	void placeUserShips();	// places the users ships on the board
    	int randrow(); // generate a random row and column
    	int randcol();
    	void placeComputerShips();	// place the computer ships into the vector
	void computerPlay();	// simulate the computers turn
	int checkLeft();	// the 4 directional functions are how the ship tries to sink ships once it gets an initial hit
	int checkRight();
	int checkDown();
	int checkUp();
	int game();	// check if the game is over
	int isSunk(Ship s);	// check if a ship has been sunk
	int placementValid(Ship s, int, int, int);	// check if a ship can be placed in this location
	void initializeBoards();	// reset the boards and global variables when running the game again in the graphics window
	int randVertical();	// generate a random 1 or 0 to place the ships either vertically or horizontally

	private:
	int boardSize;	// the size of the battleship board
	int spotA;	// store the position of where the user shot a missile
	int spotB;
    	int compPrevRow;	// store the location of where the computer shot when he got an initial hit
    	int compPrevCol;
    	int compOnTarget;   // checks if the last shot of the computer was a hit, to allow for another turn
	int shipSunk;	// check if the computer has sunk a ship
	int count;	// to allow the AI to track a ship once it has been initially hit
	int direction;	// allow the AI to check different directions once it has been initially hit
	int value;	// variable to check if the game has ended
	int userValue;	// check which player has won
	int computerValue;
	vector< vector<char> > userBoard;	// store the battleship board for the user and computer
	vector< vector<char> > computerBoard;
	Carrier carrier;	// instantiations of ship objects for the computer
	Battleship1 battleship;
	Destroyer destroyer;
	Submarine submarine;
	PatrolBoat patrolboat;
	Carrier Ucarrier;	// instantiations of ship objects for the user
	Battleship1 Ubattleship;
	Destroyer Udestroyer;
	Submarine Usubmarine;
	PatrolBoat Upatrolboat;

};

#endif
