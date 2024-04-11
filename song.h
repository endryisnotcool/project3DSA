//song class

#ifndef UNTITLED1_SONG_H
#define UNTITLED1_SONG_H

#include <vector>
#include <string>

using namespace std;


class song {
private:
    const vector<string> ARTIST;
    const vector<string> GENRE;
    const string TITLE;
    const string ALBUM;
    const bool EXPLICIT;
    const int POPULARITY;
    const string TRACKID;

public:

    //constructor
    song(vector<string> artist, vector<string> genre, string title, string album, bool isExplicit, int popularity, string trackID)
    : ARTIST(artist), GENRE(genre), TITLE(title), ALBUM(album), EXPLICIT(isExplicit), POPULARITY(popularity), TRACKID(trackID) {}

    //getter functions
    vector<string> getArtist();
    vector<string> getGenre();
    string getTitle();
    string getAlbum();
    bool getExplicit();
    int getPopularity();
    string getTrackID();
};

vector<string> song::getArtist() {
    return ARTIST;
}

vector<string> song::getGenre() {
    return GENRE;
}

string song::getTitle() {
    return TITLE;
}

string song::getAlbum() {
    return ALBUM;
}

bool song::getExplicit() {
    return EXPLICIT;
}

int song::getPopularity() {
    return POPULARITY;
}

string song::getTrackID() {
    return TRACKID;
}



#endif
