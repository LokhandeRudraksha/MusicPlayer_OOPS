#ifndef SONG_QUEUE_H
#define SONG_QUEUE_H

#include <string>
#include <iostream>
#include "Song.h"
#include "QueueNode.h"

class SongQueue {
private:
    QueueNode* head;
    QueueNode* tail;
    QueueNode* current;

public:
    SongQueue();
    ~SongQueue();

    void enqueue(Song song);
    bool isEmpty() const;
    Song* getCurrentSong();
    bool nextSong();
    bool prevSong();
    void displayQueue() const;
};

#endif