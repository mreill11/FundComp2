/* Matt Reilly
 *
 * main.cpp, cse20212
 * Driver program for CardDeck
 */

#include <iostream>
#include <iterator>
#include <deque>
#include "CardDeck.h"

using namespace std;

int main() {
	CardDeck myDeck(10); 		// initialize deck of 10 cards
	cout << "size of deck: " << myDeck.getSize() << endl;

	cout << myDeck;
	if (myDeck.inOrder())
		cout << "Deck is in order" << endl;
	else
		cout << "Deck is not in order" << endl;

	myDeck.shuffle();
	cout << myDeck;
	if (myDeck.inOrder())
		cout << "Deck is in order" << endl;
	else
		cout << "Deck is not in order" << endl;

	return 0;
}
