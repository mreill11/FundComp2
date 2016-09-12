//David Durkin
//SDL program; User driven movement of a blue square

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

//Rectangle class
class Rectangle{

public:
	//Constants
	static const int RECT_WIDTH = 50;
	static const int RECT_HEIGHT = 50;
	static const int RECT_VEL = 10;

	//Constructor
	Rectangle();
	//Member functions
	void handleEvent( SDL_Event& e );
	void move();
	void render();
private:
	int xpos, ypos, xvel, yvel;

};

//Starts things up
bool init();
//Shuts things down
void close();
//Initializes window
SDL_Window* gWindow = NULL;
//Initializes renderer
SDL_Renderer* gRenderer = NULL;

//Constructor which sets variables
Rectangle::Rectangle(){
	xpos = 200;
	ypos = 200;

	xvel = 0;
	yvel = 0;
}

//Handles events and updates rectangle's position variables
void Rectangle::handleEvent( SDL_Event& e ){

    //If key pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Change the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: 
		yvel -= RECT_VEL; 
		break;
            case SDLK_DOWN: 
		yvel += RECT_VEL; 
		break;
            case SDLK_LEFT: 
		xvel -= RECT_VEL; 
		break;
            case SDLK_RIGHT: 
		xvel += RECT_VEL; 
		break;
        }
    }
    //If key released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        //Change the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: 
		yvel += RECT_VEL; 
		break;
            case SDLK_DOWN: 
		yvel -= RECT_VEL; 
		break;
            case SDLK_LEFT: 
		xvel += RECT_VEL; 
		break;
            case SDLK_RIGHT: 
		xvel -= RECT_VEL; 
		break;
        }
    }

}

//Moves Rectangle properly
void Rectangle::move(){

    //Move left or right
    xpos += xvel;

    //If the rectangle moves out of window, move it back
    if( ( xpos < 0 ) || ( xpos + RECT_WIDTH > SCREEN_WIDTH ) ){
        xpos -= xvel;
    }

    //Move up or down
    ypos += yvel;

    //Same as previous
    if( ( ypos < 0 ) || ( ypos + RECT_HEIGHT > SCREEN_HEIGHT ) ){
        ypos -= yvel;
    }

}

//Render the rectangle on the screen
void Rectangle::render(){

	SDL_Rect fillRect = { xpos, ypos, RECT_WIDTH ,RECT_HEIGHT };
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );		
	SDL_RenderFillRect( gRenderer, &fillRect );

}

//Initialize things
bool init(){

	bool result = true;

	//Test initialization and initialize
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
		printf("Initialization failed! SDL Error: %s\n", SDL_GetError());
		result = false;
	}
	else{
		//Create a window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( gWindow == NULL ){
			printf("Window creation failed! SDL Error: %s\n", SDL_GetError());
			result = false;
		}
		else{
			//Create renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if( gRenderer == NULL ){
				printf("Renderer creation failed! SDL Error: %s\n", SDL_GetError());
				result = false;
			}
			else{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			}
		}
	}

	return result;
}

//Shut things down
void close(){
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] ){
	
	//Start up SDL and create window
	if( !init() ){
		printf( "Failed to initialize!\n" );
	}
	else{	
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		Rectangle r;

		//While application is running
		while( !quit ){
			//Handle events
			while( SDL_PollEvent( &e ) != 0 ){
				//User requests quit
				if( e.type == SDL_QUIT ){
					quit = true;
				}
				r.handleEvent(e);
			}

			r.move();

			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			r.render();

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
			
	}

	//Free resources and close SDL
	close();

	return 0;
}
