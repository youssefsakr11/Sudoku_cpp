// Implementation file
#include "Sudoku.h"
#include <iostream>
using namespace std;

void Sudoku::initializeGrid() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;
            solution[i][j] = 0;
        }
    }
}

bool Sudoku::isValid(int row, int col, int num) {
    // Check the row and column
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row / 3 * 3;
    int startCol = col / 3 * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    // Check if the number aligns with the solution grid
    if (solution[row][col] != 0 && solution[row][col] != num) {
        return false;
    }

    return true; // Valid placement
}

bool Sudoku::solve(int row, int col) {
    if (row == 9) return true;
    if (col == 9) return solve(row + 1, 0);
    if (grid[row][col] != 0) return solve(row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;
            if (solve(row, col + 1)) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

void Sudoku::generatePuzzle() {
    initializeGrid();

    int attempts = 0;
    for (int i = 0; i < 10; i++) {
        int row = rand() % 9;
        int col = rand() % 9;
        int num = rand() % 9 + 1;

        if (grid[row][col] == 0 && isValid(row, col, num)) {
            grid[row][col] = num;
        }
        else {
            i--; // Retry
            attempts++;
            if (attempts > 100) {
                cout << "Too many failed attempts at placing initial numbers. Aborting.\n";
                return;
            }
        }
    }

    if (!solve(0, 0)) {
        cout << "Error: Failed to solve during puzzle generation.\n";
        return;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solution[i][j] = grid[i][j];
        }
    }

    cout << "Solved grid (solution):\n";
    displayGrid();

    int cellsToRemove = 81 - prefilledCells;
    while (cellsToRemove > 0) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            cellsToRemove--;
        }
    }
}

Sudoku::Sudoku() : prefilledCells(35), heartsRemaining(3) {}

void Sudoku::setDifficulty(const char* difficulty) {
    if (strcmp(difficulty, "easy") == 0) prefilledCells = 35;
    else if (strcmp(difficulty, "medium") == 0) prefilledCells = 25;
    else if (strcmp(difficulty, "hard") == 0) prefilledCells = 20;
    else cout << "Invalid difficulty! Defaulting to easy.\n";
}

void Sudoku::displayGrid() const {
    cout << "Current Sudoku Grid:\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) cout << ". ";
            else cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Hearts Remaining: " << heartsRemaining << endl;
}

void Sudoku::resetGame() {
    userMoves = HashMap<Cell, int>();
    initializeGrid();
    generatePuzzle();
    heartsRemaining = 3; // Reset hearts when restarting
}

void Sudoku::startGame(const char* difficulty) {
    setDifficulty(difficulty);
    cout << "Generated puzzle:\n";
    generatePuzzle();
}

void Sudoku::play() {
    while (heartsRemaining > 0) {
        displayGrid();
        int row, col, num;
        cout << "Enter row (1-9), column (1-9), and number (1-9) (-1 to quit): ";
        cin >> row;
        if (row == -1) break;
        cin >> col >> num;

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            cout << "Invalid input! Try again." << endl;
            continue;
        }

        Cell key = { row - 1, col - 1 };
        int existingValue;

        if (userMoves.get(key, existingValue) || grid[row - 1][col - 1] != 0) {
            cout << "Wrong insertion! Try again." << endl;
            heartsRemaining--; // Decrease hearts on wrong move
        }
        else if (isValid(row - 1, col - 1, num)) {
            userMoves.insert(key, num);
            grid[row - 1][col - 1] = num;
            cout << "Number placed successfully!" << endl;
        }
        else {
            cout << "Wrong insertion! Try again." << endl;
            heartsRemaining--; // Decrease hearts on wrong move
        }

        if (heartsRemaining == 0) {
            cout << "GAME OVER" << endl;
            cout << "Would you like to play again? (yes/no): ";
            string choice;
            cin >> choice;

            if (choice == "yes") {
                resetGame();
                play();
            }
            else {
                cout << "THANK YOU FOR PLAYING!" << endl;
                break;
            }
        }
    }
}

bool Sudoku::hasUniqueSolution() {
    // Implement the method to check for a unique solution if needed
    return true;
}