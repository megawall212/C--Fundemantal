#include "WelcomeWindow.h"
#include <iostream>

using namespace std;

WelcomeWindow::WelcomeWindow()
    : playerName(""), cursorVisible(true) {

    if (!font.loadFromFile("files/font.ttf")) {
        cerr << "Error loading font.ttf" << endl;
        exit(1); // Exit the windows if the font fails to load
    }

    //SFML window

    std::ifstream file("files/config.cfg");
    int cols, rows;
    file >> cols >> rows;

    window.create(sf::VideoMode(cols*32, rows*32+100), "Minesweeper", sf::Style::Close);

    // Welcome and Title text required

    welcomeText.setFont(font);
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setCharacterSize(24);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setPosition(400 - welcomeText.getLocalBounds().width / 2, 306 - 150);

    // Asking for user input/ prompt text

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
    nameText.setOrigin(0, 0); // 🔧 Debug: I change it to (0,0), which is Top-left
    nameText.setPosition(400, 306 - 45);

    // Cursor text
    cursorText.setFont(font);
    cursorText.setString("|");
    cursorText.setCharacterSize(18);
    cursorText.setFillColor(sf::Color::Yellow);
    cursorText.setOrigin(0, 0);
    // Debug: Adjust Y by small amount (fine-tuned)
    // Make sure the cursor is at the same level with the textline
    cursorText.setPosition(400, 306 - 45 + 3);
}


// Run the program and draw everything

string WelcomeWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        update(); //cursor
        render();
    }
    return playerName;
}

// Handle keyboard movement

void WelcomeWindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close(); //close the window
            exit(0);
        }

        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') { //if we press the backspace
                if (!playerName.empty()) {
                    playerName.pop_back(); // remove the last character
                    formatPlayerName();  // update the username
                }
            }
            else if (isalpha(static_cast<char>(event.text.unicode)) && playerName.size() < 10) {
                // if it's less than 10 chars, Add letters (maybe it's useless...)

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

        // Debug: Reset cursor to default baseline Y
        // Make sure the cursor is at center
        cursorText.setPosition(400, nameText.getPosition().y);
        return;
    }

    // Capitalize name and lowercase the rest of chars
    string formattedName;
    formattedName += toupper(playerName[0]);
    for (size_t i = 1; i < playerName.size(); ++i) {
        formattedName += tolower(playerName[i]);
    }

    nameText.setString(formattedName);

    // Debug: Keep vertical origin, only update horizontal center

    nameText.setOrigin(nameText.getLocalBounds().width / 2.f, nameText.getOrigin().y);
    nameText.setPosition(400, nameText.getPosition().y);

    // Debug: Place cursor after the text on same Y line
    // make sure they're at the same baseline

    float cursorX = nameText.getPosition().x + nameText.getLocalBounds().width / 2.f + 1.f;
    cursorText.setPosition(cursorX, nameText.getPosition().y);
}

void WelcomeWindow::update() {
    if (cursorBlinkTimer.getElapsedTime().asSeconds() > 0.5f) {
        cursorVisible = !cursorVisible;
        cursorBlinkTimer.restart(); //reset the timer
    }
}


// That is my draw function
// basically draw all elements to the window

void WelcomeWindow::render() {
    window.clear(sf::Color::Blue);  //Background color
    window.draw(welcomeText);       // Welcome message
    window.draw(promptText);
    window.draw(nameText);

    if (cursorVisible && playerName.size() < 10) {
        window.draw(cursorText); // Don't forget the cursor
    }

    window.display();
}
