// button.cpp
#include "button.h"
#include <iostream>

button::button(const char* imagepath, Vector2 imageposition, float scaleFactor) {
    Image image = LoadImage(imagepath);
    int originalWidth = image.width;
    int originalHeight = image.height;
    int newWidth = static_cast<int>(originalWidth * scaleFactor);
    int newHeight = static_cast<int>(originalHeight * scaleFactor);
    ImageResize(&image, newWidth, newHeight);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = imageposition;
    scale = scaleFactor;
    isHovered = false;

    if (texture.id == 0) {
        std::cerr << "Error loading texture: " << imagepath << std::endl;
    }
}

button::~button() {
    UnloadTexture(texture);
}

void button::draw() {
    Color tintColor = isHovered ? RED : WHITE;
    DrawTextureEx(texture, position, 0.0f, 1.0f, tintColor);
}

bool button::ispressed(Vector2 mousePos, bool mousePressed) {
    Rectangle rect = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    return CheckCollisionPointRec(mousePos, rect) && mousePressed;
}

void button::updateHoverState(Vector2 mousePos) {
    Rectangle rect = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    isHovered = CheckCollisionPointRec(mousePos, rect);
}
