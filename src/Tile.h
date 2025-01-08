#pragma once
#include "raylib.h"
#include "utilities.h"
#include "Button.h"

class Tile : public Button{
    public:
        Tile(Point topLeft, int cellsize, Color color, int row, int col, int val = 0);

        int row, col;
        bool changeable;

        void draw() override;
        void setValue(int val);
        void setColor(Color color);
        void setSelected(bool selected);
        void takeInput();
        
        int getValue();
        Color getColor();



    private:
        int cellSize;
        int value;
        bool selected;

        
};