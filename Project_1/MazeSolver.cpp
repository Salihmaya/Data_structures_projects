#include "RandMazeGenerator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <random>

using namespace std;

// Constructor for MazeSolver
MazeSolver::MazeSolver(int mazeID, vector<vector<Cell>> maze, int startX, int startY, int endX, int endY)
    : mazeID(mazeID) {

    // make all cells not visited
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            maze[i][j].visited = false;
        }
    }


    vector<pair<int, int>> solution;
    auto cell = maze[startY][startX];
    cell.visited = true; // Mark the start cell as visited
    cellStack.push(cell);
    bool solved = false;

    while (!cellStack.isEmpty()) {
        Cell cell = cellStack.top(); // Get the top cell in the stack
        int x = cell.x;
        int y = cell.y;
        // cout << x << " " << y;
        if (x == endX && y == endY) {
            // Found the solution
            solved = true;
            break;
        }
        // cellStack.pop(); // Remove the cell from the stack after processing
        while (!pushFirstAvailableNeighborToStack(maze, x, y)) // Push the first available neighbor
        {

            cellStack.pop();
            x = cellStack.top().x;
            y = cellStack.top().y;
        }
    }

    if (solved) {
        // while not stack empty, save it to a vector
        while (!cellStack.isEmpty()) {
            pair<int, int> step = make_pair(cellStack.top().x, cellStack.top().y);
            solution.push_back(step);
            cellStack.pop();
        }

        // write each element of vector to a file in the reverse order to indicate exact path
        // consider the maze solving order starting from the entry x and y and reaching to endX and Y
        ofstream outFile("maze_solution_path_" + to_string(startX) +"_"+ to_string(startY) + "_" + to_string(endX) + "_"+ to_string(endY) + ".txt");
        if (outFile.is_open()) {
            for (auto it = solution.rbegin(); it != solution.rend(); ++it) {
                outFile  << it->first <<" "<< it->second << endl;
            }
            outFile.close();
        }
        else {
            cerr << "Unable to open file to write the solution." << endl;
        }
    }
    else {
        cerr << "No solution found for the maze with ID " << mazeID << endl;
    }
}


bool MazeSolver::pushFirstAvailableNeighborToStack(vector<vector<Cell>>& maze, int x, int y) {

    // Assuming that 'rows' and 'cols' are the dimensions of the maze
    int rows = maze.size();
    int cols = maze[0].size();
    // cout << "rows" << rows << " cols" << cols;

    Cell* currentCell = &maze[y][x];

    int currentX = currentCell->x;
    int currentY = currentCell->y;
    //cout << "current location:" << currentY << " " << currentX;

    // Check all four directions, making sure not to revisit a cell or go through walls
    // Check down
    if (currentY > 0 && !currentCell->downWall && !maze[currentY - 1][currentX].visited) {
        //cout << currentY - 1 << currentX;
        maze[currentY - 1][currentX].visited = true;
        this->cellStack.push(maze[currentY - 1][currentX]);
    }
    // Check right
    else if (currentX < cols - 1 && !currentCell->rightWall && !maze[currentY][currentX + 1].visited) {
        //cout << currentY << currentX + 1;
        maze[currentY][currentX + 1].visited = true;
        this->cellStack.push(maze[currentY][currentX + 1]);
    }
    // Check up
    else if (currentY < rows - 1 && !currentCell->upWall && !maze[currentY + 1][currentX].visited) {
        //cout << currentY + 1 << currentX;
        maze[currentY + 1][currentX].visited = true;
        this->cellStack.push(maze[currentY + 1][currentX]);
    }
    // Check left
    else if (currentX > 0 && !currentCell->leftWall && !maze[currentY][currentX - 1].visited) {
        //cout << currentY  << currentX -1;
        maze[currentY][currentX - 1].visited = true;
        this->cellStack.push(maze[currentY][currentX - 1]);
    }
    else {
        return false;
    }
    return true;
}


