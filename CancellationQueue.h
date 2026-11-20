// ============================================================================
// CancellationQueue.h  (All_Cancellations)
// Linked FIFO queue of the cancellation records "CT RID" from the input file.
// The file is sorted by CT, so the front is always the next one to process.
// ============================================================================
#pragma once
#include "Definitions.h"

class CancellationQueue
{
private:
    struct Node
    {
        CancellationRequest data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

public:
    CancellationQueue();
    ~CancellationQueue();

    void enqueue(const CancellationRequest& request);    // O(1)
    bool dequeue(CancellationRequest& request);          // false if empty   O(1)
    bool peek(CancellationRequest& request) const;       // false if empty   O(1)
    bool isEmpty() const;                                // O(1)
    int  getCount() const;                               // O(1)
    void print() const;                                  // O(n)
    void clear();                                        // O(n)
};
