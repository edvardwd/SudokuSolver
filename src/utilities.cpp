#include "utilities.h"

using namespace std;

void printBoard(vector<vector<int>> board){
    //usleep(100000);
    system("clear");
    int n = sqrt(board.size());
    for (int i = 0; i < board.size(); i++){
        if (i % n == 0 && (i + 1) != board.size() && i != 0){
            cout << " +-------+-------+-------+" << endl;
        }
        for (int j = 0; j < board.size(); j++){
            if (j% n == 0 && (j + 1) != board.size()){
                cout << " |";
            }
            cout << " " << board.at(i).at(j);

        }
        cout << " |" << endl;
    }
    cout << endl;
}

unordered_set<int> getSquare(vector<vector<int>> board, int row, int col){
    unordered_set<int> square;
    int n = sqrt(board.size());
    for (int i = (row / n)*n; i < (row / n)*n + n; i++){
        for (int j = (col / n)*n; j < (col / n)*n + n; j++){
            square.emplace(board.at(i).at(j));
        }
    }
    return square;
}

unordered_set<int> getColumn(vector<vector<int>> board, int col){
    unordered_set<int> column;
    for (const auto& row : board){
        column.emplace(row.at(col));
    }
    return column;
}

bool isLegal(vector<vector<int>> board, int row, int col, int num){
    vector<int> rowVec = board.at(row);
    unordered_set<int> column = getColumn(board, col);
    unordered_set<int> square = getSquare(board, row, col);

    if (find(rowVec.begin(), rowVec.end(), num) != rowVec.end()){
        return false;
    }
    if (column.find(num) != column.end()){
        return false;
    }
    if (square.find(num) != square.end()){
        return false;
    }
    return true;
}


bool solve(vector<vector<int>>& board, int row, int col, bool print, bool randomOrder){
    //to-do: add check for more soultions, i.e., check for two solutions

    //for "guessing" in random order
    random_device rd;
    mt19937 generator(rd());
    vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(nums.begin(), nums.end(), generator);

    if (row == board.size()){
        return true;
    }
    else if (col == board.size()){
        return solve(board, row + 1, 0);
    }
    else if (board.at(row).at(col) != 0){
        return solve(board, row, col + 1);
    }
    else{
        for (int i = 1; i <= 9; i++){
            int k;
            k = randomOrder ? nums.at(i - 1) : i; //guesses in random or "proper" order
            if (isLegal(board, row, col, k)){
                board.at(row).at(col) = k;
                if (print) printBoard(board);

                if (solve(board, row, col)){
                    return true;
                }
                board.at(row).at(col) = 0; //undo
            }
        }
        return false;
    }
}

pair<int, int> getRandomCell(){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 8);

    return {distribution(generator), distribution(generator)};
}

vector<vector<int>> generateBoard(Difficulty difficulty){
    vector<vector<int>> board(9, vector<int>(9)); //empty board
    solve(board, 0, 0, true, true);
    
    int toRemove;
    if (difficulty == Difficulty::easy) toRemove = 44;
    else if (difficulty == Difficulty::medium) toRemove = 50;
    else toRemove = 60;

    while (toRemove > 0){
        auto [row, col]  = getRandomCell();
        if (board.at(row).at(col) != 0){
            board.at(row).at(col) = 0;
            toRemove--;
        }
    }
    vector<vector<int>> boardCopy = board;
    if (!solve(boardCopy)) return generateBoard(difficulty); //ensure that the board is solvable

    return board;
}
