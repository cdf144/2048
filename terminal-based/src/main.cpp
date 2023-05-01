#include <conio.h>
#include "../src/include/Grid.h"

using std::cin;
using std::cout;

void gameLoop() {
    Grid playground;
    char input;
    
    while (true) {
        playground.generate(); playground.generate();
        playground.printGrid();
        while (true) {
            input = getche();
            // cin >> input;
            cout << "\n";
            if (input=='q') 
                return;
            if (input=='n') { 
                playground.clearGrid();
                break;
            }
            if (input=='w' || input=='a' || input=='s' || input=='d') {
                switch (input) {
                case 'w':
                    playground.moveUp();
                    break;
                case 'a':
                    playground.moveLeft();
                    break;
                case 's':
                    playground.moveDown();
                    break;
                case 'd':
                    playground.moveRight();
                    break;
                default:
                    break;
                }
                if (playground.isGameOver()) {
                    cout << "You lost! Press 'n' to create a New Game: ";
                    while (input!='q' && input!='n') {
                        input = getche();
                        if (input=='q')
                            return;
                        if (input=='n') { 
                            playground.clearGrid();
                            playground.generate();
                            break;
                        }
                    }
                }
                playground.generate();
                playground.printGrid();
            }
            
        }
    }
}

int main() {
    srand(time(NULL));
    gameLoop();
    return 0;
}