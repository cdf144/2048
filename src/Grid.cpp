#include "../src/include/Grid.h"

using std::cin;
using std::cout;

SDL_Color White = {255, 255, 255, 255};

Grid::Grid() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            board[i][j] = NULL;
    }
}

void Grid::addScore(int n) {
    score += n;
}

void Grid::printScore(SDL_Renderer* Renderer, TTF_Font* Font) {
    std::string scoreString = "Score: " + std::to_string(score);
    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;
    scoreSurface = TTF_RenderText_Blended(Font, scoreString.c_str(), White);
    scoreTexture = SDL_CreateTextureFromSurface(Renderer, scoreSurface);
    int score_w, score_h;
	SDL_QueryTexture(scoreTexture, NULL, NULL, &score_w, &score_h);
    SDL_Rect scoreRect = {(400-score_w)/2, 400 + ((100-score_h)/2), score_w, score_h};
    SDL_Rect scoreBackgroundRect = {0, 400, 400, 100};
    SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(Renderer, &scoreBackgroundRect);
	SDL_RenderCopy(Renderer, scoreTexture, NULL, &scoreRect);
	SDL_FreeSurface(scoreSurface);
	SDL_DestroyTexture(scoreTexture);
}
    
void Grid::printGrid(SDL_Renderer* Renderer, TTF_Font* Font) {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++) {
            SDL_Rect tileRect = {j*100, i*100, 100, 100};
            SDL_Rect tileRectWithPadding = {j*100 + PADDING, i*100 + PADDING, 100 - PADDING*2, 100 - PADDING*2};
            SDL_SetRenderDrawColor(Renderer, 187, 173, 160, 255);
            SDL_RenderFillRect(Renderer, &tileRect);
            if (board[i][j] != NULL) {
                int number = *board[i][j];
                SDL_SetRenderDrawColor(Renderer, (122+(2*(number/4)))%256, (122-(number/4))%256, (122-(number/4))%256, 255);
                SDL_RenderFillRect(Renderer, &tileRectWithPadding);
                SDL_Surface* numberSurface = NULL;
				SDL_Texture* numberTexture = NULL;
				numberSurface = TTF_RenderText_Blended(Font, (std::to_string(number)).c_str(), White);
				numberTexture = SDL_CreateTextureFromSurface(Renderer, numberSurface);
				int number_w, number_h;
				SDL_QueryTexture(numberTexture, NULL, NULL, &number_w, &number_h);
				SDL_Rect numberRect = {100*j + ((100 - number_w)/2), 100*i + ((100 - number_h)/2), number_w, number_h};
                SDL_RenderCopy(Renderer, numberTexture, NULL, &numberRect);
				SDL_FreeSurface(numberSurface);
				SDL_DestroyTexture(numberTexture);
            }
        }
    }
    printScore(Renderer, Font);
    SDL_RenderPresent(Renderer);
}

void Grid::printLose(SDL_Renderer* Renderer, TTF_Font* Font) {
    SDL_Surface* loseSurface;
    SDL_Texture* loseTexture;
    loseSurface = TTF_RenderText_Blended(Font, "Game Over.", White);
    loseTexture = SDL_CreateTextureFromSurface(Renderer, loseSurface);
    int lose_w, lose_h;
	SDL_QueryTexture(loseTexture, NULL, NULL, &lose_w, &lose_h);
    SDL_Rect loseRect = {((SCREEN_WIDTH - lose_w)/2), ((SCREEN_HEIGHT - lose_h)/2), lose_w, lose_h};
    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(Renderer, 10, 10, 10, 255);
    SDL_RenderFillRect(Renderer, &screenRect);
	SDL_RenderCopy(Renderer, loseTexture, NULL, &loseRect);
	SDL_FreeSurface(loseSurface);
	SDL_DestroyTexture(loseTexture);
    SDL_RenderPresent(Renderer);
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