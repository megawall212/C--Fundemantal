#include <iostream>
#include <SFML/Graphics.hpp>

/*

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}

*/

#include "WelcomeWindow.h"
#include "gamewindow.h"

#include "WelcomeWindow.h"
#include "gamewindow.h"
#include <fstream>  // Added for config file reading

using namespace std;

int main() {
    WelcomeWindow welcomeWindow;
    string playerName = welcomeWindow.run();


    if (!playerName.empty()) {
        // Read dimensions from config file
        ifstream configFile("files/config.cfg");
        int width = 800, height = 612;  // Default values if config fails

        if (configFile.is_open()) {
            int cols, rows, mines;
            configFile >> cols >> rows >> mines;
            width = cols * 32;
            height = (rows * 32) + 100;
            configFile.close();
        }

        gamewindow gameWindow(width, height, playerName);
        gameWindow.run();
    }

    return 0;
}