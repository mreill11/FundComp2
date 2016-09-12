//Battleship Program
//Battleship.h

#ifndef BATTLESHIP1_H
#define BATTLESHIP1_H
#include "Ship.h"

class Battleship1 : public Ship {
public:
	Battleship1();
	int getLength();

private:
	int length;
};

#endif