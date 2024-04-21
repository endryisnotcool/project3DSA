#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "song.h"
#include "redblacktree.h"
#include "search.h"
using namespace std;
using namespace sf;


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


    /*vector<string> test = search("mary on a cross", artistMap, genreMap, songTree, albumTree, true, "song");
    for(string s : test) {
       cout << s << endl;
    }*/


    RenderWindow programWindow(VideoMode(800, 800), "songSearcher");
    Font font;




    if (!font.loadFromFile("Metropolis-SemiBold.otf")){
        cout << "can't load :(";
        return 0;
    }

    Text programName;
    programName.setString("WELCOME TO SONGSEARCHER");
    programName.setFont(font);
    programName.setCharacterSize(24);
    programName.setStyle(Text::Bold);
    programName.setFillColor(Color::White);
    FloatRect programNameRect = programName.getLocalBounds();
    programName.setOrigin(programNameRect.left + programNameRect.width / 2.0f,
                          programNameRect.top + programNameRect.height / 2.0f);
    programName.setPosition(Vector2f(400, 250));




    Text searchBy;
    searchBy.setString("Search By:");
    searchBy.setFont(font);
    searchBy.setCharacterSize(22);
    //searchBy.setStyle(Text::Bold);
    searchBy.setFillColor(Color::White);
    FloatRect searchByRect = searchBy.getLocalBounds();
    searchBy.setOrigin(searchByRect.left + searchByRect.width / 2.0f,
                       searchByRect.top + searchByRect.height / 2.0f);
    searchBy.setPosition(Vector2f(260, 375));




    Text songName;
    songName.setString("Song Name");
    songName.setFont(font);
    songName.setCharacterSize(18);
    songName.setFillColor(Color::White);
    //songName.setStyle(Text::Bold);
    FloatRect songNameRect = songName.getLocalBounds();
    songName.setOrigin(songNameRect.left + songNameRect.width / 2.0f,
                       songNameRect.top + songNameRect.height / 2.0f);
    songName.setPosition(Vector2f(328, 425));




    Text genreName;
    genreName.setString("Genre");
    genreName.setFont(font);
    genreName.setCharacterSize(18);
    genreName.setFillColor(Color::White);
    //genreName.setStyle(Text::Bold);
    FloatRect genreNameRect = genreName.getLocalBounds();
    genreName.setOrigin(genreNameRect.left + genreNameRect.width / 2.0f,
                        genreNameRect.top + genreNameRect.height / 2.0f);
    genreName.setPosition(Vector2f(305, 475));




    Text artistName;
    artistName.setString("Artist Name");
    artistName.setFont(font);
    artistName.setCharacterSize(18);
    artistName.setFillColor(Color::White);
    //artistName.setStyle(Text::Bold);
    FloatRect artistNameRect = artistName.getLocalBounds();
    artistName.setOrigin(artistNameRect.left + artistNameRect.width / 2.0f,
                         artistNameRect.top + artistNameRect.height / 2.0f);
    artistName.setPosition(Vector2f(330, 525));




    Text albumName;
    albumName.setString("Album Name");
    albumName.setFont(font);
    albumName.setCharacterSize(18);
    albumName.setFillColor(Color::White);
    //albumName.setStyle(Text::Bold);
    FloatRect albumNameRect = albumName.getLocalBounds();
    albumName.setOrigin(albumNameRect.left + albumNameRect.width / 2.0f,
                        albumNameRect.top + albumNameRect.height / 2.0f);
    albumName.setPosition(Vector2f(335, 575));




    Text explicitTitle;
    explicitTitle.setString("Explicit");
    explicitTitle.setFont(font);
    explicitTitle.setCharacterSize(18);
    explicitTitle.setFillColor(Color::White);
    //explicitTitle.setStyle(Text::Bold);
    FloatRect explicitTitleRect = explicitTitle.getLocalBounds();
    explicitTitle.setOrigin(explicitTitleRect.left + explicitTitleRect.width / 2.0f,
                            explicitTitleRect.top + explicitTitleRect.height / 2.0f);
    explicitTitle.setPosition(Vector2f(515, 500));




    RectangleShape rectangle(Vector2f(400,30));
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineColor(Color::Green);
    rectangle.setOutlineThickness(4.0);
    FloatRect rectangleRect = rectangle.getLocalBounds();
    rectangle.setOrigin(rectangleRect.left + rectangleRect.width/2.0f, rectangleRect.top + rectangleRect.height/2.0f);
    rectangle.setPosition(Vector2f(400, 305));




    CircleShape songButton(15);
    songButton.setFillColor(Color::White);
    songButton.setOutlineColor(Color::Green);
    songButton.setOutlineThickness(2.0);
    FloatRect songRect = songButton.getLocalBounds();
    songButton.setOrigin(songRect.left + songRect.width/2.0f, songRect.top + songRect.height/2.0f);
    songButton.setPosition(Vector2f(250, 425));




    CircleShape genreButton(15);
    genreButton.setFillColor(Color::White);
    genreButton.setOutlineColor(Color::Green);
    genreButton.setOutlineThickness(2.0);
    FloatRect genreRect = genreButton.getLocalBounds();
    genreButton.setOrigin(genreRect.left + genreRect.width/2.0f, genreRect.top + genreRect.height/2.0f);
    genreButton.setPosition(Vector2f(250, 475));




    CircleShape artistButton(15);
    artistButton.setFillColor(Color::White);
    artistButton.setOutlineColor(Color::Green);
    artistButton.setOutlineThickness(2.0);
    FloatRect artistRect = artistButton.getLocalBounds();
    artistButton.setOrigin(artistRect.left + artistRect.width/2.0f, artistRect.top + artistRect.height/2.0f);
    artistButton.setPosition(Vector2f(250, 525));




    CircleShape albumButton(15);
    albumButton.setFillColor(Color::White);
    albumButton.setOutlineColor(Color::Green);
    albumButton.setOutlineThickness(2.0);
    FloatRect albumRect = albumButton.getLocalBounds();
    albumButton.setOrigin(albumRect.left + albumRect.width/2.0f, albumRect.top + albumRect.height/2.0f);
    albumButton.setPosition(Vector2f(250, 575));




    CircleShape explicitButton(15);
    explicitButton.setFillColor(Color::White);
    explicitButton.setOutlineColor(Color::Red);
    explicitButton.setOutlineThickness(2.0);
    FloatRect explicitRect = explicitButton.getLocalBounds();
    explicitButton.setOrigin(explicitRect.left + explicitRect.width/2.0f, explicitRect.top + explicitRect.height/2.0f);
    explicitButton.setPosition(Vector2f(450, 500));




    CircleShape fillButton(10);
    fillButton.setFillColor(Color::Green);


    CircleShape explicitFill(10);
    explicitFill.setFillColor(Color::Red);




    string userInputString;
    Text userInput;
    userInput.setString("");
    userInput.setFont(font);
    userInput.setCharacterSize(18);
    userInput.setStyle(Text::Bold);
    userInput.setFillColor(Color::Black);
    FloatRect userInputRect = userInput.getLocalBounds();
    userInput.setOrigin(userInputRect.left + userInputRect.width / 2.0f,
                        userInputRect.top + userInputRect.height / 2.0f);
    userInput.setPosition(Vector2f((float) 800 / 2.0f, ((float) 800 / 2.0f) - 95));




    Text cursor;
    cursor.setString("|");
    cursor.setFont(font);
    cursor.setCharacterSize(18);
    cursor.setStyle(Text::Bold);
    cursor.setFillColor(Color::Green);
    bool shift = false;
    bool songClicked = true;
    bool genreClicked = false;
    bool albumNameClicked = false;
    bool artistNameClicked = false;
    bool explicitClicked = false;


    while(programWindow.isOpen()){
        programWindow.clear(Color::Black);
        programWindow.draw(programName);
        programWindow.draw(rectangle);
        programWindow.draw(userInput);
        programWindow.draw(searchBy);
        programWindow.draw(songName);
        programWindow.draw(genreName);
        programWindow.draw(artistName);
        programWindow.draw(albumName);
        programWindow.draw(explicitTitle);
        programWindow.draw(songButton);
        programWindow.draw(genreButton);
        programWindow.draw(artistButton);
        programWindow.draw(albumButton);
        programWindow.draw(explicitButton);
        if (songClicked){
            FloatRect fillButtonRect = fillButton.getLocalBounds();
            fillButton.setOrigin(fillButtonRect.left + fillButtonRect.width/2.0f, fillButtonRect.top + fillButtonRect.height/2.0f);
            fillButton.setPosition(Vector2f(250,425));
            programWindow.draw(fillButton);
        }
        else if (genreClicked){
            FloatRect fillButtonRect = fillButton.getLocalBounds();
            fillButton.setOrigin(fillButtonRect.left + fillButtonRect.width/2.0f, fillButtonRect.top + fillButtonRect.height/2.0f);
            fillButton.setPosition(Vector2f(250,475));
            programWindow.draw(fillButton);
        }
        else if (artistNameClicked){
            FloatRect fillButtonRect = fillButton.getLocalBounds();
            fillButton.setOrigin(fillButtonRect.left + fillButtonRect.width/2.0f, fillButtonRect.top + fillButtonRect.height/2.0f);
            fillButton.setPosition(Vector2f(250,525));
            programWindow.draw(fillButton);
        }
        else if (albumNameClicked){
            FloatRect fillButtonRect = fillButton.getLocalBounds();
            fillButton.setOrigin(fillButtonRect.left + fillButtonRect.width/2.0f, fillButtonRect.top + fillButtonRect.height/2.0f);
            fillButton.setPosition(Vector2f(250,575));
            programWindow.draw(fillButton);
        }
        if (explicitClicked){
            FloatRect explicitButtonRect = explicitFill.getLocalBounds();
            explicitFill.setOrigin(explicitButtonRect.left + explicitButtonRect.width/2.0f, explicitButtonRect.top + explicitButtonRect.height/2.0f);
            explicitFill.setPosition(Vector2f(450,500));
            programWindow.draw(explicitFill);
        }


        if (userInputString.empty()) {
            FloatRect cursorRect = cursor.getLocalBounds();
            cursor.setOrigin(cursorRect.left + cursorRect.width/2.0f, cursorRect.top + cursorRect.height/2.0f);
            cursor.setPosition(400, 305);
            programWindow.draw(cursor);
        }
        else {
            cursor.setOrigin(userInputRect.left + userInputRect.width / 2.0f,
                             userInputRect.top + userInputRect.height / 2.0f);
            cursor.setPosition(
                    Vector2f(userInput.getPosition() + Vector2f(userInput.getLocalBounds().width, -1.0f)));
            programWindow.draw(cursor);
        }


        programWindow.display();


        Event programEvent;
        Vector2i positionMouse = Mouse::getPosition(programWindow);


        while (programWindow.pollEvent(programEvent)) {
            if (programEvent.type == Event::Closed) {
                programWindow.close();
                return 0;
            }
            else if (Mouse::isButtonPressed(Mouse::Left)){
                if (songButton.getGlobalBounds().contains(positionMouse.x, positionMouse.y)){
                    songClicked = !songClicked;
                }
                else if (genreButton.getGlobalBounds().contains(positionMouse.x, positionMouse.y)){
                    genreClicked = !genreClicked;
                }
                else if (artistButton.getGlobalBounds().contains(positionMouse.x, positionMouse.y)){
                    artistNameClicked = !artistNameClicked;
                }
                else if (albumButton.getGlobalBounds().contains(positionMouse.x, positionMouse.y)){
                    albumNameClicked = !albumNameClicked;
                }
                else if (explicitButton.getGlobalBounds().contains(positionMouse.x, positionMouse.y)){
                    explicitClicked = !explicitClicked;
                }
            }
            else if (programEvent.type == Event::KeyPressed) {
                if (programEvent.key.code == Keyboard::Enter && userInputString.size() >= 1) {
                    programWindow.close();
                } else if (programEvent.key.code == Keyboard::Backspace) {
                    userInputString.pop_back();
                    userInput.setString(userInputString);
                } else if (programEvent.key.code == Keyboard::LShift || programEvent.key.code == Keyboard::RShift){
                    shift = true;
                } else if (programEvent.key.code == Keyboard::Enter){
                    programWindow.close();
                }
            }
            else if (programEvent.type == Event::TextEntered) {
                char userInputChar = (char)programEvent.text.unicode;
                if (isalnum(userInputChar) || strchr(",./:;><?\"\'\\+=-_)(*&^%$#@!~`{}[] ", userInputChar)) {
                    if (userInputString.length() >= 0 && userInputString.length() <= 30){
                        if (shift == true) {
                            userInputString += toupper(userInputChar);
                            userInput.setString(userInputString);
                            shift = false;
                        } else {
                            userInputString += tolower(userInputChar);
                            userInput.setString(userInputString);
                        }
                    }
                }
                FloatRect tempRect = userInput.getLocalBounds();
                userInput.setOrigin(tempRect.left + tempRect.width/2.0f, tempRect.top + tempRect.height/2.0f);
                userInput.setPosition(400, 305);
                userInputRect = userInput.getLocalBounds();
            }
        }
    }

    RenderWindow resultWindow(VideoMode(800,800), "Results");

    if (songClicked){
        auto startTime = chrono::steady_clock::now();
        vector<string> songResults = search(toLowerCase(userInputString), artistMap, genreMap, songTree, albumTree, explicitClicked, "song");
        auto endTime = chrono::steady_clock::now();
        auto programDurationTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    }
    else if (genreClicked){
        auto startTime = chrono::steady_clock::now();
        vector<string> genreResults = search(toLowerCase(userInputString), artistMap, genreMap, songTree, albumTree, explicitClicked, "genre");
        auto endTime = chrono::steady_clock::now();
        auto programDurationTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    }
    else if (artistNameClicked){
        auto startTime = chrono::steady_clock::now();
        vector<string> artistResults = search(toLowerCase(userInputString), artistMap, genreMap, songTree, albumTree, explicitClicked, "artist");
        auto endTime = chrono::steady_clock::now();
        auto programDurationTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    }
    else if (albumNameClicked){
        auto startTime = chrono::steady_clock::now();
        vector<string> albumNameClicked = search(toLowerCase(userInputString), artistMap, genreMap, songTree, albumTree, explicitClicked, "album");
        auto endTime = chrono::steady_clock::now();
        auto programDurationTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    }

    while (resultWindow.isOpen()){
        resultWindow.clear(Color::Black);

        Event resultEvent;
        while (resultWindow.pollEvent(resultEvent)){
            if (resultEvent.type == Event::Closed){
                resultWindow.close();
                return 0;
            }
        }
    }
}