#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

// Prevent Windows headers included by miniaudio from defining conflicting byte types
#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0

#include "miniaudio.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>
#include "Song.h"
#include "songqueue.h"
#include "QueueNode.h"

class MusicPlayer
{
    private:
        std::vector<Song> availableSongs;
        SongQueue playQueue;
        int volume;
        bool isPlaying;
        
        ma_engine engine;
        ma_sound sound;
        bool engineInitialized;

        void playCurrentTrack();
    
    public:
        MusicPlayer();
        ~MusicPlayer();
        void loadSongsFromFolder(const std::string &);
        void displayLibrary() const;
        void addSongToQueue(int);
        void startPlayback();
        void pauseSong();
        void resumeSong();
        void next();
        void previous();
        void volumeUp();
        void volumeDown();
        void searchSong(const std::string &);
        void showQueue() const;
};

#endif