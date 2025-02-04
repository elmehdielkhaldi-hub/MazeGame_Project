#include "Maze.h"

    Maze::Maze(int w, int h, int size) : width(w), height(h), cellSize(size), maze(w, std::vector<int>(h, 1)) {
            std::srand(std::time(0));
            generateMaze(1, 1);
        }

    void Maze::draw(Texture2D wallTexture, Texture2D pathTexture) const {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (maze[x][y] == 1) {
                    DrawTexture(wallTexture, x * cellSize, y * cellSize, WHITE);
                } else {
                    DrawTexture(pathTexture, x * cellSize, y * cellSize, WHITE);
                }
            }
        }
    }
        void  Maze::generateMaze(int x, int y) {
                maze[x][y] = 0;  // Mark the current cell as a path
                int directions[] = {0, 1, 2, 3};  // Directions: Up, Right, Down, Left
                std::random_shuffle(std::begin(directions), std::end(directions));

                for (int i = 0; i < 4; ++i) {
                    int dx = 0, dy = 0;
                    switch (directions[i]) {
                        case 0: dy = -2; break;  // Up
                        case 1: dx = 2; break;   // Right
                        case 2: dy = 2; break;   // Down
                        case 3: dx = -2; break;  // Left
                    }

                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && maze[nx][ny] == 1) {
                        maze[x + dx / 2][y + dy / 2] = 0;
                        maze[nx][ny] = 0;
                        generateMaze(nx, ny);
                    }
                }
            }
        bool Maze:: isPath(int x, int y) const {
                return maze[x][y] == 0;
            }

            int Maze:: getWidth() const { return width; }
            int Maze::getHeight() const { return height; }

