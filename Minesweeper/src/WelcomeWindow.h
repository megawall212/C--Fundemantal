#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class WelcomeWindow {
public:
    WelcomeWindow();
    string run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text welcomeText;
    sf::Text promptText;
    sf::Text nameText;
    sf::Text cursorText;
    string playerName;
    bool cursorVisible;
    sf::Clock cursorBlinkTimer;
    const float centerX = 400;
    const float inputTextY = 306 - 45;

    void handleEvents();
    void update();
    void render();
    void formatPlayerName();
};

#endif