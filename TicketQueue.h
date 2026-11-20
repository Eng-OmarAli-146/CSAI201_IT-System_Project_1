// ============================================================================
// TicketQueue.h
// BASE class: a linked FIFO queue (head + tail pointers) of Ticket pointers.
// It does NOT own the tickets, it only owns its own nodes.
//
// These classes are derived from it:
//     RequestQueue    (All_Requests)
//     CompletedQueue  (Completed_List)
//     CancelledQueue  (Cancelled_List)
//     WaitingSRQueue  (Waiting_SR)
//     WaitingNRQueue  (Waiting_NR, adds removeByID)
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"

class TicketQueue
{
protected:
    struct Node
    {
        Ticket* data;
        Node* next;
    };

    Node* head;     // front of the queue (next ticket to leave)
    Node* tail;     // back of the queue (last ticket that arrived)
    int count;

public:
    TicketQueue();
    ~TicketQueue();

    void    enqueue(Ticket* t);          // add at the back          O(1)
    Ticket* dequeue();                   // remove from the front    O(1)
    Ticket* peek() const;                // look at the front        O(1)
    bool    isEmpty() const;             // O(1)
    int     getCount() const;            // O(1)
    void    printIDs() const;            // prints the ticket IDs, "-" if empty   O(n)

    // copies the ticket pointers into a NEW array (the caller must delete[] it)
    Ticket** toArray(int& size) const;   // O(n)

    void clear();                        // frees the nodes only               O(n)
    void clearAndDeleteTickets();        // frees the nodes AND the tickets    O(n)
};
