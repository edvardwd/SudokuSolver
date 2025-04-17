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

    vector<vector<int>> board = generateBoard(Difficulty::easy);
    
    Grid grid{{50, 50}, 1000, 1000, board};
    InitWindow(1600, 1200, "Sudoku");
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