#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "MusicPlayer.h"
#include "Song.h"
#include "songqueue.h"
#include "QueueNode.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <filesystem>
#include <cctype>

namespace fs = std::filesystem;
using namespace std;

MusicPlayer::MusicPlayer()
{
    volume = 50;
    isPlaying = false;
    engineInitialized = (ma_engine_init(NULL, &engine) == MA_SUCCESS);
}

MusicPlayer::~MusicPlayer()
{
    if (isPlaying) {
        ma_sound_uninit(&sound);
    }
    if (engineInitialized) {
        ma_engine_uninit(&engine);
    }
}

void MusicPlayer::playCurrentTrack() 
{
    Song* current = playQueue.getCurrentSong();
    if (!current) 
    {
        cout << "No song currently selected in queue.\n";
        return;
    }

    if (isPlaying) {
        ma_sound_stop(&sound);
        ma_sound_uninit(&sound);
        isPlaying = false;
    }

    if (engineInitialized) {
        if (ma_sound_init_from_file(&engine, current->getFilePath().c_str(), 0, NULL, NULL, &sound) == MA_SUCCESS) {
            // Convert integer percentage (0-100) to float scale (0.0f - 1.0f)
            ma_sound_set_volume(&sound, static_cast<float>(volume) / 100.0f);
            ma_sound_start(&sound);
            isPlaying = true;
            cout << "\n >>> NOW PLAYING: " << current->getTitle() << " (Volume: " << volume << "%) <<<\n";
        } else {
            cout << "Error: Could not load or decode audio file: " << current->getFilePath() << "\n";
        }
    }
}

void MusicPlayer::loadSongsFromFolder(const string& folderPath) 
{
    string cleanPath = folderPath;
    // Strip surrounding quotes if user copied path with quotes
    if (!cleanPath.empty() && (cleanPath.front() == '"' || cleanPath.front() == '\'')) {
        cleanPath.erase(0, 1);
    }
    if (!cleanPath.empty() && (cleanPath.back() == '"' || cleanPath.back() == '\'')) {
        cleanPath.pop_back();
    }

    if (!fs::exists(cleanPath) || !fs::is_directory(cleanPath)) 
    {
        cout << "Invalid directory path: " << cleanPath << "!\n";
        return;
    }

    availableSongs.clear();
    for (const auto& entry : fs::directory_iterator(cleanPath)) 
    {
        if (entry.is_regular_file()) 
        {
            string ext = entry.path().extension().string();
            // Convert extension to lowercase for robust matching
            for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

            if (ext == ".mp3" || ext == ".wav" || ext == ".flac") 
            {
                string filename = entry.path().stem().string();
                string fullPath = entry.path().string();
                availableSongs.emplace_back(filename, "Unknown", 0, fullPath);
            }
        }
    }
    cout << "Successfully loaded " << availableSongs.size() << " songs from folder.\n";
}

void MusicPlayer::displayLibrary() const 
{
    if (availableSongs.empty()) 
    {
        cout << "No songs found in library. Load a folder first.\n";
        return;
    }
    cout << "\n=== Song Library ===\n";
    for (size_t i = 0; i < availableSongs.size(); ++i) 
    {
        cout << i + 1 << ". " << availableSongs[i].getTitle() << "\n";
    }
    cout << "====================\n";
}

void MusicPlayer::addSongToQueue(int index) 
{
    if (index < 1 || index > static_cast<int>(availableSongs.size())) 
    {
        cout << "Invalid song index!\n";
        return;
    }
    playQueue.enqueue(availableSongs[index - 1]);
}

void MusicPlayer::startPlayback() 
{
    if (playQueue.isEmpty()) 
    {
        cout << "Queue is empty! Add songs to queue first.\n";
        return;
    }
    playCurrentTrack();
}

void MusicPlayer::pauseSong() 
{
    if (isPlaying) 
    {
        ma_sound_stop(&sound);
        isPlaying = false;
        cout << "Playback paused.\n";
    } else 
    {
        cout << "Player is already paused or stopped.\n";
    }
}

void MusicPlayer::resumeSong() 
{
    if (!isPlaying && playQueue.getCurrentSong()) 
    {
        ma_sound_start(&sound);
        isPlaying = true;
        cout << "Playback resumed.\n";
    }
}

void MusicPlayer::next() 
{
    if (playQueue.nextSong()) 
    {
        playCurrentTrack();
    } else 
    {
        cout << "End of queue reached.\n";
    }
}

void MusicPlayer::previous() 
{
    if (playQueue.prevSong()) 
    {
        playCurrentTrack();
    } else 
    {
        cout << "This is the first song in the queue.\n";
    }
}

void MusicPlayer::volumeUp() 
{
    if (volume < 100) {
        volume += 10;
    } else {
        volume = 100;
    }

    // Apply to current playing sound if active
    if (isPlaying && engineInitialized) {
        ma_sound_set_volume(&sound, static_cast<float>(volume) / 100.0f);
    }
    
    cout << "Volume increased to " << volume << "%\n";
}

void MusicPlayer::volumeDown() 
{
    if (volume > 0) {
        volume -= 10;
    } else {
        volume = 0;
    }

    // Apply to current playing sound if active
    if (isPlaying && engineInitialized) {
        ma_sound_set_volume(&sound, static_cast<float>(volume) / 100.0f);
    }

    cout << "Volume decreased to " << volume << "%\n";
}


void MusicPlayer::searchSong(const string& query)
{
    cout << "\n--- Search Results for \"" << query << "\" ---\n";
    bool found = false;
    for (size_t i = 0; i < availableSongs.size(); ++i) 
    {
        if (availableSongs[i].getTitle().find(query) != string::npos) 
        {
            cout << i + 1 << ". " << availableSongs[i].getTitle() << "\n";
            found = true;
        }
    }
    if (!found) 
        cout << "No matching songs found.\n";
    cout << "------------------------------------\n";
}

void MusicPlayer::showQueue() const 
{
    playQueue.displayQueue();
}