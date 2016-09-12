/* cse20212, BattleshipGame.cpp
 */

#include "BattleshipGame.h"
#include "Ship.h"

using namespace std;

// Constructor, takes size as a parameter (10)
BattleshipGame::BattleshipGame(int size) {
	boardSize = size; // num of rows. cols
	compOnTarget = 0; // whether or not computer hit last turn
	shipSunk = 1;     // is a ship sunk?
	count = 1;
	direction = 1;    // direction computer is shooting in
	value = 0;

	vector<char> row; // create one vector for each row
	// initialize empty board
	for (int i=0; i < boardSize; i++) {
		row.push_back('O'); // input the value into the row vector
	}

	for (int i=0; i < boardSize; i++) {
		userBoard.push_back(row); // create the puzzle one row at a time
		computerBoard.push_back(row);
	}
}

// This function initializes the user and computer boards
void BattleshipGame::initializeBoards() {

	// loop through rows, cols
	for (int i=0; i < boardSize; i++) {
		for (int j=0; j<boardSize; j++) {
				userBoard[i][j] = 'O'; // create the puzzle one row at a time
				computerBoard[i][j] = 'O';
		}
	}
	// Reset and initialize everything, avoid segfaults
	compOnTarget = 0;
	shipSunk = 1;
	count = 1;
	direction = 1;
	value = 0;
	carrier.reset();
	Ucarrier.reset();
	battleship.reset();
	Ubattleship.reset();
	destroyer.reset();
	Udestroyer.reset();
	submarine.reset();
	Usubmarine.reset();
	patrolboat.reset();
	Upatrolboat.reset();
	placeUserShips();
	placeComputerShips();

}

// Display the user board in the terminal
void BattleshipGame::displayUser(){
	for(int i = 0; i < boardSize; i++){
		cout << " | "; // vertical divider
		for(int j = 0; j < boardSize; j++){
			cout << userBoard[i][j] << " | ";
		}
		cout << endl;
		cout << "-----------------------------------------" << endl; // divider line
	}
}

// Return user board
vector< vector<char> > BattleshipGame::getUser() const{
	return userBoard;
}

// Return computer board
vector< vector<char> > BattleshipGame::getComputer(){
	return computerBoard;
}

// Execute one player turn of the battleship game
// Takes mouse click position as args
int BattleshipGame::turn(int mouseX, int mouseY) {
	char letterChoice;
	int hit = 0;
	int Valid = 0;


	// Player Turn

	spotB = mouseX/28; // Determine which square was clicked
	spotA = mouseY/28;
	Valid = checkValid(spotA, spotB); // Make sure click was valid
	if (!Valid) { // exit if it wasn't, tell user to quit fooling around and play the game
		return 1;
	}

	// These if statements test if the shot was a hit for each type of ship
	// The comments on the first one apply to all subsequent else if's
	if (computerBoard[spotA][spotB] == 'C') {
		computerBoard[spotA][spotB] = 'H';
		cout << "That's a hit!" << endl;
		carrier.hit(); // tell the ship it was hit
		if (carrier.isSunk()) { // check if the ship was sunk
			cout << "You sunk their carrier!" << endl; // nice!
		}
		hit = 1; // alert the program of a hit
	} else if (computerBoard[spotA][spotB] == 'B') {
		computerBoard[spotA][spotB] = 'H';
		cout << "That's a hit!" << endl;
		battleship.hit();
		if (battleship.isSunk()) {
			cout << "You sunk their battleship!" << endl;
		}
		hit = 1;
	} else if (computerBoard[spotA][spotB] == 'S') {
		computerBoard[spotA][spotB] = 'H';
		cout << "That's a hit!" << endl;
		submarine.hit();
		if (submarine.isSunk()) {
			cout << "You sunk their submarine!" << endl;
		}
		hit = 1;
	} else if (computerBoard[spotA][spotB] == 'D') {
		computerBoard[spotA][spotB] = 'H';
		cout << "That's a hit!" << endl;
		destroyer.hit();
		if (destroyer.isSunk()) {
			cout << "You sunk their destroyer!" << endl;
		}
		hit = 1;
	} else if (computerBoard[spotA][spotB] == 'P') {
		computerBoard[spotA][spotB] = 'H';
		cout << "That's a hit!" << endl;
		patrolboat.hit();
		if (patrolboat.isSunk()) {
			cout << "You sunk their patrol boat!" << endl;
		}
		hit = 1;
	} else { // not a hit!
		computerBoard[spotA][spotB] = 'M'; // update the computer board
		cout << "You missed!" << endl;     // smooth move
		hit = 0;  // no hit
	}


	return hit;
}

// Track the game progress
int BattleshipGame::game() {
	userValue = 0;
	computerValue = 0;

	// Check the progress of both the user and computer, see who is in the lead
	for (int i=0; i < boardSize; i++) {        // loop through
		for (int j=0; j < boardSize; j++) {    // both rows and cols
			if (userBoard[i][j] == 'B' || userBoard[i][j] == 'P' || userBoard[i][j] == 'S' || userBoard[i][j] == 'D' || userBoard[i][j] == 'C') {
				userValue++; // increment how many spots on ships you have left
			}
			if (computerBoard[i][j] == 'B' || computerBoard[i][j] == 'P' || computerBoard[i][j] == 'S' || computerBoard[i][j] == 'D' || computerBoard[i][j] == 'C') {
				computerValue++;  // same thing for computer
			}
		}
	}

	// Check if someone won the game
	if (userValue == 0) {
		userValue = 1; // user lost, return 1 to show this
		return userValue;
	} else if (computerValue == 0) {
		computerValue = 2; // computer lost, return 2 to show this
		return computerValue;
	} else {
		return 0; // no one lost, keep on playing
	}
}

// Check if the user shot is valid
int BattleshipGame::checkValid(int spotA, int spotB) {
	
	if (spotA > 9 || spotA < 0) { // user shot outside of bounds
		cout << "You cannot shoot a missle here, try a new strategy!" << endl;
		return 0;
	}
	else if (spotB > 9 || spotB < 0) {
		cout << "You cannot shoot a missle here, try a new strategy!" << endl;
		return 0;
	}
	else if (computerBoard[spotA][spotB] == 'M' || computerBoard[spotA][spotB] == 'H') { // user already shot here
		cout << "You have already shot a missle here! Try a new strategy." << endl;
		return 0;
	}

	return 1;
}

// This function handles the placing of user ships on the board
void BattleshipGame::placeUserShips(){
	cout << "Place Your Ships. Ships will be placed extending to the right of or downwards from your grid selection." << endl; 
	int play = 1;
	char letter;
	int number, row, col, vertical, success;

	displayUser();
	do { // Place Carrier
		cout << "Where would you like to place your Carrier?" << endl;
		cout << "Letter: ";
		cin >> letter; // get row letter
		row = toupper(letter) - 65;
		cout << "Number: ";
		cin >> number; // get col number
		col = number - 1; // adjust for 0 start
		cout << "1 for Vertical, 0 for Horizontal: ";
		cin >> vertical; // get orientation
		success = userplaceship(Ucarrier, row, col, vertical);	// try to place ship on board
		displayUser(); // display ship
	} while (!success);
	success = 0;
	do { // Same process as above, but for battleship
		cout << "Where would you like to place your Battleship?" << endl;
		cout << "Letter: ";
		cin >> letter;
		row = toupper(letter) - 65;
		cout << "Number: ";
		cin >> number;
		col = number - 1;
		cout << "1 for Vertical, 0 for Horizontal: ";
		cin >> vertical;
		success = userplaceship(Ubattleship, row, col, vertical);
		displayUser();
	} while (!success);
	success = 0;
	do { // Same process as above, but for submarine
		cout << "Where would you like to place your Submarine?" << endl;
		cout << "Letter: ";
		cin >> letter;
		row = toupper(letter) - 65;
		cout << "Number: ";
		cin >> number;
		col = number - 1;
		cout << "1 for Vertical, 0 for Horizontal: ";
		cin >> vertical;
		success = userplaceship(Usubmarine, row, col, vertical);
		displayUser();
	} while (!success);
	success = 0;
	do { // Same process as above, but for destroyer
		cout << "Where would you like to place your Destroyer?" << endl;
		cout << "Letter: ";
		cin >> letter;
		row = toupper(letter) - 65;
		cout << "Number: ";
		cin >> number;
		col = number - 1;
		cout << "1 for Vertical, 0 for Horizontal: ";
		cin >> vertical;
		success = userplaceship(Udestroyer, row, col, vertical);
		displayUser();
	} while (!success);
	success = 0;
	do { // Same process as above, but for patrol boat
		cout << "Where would you like to place your Patrol Boat?" << endl;
		cout << "Letter: ";
		cin >> letter;
		row = toupper(letter) - 65;
		cout << "Number: ";
		cin >> number;
		col = number - 1;
		cout << "1 for Vertical, 0 for Horizontal: ";
		cin >> vertical;
		success = userplaceship(Upatrolboat, row, col, vertical);
		displayUser();
	} while (!success);
}

void BattleshipGame::placeComputerShips() { // Place computer ships on board randomly

	// Place all 5 ships randomly
	computerplaceship(carrier, randrow(), randcol(), randVertical());
	computerplaceship(battleship, randrow(), randcol(), randVertical());
	computerplaceship(submarine, randrow(), randcol(), randVertical());
	computerplaceship(destroyer, randrow(), randcol(), randVertical());
	computerplaceship(patrolboat, randrow(), randcol(), randVertical());
	cout << "Placing Computer Ships ..." << endl;
}

// return random row
int BattleshipGame::randrow() {
	return rand() % 10;
}

// return random col
int BattleshipGame::randcol() {
	return rand() % 10;
}

// return random orientation
int BattleshipGame::randVertical() {
	return rand() % 2;
}

// This function executes the computer's turn until it misses
void BattleshipGame::computerPlay() {
	int row = randrow(), col = randcol(); // place computer will shoot
	int left, right, down, up; // directions for AI

	do {
		value = game(); // make sure game is going
		if (value) {
			break;
		} // AI AI AI AI
		if (!shipSunk) { // if ship isn't sunk
			compOnTarget = 1; // computer is on target
			if (direction % 4 == 1) { // should computer check left?
				left = checkLeft();   // is there a ship to the left?
				if (left == 0) {
					direction += 1;   // increment direction if left was wrong
				}
			} else if (direction % 4 == 2) { // should computer check right?
				right = checkRight();        // is there a ship on the right?
				if (right == 0) {
					direction += 1;          // increment direction if right was wrong
				}
			} else if (direction % 4 == 3) { // should computer check down?
				down = checkDown();          // is there a ship below?
				if (down == 0) {
					direction += 1;          // increment direction if down was wrong
				}
			} else if (direction % 4 == 0) { // should computer check up?
				up = checkUp();              // is there a ship above?
				if (up == 0) {
					direction += 1;          // increment direction if up was wrong
				}
			} else {
				direction += 1;              // increment direction
			}
			continue;
		} else {
			count = 1;
		}

		// Handle computer shot
		if (userBoard[row][col] == 'C') { // Carrier hit
			cout << "Computer hit!" << endl;
			userBoard[row][col] = 'H';    // update user board vector
			compOnTarget = 1;             // computer is on target
			compPrevRow = row;            // update previous row
			compPrevCol = col;            // update previous column
			shipSunk = 0;                 // ship not sunk
			Ucarrier.hit();               // tell ship it was hit
		} else if (userBoard[row][col] == 'B') { // same process, different ship
			cout << "Computer hit!" << endl;
			userBoard[row][col] = 'H';
			compOnTarget = 1;
			compPrevRow = row;
			compPrevCol = col;
			shipSunk = 0;
			Ubattleship.hit();
		} else if (userBoard[row][col] == 'S') { 
			cout << "Computer hit!" << endl;
			userBoard[row][col] = 'H';
			compOnTarget = 1;
			compPrevRow = row;
			compPrevCol = col;
			shipSunk = 0;
			Usubmarine.hit();
		} else if (userBoard[row][col] == 'D') {
			cout << "Computer hit!" << endl;
			userBoard[row][col] = 'H';
			compOnTarget = 1;
			compPrevRow = row;
			compPrevCol = col;
			shipSunk = 0;
			Udestroyer.hit();
		} else if (userBoard[row][col] == 'P') {
			cout << "Computer hit!" << endl;
			userBoard[row][col] = 'H';
			compOnTarget = 1;
			compPrevRow = row;
			compPrevCol = col;
			shipSunk = 0;
			Upatrolboat.hit();
		} else if (userBoard[row][col] == 'O') { // Miss!
			userBoard[row][col] = 'M';           // update user board as a miss
			cout << "Computer miss!" << endl;
			compOnTarget = 0;                    // computer not on target
		} else if (userBoard[row][col] == 'H' || userBoard[row][col] == 'M') { // Already shot here
			row = randrow();                     // choose a new row
			col = randcol();                     // choose a new col
			compOnTarget = 1;                    // keep the loop going
		}
	} while(compOnTarget);

}

int BattleshipGame::checkLeft() {
	if (compPrevCol - count <= 9 && compPrevCol - count >= 0 && !shipSunk) { // Make sure checking left doesn't put you out of bounds
		// Check if left is empty and not a miss
		if (userBoard[compPrevRow][compPrevCol - count] == 'O' && userBoard[compPrevRow][compPrevCol - count] != 'M') {
			compOnTarget = 0; // computer is not on target
			userBoard[compPrevRow][compPrevCol - count] = 'M'; // Miss!
			count = 1;
			cout << "Computer miss!" << endl;
			return 0;
		} else if (userBoard[compPrevRow][compPrevCol - count] == 'C') { // Is carrier there to the left?
			userBoard[compPrevRow][compPrevCol - count] = 'H'; // Hit!
		    	count += 1; // increment count
			Ucarrier.hit(); // tell ship it was hit
			shipSunk = Ucarrier.isSunk(); // check if ship is sunk
			cout << "Computer hit!" << endl;
			if (shipSunk) { // Alert that the ship was sunk
				cout << "The enemy sunk your carrier!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol - count] == 'B') { // Same thing for Battleship
			userBoard[compPrevRow][compPrevCol - count] = 'H';
		    	count += 1;
			Ubattleship.hit();
			shipSunk = Ubattleship.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your battleship!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol - count] == 'S') { // Same thing for submarine
			userBoard[compPrevRow][compPrevCol - count] = 'H';
		    	count += 1;
			Usubmarine.hit();
			shipSunk = Usubmarine.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your submarine!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol - count] == 'D') { // Same thing for destroyer
			userBoard[compPrevRow][compPrevCol - count] = 'H';
		    	count += 1;
			Udestroyer.hit();
			shipSunk = Udestroyer.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your destroyer!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol - count] == 'P') { // Same thing for Patrol Boat
			userBoard[compPrevRow][compPrevCol - count] = 'H';
		    	count += 1;
			Upatrolboat.hit();
			shipSunk = Upatrolboat.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your patrol boat!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol - count] == 'H') { // Computer already hit here
			count++; // increment count to check further
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol - count] == 'M') { // Computer missed here
			count = 1; // stop counting this direction
			return 0;
		}
	}
	count = 1; // reset count
	return 0;
}

// This function checks to the right
// It does everything the exact same way as checkLeft() which is commented above, except to the right
int BattleshipGame::checkRight() {
	if (compPrevCol + count <= 9 && compPrevCol + count >= 0 && !shipSunk) {
		if (userBoard[compPrevRow][compPrevCol + count] == 'O' && userBoard[compPrevRow][compPrevCol + count] != 'M') {
			compOnTarget = 0;
			userBoard[compPrevRow][compPrevCol + count] = 'M';
			count = 1;
			cout << "Computer miss!" << endl;
			return 0;
		} else if (userBoard[compPrevRow][compPrevCol + count] == 'C') {
			userBoard[compPrevRow][compPrevCol + count] = 'H';
		    	count += 1;
			Ucarrier.hit();
			shipSunk = Ucarrier.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your carrier!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol + count] == 'B') {
			userBoard[compPrevRow][compPrevCol + count] = 'H';
		    	count += 1;
			Ubattleship.hit();
			shipSunk = Ubattleship.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your battleship!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol + count] == 'S') {
			userBoard[compPrevRow][compPrevCol + count] = 'H';
		    	count += 1;
			Usubmarine.hit();
			shipSunk = Usubmarine.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your submarine!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol + count] == 'D') {
			userBoard[compPrevRow][compPrevCol + count] = 'H';
		    	count += 1;
			Udestroyer.hit();
			shipSunk = Udestroyer.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your destroyer!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol + count] == 'P') {
			userBoard[compPrevRow][compPrevCol + count] = 'H';
		    	count += 1;
			Upatrolboat.hit();
			shipSunk = Upatrolboat.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your patrol boat!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol + count] == 'H') {
			count++;
			return 1;
		} else if (userBoard[compPrevRow][compPrevCol + count] == 'M') {
			count = 1;
			return 0;
		}
	}
	count = 1;
	return 0;
}

// This function checks up
// It does everything the exact same way as checkLeft() which is commented above, except upwards
int BattleshipGame::checkUp() {
	if (compPrevRow - count <= 9 && compPrevRow - count >= 0 && !shipSunk) {
		if (userBoard[compPrevRow - count][compPrevCol] == 'O' && userBoard[compPrevRow - count][compPrevCol] != 'M') {
			compOnTarget = 0;
			userBoard[compPrevRow - count][compPrevCol] = 'M';
			count = 1;
			cout << "Computer miss!" << endl;
			return 0;
		} else if (userBoard[compPrevRow - count][compPrevCol] == 'C') {
			userBoard[compPrevRow - count][compPrevCol] = 'H';
		    	count += 1;
			Ucarrier.hit();
			shipSunk = Ucarrier.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your carrier!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow - count][compPrevCol] == 'B') {
			userBoard[compPrevRow - count][compPrevCol] = 'H';
		    	count += 1;
			Ubattleship.hit();
			shipSunk = Ubattleship.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your battleship!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow - count][compPrevCol] == 'S') {
			userBoard[compPrevRow - count][compPrevCol] = 'H';
		    	count += 1;
			Usubmarine.hit();
			shipSunk = Usubmarine.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your submarine!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow - count][compPrevCol] == 'D') {
			userBoard[compPrevRow - count][compPrevCol] = 'H';
		    	count += 1;
			Udestroyer.hit();
			shipSunk = Udestroyer.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your destroyer!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow - count][compPrevCol] == 'P') {
			userBoard[compPrevRow - count][compPrevCol] = 'H';
		    	count += 1;
			Upatrolboat.hit();
			shipSunk = Upatrolboat.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your patrol boat!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow - count][compPrevCol] == 'H') {
			count++;
			return 1;
		} else if (userBoard[compPrevRow - count][compPrevCol] == 'M') {
			count = 1;
			return 0;
		}
	}
	count = 1;
	return 0;
}

// This function checks down
// It does everything the exact same way as checkLeft() which is commented above, except downwards
int BattleshipGame::checkDown() {
	if (compPrevRow + count <= 9 && compPrevRow + count >= 0 && !shipSunk) {
		if (userBoard[compPrevRow + count][compPrevCol] == 'O' && userBoard[compPrevRow + count][compPrevCol] != 'M') {
			compOnTarget = 0;
			userBoard[compPrevRow + count][compPrevCol] = 'M';
			count = 1;
			cout << "Computer miss!" << endl;
			return 0;
		} else if (userBoard[compPrevRow + count][compPrevCol] == 'C') {
			userBoard[compPrevRow + count][compPrevCol] = 'H';
		    	count += 1;
			Ucarrier.hit();
			shipSunk = Ucarrier.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your carrier!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow + count][compPrevCol] == 'B') {
			userBoard[compPrevRow + count][compPrevCol] = 'H';
		    	count += 1;
			Ubattleship.hit();
			shipSunk = Ubattleship.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your battleship!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow + count][compPrevCol] == 'S') {
			userBoard[compPrevRow + count][compPrevCol] = 'H';
		    	count += 1;
			Usubmarine.hit();
			shipSunk = Usubmarine.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your submarine!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow + count][compPrevCol] == 'D') {
			userBoard[compPrevRow + count][compPrevCol] = 'H';
		    	count += 1;
			Udestroyer.hit();
			shipSunk = Udestroyer.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your destoyer!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow + count][compPrevCol] == 'P') {
			userBoard[compPrevRow + count][compPrevCol] = 'H';
		    	count += 1;
			Upatrolboat.hit();
			shipSunk = Upatrolboat.isSunk();
			cout << "Computer hit!" << endl;
			if (shipSunk) {
				cout << "The enemy sunk your patrol boat!" << endl;
			}
			return 1;
		} else if (userBoard[compPrevRow + count][compPrevCol] == 'H') {
			count++;
			return 1;
		} else if (userBoard[compPrevRow + count][compPrevCol] == 'M') {
			count = 1;
			return 0;
		}
	}
	count = 1;
    return 0;
}

// This function ensures the placement of a ship is valid
int BattleshipGame::placementValid (Ship s, int row, int col, int vertical) {
	int length = s.getLength(); // length of ship
	int alpha, digit;
	char d;

	d = '0' + col;

	if (!isdigit(d)) { // exit
		return 0;
	}

	if (vertical) { // vertical ship
		for (int i = 0; i < length; i++) {
			if (row + length > 10 || col > 9 || row < 0 || col < 0 ||  userBoard[row + i][col] != 'O') { // ship out of bounds
				return 0;
			}
		} 
	} else { // horizontal ship
		for (int i = 0; i < length; i++) {
			if (row > 9 || col + length > 10 || row < 0 || col < 0 ||  userBoard[row][col + i] != 'O') { // ship out of bounds
				return 0;
			}
		}
	}
	return 1; // all good

}

// This function handles the placing of user ships
int BattleshipGame::userplaceship (Ship s, int row, int col, int vertical){
	if(s.getName() == "Carrier"){ // Place Carrier
		if (placementValid(Ucarrier, row, col, vertical)) {
			if (vertical){ // place vertically
					userBoard[row][col] = 'C';
					userBoard[row+1][col] = 'C';
					userBoard[row+2][col] = 'C';
					userBoard[row+3][col] = 'C';
					userBoard[row+4][col] = 'C';

			} else{ // place horizontally
					userBoard[row][col] = 'C';
					userBoard[row][col+1] = 'C';
					userBoard[row][col+2] = 'C';
					userBoard[row][col+3] = 'C';
					userBoard[row][col+4] = 'C';
			}
			return 1;
		} else { // bad placement
			cout << "You cannot place a ship here. Try Again!" << endl;
			return 0;
		}
	}
	else if(s.getName() == "Battleship"){ // Place Battleship
		if (placementValid(Ubattleship, row, col, vertical)) {
			if (vertical){
					userBoard[row][col] = 'B';
					userBoard[row+1][col] = 'B';
					userBoard[row+2][col] = 'B';
					userBoard[row+3][col] = 'B';

			} else{
					userBoard[row][col] = 'B';
					userBoard[row][col+1] = 'B';
					userBoard[row][col+2] = 'B';
					userBoard[row][col+3] = 'B';
			}
			return 1;
		} else {
			cout << "You cannot place a ship here. Try Again!" << endl;
			return 0;
		}
	}
	else if(s.getName() == "Submarine"){ // Place Submarine
		if (placementValid(Usubmarine, row, col, vertical)) {
			if (vertical){
					userBoard[row][col] = 'S';
					userBoard[row+1][col] = 'S';
					userBoard[row+2][col] = 'S';
			} else{
					userBoard[row][col] = 'S';
					userBoard[row][col+1] = 'S';
					userBoard[row][col+2] = 'S';

			}
			return 1;
		} else {
			cout << "You cannot place a ship here. Try Again!" << endl;
			return 0;
		}
	}
	else if(s.getName() == "Destroyer"){ // Place Destroyer
		if (placementValid(Udestroyer, row, col, vertical)) {
			if (vertical){
				userBoard[row][col] = 'D';
				userBoard[row+1][col] = 'D';
				userBoard[row+2][col] = 'D';

			} else{
				userBoard[row][col] = 'D';
				userBoard[row][col+1] = 'D';
				userBoard[row][col+2] = 'D';
			}
			return 1;
		} else {
			cout << "You cannot place a ship here. Try Again!" << endl;
			return 0;
		}
	}
	else if(s.getName() == "PatrolBoat"){ // Place Patrol Boat
		if (placementValid(Upatrolboat, row, col, vertical)) {
			if (vertical){
				userBoard[row][col] = 'P';
				userBoard[row+1][col] = 'P';
			} else{
				userBoard[row][col] = 'P';
				userBoard[row][col+1] = 'P';
			}
			return 1;
		} else {
			cout << "You cannot place a ship here. Try Again!" << endl;
			return 0;
		}
	}
	else{ // Nope, not a ship
		cout << "Improper ship name" << endl;
		return 0;
	}
}

// This function handles the placing of computer ships
void BattleshipGame::computerplaceship(Ship s, int row, int col, int vertical){
	int counter;

	if(s.getName() == "Carrier"){ // Carrier

		if (vertical){ // Vertical placement
			do {
				counter = 0;
				for (int i=0; i < 5; i++) { // Carrier is 5 spots long
					if (computerBoard[row + i][col] != 'O' || row + 4 > 9) { // ship is out of bounds
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break; // ship is in bounds, place
				}
			} while (1);
			// Found compatible placement, update vector
			computerBoard[row][col] = 'C';
			computerBoard[row+1][col] = 'C';
			computerBoard[row+2][col] = 'C';
			computerBoard[row+3][col] = 'C';
			computerBoard[row+4][col] = 'C';
		}
		else{ // horizontal placement
			do {
				counter = 0;
				for (int i=0; i < 5; i++) {
					if (computerBoard[row][col + i] != 'O' || col + 4 > 9) { // ship is out of bounds
						row = randrow(); // find a new row, col
						col = randcol();
						counter++; // increment counter
					}
				}
				if (counter == 0) {
					break; // found proper placement
				}
			} while (1);
			// place ship
			computerBoard[row][col] = 'C';
			computerBoard[row][col+1] = 'C';
			computerBoard[row][col+2] = 'C';
			computerBoard[row][col+3] = 'C';
			computerBoard[row][col+4] = 'C';
		}
	}
	else if(s.getName() == "Battleship"){ // Follow the same procedure for the Battleship
		if (vertical){
			do {
				counter = 0;
				for (int i=0; i < 4; i++) {
					if (computerBoard[row + i][col] != 'O' || row + 3 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'B';
			computerBoard[row+1][col] = 'B';
			computerBoard[row+2][col] = 'B';
			computerBoard[row+3][col] = 'B';
		}
		else{
			do {
				counter = 0;
				for (int i=0; i < 4; i++) {
					if (computerBoard[row][col + i] != 'O' || col + 3 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'B';
			computerBoard[row][col+1] = 'B';
			computerBoard[row][col+2] = 'B';
			computerBoard[row][col+3] = 'B';
		}
	}
	else if(s.getName() == "Submarine"){ // Follow the same procedure for the Submarine
		if (vertical){
			do {
				counter = 0;
				for (int i=0; i < 3; i++) {
					if (computerBoard[row + i][col] != 'O' || row + 2 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'S';
			computerBoard[row+1][col] = 'S';
			computerBoard[row+2][col] = 'S';
		}
		else{
			do {
				counter = 0;
				for (int i=0; i < 3; i++) {
					if (computerBoard[row][col + i] != 'O' || col + 2 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'S';
			computerBoard[row][col+1] = 'S';
			computerBoard[row][col+2] = 'S';
		}
	}
	else if(s.getName() == "Destroyer"){ // Follow the same procedure for the Destroyer
		if (vertical){
			do {
				counter = 0;
				for (int i=0; i < 3; i++) {
					if (computerBoard[row + i][col] != 'O' || row + 2 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'D';
			computerBoard[row+1][col] = 'D';
			computerBoard[row+2][col] = 'D';
		}
		else{
			do {
				counter = 0;
				for (int i=0; i < 3; i++) {
					if (computerBoard[row][col + i] != 'O' || col + 2 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'D';
			computerBoard[row][col+1] = 'D';
			computerBoard[row][col+2] = 'D';
		}
	}
	else if(s.getName() == "PatrolBoat"){ // Follow the same procedure for the Patrol Boat
		if (vertical){
			do {
				counter = 0;
				for (int i=0; i < 2; i++) {
					if (computerBoard[row + i][col] != 'O' || row + 1 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'P';
			computerBoard[row+1][col] = 'P';
		}
		else{
			do {
				counter = 0;
				for (int i=0; i < 2; i++) {
					if (computerBoard[row][col + i] != 'O' || col + 1 > 9) {
						row = randrow();
						col = randcol();
						counter++;
					}
				}
				if (counter == 0) {
					break;
				}
			} while (1);
			computerBoard[row][col] = 'P';
			computerBoard[row][col+1] = 'P';
		}
	}
	else{
		cout << "Improper ship name" << endl;
	}
}

// Thanks for reading!
