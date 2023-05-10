#include "Grid.h"

using std::cin;
using std::cout;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont;
Mix_Music* gMusic = NULL;
Mix_Chunk* gPressButtonSound = NULL;

std::string FONT_PATH = "res/font/SourceCodePro-Regular.ttf";
std::string BG_MUSIC_PATH = "res/audio/g_music.mp3";
std::string BUTTON_SOUND_PATH = "res/audio/g_button.wav";

bool init(SDL_Window** Window, SDL_Renderer** Renderer) {
    TTF_Init();
    gFont = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError();
        return false;
    }
    *Window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*Window == NULL) {
        cout << "Failed to create window! SDL_Error: " << SDL_GetError();
        return false;
    }
    *Renderer = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);
    if (*Renderer == NULL) {
        cout << "Failed to create renderer! SDL_Error " << SDL_GetError();
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Failed to initialize mixer! SDL_Error " << SDL_GetError();
        return false;
    } 
    return true;
}

void close(SDL_Window** Window, SDL_Renderer** Renderer) {
    SDL_DestroyWindow(*Window);
    *Window = NULL;
    Mix_FreeChunk(gPressButtonSound);
    gPressButtonSound = NULL;
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    SDL_DestroyRenderer(*Renderer);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void gameLoop(SDL_Renderer* Renderer) {
    Grid playground;
    bool quit = false;
    gMusic = Mix_LoadMUS(BG_MUSIC_PATH.c_str());
    gPressButtonSound = Mix_LoadWAV(BUTTON_SOUND_PATH.c_str());
    Mix_PlayMusic(gMusic, -1);
    SDL_Event e;
    while (!quit) {
        playground.generate(); playground.generate();
        playground.printGrid(Renderer, gFont);
        while (SDL_WaitEvent(&e)) {
            if (e.type == SDL_KEYUP || e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEBUTTONDOWN)
                continue;
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type = SDL_KEYDOWN) {
                SDL_Keycode Key = e.key.keysym.sym;
                if (Key == SDLK_q || Key == SDLK_n || Key == SDLK_m || Key == SDLK_SPACE) {
                    if (Key == SDLK_q)
                        return;
                    if (Key == SDLK_n) {
                        playground.clearGrid(Renderer);
                        break;
                    }
                    if (Key == SDLK_m) {
                        if (Mix_PlayingMusic() == 0)
                            Mix_PlayMusic(gMusic, -1);
                        else {
                            if (Mix_PausedMusic() == 1)
                                Mix_ResumeMusic();
                            else
                                Mix_PauseMusic();
                        }
                    }
                    if (Key == SDLK_SPACE) {
                        if (Mix_PlayingMusic() == 1)
                            Mix_HaltMusic();
                        else
                            Mix_PlayMusic(gMusic, -1);
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
                    Mix_PlayChannel(2, gPressButtonSound, 0);
                    playground.generate(); 
                    playground.printGrid(Renderer, gFont);
                }
            }
            if (playground.isGameOver()) {
                playground.printLose(Renderer, gFont);
                while (SDL_WaitEvent(&e) && (e.key.keysym.sym != SDLK_q || e.key.keysym.sym != SDLK_n)) {
                    if (e.key.keysym.sym == SDLK_q) return;
                    if (e.key.keysym.sym == SDLK_n) {
                        playground.clearGrid(Renderer);
                        playground.generate(); playground.generate();
                        playground.printGrid(Renderer, gFont);
                        break;
                    }
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