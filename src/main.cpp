#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "../src/include/Grid.h"

using std::cin;
using std::cout;

int main() {
    srand(time(NULL));
    Grid playground;
    char input;
    
    playground.generate(); playground.generate();
    playground.printGrid();

    while (!playground.isGameOver()) {
        input = getche();
        // cin >> input;
        cout << "\n";
        if (input=='q') break;
        if (input=='n') { 
            playground.clearGrid();
            playground.generate(); playground.generate();
            playground.printGrid();
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
            }
            playground.generate();
            playground.printGrid();
        } 
    }
    return 0;
}