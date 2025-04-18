#include "WelcomeWindow.h"
#include <iostream>

WelcomeWindow::WelcomeWindow()
    : playerName(""), cursorVisible(true) {

    if (!font.loadFromFile("C:/Users/lzy46/Desktop/COP 3503C/HelloSFML/files/font.ttf")) {
        std::cerr << "Error loading font.ttf" << std::endl;
        exit(1);
    }

    window.create(sf::VideoMode(800, 612), "Minesweeper", sf::Style::Close);

    // Welcome text
    welcomeText.setFont(font);
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setCharacterSize(24);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setPosition(400 - welcomeText.getLocalBounds().width/2, 306-150);

    // Prompt text
    promptText.setFont(font);
    promptText.setString("Enter your name:");
    promptText.setCharacterSize(20);
    promptText.setFillColor(sf::Color::White);
    promptText.setStyle(sf::Text::Bold);
    promptText.setPosition(400 - promptText.getLocalBounds().width/2, 306-75);

    // Name input
    nameText.setFont(font);
    nameText.setCharacterSize(18);
    nameText.setFillColor(sf::Color::Yellow);
    nameText.setStyle(sf::Text::Bold);
    nameText.setPosition(400, 306-45);

    // Cursor
    cursorText.setFont(font);
    cursorText.setString("|");
    cursorText.setCharacterSize(18);
    cursorText.setFillColor(sf::Color::Yellow);
    cursorText.setPosition(400, 306-45);
}

void WelcomeWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
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
        return;
    }

    std::string formattedName;
    formattedName += toupper(playerName[0]);
    for (size_t i = 1; i < playerName.size(); ++i) {
        formattedName += tolower(playerName[i]);
    }

    nameText.setString(formattedName);
    nameText.setOrigin(nameText.getLocalBounds().width/2, nameText.getLocalBounds().height/2);
    cursorText.setPosition(400 + nameText.getLocalBounds().width/2 + 2, 306-45);
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