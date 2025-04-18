#ifndef WELCOME_WINDOW_H
#define WELCOME_WINDOW_H

#include <SFML/Graphics.hpp>  // This should include Font.hpp
#include <string>
#include <cctype>

class WelcomeWindow {
public:
    WelcomeWindow();
    void run();

private:
    // Member variables
    sf::RenderWindow window;
    sf::Font font;            // Font declaration
    sf::Text welcomeText;
    sf::Text promptText;
    sf::Text nameText;
    sf::Text cursorText;
    std::string playerName;
    bool cursorVisible;
    sf::Clock cursorBlinkTimer;

    // Member functions
    void handleEvents();
    void formatPlayerName();
    void update();
    void render();
};

#endif // WELCOME_WINDOW_H