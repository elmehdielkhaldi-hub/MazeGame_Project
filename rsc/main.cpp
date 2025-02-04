#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // For std::random_shuffle
#include "raylib.h"
#include <iostream>

// -------- Button Class --------
class button {
private:
    Texture2D texture;
    Vector2 position;
    float scale;
    bool isHovered;

public:
    button(const char* imagepath, Vector2 imageposition, float scaleFactor) {
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

    ~button() {
        UnloadTexture(texture);
    }

    void draw() {
        Color tintColor = isHovered ? RED : WHITE;
        DrawTextureEx(texture, position, 0.0f, 1.0f, tintColor);
    }

    bool ispressed(Vector2 mousePos, bool mousePressed) {
        Rectangle rect = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
        return CheckCollisionPointRec(mousePos, rect) && mousePressed;
    }

    void updateHoverState(Vector2 mousePos) {
        Rectangle rect = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
        isHovered = CheckCollisionPointRec(mousePos, rect);
    }
};

// -------- Maze Class --------
class Maze {
private:
    std::vector<std::vector<int>> maze;
    int width;
    int height;
    int cellSize;

    void generateMaze(int x, int y) {
        maze[x][y] = 0;  // Mark the current cell as a path
        int directions[] = {0, 1, 2, 3};
        std::random_shuffle(std::begin(directions), std::end(directions));

        for (int i = 0; i < 4; ++i) {
            int dx = 0, dy = 0;
            switch (directions[i]) {
                case 0: dy = -2; break;
                case 1: dx = 2; break;
                case 2: dy = 2; break;
                case 3: dx = -2; break;
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

public:
    Maze(int w, int h, int size) : width(w), height(h), cellSize(size), maze(w, std::vector<int>(h, 1)) {
        std::srand(std::time(0));
        generateMaze(1, 1);
    }

    void draw(Texture2D wallTexture, Texture2D pathTexture) const {
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

    bool isPath(int x, int y) const {
        return maze[x][y] == 0;
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// -------- Player Class --------
class Player {
private:
    int x, y;
    Texture2D texture;
    int cellSize;

    void adjustPosition() {
        // Prevent going out of bounds
        if (x < 0) x = 0;
        if (y < 0) y = 0;
    }

public:
    Player(int startX, int startY, Texture2D tex, int size) : x(startX), y(startY), texture(tex), cellSize(size) {}

    void draw() const {
        DrawTexture(texture, x * cellSize, y * cellSize, WHITE);
    }

    void move(const Maze& maze) {
        if (IsKeyPressed(KEY_UP) && maze.isPath(x, y - 1)) y--;
        if (IsKeyPressed(KEY_DOWN) && maze.isPath(x, y + 1)) y++;
        if (IsKeyPressed(KEY_LEFT) && maze.isPath(x - 1, y)) x--;
        if (IsKeyPressed(KEY_RIGHT) && maze.isPath(x + 1, y)) x++;
        adjustPosition();
    }

    bool hasWon(const Maze& maze) const {
        return x == maze.getWidth() - 2 && y == maze.getHeight() - 2;
    }
};

// -------- Main Function --------
const int WIDTH = 23;
const int HEIGHT = 23;
const int CELL_SIZE = 40;
const int RIGHT_PADDING = 200;

int main() {
    InitWindow(WIDTH * CELL_SIZE + RIGHT_PADDING, HEIGHT * CELL_SIZE, "Maze Game with Classes");
    SetTargetFPS(60);

    // Load textures with resizing
    Image wallImg = LoadImage("img/Tile_13-128x128.png");
    ImageResize(&wallImg, CELL_SIZE, CELL_SIZE);
    Texture2D wallTexture = LoadTextureFromImage(wallImg);
    UnloadImage(wallImg);

    Image pathImg = LoadImage("img/Grass_15-128x128.png");
    ImageResize(&pathImg, CELL_SIZE, CELL_SIZE);
    Texture2D pathTexture = LoadTextureFromImage(pathImg);
    UnloadImage(pathImg);

    Image playerImg = LoadImage("img/adventurer-slide-00.png");
    ImageResize(&playerImg, CELL_SIZE, CELL_SIZE);
    Texture2D playerTexture = LoadTextureFromImage(playerImg);
    UnloadImage(playerImg);

    Maze maze(WIDTH, HEIGHT, CELL_SIZE);
    Player player(1, 1, playerTexture, CELL_SIZE);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        maze.draw(wallTexture, pathTexture);
        player.move(maze);
        player.draw();

        if (player.hasWon(maze)) {
            DrawText("You Win!", WIDTH * CELL_SIZE / 2, HEIGHT * CELL_SIZE / 2, 100, RED);
        }

        EndDrawing();
    }

    UnloadTexture(wallTexture);
    UnloadTexture(pathTexture);
    UnloadTexture(playerTexture);
    CloseWindow();
    return 0;
}
