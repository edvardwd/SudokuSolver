#include "Button.h"

Button::Button(Point topLeft, int width, int height, string text, Color color, bool outline) : 
            topLeft{topLeft}, text{text}, width{width}, height{height}, color{color}, outline{outline}{
    this->rect = Rectangle{(float) topLeft.x, (float) topLeft.y, (float) width, (float) height};
}

void Button::draw(){
    DrawRectangleRec(rect, this->color);
    int fontSize = height * 0.6;
    int textWidth = MeasureText(text.c_str(), fontSize);
    int textX = topLeft.x + (width - textWidth) / 2;
    int textY = topLeft.y + (height - fontSize) / 2;
    DrawText(text.c_str(), textX, textY, fontSize, RAYWHITE);
    if (outline) DrawRectangleLines(topLeft.x, topLeft.y, width, height, BLACK);
}


bool Button::isClicked(){
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, this->rect)){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return true;
        }
    }
    return false;
}
