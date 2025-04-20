// This is my code for minesweeper project
// first include all headers and standard libraries

#include "gamewindow.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <random> //to place the mines randomly
#include <sstream> //maybe we don't need that
#include <iomanip> //for timer and digits

using namespace std;

// set up the game window and board

gamewindow::gamewindow(int width, int height, const string& playerName)
    : window(sf::VideoMode(width, height), "Minesweeper Game"), //SFML window
      playerName(playerName), //player's name
//set up everything we need
//including game status (game win/lose)
// UI features (debugMode,although it's not working very well)
// Initial number of flags and time both starts at 0

      gameOver(false), gameWon(false), debugMode(false), paused(false),
      flagsPlaced(0), elapsedSeconds(0) {

    loadTextures(); //load all the images we need from disk
    setupBoard(); // this will load the config and prepare the game tiles

    // save the initial time
    //<chrono> is a header in C++
    // basically it is a C++ function a C++ function
    // that returns the current time point
    // of the high-resolution clock
    startTime = chrono::high_resolution_clock::now();
    cout << "Game window created for: " << playerName << endl;
}

// This is the core game loop
// It's only called once from main()
// and loops until the window is closed

void gamewindow::run() {
    while (window.isOpen()) {  // this is a while loop that lasts until the window's closed
        handleEvents(); //we need to do something and respond to the clicks and inputs

        // Debugging/FIXED:
        // Timer should stop while paused, and resumes correctly
        // it was on before...

        // So just keep timer running if the game's not paused/over
        if (!paused && !gameOver) {
            updateTimer();                // start the timer as normal
        }

        // record the pause time when pause starts
        // also stop the timer

        if (paused && !isPausedTimer) {
            pauseStartTime = chrono::high_resolution_clock::now();
            isPausedTimer = true;
        }

        // Resume: make sure to shift startTime
        // to ignore the paused duration
        if (!paused && isPausedTimer) {
            auto now = chrono::high_resolution_clock::now();
            auto pausedDuration = chrono::duration_cast<chrono::seconds>(now - pauseStartTime);
            startTime += pausedDuration; // skip over the pause, push it back to start forward
            isPausedTimer = false;
        }

        render();
    }
}

// handleEvents() – Processes window and mouse input
// check all the sf helpful classes/functions

void gamewindow::handleEvents() {
    sf::Event event;    //handle user/system events like key presses
    while (window.pollEvent(event)) {   //poll all the pending events
        if (event.type == sf::Event::Closed) {
            window.close(); //if the user clicks X, close the window
        }

        // when we click the mouse
        //Convert pixel coords to world coords for mouse click
        // It basically gets the position of the mouse on the game window
        // in world coordinates
        // which are used for rendering

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            handleMouseClick(mousePos, event.mouseButton.button);
        }
    }
}

//render function (): to draw everything on the screen

void gamewindow::render() {
    window.clear(sf::Color::White); //clear the window with white color

    // nested for loop:
    // draw each tiles on the board
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            // Tiles will render differently if paused or debug is active
            tiles[y][x].draw(window, debugMode, paused); // Reveal all if paused or debug

    drawButtons();  // Draw all the UI buttons (smiley face, pause, debug...)
    drawCounter();  // To be implemented later
    drawTimer();    // To be implemented later

    window.display(); // don't forget to display everything on screen
}

// Draw all the UI buttons (smiley face, pause, debug...)
// also the leaderboard

void gamewindow::drawButtons() {

    //vertically place all buttons
    //right below grid

    float buttonY = 32 * (rows + 0.5f);

    // Happy face:
    // Set happy face texture based on win/loss state

    happyFace.setTexture(gameWon ? winFaceTexture : (gameOver ? loseFaceTexture : happyFaceTexture));
    happyFace.setPosition((cols * 32) / 2.0f - 32, buttonY);

    // Set texture and position for debug button

    debugButton.setTexture(debugTexture);

    //Make sure it's centered horizontally
    debugButton.setPosition((cols * 32) - 304, buttonY);

    // Set pause/play toggle texture

    pausePlayButton.setTexture(paused ? playTexture : pauseTexture);
    pausePlayButton.setPosition((cols * 32) - 240, buttonY);

    // Leaderboard button

    leaderboardButton.setTexture(leaderboardTexture);
    leaderboardButton.setPosition((cols * 32) - 176, buttonY);

    // Draw each button to the window

    window.draw(happyFace);
    window.draw(debugButton);
    window.draw(pausePlayButton);
    window.draw(leaderboardButton);
}

//loadTextures() – Load all image assets
//into memory from /files/images

void gamewindow::loadTextures() {
    tileHiddenTexture.loadFromFile("files/images/tile_hidden.png");
    tileRevealedTexture.loadFromFile("files/images/tile_revealed.png");
    mineTexture.loadFromFile("files/images/mine.png");
    flagTexture.loadFromFile("files/images/flag.png");

    // Load all number images (from 1 to 8)
    for (int i = 0; i < 8; ++i) {
        numberTextures[i].loadFromFile("files/images/number_" + to_string(i + 1) + ".png");
    }

    // Load UI images
    happyFaceTexture.loadFromFile("files/images/face_happy.png");
    winFaceTexture.loadFromFile("files/images/face_win.png");
    loseFaceTexture.loadFromFile("files/images/face_lose.png");
    debugTexture.loadFromFile("files/images/debug.png");
    pauseTexture.loadFromFile("files/images/pause.png");
    playTexture.loadFromFile("files/images/play.png");
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    digitsTexture.loadFromFile("files/images/digits.png");
}

// setupBoard() – Loads config file
// and prepares a clean tile grid

void gamewindow::setupBoard() {
    // Load board dimensions and mine count from config

    ifstream config("files/config.cfg");
    config >> cols >> rows >> mineCount;

    // Create 2D vector of tiles

    tiles.resize(rows, vector<Tile>(cols));
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x) {
            tiles[y][x].setPosition(x * 32, y * 32); //Set tile pixel position
            tiles[y][x].setBaseTexture(tileHiddenTexture); // Set default base texture
            tiles[y][x].setTileRevealedTexture(tileRevealedTexture); // Set revealed texture for logic
        }

    placeMines(); //place random mines
    calculateAdjacentMines();  //Assign numbers to tiles
}

//placeMines function: we need to:
//randomly places a fixed number of mines on the board

void gamewindow::placeMines() {
    int placed = 0; //original count should be set to 0
    random_device rd; // a hardware-based random number generator

    // basically a build-in RNG (random number generator) in C++
    //rd calls the random_device we had before
    // 19937... well it uses 19937 bits internally
    mt19937 gen(rd());

    // Now we should randomly pick tile coordinates on the board:
    // Uniform integer distributions:
    uniform_int_distribution<> xDist(0, cols - 1);
    uniform_int_distribution<> yDist(0, rows - 1);



    while (placed < mineCount) {
        int x = xDist(gen);
        int y = yDist(gen);
        if (!tiles[y][x].isMine()) {
            tiles[y][x].setMine(true); // Mark tile as mine
            placed++;   //Count it
        }
    }
}

// Counts how many adjacent tiles are mines for each tile

void gamewindow::calculateAdjacentMines() {

    // x and y offsets
    const int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    const int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x) {
            int count = 0;

            // Check each of the 8 surrounding tiles
            for (int d = 0; d < 8; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];

            // We should skip out-of-bounds neighbors
                if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && tiles[ny][nx].isMine()) {
                    count++;
                }
            }
            tiles[y][x].setAdjacentMines(count); // save our count
        }
}

// handleMouseClick() – Handles mouse clicks on tiles and UI buttons

void gamewindow::handleMouseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {

    // We would restart the game if the smiley face is clicked
    if (happyFace.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left) resetGame();  // left-click the smiley face
        return;
    }

    //if the debug button is clicked
    // switch to debug mode
    // my debug is not working well (but it's fine you don't need it)
    // it should show the mines temporarily
    if (debugButton.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left && !gameOver) {
            debugMode = !debugMode;
        }
        return;
    }

    // That is the pause button for pause/unpause the game

    if (pausePlayButton.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left && !gameOver) {
            paused = !paused;
        }
        return;
    }

    // Show the leaderboard
    // Pause and open the leaderboard window

    if (leaderboardButton.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left) {
            paused = true;
            leaderboard.show(); // show it
            while (leaderboard.isVisible()) {
                sf::Event event;
                while (leaderboard.window.pollEvent(event)) {
                    leaderboard.handleEvent(event); //scrolling and close
                }
                leaderboard.draw(window); //draw overlay
            }
        }
        return;
    }

    // There should be not input if the game's paused or over
    if (paused || gameOver)
        return;

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (tiles[y][x].contains(mousePos)) {

                // left-click: reveal the tile

                if (button == sf::Mouse::Left) {

                    // Only reveals the hidden one
                    if (tiles[y][x].getState() == Tile::HIDDEN) {
                        revealTile(x, y);

                        //Check if player wins

                        checkWinCondition();
                    }


                }

                // now if we right-click it should toggle the flag
                else if (button == sf::Mouse::Right)
                    {
                    if (tiles[y][x].getState() != Tile::REVEALED) {
                        tiles[y][x].toggleFlag(); // You could flag/unflag

                        // Change the overlay sprite
                        // And update the visual flag overlay

                        if (tiles[y][x].getState() == Tile::FLAGGED)
                            tiles[y][x].setOverlayTexture(flagTexture);
                        else
                            tiles[y][x].clearOverlay();

                        // update the flag count
                        flagsPlaced += (tiles[y][x].getState() == Tile::FLAGGED) ? 1 : -1;
                    }
                }
                return;
            }
}
// RevealTile() is called when a tile is left-clicked by us
// It reveals a tile
// From the instruction:  When the revealed tile has no adjacent mines,
// you will just display a revealed tile and all
// non-mine tiles surrounding it will be revealed
// This happens recursively

void gamewindow::revealTile(int x, int y) {

    //check for boundary first

    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return;

    Tile& tile = tiles[y][x];

    // Skip if already revealed or flagged
    if (tile.getState() != Tile::HIDDEN)
        return;

    tile.reveal(); // we change the state to revealed
    tile.setBaseTexture(tileRevealedTexture); // We also need to change the appearance to the revealed tile

    // GG: if tile is a mine, we reveal it and end the game
    if (tile.isMine()) {
        tile.setOverlayTexture(mineTexture); //show user the mine
        revealAllMines();  // Reveal all other mines
        gameOver = true;  // game over...
        return;
    }


    int n = tile.getAdjacentMines();
    if (n > 0) {
        // here comes the recursive part
        // If tile has a number (1–8), show that number as overlay
        tile.setOverlayTexture(numberTextures[n - 1]);
    } else {
        for (int dy = -1; dy <= 1; ++dy)
            for (int dx = -1; dx <= 1; ++dx)
                if (dx != 0 || dy != 0)
                    revealTile(x + dx, y + dy); //reveal the surroundings
    }
}

// this happens after u click on a mine...
// It should reveal all mines on the board and end the game.

void gamewindow::revealAllMines() {
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (tiles[y][x].isMine()) {
                tiles[y][x].reveal();
                tiles[y][x].setBaseTexture(tileRevealedTexture);
                tiles[y][x].setOverlayTexture(mineTexture);
            }
}

// Check for all non-mine tiles (if they are revealed)
// If true, we should mark game as won
// And also auto-flags all the remaining mines.
void gamewindow::checkWinCondition() {
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (!tiles[y][x].isMine() && tiles[y][x].getState() != Tile::REVEALED)
                return;
// Update player status
    gameWon = true;
    gameOver = true;

// Auto-flag all mines visually

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (tiles[y][x].isMine()) {
                tiles[y][x].toggleFlag();
                tiles[y][x].setOverlayTexture(flagTexture);
            }
// add the score to leader board
    leaderboard.addEntry(playerName, elapsedSeconds);
}

void gamewindow::resetGame() {
    // Debug: We need to make sure it;s always a full game reset after win or loss

    // Reset all flags and states
    gameOver = false;
    gameWon = false;
    paused = false;
    debugMode = false;
    flagsPlaced = 0;
    elapsedSeconds = 0;
    isPausedTimer = false;

    // Clear all tile visuals and data
    // Reset the graphics and tile's state
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            tiles[y][x].reset();
            tiles[y][x].setBaseTexture(tileHiddenTexture);  // This reassigns hidden base after sprite wipe

        }
    }

    // Regenerate the board
    // also the calculated numbers
    placeMines();
    calculateAdjacentMines();

    // Restart the timer too
    startTime = chrono::high_resolution_clock::now();
}


void gamewindow::updateTimer() {
    auto now = chrono::high_resolution_clock::now();
    elapsedSeconds = chrono::duration_cast<chrono::seconds>(now - startTime).count();
}

void gamewindow::drawTimer() {
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;

    int minTens = minutes / 10;
    int minOnes = minutes % 10;
    int secTens = seconds / 10;
    int secOnes = seconds % 10;

    float y = 32 * (rows + 0.5f) + 16;
    float x = (cols * 32) - 97;

    sf::Sprite digit;
    digit.setTexture(digitsTexture);

    digit.setTextureRect(sf::IntRect(minTens * 21, 0, 21, 32));
    digit.setPosition(x, y);
    window.draw(digit);

    digit.setTextureRect(sf::IntRect(minOnes * 21, 0, 21, 32));
    digit.setPosition(x + 21, y);
    window.draw(digit);

    digit.setTextureRect(sf::IntRect(secTens * 21, 0, 21, 32));
    digit.setPosition(x + 43, y);
    window.draw(digit);

    digit.setTextureRect(sf::IntRect(secOnes * 21, 0, 21, 32));
    digit.setPosition(x + 64, y);
    window.draw(digit);
}

// Draws remaining mine counter in 3 digits
// Shows negative numbers and sign after 0. (if you keep right-click...)

void gamewindow::drawCounter() {
    int count = mineCount - flagsPlaced;
    bool isNegative = count < 0;
    count = abs(count);

    int hundreds = count / 100;
    int tens = (count / 10) % 10;
    int ones = count % 10;

    float y = 32 * (rows + 0.5f) + 16;
    float x = 33;

    sf::Sprite digit;
    digit.setTexture(digitsTexture);

    if (isNegative) {
        digit.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32)); // '-' symbol at index 10
        digit.setPosition(x - 21, y);
        window.draw(digit);
    } else {
        digit.setTextureRect(sf::IntRect(hundreds * 21, 0, 21, 32));
        digit.setPosition(x, y);
        window.draw(digit);
    }

    digit.setTextureRect(sf::IntRect(tens * 21, 0, 21, 32));
    digit.setPosition(x + 21, y);
    window.draw(digit);

    digit.setTextureRect(sf::IntRect(ones * 21, 0, 21, 32));
    digit.setPosition(x + 42, y);
    window.draw(digit);
}

// Well all these 3 functions are useful for debug.

void Tile::saveCurrentState() {
    savedBaseTexture = sprite.getTexture();
    savedOverlayTexture = overlaySprite.getTexture();
    savedFlagged = (state == FLAGGED);
    savedState = state;
}

void Tile::restoreSavedState() {
    if (savedBaseTexture) sprite.setTexture(*savedBaseTexture);
    if (savedOverlayTexture) overlaySprite.setTexture(*savedOverlayTexture);
    state = savedState;
}

void Tile::forceRevealVisualOnly(const sf::Texture& revealTexture) {
    sprite.setTexture(revealTexture); // all tiles show revealed base
    overlaySprite = sf::Sprite();     // clear overlays
}

