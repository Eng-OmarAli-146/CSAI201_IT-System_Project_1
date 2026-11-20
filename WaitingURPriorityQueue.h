// ============================================================================
// WaitingURPriorityQueue.h  (Waiting_UR)
// Array based MAX-HEAP of the waiting urgent tickets.
// The ticket on top is the one that must be served first:
//     higher PR first, then smaller QT, then smaller RID.
// RID is unique, so this rule is a strict order and the result is deterministic.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"

class WaitingURPriorityQueue
{
private:
    Ticket** items;     // the heap is stored in this dynamic array
    int count;
    int capacity;

    bool isBetter(Ticket* a, Ticket* b) const;   // true if a must be served before b
    void grow();
    void siftUp(int index);
    void siftDown(int index);

public:
    WaitingURPriorityQueue();
    ~WaitingURPriorityQueue();

    void    insert(Ticket* t);          // O(log n)
    Ticket* removeHighest();            // O(log n)
    Ticket* peekHighest() const;        // O(1)
    bool    isEmpty() const;            // O(1)
    int     getCount() const;           // O(1)
    void    printIDs() const;           // IDs in scheduling order (works on a copy)   O(n log n)
    void    clear();                    // frees the array only (not the tickets)
};
