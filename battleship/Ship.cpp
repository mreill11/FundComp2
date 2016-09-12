//David Durkin, Matt Reilly, Chris Beaufils
//Battleship program Ship.cpp

#include "Ship.h"

// Constructor, sets members to input
Ship::Ship(string nameIN, int verticalIN, int lengthIN, int hitsIN){
	vertical = verticalIN;
	name = nameIN;
	length = lengthIN;
	hits = hitsIN;
}

// Horizontal or vertical?
void Ship::setOrientation(int verticalIn){
	vertical = verticalIn;
}

// Return length of ship
int Ship::getLength() {
	return length;
}

// Return orientation
int Ship::getVertical(){
	return vertical;
}

// Set ship name
void Ship::setName(string in){
	name = in;
}

// Return ship name
string Ship::getName(){
	return name;
}

// Return whether or not ship has been sunk
int Ship::isSunk(){
	if(hits >= length){
		return 1;
	}
	else{
		return 0;
	}
}

// Increment ship hit counter
void Ship::hit(){
	hits++;
}

// Reset ship
void Ship::reset(){
	hits = 0;
}
