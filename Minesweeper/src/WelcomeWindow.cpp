#include "WelcomeWindow.h"
#include <iostream>

using namespace std;

WelcomeWindow::WelcomeWindow()
    : playerName(""), cursorVisible(true) {

    if (!font.loadFromFile("files/font.ttf")) {
        cerr << "Error loading font.ttf" << endl;
        exit(1);
    }

    window.create(sf::VideoMode(800, 612), "Minesweeper", sf::Style::Close);

    // Welcome text
    welcomeText.setFont(font);
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setCharacterSize(24);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setPosition(400 - welcomeText.getLocalBounds().width / 2, 306 - 150);

    // Prompt text
    promptText.setFont(font);
    promptText.setString("Enter your name:");
    promptText.setCharacterSize(20);
    promptText.setFillColor(sf::Color::White);
    promptText.setStyle(sf::Text::Bold);
    promptText.setPosition(400 - promptText.getLocalBounds().width / 2, 306 - 75);

    // Name text
    nameText.setFont(font);
    nameText.setCharacterSize(18);
    nameText.setFillColor(sf::Color::Yellow);
    nameText.setStyle(sf::Text::Bold);
    nameText.setOrigin(0, 0); // 🔧 CHANGE: Origin at top-left
    nameText.setPosition(400, 306 - 45);

    // Cursor text
    cursorText.setFont(font);
    cursorText.setString("|");
    cursorText.setCharacterSize(18);
    cursorText.setFillColor(sf::Color::Yellow);
    cursorText.setOrigin(0, 0); // 🔧 CHANGE: Origin at top-left
    cursorText.setPosition(400, 306 - 45 + 3); // 🔧 Adjust Y by small amount (fine-tuned)
}


string WelcomeWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
    return playerName;
}

void WelcomeWindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);
        }

        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') {
                if (!playerName.empty()) {
                    playerName.pop_back();
                    formatPlayerName();
                }
            }
            else if (isalpha(static_cast<char>(event.text.unicode)) && playerName.size() < 10) {
                playerName += static_cast<char>(event.text.unicode);
                formatPlayerName();
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            if (!playerName.empty()) {
                window.close();
            }
        }
    }
}

void WelcomeWindow::formatPlayerName() {
    if (playerName.empty()) {
        nameText.setString("");

        // 🟡 CHANGE: Reset cursor to default baseline Y
        cursorText.setPosition(400, nameText.getPosition().y);
        return;
    }

    // Capitalize name
    string formattedName;
    formattedName += toupper(playerName[0]);
    for (size_t i = 1; i < playerName.size(); ++i) {
        formattedName += tolower(playerName[i]);
    }

    nameText.setString(formattedName);

    // 🟡 CHANGE: Keep vertical origin, only update horizontal center
    nameText.setOrigin(nameText.getLocalBounds().width / 2.f, nameText.getOrigin().y);
    nameText.setPosition(400, nameText.getPosition().y);

    // 🟡 CHANGE: Place cursor after the text on same Y line (baseline)
    float cursorX = nameText.getPosition().x + nameText.getLocalBounds().width / 2.f + 1.f;
    cursorText.setPosition(cursorX, nameText.getPosition().y);
}

void WelcomeWindow::update() {
    if (cursorBlinkTimer.getElapsedTime().asSeconds() > 0.5f) {
        cursorVisible = !cursorVisible;
        cursorBlinkTimer.restart();
    }
}

void WelcomeWindow::render() {
    window.clear(sf::Color::Blue);
    window.draw(welcomeText);
    window.draw(promptText);
    window.draw(nameText);

    if (cursorVisible && playerName.size() < 10) {
        window.draw(cursorText);
    }

    window.display();
}
