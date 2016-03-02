main: main.o CardDeck.o
	g++ main.o CardDeck.o -o main

main.o: main.cpp
	g++ -c main.cpp
CardDeck.o: CardDeck.cpp
	g++ -c CardDeck.cpp

clean:
	rm -f *.o main
