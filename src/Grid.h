#pragma once
#include "raylib.h"
#include <memory>
#include <vector>
#include "Tile.h"
#include "Button.h"

using namespace std;

class Grid{
    public:
        Grid(Point topLeft, int width, int height, vector<vector<int>> initBoard);
        void draw();
        void handleInput();
        bool solve(int row = 0, int col = 0);
        bool isSolved();
        void updateVisual();

    private:
        Point topLeft;
        const int gridHeight;
        const int gridWidth;
        const int cellSize;
        const int nRows = 9, nCols = 9;

        vector<vector<int>> board;
        vector<vector<int>> initialBoard;
        vector<shared_ptr<Tile>> tiles;
        shared_ptr<Tile> currentSelected;
        Button solveButton;
        Button resetButton;
        Button newBoardButton;

        void showSolved();
        bool autoSolved;
        bool congratulate;
    
};