//song class

#ifndef UNTITLED1_SONG_H
#define UNTITLED1_SONG_H

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
    vector<string> getArtist();
    string getTitle();
    string getAlbum();
    bool isExplicit();
    int getPopularity();
    string getTrackID();
    string getGenre();
};

vector<string> song::getArtist() {
    return ARTIST;
}

string song::getTitle() {
    return TITLE;
}

string song::getAlbum() {
    return ALBUM;
}

bool song::isExplicit() {
    return EXPLICIT;
}

int song::getPopularity() {
    return POPULARITY;
}

string song::getTrackID() {
    return TRACKID;
}

string song::getGenre(){
    return GENRE;
}


#endif
