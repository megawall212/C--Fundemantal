#include "gamewindow.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <iomanip>

using namespace std;

gamewindow::gamewindow(int width, int height, const string& playerName)
    : window(sf::VideoMode(width, height), "Minesweeper Game"),
      playerName(playerName),
      gameOver(false), gameWon(false), debugMode(false), paused(false),
      flagsPlaced(0), elapsedSeconds(0) {

    loadTextures();
    setupBoard();
    startTime = chrono::high_resolution_clock::now();
    cout << "Game window created for: " << playerName << endl;
}

void gamewindow::run() {
    while (window.isOpen()) {
        handleEvents();

        // FIXED: Timer stops while paused, and resumes correctly

        if (!paused && !gameOver) {
            updateTimer();                // normal counting
        }

        // Store when pause starts
        if (paused && !isPausedTimer) {
            pauseStartTime = chrono::high_resolution_clock::now();
            isPausedTimer = true;
        }

        // Resume: shift startTime to ignore the paused duration
        if (!paused && isPausedTimer) {
            auto now = chrono::high_resolution_clock::now();
            auto pausedDuration = chrono::duration_cast<chrono::seconds>(now - pauseStartTime);
            startTime += pausedDuration; // skip over the pause
            isPausedTimer = false;
        }

        render();
    }
}

void gamewindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            handleMouseClick(mousePos, event.mouseButton.button);
        }
    }
}

void gamewindow::render() {
    window.clear(sf::Color::White);

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            tiles[y][x].draw(window, debugMode, paused); // Reveal all if paused or debug

    drawButtons();
    drawCounter();  // To be implemented
    drawTimer();    // To be implemented

    window.display();
}

void gamewindow::drawButtons() {
    float buttonY = 32 * (rows + 0.5f);

    happyFace.setTexture(gameWon ? winFaceTexture : (gameOver ? loseFaceTexture : happyFaceTexture));
    happyFace.setPosition((cols * 32) / 2.0f - 32, buttonY);

    debugButton.setTexture(debugTexture);
    debugButton.setPosition((cols * 32) - 304, buttonY);

    pausePlayButton.setTexture(paused ? playTexture : pauseTexture);
    pausePlayButton.setPosition((cols * 32) - 240, buttonY);

    leaderboardButton.setTexture(leaderboardTexture);
    leaderboardButton.setPosition((cols * 32) - 176, buttonY);

    window.draw(happyFace);
    window.draw(debugButton);
    window.draw(pausePlayButton);
    window.draw(leaderboardButton);
}

void gamewindow::loadTextures() {
    tileHiddenTexture.loadFromFile("files/images/tile_hidden.png");
    tileRevealedTexture.loadFromFile("files/images/tile_revealed.png");
    mineTexture.loadFromFile("files/images/mine.png");
    flagTexture.loadFromFile("files/images/flag.png");

    for (int i = 0; i < 8; ++i) {
        numberTextures[i].loadFromFile("files/images/number_" + to_string(i + 1) + ".png");
    }

    happyFaceTexture.loadFromFile("files/images/face_happy.png");
    winFaceTexture.loadFromFile("files/images/face_win.png");
    loseFaceTexture.loadFromFile("files/images/face_lose.png");
    debugTexture.loadFromFile("files/images/debug.png");
    pauseTexture.loadFromFile("files/images/pause.png");
    playTexture.loadFromFile("files/images/play.png");
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    digitsTexture.loadFromFile("files/images/digits.png");
}

void gamewindow::setupBoard() {
    ifstream config("files/config.cfg");
    config >> cols >> rows >> mineCount;

    tiles.resize(rows, vector<Tile>(cols));
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x) {
            tiles[y][x].setPosition(x * 32, y * 32);
            tiles[y][x].setBaseTexture(tileHiddenTexture);
            tiles[y][x].setTileRevealedTexture(tileRevealedTexture);
        }

    placeMines();
    calculateAdjacentMines();
}

void gamewindow::placeMines() {
    int placed = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> xDist(0, cols - 1);
    uniform_int_distribution<> yDist(0, rows - 1);

    while (placed < mineCount) {
        int x = xDist(gen);
        int y = yDist(gen);
        if (!tiles[y][x].isMine()) {
            tiles[y][x].setMine(true);
            placed++;
        }
    }
}

void gamewindow::calculateAdjacentMines() {
    const int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    const int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x) {
            int count = 0;
            for (int d = 0; d < 8; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && tiles[ny][nx].isMine()) {
                    count++;
                }
            }
            tiles[y][x].setAdjacentMines(count);
        }
}

void gamewindow::handleMouseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
    if (happyFace.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left) resetGame();
        return;
    }

    if (debugButton.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left && !gameOver) {
            debugMode = !debugMode;
        }
        return;
    }

    if (pausePlayButton.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left && !gameOver) {
            paused = !paused;
        }
        return;
    }

    if (leaderboardButton.getGlobalBounds().contains(mousePos)) {
        if (button == sf::Mouse::Left) {
            paused = true;
            leaderboard.show();
            while (leaderboard.isVisible()) {
                sf::Event event;
                while (leaderboard.window.pollEvent(event)) {
                    leaderboard.handleEvent(event);
                }
                leaderboard.draw(window);
            }
        }
        return;
    }

    if (paused || gameOver)
        return;

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (tiles[y][x].contains(mousePos)) {
                if (button == sf::Mouse::Left) {
                    if (tiles[y][x].getState() == Tile::HIDDEN) {
                        revealTile(x, y);
                        checkWinCondition();
                    }
                } else if (button == sf::Mouse::Right) {
                    if (tiles[y][x].getState() != Tile::REVEALED) {
                        tiles[y][x].toggleFlag();
                        if (tiles[y][x].getState() == Tile::FLAGGED)
                            tiles[y][x].setOverlayTexture(flagTexture);
                        else
                            tiles[y][x].clearOverlay();
                        flagsPlaced += (tiles[y][x].getState() == Tile::FLAGGED) ? 1 : -1;
                    }
                }
                return;
            }
}

void gamewindow::revealTile(int x, int y) {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return;

    Tile& tile = tiles[y][x];
    if (tile.getState() != Tile::HIDDEN)
        return;

    tile.reveal();
    tile.setBaseTexture(tileRevealedTexture);

    if (tile.isMine()) {
        tile.setOverlayTexture(mineTexture);
        revealAllMines();
        gameOver = true;
        return;
    }

    int n = tile.getAdjacentMines();
    if (n > 0) {
        tile.setOverlayTexture(numberTextures[n - 1]);
    } else {
        for (int dy = -1; dy <= 1; ++dy)
            for (int dx = -1; dx <= 1; ++dx)
                if (dx != 0 || dy != 0)
                    revealTile(x + dx, y + dy);
    }
}

void gamewindow::revealAllMines() {
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (tiles[y][x].isMine()) {
                tiles[y][x].reveal();
                tiles[y][x].setBaseTexture(tileRevealedTexture);
                tiles[y][x].setOverlayTexture(mineTexture);
            }
}

void gamewindow::checkWinCondition() {
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (!tiles[y][x].isMine() && tiles[y][x].getState() != Tile::REVEALED)
                return;

    gameWon = true;
    gameOver = true;

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (tiles[y][x].isMine()) {
                tiles[y][x].toggleFlag();
                tiles[y][x].setOverlayTexture(flagTexture);
            }

    leaderboard.addEntry(playerName, elapsedSeconds);
}

void gamewindow::resetGame() {
    // --- FIXED: Full game reset after win or loss ---

    // Reset all flags and states
    gameOver = false;
    gameWon = false;
    paused = false;
    debugMode = false;
    flagsPlaced = 0;
    elapsedSeconds = 0;
    isPausedTimer = false;

    // Clear all tile visuals and data
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            tiles[y][x].reset();
            tiles[y][x].setBaseTexture(tileHiddenTexture);  // This reassigns hidden base after sprite wipe

        }
    }

    // Regenerate a fresh board
    placeMines();
    calculateAdjacentMines();

    // Restart timer
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

