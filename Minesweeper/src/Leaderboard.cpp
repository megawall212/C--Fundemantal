#include "Leaderboard.h"
#include <sstream>
#include <iomanip>

Leaderboard::Leaderboard() : m_visible(false) {
    window.create(sf::VideoMode(400, 300), "Leaderboard", sf::Style::Titlebar | sf::Style::Close);
    window.setVisible(false);

    font.loadFromFile("files/font.ttf");

    titleText.setFont(font);
    titleText.setString("Top 5 Scores");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(120, 20);

    entriesText.setFont(font);
    entriesText.setCharacterSize(20);
    entriesText.setFillColor(sf::Color::White);
    entriesText.setPosition(40, 70);

    loadScores();
    updateText();
}

void Leaderboard::show() {
    m_visible = true;
    window.setVisible(true);
    updateText();
}

void Leaderboard::hide() {
    m_visible = false;
    window.setVisible(false);
    saveScores();
}

bool Leaderboard::isVisible() const {
    return m_visible;
}

void Leaderboard::draw(sf::RenderWindow& parentWindow) {
    if (!m_visible) return;

    window.clear(sf::Color(0, 0, 128));
    window.draw(titleText);
    window.draw(entriesText);
    window.display();
}

void Leaderboard::handleEvent(const sf::Event& event) {
    if (!m_visible) return;
    if (event.type == sf::Event::Closed) {
        hide();
    }
}

void Leaderboard::addEntry(const std::string& name, int time) {
    lastAddedName = name;
    lastAddedTime = time;

    scores.emplace_back(time, name);
    std::sort(scores.begin(), scores.end());
    if (scores.size() > 5)
        scores.resize(5);
    updateText();
}


void Leaderboard::loadScores() {
    scores.clear();
    std::ifstream in("files/leaderboard.txt");
    std::string line;
    while (getline(in, line)) {
        std::stringstream ss(line);
        std::string name;
        int time;

        //line = 07:01,Alex

        string minutes;
        string seconds;

        getline(ss, minutes, ':');
        getline(ss, seconds, ',');
        getline(ss, name);

        time = stoi(minutes)*60 + stoi(seconds);

        scores.emplace_back(time, name);

        /*
        if (ss >> time && getline(ss, name)) {
            if (!name.empty() && name[0] == ',') name.erase(0, 1);
            scores.emplace_back(time, name);
        }
        */

    }
    in.close();
}

void Leaderboard::saveScores() {
    std::ofstream out("files/leaderboard.txt");
    for (auto& [time, name] : scores) {
        string minutes;
        string seconds;

        int minutes_t = time / 60;
        int seconds_t = time % 60;

        minutes = to_string(minutes_t);
        seconds = to_string(seconds_t);

        if (minutes.size() == 1) {
            minutes = "0" + minutes;
        }
        if (seconds.size() == 1) {
            seconds = "0" + seconds;
        }

        out << minutes << ":" << seconds << "," << name << "\n";
    }
    out.close();
}

void Leaderboard::updateText() {
    std::stringstream ss;
    int rank = 1;
    for (auto& [time, name] : scores) {
        int mins = time / 60;
        int secs = time % 60;

        bool isNew = (time == lastAddedTime && name == lastAddedName);

        ss << rank << ". ";
        if (isNew) ss << "*";  // Only shown in display
        ss << name << " - ";
        ss << std::setw(2) << std::setfill('0') << mins << ":";
        ss << std::setw(2) << std::setfill('0') << secs << "\n";
        rank++;
    }
    entriesText.setString(ss.str());
}
