#ifndef MAZE_H
#define MAZE_H

#pragma once

class Maze
{
public:

    Maze(int , int , int); 
        void draw(Texture2D wallTexture, Texture2D pathTexture) const;
        bool isPath(int , int ) const;
        int getWidth() const ;
        int getHeight() const;


private:


    std::vector<std::vector<int>> maze;
        int width;
        int height; 
        int cellSize;
        void generateMaze(int,int);
    
};

#endif