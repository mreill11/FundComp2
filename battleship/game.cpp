/* cse20212, game.cpp
 * We worked from Lazy Foo tutorials on SDL, so some of this code is directly from the tutorials.
 * Visit http://lazyfoo.net/SDL_tutorials/ to view the tutorials and licensing information.
*/

#include "BattleshipGame.h"
//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 580;
const int SCREEN_HEIGHT = 280;

//Button constants
const int BUTTON_WIDTH = 28;
const int BUTTON_HEIGHT = 28;
const int TOTAL_BUTTONS = 100;

//Array to track Comp Board
vector< vector<char> > compBoard;
vector< vector<char> > userBoard;

// Enumerated type Sprite
enum LButtonSprite
{
	WHITE = 0,
	GREY = 2,
	BLUE = 3,
	RED = 1,
	NONE = 5,
	TITLE = 6,
	BUTTON_SPRITE_TOTAL = 4
};

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );
	
		//Shows button sprite
		void render(int);


	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Mouse button sprites
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;
LTexture gTitleScreen;
LTexture gWinningScreen;
LTexture gLosingScreen;

//Buttons objects
LButton gButtons[ 2*TOTAL_BUTTONS ];
LButton gTitle[ 0 ];

BattleshipGame game;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = WHITE;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN  )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = WHITE;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = GREY;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BLUE;
				break;
				
			}
		}
	}
}
	
void LButton::render(int color) // modified to persist proper color
{
	if (color == NONE) { // Keep the white or gray, depending on where mouse is
		gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
	} else { // persist color, hit or miss
		gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ color ] );
	}


}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "BATTLESHIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

// 
// !gTitleScreen.loadFromFile( "graphics/titlescreen.bmp" )

	//Load sprites
	if(!gButtonSpriteSheetTexture.loadFromFile("graphics/battleshipSprites.bmp" ) || !gTitleScreen.loadFromFile( "graphics/titlescreen.bmp" ) || !gWinningScreen.loadFromFile("graphics/winningScreen.bmp") || !gLosingScreen.loadFromFile("graphics/losingScreen.bmp"))
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = i * 28;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}
		// make user board
		int x = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				gButtons[x].setPosition(i*28, j*28);
				x++;
			}
		}
		// make computer board
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				gButtons[x].setPosition((i*28) + 300, j*28);
				x++;
			}
		}

	}

	return success;
}

void close()
{
	//Free loaded images
	gButtonSpriteSheetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	bool play = false; // keep playing?
	bool quit = false; // quit?

	do {
		play = false;
		srand(time(NULL));
		int result, over;
		int permission = 1;
		game.initializeBoards();

		//Start up SDL and create window
		if( !init() )
		{
			printf( "Failed to initialize!\n" );
		}
		else
		{
			//Load media
			if( !loadMedia() )
			{
				printf( "Failed to load media!\n" );
			}
			else
			{
				
				gTitleScreen.render( 0, 0 );

				//Update screen
				SDL_RenderPresent( gRenderer );
				SDL_Event e2;

				//Main loop flag
				bool quit = false;
				bool keyboard = false;
				SDL_PollEvent( &e2 );

				while ( !keyboard ) {
					SDL_PollEvent( &e2 );
					if ( e2.type == SDL_QUIT ) {
						quit = true;
						break;
					} else if (e2.type == SDL_KEYDOWN ) {
						keyboard = true;
					}
				}

				//Event handler
				SDL_Event e;

				//While application is running
				while( !quit )
				{
					//Handle events on queue
					while( SDL_PollEvent( &e ) != 0 )
					{
						compBoard = game.getComputer();
						userBoard = game.getUser();
						over = game.game();
						//User requests quit
						if( e.type == SDL_QUIT || over)
						{
							quit = true;
						} else if ( e.type == SDL_MOUSEBUTTONDOWN ) {
							//Get mouse position
							int x, y;
							SDL_GetMouseState( &x, &y );
							// execute turn
							result = game.turn(x, y);
							if (result) {
								break;
							}
							game.computerPlay(); // execute computer turn
						}

						//Handle button events
						for( int i = 0; i < 2*TOTAL_BUTTONS; ++i )
						{
							gButtons[ i ].handleEvent( &e );
						}
					}

					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );

					//Render buttons
					int set = 0;
					for( int i = 0; i < 10; i++ ) {
						for (int j = 0; j < 10; j++) {
							switch(compBoard[j][i]) { // set render color
								case 'H':
									gButtons[ set ].render(RED);
									break;
								case 'M':
									gButtons[ set ].render(BLUE);
									break;
								default:
									gButtons[ set ].render(NONE);
									break;
							}
							set++;
						}					
					}

					for( int i = 0; i < 10; i++ ) {
						for (int j = 0; j < 10; j++) {
							switch(userBoard[j][i]) { // set render color
								case 'H':
									gButtons[ set ].render(RED);
									break;
								case 'M':
									gButtons[ set ].render(BLUE);
									break;
								case 'B': case 'D': case 'C': case 'P': case 'S':
									gButtons[ set ].render(GREY);
									break;
								default:
									gButtons[ set ].render(WHITE);
									break;
							}
							set++;
						}					
					}

					//Update screen
					SDL_RenderPresent( gRenderer );
				}
			}
		}
		if (over == 1) {
			gLosingScreen.render( 0, 0 );
		} else if (over == 2) {
			gWinningScreen.render( 0, 0 );
		}


		//Update screen
		SDL_RenderPresent( gRenderer );
		SDL_Event e3;

		while ( !play ) {
			SDL_PollEvent( &e3 );
			if ( e3.type == SDL_QUIT ) {
				quit = true;
				break;
			} else if (e3.type == SDL_KEYDOWN ) {
				play = true;

			}
		}

		//Free resources and close SDL
		close();
	} while (play);

	return 0;
}
