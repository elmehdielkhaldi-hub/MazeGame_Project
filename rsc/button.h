// button.h
#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

class button {
private:
    Texture2D texture;
    Vector2 position;
    float scale;
    bool isHovered;

public:
    button(const char* imagepath, Vector2 imageposition, float scaleFactor);
    ~button();

    void draw();
    bool ispressed(Vector2 mousePos, bool mousePressed);
    void updateHoverState(Vector2 mousePos);
};

#endif // BUTTON_H
