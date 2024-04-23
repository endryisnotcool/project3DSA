#include "search.h"

using namespace std;

//turns a string to all lowercase
string toLowerCase(string s) {
    string lowerS;
    for(char c : s)
        lowerS += (tolower(c));

    return lowerS;
}

vector<string> search(const string& query, const unordered_map<string, vector<song>>& artistMap,
                     const unordered_map<string, vector<song>>& genreMap, RBTree songTree,
                     RBTree albumTree, bool includeExplicit, const string& searchType) {

    //for keeping track of how long it took to get results
    long long programDurationTime;

    //vector for search results
    vector<song> songs;

    // search by song title
    if (searchType == "song") {
        auto startTime = chrono::steady_clock::now();
        songs = songTree.treeSearch(toLowerCase(query));
        auto endTime = chrono::steady_clock::now();
        programDurationTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();

    // search by artist
    } else if (searchType == "artist") {
        auto startTime = chrono::steady_clock::now();
        auto searchResult = artistMap.find(toLowerCase(query));
        auto endTime = chrono::steady_clock::now();
        programDurationTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
        if(searchResult != artistMap.end()) {
            songs = searchResult->second;
        } else {
            return {""};
        }

    // search by album
    } else if (searchType == "album") {
        auto startTime = chrono::steady_clock::now();
        songs = albumTree.treeSearch(toLowerCase(query));
        auto endTime = chrono::steady_clock::now();
        programDurationTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();

    // search by genre
    } else if (searchType == "genre") {
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
    cout << "Time Searched for " << searchType << " category: " << to_string(programDurationTime) << " ns" << endl;

    //get songs ready for return by sorting and putting in proper format
    sort(songs.begin(), songs.end(), compareByPopularity);

    //turns songs into string format for displaying
    vector<string> returnList;
    for (const auto& s : songs) {
        if (!includeExplicit && s.isExplicit())
            continue;
        string returnString;
        returnString += s.getTitle() + ";";

        for (const auto& artist : s.getArtist())
            returnString += artist + ", ";

        returnString = returnString.substr(0, returnString.length() - 2);
        returnString +=  + ";";

        returnString += s.getAlbum() + ";" + s.getGenre();
        returnList.push_back(returnString);
    }

    return returnList;
}