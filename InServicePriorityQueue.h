// ============================================================================
// InServicePriorityQueue.h  (In_Service)
// Array based MIN-HEAP of the tickets that technicians are handling now.
// Key: smaller FT first, and smaller RID when the FT is equal.
// At the start of every minute we complete all tickets with FT <= current
// minute, so we only ever need to look at the root.
// The RID tie-break makes tickets that finish in the same minute come out in
// ascending RID, which is the order required in the output file.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"

class InServicePriorityQueue
{
private:
    Ticket** items;
    int count;
    int capacity;

    bool isBefore(Ticket* a, Ticket* b) const;   // true if a finishes before b
    void grow();
    void siftUp(int index);
    void siftDown(int index);
    int  findIndex(int RID) const;               // position in the array, -1 if absent

public:
    InServicePriorityQueue();
    ~InServicePriorityQueue();

    void    insert(Ticket* t);          // ticket gets assigned          O(log T)
    Ticket* peek() const;               // earliest FT, not removed      O(1)
    Ticket* extractMin();               // earliest FT, removed          O(log T)
    Ticket* getByID(int RID) const;     // nullptr if not in service     O(T)
    Ticket* removeByID(int RID);        // cancel an assigned NR         O(T)
    bool    isEmpty() const;            // O(1)
    int     getCount() const;           // O(1)
    void    clear();                    // frees the array only (not the tickets)
};
