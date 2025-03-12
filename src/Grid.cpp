#include "Grid.h"


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
    for (const auto& tile : tiles){
        tile->draw();
    }

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
    this->solveButton.draw();
    this->resetButton.draw();
    this->newBoardButton.draw();
}

void Grid::handleInput(){
    for (auto& tile : tiles){
        bool selected = tile->isClicked() && tile->changeable;
        if (selected && this->currentSelected == tile){
            this->currentSelected = nullptr;
            tile->setColor(WHITE);
            tile ->setSelected(false);
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
    /*
    if (this->isSolved() && !this->autoSolved){
        cout << "Congratulations, you solved the board!" << endl;
    }
    */
}




bool Grid::solve(int row, int col){
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