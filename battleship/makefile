BattleshipGame: BattleshipGame.o Carrier.o Battleship1.o Destroyer.o Submarine.o PatrolBoat.o Ship.o
	g++ game.cpp -w -lSDL2 -lSDL2_image BattleshipGame.o Ship.o Carrier.o Battleship1.o Destroyer.o Submarine.o PatrolBoat.o -o battleship


BattleshipGame.o: BattleshipGame.cpp BattleshipGame.h Carrier.h makefile

Ship.o: Ship.cpp Ship.h makefile

Carrier.o: Ship.cpp Ship.h Carrier.h makefile

Battleship1.o: Ship.h Battleship1.h makefile

Destroyer.o: Ship.h Destroyer.h makefile

Submarine.o: Ship.h Submarine.h makefile

PatrolBoat.o: Ship.h PatrolBoat.h makefile

clean:
	rm -f *.o battleship
