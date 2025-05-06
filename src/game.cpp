#include "game.h"
#include <random>
#include <ctime>
#include <raylib.h>
#include <chrono>
#include <regex>
#include <iostream>

Game::Game() : level(1), duration(0) {
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    //Music part and its files are not essential for the game to work
    //Files with sounds have to be in the build dir

    InitAudioDevice();
    music = LoadMusicStream("Assets/Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Assets/Sounds/rotate.mp3");
    clearSound = LoadSound("Assets/Sounds/clear.mp3");

    startTime = std::chrono::steady_clock::now();
}

Game::~Game() {
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() {
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id) {
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;
    }
}

void Game::HandleInput() {
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0) {
        gameOver = false;
        Reset();
    }
    switch (keyPressed) {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockLeft() {
    if (!gameOver) {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight() {
    if (!gameOver) {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown() {
    if (!gameOver) {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles) {
        if (grid.IsCellOutside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock() {
    if (!gameOver) {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.UndoRotation();
        } else {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles) {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false) {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0) {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles) {
        if (grid.IsCellEmpty(item.row, item.column) == false) {
            return false;
        }
    }
    return true;
}

void Game::Reset() {
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    level = 1;
    duration = 0;
    gameOver = false;
    gameResultSaved = false;

    startTime = std::chrono::steady_clock::now();
}

void Game::UpdateScore(int linesCleared, int moveDownPoints) {
    static const int pointsPerLine = 100;
    score += linesCleared * pointsPerLine + moveDownPoints;
    level = score / 1000 + 1;
}

void Game::HandleGameOver() {
    if (gameOver && !gameResultSaved) {
        auto endTime = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
        SaveGameResult();
        gameResultSaved = true;
    }
}

void Game::SaveGameResult() {
    auto endTime = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::string playerName = "LocalPlayer";

    std::regex playerNamePattern("[a-zA-Z0-9]{1,20}");
    if (!std::regex_match(playerName, playerNamePattern)) {
        std::cerr << "Invalid player name format. Exiting...\n";
        return;
    }

    grid.saveGameResults(playerName, score, level, duration);
}
