#include <iostream>
#include <cstdlib>
#include "Grid.h"

using std::cin;
using std::cout;

Grid::Grid() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            board[i][j] = NULL;
    }
}
    
void Grid::printGrid() {
    system("cls");
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++) {
            if (board[i][j] == NULL) cout << "-" << "    ";
            else {
                if (*board[i][j] < 10)
                    cout << *board[i][j] << "    ";
                if (*board[i][j] >= 10 && *board[i][j] < 100)
                    cout << *board[i][j] << "   ";
                if (*board[i][j] >= 100 && *board[i][j] < 1000)
                    cout << *board[i][j] << "  ";
                if (*board[i][j] >= 1000)
                    cout << *board[i][j] << " ";
            }
        } 
        cout << "\n";
    }
    cout << "\n";
    cout << "Use WASD to move, Press 'q' to quit: ";
}
    
void Grid::generate() {
    int countEmptyTiles = 0;
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            if (board[i][j] == NULL)
                ++countEmptyTiles;
    }
    if (countEmptyTiles == 0) cout << "Try a different move" << std::endl;
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

Grid::~Grid() {
    for (int i=0; i<GRID_SIZE; i++) {
        for (int j=0; j<GRID_SIZE; j++)
            delete board[i][j];
    }
    cout << "Grid destroyed" << std::endl;
}