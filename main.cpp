#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include "search.h"
using namespace std;
using namespace sf;

void setText(Text &text, float x, float y) {
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x,y));
}

int main() {
    //initialize songs
    ifstream dataSet("dataset.csv");
    string line;
    bool firstLine = true;
    int numSongsAdded = 0;

    //data types
    unordered_map<string, vector<song>> artistMap;
    unordered_map<string, vector<song>> genreMap;
    RBTree songTree;
    RBTree albumTree;
    while (getline(dataSet, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }

        /*
         * because of the ABSURD complexity of adding songs
         * whose titles contain quotes (look at entry 725 to see what I mean)
         * I have decided to skip songs with quotes in titles.
         * The database still has n > 100,000 with this restriction. (n = 104,977)
         *
         * -Jack
         * */
        if(line.find('\"') != string::npos) {
            continue;
        }

        //setup
        vector<string> songData;
        string value;
        stringstream ss(line);

        //get data from dataset
        while (getline(ss, value, ',')) {
            songData.push_back(value);
        }

        //parse songData vector
        string trackID = songData[1];
        vector<string> artists;
        stringstream s2(songData[2]);
        string artist;
        while (getline(s2, artist, ';'))
            artists.push_back(artist);
        string album = songData[3];
        string title = songData[4];
        int popularity = stoi(songData[5]);
        string duration = songData[6];
        bool isExplicit = true;
        if (songData[7] == "false")
            isExplicit = false;
        string genre = songData[20];

        //create song object
        song newSong(artists, title, album, isExplicit, popularity, trackID, genre);

        //add song object to data types
        genreMap[toLowerCase(genre)].push_back(newSong);

        for (string a: artists)
            artistMap[toLowerCase(a)].push_back(newSong);


        songTree.insert(toLowerCase(title), newSong);


        albumTree.insert(toLowerCase(album), newSong);

        numSongsAdded++;
    }

    cout << endl << "successfully added " << numSongsAdded << " songs" << endl;

    cout << search("MF DOOM", artistMap, genreMap, songTree, albumTree, true, "artist") << endl;


    RenderWindow welcomeWindow(VideoMode(800, 800), "songSearcher");
    Font font;

    if (!font.loadFromFile("Metropolis-SemiBold.otf")) {
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

    RectangleShape rectangle(Vector2f(400, 30));
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineColor(Color::Green);
    rectangle.setOutlineThickness(4.0);
    FloatRect rectangleRect = rectangle.getLocalBounds();
    rectangle.setOrigin(rectangleRect.left + rectangleRect.width / 2.0f,
                        rectangleRect.top + rectangleRect.height / 2.0f);
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

    while (welcomeWindow.isOpen()) {
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