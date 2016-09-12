//Battleship Program
//Carrier.h

#ifndef CARRIER_H
#define CARRIER_H
#include "Ship.h"
#include <string>


class Carrier : public Ship {
public:
	Carrier();
	int getLength();

private:
	int length;
};

#endif