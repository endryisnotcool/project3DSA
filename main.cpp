#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


void setText(Text &text, float x, float y){
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x,y));
}

int main() {
    RenderWindow welcomeWindow(VideoMode(800, 800), "songSearcher");
    Font font;

    if (!font.loadFromFile("Metropolis-SemiBold.otf")){
        cout << "can't load :(";
        return 0;
    }

    Text welcomeText;
    welcomeText.setString("WELCOME TO SONGSEARCHER");
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(24);
    welcomeText.setStyle(Text::Bold | Text::Underlined);
    welcomeText.setFillColor(Color::White);
    FloatRect welcomeTextRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(welcomeTextRect.left + welcomeTextRect.width / 2.0f,
                          welcomeTextRect.top + welcomeTextRect.height / 2.0f);
    welcomeText.setPosition(Vector2f((float) 800 / 2.0f, ((float) 800 / 2.0f) - 150));

    RectangleShape rectangle(Vector2f(400,30));
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineColor(Color::Green);
    rectangle.setOutlineThickness(4.0);
    FloatRect rectangleRect = rectangle.getLocalBounds();
    rectangle.setOrigin(rectangleRect.left + rectangleRect.width/2.0f, rectangleRect.top + rectangleRect.height/2.0f);
    rectangle.setPosition(Vector2f((float) 800 / 2.0f, ((float) 800 / 2.0f) - 95));

    string playerName;
    Text playerInput;
    playerInput.setString("");
    playerInput.setFont(font);
    playerInput.setCharacterSize(18);
    playerInput.setStyle(Text::Bold);
    playerInput.setFillColor(Color::Black);
    FloatRect playerInputRect = playerInput.getLocalBounds();
    playerInput.setOrigin(playerInputRect.left + playerInputRect.width / 2.0f,
                          playerInputRect.top + playerInputRect.height / 2.0f);
    playerInput.setPosition(Vector2f((float) 800 / 2.0f, ((float) 800 / 2.0f) - 95));

    Text cursor;
    cursor.setString("|");
    cursor.setFont(font);
    cursor.setCharacterSize(18);
    cursor.setStyle(Text::Bold);
    cursor.setFillColor(Color::Green);
    bool showCursor = true;

    while(welcomeWindow.isOpen()){
        welcomeWindow.clear(Color::Black);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(rectangle);
        welcomeWindow.draw(playerInput);

        if (playerName.empty()) {
            setText(cursor, (float) 800 / 2.0f, ((float) 800 / 2.0f) - 95);
            welcomeWindow.draw(cursor);
        } else {
            cursor.setOrigin(playerInputRect.left + playerInputRect.width / 2.0f,
                             playerInputRect.top + playerInputRect.height / 2.0f);
            cursor.setPosition(
                    Vector2f(playerInput.getPosition() + Vector2f(playerInput.getLocalBounds().width, -1.0f)));
            welcomeWindow.draw(cursor);
        }

        welcomeWindow.display();

        Event welcomeEvent;

        while (welcomeWindow.pollEvent(welcomeEvent)) {
            if (welcomeEvent.type == Event::Closed) {
                welcomeWindow.close();
                return 0;
            } else if (welcomeEvent.type == Event::KeyPressed) {
                if (welcomeEvent.key.code == Keyboard::Enter && playerName.size() >= 1) {
                    welcomeWindow.close();
                } else if (welcomeEvent.key.code == Keyboard::Backspace) {
                    playerName.pop_back();
                    playerInput.setString(playerName);
                }
            } else if (welcomeEvent.type == Event::TextEntered) {
                if (playerName.size() < 30) {
                    if (playerName.empty()) {
                        playerName += toupper(welcomeEvent.text.unicode);
                        playerInput.setString(playerName);
                    } else {
                        playerName += tolower(welcomeEvent.text.unicode);
                        playerInput.setString(playerName);
                    }
                }
                setText(playerInput, (float) 800 / 2.0f, (float) 800 / 2.0f - 95);
                playerInputRect = playerInput.getLocalBounds();
            }
        }
    }
}
