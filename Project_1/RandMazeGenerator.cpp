#include "RandMazeGenerator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <random>

using namespace std;

// Constructor for RandomMazeGenerator
RandomMazeGenerator::RandomMazeGenerator(int rows, int cols) : rows(rows), cols(cols), maze(rows, vector<Cell>(cols)) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            maze[y][x] = Cell(x, y);
        }
    }
}


void RandomMazeGenerator::generateMaze() {
    random_device rd;
    mt19937 gen(rd()); // this function is very interesting since it doesnt generate single random value like srand time, it always recreate a random number
    cellStack.push(make_pair(0, 0));
    maze[0][0].visited = true;
    int visitedCells = 1;

    while (visitedCells < rows * cols) {
        auto currentCell = cellStack.top();
        int x = currentCell.first;
        int y = currentCell.second;

        vector<pair<int, int>> unvisitedNeighbors;

        // Add unvisited neighbors for each cell to vector including int pairs
        // Left neighbor
        if (x > 0 && !maze[y][x - 1].visited) {
            unvisitedNeighbors.push_back(make_pair(x - 1, y));
        }
        // Right neighbor
        if (x < cols - 1 && !maze[y][x + 1].visited) {
            unvisitedNeighbors.push_back(make_pair(x + 1, y));
        }
        // Up neighbor
        if (y < rows - 1 && !maze[y + 1][x].visited) {
            unvisitedNeighbors.push_back(make_pair(x, y + 1));
        }
        // Down neighbor
        if (y > 0 && !maze[y - 1][x].visited) {
            unvisitedNeighbors.push_back(make_pair(x, y - 1));
        }

        if (!unvisitedNeighbors.empty()) {
            int randomIndex = gen() % unvisitedNeighbors.size();
            auto nextCell = unvisitedNeighbors[randomIndex];
            int nextX = nextCell.first;
            int nextY = nextCell.second;

            // Knock down the wall between currentCell and nextCell
            if (nextX < x) {
                // nextCell is to the left of currentCell
                maze[y][x].leftWall = false;
                maze[nextY][nextX].rightWall = false;
            }
            else if (nextX > x) {
                // nextCell is to the right of currentCell
                maze[y][x].rightWall = false;
                maze[nextY][nextX].leftWall = false;
            }
            else if (nextY > y) {
                // nextCell is below currentCell
                maze[y][x].upWall = false;
                maze[nextY][nextX].downWall = false;
            }
            else if (nextY < y) {
                // nextCell is above currentCell
                maze[y][x].downWall = false;
                maze[nextY][nextX].upWall = false;
            }

            // Mark nextCell as visited and push it to the stack
            maze[nextY][nextX].visited = true;
            cellStack.push(nextCell);
            visitedCells++;
        }
        else {
            // If there are no unvisited neighbors, backtrack
            cellStack.pop();
        }
    }
}



// Method to print the maze
void RandomMazeGenerator::printMaze() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Cell (" << maze[i][j].x << ", " << maze[i][j].y << "): ";
            cout << "L=" << maze[i][j].leftWall << ", ";
            cout << "R=" << maze[i][j].rightWall << ", ";
            cout << "U=" << maze[i][j].upWall << ", ";
            cout << "D=" << maze[i][j].downWall << endl;
        }
    }
}

// Method to print the path from the start to end cell
void RandomMazeGenerator::printPath(int startX, int startY, int endX, int endY) const {
    const Cell* currentCell = &maze[endY][endX];
    cout << "Path from (" << startX << "," << startY << ") to (" << endX << "," << endY << "): " << endl;

    while (currentCell) {
        cout << "(" << currentCell->x << "," << currentCell->y << ") <- ";
        currentCell = currentCell->previousCell;
    }
    cout << "Start" << endl;
}
void RandomMazeGenerator::writeMazeToFile(int mazeID) const {
    ofstream outFile;
    string filename = "maze_" + to_string(mazeID) + ".txt";
    outFile.open(filename);

    // First, write the size of the maze6
    outFile << rows << " " << cols << endl;

    // Then, write each cell's details
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outFile << "x=" << maze[i][j].x << " "
                << "y=" << maze[i][j].y << " "
                << "l=" << maze[i][j].leftWall << " "
                << "r=" << maze[i][j].rightWall << " "
                << "u=" << maze[i][j].upWall << " "
                << "d=" << maze[i][j].downWall << endl;
        }
    }

    outFile.close();
}