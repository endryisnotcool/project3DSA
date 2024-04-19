#include "search.h"

using namespace std;

string toLowerCase(string s) {
    string lowerS;
    for(char c : s)
        lowerS += (tolower(c));

    return lowerS;
}

string search(const string& query, const unordered_map<string, vector<song>>& artistMap,
                     const unordered_map<string, vector<song>>& genreMap, RBTree songTree,
                     RBTree albumTree, bool includeExplicit, const string& searchType) {
    vector<song> songs;
    if (searchType == "song") {
        // search by song title
        cout << "Songs with title matching '" << query << "':" << endl;
        songs = songTree.treeSearch(toLowerCase(query));
    } else if (searchType == "artist") {
        // search by artist
        cout << "Songs by artist matching '" << query << "':" << endl;
        auto searchResult = artistMap.find(toLowerCase(query));
        if(searchResult != artistMap.end()) {
            songs = searchResult->second;
        } else {
            return "";
        }
    } else if (searchType == "album") {
        // search by album
        cout << "Songs from album matching '" << query << "':" << endl;
        songs = albumTree.treeSearch(toLowerCase(query));

    } else if (searchType == "genre") {
        // search by genre
        cout << "Songs with genre matching '" << query << "':" << endl;
        auto searchResult = genreMap.find(toLowerCase(query));
        if(searchResult != artistMap.end()) {
            songs = searchResult->second;
        } else {
            return "";
        }
    }
    else {
        cout << "Invalid search type. Please choose from 'song', 'artist', 'album', or 'genre'." << endl;
        return "";
    }
    string returnString;

    sort(songs.begin(), songs.end(), compareByPopularity);

    for (const auto& s : songs) {
        if (!includeExplicit && s.isExplicit())
            continue;
        //cout << "Title: " << s.getTitle() << ", Artist(s): ";
        returnString += s.getTitle() + ";";

        for (const auto& artist : s.getArtist()) {
            //cout << artist << ", ";
            returnString += artist + ", ";
        }
        returnString = returnString.substr(0, returnString.length() - 2);
        returnString +=  + ";";

        //cout << "Album: " << s.getAlbum() << ", Genre: " << s.getGenre()
        //    << ", Popularity: " << s.getPopularity() << ", Track ID: " << s.getTrackID() << endl;
        returnString += s.getAlbum() + ";" + s.getGenre();
    }
    return returnString;
}