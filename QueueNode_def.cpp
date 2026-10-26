#include "Song.h"
#include <iostream>
#include <string>
#include <vector>
#include<filesystem>
#include <cstdlib>
#include "QueueNode.h"

QueueNode::QueueNode(Song s) : song(s), next(nullptr), prev(nullptr)
{
}

Song QueueNode::getSong() const
{
    return song;
}

Song* QueueNode::getSongPtr()
{
    return &song;
}

void QueueNode::setNext(QueueNode* node)
{
    next = node;
}

void QueueNode::setPrev(QueueNode* node)
{
    prev = node;
}

QueueNode* QueueNode::getNext() const
{
    return next;
}

QueueNode* QueueNode::getPrev() const
{
    return prev;
}