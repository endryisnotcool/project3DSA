#include "search.h"

using namespace std;

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
