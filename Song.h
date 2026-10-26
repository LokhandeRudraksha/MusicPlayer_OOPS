#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>

class Song {
private:
    std::string title;
    std::string artist;
    int duration;
    std::string filePath;

public:
    Song(std::string title = "",
         std::string artist = "",
         int duration = 0,
         std::string filePath = "");

    std::string getTitle() const;
    std::string getArtist() const;
    int getDuration() const;
    std::string getFilePath() const;

    void display() const;

    friend std::ostream& operator<<(std::ostream& out, const Song& song);
    friend std::istream& operator>>(std::istream& in, Song& song);
};

#endif