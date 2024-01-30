#pragma once
#include "stack.h"
#include <vector>
#include <utility>

using namespace std;

class Cell {
public:
    int x, y;
    bool leftWall, rightWall, upWall, downWall;
    bool visited;
    Cell* previousCell;


    Cell() : x(0), y(0), leftWall(true), rightWall(true), upWall(true), downWall(true), visited(false), previousCell(nullptr) {}
    Cell(int x, int y) : x(x), y(y), leftWall(true), rightWall(true), upWall(true), downWall(true), visited(false), previousCell(nullptr) {}
};

class RandomMazeGenerator {
private:
    int rows, cols;
    Stack<pair<int, int>> cellStack;

public:
    vector<vector<Cell>> maze;

    RandomMazeGenerator(int rows, int cols);
    void generateMaze();
    void printMaze() const;
    void printPath(int startX, int startY, int endX, int endY) const;
    void writeMazeToFile(int mazeID) const;
};


class MazeSolver {
private:
    Stack<Cell> cellStack;
    int mazeID;
    bool pushFirstAvailableNeighborToStack(vector<vector<Cell>>& maze, int x, int y);
    

public:
    MazeSolver(int mazeID, vector<vector<Cell>> maze, int startX, int startY, int endX, int endY); // mazeID => maze => cellStack constr
};