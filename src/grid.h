#pragma once

#include <vector>
#include <raylib.h>
#include <filesystem>

class Grid {
public:
    Grid();

    void Initialize();

    void Print();

    void Draw();

    bool IsCellOutside(int row, int column);

    bool IsCellEmpty(int row, int column);

    int ClearFullRows();

    void saveGameResults(const std::string &playerName, int score, int level, int duration);

    int grid[20][10];

private:
    bool IsRowFull(int row);

    void ClearRow(int row);

    void MoveRowDown(int row, int numRows);

    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
    std::filesystem::path resultsDir;
};