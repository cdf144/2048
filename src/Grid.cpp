#include "../src/include/Grid.h"

using std::cin;
using std::cout;

Grid::Grid() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            board[i][j] = NULL;
    }
}

void Grid::addScore(int n) {
    score += n;
}
    
void Grid::printGrid(SDL_Renderer* Renderer, TTF_Font* Font) {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++) {
            SDL_Rect rect = {j*100, i*100, 100, 100};
            if (board[i][j] != NULL) {
                int number = *board[i][j];
                SDL_SetRenderDrawColor(Renderer, (100+(2*(number/4)))%256, (240-(3*number))%256, (240-(5*number))%256, 255);
                SDL_RenderFillRect(Renderer, &rect);
                SDL_Surface* surface = NULL;
				SDL_Texture* texture = NULL;
                SDL_Color White = {255, 255, 255, 255};
				surface = TTF_RenderText_Blended(Font, (std::to_string(number)).c_str(), White);
				texture = SDL_CreateTextureFromSurface(Renderer, surface);
				int number_w, number_h;
				SDL_QueryTexture(texture, NULL, NULL, &number_w, &number_h);
				SDL_Rect numberRect = {100*j + ((100 - number_w)/2), 100*i + ((100 - number_h)/2), number_w, number_h};
                SDL_RenderCopy(Renderer, texture, NULL, &numberRect);
				SDL_FreeSurface(surface);
				SDL_DestroyTexture(texture);
            } else {
                SDL_SetRenderDrawColor(Renderer, 187, 173, 160, 255);
                SDL_RenderFillRect(Renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(Renderer);
}

bool Grid::win() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            if (board[i][j] != NULL && *board[i][j] == 2048)
                return true;
    }
    return false;
}
    
void Grid::generate() {
    int countEmptyTiles = 0;
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            if (board[i][j] == NULL)
                ++countEmptyTiles;
    }
    if (countEmptyTiles == 0) return;
    else {
        while (true) {
            int row = rand()%4;
            int col = rand()%4;
            if (board[row][col] == NULL) {
                board[row][col] = new int;
                *board[row][col] = ((rand()%5) == 4 ? 4 : 2);
                break;
            }
        }
    }
}

bool Grid::isGameOver() {
    int countEmptyTiles = 0;
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            if (board[i][j] == NULL)
                ++countEmptyTiles;
    }
    if (countEmptyTiles != 0) return false;
    else {
        for (int i=0; i<GRID_SIZE; i++) {
            for (int j=0; j<GRID_SIZE; j++) {
                if (board[i][j] != NULL) {
                    if (j < 3 && board[i][j+1] != NULL)
                        if (*board[i][j] == *board[i][j+1])
                            return false;
                    if (j > 0 && board[i][j-1] != NULL)
                        if (*board[i][j] == *board[i][j-1])
                            return false; 
                    if (i < 3 && board[i+1][j] != NULL)
                        if (*board[i][j] == *board[i+1][j])
                            return false;
                    if (i > 0 && board[i-1][j] != NULL)
                        if (*board[i][j] == *board[i-1][j])
                            return false;
                }
            }
        }
    }
    return true;
}

void Grid::moveRight() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=3; j>=0; j--) {
            if (board[i][j] == NULL) {
                for (int k=j-1; k>=0; k--) {
                    if (board[i][k] != NULL) {
                        board[i][j] = board[i][k];
                        board[i][k] = NULL;
                        break;
                    }
                }
                for (int k=j-1; k>=0; k--) {
                    if (board[i][k] != NULL) {
                        if (*board[i][k] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[i][k] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
            else {
                for (int k=j-1; k>=0; k--) {
                    if (board[i][k] != NULL) {
                        if (*board[i][k] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[i][k] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}
void Grid::moveLeft() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++) {
            if (board[i][j] == NULL) {
                for (int k=j+1; k<GRID_SIZE; k++) {
                    if (board[i][k] != NULL) {
                        board[i][j] = board[i][k];
                        board[i][k] = NULL;
                        break;
                    }
                }
                for (int k=j+1; k<GRID_SIZE; k++) {
                    if (board[i][k] != NULL) {
                        if (*board[i][k] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[i][k] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
            else {
                for (int k=j+1; k<GRID_SIZE; k++) {
                    if (board[i][k] != NULL) {
                        if (*board[i][k] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[i][k] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}
void Grid::moveUp() {
    for (int j=0; j<GRID_SIZE; j++) {
        for (int i=0; i<GRID_SIZE; i++) {
            if (board[i][j] == NULL) {
                for (int k=i+1; k<GRID_SIZE; k++) {
                    if (board[k][j] != NULL) {
                        board[i][j] = board[k][j];
                        board[k][j] = NULL;
                        break;
                    }
                }
                for (int k=i+1; k<GRID_SIZE; k++) {
                    if (board[k][j] != NULL) {
                        if (*board[k][j] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[k][j] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
            else {
                for (int k=i+1; k<GRID_SIZE; k++) {
                    if (board[k][j] != NULL) {
                        if (*board[k][j] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[k][j] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}        
void Grid::moveDown() {
    for (int j=0; j<GRID_SIZE; j++) {
        for (int i=3; i>=0; i--) {
            if (board[i][j] == NULL) {
                for (int k=i-1; k>=0; k--) {
                    if (board[k][j] != NULL) {
                        board[i][j] = board[k][j];
                        board[k][j] = NULL;
                        break;
                    }
                }
                for (int k=i-1; k>=0; k--) {
                    if (board[k][j] != NULL) {
                        if (*board[k][j] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[k][j] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
            else {
                for (int k=i-1; k>=0; k--) {
                    if (board[k][j] != NULL) {
                        if (*board[k][j] == *board[i][j]) {
                            *board[i][j] = (*board[i][j])<<1;
                            addScore(*board[i][j]);
                            board[k][j] = NULL;
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Grid::clearGrid(SDL_Renderer* Renderer) {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            board[i][j] = NULL;
    }
    score = 0;
	SDL_RenderClear(Renderer);
}

Grid::~Grid() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            delete board[i][j];
    }
}