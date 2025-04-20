//
// Created by lzy46 on 4/14/2025.
//

#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {
public:
    enum State { HIDDEN, REVEALED, FLAGGED };

    // Constructor
    Tile();


    void setPosition(float x, float y);

    // Gameplay state
    void setMine(bool isMine);
    bool isMine() const;
    State getState() const;
    void reveal();
    void toggleFlag();
    void setAdjacentMines(int count);
    int getAdjacentMines() const;
    bool contains(sf::Vector2f point) const;
    void reset();

    // Drawing (debug or pause reveal support)
    void draw(sf::RenderWindow& window, bool debugMode = false, bool pauseMode = false);

    // Texture management
    void setBaseTexture(const sf::Texture& texture);
    void setOverlayTexture(const sf::Texture& texture);
    void setTileRevealedTexture(const sf::Texture& texture);
    void clearOverlay();

    // Pause
    void saveCurrentState();     // Save game state before pause
    void restoreSavedState();    // Restore state after unpausing the game
    void forceRevealVisualOnly(const sf::Texture& revealTexture); //  revealed visuals

private:
    // Visuals
    sf::Sprite sprite;         // Base tile image
    sf::Sprite overlaySprite;  // Overlay: number, flag, or mine
    sf::Sprite tile_revealed;

    // State
    State state;
    bool mine;
    int adjacentMines;
    sf::Vector2f position;

    // For pause state restore
    const sf::Texture* savedBaseTexture = nullptr;
    const sf::Texture* savedOverlayTexture = nullptr;

    bool savedFlagged = false;
    State savedState;
};

#endif
