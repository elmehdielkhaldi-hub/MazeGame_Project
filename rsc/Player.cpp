#include "Player.h"

Player::Player(int startX, int startY, Texture2D tex, int size) 
    : x(startX), y(startY), texture(tex), cellSize(size) {}

void Player::draw() const {
    DrawTexture(texture, x * cellSize, y * cellSize, WHITE);
}

void Player::move(const Maze& maze) {
    if (IsKeyPressed(KEY_UP) && maze.isPath(x, y - 1)) y--;
    if (IsKeyPressed(KEY_DOWN) && maze.isPath(x, y + 1)) y++;
    if (IsKeyPressed(KEY_LEFT) && maze.isPath(x - 1, y)) x--;
    if (IsKeyPressed(KEY_RIGHT) && maze.isPath(x + 1, y)) x++;
}

bool Player::hasWon(const Maze& maze) const {
    return x == maze.getWidth() - 2 && y == maze.getHeight() - 2;
}

// Add these getters
int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}
