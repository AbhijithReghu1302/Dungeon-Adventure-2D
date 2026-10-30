# Dungeon Adventure – 2D Fighting Game

A 2D dungeon fighting game developed using **C++ and Raylib**. The project features player movement, enemy AI, combat mechanics, health management, healing potions, and stage progression.

## Features

- **Player Movement:** Move using WASD or arrow keys.
- **Enemy AI:** Enemies pursue the player using distance and direction calculations.
- **Combat System:** Attack nearby enemies using the Space key.
- **Health System:** Player and enemies have health points and health bars.
- **Healing Potions:** Restore player health using healing potions.
- **Game States:** Includes victory and game-over conditions.
- **Stage Progression:** Progress through increasingly challenging dungeon stages.

## Technologies Used

- C++
- Raylib
- GCC (MSYS2 UCRT64)
- Visual Studio Code

## Controls

| Key | Action |
|---|---|
| W / A / S / D | Move player |
| Arrow Keys | Move player |
| Space | Attack enemies |
| H | Use healing potion |
| Enter | Continue to next stage |
| Esc | Close the game |

## Project Structure

```text
DungeonAdventure/
│
├── data/
│   └── savegame.txt
│
├── include/
│   ├── Dungeon.h
│   ├── Game.h
│   └── Player.h
│
├── src/
│   ├── Dungeon.cpp
│   ├── Game.cpp
│   ├── Player.cpp
│   └── game2d.cpp
│
├── main.cpp
├── README.md
└── .gitignore
```

## How to Run

1. Install a C++ compiler.
2. Install Raylib.
3. Open the project folder in Visual Studio Code.
4. Compile the graphical game using the following command:

```powershell
g++ src/game2d.cpp -o Dungeon2D.exe -I"C:\msys64\ucrt64\include" -L"C:\msys64\ucrt64\lib" -lraylib -lopengl32 -lgdi32 -lwinmm -luser32
```

5. Run the executable:

```powershell
.\Dungeon2D.exe
```

**Note:** The compilation command above assumes Raylib is installed in the MSYS2 UCRT64 environment on Windows.

## Project Purpose

This project was developed as part of the Computer Aptitude coursework to explore C++ programming, game logic, enemy AI, graphical programming, and interactive game development.

## Author

Developed as a C++ game development project.