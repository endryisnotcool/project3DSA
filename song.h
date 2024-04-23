#ifndef PROJECT3DSA_SONG_H
#define PROJECT3DSA_SONG_H

#include <vector>
#include <string>

using namespace std;

//song class
//makes song objecs
class song {
private:

    //instance variables
    vector<string> ARTIST;
    string TITLE;
    string ALBUM;
    bool EXPLICIT;
    int POPULARITY;
    string TRACKID;
    string GENRE;

public:

    //constructor
    song(vector<string> artist, string title, string album, bool isExplicit, int popularity, string trackID, string genre)
            : ARTIST(artist), TITLE(title), ALBUM(album), EXPLICIT(isExplicit), POPULARITY(popularity), TRACKID(trackID), GENRE(genre) {}

    //getter functions
    vector<string> getArtist() const { return ARTIST; }
    string getTitle() const { return TITLE; }
    string getAlbum() const { return ALBUM; }
    bool isExplicit() const { return EXPLICIT; }
    int getPopularity() const { return POPULARITY; }
    string getTrackID() const { return TRACKID; }
    string getGenre() const { return GENRE; }

    //copy assignment operator
    song& operator = (const song& other) {
        if (this != &other) {
            ARTIST = other.ARTIST;
            TITLE = other.TITLE;
            ALBUM = other.ALBUM;
            EXPLICIT = other.EXPLICIT;
            POPULARITY = other.POPULARITY;
            TRACKID = other.TRACKID;
            GENRE = other.GENRE;
        }
        return *this;
    }
};

//compare by popularity method for sorting
static bool compareByPopularity(const song& a, const song& b) {
    return a.getPopularity() < b.getPopularity();
}

#endif
