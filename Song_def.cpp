#include "Song.h"
#include <iomanip>

using namespace std;

Song::Song(string title, string artist, int duration, string filePath) {
    this->title = title;
    this->artist = artist;
    this->duration = duration;
    this->filePath = filePath;
}

string Song::getTitle() const {
    return title;
}

string Song::getArtist() const {
    return artist;
}

int Song::getDuration() const {
    return duration;
}

string Song::getFilePath() const {
    return filePath;
}

void Song::display() const {
    cout << *this << endl;
}

ostream& operator<<(ostream& out, const Song& song) {
    out << song.title << " - "
        << song.artist << " ("
        << song.duration / 60 << ":"
        << (song.duration % 60 < 10 ? "0" : "") << song.duration % 60 << ")";

    return out;
}

istream& operator>>(istream& in, Song& song) {
    cout << "Enter song title: ";
    getline(in >> ws, song.title);

    cout << "Enter artist name: ";
    getline(in, song.artist);

    cout << "Enter duration in seconds: ";

    if (in >> song.duration) {
        if (song.duration < 0) {
            in.setstate(ios::failbit);
        }
    }

    return in;
}