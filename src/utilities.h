#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "unistd.h"
#include <random>

using namespace std;

struct Point{
    int x;
    int y;
};

enum class Difficulty {easy, medium, hard};

void printBoard(vector<vector<int>> board);
unordered_set<int> getSquare(vector<vector<int>> board, int row, int col);
unordered_set<int> getColumn(vector<vector<int>> board, int col);
bool isLegal(vector<vector<int>> board, int row, int col, int num);
bool solve(vector<vector<int>>& board, int row = 0, int col = 0, bool print = false, bool randomOrder = false);
int countSolutions(vector<vector<int>>& board, int row = 0, int col = 0);
vector<vector<int>> generateBoard(Difficulty difficulty);