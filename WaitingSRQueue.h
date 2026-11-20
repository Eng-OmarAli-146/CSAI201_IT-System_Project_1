// ============================================================================
// WaitingSRQueue.h  (Waiting_SR)
// Waiting specialist tickets, served FCFS by an ST only.
// SR tickets cannot be cancelled, so a plain FIFO queue is enough.
// It is a separate list from Waiting_NR, so a waiting SR never blocks an NR.
// ============================================================================
#pragma once
#include "TicketQueue.h"

class WaitingSRQueue : public TicketQueue
{
    // nothing to add
};
