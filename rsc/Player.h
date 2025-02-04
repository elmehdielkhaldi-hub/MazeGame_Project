#ifndef PLAYER_H
#define PLAYER_H

#pragma once

class Player
{
public:
    Player(int, int, Texture2D, int);
    void draw() const;
    void move(const Maze&);
    bool hasWon(const Maze&) const;

    // Add these getter methods
    int getX() const;
    int getY() const;

private:
    int x, y;
    Texture2D texture;
    int cellSize;
};

#endif
