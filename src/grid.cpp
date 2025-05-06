#include "grid.h"
#include <iostream>
#include "colors.h"
#include <fstream>
#include <ranges>
#include <thread>
#include <algorithm>
#include <filesystem>

Grid::Grid() : resultsDir("game_results") {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();

    //Dir to store game results if it doesn't exist
    std::filesystem::create_directories(resultsDir);
}

void Grid::Initialize() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column) {
    if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column) {
    if (grid[row][column] == 0) {
        return true;
    }
    return false;
}

//Fixed after updating to gcc 14.1 and using algorithm library
int Grid::ClearFullRows() {
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--) {
        if (std::ranges::all_of(grid[row], [](int cell) { return cell != 0; })) {
            ClearRow(row);
            completed++;
        } else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row) {
    for (int column = 0; column < numCols; column++) {
        if (grid[row][column] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (int column = 0; column < numCols; column++) {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows) {
    for (int column = 0; column < numCols; column++) {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

//Indirect method of <filesystem> usage
void Grid::saveGameResults(const std::string& playerName, int score, int level, int duration) {
    auto saveTask = [this, playerName, score, level, duration] {
        std::filesystem::path resultFile = resultsDir / (playerName + ".txt");
        std::cout << "Saving game results to: " << std::filesystem::absolute(resultFile) << "\n";

        //Ensuring the game directory exists
        std::filesystem::create_directories(resultsDir);

        std::ofstream file(resultFile, std::ios::app);
        if (file.is_open()) {
            file << "Score: " << score << "\n";
            file << "Level: " << level << "\n";
            file << "Duration: " << duration << " seconds\n";
            file << "-------------------------\n";
            file.close();
        } else {
            std::cerr << "Failed to open file: " << resultFile << "\n";
        }
    };
    std::thread saveThread(saveTask); // Running the save task in a separate thread
    saveThread.join();
}
