/**
 * @file game.h
 * @brief Definition of the Game class.
 */

#pragma once

#include "grid.h"
#include "blocks.cpp"
#include <chrono>

/**
 * @brief The Game class represents the Tetris game.
 */

class Game {
public:
    /**
     * @brief Construct a new Game object.
     */
    Game();

    /**
     * @brief Destroy the Game object.
     */

    ~Game();

    /**
     * @brief Runs the game loop.
     */

    void Draw();

    void HandleInput();

    void MoveBlockDown();

    void HandleGameOver(); //Method to handle game over state

    bool gameOver;
    int score; //score which we have to use in savegameresults
    Music music;

private:
    void MoveBlockLeft();

    void MoveBlockRight();

    Block GetRandomBlock();

    std::vector<Block> GetAllBlocks();

    bool IsBlockOutside();

    void RotateBlock();

    void LockBlock();

    bool BlockFits();

    void Reset();

    void UpdateScore(int linesCleared, int moveDownPoints);

    void SaveGameResult(); //Kept private, called internally

    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
    int level; //Level of the game if private here. we've to address it for savegameresults
    int duration; //Dur of the game in seconds. private here. we've to address it for savegameresults
    bool gameResultSaved; //Flag to check if game result is saved
    std::chrono::steady_clock::time_point startTime;
};