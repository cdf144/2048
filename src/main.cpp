#include <iostream>

using std::cin;
using std::cout;

const int GRID_SIZE = 4;

class Tile {
    public:
        int val{ 0 };
};

class Grid {
    public:
        Tile* board[GRID_SIZE][GRID_SIZE];
        Grid() {
            for (int i=0; i<GRID_SIZE; i++) {
                for (int j=0; j<GRID_SIZE; j++)
                    board[i][j] = NULL;
            }
        }

        void insertTileVal(int val, int row, int col) {
            board[row][col] = new Tile;
            board[row][col]->val = val;
        }
        
        void printGrid() {
            for (int i=0; i<GRID_SIZE; i++) {
                for (int j=0; j<GRID_SIZE; j++) {
                    if (board[i][j] == NULL) cout << "-" << ' ';
                    else cout << board[i][j]->val << ' ';
                } 
                cout << "\n";
            }
        }
        ~Grid() {
            for (int i=0; i<GRID_SIZE; i++) {
                for (int j=0; j<GRID_SIZE; j++)
                    delete board[i][j];
            }
            cout << "Grid destroyed" << std::endl;
        }
};



bool isGameOver() {return 1;}

int main() {
    Grid playground;
    playground.printGrid();
    return 0;
}