Fund Comp II
------------

##Battleship

![alt text](https://bytebucket.org/FriarUp/battleship/raw/ffc4090753a2637969e6f9194f15bd9b0461d309/graphics/titlescreen.bmp "Title Screen")

This is a GUI implementation of the classic game Battleship by Chris Beaufils, David Durkin, and Matt Reilly.

Our program is run on the student machines using the SDL library. Our 
makefile properly compiles the program to be run. The executable is computed using -lSDL2 -lSDL2_image to account for the 
graphics.

   From the user perspective, the program is not very difficult to 
run. Once the program begins, the user is prompted in the terminal to 
place their ships. They are able to do this by selecting a row using a 
letter A-J, then by selecting a column 1-10. The indicated position is 
where the head of the ship will go, then the user can select whether 
they want the ship vertical or horizontal by selecting a 1 for vertical 
or 0 for horizontal.  Once all 5 ships have been placed, the GUI 
initializes and the introduction screen is displayed. The game begins 
when the user presses any key on the keyboard. The GUI then displays 
both the user and computer board side by side. The user shoots missiles 
on the user board on the left attempting to sink the computers ships. 
This board displays all white tiles, and the tiles turn grey when the 
mouse hovers over a tile. The computer board is on the right side, and 
displays grey tiles where the 5 user ships are placed.  As each player 
shoots and misses, the missed tile turns blue, while every hit turns the 
tile red. This allows the user to keep track of both their own shots as 
well as the computers progress in the game, just like a normal game of 
battleship.  When either the computer or user wins, the GUI then 
switches to a final screen congratulating the winner. The winner can 
play again by pressing any key and the process repeats with the GUI 
closing and the user placing their ships once again in the terminal. The 
user can also quit at anytime by simply closing the window. This 
effectively ends the program altogether. 

![alt text](https://bytebucket.org/FriarUp/battleship/raw/65e9567d87d5e8ec4d681ad59130abb69855dd98/graphics/gameScreenshot.png "Screenshot")

   In running this program, we had very few but serious bugs. Every 
once in a while, roughly every 1 out of 10 tries, the user will place 
all of their ships, then the program will have a segmentation fault. The 
reason for this is because the computer attempts to place their ships 
out of bounds. We believed this should be averted because we have a 
function that checks if the ship placement is valid, but for some reason 
it still occasionally fails. The other error that occurs is that after 
the user plays many games consecutively, the program occasionally 
freezes after the user places their ships to begin the next game. The computer 
places their ships this time but then the GUI window does not open. We do not 
know why this occurs, but it seems to only happen after the user plays 
the game many times in a row. When this happens, the user has to close 
the terminal completely in order to run the game again, because CTRL+C 
is unresponsive. Our group wanted to be able to place the ships in 
the graphics window, but we decided to concentrate our time on 
making the gameplay function smoothly with the graphics and did not 
think it was wise to try to implement such a large feature so late 
in the process. The user can place ships perfectly fine in the 
terminal, and we did not believe it was necessary to do this in the 
graphics window. This does not take anything away from the gameplay 
whatsoever. Aside from this, our game runs smoothly, and the AI functions
perfectly and is very competitive.
