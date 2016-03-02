/* Matt Reilly
 * main.cpp, cse20212
 * 
 * This is the driver class for my Connect Four classes.
 */


#include "C4Board.h"
#include "C4Col.h"
using namespace std;

int main() {
	C4Board board;	// instantiate a C4Board
	board.play();	// start the game	
	
	return 0;
}
