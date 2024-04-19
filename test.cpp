#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "redblacktree.h"
#include "search.h"

using namespace std;

string toLowerCase(string s) {
    string lowerS;
    for (char c : s)
        lowerS += (tolower(c));

    return lowerS;
}

int main() {
    ifstream dataSet("dataset.csv");
    string line;
    bool firstLine = true;
    int numSongsAdded = 0;

    unordered_map<string, vector<song>> artistMap;
    unordered_map<string, vector<song>> genreMap;
    RBTree songTree;
    RBTree albumTree;
    while (getline(dataSet, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }

        if (line.find('\"') != string::npos) {
            continue;
        }

        vector<string> songData;
        string value;
        stringstream ss(line);

        while (getline(ss, value, ',')) {
            songData.push_back(value);
        }

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

        song newSong(artists, title, album, isExplicit, popularity, trackID, genre);

        genreMap[toLowerCase(genre)].push_back(newSong);

        for (string a : artists)
            artistMap[toLowerCase(a)].push_back(newSong);

        songTree.insert(toLowerCase(title), newSong);
        albumTree.insert(toLowerCase(album), newSong);

        numSongsAdded++;
    }

    cout << endl << "Successfully added " << numSongsAdded << " songs" << endl;

    string searchType;
    cout << "What would you like to search for? (song/artist/album/genre): ";
    cin >> searchType;

    string query;
    cout << "Enter your search query: ";
    cin.ignore();
    getline(cin, query);

    bool includeExplicit = false;
    char includeExplicitChoice;
    cout << "Include explicit songs in the search? (y/n): ";
    cin >> includeExplicitChoice;
    if (includeExplicitChoice == 'y' || includeExplicitChoice == 'Y') {
        includeExplicit = true;
    }

    search(query, artistMap, genreMap, songTree, albumTree, includeExplicit, searchType);

    return 0;
}
