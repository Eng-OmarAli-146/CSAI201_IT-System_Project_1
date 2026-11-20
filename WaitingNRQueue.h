// ============================================================================
// WaitingNRQueue.h  (Waiting_NR)
// Waiting normal tickets, served FCFS by a GT only.
// Derived from TicketQueue with ONE extra function: removeByID, used when a
// waiting NR is cancelled. In a linked list this is just a pointer update, so
// the order of the other tickets does not change (no shifting like an array).
// ============================================================================
#pragma once
#include "TicketQueue.h"

class WaitingNRQueue : public TicketQueue
{
public:
    Ticket* removeByID(int RID);    // nullptr if not found     O(n)
};
