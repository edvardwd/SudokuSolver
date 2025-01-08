#include "Tile.h"


using namespace std;

Tile::Tile(Point topLeft, int cellSize, Color color, int row, int col, int val) :
                cellSize{cellSize}, row{row}, col{col}, value{val}, selected{false},
                Button::Button(topLeft, cellSize, cellSize, "", color, false){   
                    this->rect =  Rectangle{float(topLeft.x), float(topLeft.y), float(cellSize), float(cellSize)};
                    this->changeable = (value == 0) ? true : false;
                }

void Tile::draw(){
    DrawRectangleRec(rect, this->color);

    string text = (this->value == 0) ? " " : to_string(this->value);
    int fontSize = cellSize * 0.6;

    int textWidth = MeasureText(text.c_str(), fontSize);
    int textX = topLeft.x + (cellSize - textWidth) / 2;
    int textY = topLeft.y + (cellSize - fontSize) / 2;
    
    DrawText(text.c_str(), textX, textY, fontSize, BLACK);
}

void Tile::setValue(int val){
    this->value = val;
}

int Tile::getValue(){
    return this->value;
}

Color Tile::getColor(){
    return this->color;
}

void Tile::setColor(Color color){
    this->color = color;
}

void Tile::setSelected(bool selected){
    this->selected = selected;
}

/*
bool Tile::isClicked(){
    Vector2 mousePos = GetMousePosition();
    bool pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool hover = CheckCollisionPointRec(mousePos, this->rect);
    return (hover && pressed && this->changeable) ? true : false;
}
*/

void Tile::takeInput(){
    int key = GetCharPressed();
    if (key >= 48 && key <= 57){
        this->value = key - 48;
    }
    else if (IsKeyPressed(KEY_BACKSPACE)){
        this->value = 0;
    }
}
