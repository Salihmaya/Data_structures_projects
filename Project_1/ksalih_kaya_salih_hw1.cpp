// Salih Kaya 27890 ksalih@sabanciuniv.edu
#include "RandMazeGenerator.h"
#include <iostream>

using namespace std;
// Random Maze generator cpp is utilized to generate required number of mazes in the required format of N*M
// Maze Solver cpp is then utilized to solve the created Xth maze based on the inputs of entry and end points
// Stack is a regular stack implementation with the common functions of it
// Auto is used a lot in the functions it is not efficient, I know. However, I got a lot of errors from mismatching types and it accelerated my writing process a lot.

int main() {
    // Define the number of mazes to be generated
    int numberOfMazes;
    cout << "Enter the number of mazes: ";
    cin >> numberOfMazes;

    // Define the size of the mazes
    int rows, cols;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> rows >> cols;

    vector < vector < vector<Cell>>> mymazes;

    for (int i = 0; i < numberOfMazes; ++i) {

        // Create a maze of the given size
        RandomMazeGenerator mazeGenerator(rows, cols);

        // Generate the maze
        mazeGenerator.generateMaze();

        // Save the maze to a file
        int mazeID = i + 1;  // Unique ID for each maze
        mazeGenerator.writeMazeToFile(mazeID);

        auto mymaze = mazeGenerator.maze;
        mymazes.push_back(mymaze);
        

    }

    cout << "All mazes are generated.\n";


    cout << "Enter a maze ID between 1 to " << numberOfMazes << " inclusive to find a path : ";
    int mazeIdToSolve;
    cin >> mazeIdToSolve;

    int enterX, enterY;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row):";
    cin >> enterX >> enterY;

    int endX, endY;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row):";
    cin >> endX >> endY;

    auto solver = MazeSolver(mazeIdToSolve, mymazes[mazeIdToSolve - 1], enterX,  enterY, endX, endY);

    return 0;
}
