//Battleship Program
//Submarine.h

#ifndef SUBMARINE_H
#define SUBMARINE_H
#include "Ship.h"


class Submarine : public Ship {
public:
	Submarine();
	int getLength();

private:
	int length;
};

#endif
