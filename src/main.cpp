#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;

const int GRID_SIZE = 4;

class Grid {
    public:
        int* board[GRID_SIZE][GRID_SIZE];
        Grid() {
            for (int i=0; i<GRID_SIZE; i++) {
                for (int j=0; j<GRID_SIZE; j++)
                    board[i][j] = NULL;
            }
        }

        void setTileVal (int val, int row, int col) {
            board[row][col] = new int;
            *board[row][col] = val;
        }

        void merge(int row, int col) {
            *board[row][col] *= 2;
        }
        
        void printGrid() {
            for (int i=0; i<GRID_SIZE; i++) {
                for (int j=0; j<GRID_SIZE; j++) {
                    if (board[i][j] == NULL) cout << "-" << ' ';
                    else cout << *board[i][j] << ' ';
                } 
                cout << "\n";
            }
            cout << "\n";
        }
        
        void generate() {
            while (true) {
                int row = rand()%4;
                int col = rand()%4;
                if (board[row][col] == NULL) {
                    board[row][col] = new int;
                    *board[row][col] = 2;
                    break;
                }
            }
        }

        bool isEmptyTile (int row, int col) {
            if (board[row][col] == NULL) return true;
            else return false;
        }

        bool isGameOver() {
            int countEmptyTiles = 0;
            for (int i=0; i<GRID_SIZE; i++) {
                for (int j=0; j<GRID_SIZE; j++) {
                    if (board[i][j] == NULL)
                        countEmptyTiles++;
                    else if (*board[i][j] == 2048)
                        return true;
                }
            }
            if (countEmptyTiles != 0) return false;
            return true;
        }

        ~Grid() {
            for (int i=0; i<GRID_SIZE; i++) {
                for (int j=0; j<GRID_SIZE; j++)
                    delete board[i][j];
            }
            cout << "Grid destroyed" << std::endl;
        }
};

int main() {
    srand(time(NULL));
    Grid playground;
    while (!playground.isGameOver()) {
        playground.generate();
        playground.printGrid();
    }
    return 0;
}