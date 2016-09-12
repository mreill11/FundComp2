//Battleship Program
//Destroyer.h

#ifndef DESTROYER_H
#define DESTROYER_H
#include "Ship.h"


class Destroyer : public Ship {
public:
	Destroyer();
	int getLength();

private:
	int length;
};

#endif