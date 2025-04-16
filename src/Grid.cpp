#include "Grid.h"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
// Define a dummy function when not compiling with Emscripten
static void emscripten_sleep(int ms) { /* no-op */ }
#endif


Grid::Grid(Point topLeft, int width, int height, vector<vector<int>> initBoard) : 
            topLeft{topLeft}, gridHeight{height}, gridWidth{width}, cellSize{width / 9}, board{initBoard},
            initialBoard{initBoard}, currentSelected{nullptr}, autoSolved{false} {
                this->solveButton = Button{{topLeft.x + (nRows + 1)*cellSize, topLeft.y + cellSize},
                                         cellSize*3, cellSize, "SOLVE", GREEN, true};
                this->resetButton = Button{{topLeft.x + (nRows + 1)*cellSize, topLeft.y + 2*cellSize},
                                         cellSize*3, cellSize, "RESET", ORANGE, true};
                this->newBoardButton = Button{{topLeft.x + (nRows + 1)*cellSize, topLeft.y + 3*cellSize},
                                         cellSize*3, cellSize, "NEW", BLUE, true};

                for (int i = 0; i < board.size(); i++){
                    for (int j = 0; j < board.at(0).size(); j++){
                        int tileX = topLeft.x + cellSize * j;
                        int tileY = topLeft.y + cellSize * i;
                        int val = board.at(i).at(j);
                        Color color = (val == 0) ? WHITE : RAYWHITE;

                        tiles.emplace_back(new Tile{{tileX, tileY}, cellSize,  color, i, j, val});
                    }
                } 
}

void Grid::draw(){
    // Draw the tiles
    for (const auto& tile : tiles){
        tile->draw();
    }

    // Draw lines
    for (int i = 0; i <= nRows; i++){
        Color color = LIGHTGRAY;
        if (i % 3 == 0 || i == 0 || i == nRows){
            color = DARKBROWN;
        }
        DrawLine(topLeft.x, topLeft.y + i * cellSize, topLeft.x + cellSize * nCols, topLeft.y + i * cellSize, color);
    }

    for (int j = 0; j <= nCols; j++){
        Color color = LIGHTGRAY;
        if (j % 3 == 0 || j == 0 || j == nCols){
            color = DARKBROWN;
        }
        DrawLine(topLeft.x + j * cellSize, topLeft.y, topLeft.x + j * cellSize, topLeft.y + nRows * cellSize, color);
    }

    // Draw buttons
    this->solveButton.draw();
    this->resetButton.draw();
    this->newBoardButton.draw();

    // Display congrats message if the board was solved manually
    if (this->congratulate){
        DrawText("Congratulions!\nBoard solved!", 
            topLeft.x + cellSize*(nRows+1), topLeft.y + cellSize * 4,
             cellSize * 0.5, DARKBROWN);
    }
}

void Grid::handleInput(){
    for (auto& tile : tiles){
        bool selected = tile->isClicked() && tile->changeable;
        if (selected && this->currentSelected == tile){
            this->currentSelected = nullptr;
            tile->setColor(WHITE);
            tile->setSelected(false);
        }
        else if (selected){
            if (this->currentSelected != nullptr){
                this->currentSelected->setSelected(false);
                this->currentSelected->setColor(WHITE);
                this->currentSelected->setValue(board.at(currentSelected->row).at(currentSelected->col));
            }
            this->currentSelected = tile;
            tile->setSelected(true);
            tile->setColor(LIGHTGRAY);
        }
    }
    if (this->currentSelected != nullptr){
        this->currentSelected->takeInput();
        if (IsKeyPressed(KEY_ENTER)){
            if (isLegal(board, currentSelected->row, currentSelected->col, currentSelected->getValue())){
                board.at(currentSelected->row).at(currentSelected->col) = currentSelected->getValue();
            } else{
                currentSelected->setValue(board.at(currentSelected->row).at(currentSelected->col));
            }
            currentSelected->setSelected(false);
            currentSelected->setColor(WHITE);
            currentSelected = nullptr;
        }
    }
    if (this->solveButton.isClicked()){
        this->solve();
        this->autoSolved = true;
        if (this->isSolved()){
            showSolved();
        }
        else{
            this->board = this->initialBoard;
            this->updateVisual();
            this->solve();
            if (this->isSolved()) showSolved();
            else cout << "Unsolvable board" << endl;
        }
    }

    if (this->resetButton.isClicked()){
        this->autoSolved = false;
        this->board = this->initialBoard;
        this->updateVisual();
    }

    if (this->newBoardButton.isClicked()){
        //To-do - make choice of difficulty available
        this->board = generateBoard(Difficulty::easy);
        this->initialBoard = this->board;
        //essentially a copy of the constructor
        this->tiles.clear();
        for (int i = 0; i < board.size(); i++){
            for (int j = 0; j < board.at(0).size(); j++){
                int tileX = topLeft.x + cellSize * j;
                int tileY = topLeft.y + cellSize * i;
                int val = board.at(i).at(j);
                Color color = (val == 0) ? WHITE : RAYWHITE;

                tiles.emplace_back(new Tile{{tileX, tileY}, cellSize,  color, i, j, val});
            }
        } 
        this->updateVisual(); 
    }
    
    this->congratulate = (this->isSolved() && !this->autoSolved) ? true : false;
    
}




bool Grid::solve(int row, int col){
    static int count = 0;
    emscripten_sleep(1);   // 1ms delay allows screen updates
    
    // Force redraw
    BeginDrawing();
    this->draw();
    ClearBackground(LIGHTGRAY);
    EndDrawing();


    if (row == board.size()){
        return true;
    }
    else if (col == board.size()){
        return solve(row + 1, 0);
    }
    else if (board.at(row).at(col) != 0){
        return solve(row, col + 1);
    }
    else{
        for (int k = 1; k <= board.size(); k++){
            if (isLegal(board, row, col, k)){
                board.at(row).at(col) = k;
                tiles.at(row * nRows + col)->setValue(k);
                tiles.at(row * nRows + col)->setColor(YELLOW);
                BeginDrawing();
                this->draw();
                EndDrawing();

                if (solve(row, col)){
                    return true;
                }
                board.at(row).at(col) = 0; //undo
                tiles.at(row * nRows + col)->setValue(0);
                tiles.at(row * nRows + col)->setColor(WHITE);
            }
        }
        return false;
    }
}

bool Grid::isSolved(){
    for (const auto& tile : tiles){
        if (tile->getValue() == 0){
            return false;
        }
    }
    return true;
}

void Grid::showSolved(){
    if (this->isSolved()){
        for (auto& tile : tiles){
            if (tile->changeable){
                tile->setColor(GREEN);
            }
        }
    }
}


void Grid::updateVisual(){
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < nCols; j++){
            this->tiles.at(i*nRows+ j)->setValue(this->board.at(i).at(j));
            if (this->tiles.at(i*nRows+ j)->changeable) this->tiles.at(i*nRows + j)->setColor(WHITE);
            else this->tiles.at(i*nRows+ j)->setColor(RAYWHITE);
        }
    }
}