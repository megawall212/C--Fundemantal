#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <string>
#include "Tile.h"
#include "Leaderboard.h"

class gamewindow {
public:
    // Constructor - creates window with specified dimensions and player name
    gamewindow(int width, int height, const std::string& playerName);

    // Main game loop
    void run();

private:
    // Core game functions
    void handleEvents();       // Handles user input
    void render();             // Draws all game elements
    void loadTextures();       // Loads all required textures
    void setupBoard();         // Initializes game board
    void placeMines();         // Randomly places mines
    void calculateAdjacentMines(); // Calculates adjacent mines for each tile
    void handleMouseClick(sf::Vector2f mousePos, sf::Mouse::Button button); // Processes mouse clicks
    void revealTile(int x, int y); // Reveals tile and handles recursive reveal
    void revealAllMines();     // Reveals all mines (game over)
    void checkWinCondition();  // Checks if player has won
    void resetGame();          // Resets game to initial state
    void updateCounter();      // Updates mine counter display
    void updateTimer();        // Updates game timer display
    void drawButtons();        // Draws all UI buttons
    void drawTimer();    // Draws the MM:SS game timer
    void drawCounter();  // Draws the mine counter (mines remaining)


    // Game window and state
    sf::RenderWindow window;
    std::string playerName;
    Leaderboard leaderboard;   // Leaderboard instance

    // Board configuration
    int cols, rows, mineCount;
    std::vector<std::vector<Tile>> tiles;

    // Game state
    bool gameOver;
    bool gameWon;
    bool debugMode;
    bool paused;
    int flagsPlaced;

    // UI elements
    sf::Sprite happyFace;
    sf::Sprite debugButton;
    sf::Sprite pausePlayButton;
    sf::Sprite leaderboardButton;

    // Timer
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    int elapsedSeconds;

    // FIXED: Added pause support
    bool isPausedTimer = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> pauseStartTime;


    // Textures
    sf::Texture tileHiddenTexture;
    sf::Texture tileRevealedTexture;
    sf::Texture mineTexture;
    sf::Texture flagTexture;
    sf::Texture numberTextures[8]; // For numbers 1-8
    sf::Texture happyFaceTexture;
    sf::Texture winFaceTexture;
    sf::Texture loseFaceTexture;
    sf::Texture debugTexture;
    sf::Texture pauseTexture;
    sf::Texture playTexture;
    sf::Texture leaderboardTexture;
    sf::Texture digitsTexture; // For counter and timer
};

#endif