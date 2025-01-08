#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "unistd.h"

using namespace std;

struct Point{
    int x;
    int y;
};

void printBoard(vector<vector<int>> board);
unordered_set<int> getSquare(vector<vector<int>> board, int row, int col);
unordered_set<int> getColumn(vector<vector<int>> board, int col);
bool isLegal(vector<vector<int>> board, int row, int col, int num);
bool solve(vector<vector<int>>& board, int row = 0, int col = 0);