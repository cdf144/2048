## **INT2215 Advanced Programming Class Personal Project**
## ***2048***
### General Game Information<sup>[Wikipedia](https://en.wikipedia.org/wiki/2048_(video_game))<sup>
- 2048 is a puzzle game played on a 4x4 grid, with numbered tiles that slide when the player moves them in one of the four possible directions.
- Every turn, a new tile randomly appears in an empty spot on the board with a value of either 2 or 4
- Tiles slide as far as possible in the chosen direction until they are stopped by either another tile or the edge of the grid. If two tiles of the same number collide while moving, they will merge into a tile with the total value of the two tiles that collided. The resulting tile cannot merge with another tile again in the same move.
- If a move causes three consecutive tiles of the same value to slide together, only the two tiles farthest along the direction of motion will combine. If all four spaces in a row or column are filled with tiles of the same value, a move parallel to that row/column will combine the first two and last two.
- The game is won when a tile with a value of 2048 appears on the board.

### Game Features
- A functioning 2048 game on console
- Winning announcement *(TBA)*
- Scoreboard & a way to create a New Game *(TBA)*
- Graphics on a separate window with SDL *(WIP)* *(Top Priority)*

### Building from Source
As of now the program as well as the building process are only tested on Windows 10

Make sure gcc/g++ compiler have been set as PATH.
Since we are going to compile the project using `make`, make sure to modify `INCLUDE_PATHS` and `LIBRARY_PATHS` in `Makefile` so that it is appropiate with where you put the dependencies (SDL2) in your system.
```
make
.\2048.exe
```
SHA1 Hash: `c63086534caa8b9beef3d780145196f5e129a70e`