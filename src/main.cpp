#include "../src/include/Grid.h"

using std::cin;
using std::cout;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont;

std::string FONT_PATH = "res/font/SourceCodePro-Regular.ttf";

bool init(SDL_Window** Window, SDL_Renderer** Renderer) {
    bool initSuccess = true;
    TTF_Init();
    gFont = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError();
        initSuccess = false;
    }
    else {
        *Window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (*Window == NULL) {
            cout << "Failed to create window! SDL_Error: " << SDL_GetError();
            initSuccess = false;
        }
        else {
            *Renderer = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);
            if (*Renderer == NULL) {
                cout << "Failed to create renderer! SDL_Error " << SDL_GetError();
                initSuccess = false;
            }
        }
    }
    return initSuccess;
}

void close(SDL_Window** Window, SDL_Renderer** Renderer) {
    SDL_DestroyWindow(*Window);
    *Window = NULL;
    SDL_DestroyRenderer(*Renderer);
    TTF_Quit();
    SDL_Quit();
}

void gameLoop(SDL_Renderer* Renderer) {
    Grid playground;
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        playground.generate(); playground.generate();
        playground.printGrid(Renderer, gFont);
        while (SDL_WaitEvent(&e)) {
            SDL_RenderClear(Renderer);
            if (e.type == SDL_KEYUP)
                continue;
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type = SDL_KEYDOWN) {
                SDL_Keycode Key = e.key.keysym.sym;
                if (Key == SDLK_q || Key == SDLK_n) {
                    if (Key == SDLK_q)
                        return;
                    if (Key == SDLK_n) {
                        playground.clearGrid(Renderer);
                        break;
                    }
                }
                if (Key == SDLK_UP || Key == SDLK_DOWN || Key == SDLK_LEFT || Key == SDLK_RIGHT) {
                    switch (Key) {
                        case SDLK_UP: playground.moveUp(); break;
                        case SDLK_DOWN: playground.moveDown(); break;
                        case SDLK_LEFT: playground.moveLeft(); break;
                        case SDLK_RIGHT: playground.moveRight(); break;
                        default: break;   
                    }
                    playground.generate(); 
                    playground.printGrid(Renderer, gFont);
                }
            }
        }
    }    
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (!init(&gWindow, &gRenderer))
        printf("Failed to initialize!\n");
    else
        gameLoop(gRenderer);
    close(&gWindow, &gRenderer);
    return 0;
}