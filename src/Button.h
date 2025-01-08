#pragma once
#include "raylib.h"
#include "utilities.h"

class Button{
    public:
        Button(Point topLeft, int width, int height, string , Color color, bool outline);
        Button() = default;
        virtual void draw();
        bool isClicked();

    protected:
        int width, height;
        Point topLeft;
        Rectangle rect;
        string text;
        Color color;
        bool outline;

};