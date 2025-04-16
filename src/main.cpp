#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include "unistd.h"
#include "Grid.h"
#include "Tile.h"
#include "utilities.h"

using namespace std;


int main(){
    vector<vector<int>> board{{0, 2, 0, 0, 0, 0, 0, 0, 0},
            {1, 5, 8, 0, 0, 0, 0, 3, 0},
            {3, 4, 0, 1, 6, 0, 9, 0, 2},
            {0, 0, 9, 2, 0, 8, 1, 7, 5},
            {0, 0, 0, 0, 4, 0, 0, 0, 0},
            {0, 3, 5, 6, 0, 1, 0, 0, 0},
            {0, 0, 0, 3, 0, 0, 5, 9, 4},
            {5, 1, 3, 4, 8, 0, 0, 0, 7},
            {6, 9, 0, 7, 5, 2, 0, 0, 3}};
    
    Grid grid{{50, 50}, 500, 500, board};
    InitWindow(800, 600, "Sudoku");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        grid.handleInput();
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        grid.draw();
        EndDrawing();
        
    }
    CloseWindow();
    
    return 0;
}