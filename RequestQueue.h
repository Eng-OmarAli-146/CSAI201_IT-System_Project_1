// ============================================================================
// RequestQueue.h  (All_Requests)
// Every request loaded from the input file, in file order.
// The file is sorted by QT, so the front is always the next request to release.
// ============================================================================
#pragma once
#include "TicketQueue.h"

class RequestQueue : public TicketQueue
{
    // nothing to add: enqueue / dequeue / peek come from TicketQueue
};
