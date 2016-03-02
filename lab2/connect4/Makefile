main: main.o C4Board.o C4Col.o 
	g++ main.o C4Board.o C4Col.o -o main

main.o: main.cpp
	g++ -c main.cpp
C4Board.o: C4Board.cpp 
	g++ -c C4Board.cpp
C4Col.o: C4Col.cpp 
	g++ -c C4Col.cpp

clean:
	rm -f *.o main
