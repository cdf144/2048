#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init() {
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize!\nSDL_Error: %s", SDL_GetError() );
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( gWindow == nullptr ) {
            printf( "Window could not be created!\nSDL_Error: %s", SDL_GetError() );
            success = false;
        }
        else
            gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
    return success;
}

bool loadMedia() {
	bool success = true;
    gHelloWorld = SDL_LoadBMP( "media/hello_world.bmp" );
    if( gHelloWorld == nullptr ) {
        printf( "Unable to load image %s!\nSDL_Error: %s", "media/hello_world.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}

void close() {
	SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_Quit();
}

int main( int argc, char* argv[] ) {
    if ( !init() )
        printf( "Failed to initialize!\n" );
    else {
        if ( !loadMedia() )
            printf( "Failed to load media!" );
        else {
            SDL_BlitSurface( gHelloWorld, nullptr, gScreenSurface, nullptr);
            SDL_UpdateWindowSurface( gWindow );
            SDL_Event e; bool quit = false;
            while( quit == false ) {
                while( SDL_PollEvent( &e ) ) {
                    if ( e.type == SDL_EventType::SDL_QUIT )
                        quit == true;
                }
            }
        }
    }
    close();
    return 0;
}