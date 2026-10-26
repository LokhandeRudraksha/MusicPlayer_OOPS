#include "Song.h"
#include "songqueue.h"
#include "QueueNode.h"
#include <iostream>
#include <string>

SongQueue::SongQueue() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
}

SongQueue::~SongQueue() {
    QueueNode* temp = head;
    while (temp) {
        QueueNode* nextNode = temp->getNext();
        delete temp;
        temp = nextNode;
    }
}

void SongQueue::enqueue(Song Song) {
    QueueNode* newNode = new QueueNode(Song);
    if (!head) {
        head = tail = current = newNode;
    }
    else {
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    std::cout << "Added to queue: " << Song.getTitle() << "\n";
}

bool SongQueue::isEmpty() const { 
    return head == nullptr; 
}

Song* SongQueue::getCurrentSong() {
    if (current) {
        return current->getSongPtr();
    }
    return nullptr;
}

bool SongQueue::nextSong() {
    if (current && current->getNext()) {
        current = current->getNext();
        return true;
    }
    return false;
}

bool SongQueue::prevSong() {
    if (current && current->getPrev()) {
        current = current->getPrev();
        return true;
    }
    return false;
}

void SongQueue::displayQueue() const {
    if (!head) {
        std::cout << "Queue is empty.\n";
        return;
    }
    std::cout << "\n--- Current Song Queue ---\n";
    QueueNode* temp = head;
    int index = 1;
    while (temp) {
        std::cout << (temp == current ? " -> " : "    ")
            << index++ << ". " << temp->getSong().getTitle() << "\n";
        temp = temp->getNext();
    }
    std::cout << "--------------------------\n";
}