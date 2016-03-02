#ifndef CARDDECK_H
#define CARDDECK_H

/* Matt Reilly
 *
 * CardDeck.h, cse20212
 * Header file for CardDeck
 */

#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

class CardDeck {

	friend ostream & operator<<(ostream & output, const CardDeck &); 	// Overload << operator

	public:
		CardDeck(int n = 52); 			// Card Deck with 52 cards
		int getSize(); 					// Return size of deck
		void shuffle(); 				// Shuffle deck
		int inOrder(); 					// Determine if deck is in order

	private:
		deque<int> deck; 				// deque to store deck
};

#endif
