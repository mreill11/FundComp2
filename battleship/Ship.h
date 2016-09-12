//David Durkin, Matt Reilly, Chris Beaufils
//Battleship Program ship class 

#ifndef SHIP_H
#define SHIP_H
#include <string>
using namespace std;

class Ship {

public:
	Ship(string nameIN, int verticalIN, int lengthIN, int hitsIN);
	void setOrientation(int);
	int getVertical();
	string getName();
	void setName(string);
	void hit();
	int isSunk();
	int getLength();
	void reset();

private:
	int vertical;
	string name;
	int hits;
	int length;
	
};


#endif 
