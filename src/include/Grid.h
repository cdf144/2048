#ifndef Grid_h
#define Grid_h

#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

const int GRID_SIZE = 4;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 500;
const int PADDING = 10;

const int DEFAULT_FONT_SIZE = 40;

bool init(SDL_Window** Window, SDL_Renderer** Renderer);
void close(SDL_Window** Window, SDL_Renderer** Renderer);


struct Grid {
    int* board[GRID_SIZE][GRID_SIZE];
    int score = 0;
    Grid();
    void addScore(int n);
    void printScore(SDL_Renderer* Renderer, TTF_Font* Font);
    void printGrid(SDL_Renderer* Renderer, TTF_Font* Font);
    void printLose(SDL_Renderer* Renderer, TTF_Font* Font);
    void generate();
    bool isGameOver();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void clearGrid(SDL_Renderer* Renderer);
    ~Grid();
};

#endif