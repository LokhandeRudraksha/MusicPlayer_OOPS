#ifndef QUEUENODE_H
#define QUEUENODE_H
#include<filesystem>
#include "Song.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class QueueNode
{
    private:
        QueueNode* next;
        QueueNode* prev;
        Song song;
    
    public:
        QueueNode(Song);
        Song getSong() const;
        Song* getSongPtr();
        void setNext(QueueNode*);
        void setPrev(QueueNode*);
        QueueNode* getNext() const;
        QueueNode* getPrev() const;
};

#endif