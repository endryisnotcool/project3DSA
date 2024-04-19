//song class

#ifndef PROJECT3DSA_SONG_H
#define PROJECT3DSA_SONG_H

#include <vector>
#include <string>

using namespace std;

class song {
private:
    const vector<string> ARTIST;
    const string TITLE;
    const string ALBUM;
    const bool EXPLICIT;
    const int POPULARITY;
    const string TRACKID;
    const string GENRE;

public:

    //constructor
    song(vector<string> artist, string title, string album, bool isExplicit, int popularity, string trackID, string genre)
            : ARTIST(artist), TITLE(title), ALBUM(album), EXPLICIT(isExplicit), POPULARITY(popularity), TRACKID(trackID), GENRE(genre) {}

    //getter functions
    vector<string> getArtist() const;
    string getTitle() const;
    string getAlbum() const;
    bool isExplicit() const;
    int getPopularity() const;
    string getTrackID() const;
    string getGenre() const;
};

vector<string> song::getArtist() const {
    return ARTIST;
}

string song::getTitle() const {
    return TITLE;
}

string song::getAlbum() const {
    return ALBUM;
}

bool song::isExplicit() const {
    return EXPLICIT;
}

int song::getPopularity() const {
    return POPULARITY;
}

string song::getTrackID() const {
    return TRACKID;
}

string song::getGenre() const {
    return GENRE;
}


#endif
