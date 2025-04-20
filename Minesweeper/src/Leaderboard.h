#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

class Leaderboard {
    std::string lastAddedName = "";
    int lastAddedTime = -1;

public:
    Leaderboard();

    void show();
    void hide();
    bool isVisible() const;

    void draw(sf::RenderWindow& parentWindow);
    void handleEvent(const sf::Event& event);
    void addEntry(const std::string& name, int time);

    sf::RenderWindow window; // Debug: It needs to be public to handle draw loop from gamewindow

private:
    sf::Font font;
    sf::Text titleText;
    sf::Text entriesText;
    std::vector<std::pair<int, std::string>> scores;
    bool m_visible;

    void loadScores();
    void saveScores();
    void updateText();
};

#endif
