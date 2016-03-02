/* Matt Reilly
 *
 * CardDeck.cpp, cse20212
 * This is the CardDeck class.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CardDeck.h"

using namespace std;

// Overload << operator
ostream & operator<<(ostream & output, const CardDeck & myDeck) {
	srand(time(0));
	deque<int>::const_iterator i;  // establish forward iterator
	for (i = myDeck.deck.begin(); i != myDeck.deck.end(); i++)
		output << *i << ", ";
	output << endl;
	return output;
}

// CardDeck constructor, fill deck with values
CardDeck::CardDeck(int n) {
	for (int i = 0; i < n; ++i)
		deck.push_back(i);
}

// return size of deck
int CardDeck::getSize() {
	return deck.size();
}

// Shuffles deck with random_shuffle from STL
void CardDeck::shuffle() {
	random_shuffle(deck.begin(), deck.end());
}

// Check if deck is in order
int CardDeck::inOrder() {
	for (int i = 0; i < deck.size() - 1; i++) {
		if (deck[i] > deck[i+1]) 
			return 0; 				// deck is out of order
	}
	return 1; 						// deck is in order
}
