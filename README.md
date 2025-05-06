# Tetris Game

This is microproject of Tetris game built using C++ and the raylib library.
<br> It was realized as a microproject during semester 4 of the *Computer Programming 4* course.
<br>[Official raylib site](https://www.raylib.com/)
<br>[raylib github](https://github.com/raysan5/raylib)

## Features
- Classic Tetris gameplay
- Customizable colors and fonts
- Score tracking
- Game over handling
- Smooth animations and input handling

## Prerequisites
To run this project, you need to have the following installed:
- [CMake](https://cmake.org/) or any other build system of your choice
- [vcpkg](https://vcpkg.io/) (for managing dependencies)
- A C++20 compatible compiler
- The `raylib` library

## Setting Up the Project
1. Clone the repository to your local machine.
2. Install the `raylib` library using `vcpkg`:
   ```bash
   vcpkg install raylib
   ```
3. Configure your build system (e.g., CMake, Make) to include the following:
   - The `raylib` library files (`.lib` and `.dll`) located in your system.
   - The asset files required for the game.

## Asset Files
The project requires the following asset files:

### `Assets/Sounds`
- `clear.mp3`: Sound effect for clearing a line.
- `music.mp3`: Background music for the game.
- `rotate.mp3`: Sound effect for rotating a block.

### `Assets/game_results`
- `Local-player.txt`: Stores game results for the local player.
- `LocalPlayer.txt`: Alternate file for storing game results.

### `Assets/Font`
- `monogram.ttf`: Font used for rendering text in the game.

### Directory Structure
Ensure the following directory structure is maintained:
```
Project/
├── Assets/
│   ├── Sounds/
│   │   ├── clear.mp3
│   │   ├── music.mp3
│   │   └── rotate.mp3
│   ├── game_results/
│   │   ├── Local-player.txt
│   │   └── LocalPlayer.txt
│   └── Font/
│       └── monogram.ttf
├── src/
│   ├── main.cpp
│   ├── game.cpp
│   ├── game.h
│   ├── colors.cpp
│   ├── colors.h
│   ├── grid.cpp
│   ├── position.cpp
│   ├── block.cpp
│   ├── block.h
│   └── blocks.cpp
├── CMakeLists.txt
└── README.md
```

## Building the Project
1. Set up your build system to include the `raylib` library and the asset files.
2. Build the project using your chosen build system.

## Running the Game
After building, run the executable. Ensure the `Assets` directory is in the same directory as the executable to avoid asset loading issues.

## Notes
- The user is responsible for configuring the build system to include the required library files and assets.
- If you encounter issues with asset loading, verify the paths in the code and ensure the assets are correctly placed.