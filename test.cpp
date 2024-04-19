#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "redblacktree.h"

using namespace std;

string toLowerCase(string s) {
    string lowerS;
    for (char c : s)
        lowerS += (tolower(c));

    return lowerS;
}

void search(const string& query, const unordered_map<string, vector<song>>& artistMap,
            const unordered_map<string, vector<song>>& genreMap, const RBTree& songTree,
            const RBTree& albumTree, bool includeExplicit, const string& searchType) {
    if (searchType == "song") {
        // search by song title
        cout << "Songs with title matching '" << query << "':" << endl;
        vector<song> songsWithTitle = songTree.search(toLowerCase(query));
        for (const auto& s : songsWithTitle) {
            if (!includeExplicit && s.isExplicit())
                continue;
            cout << "Title: " << s.getTitle() << ", Artist(s): ";
            for (const auto& artist : s.getArtist()) {
                cout << artist << ", ";
            }
            cout << "Album: " << s.getAlbum() << ", Genre: " << s.getGenre()
                 << ", Popularity: " << s.getPopularity() << ", Track ID: " << s.getTrackID() << endl;
        }
    } else if (searchType == "artist") {
        // search by artist
        cout << "Songs by artist matching '" << query << "':" << endl;
        vector<song> songsByArtist = artistMap.find(toLowerCase(query))->second;
        for (const auto& s : songsByArtist) {
            if (!includeExplicit && s.isExplicit())
                continue;
            cout << "Title: " << s.getTitle() << ", Artist(s): ";
            for (const auto& artist : s.getArtist()) {
                cout << artist << ", ";
            }
            cout << "Album: " << s.getAlbum() << ", Genre: " << s.getGenre()
                 << ", Popularity: " << s.getPopularity() << ", Track ID: " << s.getTrackID() << endl;
        }
    } else if (searchType == "album") {
        // search by album
        cout << "Songs from album matching '" << query << "':" << endl;
        vector<song> songsFromAlbum = albumTree.search(toLowerCase(query));
        for (const auto& s : songsFromAlbum) {
            if (!includeExplicit && s.isExplicit())
                continue;
            cout << "Title: " << s.getTitle() << ", Artist(s): ";
            for (const auto& artist : s.getArtist()) {
                cout << artist << ", ";
            }
            cout << "Album: " << s.getAlbum() << ", Genre: " << s.getGenre()
                 << ", Popularity: " << s.getPopularity() << ", Track ID: " << s.getTrackID() << endl;
        }
    } else if (searchType == "genre") {
        // search by genre
        cout << "Songs with genre matching '" << query << "':" << endl;
        vector<song> songsWithGenre = genreMap.find(toLowerCase(query))->second;
        for (const auto& s : songsWithGenre) {
            if (!includeExplicit && s.isExplicit())
                continue;
            cout << "Title: " << s.getTitle() << ", Artist(s): ";
            for (const auto& artist : s.getArtist()) {
                cout << artist << ", ";
            }
            cout << "Album: " << s.getAlbum() << ", Genre: " << s.getGenre()
                 << ", Popularity: " << s.getPopularity() << ", Track ID: " << s.getTrackID() << endl;
        }
    } else {
        cout << "Invalid search type. Please choose from 'song', 'artist', 'album', or 'genre'." << endl;
    }
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
