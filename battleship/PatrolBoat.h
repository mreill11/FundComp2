//Battleship Program
//PatrolBoat.h

#ifndef PATROLBOAT_H
#define PATROLBOAT_H
#include "Ship.h"
#include <string>


class PatrolBoat : public Ship {
public:
	PatrolBoat();
	int getLength();

private:
	int length;
};

#endif