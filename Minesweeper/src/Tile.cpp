//
// Created by lzy46 on 4/14/2025.
//

#include "Tile.h"

Tile::Tile() {
    state = HIDDEN;
    mine = false;
    adjacentMines = 0;
    position = {0, 0};
}

void Tile::setPosition(float x, float y) {
    position = {x, y};
    sprite.setPosition(position);
    overlaySprite.setPosition(position);
    tile_revealed.setPosition(position);
}

void Tile::setMine(bool isMine) {
    mine = isMine;
}

bool Tile::isMine() const {
    return mine;
}

Tile::State Tile::getState() const {
    return state;
}

void Tile::reveal() {
    if (state != REVEALED)
        state = REVEALED;
}

void Tile::toggleFlag() {
    if (state == HIDDEN)
        state = FLAGGED;
    else if (state == FLAGGED)
        state = HIDDEN;
}

void Tile::setAdjacentMines(int count) {
    adjacentMines = count;
}

void Tile::setBaseTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Tile::setOverlayTexture(const sf::Texture& texture) {
    overlaySprite.setTexture(texture);
}

void Tile::setTileRevealedTexture(const sf::Texture &texture) {
    tile_revealed.setTexture(texture);
}


void Tile::clearOverlay() {
    overlaySprite = sf::Sprite(); // Reset it
}


int Tile::getAdjacentMines() const {
    return adjacentMines;
}

bool Tile::contains(sf::Vector2f point) const {
    return sprite.getGlobalBounds().contains(point);
}

void Tile::reset() {
    state = HIDDEN;
    mine = false;
    adjacentMines = 0;
}

void Tile::draw(sf::RenderWindow& window, bool debugMode, bool pauseMode) {
    // Always draw the base tile depending on state
    if (state == REVEALED)
        window.draw(sprite);  // This should be tile_revealed
    else
        window.draw(sprite);  // This should be tile_hidden

    // Draw flag if flagged
    if (state == FLAGGED) {
        window.draw(overlaySprite);  // This should be flag.png
    }

    // Draw mine if revealed and it's a mine
    if (state == REVEALED && mine) {
        window.draw(overlaySprite);  // This should be mine.png
    }

    // If tile is revealed and has number
    if (state == REVEALED && !mine && adjacentMines > 0) {
        window.draw(overlaySprite);
    }

    // Debug: Show mine if hidden
    // Well, but it doesn't matter in this project
    if (debugMode && mine && state != REVEALED) {
        window.draw(overlaySprite);

        if (pauseMode) {
            window.draw(tile_revealed);
        }


    }
}
