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
                board.at(row).at(col) = 0; //backtrack
            }
        }
        return false;
    }
}

int countSolutions(vector<vector<int>>& board, int row, int col){
    if (row == 9) return 1; //filled board -> count 1 solution
    if (col == 9) return countSolutions(board, row + 1, 0);
    if (board[row][col] != 0) return countSolutions(board, row, col + 1);

    int totalSolutions = 0;   
    for (int i = 1; i <= 9; i++){
        if (isLegal(board, row, col, i)){
            board[row][col] = i;
            totalSolutions += countSolutions(board, row, col);
            board[row][col] = 0; //backtrack

            // Exit early if more than one solution is found
            if (totalSolutions > 1) return totalSolutions; 
        }
    }
    return totalSolutions;
}


vector<vector<int>> generateBoard(Difficulty difficulty){
    vector<vector<int>> board(9, vector<int>(9)); //empty board
    solve(board, 0, 0, false, true); //ensures a "random board"
    
    int toRemove;
    if (difficulty == Difficulty::easy) toRemove = 44;
    else if (difficulty == Difficulty::medium) toRemove = 50;
    else toRemove = 60;

    //Create a vector of all cells shuffled
    vector<pair<int, int>> cells;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cells.push_back({i, j});
        }
    }
    random_device rd;
    mt19937 generator(rd());
    shuffle(cells.begin(), cells.end(), generator);

    int removed = 0;
    for (auto [row, col] : cells){
        if (board[row][col] != 0){
            int backup = board[row][col];
            board[row][col] = 0;

            vector<vector<int>> boardCopy = board;
            if (countSolutions(boardCopy) == 1){
                removed++;
                if (removed == toRemove) break; // removed enough cells
            }
            else{
                // no unique solution -> backtrack
                //cout << "No unique!" << endl;
                board[row][col] = backup;
            }
        }
    }

    return board;
}