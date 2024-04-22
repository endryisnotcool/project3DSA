#include "search.h"

using namespace std;

string toLowerCase(string s) {
    string lowerS;
    for(char c : s)
        lowerS += (tolower(c));

    return lowerS;
}

vector<string> search(const string& query, const unordered_map<string, vector<song>>& artistMap,
                     const unordered_map<string, vector<song>>& genreMap, RBTree songTree,
                     RBTree albumTree, bool includeExplicit, const string& searchType) {
    long long programDurationTime;
    vector<song> songs;
    if (searchType == "song") {
        // search by song title
        cout << "Songs with title matching '" << query << "': ";
        auto startTime = chrono::steady_clock::now();
        songs = songTree.treeSearch(toLowerCase(query));
        auto endTime = chrono::steady_clock::now();
        programDurationTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    } else if (searchType == "artist") {
        // search by artist
        cout << "Songs by artist matching '" << query << "': ";
        auto startTime = chrono::steady_clock::now();
        auto searchResult = artistMap.find(toLowerCase(query));
        auto endTime = chrono::steady_clock::now();
        programDurationTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();

        if(searchResult != artistMap.end()) {
            songs = searchResult->second;
        } else {
            return {""};
        }
    } else if (searchType == "album") {
        // search by album
        cout << "Songs from album matching '" << query << "': ";
        auto startTime = chrono::steady_clock::now();
        songs = albumTree.treeSearch(toLowerCase(query));
        auto endTime = chrono::steady_clock::now();
        programDurationTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();

    } else if (searchType == "genre") {
        // search by genre
        cout << "Songs with genre matching '" << query << "': ";
        auto startTime = chrono::steady_clock::now();
        auto searchResult = genreMap.find(toLowerCase(query));
        auto endTime = chrono::steady_clock::now();
        programDurationTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();

        if(searchResult != artistMap.end()) {
            songs = searchResult->second;
        } else {
            return {""};
        }
    }
    else {
        cout << "Invalid search type. Please choose from 'song', 'artist', 'album', or 'genre'." << endl;
        return {""};
    }
    cout << songs.size() << endl;
    cout << "Time Searched for " << searchType << " category: " << to_string(programDurationTime) << "ns" << endl;

    //get songs ready for return by sorting and putting in proper format
    sort(songs.begin(), songs.end(), compareByPopularity);
    vector<string> returnList;
    for (const auto& s : songs) {
        if (!includeExplicit && s.isExplicit())
            continue;
        string returnString;
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
        returnList.push_back(returnString);
    }
    return returnList;
}